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
#include "DirectedComponent.h"

namespace fsn {
	class Atom;
	
	class DirChanger: public virtual DirectedComponent {
	public:
		DirChanger(char type);
		
		virtual Direction getDir() const;
		virtual bool onHit(Atom& atom);
	};
}


#endif /* _FSN_DIRCHANGER_H_ */
