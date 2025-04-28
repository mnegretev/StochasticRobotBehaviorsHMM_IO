/********************************************************************************
*                                                                            	*
*  Sort_State_Machine_NN.cpp 		                              	     	*
*  ===================                                                       	*
*                                                                            	*
*  Description: 							     	*
*  It sorts a group of numbers with state machines using 			*
*  recurrent neural networks.						     	*
*									     	*
*  Compile:								     	*
*	make -f Makefile_Sort_State_Machine_NN				     	*
*									     	*
*                               J. Savage                                    	*
*                                                                        	*
*                               FI-UNAM 2018                                 	*
********************************************************************************/

// System include files
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
// Robotics include files
//#include "../utilities/constants.h"
#include "structures.h"
//#include "../simulator/simulation.h"
//#include "../utilities/utilities.h"
//#include "../utilities/random.h"
#include "inputs.h"
#include "neural_networks_lib.h"
#include "state_machine_nn.h"





// it sorts the data from an input file 
int sorts_NN(Inputs inputs)
{
 char file_data[250];
 char file_nn[250];
 char file_output[250];
 int j,k;
 FILE *fpw;
 int debug=1;
 int selection = 3;
 nn_inputs n_inputs;
 nn_inputs n_outputs;
 int flg_noise = 0;


 selection=inputs.selection; 
 strcpy(file_nn,inputs.file);
 printf("NN configuration file %s\n",file_nn);


 // it reads the input file
 sprintf(file_data,"%s%s.dat",inputs.path,inputs.environment);
 printf("input file: %s\n",file_data);
 read_inputs(&n_inputs,file_data,&n_outputs);

 // it opens the output file
 sprintf(file_output,"%s%s.dat",inputs.path,inputs.output);
 printf("output file: %s\n",file_output);
 if((fpw=fopen(file_output,"w")) == NULL){
	printf("File %s can not be open\n",file_output);
       	return(0);
 }	

 fprintf(fpw,"%d\n",n_inputs.num_tests);
 fprintf(fpw,"%d\n",n_inputs.num_inputs);
 fprintf(fpw,"%d\n",n_inputs.num_bits_inputs);


 for(j=1; j<=n_inputs.num_tests;j++){

	printf("\n\n ************************ Test %d ************************************\n",j);

	// It sorts data using a recurrent neural network
	state_machine_nn(file_nn,n_inputs,j,&n_outputs,flg_noise,selection,inputs.path,inputs.number_steps);

	for(k=1;k <= n_inputs.num_inputs;k++){
 		fprintf(fpw,"%d ",n_outputs.x[j][k]);
	}
	fprintf(fpw,"\n");

 }


 fclose(fpw);
 return(j-1);


}




// Main program
int main(int argc, char *argv[])
{

 Inputs inputs;
 int num_steps;


 /* it gets line inputs */
 get_inputs(argc,argv,&inputs);

 //it sorts the data with the NN
 num_steps=sorts_NN(inputs);

 return 0;

}


