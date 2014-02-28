//
//  Storage.h
//  Fission
//
//  Created by C0deH4cker on 2/28/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FSN_STORAGE_H_
#define _FSN_STORAGE_H_

#include "Component.h"
#include "DynamicComponent.h"
#include <stack>
#include <queue>
#include "macros.h"
#include "Grid.h"
#include "Atom.h"

namespace fsn {
	template <class T>
	class Storage: public virtual DynamicComponent {
	public:
		static const Atom& getNext(std::stack<Atom> stack) {
			return stack.top();
		}
		
		static const Atom& getNext(std::queue<Atom> queue) {
			return queue.front();
		}
		
		Storage(char type, Grid& grid)
		: Component(type), DynamicComponent(type, grid), tickspeed(-1) {}
		
		virtual bool onHit(Atom& atom) {
			if(atom.energy > 0) {
				tickspeed = MAX(atom.mass, 1);
				grid.addDynamic(this);
			}
			else {
				stored.push(atom);
			}
			
			return true;
		}
		
		virtual bool onTick() {
			// XXX: Is this if statement necessary?
			if(stored.empty()) {
				return false;
			}
			
			if(++curTick % tickspeed == 0) {
				grid.spawn(getNext(stored));
				stored.pop();
			}
			
			return !stored.empty();
		}
		
	private:
		int tickspeed;
		int curTick;
		T stored;
	};
	
	typedef Storage<std::stack<Atom> > Stack;
	typedef Storage<std::queue<Atom> > Queue;
}


#endif /* _FSN_STACK_H_ */
