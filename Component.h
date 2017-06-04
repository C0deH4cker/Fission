//
//  Component.h
//  Fission
//
//  Created by C0deH4cker on 2/23/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FSN_COMPONENT_H_
#define _FSN_COMPONENT_H_

#include "Point.h"

namespace fsn {
	class Atom;
	class Grid;
	
	/*! Virtual base class for all components */
	class Component {
	public:
		static Component* create(char type, Grid& grid, Point pt);
		
		Component(char type);
		virtual ~Component();
		
		/*!
		 Called when an atom hits this component.
		 @param atom Atom that hit the component.
		 @return True if the atom should be destroyed, false otherwise.
		 */
		virtual bool onHit(Atom& atom);
		
		char getType() const { return type; }
		
	protected:
		char type;
	};
}


#endif /* _FSN_COMPONENT_H_ */
