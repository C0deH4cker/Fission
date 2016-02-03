//
//  Terminator.cpp
//  Fission
//
//  Created by C0deH4cker on 2/25/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Terminator.h"
#include "Component.h"
#include "Grid.h"
#include "Atom.h"

using namespace fsn;


Terminator::Terminator(Token type, Grid& grid)
: Component(type), grid(grid) {}

bool Terminator::onHit(Atom& atom) {
	// I'll be back
	grid.terminate((int)atom.mass);
	return true;
}

