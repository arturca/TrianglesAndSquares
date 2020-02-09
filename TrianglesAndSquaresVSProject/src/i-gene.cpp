#include "i-gene.h"


int AGene::recognizeGene() {
	//circle
	if (getApexes().size() == 1) {
		return 0;
	}
	//triangle
	if (getApexes().size() == 3) {
		return 1;
	}
	else return -1;

};

