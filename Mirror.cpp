//
//  Mirror.cpp
//  Fission
//
//  Created by C0deH4cker on 2/24/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Mirror.h"
#include <cstdlib>
#include <iostream>
#include "Atom.h"
#include "Direction.h"
#include "Errors.h"

using namespace fsn;


Mirror::Mirror(char type)
: Component(type) {}

bool Mirror::onHit(Atom& atom) {
	bool destroy = false;
	
	switch(type) {
		case '/':
			// 00:11, 01:10, 10:01, 11:00
			atom.dir ^= 3;
			break;
		
		case '\\':
			// 00:01, 01:00, 10:11, 11:10
			atom.dir ^= 1;
			break;
		
		case '|':
			// 00:00, 01:11, 10:10, 11:01
			atom.dir ^= (atom.dir & 1) << 1;
			break;
		
		case '-':
			// 00:10, 01:01, 10:00, 11:11
			atom.dir ^= (atom.dir & ~1) << 1;
			break;
		
		case 'Z':
			if(atom.energy >= 1) {
				--atom.energy;
			}
			else {
				atom.dir = (atom.dir + 1) & 3;
			}
			break;
		
		case 'S':
			if(atom.energy >= 1) {
				--atom.energy;
			}
			else {
				atom.dir = (atom.dir + 3) & 3;
			}
			break;
		
		case '#':
			atom.dir = (atom.dir + arc4random() % 3 + 3) & 3;
			break;
		
		case 'H':
			atom.dir ^= 2;
			destroy = atom.dir & 2;
			break;
		
		case 'I':
			atom.dir ^= 2;
			destroy = atom.dir & 1;
			break;
		
		case '%':
			if(atom.energy >= 1) {
				--atom.energy;
				atom.dir ^= 1;
			}
			else {
				atom.dir ^= 3;
			}
			break;
		
		case '&':
			if(atom.energy >= 1) {
				--atom.energy;
				atom.dir ^= 3;
			}
			else {
				atom.dir ^= 1;
			}
			break;
		
		default:
			fatal("Cell '%c' is not a mirror.", type);
	}
	
	return destroy;
}

