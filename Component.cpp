//
//  Component.cpp
//  Fission
//
//  Created by C0deH4cker on 2/23/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Component.h"
#include <iostream>
#include <cctype>
#include <cstdint>
#include "Grid.h"
#include "Atom.h"
#include "DirChanger.h"
#include "Mirror.h"
#include "PartialMirror.h"
#include "Storage.h"
#include "Cloner.h"
#include "Wedge.h"
#include "IOComponent.h"
#include "Terminator.h"
#include "Jumper.h"
#include "Skipper.h"
#include "Teleporter.h"


using namespace fsn;


std::shared_ptr<Component> Component::create(Token type, Grid& grid, Point pt) {
	switch(type) {
		case Token::SPAWNER_UP:
		case Token::SPAWNER_LEFT:
		case Token::SPAWNER_DOWN:
		case Token::SPAWNER_RIGHT:
			grid.spawn(Atom(pt, DirChanger::getDir(type)));
			/* FALLTHROUGH */
		case Token::DIR_UP:
		case Token::DIR_LEFT:
		case Token::DIR_DOWN:
		case Token::DIR_RIGHT:
			return std::make_shared<DirChanger>(type);
		
		case Token::MIRROR_URDL:
		case Token::MIRROR_ULDR:
		case Token::MIRROR_VERTICAL:
		case Token::MIRROR_HORIZONTAL:
		case Token::MIRROR_TURN_LEFT:
		case Token::MIRROR_TURN_RIGHT:
		case Token::MIRROR_RANDOM:
		case Token::MIRROR_ENERGY_URDL:
		case Token::MIRROR_ENERGY_ULDR:
			return std::make_shared<Mirror>(type);
		
		case Token::PARTIAL_CLONER:
		case Token::PARTIAL_SPLITTER:
			return std::make_shared<PartialMirror>(type, grid);
		
		case Token::STACK:
			return std::make_shared<Stack>(type);
			
		case Token::QUEUE:
			return std::make_shared<Queue>(type);
		
		case Token::CLONER_UP:
		case Token::CLONER_LEFT:
		case Token::CLONER_DOWN:
		case Token::CLONER_RIGHT:
			return std::make_shared<Cloner>(type, grid);
		
		case Token::WEDGE_UP:
		case Token::WEDGE_LEFT:
		case Token::WEDGE_DOWN:
		case Token::WEDGE_RIGHT:
			return std::make_shared<Wedge>(type, grid);
		
		case Token::IO_NEWLINE:
		case Token::IO_OUTCHAR:
		case Token::IO_ENDCHAR:
		case Token::IO_INCHAR:
		case Token::IO_OUTSTR:
			return std::make_shared<IOComponent>(type);
		
		case Token::TERMINATOR:
			return std::make_shared<Terminator>(type, grid);
		
		case Token::JUMP:
			return std::make_shared<Jumper>(type, grid.width, grid.height);
		
		case Token::SKIP:
			return grid.addSkipper(type, pt);
		
		case Token::TP_0:
		case Token::TP_1:
		case Token::TP_2:
		case Token::TP_3:
		case Token::TP_4:
		case Token::TP_5:
		case Token::TP_6:
		case Token::TP_7:
		case Token::TP_8:
		case Token::TP_9:
			return grid.addTeleporter(type, pt);
		
		default:
			return std::make_shared<Component>(type);
	}
}

Component::Component(Token type)
: type(type) {
	
}

Component::~Component() {
	
}

bool Component::onHit(Atom& atom) {
	bool destroy = false;
	
	switch(type) {
		case Token::DESTROY:
			destroy = true;
			break;
		
		case Token::INCMASS:
			++atom.mass;
			break;
		
		case Token::DECMASS:
			--atom.mass;
			break;
		
		case Token::INCENERGY:
			++atom.energy;
			break;
		
		case Token::DECENERGY:
			--atom.energy;
			break;
		
		case Token::INVENERGY:
			atom.energy = -atom.energy;
			break;
		
		case Token::SWAP: {
			int64_t mass = atom.mass;
			atom.mass = atom.energy;
			atom.energy = mass;
			break;
		}
		
		case Token::LITERAL:
			atom.flags |= AtomicFlags::Setting;
			break;
		
		case Token::CLEAR:
			atom.mass = 1;
			atom.energy = 0;
			break;
		
		default:
			if(islower((char)type)) {
				atom.mass = (char)type;
			}
			break;
	}
	
	return destroy;
}

