//
//  Skipper.h
//  Fission
//
//  Created by C0deH4cker on 3/21/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef FSN_SKIPPER_H
#define FSN_SKIPPER_H

#include "Component.h"

namespace fsn {
	class Atom;
	
	class Skipper: public virtual Component {
	public:
		int prevX, prevY, nextX, nextY;
		
		Skipper(Token type, int prevX, int nextX, int prevY, int nextY);
		
		virtual bool onHit(Atom& atom);
	};
}


#endif /* FSN_SKIPPER_H */
