//
//  Teleporter.cpp
//  Fission
//
//  Created by C0deH4cker on 2/24/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Teleporter.h"
#include "Grid.h"

using namespace fsn;


Teleporter::Teleporter(char type, Grid& grid, int index)
: Component(type), grid(grid), index(index) {}

bool Teleporter::onHit(Atom& atom) {
	grid.teleport(atom, index);
	return false;
}

