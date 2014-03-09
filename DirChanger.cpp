//
//  DirChanger.cpp
//  Fission
//
//  Created by C0deH4cker on 2/25/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "DirChanger.h"
#include "macros.h"
#include "tokens.h"
#include "DirectedComponent.h"
#include "Component.h"
#include "Atom.h"
#include "Direction.h"

using namespace fsn;


Direction DirChanger::getDir(char type) {
	switch(type) {
		case TOK_SPAWNER_UP:    case TOK_DIR_UP:	    return UP;
		case TOK_SPAWNER_LEFT:  case TOK_DIR_LEFT:  return LEFT;
		case TOK_SPAWNER_DOWN:  case TOK_DIR_DOWN:  return DOWN;
		case TOK_SPAWNER_RIGHT: case TOK_DIR_RIGHT: return RIGHT;
			
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

