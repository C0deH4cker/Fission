//
//  Grid.cpp
//  Fission
//
//  Created by C0deH4cker on 2/23/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Grid.h"
#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <sstream>
#include <unistd.h>
#include "Component.h"
#include "DynamicComponent.h"
#include "Fission.h"

using namespace fsn;


Grid::Grid(std::istream& src, bool skipShebang)
: status(INT_MIN), stop(false), width(0), height(0), telcount{0} {
	std::vector<std::string> prog;
	std::string line;
	
	// Read the first line but don't process it
	if(skipShebang) {
		std::getline(src, line);
	}
	
	// Read in every line, keeping track of the longest one
	while(std::getline(src, line)) {
		if(line.size() > width) {
			width = (int)line.size();
		}
		
		prog.push_back(line);
	}
	
	height = (int)prog.size();
	cells.reserve(height);
	
	// Convert the character grid to components
	for(int i = 0; i < height; i++) {
		std::vector<std::shared_ptr<Component>> row;
		row.reserve(width);
		
		for(int j = 0; j < width; j++) {
			std::shared_ptr<Component> comp;
			if(j >= prog[i].size()) {
				// Default to ' ' if after EOL
				comp = std::make_shared<Component>(Token::EMPTY);
			}
			else {
				comp = Component::create((Token)prog[i][j], *this, {j, i});
			}
			
			row.push_back(comp);
		}
		
		cells.push_back(row);
	}
}

void Grid::tick(Fission& mgr, bool trace) {
	std::priority_queue<Atom, std::vector<Atom>, std::greater<Atom>> next;
	std::unordered_set<Point> printed;
	std::stringstream gridtrace;
	
	int i = 0;
	if(trace) {
		usleep(1000*1000 / 4);
		std::cerr << std::endl;
	}
	
	// Tick all dynamic components
	auto dyn = dynamics.begin();
	while(dyn != dynamics.end()) {
		// Tick the component
		if(!(*dyn)->onTick()) {
			// Stop ticking
			dyn = dynamics.erase(dyn);
		}
		else {
			++dyn;
		}
	}
	
	// Move all atoms and store them in a new atom map
	while(!atoms.empty()) {
		Atom cur(atoms.top());
		atoms.pop();
		
		if(trace && printed.find(cur.pos) == printed.end()) {
			while(Point{i % width, i / width} < cur.pos) {
				// Print the component
				std::cerr.put((char)cells[i / width][i % width]->getType());
				
				if(++i % width == 0) {
					std::cerr << std::endl;
				}
			}
			
			// Print the atom
			std::cerr << "\u269b";
			
			if(++i % width == 0) {
				std::cerr << std::endl;
			}
		}
		
		// Move the atom
		next.push(cur.move(width, height));
	}
	
	if(trace) {
		while(i < width * height) {
			// Print the component
			std::cerr.put((char)cells[i / width][i % width]->getType());
			
			if(++i % width == 0) {
				std::cerr << std::endl;
			}
		}
		std::cerr << std::endl;
	}
	
	// Process each new collision
	while(!next.empty()) {
		// Pop the top atom
		Atom cur(next.top());
		next.pop();
		
		// Get the atom's position and the component it's on
		std::shared_ptr<Component> comp = cells[cur.pos.y][cur.pos.x];
		
		if((cur.flags & AtomicFlags::Printing) != AtomicFlags::None
		   && comp->getType() != Token::IO_OUTSTR) {
			// If the atom is in printing mode, print the component's char
			std::cout.put((char)comp->getType());
			++cur.mass;
		}
		else if((cur.flags & AtomicFlags::Setting) != AtomicFlags::None) {
			cur.mass = (char)comp->getType();
			cur.flags &= ~AtomicFlags::Setting;
		}
		else if(comp->onHit(cur)) {
			// Process the hit, and don't add the atom again if it's destroyed
			continue;
		}
		
		// Add the atom back in
		atoms.push(cur);
	}
	
	// No atoms left and no ticking components?
	if((atoms.empty() && dynamics.empty()) || stop) {
		mgr.terminate(stop ? status : 0);
	}
}

void Grid::spawn(const Atom& atom) {
	atoms.push(atom.activate());
}

void Grid::teleport(Atom& atom, int channel, int from) {
	const std::vector<Point>& tp(teleporters[channel]);
	atom.pos = tp[(from + 1) % tp.size()];
}

std::shared_ptr<Teleporter> Grid::addTeleporter(Token type, Point pt) {
	int channel = Teleporter::getChannel(type);
	teleporters[channel].push_back(pt);
	return std::make_shared<Teleporter>(type, *this, telcount[channel]++);
}

std::shared_ptr<Skipper> Grid::addSkipper(Token type, Point pt) {
	// Store the next and previous x and y values for every skipper, because
	// just doing a linear sweep is too mainstream. At least this makes skipping
	// be an O(1) action. Sacrificing a tiny bit of time while reading the grid
	// in to make runtime actions more efficient is always better than quick
	// initialization but slow runtime.
	std::map<int, std::shared_ptr<Skipper>>& row = skipRows[pt.y];
	std::map<int, std::shared_ptr<Skipper>>& col = skipCols[pt.x];
	
	// At first, the previous and next location is itself because of wraparound
	int prevX = pt.x, nextX = pt.x, prevY = pt.y, nextY = pt.y;
	
	auto it = row.begin();
	if(it != row.end()) {
		// This new item's next x is the first item's x
		nextX = it->first;
		// The first item's previous x is this new item's x
		it->second->prevX = pt.x;
		
		auto rit = row.rbegin();
		// This new item's prev x is the last item's x
		prevX = rit->first;
		// The last item's next x is this new item's x
		rit->second->nextX = pt.x;
	}
	
	it = col.begin();
	if(it != col.end()) {
		// This new item's next y is the first item's y
		nextY = it->first;
		// The first item's previous y is this new item's y
		it->second->prevY = pt.y;
		
		auto rit = col.rbegin();
		// This new item's prev y is the last item's y
		prevY = rit->first;
		// The last item's next y is this new item's y
		rit->second->nextY = pt.y;
	}
	
	// Create the skipper and save pointers to it for later use
	std::shared_ptr<Skipper> ret = std::make_shared<Skipper>(type, prevX, nextX, prevY, nextY);
	row[pt.x] = col[pt.y] = ret;
	
	return ret;
}

void Grid::addDynamic(std::shared_ptr<DynamicComponent> dyn) {
	dynamics.insert(dyn);
}

void Grid::removeDynamic(std::shared_ptr<DynamicComponent> dyn) {
	dynamics.erase(dyn);
}

void Grid::terminate(int status) {
	stop = true;
	this->status = std::max(this->status, status);
}

