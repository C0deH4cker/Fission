//
//  Terminator.h
//  Fission
//
//  Created by C0deH4cker on 2/25/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FSN_TERMINATOR_H_
#define _FSN_TERMINATOR_H_

#include "Component.h"
#include "Grid.h"

namespace fsn {
	class Atom;
	
	class Terminator: public virtual Component {
	public:
		Terminator(char type, Grid& grid);
		
		virtual bool onHit(Atom& atom);
		
	private:
		Grid& grid;
	};
}


#endif /* _FSN_TERMINATOR_H_ */
