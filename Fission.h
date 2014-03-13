//
//  Fission.h
//  Fission
//
//  Created by C0deH4cker on 2/23/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FSN_FISSION_H_
#define _FSN_FISSION_H_

#include <string>
#include "Grid.h"

namespace fsn {
	class Fission {
	public:
		Fission();
		~Fission();
		
		int run(int argc, char* argv[]);
		bool running() const;
		void terminate(int status);
		
	private:
		bool skipShebang;
		bool trace;
		Grid* grid;
		bool stop;
		int code;
		
		void tick();
		int usage(const std::string& argv0);
		int mainloop();
	};
}


#endif /* _FSN_FISSION_H_ */
