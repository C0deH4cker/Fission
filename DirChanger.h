//
//  DirChanger.h
//  Fission
//
//  Created by C0deH4cker on 2/25/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef FSN_DIRCHANGER_H
#define FSN_DIRCHANGER_H

#include "DirectedComponent.h"
#include "Direction.h"

namespace fsn {
	class Atom;
	
	class DirChanger: public virtual DirectedComponent {
	public:
		static Direction getDir(Token type);
		
		DirChanger(Token type);
		
		virtual Direction getDir() const;
		virtual bool onHit(Atom& atom);
	};
}


#endif /* FSN_DIRCHANGER_H */
