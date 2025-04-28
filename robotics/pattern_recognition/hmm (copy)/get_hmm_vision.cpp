/********************************************************
*	get_hmm_vision.c				*
*							*
*							*
*		University of Mexico U.N.A.M.		*
*			Jesus Savage			*
*							*
*				4/17/2009		*
*				4/17/2009		*
*********************************************************
*/


#include "HMMGet.h"

// It updates the hmm probabilities using the Viterbi algorithm

main(int argc,char *argv[])
{
	HMMGet *trainer = 0;
	
	trainer = new HMMGet;
	
	trainer->get_inputs(argc, argv);
	trainer->execute(argc, argv);
	
	delete trainer;
	
}



