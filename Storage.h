//
//  Storage.h
//  Fission
//
//  Created by C0deH4cker on 2/28/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef FSN_STORAGE_H
#define FSN_STORAGE_H

#include "Component.h"
#include <stack>
#include <queue>
#include <cstdint>
#include "Atom.h"

namespace fsn {
	template <class T>
	class Storage: public virtual Component {
	public:
		static void push(std::stack<int64_t>& stack, int64_t value) {
			stack.push(value);
		}
		
		static void push(std::queue<int64_t>& queue, int64_t value) {
			queue.push(value);
		}
		
		static int64_t pop(std::stack<int64_t>& stack) {
			int64_t ret = stack.top();
			stack.pop();
			return ret;
		}
		
		static int64_t pop(std::queue<int64_t>& queue) {
			int64_t ret = queue.front();
			queue.pop();
			return ret;
		}
		
		Storage(Token type)
		: Component(type) {}
		
		virtual bool onHit(Atom& atom) {
			bool destroy = false;
			
			if(atom.energy >= 0) {
				// Push
				push(stored, atom.mass);
				destroy = true;
			}
			else if(stored.empty()) {
				// Pop, but empty, so reflect
				atom.dir ^= 2;
				atom.energy = -atom.energy;
			}
			else {
				// Pop
				atom.mass = pop(stored);
				atom.energy = ~atom.energy;
			}
			
			return destroy;
		}
		
	private:
		T stored;
	};
	
	using Stack = Storage<std::stack<int64_t>>;
	using Queue = Storage<std::queue<int64_t>>;
}


#endif /* FSN_STACK_H */
