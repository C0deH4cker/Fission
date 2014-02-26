//
//  Atom.cpp
//  Fission
//
//  Created by C0deH4cker on 2/23/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Atom.h"
#include "Direction.h"

using namespace fsn;


Atom::Atom(const Point& startingPos, Direction startingDir)
: pos(startingPos), dir(startingDir), mass(1), energy(0),
printing(false) {}

Atom Atom::move(int w, int h) const {
	Atom ret(*this);
	
	int d = (dir & 2) - 1;
	
	if(dir & 1) {
		ret.pos.x = (int)(pos.x + d + w) % w;
	}
	else {
		ret.pos.y = (int)(pos.y + d + h) % h;
	}
	
	return ret;
}

bool fsn::operator==(const Atom& a, const Atom& b) {
	return a.pos == b.pos &&
	       a.dir == b.dir &&
	       a.mass == b.mass &&
	       a.energy == b.energy &&
	       a.printing == b.printing;
}

bool fsn::operator!=(const Atom& a, const Atom& b) {
	return !(a == b);
}

bool fsn::operator>(const Atom& a, const Atom& b) {
	if(a.pos > b.pos) return true;
	if(a.pos < b.pos) return false;
	
	if(a.dir != DOWN && b.dir == DOWN) return true;
	if(a.dir == DOWN && a.dir != DOWN) return false;
	
	if(a.dir != RIGHT && b.dir == RIGHT) return true;
	if(a.dir == RIGHT && b.dir != RIGHT) return false;
	
	if(a.energy < b.energy) return true;
	if(a.energy > b.energy) return false;
	
	return a.mass > b.mass;
}

bool fsn::operator>=(const Atom& a, const Atom& b) {
	return a > b || a == b;
}

bool fsn::operator<(const Atom& a, const Atom& b) {
	return !(a >= b);
}

bool fsn::operator<=(const Atom& a, const Atom& b) {
	return !(a > b);
}

