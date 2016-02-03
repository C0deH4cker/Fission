//
//  IOComponent.h
//  Fission
//
//  Created by C0deH4cker on 2/25/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef FSN_IOCOMPONENT_H
#define FSN_IOCOMPONENT_H

#include "Component.h"

namespace fsn {
	class Atom;
	
	class IOComponent: public virtual Component {
	public:
		IOComponent(Token type);
		
		virtual bool onHit(Atom& atom);
		
	private:
		bool pastEOF;
	};
}


#endif /* FSN_IOCOMPONENT_H */
