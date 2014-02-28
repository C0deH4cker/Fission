//
//  IOComponent.cpp
//  Fission
//
//  Created by C0deH4cker on 2/25/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "IOComponent.h"
#include <iostream>
#include "macros.h"
#include "Atom.h"
#include "Grid.h"

using namespace fsn;


IOComponent::IOComponent(char type, Grid& grid)
: Component(type), pastEOF(false), grid(grid) {
	
}

bool IOComponent::onHit(Atom& atom) {
	char c;
	bool destroy = false;
	
	switch(type) {
		case '!':
			std::cout.put((char)atom.mass);
			break;
			
		case 'O':
			std::cout.put((char)atom.mass);
			destroy = true;
			break;
		
		case '?':
			if(pastEOF) {
				return true;
			}
			
			if(std::cin.get(c)) {
				atom.mass = (int)(unsigned char)c;
				atom.energy = 0;
			}
			else {
				atom.energy = 1;
				pastEOF = true;
			}
			break;
		
		case '\'':
			if(atom.printing) {
				atom.printing = false;
			}
			else {
				atom.printing = true;
				atom.mass = 0;
			}
			break;
		
		
		default:
			fatal("Cell '%c' is not an IOComponent.", type);
	}
	
	return destroy;
}

