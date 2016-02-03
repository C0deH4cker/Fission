//
//  Atom.cpp
//  Fission
//
//  Created by C0deH4cker on 2/23/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Atom.h"
#include <sstream>

using namespace fsn;

unsigned Atom::lastid = 0;

AtomicData& AtomicData::operator+=(const AtomicData& other) {
	mass += other.mass;
	energy += other.energy;
	return *this;
}

AtomicData& AtomicData::operator-=(const AtomicData& other) {
	mass -= other.mass;
	energy -= other.energy;
	return *this;
}

AtomicData& AtomicData::operator*=(const AtomicData& other) {
	mass *= other.mass;
	energy *= other.energy;
	return *this;
}

AtomicData& AtomicData::operator/=(const AtomicData& other) {
	mass /= other.mass;
	energy /= other.energy;
	return *this;
}

AtomicData fsn::operator+(const AtomicData& a, const AtomicData& b) {
	AtomicData ret {
		a.mass + b.mass,
		a.energy + b.energy
	};
	return ret;
}

AtomicData fsn::operator-(const AtomicData& a, const AtomicData& b) {
	AtomicData ret {
		a.mass - b.mass,
		a.energy - b.energy
	};
	return ret;
}

AtomicData fsn::operator*(const AtomicData& a, const AtomicData& b) {
	AtomicData ret {
		a.mass * b.mass,
		a.energy * b.energy
	};
	return ret;
}

AtomicData fsn::operator/(const AtomicData& a, const AtomicData& b) {
	AtomicData ret {
		a.mass / b.mass,
		a.energy / b.energy
	};
	return ret;
}

Atom::Atom(const Point& startingPos, Direction startingDir)
: AtomicData{1, 0}, pos(startingPos), dir(startingDir),
flags(AtomicFlags::None), id(0) {}

Atom::Atom(const Atom& other)
: AtomicData{other.mass, other.energy}, pos(other.pos), dir(other.dir),
flags(other.flags), id(other.id) {}

Atom& Atom::operator=(const Atom& other) {
	pos = other.pos;
	dir = other.dir;
	mass = other.mass;
	energy = other.energy;
	flags = other.flags;
	id = other.id;
	return *this;
}

Atom Atom::activate() const {
	Atom copy = *this;
	copy.id = ++Atom::lastid;
	return copy;
}

Atom Atom::move(int w, int h, int64_t steps) const {
	Atom ret(*this);
	
	if(steps < 0) {
		ret.dir ^= 2;
	}
	
	int64_t d = steps * ((dir & 2) - 1);
	
	if(dir & 1) {
		ret.pos.x = ((pos.x + d) % w + w) % w;
	}
	else {
		ret.pos.y = ((pos.y + d) % h + h) % h;
	}
	
	return ret;
}

void Atom::show(std::ostream& os, char hit) const {
	std::stringstream ss;
	ss << "Atom " << id << " at " << pos << " with mass " << mass << " and energy " << energy
	   << " hit component '" << hit << "'" << std::endl;
	os << ss.str();
}

bool fsn::operator==(const Atom& a, const Atom& b) {
	return a.id == b.id;
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


Atom fsn::operator+(const Atom& a, const AtomicData& b) {
	Atom ret(a);
	ret.mass += b.mass;
	ret.energy += b.energy;
	return ret;
}

Atom fsn::operator+(const AtomicData& a, const Atom& b) {
	Atom ret(b);
	ret.mass += a.mass;
	ret.energy += a.energy;
	return ret;
}

Atom fsn::operator-(const Atom& a, const AtomicData& b) {
	Atom ret(a);
	ret.mass -= b.mass;
	ret.energy -= b.energy;
	return ret;
}

Atom fsn::operator-(const AtomicData& a, const Atom& b) {
	Atom ret(b);
	ret.mass -= a.mass;
	ret.energy -= a.energy;
	return ret;
}

Atom fsn::operator*(const Atom& a, const AtomicData& b) {
	Atom ret(a);
	ret.mass *= b.mass;
	ret.energy *= b.energy;
	return ret;
}

Atom fsn::operator*(const AtomicData& a, const Atom& b) {
	Atom ret(b);
	ret.mass *= a.mass;
	ret.energy *= a.energy;
	return ret;
}

Atom fsn::operator/(const Atom& a, const AtomicData& b) {
	Atom ret(a);
	ret.mass /= b.mass;
	ret.energy /= b.energy;
	return ret;
}

Atom fsn::operator/(const AtomicData& a, const Atom& b) {
	Atom ret(b);
	ret.mass /= a.mass;
	ret.energy /= a.energy;
	return ret;
}

