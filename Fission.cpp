//
//  Fission.cpp
//  Fission
//
//  Created by C0deH4cker on 2/23/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Fission.h"
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <functional>

using namespace fsn;


Fission::Fission()
: code(0), stop(false) {}

Fission::~Fission() {
	delete grid;
}

int Fission::run(int argc, char* argv[]) {
	std::ifstream src;
	bool skipShebang = false;
	std::unordered_map<std::string, std::function<int()>> options;

    trace = false;
	
	options["-s"] = options["--script"] = [&]() {
		skipShebang = true;
		return 0;
	};
	
	options["-t"] = options["--trace"] = [&]() {
		trace = true;
		return 0;
	};
	
	options["-h"] = options["--help"] = options["--usage"] = [&]() {
		return usage(argv[0]);
	};
	
	for(int i = 1; i < argc; i++) {
		std::string arg(argv[i]);
		
		if(arg[0] == '-') {
			try {
				int ret = options[arg]();
				if(ret) {
					return ret;
				}
			}
			catch(std::bad_function_call e) {
				std::cerr << "Invalid option: " << arg << std::endl;
				return usage(argv[0]);
			}
		}
		else {
			if(src.is_open()) {
				std::cerr << "Unexpected argument: " << arg << std::endl;
				return usage(argv[0]);
			}
			
			src.open(arg);
			if(!src.is_open()) {
				std::cerr << "Unable to open '" << arg << "'." << std::endl;
				return 1;
			}
		}
	}
	
	if(!src.is_open()) {
		std::cerr << "No source file specified." << std::endl;
		return usage(argv[0]);
	}
	
	grid = new Grid(src, skipShebang);
	
	return mainloop();
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

int Fission::mainloop() {
	do {
		grid->tick(*this, trace);
	} while(running());
	
	return code;
}

int Fission::usage(const std::string& argv0) {
	std::cerr
	  << "Usage: " << argv0 << " [options] program.fsn" << std::endl
	  << "Options:" << std::endl
	  << "-s, --script         Run as a script (ignore first line)" << std::endl
	  << "-t, --trace          Trace program execution" << std::endl
	  << "-h, --help, --usage  Show this help and exit" << std::endl;
	
	return 1;
}

