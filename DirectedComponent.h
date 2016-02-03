//
//  DirectedComponent.h
//  Fission
//
//  Created by C0deH4cker on 2/25/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef FSN_DIRECTEDCOMPONENT_H
#define FSN_DIRECTEDCOMPONENT_H

#include "Component.h"
#include "Direction.h"

namespace fsn {
	class DirectedComponent: public virtual Component {
	public:
		DirectedComponent(Token type);
		virtual ~DirectedComponent();
		
		virtual Direction getDir() const=0;
	};
}


#endif /* FSN_DIRECTEDCOMPONENT_H */
