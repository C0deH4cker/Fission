//
//  Wedge.cpp
//  Fission
//
//  Created by C0deH4cker on 2/24/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Wedge.h"
#include "Atom.h"
#include "Component.h"
#include "Direction.h"
#include "Errors.h"
#include "Grid.h"

using namespace fsn;


Wedge::Wedge(char type, Grid& grid)
: Component(type), DirectedComponent(type), value(2), grid(grid) {}

Direction Wedge::getDir() const {
	switch(type) {
		case '^': return UP;
		case '<': return LEFT;
		case 'V': return DOWN;
		case '>': return RIGHT;
		
		default:
			fatal("Cell '%c' is not a Wedge.", type);
	}
}

bool Wedge::onHit(Atom& atom) {
	Direction dir(getDir());
	
	if(atom.dir == dir) {
		// Hit the inside of the fork, so consume the atom
		value = atom.mass;
		return true;
	}
	
	if((atom.dir ^ 2) == dir) {
		// The atom hit the vertex, so split the atom.
		//
		// WARNING: DO NOT TRY THIS AT HOME. SPLITTING ATOMS IS ONLY TO BE DONE
		// BY TRAINED PROFESSIONALS. BY USING THE PRODUCT YOU ACKNOWLEDGE THAT
		// THERE IS NO WARRANTY, EXPRESS OR IMPLIED,	 AND THAT C0deH4cker IS NOT
		// LIABLE FOR ANY INJURIES, DECAPITATIONS, OR SPONTANEOUS COMBUSTIONS
		// THAT MAY RESULT FROM YOUR USE OF THE PRODUCT. IF THE WORLD AND/OR
		// UNIVERSE COME TO A FIERY END AS A RESULT OF SPLITTING ATOMS WITH
		// THE PRODUCT, C0deH4cker IS NOT TO BE HELD RESPONSIBLE IN ANY WAY.
		//
		// Have fun!
		int left = atom.mass / value;
		atom.mass -= left;
		atom.dir = (dir + 1) & 3;
		
		Atom split(atom);
		split.mass = left;
		split.dir = (dir + 3) & 3;
		
		grid.spawn(split);
	}
	else {
		atom.dir = dir;
	}
	
	return false;
}

