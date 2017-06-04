//
//  Atom.h
//  Fission
//
//  Created by C0deH4cker on 2/23/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FSN_ATOM_H_
#define _FSN_ATOM_H_

#include "Point.h"
#include "Direction.h"

namespace fsn {
	class Atom {
	public:
		int mass;
		int energy;
		Point pos;
		Direction dir;
		bool printing;
		bool setting;
		
		Atom(const Point& startingPos, Direction startingDir);
		Atom(const Atom& other);
		
		Atom& operator=(const Atom& other);
		
		Atom move(int w, int h, int steps = 1) const;
	};
	
	bool operator==(const Atom& a, const Atom& b);
	bool operator!=(const Atom& a, const Atom& b);
	bool operator<(const Atom& a, const Atom& b);
	bool operator<=(const Atom& a, const Atom& b);
	bool operator>(const Atom& a, const Atom& b);
	bool operator>=(const Atom& a, const Atom& b);
}


#endif /* _FSN_ATOM_H_ */
