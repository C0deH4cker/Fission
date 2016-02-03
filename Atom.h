//
//  Atom.h
//  Fission
//
//  Created by C0deH4cker on 2/23/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef FSN_ATOM_H
#define FSN_ATOM_H

#include <cstdint>
#include <ostream>
#include "common.h"
#include "Direction.h"
#include "Point.h"

namespace fsn {
	struct AtomicData {
		int64_t mass;
		int64_t energy;
		
		AtomicData& operator+=(const AtomicData& other);
		AtomicData& operator-=(const AtomicData& other);
		AtomicData& operator*=(const AtomicData& other);
		AtomicData& operator/=(const AtomicData& other);
	};
	
	AtomicData operator+(const AtomicData& a, const AtomicData& b);
	AtomicData operator-(const AtomicData& a, const AtomicData& b);
	AtomicData operator*(const AtomicData& a, const AtomicData& b);
	AtomicData operator/(const AtomicData& a, const AtomicData& b);
	
	ENUM_BITFIELD(AtomicFlags, uint8_t) {
		None     = 0,
		Printing = 1<<0,
		Setting  = 1<<1,
		Debug    = 1<<2
	};
	
	class Atom: public AtomicData {
	public:
		static unsigned lastid;
		
		Point pos;
		Direction dir;
		AtomicFlags flags;
		unsigned id;
		
		Atom(const Point& startingPos, Direction startingDir);
		Atom(const Atom& other);
		
		Atom& operator=(const Atom& other);
		
		Atom move(int w, int h, int64_t steps = 1) const;
		
		void show(std::ostream& os, char hit) const;
		
		friend class Grid;
		
	private:
		Atom activate() const;
	};
	
	bool operator==(const Atom& a, const Atom& b);
	bool operator!=(const Atom& a, const Atom& b);
	bool operator<(const Atom& a, const Atom& b);
	bool operator<=(const Atom& a, const Atom& b);
	bool operator>(const Atom& a, const Atom& b);
	bool operator>=(const Atom& a, const Atom& b);
	
	Atom operator+(const Atom& a, const AtomicData& b);
	Atom operator+(const AtomicData& a, const Atom& b);
	Atom operator-(const Atom& a, const AtomicData& b);
	Atom operator-(const AtomicData& a, const Atom& b);
	Atom operator*(const Atom& a, const AtomicData& b);
	Atom operator*(const AtomicData& a, const Atom& b);
	Atom operator/(const Atom& a, const AtomicData& b);
	Atom operator/(const AtomicData& a, const Atom& b);
}


#endif /* FSN_ATOM_H */
