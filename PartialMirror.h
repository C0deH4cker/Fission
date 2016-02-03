//
//  PartialMirror.h
//  Fission
//
//  Created by C0deH4cker on 2/26/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef FSN_PARTIALMIRROR_H
#define FSN_PARTIALMIRROR_H

#include "Component.h"
#include "Token.h"

namespace fsn {
	class Atom;
	class Grid;
	
	class PartialMirror: public virtual Component {
	public:
		PartialMirror(Token type, Grid& grid);
		
		virtual bool onHit(Atom& atom);
		
	private:
		Grid& grid;
	};
}


#endif /* FSN_PARTIALMIRROR_H */
