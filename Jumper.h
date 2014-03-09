//
//  Jumper.h
//  Fission
//
//  Created by C0deH4cker on 3/5/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FSN_JUMPER_H_
#define _FSN_JUMPER_H_

#include "Component.h"

namespace fsn {
	class Atom;
	
	class Jumper: public virtual Component {
	public:
		Jumper(char type, int width, int height);
		
		virtual bool onHit(Atom& atom);
		
	private:
		int width, height;
	};
}


#endif /* _FSN_JUMPER_H_ */
