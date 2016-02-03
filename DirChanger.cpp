//
//  DirChanger.cpp
//  Fission
//
//  Created by C0deH4cker on 2/25/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "DirChanger.h"
#include "common.h"
#include "Component.h"
#include "Atom.h"

using namespace fsn;


Direction DirChanger::getDir(Token type) {
	switch(type) {
		case Token::SPAWNER_UP:    case Token::DIR_UP:    return UP;
		case Token::SPAWNER_LEFT:  case Token::DIR_LEFT:  return LEFT;
		case Token::SPAWNER_DOWN:  case Token::DIR_DOWN:  return DOWN;
		case Token::SPAWNER_RIGHT: case Token::DIR_RIGHT: return RIGHT;
			
		default:
			fatal("Cell '%c' is not a DirChanger.", (char)type);
	}
}

DirChanger::DirChanger(Token type)
: Component(type), DirectedComponent(type) {}

Direction DirChanger::getDir() const {
	return getDir(type);
}

bool DirChanger::onHit(Atom& atom) {
	atom.dir = getDir();
	return false;
}

