//
//  Point.cpp
//  Fission
//
//  Created by C0deH4cker on 2/23/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Point.h"

using namespace fsn;


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

