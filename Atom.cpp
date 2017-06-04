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
: mass(1), energy(0), pos(startingPos), dir(startingDir),
printing(false), setting(false) {}

Atom::Atom(const Atom& other)
: mass(other.mass), energy(other.energy), pos(other.pos), dir(other.dir),
printing(other.printing), setting(other.setting) {}

Atom& Atom::operator=(const Atom& other) {
	mass = other.mass;
	energy = other.energy;
	pos = other.pos;
	dir = other.dir;
	printing = other.printing;
	setting = other.setting;
	return *this;
}


Atom Atom::move(int w, int h, int steps) const {
	Atom ret(*this);
	
	if(steps < 0) {
		ret.dir ^= 2;
	}
	
	int d = steps * ((dir & 2) - 1);
	
	if(dir & 1) {
		ret.pos.x = ((pos.x + d) % w + w) % w;
	}
	else {
		ret.pos.y = ((pos.y + d) % h + h) % h;
	}
	
	return ret;
}

bool fsn::operator==(const Atom& a, const Atom& b) {
	return a.mass == b.mass &&
	       a.energy == b.energy &&
	       a.pos == b.pos &&
	       a.dir == b.dir &&
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

