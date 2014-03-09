//
//  Grid.h
//  Fission
//
//  Created by C0deH4cker on 2/23/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FSN_GRID_H_
#define _FSN_GRID_H_

#include <istream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <unordered_set>
#include <functional>
#include "Point.h"
#include "Atom.h"
#include "Direction.h"

namespace fsn {
	class Fission;
	class Component;
	class DynamicComponent;
	class Teleporter;
	
	class Grid {
	public:
		int width, height;
		
		Grid(std::istream& src, bool skipShebang = false);
		~Grid();
		
		void tick(Fission& mgr);
		void spawn(const Atom& atom);
		void teleport(Atom& atom, int number, int from);
		Teleporter* addTeleporter(char type, Point pt);
		void addDynamic(DynamicComponent* dyn);
		void removeDynamic(DynamicComponent* dyn);
		void terminate(int status);
		
	private:
		std::vector<std::vector<Component*> > cells;
		std::priority_queue<Atom, std::vector<Atom>, std::greater<Atom> > atoms;
		std::vector<Point> teleporters[10];
		std::unordered_set<DynamicComponent*> dynamics;
		int indices[10];
		bool stop;
		int status;
	};
}


#endif /* _FSN_GRID_H_ */
