//
//  Jumper.cpp
//  Fission
//
//  Created by C0deH4cker on 3/5/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Jumper.h"
#include "Component.h"
#include "Atom.h"

using namespace fsn;


Jumper::Jumper(Token type, int width, int height)
: Component(type), width(width), height(height) {}


bool Jumper::onHit(Atom& atom) {
	atom = atom.move(width, height, atom.energy);
	atom.energy = 0;
	
	return false;
}

