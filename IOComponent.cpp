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
#include "tokens.h"
#include "Atom.h"

using namespace fsn;


IOComponent::IOComponent(char type)
: Component(type), pastEOF(false) {
	
}

bool IOComponent::onHit(Atom& atom) {
	char c;
	bool destroy = false;
	
	switch(type) {
		case TOK_IO_NEWLINE:
			std::cout.put('\n');
			break;
		
		case TOK_IO_OUTCHAR:
			std::cout.put((char)atom.mass);
			break;
			
		case TOK_IO_ENDCHAR:
			std::cout.put((char)atom.mass);
			destroy = true;
			break;
		
		case TOK_IO_INCHAR:
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
		
		case TOK_IO_OUTSTR:
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

