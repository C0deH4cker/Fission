//
//  Component.cpp
//  Fission
//
//  Created by C0deH4cker on 2/23/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Component.h"
#include <cctype>
#include <iostream>
#include <cstdlib>
#include "Atom.h"
#include "Grid.h"
#include "Mirror.h"
#include "Wedge.h"
#include "Teleporter.h"
#include "IOComponent.h"
#include "Terminator.h"
#include "DirChanger.h"

using namespace fsn;


Component* Component::create(char type, Grid& grid, Point pt) {
	switch(type) {
		case 'U':
		case 'L':
		case 'D':
		case 'R': {
			DirChanger* ret = new DirChanger(type);
			grid.spawn(Atom(pt, ret->getDir()));
			return ret;
		}
		
		case 'M':
		case 'W':
		case '[':
		case ']':
			return new DirChanger(type);
		
		case '/':
		case '\\':
		case '|':
		case '-':
		case 'Z':
		case 'S':
		case '#':
		case 'H':
		case 'I':
		case '%':
		case '&':
			return new Mirror(type);
		
		/* TODO: Implement these cases
		case 'X':
		case ':':
		case '@':
		case 'K':
		case 'E':
		
		case '{':
		case '}':
		case 'Y':
		case 'A':
		*/
		
		case '<':
		case '>':
		case 'V':
		case '^':
			return new Wedge(type);
		
		case '!':
		case 'O':
		case '?':
		case '\'':
			return new IOComponent(type, grid);
		
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			return new Teleporter(type, grid, type - '0');
		
		case '*':
			return new Terminator(type, grid);
		
		default:
			return new Component(type);
	}
}

Component::Component(char type)
: type(type) {
	
}

Component::~Component() {
	
}

bool Component::onHit(Atom& atom) {
	bool destroy = false;
	
	switch(type) {
		case ' ':
			atom.mass = type;
			break;
		
		case ';':
			destroy = true;
			break;
		
		case '+':
			++atom.mass;
			break;
		
		case '_':
			--atom.mass;
			break;
		
		case '$':
			++atom.energy;
			break;
		
		case '~':
			--atom.energy;
			break;
		
		default:
			if(islower(type)) {
				atom.mass = type;
			}
			else {
				//std::cerr << "Unknown: " << (char)type << std::endl;
			}
			break;
	}
	
	return destroy;
}

