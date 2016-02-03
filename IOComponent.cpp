//
//  IOComponent.cpp
//  Fission
//
//  Created by C0deH4cker on 2/25/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "IOComponent.h"
#include <iostream>
#include "common.h"
#include "Atom.h"

using namespace fsn;


IOComponent::IOComponent(Token type)
: Component(type), pastEOF(false) {}

bool IOComponent::onHit(Atom& atom) {
	char c = '\0';
	bool destroy = false;
	
	switch(type) {
		case Token::IO_NEWLINE:
			std::cout.put('\n');
			break;
		
		case Token::IO_OUTCHAR:
			std::cout.put((char)atom.mass);
			break;
			
		case Token::IO_ENDCHAR:
			std::cout.put((char)atom.mass);
			destroy = true;
			break;
		
		case Token::IO_INCHAR:
			if(pastEOF) {
				return true;
			}
			
			if(std::cin.get(c)) {
				atom.mass = (int64_t)(unsigned char)c;
				atom.energy = 0;
			}
			else {
				atom.energy = 1;
				pastEOF = true;
			}
			break;
		
		case Token::IO_OUTSTR:
			if((atom.flags & AtomicFlags::Printing) == AtomicFlags::None) {
				atom.mass = 0;
			}
			atom.flags ^= AtomicFlags::Printing;
			break;
		
		
		default:
			fatal("Cell '%c' is not an IOComponent.", (char)type);
	}
	
	return destroy;
}

