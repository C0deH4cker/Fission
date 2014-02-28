#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>
#include "Fission.h"

using namespace fsn;


int main(int argc, char* argv[]) {
	std::ifstream src;
	
#if !DEBUG
	if(argc != 2) {
		fprintf(stderr, "Usage: %s program.fsn\n", argv[0]);
		return 1;
	}
	
	src.open(argv[1]);
	if(!src.is_open()) {
		std::cerr << "Unable to open '" << argv[1] << "'." << std::endl;
		exit(EXIT_FAILURE);
	}
#else
	
	src.open("cloners.fsn");
	if(!src.is_open()) {
		std::cerr << "Unable to open source file." << std::endl;
		exit(EXIT_FAILURE);
	}
#endif
	
	Fission prog(src);
	
	return prog.run();
}

