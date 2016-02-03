//
//  Jumper.h
//  Fission
//
//  Created by C0deH4cker on 3/5/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef FSN_JUMPER_H
#define FSN_JUMPER_H

#include "Component.h"

namespace fsn {
	class Atom;
	
	class Jumper: public virtual Component {
	public:
		Jumper(Token type, int width, int height);
		
		virtual bool onHit(Atom& atom);
		
	private:
		int width, height;
	};
}


#endif /* FSN_JUMPER_H */
