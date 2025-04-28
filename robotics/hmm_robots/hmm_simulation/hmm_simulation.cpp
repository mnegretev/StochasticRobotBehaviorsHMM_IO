/********************************************************************************************************
*                               									*
*        hmm_simulation.cpp     									*
*        Basic HMM simulation   									*
*                               									*
* Compilation:                              								*
* make -f Makefile_hmm_simulation              								*
*                               									*
* Usage: hmm_simulation -                								*
*                               									*
* Example:                              								*
* hmm_simulation -p test_data/ -f sim_state_machine -o sim_state_machine -s 20                         	*
*                               									*
*               Jesus Savage    									*
*               FI-UNAM         									*
*                               									*
*               2-25-2022       									*
*               3-06-2022       									*
*                               									*
*                               									*
*********************************************************************************************************/

// System include files
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//Constants
//#define DEBUG 1 // Uncomment this line to see debuging data
#define NUM_MAX_OBS 1000
#define REAL float
#define NUM_MAX_STATES 100
#define MAX_NUM_SENSORS 2048
#define NUM_MAX_CENTROIDS 1024
#ifndef PI
#define PI 3.1415926535f
#endif
#define CNT_GOAL 0.6
#define MAG_ADVANCE 0.04


// Structures
typedef struct _raw{
        int flag;
         int region;
         float x,y,theta[MAX_NUM_SENSORS],sensors[MAX_NUM_SENSORS];
} Raw;

typedef struct _Inputs_sim{
 char path[256];
 char input_file[256];
 char output_file[256];
 int num_steps;
 int selection;
} Inputs_sim;


struct hmm_database {
        char objects_file[300];
        double bigger, prob[NUM_MAX_CENTROIDS], p;
        double vit_prob[NUM_MAX_CENTROIDS];
        int index;
        int index_vit ;
        double bigger_vit;
        float **ais, *pis, **bis, **cis;
        int num_bits_inputs;
        int num_states;
        int num_obs_symbols;
        int num_out_symbols;
        int num_vectors;
        int  *seq_states;
        int *observations;
};


// Include local files
#include "random.h"


// Functions
REAL *alloc_vector(int len)
{
    return (REAL *) malloc((unsigned) len*sizeof(REAL));

}

int *alloc_vector_int(int len)
{
    return (int *) malloc((unsigned) len*sizeof(int));
}



// It allocates memory space
float **alloc_matrix(int row,int col)
{
    int i;
    float **m;

    m = (float **) malloc((unsigned) row*sizeof(float *));
    for (i=0; i<row; i++)
        m[i] = (float *) malloc((unsigned) col*sizeof(float));
    return m;
}



// it initializes the hmm
void hmm_initialize(struct hmm_database *hmm, int Meally) {
        int i,j;

        hmm->index = 1;
        hmm->index_vit = -1;

        #ifdef DEBUG
        printf("hmm_initialize Meally %d\n",Meally);
        #endif

        // It allocates the matrices used for the hmm evaluation
        if ((hmm->ais = (float **)alloc_matrix(hmm->num_states + 1, hmm->num_states + 1 )) == 0) {
                        printf("\n Memory allocation error ");
                        exit(1);
        }
        if ((hmm->bis = (float **)alloc_matrix(hmm->num_states + 1, hmm->num_obs_symbols + 1)) == 0) {
                        printf("\n Memory allocation error ");
                        exit(1);
        }
        if(Meally == 1){
                if ((hmm->cis = (float **)alloc_matrix(hmm->num_states*hmm->num_obs_symbols + 1, hmm->num_out_symbols + 1)) == 0) {
                        printf("\n Memory allocation error ");
                        exit(1);
                }
        }
        else{
                if ((hmm->cis = (float **)alloc_matrix(hmm->num_states + 1, hmm->num_out_symbols + 1)) == 0) {
                        printf("\n Memory allocation error ");
                        exit(1);
                }
        }
        if ((hmm->pis = (float *)alloc_vector(hmm->num_states + 1)) == 0) {
                        printf("\n Memory allocation error ");
                        exit(1);
        }

        if ((hmm->observations = (int *) alloc_vector_int((hmm->num_vectors + 1)) ) == 0) {
                printf("\n Memory allocation error: observations ");
                exit(0);
        }

        // it allocates the states vectors
        if ((hmm->seq_states = (int *) alloc_vector_int((hmm->num_vectors + 1))) == 0) {
                        printf("\n Memory allocation error: observations ");
                        exit(0);
        }

}



