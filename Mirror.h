//
//  Mirror.h
//  Fission
//
//  Created by C0deH4cker on 2/24/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef FSN_MIRROR_H
#define FSN_MIRROR_H

#include "Component.h"
#include "Token.h"

namespace fsn {
	class Atom;
	
	class Mirror: public virtual Component {
	public:
		Mirror(Token type);
		
		virtual bool onHit(Atom& atom);
	};
}


#endif /* FSN_MIRROR_H */
