//
//  Wedge.h
//  Fission
//
//  Created by C0deH4cker on 2/24/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef FSN_WEDGE_H
#define FSN_WEDGE_H

#include "DirectedComponent.h"
#include "Direction.h"
#include "Atom.h"

namespace fsn {
	class Grid;
	
	class Wedge: public virtual DirectedComponent {
	public:
		Wedge(Token type, Grid& grid);
		
		virtual bool onHit(Atom& atom);
		virtual Direction getDir() const;
		
	private:
		Grid& grid;
		AtomicData saved;
	};
}


#endif /* FSN_WEDGE_H */
