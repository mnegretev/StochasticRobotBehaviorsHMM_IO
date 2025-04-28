/*
	Jesus Savage

	Compilation:
        make transform_gen

	2003
	2013 
*/





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include "/usr/include/sys/time.h"

#include "genetics.h"



int main(int argc,char *args[]){

	
	srandom((int)time((time_t *)NULL));
	
	if (argc>1){
	    if (strcmp(args[1],"-h")==0){
	     printf("Usage: \n");
	     printf("\n	transform_gen states_machine path num_individuals num_bits_states num_bits_output num_bits_inputs num_bits_individuals population_file \n");
	     printf("\n	transform_gen potentials path num_individuals num_bits_variables num_bits_fractions num_variables population_file \n");
	     printf("\n	transform_gen neural_nets path num_individuals num_bits_variables num_bits_fractions population_file num_layers num_nn_recurrent\n"); 
	     printf("				flg_weight_recurrent times_inputs_delay num_nn_layer2 num_nn_layer2 ... num_nn_layern \n");
	     printf("\n	transform state_machine_hmm path_observations num_individuals num_bits_individuals num_states num_symbols num_outputs name_pop\n");
	     printf("\nExamples: \n");
	     printf("	transform_gen state_machine ../observations/ 100 4 3 5 3584 avoid\n");
	     printf("	transform_gen potentials /home/savage/observations/ 100 16 8 5 avoid\n");
	     printf("	transform_gen neural_nets /home/savage/observations/ 100 8 4 avoid 3 2 0 0 4 3 2\n");
	     printf("	transform_gen state_machine_hmm ../data/ 100 10 14 32 5 avoid\n");
	    }
            else if (strcmp(args[1],"state_machine")==0){
	     	transform_state_machine(args,argc);
	    }
            else if (strcmp(args[1],"potentials")==0){
	     	transform_potentials(args,argc);
	    }
            else if (strcmp(args[1],"neural_nets")==0){
	     	transform_nn(args,argc);
	    }
            else if (strcmp(args[1],"state_machine_hmm")==0){
	     	transform_state_machine_hmm(args,argc);
	    }
      	else
	     printf("\nWrong parameters, type transform_gen -h for help\n");
	}
      	else
	     printf("\nPlease enter parameters or -h for help\n");

	exit(0);

}
