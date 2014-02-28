//
//  DirChanger.cpp
//  Fission
//
//  Created by C0deH4cker on 2/25/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "DirChanger.h"
#include "macros.h"
#include "DirectedComponent.h"
#include "Component.h"
#include "Atom.h"
#include "Direction.h"

using namespace fsn;


Direction DirChanger::getDir(char type) {
	switch(type) {
		case 'U': case 'W': return UP;
		case 'L': case ']': return LEFT;
		case 'D': case 'M': return DOWN;
		case 'R': case '[': return RIGHT;
			
		default:
			fatal("Cell '%c' is not a DirChanger.", type);
	}
}

DirChanger::DirChanger(char type)
: Component(type), DirectedComponent(type) {}

Direction DirChanger::getDir() const {
	return getDir(type);
}

bool DirChanger::onHit(Atom& atom) {
	atom.dir = getDir();
	return false;
}

