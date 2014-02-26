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
		Point pos;
		Direction dir;
		int energy;
		unsigned mass;
		bool printing;
		
		Atom(const Point& startingPos, Direction startingDir);
		
		Atom move(int w, int h) const;
	};
	
	bool operator==(const Atom& a, const Atom& b);
	bool operator!=(const Atom& a, const Atom& b);
	bool operator<(const Atom& a, const Atom& b);
	bool operator<=(const Atom& a, const Atom& b);
	bool operator>(const Atom& a, const Atom& b);
	bool operator>=(const Atom& a, const Atom& b);
}


#endif /* _FSN_ATOM_H_ */
