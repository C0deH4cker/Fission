//
//  DirChanger.h
//  Fission
//
//  Created by C0deH4cker on 2/25/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FSN_DIRCHANGER_H_
#define _FSN_DIRCHANGER_H_

#include "Component.h"
#include "Direction.h"
#include "Point.h"

namespace fsn {
	class Atom;
	
	class DirChanger: public virtual Component {
	public:
		DirChanger(char type);
		
		Direction getDir() const;
		virtual bool onHit(Atom& atom);
		
	private:
		Direction dir;
	};
}


#endif /* _FSN_DIRCHANGER_H_ */
