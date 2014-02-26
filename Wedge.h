//
//  Wedge.h
//  Fission
//
//  Created by C0deH4cker on 2/24/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FSN_WEDGE_H_
#define _FSN_WEDGE_H_

#include "Component.h"
#include "DirectedComponent.h"
#include "Grid.h"

namespace fsn {
	class Atom;
	
	class Wedge: public virtual DirectedComponent {
	public:
		Wedge(char type, Grid& grid);
		
		virtual bool onHit(Atom& atom);
		virtual Direction getDir() const;
		
	private:
		Grid& grid;
		int value;
	};
}


#endif /* _FSN_WEDGE_H_ */
