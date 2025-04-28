/*
	Jesus Savage

	Compilation:
        make transform_gen

	2003
	2020 
*/





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include "/usr/include/sys/time.h"

#include "../utilities/structures.h"
#include "genetics.h"


int main(int argc,char *args[]){

	
	srandom((int)time((time_t *)NULL));
	
	if (argc>1){
	    if (strcmp(args[1],"-h")==0){
	     printf("Usage: \n");
	     printf("\n	transform_gen state_machine path num_individuals num_bits_states num_bits_output num_bits_inputs num_bits_individuals population_file \n");
	     printf("\n	transform_gen state_machine_stochastic path num_individuals num_bits_states num_bits_output num_bits_inputs num_bits_stochastic_variables population_file \n");
	     printf("\n	transform_gen reactive path num_individuals num_bits_output num_bits_inputs population_file \n");
	     printf("\n	transform_gen reactive_stochastic path num_individuals num_bits_output num_bits_inputs population_file num_bits_variables \n");
	     printf("\n	transform_gen potentials path num_individuals num_bits_variables num_bits_fractions num_variables population_file \n");
	     printf("\n	transform_gen neural_nets path num_individuals num_bits_variables num_bits_fractions population_file num_layers num_nn_recurrent\n"); 
	     printf("				times_inputs_delay num_nn_layer1 num_nn_layer2 ... num_nn_layern \n");
	     printf("\n	transform_gen state_machine_hmm path_observations num_individuals num_bits_individuals num_states num_symbols num_outputs name_pop Meally/Moore\n");
	     printf("\n	transform_gen mdp path num_individuals num_bits_variables num_bits_fractions num_variables name_pop\n");
	     printf("\n	transform_gen in_state_machine path num_individuals num_bits_states num_bits_output num_bits_inputs num_bits_individuals population_file \n");
	     printf("\nExamples: \n");
	     printf("	transform_gen state_machine ../observations/ 100 4 3 5 3584 avoid\n");
	     printf("	transform_gen state_machine_stochastic ../observations/ 100 4 3 8 8 avoid\n");
	     printf("	transform_gen reactive ../observations/ 100 3 5 avoid\n");
	     printf("	transform_gen reactive_stochastic ../observations/ 100 3 8 avoid 8\n");
	     printf("	transform_gen potentials /home/savage/observations/ 100 16 8 5 avoid\n");
	     printf("	transform_gen neural_nets /home/savage/observations/ 100 8 4 avoid 3 2 0 0 4 3 2\n");
	     printf("	transform_gen neural_nets /home/biorobotica/data/data_15/ 20 8 7 avoid_nn 2 4 0 5 20 3\n");
	     printf("	transform_gen state_machine_hmm ../data/ 100 10 14 32 5 avoid 1\n");
	     printf("	transform_gen state_machine_hmm ../data/ 100 10 14 32 5 avoid 0\n");
	     printf("	transform_gen mdp /home/savage/data/data_15/ 100 8 7 72 avoid\n");
	     printf("	transform_gen in_state_machine /home/biorobotica/data/data_5/ 100 4 3 13 432 avoid_infsm \n");
	    }
            else if (strcmp(args[1],"state_machine")==0){
	     	transform_state_machine(args,argc);
	    }
            else if (strcmp(args[1],"state_machine_stochastic")==0){
	     	transform_state_machine_stochastic(args,argc);
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
            else if (strcmp(args[1],"reactive")==0){
	     	transform_reactive(args,argc);
	    }
            else if (strcmp(args[1],"reactive_stochastic")==0){
	     	transform_reactive_stochastic(args,argc);
	    }
            else if (strcmp(args[1],"mdp")==0){
	     	transform_mdp(args,argc);
	    }
            else if (strcmp(args[1],"in_state_machine")==0){
	     	transform_in_state_machine(args,argc);
	    }
      	else
	     printf("\nWrong parameters, type transform_gen -h for help\n");
	}
      	else
	     printf("\nPlease enter parameters or -h for help\n");

	exit(0);

}
