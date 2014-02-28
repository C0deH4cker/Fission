//
//  PartialMirror.h
//  Fission
//
//  Created by C0deH4cker on 2/26/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FSN_PARTIALMIRROR_H_
#define _FSN_PARTIALMIRROR_H_

#include "Component.h"

namespace fsn {
	class PartialMirror: public virtual Component {
	public:
		PartialMirror(char type, Grid& grid);
		
		virtual bool onHit(Atom& atom);
		
	private:
		Grid& grid;
	};
}


#endif /* _FSN_PARTIALMIRROR_H_ */
