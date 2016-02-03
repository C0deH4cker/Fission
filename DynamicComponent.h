//
//  DynamicComponent.h
//  Fission
//
//  Created by C0deH4cker on 2/24/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef FSN_DYNAMICCOMPONENT_H
#define FSN_DYNAMICCOMPONENT_H

#include "Component.h"

namespace fsn {
	class Atom;
	class Grid;
	
	class DynamicComponent: public virtual Component {
	public:
		DynamicComponent(Token type, Grid& grid);
		virtual ~DynamicComponent();
		
		virtual bool onHit(Atom& atom)=0;
		
		/*!
		 Called once per tick to perform logic updates.
		 @return True if this component should stop ticking, false otherwise.
		 */
		virtual bool onTick()=0;
		
	protected:
		Grid& grid;
	};
}


#endif /* FSN_DYNAMICCOMPONENT_H */
