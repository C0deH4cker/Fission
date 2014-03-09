#include <fstream>
#include <iostream>
#include <cstring>
#include "Fission.h"

using namespace fsn;


void usage(const char* argv0) {
	std::cerr << "Usage: " << argv0 << " [-s] program.fsn" << std::endl;
	std::cerr << "-s    Run as a script (ignore first line)" << std::endl;
}

int main(int argc, char* argv[]) {
	std::ifstream src;
	
	if(argc < 2 || argc > 3) {
		usage(argv[0]);
		return 1;
	}
	
	bool skipShebang = false;
	
	if(argc == 3) {
		if(strcmp(argv[1], "-s") == 0) {
			skipShebang = true;
		}
		else {
			usage(argv[0]);
			return 1;
		}
	}
	
	src.open(argv[argc-1]);
	if(!src.is_open()) {
		std::cerr << "Unable to open '" << argv[argc-1] << "'." << std::endl;
		return 2;
	}
	
	return Fission(src, skipShebang).run();
}

