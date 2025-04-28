/*
   GENETIC ALGORITHMS PROGRAM 
  
	Edna Marquez
	Jesus Savage

	Compilation:
        make genetics_general 
	genetics_general -h
	wish genetics_state_machine.tcl
	wish genetics_potentials.tcl

	2003
	2011 
*/





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include "/usr/include/sys/time.h"

#include "genetics.h"



int main(int argc,char *args[]){
	
	int flg_vsc=0;
	
	//srandom((int)time((time_t *)NULL));
	initialize_seed();
	
	if (argc>1){
	  if (strcmp(args[1],"genera")==0){
	     if (strcmp(args[2],"vasconcelos")==0) flg_vsc=1;
	     printf("Create a new population  \n");	  
	     genera(args,flg_vsc);
	  }   
	  else
	    if (strcmp(args[1],"standard")==0){
	     printf("Generate  offspring  \n");
	     descend_binary(args,argc,0);
	  }
	  else
            if (strcmp(args[1],"vasconcelos")==0){
             printf("Generate  offspring using the Vasconcelos algorithm \n");
             descend_binary(args,argc,1);
          }
	  else
            if (strcmp(args[1],"fitness")==0){
	     if (strcmp(args[2],"vasconcelos")==0) flg_vsc=1;
             printf("Changes the fitness using fitness sharing and Pareto algorithm \n");
             fitness_sharing(args,argc,flg_vsc);
          }
	  else
	    if (strcmp(args[1],"-h")==0){
	     printf("Usage: \n");
	     printf("	genetics_general genera standard path num_individuals num_bits_individuals population_file \n");
	     printf("	genetics_general genera vasconcelos path num_individuals num_bits_individuals population_file \n");
	     printf("	genetics_general standard path num_individuals num_bits_individuals population_file mutation_factor cross_factor num_best_factor\n\n");
	     printf("	genetics_general vasconcelos path num_individuals num_bits_individuals population_file mutation_factor cross_factor num_best_factor\n\n");
	     printf("	genetics_general fitness vasconcelos/standard path num_individuals num_bits_individuals population_file \n");
	     printf("Examples: \n");
	     printf("	genetics_general genera standard /home/savage/observations/ 100 640 avoid\n");
	     printf("	genetics_general genera vasconcelos /home/savage/observations/ 100 640 avoid\n\n");
	     printf("	genetics_general standard /home/savage/observations/ 100 640 avoid 0.1 0.85 0.10\n");
	     printf("	genetics_general vasconcelos /home/savage/observations/ 100 640 avoid 0.1 0.85 0.10\n");
	     printf("	genetics_general fitness vasconcelos /home/savage/observations/ 10 7488 avoid \n\n");
	  }
            else
	     printf("\nInvalid function\n");
	}
	else
	  printf("Few arguments\n");

	return(0);

}
