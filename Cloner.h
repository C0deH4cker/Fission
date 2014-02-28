//
//  Cloner.h
//  Fission
//
//  Created by C0deH4cker on 2/27/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FSN_CLONER_H_
#define _FSN_CLONER_H_

#include "Component.h"
#include "DirectedComponent.h"
#include "Direction.h"

namespace fsn {
	class Grid;
	
	class Cloner: public virtual DirectedComponent {
	public:
		Cloner(char type, Grid& grid);
		
		virtual bool onHit(Atom& atom);
		virtual Direction getDir() const;
		
	private:
		Grid& grid;
		int multiplier;
		int storedMass;
		int storedEnergy;
		Direction stored;
	};
}


#endif /* _FSN_CLONER_H_ */
