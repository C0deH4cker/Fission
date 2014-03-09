//
//  Mirror.cpp
//  Fission
//
//  Created by C0deH4cker on 2/24/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Mirror.h"
#include <cstdlib>
#include "macros.h"
#include "tokens.h"
#include "Atom.h"
#include "Direction.h"

using namespace fsn;


Mirror::Mirror(char type)
: Component(type) {}

bool Mirror::onHit(Atom& atom) {
	bool destroy = false;
	
	switch(type) {
		case TOK_MIRROR_URDL:
			// 00:11, 01:10, 10:01, 11:00
			atom.dir ^= 3;
			break;
		
		case TOK_MIRROR_ULDR:
			// 00:01, 01:00, 10:11, 11:10
			atom.dir ^= 1;
			break;
		
		case TOK_MIRROR_VERTICAL:
			// 00:00, 01:11, 10:10, 11:01
			atom.dir ^= (atom.dir & 1) << 1;
			break;
		
		case TOK_MIRROR_HORIZONTAL:
			// 00:10, 01:01, 10:00, 11:11
			atom.dir ^= (atom.dir & ~1) << 1;
			break;
		
		case TOK_MIRROR_TURN_LEFT:
			if(atom.energy >= 1) {
				--atom.energy;
			}
			else {
				atom.dir = (atom.dir + 1) & 3;
			}
			break;
		
		case TOK_MIRROR_TURN_RIGHT:
			if(atom.energy >= 1) {
				--atom.energy;
			}
			else {
				atom.dir = (atom.dir + 3) & 3;
			}
			break;
		
		case TOK_MIRROR_RANDOM:
			atom.dir = (atom.dir + arc4random() % 3 + 3) & 3;
			break;
		
		case TOK_MIRROR_ENERGY_URDL:
			if(atom.energy >= 1) {
				--atom.energy;
				atom.dir ^= 1;
			}
			else {
				atom.dir ^= 3;
			}
			break;
		
		case TOK_MIRROR_ENERGY_ULDR:
			if(atom.energy >= 1) {
				--atom.energy;
				atom.dir ^= 3;
			}
			else {
				atom.dir ^= 1;
			}
			break;
		
		default:
			fatal("Cell '%c' is not a Mirror.", type);
	}
	
	return destroy;
}

