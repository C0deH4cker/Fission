//
//  DynamicComponent.h
//  Fission
//
//  Created by C0deH4cker on 2/24/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FSN_DYNAMICCOMPONENT_H_
#define _FSN_DYNAMICCOMPONENT_H_

#include "Component.h"

namespace fsn {
	class Atom;
	class Grid;
	
	class DynamicComponent: public virtual Component {
	public:
		DynamicComponent(char type);
		virtual ~DynamicComponent();
		
		virtual bool onHit(Atom& atom) { return false; }
		
		/*!
		 Called once per tick to perform logic updates.
		 @param grid Reference to the grid object to change global state.
		 @return True if this component should stop ticking, false otherwise.
		 */
		virtual bool onTick(Grid& grid)=0;
	};
}


#endif /* _FSN_DYNAMICCOMPONENT_H_ */
