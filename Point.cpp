//
//  Point.cpp
//  Fission
//
//  Created by C0deH4cker on 2/23/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Point.h"
#include <sstream>

using namespace fsn;


size_t Point::hash() const {
	return ((size_t)x << 32) | (size_t)y;
}

bool fsn::operator==(const Point& a, const Point& b) {
	return a.x == b.x && a.y == b.y;
}

bool fsn::operator!=(const Point& a, const Point& b) {
	return !(a == b);
}


bool fsn::operator<(const Point& a, const Point& b) {
	if(a.y < b.y) return true;
	if(a.y > b.y) return false;
	
	return a.x < b.x;
}

bool fsn::operator<=(const Point& a, const Point& b) {
	return a < b || a == b;
}

bool fsn::operator>(const Point& a, const Point& b) {
	return !(a <= b);
}

bool fsn::operator>=(const Point& a, const Point& b) {
	return !(a < b);
}

std::ostream& fsn::operator<<(std::ostream& os, Point pt) {
	// Print to stringstream so that the point description can be
	// printed at once to avoid messing up stream modifiers.
	std::stringstream ss;
	ss << "(" << pt.x << ", " << pt.y << ")";
	return os << ss.str();
}

