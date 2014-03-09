//
//  IOComponent.h
//  Fission
//
//  Created by C0deH4cker on 2/25/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FSN_IOCOMPONENT_H_
#define _FSN_IOCOMPONENT_H_

#include "Component.h"

namespace fsn {
	class Atom;
	
	class IOComponent: public virtual Component {
	public:
		IOComponent(char type);
		
		virtual bool onHit(Atom& atom);
		
	private:
		bool pastEOF;
	};
}


#endif /* _FSN_IOCOMPONENT_H_ */
