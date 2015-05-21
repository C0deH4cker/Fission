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
#include <stack>
#include <queue>
#include "macros.h"
#include "Grid.h"
#include "Atom.h"

namespace fsn {
	struct StoredData {
		int mass;
		int energy;
	};
	
	template <class T>
	class Storage: public virtual Component {
	public:
		static const StoredData& getTop(std::stack<StoredData>& stack) {
			return stack.top();
		}
		
		static const StoredData& getTop(std::queue<StoredData>& queue) {
			return queue.front();
		}
		
		Storage(char type)
		: Component(type) {}
		
		virtual bool onHit(Atom& atom) {
			bool destroy = false;
			
			if(atom.energy >= 0) {
				// Push
				stored.push({atom.mass, atom.energy});
				destroy = true;
			}
			else if(stored.empty()) {
				// Pop, but empty, so reflect
				atom.dir ^= 2;
				atom.energy = -atom.energy;
			}
			else {
				// Pop
				const StoredData& top = getTop(stored);
				atom.mass = top.mass;
				atom.energy = top.energy;
				stored.pop();
			}
			
			return destroy;
		}
		
	private:
		T stored;
	};
	
	typedef Storage<std::stack<StoredData>> Stack;
	typedef Storage<std::queue<StoredData>> Queue;
}


#endif /* _FSN_STACK_H_ */
