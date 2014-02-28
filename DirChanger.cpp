//
//  DirChanger.cpp
//  Fission
//
//  Created by C0deH4cker on 2/25/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "DirChanger.h"
#include "DirectedComponent.h"
#include "Component.h"
#include "Errors.h"
#include "Atom.h"
#include "Direction.h"

using namespace fsn;


DirChanger::DirChanger(char type)
: Component(type), DirectedComponent(type) {}

Direction DirChanger::getDir() const {
	switch(type) {
		case 'U': case 'W': return UP;
		case 'L': case ']': return LEFT;
		case 'D': case 'M': return DOWN;
		case 'R': case '[': return RIGHT;
			
		default:
			fatal("Cell '%c' is not a DirChanger.", type);
	}
}

bool DirChanger::onHit(Atom& atom) {
	atom.dir = getDir();
	return false;
}

