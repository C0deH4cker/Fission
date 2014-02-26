//
//  Mirror.h
//  Fission
//
//  Created by C0deH4cker on 2/24/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FSN_MIRROR_H_
#define _FSN_MIRROR_H_

#include "Component.h"

namespace fsn {
	class Atom;
	
	class Mirror: public virtual Component {
	public:
		Mirror(char type);
		
		virtual bool onHit(Atom& atom);
	};
}


#endif /* _FSN_MIRROR_H_ */
