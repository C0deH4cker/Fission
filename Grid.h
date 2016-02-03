//
//  Grid.h
//  Fission
//
//  Created by C0deH4cker on 2/23/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef FSN_GRID_H
#define FSN_GRID_H

#include <istream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <memory>
#include "Atom.h"
#include "Point.h"
#include "Token.h"
#include "Teleporter.h"
#include "Skipper.h"
#include "DynamicComponent.h"


namespace fsn {
	class Fission;
	
	class Grid {
	public:
		int width, height;
		
		Grid(std::istream& src, bool skipShebang = false);
		
		void tick(Fission& mgr, bool trace = false);
		void spawn(const Atom& atom);
		void teleport(Atom& atom, int channel, int from);
		std::shared_ptr<Teleporter> addTeleporter(Token type, Point pt);
		std::shared_ptr<Skipper> addSkipper(Token type, Point pt);
		void addDynamic(std::shared_ptr<DynamicComponent> dyn);
		void removeDynamic(std::shared_ptr<DynamicComponent> dyn);
		void terminate(int status);
		
	private:
		std::vector<std::vector<std::shared_ptr<Component>>> cells;
		std::priority_queue<Atom, std::vector<Atom>, std::greater<Atom>> atoms;
		std::vector<Point> teleporters[36];
		std::unordered_map<int, std::map<int, std::shared_ptr<Skipper>>> skipRows;
		std::unordered_map<int, std::map<int, std::shared_ptr<Skipper>>> skipCols;
		std::unordered_set<std::shared_ptr<DynamicComponent>> dynamics;
		int telcount[36];
		bool stop;
		int status;
	};
}


#endif /* FSN_GRID_H */