/* Function that reads the ais,bis and pis of a hmm */
void read_hmms(struct hmm_database *hmm, int flg_read,char *path, int flg_inputs)
{
   FILE *fp2;
   float average,tmp;
   int j,k;
   char input_file[400];
   int n_states,n_obs_symbols,n_out_symbols;
   int n_bits_inputs;
   int limits;


   /* It opens the hmm file */
   sprintf(input_file,"%s%s.prb",path,hmm->objects_file);
   //printf("Reading HMM FILE: %s\n",input_file);
   fp2=fopen(input_file,"r");
   if(fp2==0){
        printf("\n File %s does not exists\n",input_file);
        exit(0);
   }

   /* It reads the number of states, observation symbols and output symbols */
   fscanf(fp2,"%d",&n_states);
   hmm->num_states=n_states;
   fscanf(fp2,"%d",&n_obs_symbols);
   hmm->num_obs_symbols=n_obs_symbols;
   fscanf(fp2,"%d",&n_out_symbols);
   hmm->num_out_symbols=n_out_symbols;


   if(flg_read==0) {
                fclose(fp2);
#ifdef DEBUG
                printf("Num.states %d num.obs_symbols %d num_out_symbols %d\n",n_states,n_obs_symbols,n_out_symbols);
                printf("Meally/Moore %d\n",flg_inputs);
#endif
                return;
   }

   // It reads the initial probabilities
   average=0;
   for(j=1;j<=n_states;j++){
        fscanf(fp2,"%f",&tmp);
        hmm->pis[j]=tmp;
#ifdef DEBUG
        printf(" pi[%d] %f\n",j,hmm->pis[j]);
#endif
        average+=hmm->pis[j];
   }

#ifdef DEBUG
   printf("\n sum pis %f\n",average);
#endif

   // It reads the transition probabilities
   for(j=1;j<=n_states;j++){
        average=0;
        for(k=1;k<=n_states;k++){
                fscanf(fp2,"%f",&tmp);
                hmm->ais[j][k]=tmp;
#ifdef DEBUG
                printf("\n a[%d][%d] %f",j,k,hmm->ais[j][k]);
#endif
                average+=hmm->ais[j][k];
        }
#ifdef DEBUG
        printf("\n %d.- sum= ais %f\n",j,average);
#endif
   }

   for(j=1;j<=n_states;j++){
        average=0;
        for(k=1;k<=n_obs_symbols;k++){
                     fscanf(fp2,"%f",&tmp);
                     hmm->bis[j][k]=tmp;
#ifdef DEBUG
                     printf(" b[%d][%d] %f\n",j,k,hmm->bis[j][k]);
#endif
                     average+=hmm->bis[j][k];
        }
#ifdef DEBUG
        printf("sum bis[%d] %f\n",j,average);
#endif
   }

   if(flg_inputs==1) limits=n_states*n_obs_symbols;
   else limits=n_states;

#ifdef DEBUG
   printf("Meally/Moore %d limits %d \n",flg_inputs, limits);
#endif


   for(j=1;j<=limits;j++){
        average=0;
        for(k=1;k<=n_out_symbols;k++){
                     fscanf(fp2,"%f",&tmp);
                     hmm->cis[j][k]=tmp;
#ifdef DEBUG
                     printf(" c[%d][%d] %f\n",j,k,hmm->cis[j][k]);
#endif
                     average+=hmm->cis[j][k];
        }
#ifdef DEBUG
        printf("sum cis[%d] %f\n",j,average);
#endif
   }

   fclose(fp2);

}


/* Function that that calculate the first state from the pis */
int calculate_hmm_first_state(struct hmm_database hmm)
{
 int i,j;
 float rand;
 float tmp;


 // it generates a Uniform random variable between 0 and 1
 rand=generaR(0.0,1.0);
#ifdef DEBUG
 printf(" random %f\n",rand);
#endif

 tmp=hmm.pis[1];

 for(j=1;j<=hmm.num_states;j++){
        if(rand <= tmp){
                i=j;
                j=hmm.num_states+1;
        } else{
                tmp= tmp + hmm.pis[j+1];
                i=j;
        }
   }

#ifdef DEBUG
   printf(" Initial HMM state %d tmp %f\n",i,tmp);
#endif

   return i;

}

