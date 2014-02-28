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
#include "Atom.h"
#include "Component.h"
#include "DynamicComponent.h"
#include "Fission.h"

using namespace fsn;


Grid::Grid(std::istream& src)
: status(0), stop(false), width(0), height(0) {
	std::vector<std::string> prog;
	std::string line;
	
	// Read in every line, keeping track of the longest one
	while(getline(src, line)) {
		if(line.size() > width) {
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
			if(j >= prog[i].size()) {
				// Default to ' ' if after EOL
				comp = new Component(' ');
			}
			else {
				comp = Component::create(prog[i][j], *this, {j, i});
				
				// Handle teleporters
				if(isdigit(prog[i][j])) {
					teleporters[prog[i][j] - '0'].insert({j, i});
				}
			}
			
			row.push_back(comp);
		}
		
		cells.push_back(row);
	}
}

Grid::~Grid() {
	for(int i = 0; i < cells.size(); i++) {
		for(int j = 0; j < cells[i].size(); j++) {
			delete cells[i][j];
		}
	}
}

//#define DEBUGGING
void Grid::tick(Fission& mgr) {
	std::priority_queue<Atom, std::vector<Atom>, std::greater<Atom> > next;
	
#ifdef DEBUGGING
	int i = 0;
	std::cerr.put('\n');
#endif
	
	// Move all atoms and store them in a new atom map
	while(!atoms.empty()) {
		Atom cur(atoms.top());
		atoms.pop();
		
#ifdef DEBUGGING
		while(Point{i % width, i / width} < cur.pos) {
			std::cerr.put(cells[i / width][i % width]->getType());
			
			if(++i % width == 0) {
				std::cerr.put('\n');
			}
		}
		std::cerr << "";
		if(++i % width == 0) {
			std::cerr.put('\n');
		}
#endif
		
		// See if this atom was teleported last tick
		std::map<Atom, int>::iterator t(teleported.find(cur));
		if(t != teleported.end()) {
			// Perform the teleportation
			std::set<Point>& tp(teleporters[t->second]);
			
			// At least 2 teleporters of this index
			if(tp.size() >= 2) {
				// Find the next teleporter by order
				bool moved = false;
				for(auto it = tp.begin(); it != tp.end(); ++it) {
					if(*it > cur.pos) {
						// Jump there
						cur.pos = *it;
						moved = true;
					}
				}
				
				// If it didn't find a bigger one, go to the first teleporter
				if(!moved) {
					cur.pos = *tp.begin();
				}
			}
			
			// Remove the atom once it has been successfully teleported.
			teleported.erase(t);
		}
		
		// Move the atom
		next.push(cur.move(width, height));
	}
	
#ifdef DEBUGGING
	while(i < width * height) {
		if(i % width == 0) {
			std::cerr.put('\n');
		}
		
		std::cerr.put(cells[i / width][i % width]->getType());
		++i;
	}
	std::cerr.put('\n');
#endif
	
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
	
	// Process each new collision
	while(!next.empty()) {
		// Pop the top atom
		Atom cur(next.top());
		next.pop();
		
		// Get the atom's position and the component it's on
		Component* comp = cells[cur.pos.y][cur.pos.x];
		
		if(cur.printing && comp->getType() != '\'') {
			// If the atom is in printing mode, print the component's char
			std::cout.put(comp->getType());
			++cur.mass;
		}
		else if(cur.jumping) {
			cur.jumping = false;
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

void Grid::teleport(const Atom& atom, int index) {
	teleported[atom] = index;
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

