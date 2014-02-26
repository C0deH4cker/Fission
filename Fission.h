//
//  Fission.h
//  Fission
//
//  Created by C0deH4cker on 2/23/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FSN_FISSION_H_
#define _FSN_FISSION_H_

#include <istream>
#include "Grid.h"

namespace fsn {
	class Fission {
	public:
		Fission(std::istream& src);
		
		int run();
		bool running() const;
		void terminate(int status);
		
	private:
		Grid grid;
		bool stop;
		int code;
		
		void tick();
	};
}


#endif /* _FSN_FISSION_H_ */