/* Function that calculates the average number to be in an specific state */
void average(struct hmm_database hmm, int num_states)
{
 int j;
 float average[NUM_MAX_STATES];
 float major=0;
 int indx_major=0;

 
 for(j=1;j<=num_states;j++){
 	average[j]=1/(1 - hmm.ais[j][j]);  
	if(average[j]>major){
		major=average[j];
		indx_major=j;

	}
#ifdef DEBUG
	printf("%d average %f\n",j,average[j]); 
#endif

 }


#ifdef DEBUG
 printf("%d major average %f\n",indx_major,major); 
#endif

}




/* Function that calculates an observation given a present state an the Bs matrix */
int hmm_observation(struct hmm_database hmm, int state)
{
 int i,j;
 float rand;
 float tmp;


 // it generates a Uniform random variable between 0 and 1
 rand=generaR(0.0,1.0);
#ifdef DEBUG
 printf("\nobservations random %f\n",rand);
#endif

 tmp=hmm.bis[state][1];

 for(j=1;j<=hmm.num_obs_symbols;j++){
	#ifdef DEBUG
 	printf("observations tmp %f\n",tmp);
	#endif
        if(rand <= tmp){
                i=j;
                j=hmm.num_obs_symbols+1;
        } else{
                tmp= tmp + hmm.bis[state][j+1];
                i=j;
        }
   }

#ifdef DEBUG
   printf("HMM observation %d tmp %f\n",i,tmp);
#endif

   return i;

}


/* Function that calculates an action given a present state an the Cs matrix */
int hmm_actions(struct hmm_database hmm, int state)
{
 int i,j;
 float rand;
 float tmp;


 // it generates a Uniform random variable between 0 and 1
 rand=generaR(0.0,1.0);
#ifdef DEBUG
 printf("\nactions random %f\n",rand);
#endif

 tmp=hmm.cis[state][1];

 for(j=1;j<=hmm.num_out_symbols;j++){
	#ifdef DEBUG
 	printf("actions tmp %f\n",tmp);
	#endif
        if(rand <= tmp){
                i=j;
                j=hmm.num_out_symbols+1;
        } else{
                tmp= tmp + hmm.cis[state][j+1];
                i=j;
        }
   }

#ifdef DEBUG
   printf("HMM action %d tmp %f\n",i,tmp);
#endif

   return i;

}



/* Function that calculates next state given a present state an the As matrix */
int hmm_next_state(struct hmm_database hmm, int state)
{
 int i,j;
 float rand;
 float tmp;


 // it generates a Uniform random variable between 0 and 1
 rand=generaR(0.0,1.0);
#ifdef DEBUG
 printf("\nstate random %f\n",rand);
#endif

 tmp=hmm.ais[state][1];

 for(j=1;j<=hmm.num_states;j++){
	#ifdef DEBUG
 	printf("state tmp %f\n",tmp);
	#endif
        if(rand <= tmp){
                i=j;
                j=hmm.num_states+1;
        } else{
                tmp= tmp + hmm.ais[state][j+1];
                i=j;
        }
   }

#ifdef DEBUG
   printf("HMM next state %d tmp %f\n",i,tmp);
#endif

   return i;

}




 // It saves the results in a file
void save_results(char *output_file, int num_steps, int *states, int num_inputs, int *observations, int num_outputs, int *actions){

 int j;
 FILE *fp2;


 // It opens the observations output file //
 printf("Observations output file FILE: %s\n",output_file);
 fp2=fopen(output_file,"w");
 if(fp2==0){
        printf("\n File %s can not be created\n",output_file);
        exit(0);
 }

 fprintf(fp2,"%d\n",num_steps);
 for(j=1;j<=num_steps;j++){
	fprintf(fp2,"%d ",states[j]);
 }
 fprintf(fp2,"\n");
 if(num_inputs>0){
 	for(j=1;j<=num_steps;j++){
		fprintf(fp2,"%d ",observations[j]);
 	}
 	fprintf(fp2,"\n");
 }

 if(num_outputs>0){
 	for(j=1;j<=num_steps;j++){
		fprintf(fp2,"%d ",actions[j]);
 	}
 	fprintf(fp2,"\n");
 }

}


