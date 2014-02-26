//
//  Teleporter.h
//  Fission
//
//  Created by C0deH4cker on 2/24/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FSN_TELEPORTER_H_
#define _FSN_TELEPORTER_H_

#include "Component.h"

namespace fsn {
	class Atom;
	class Grid;
	
	class Teleporter: public virtual Component {
	public:
		Teleporter(char type, Grid& grid, int index);
		
		virtual bool onHit(Atom& atom);
	
	private:
		Grid& grid;
		int index;
	};
}


#endif /* _FSN_TELEPORTER_H_ */
