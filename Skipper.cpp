//
//  Skipper.cpp
//  Fission
//
//  Created by C0deH4cker on 3/21/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Skipper.h"
#include "common.h"
#include "Component.h"
#include "Atom.h"
#include "Direction.h"

using namespace fsn;


Skipper::Skipper(Token type, int prevX, int nextX, int prevY, int nextY)
: Component(type), prevX(prevX), prevY(prevY), nextX(nextX), nextY(nextY) {}


bool Skipper::onHit(Atom& atom) {
	switch(atom.dir) {
		case UP:
			atom.pos.y = prevY;
			break;
		
		case LEFT:
			atom.pos.x = prevX;
			break;
		
		case DOWN:
			atom.pos.y = nextY;
			break;
		
		case RIGHT:
			atom.pos.x = nextX;
			break;
		
		
		default:
			fatal("Invalid direction: %hhu\n", atom.dir);
	}
	
	return false;
}

