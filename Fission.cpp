//
//  Fission.cpp
//  Fission
//
//  Created by C0deH4cker on 2/23/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Fission.h"

#include <cstdlib>
#include <ctime>

using namespace fsn;


Fission::Fission(std::istream& src)
: grid(src), code(0), stop(false) {}

int Fission::run() {
	do {
		grid.tick(*this);
	} while(running());
	
	return code;
}

bool Fission::running() const {
	return !stop;
}

void Fission::terminate(int status) {
	stop = true;
	
	if(status > code) {
		code = status;
	}
}

