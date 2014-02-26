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

namespace fsn {
	class Atom;
	
	class Wedge: public virtual Component {
	public:
		Wedge(char type);
		
		virtual bool onHit(Atom& atom);
		
	private:
		int value;
	};
}


#endif /* _FSN_WEDGE_H_ */
