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

using namespace fsn;


Wedge::Wedge(char type)
: Component(type), DirectedComponent(type), value(2) {}

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
	bool destroy = (atom.dir == dir);
	
	
	
	return destroy;
}

