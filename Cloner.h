//
//  Cloner.h
//  Fission
//
//  Created by C0deH4cker on 2/27/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef FSN_CLONER_H
#define FSN_CLONER_H

#include <cstdint>
#include "DirectedComponent.h"
#include "Direction.h"
#include "Atom.h"

namespace fsn {
	class Grid;
	
	class Cloner: public virtual DirectedComponent {
	public:
		Cloner(Token type, Grid& grid);
		
		virtual bool onHit(Atom& atom);
		virtual Direction getDir() const;
		
	private:
		Grid& grid;
		int64_t multiplier, adder;
		AtomicData waiting;
		Direction stored;
	};
}


#endif /* FSN_CLONER_H */
