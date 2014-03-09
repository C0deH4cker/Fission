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
#include "tokens.h"
#include "Atom.h"
#include "Grid.h"
#include "Mirror.h"
#include "Wedge.h"
#include "Teleporter.h"
#include "IOComponent.h"
#include "Terminator.h"
#include "DirChanger.h"
#include "PartialMirror.h"
#include "Cloner.h"
#include "Storage.h"
#include "Jumper.h"

using namespace fsn;


Component* Component::create(char type, Grid& grid, Point pt) {
	switch(type) {
		case TOK_SPAWNER_UP:
		case TOK_SPAWNER_LEFT:
		case TOK_SPAWNER_DOWN:
		case TOK_SPAWNER_RIGHT:
			grid.spawn(Atom(pt, DirChanger::getDir(type)));
			/* FALLTHROUGH */
		case TOK_DIR_UP:
		case TOK_DIR_LEFT:
		case TOK_DIR_DOWN:
		case TOK_DIR_RIGHT:
			return new DirChanger(type);
		
		case TOK_MIRROR_URDL:
		case TOK_MIRROR_ULDR:
		case TOK_MIRROR_VERTICAL:
		case TOK_MIRROR_HORIZONTAL:
		case TOK_MIRROR_TURN_LEFT:
		case TOK_MIRROR_TURN_RIGHT:
		case TOK_MIRROR_RANDOM:
		case TOK_MIRROR_ENERGY_URDL:
		case TOK_MIRROR_ENERGY_ULDR:
			return new Mirror(type);
		
		case TOK_PARTIAL_CLONER:
		case TOK_PARTIAL_SPLITTER:
			return new PartialMirror(type, grid);
		
		case TOK_STACK:
			return new Stack(type, grid);
			
		case TOK_QUEUE:
			return new Queue(type, grid);
		
		case TOK_CLONER_UP:
		case TOK_CLONER_LEFT:
		case TOK_CLONER_DOWN:
		case TOK_CLONER_RIGHT:
			return new Cloner(type, grid);
		
		case TOK_WEDGE_UP:
		case TOK_WEDGE_LEFT:
		case TOK_WEDGE_DOWN:
		case TOK_WEDGE_RIGHT:
			return new Wedge(type, grid);
		
		case TOK_IO_NEWLINE:
		case TOK_IO_OUTCHAR:
		case TOK_IO_ENDCHAR:
		case TOK_IO_INCHAR:
		case TOK_IO_OUTSTR:
			return new IOComponent(type);
		
		case TOK_TERMINATOR:
			return new Terminator(type, grid);
		
		case TOK_JUMP:
			return new Jumper(type, grid.width, grid.height);
		
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			return grid.addTeleporter(type, pt);
		
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
		case TOK_DESTROY:
			destroy = true;
			break;
		
		case TOK_INCMASS:
			++atom.mass;
			break;
		
		case TOK_DECMASS:
			--atom.mass;
			break;
		
		case TOK_INCENERGY:
			++atom.energy;
			break;
		
		case TOK_DECENERGY:
			--atom.energy;
			break;
		
		case TOK_SWAP: {
			int mass = atom.mass;
			atom.mass = atom.energy;
			atom.energy = mass;
			break;
		}
		
		case TOK_LITERAL:
			atom.setting = true;
			break;
		
		default:
			if(islower(type)) {
				atom.mass = type;
			}
			break;
	}
	
	return destroy;
}

