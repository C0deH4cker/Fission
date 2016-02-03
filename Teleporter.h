//
//  Teleporter.h
//  Fission
//
//  Created by C0deH4cker on 2/24/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef FSN_TELEPORTER_H
#define FSN_TELEPORTER_H

#include "Component.h"

namespace fsn {
	class Grid;
	class Atom;
	
	class Teleporter: public virtual Component {
	public:
		Teleporter(Token type, Grid& grid, int index);
		
		static int getChannel(Token type);
		
		virtual bool onHit(Atom& atom);
	
	private:
		Grid& grid;
		int index;
	};
}


#endif /* FSN_TELEPORTER_H */
