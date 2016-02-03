//
//  Mirror.cpp
//  Fission
//
//  Created by C0deH4cker on 2/24/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Mirror.h"
#include <random>
#include <chrono>
#include "common.h"
#include "Atom.h"

using namespace fsn;


Mirror::Mirror(Token type)
: Component(type) {}

static unsigned long long get_time() {
	return std::chrono::steady_clock::now().time_since_epoch().count();
}

bool Mirror::onHit(Atom& atom) {
	static std::mt19937 prng((unsigned)get_time());
	static std::uniform_int_distribution<> random_dir(3, 5);
	
	bool destroy = false;
	
	switch(type) {
		case Token::MIRROR_URDL:
			// 00:11, 01:10, 10:01, 11:00
			atom.dir ^= 3;
			break;
		
		case Token::MIRROR_ULDR:
			// 00:01, 01:00, 10:11, 11:10
			atom.dir ^= 1;
			break;
		
		case Token::MIRROR_VERTICAL:
			// 00:00, 01:11, 10:10, 11:01
			atom.dir ^= (atom.dir & 1) << 1;
			break;
		
		case Token::MIRROR_HORIZONTAL:
			// 00:10, 01:01, 10:00, 11:11
			atom.dir ^= (atom.dir & ~1) << 1;
			break;
		
		case Token::MIRROR_TURN_LEFT:
			if(atom.energy >= 1) {
				--atom.energy;
			}
			else {
				atom.dir = (atom.dir + 1) & 3;
			}
			break;
		
		case Token::MIRROR_TURN_RIGHT:
			if(atom.energy >= 1) {
				--atom.energy;
			}
			else {
				atom.dir = (atom.dir + 3) & 3;
			}
			break;
		
		case Token::MIRROR_RANDOM:
			atom.dir = (atom.dir + random_dir(prng)) & 3;
			break;
		
		case Token::MIRROR_ENERGY_URDL:
			if(atom.energy >= 1) {
				--atom.energy;
				atom.dir ^= 1;
			}
			else {
				atom.dir ^= 3;
			}
			break;
		
		case Token::MIRROR_ENERGY_ULDR:
			if(atom.energy >= 1) {
				--atom.energy;
				atom.dir ^= 3;
			}
			else {
				atom.dir ^= 1;
			}
			break;
		
		default:
			fatal("Cell '%c' is not a Mirror.", (char)type);
	}
	
	return destroy;
}

