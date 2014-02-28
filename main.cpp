#include <fstream>
#include <cstdio>
#include "Fission.h"

using namespace fsn;


int main(int argc, char* argv[]) {
	std::ifstream src;
	
	if(argc != 2) {
		fprintf(stderr, "Usage: %s program.fsn\n", argv[0]);
		return 1;
	}
	
	src.open(argv[1]);
	if(!src.is_open()) {
		fprintf(stderr, "Unable to open '%s'.\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	
	return Fission(src).run();
}

