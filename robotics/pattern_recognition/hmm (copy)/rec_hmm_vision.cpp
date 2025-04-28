//
// rec_hmm_vision.cpp
//
// This program recognizes an image pattern using HMM
// represent images' readings
//
// make -f Makefile_rec_hmm_vision
//
//  J. Savage, 4-22-2009
//      FI- UNAM
//

#include "HMMRec.h"


int main(int argc, char *argv[]) {

	HMMRec *recognizer;
	
	recognizer = new HMMRec();
	/* it gets line inputs */
	recognizer->get_inputs(argc, argv);
	recognizer->init();
	recognizer->find("");
	
	delete recognizer;


	
}



