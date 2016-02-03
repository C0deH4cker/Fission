//
//  Teleporter.cpp
//  Fission
//
//  Created by C0deH4cker on 2/24/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Teleporter.h"
#include "common.h"
#include "Grid.h"

using namespace fsn;


Teleporter::Teleporter(Token type, Grid& grid, int index)
: Component(type), grid(grid), index(index) {}

int Teleporter::getChannel(Token type) {
	switch(type) {
		case Token::TP_0: return 0;
		case Token::TP_1: return 1;
		case Token::TP_2: return 2;
		case Token::TP_3: return 3;
		case Token::TP_4: return 4;
		case Token::TP_5: return 5;
		case Token::TP_6: return 6;
		case Token::TP_7: return 7;
		case Token::TP_8: return 8;
		case Token::TP_9: return 9;
		
		default:
			fatal("Unknown teleporter: %c\n", (char)type);
	}
}

bool Teleporter::onHit(Atom& atom) {
	grid.teleport(atom, getChannel(type), index);
	return false;
}