// Simulation of probabilistic state machines using HMMs
void  state_machine_simulation_hmm(char *input_file, char *out_file, char *path, int num_steps, int selection){

 int states[NUM_MAX_OBS];
 int observations[NUM_MAX_OBS];
 int actions[NUM_MAX_OBS];
 char output_file[500];
 int previous_state=1;
 int flg_old=1;
 int out_symbol;
 struct hmm_database hmm;
 int num_states,num_inputs,num_outputs;
 int Time=1;
 int num=0;
 int Meally=0;
 int j=0;
 int state;



 printf("Input file %s\n",input_file);
 strcpy(hmm.objects_file,input_file);
 //sprintf(output_file,"%s%s.obs",path,out_file);
 sprintf(output_file,"%s%s.obs",path,out_file);



 // It reads the number of states, num. obs. symbols and nun. out symbols of the hmm 
 read_hmms(&hmm,0,path,0);

 //It creates the HMM structure
 hmm_initialize(&hmm,Meally);

 // It reads the complete hmm 
 read_hmms(&hmm,1,path,0);
 num_states=hmm.num_states;
 num_inputs=hmm.num_obs_symbols;
 num_outputs=hmm.num_out_symbols;


 // Initializes the random generator
 srandom((int)time((time_t *)NULL));

 states[Time]=calculate_hmm_first_state(hmm);
 
 for(j=2;j<=num_steps+1;j++){
#ifdef DEBUG
 	printf("\n\n ********************* state machine HMM %d **********\n",j-1);
#endif
	printf("%d state %d",j-1,states[Time]);
 	if(num_inputs > 0){
	       	observations[Time]= hmm_observation(hmm, states[Time]);
		printf(" obs %d",observations[Time]);
	}
 	if(num_outputs > 0) {
		actions[Time]= hmm_actions(hmm, states[Time]);
		printf(" action %d",actions[Time]);
	}
	printf("\n");

	state= states[Time];
	Time++;
 	states[Time]= hmm_next_state(hmm, state);
 }

 // It saves the results in a file
 save_results(output_file,num_steps,states,num_inputs, observations,num_outputs, actions);

 // It finds the average of times to be in a particular state
 average(hmm, num_states);

}




// it gets line inputs 
int get_inputs(int argc, char **argv, Inputs_sim *inputs)
{

 int i;

 // It sets default values 
 strcpy(inputs->path,"test_data/");
 strcpy(inputs->input_file,"hmm_destination_avoidance_fsm");
 strcpy(inputs->output_file,"observations");
 inputs->num_steps = NUM_MAX_OBS;
 //inputs->selection = 0;


// reads input parameters 
  if (argc>1) {
        for(i=1;i<argc;i++){
          if (!strcmp(argv[i],"-h")){

                //printf("Sintax: %s -p path_data -f input_file -o output_file -s number_steps -l selection: 0 Markov Chain;1 HMM; 2 EHMM \n",argv[0]);
                printf("Sintax: %s -p path_data -f input_file -o output_file -s number_steps\n\n",argv[0]);
                printf("Example Markov chain: ");
                printf("%s -p test_data/ -f weather_rain -o observations -s 100\n\n",argv[0]);
                printf("Example Hidden Markov chain: ");
                printf("%s -p test_data/ -f avoid_hmm_1 -o test -s 100\n\n",argv[0]);
                printf("Example Hidden Markov chain with actions: ");
		printf("%s -p test_data/ -f sim_state_machine -o sim_state_machine -s 10\n",argv[0]);

                exit(1);
          }
          else if (!strcmp(argv[i],"-p")){
                strcpy(inputs->path,argv[i+1]);
          }
          else if (!strcmp(argv[i],"-f")){
                strcpy(inputs->input_file,argv[i+1]);
          }
          else if (!strcmp(argv[i],"-o")){
                strcpy(inputs->output_file,argv[i+1]);
          }
          else if (!strcmp(argv[i],"-s")){
                inputs->num_steps=atoi(argv[i+1]);
		if(inputs->num_steps > NUM_MAX_OBS){
			printf("The number of steps %d exceeds the maximum number of steps %d\n", inputs->num_steps,NUM_MAX_OBS);
			printf("Change constant NUM_MAX_OBS in file hmm_simulation.cpp \n");
			exit(0);
		}
          }
          //else if (!strcmp(argv[i],"-l")){
                //inputs->selection=atoi(argv[i+1]);
          //}
    }
  }
  else{

      printf("\nIt will use default values:\n");
  }

  printf("%s -p %s -f %s -o %s -s %d\n",argv[0],inputs->path,inputs->input_file,inputs->output_file,inputs->num_steps);


  return(0);

}




// Main program
int main(int argc, char *argv[])
{

 Inputs_sim inputs;

 // it gets line inputs, function in ../utilities/inputs.h 
 get_inputs(argc,argv,&inputs);

 // it simulates a probabilistic state machine 
 state_machine_simulation_hmm(inputs.input_file, inputs.output_file, inputs.path, inputs.num_steps, inputs.selection);

 return 0;

}

