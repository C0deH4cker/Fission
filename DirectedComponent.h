//
//  DirectedComponent.h
//  Fission
//
//  Created by C0deH4cker on 2/25/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FSN_DIRECTEDCOMPONENT_H_
#define _FSN_DIRECTEDCOMPONENT_H_

#include "Component.h"
#include "Direction.h"

namespace fsn {
	class DirectedComponent: public virtual Component {
	public:
		DirectedComponent(char type);
		virtual ~DirectedComponent();
		
		virtual Direction getDir() const=0;
	};
}


#endif /* _FSN_DIRECTEDCOMPONENT_H_ */
