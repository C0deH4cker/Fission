//
//  Component.h
//  Fission
//
//  Created by C0deH4cker on 2/23/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef FSN_COMPONENT_H
#define FSN_COMPONENT_H

#include <memory>
#include "Token.h"
#include "Point.h"

namespace fsn {
	class Grid;
	class Atom;
	
	/*! Virtual base class for all components */
	class Component {
	public:
		static std::shared_ptr<Component> create(Token type, Grid& grid, Point pt);
		
		Component(Token type);
		virtual ~Component();
		
		/*!
		 Called when an atom hits this component.
		 @param atom Atom that hit the component.
		 @return True if the atom should be destroyed, false otherwise.
		 */
		virtual bool onHit(Atom& atom);
		
		Token getType() const { return type; }
		
	protected:
		Token type;
	};
}


#endif /* FSN_COMPONENT_H */
