//
//  Wedge.cpp
//  Fission
//
//  Created by C0deH4cker on 2/24/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Wedge.h"
#include "Component.h"
#include "Direction.h"

using namespace fsn;


Wedge::Wedge(char type)
: Component(type), value(2) {}

bool Wedge::onHit(Atom& atom) {
	// TODO: implement
	
	return false;
}

