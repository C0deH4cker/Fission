//
//  Fission.h
//  Fission
//
//  Created by C0deH4cker on 2/23/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef FSN_FISSION_H
#define FSN_FISSION_H

#include <string>
#include <memory>
#include "Grid.h"

namespace fsn {
	class Fission {
	public:
		Fission();
		
		int run(int argc, char* argv[]);
		bool running() const;
		void terminate(int status);
		
	private:
		bool skipShebang;
		bool trace;
		std::unique_ptr<Grid> grid;
		bool stop;
		int code;
		
		void tick();
		int usage(const std::string& argv0);
		int mainloop();
	};
}


#endif /* FSN_FISSION_H */
