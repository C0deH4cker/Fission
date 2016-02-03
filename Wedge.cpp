//
//  Wedge.cpp
//  Fission
//
//  Created by C0deH4cker on 2/24/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Wedge.h"
#include <cstdint>
#include "common.h"
#include "Grid.h"

using namespace fsn;


Wedge::Wedge(Token type, Grid& grid)
: Component(type), DirectedComponent(type), grid(grid), saved{2, 0} {}

Direction Wedge::getDir() const {
	switch(type) {
		case Token::WEDGE_UP:    return UP;
		case Token::WEDGE_LEFT:  return LEFT;
		case Token::WEDGE_DOWN:  return DOWN;
		case Token::WEDGE_RIGHT: return RIGHT;
		
		default:
			fatal("Cell '%c' is not a Wedge.", (char)type);
	}
}

bool Wedge::onHit(Atom& atom) {
	Direction dir(getDir());

	if(atom.dir == dir) {
		// Hit the inside of the fork, so consume the atom
		saved = atom;
		
		// Store 1 instead of 0 to prevent div by zero
		if(saved.mass == 0) {
			++saved.mass;
		}
		
		return true;
	}
	
	if((atom.dir ^ 2) == dir) {
		// The atom hit the vertex, so split the atom.
		//
		// WARNING: DO NOT TRY THIS AT HOME. SPLITTING ATOMS IS ONLY TO BE DONE
		// BY TRAINED PROFESSIONALS. BY USING THE PRODUCT YOU ACKNOWLEDGE THAT
		// THERE IS NO WARRANTY, EXPRESS OR IMPLIED, AND THAT THE AUTHOR IS NOT
		// LIABLE FOR ANY INJURIES, DECAPITATIONS, OR SPONTANEOUS COMBUSTIONS
		// THAT MAY RESULT FROM YOUR USE OF THE PRODUCT. IF THE WORLD AND/OR
		// UNIVERSE COME TO A FIERY END AS A RESULT OF SPLITTING ATOMS WITH
		// THE PRODUCT, THE AUTHOR IS NOT TO BE HELD RESPONSIBLE IN ANY WAY.
		//
		// Have fun!
		int64_t left = atom.mass / saved.mass;
		atom.mass -= left;
		atom.energy -= saved.energy;
		atom.dir = (dir + 1) & 3;
		
		Atom split(atom);
		split.mass = left;
		split.dir = atom.dir ^ 2;
		
		grid.spawn(split);
	}
	else {
		atom.dir = dir;
	}
	
	return false;
}

