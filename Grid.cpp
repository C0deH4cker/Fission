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
#include <map>
#include <set>
#include <unordered_set>
#include <unistd.h>
#include <limits.h>
#include "macros.h"
#include "tokens.h"
#include "Atom.h"
#include "Component.h"
#include "DynamicComponent.h"
#include "Fission.h"
#include "Teleporter.h"

using namespace fsn;


Grid::Grid(std::istream& src, bool skipShebang)
: width(0), height(0), indices{0}, stop(false), status(0) {
	std::vector<std::string> prog;
	std::string line;
	
	// Read the first line but don't process it
	if(skipShebang) {
		std::getline(src, line);
	}
	
	// Read in every line, keeping track of the longest one
	while(std::getline(src, line)) {
		if(line.size() > INT_MAX) {
			// Just skip it
			continue;
		}
		
		if(width < (int)line.size()) {
			width = (int)line.size();
		}
		
		prog.push_back(line);
	}
	
	height = (int)prog.size();
	cells.reserve(height);
	
	// Convert the character grid to components
	for(int i = 0; i < height; i++) {
		std::vector<Component*> row;
		row.reserve(width);
		
		for(int j = 0; j < width; j++) {
			Component* comp;
			if(j >= (int)prog[i].size()) {
				// Default to ' ' if after EOL
				comp = new Component(' ');
			}
			else {
				comp = Component::create(prog[i][j], *this, {j, i});
			}
			
			row.push_back(comp);
		}
		
		cells.push_back(row);
	}
}

Grid::~Grid() {
	for(size_t i = 0; i < cells.size(); i++) {
		for(size_t j = 0; j < cells[i].size(); j++) {
			delete cells[i][j];
		}
	}
}

void Grid::tick(Fission& mgr, bool trace) {
	std::priority_queue<Atom, std::vector<Atom>, std::greater<Atom>> next;
	
	int i = 0;
	if(trace) {
		usleep(1000*1000 / 4);
		std::cerr << std::endl;
	}
	
	// Tick all dynamic components
	std::unordered_set<DynamicComponent*>::iterator dyn = dynamics.begin();
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
		
		if(trace) {
			Point tracePos{i % width, i / width};
			while(tracePos < cur.pos) {
				// Print the component
				std::cerr.put(cells[i / width][i % width]->getType());
				
				if(++i % width == 0) {
					std::cerr << std::endl;
				}
				
				tracePos = Point{i % width, i / width};
			}
			
			// Check to make sure only one atom is printed per point
			if(cur.pos == tracePos) {
				// Print the atom
				std::cerr << "\u269b";
				
				if(++i % width == 0) {
					std::cerr << std::endl;
				}
			}
		}
		
		// Move the atom
		next.push(cur.move(width, height));
	}
	
	if(trace) {
		while(i < width * height) {
			// Print the component
			std::cerr.put(cells[i / width][i % width]->getType());
			
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
		Component* comp = cells[cur.pos.y][cur.pos.x];
		
		if(cur.printing && comp->getType() != TOK_IO_OUTSTR) {
			// If the atom is in printing mode, print the component's char
			std::cout.put(comp->getType());
			++cur.mass;
		}
		else if(cur.setting) {
			cur.mass = comp->getType();
			cur.setting = false;
		}
		else if(comp->onHit(cur) || cur.mass < 0) {
			// Process the hit, and don't add the atom again if it's destroyed
			continue;
		}
		
		// Add the atom back in
		atoms.push(cur);
	}
	
	// No atoms left and no ticking components?
	if((atoms.empty() && dynamics.empty()) || stop) {
		mgr.terminate(status);
	}
}

void Grid::spawn(const Atom& atom) {
	atoms.push(atom);
}

void Grid::teleport(Atom& atom, int number, int from) {
	const std::vector<Point>& tp(teleporters[number]);
	atom.pos = tp[(from + 1) % tp.size()];
}

Teleporter* Grid::addTeleporter(char type, Point pt) {
	int num = type - '0';
	teleporters[num].push_back(pt);
	return new Teleporter(type, *this, indices[num]++);
}

void Grid::addDynamic(DynamicComponent* dyn) {
	dynamics.insert(dyn);
}

void Grid::removeDynamic(DynamicComponent* dyn) {
	dynamics.erase(dyn);
}

void Grid::terminate(int status) {
	stop = true;
	this->status = status;
}

