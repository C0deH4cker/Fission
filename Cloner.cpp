//
//  Cloner.cpp
//  Fission
//
//  Created by C0deH4cker on 2/27/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Cloner.h"
#include "common.h"
#include "Grid.h"

using namespace fsn;


Cloner::Cloner(Token type, Grid& grid)
: Component(type), DirectedComponent(type), grid(grid), stored(UNKNOWN), multiplier(1), adder(0) {}


bool Cloner::onHit(Atom& atom) {
	Direction dir = getDir();
	
	if(atom.dir == dir) {
		// The atom hit the back of the cloner, so store its mass
		multiplier = atom.mass;
		adder = atom.energy;
		return true;
	}
	
	if((atom.dir ^ 2) == dir) {
		// The atom hit the vertex, so clone it because the law of conservation
		// of mass totally says this is okay and cool to do
		atom.mass *= multiplier;
		atom.energy += adder;
		atom.dir = (atom.dir + 1) & 3;
		
		Atom clone(atom);
		clone.dir ^= 2;
		grid.spawn(clone);
	}
	else {
		// The atom hit a side of the cloner
		if(stored != (atom.dir ^ 2)) {
			// Either no atom was stored, or it was on the same side
			waiting = atom;
			stored = atom.dir;
			return true;
		}
		
		// Combine the two atoms
		atom += waiting;
		atom.dir = dir;
		
		// No longer storing an atom
		stored = UNKNOWN;
	}
	
	return false;
}

Direction Cloner::getDir() const {
	switch(type) {
		case Token::CLONER_UP:    return UP;
		case Token::CLONER_LEFT:  return LEFT;
		case Token::CLONER_DOWN:  return DOWN;
		case Token::CLONER_RIGHT: return RIGHT;
		
		default:
			fatal("Cell '%c' is not a Cloner.", (char)type);
	}
}

