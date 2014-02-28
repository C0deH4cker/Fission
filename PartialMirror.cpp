//
//  PartialMirror.cpp
//  Fission
//
//  Created by C0deH4cker on 2/26/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "PartialMirror.h"
#include "Component.h"
#include "Grid.h"
#include "Atom.h"
#include "Errors.h"

using namespace fsn;


PartialMirror::PartialMirror(char type, Grid& grid)
: Component(type), grid(grid) {}

bool PartialMirror::onHit(Atom& atom) {
	switch(type) {
		case ':': {
			int smaller = atom.mass >> 1;
			atom.mass -= smaller;
			
			Atom reflected(atom);
			atom.dir ^= 2;
			atom.mass = smaller;
			
			grid.spawn(reflected);
			break;
		}
		
		case 'X': {
			Atom reflected(atom);
			reflected.dir ^= 2;
			
			grid.spawn(reflected);
			break;
		}
		
		default:
			fatal("Cell '%c' is not a PartialMirror.", type);
	}
	
	return false;
}

