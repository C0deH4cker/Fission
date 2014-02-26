//
//  IOComponent.cpp
//  Fission
//
//  Created by C0deH4cker on 2/25/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "IOComponent.h"
#include <iostream>
#include "Atom.h"
#include "Grid.h"
#include "Errors.h"

using namespace fsn;


IOComponent::IOComponent(char type, Grid& grid)
: Component(type), pastEOF(false), grid(grid) {
	
}

bool IOComponent::onHit(Atom& atom) {
	char c;
	
	switch(type) {
		case '!':
			std::cout.put((char)atom.mass);
			break;
			
		case 'O':
			std::cout.put((char)atom.mass);
			grid.terminate(0);
			break;
		
		case '?':
			if(pastEOF) {
				return true;
			}
			
			if(std::cin.get(c)) {
				atom.mass = (int)(unsigned char)c;
			}
			else {
				++atom.energy;
				pastEOF = true;
			}
			break;
		
		case '\'':
			if(atom.printing) {
				atom.printing = false;
				// Decrement mass because it started at 1 instead of 0
				--atom.mass;
			}
			else {
				atom.printing = true;
				// Don't set to 0, because that would kill it
				atom.mass = 1;
			}
			break;
		
		
		default:
			fatal("Cell '%c' is not an IOComponent.", type);
	}
	
	return false;
}

