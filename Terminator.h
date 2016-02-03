//
//  Terminator.h
//  Fission
//
//  Created by C0deH4cker on 2/25/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef FSN_TERMINATOR_H
#define FSN_TERMINATOR_H

#include "Component.h"

namespace fsn {
	class Atom;
	class Grid;
	
	class Terminator: public virtual Component {
	public:
		Terminator(Token type, Grid& grid);
		
		virtual bool onHit(Atom& atom);
		
	private:
		Grid& grid;
	};
}


#endif /* FSN_TERMINATOR_H */
