/********************************************************************************
*                                                                            	*
*  evaluate_sort.cpp 		                              	     	*
*  ===================                                                       	*
*                                                                            	*
*  Description: 							     	*
*  It evaluates the sorts done to a group of numbers with state machines using 	*
*  recurrent neural networks.						     	*
*									     	*
*  Compile:								     	*
*	make -f Makefile_Evaluate_Sort					     	*
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
#include "structures.h"
#include "inputs_sorts.h"
#include "neural_networks_lib.h"
#include "state_machine_nn.h"

#define K1 1
#define K2 0

void sorts(int num,int test,nn_inputs *n_sorts){

 int i,j,k,l;
 int tmp;
 int ftmp;


 for(l=1;l<=num;l++){

        ftmp=n_sorts->x[test][l];

        for(k=l+1;k<=num;k++){
                if (ftmp < n_sorts->x[test][k]){
                        ftmp=n_sorts->x[test][k];
                        n_sorts->x[test][k]=n_sorts->x[test][l];
                        n_sorts->x[test][l]=ftmp;
                }
        }
 }

}




// It evaluates the sort done by the NN 
float evaluate_sorts(Inputs inputs)
{
 char file_results[250];
 char file_inputs[250];
 char file_outputs[250];
 int i,j,k;
 int tmp;
 float result = 0.0,result_p;
 float result_e=0.1;
 float result_ep;
 FILE *fpw;
 nn_inputs n_inputs;
 nn_inputs n_outputs;
 nn_inputs n_sort;


 // it reads the input file
 sprintf(file_inputs,"%s%s.dat",inputs.path,inputs.environment);
 printf("input file: %s\n",file_inputs);
 read_inputs(&n_inputs,file_inputs,&n_sort);

 // it opens the output file
 sprintf(file_outputs,"%s%s.dat",inputs.path,inputs.output);
 printf("output file: %s\n",file_outputs);
 read_inputs(&n_outputs,file_outputs,&n_sort);

 sprintf(file_results,"%sresults.dat",inputs.path);
 if((fpw=fopen(file_results,"w")) == NULL){
	printf("File %s can not be open\n",file_results);
       	return(0);
 }	



 for(j=1; j<=n_inputs.num_tests;j++){

	printf("\n\n ************************ Test %d ************************************\n",j);


	for(k=1;k <= n_inputs.num_inputs;k++){
 		n_sort.x[j][k]=n_inputs.x[j][k];
	}
	
	sorts(n_inputs.num_inputs,j,&n_sort);

	result_p=0.0;
	for(k=1;k <= n_inputs.num_inputs;k++){
 		printf("%d inputs %d sort %d output %d\n",k,n_inputs.x[j][k],n_sort.x[j][k],n_outputs.x[j][k]);
		tmp = (n_sort.x[j][k]-n_outputs.x[j][k])*(n_sort.x[j][k]-n_outputs.x[j][k]);
		result_p = result_p + float(tmp*tmp);
	}
	result_p=result_p/n_inputs.num_inputs;
	result_p=sqrt(result_p);

	result_ep=0;
	for(k=1;k <= n_inputs.num_inputs;k++){
		for(i=1;i <= n_inputs.num_inputs;i++){
			if(n_inputs.x[j][k] == n_outputs.x[j][i]){
                		printf("%d %d inputs %d output %d\n",k,i,n_inputs.x[j][k],n_outputs.x[j][i]);
                		result_ep = result_ep + 10.0;
				break;
			}
		}
        }

 	printf("result ep %f\n",result_ep);
	result = result + result_p;
	result_e = result_e + result_ep;
 }


 printf("result e %f\n",result_e);
 result = K1 * result + K2 / result_e;
 printf("resul total %f\n",result);
 fprintf(fpw,"%f\n",result);
 fclose(fpw);
 return(j-1);

}




// Main program
int main(int argc, char *argv[])
{

 Inputs inputs;
 float evaluation;


 /* it gets line inputs */
 get_inputs(argc,argv,&inputs);

 //it sorts the data with the NN
 evaluation=evaluate_sorts(inputs);

 return 0;

}


