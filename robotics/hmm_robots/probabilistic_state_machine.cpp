/********************************************************************************************************
*                                                                               			*
* probabilistic_state_machine.cpp                                               			*
*  ===================                                                         	 			*
*                                                                               			*
*  Description:                                                                 			*
*	It executes a probabilistic state machine							*
*                                                                               			*
*  Compile:                                                                     			*
*       make -f Makefile_probabilistic_state_machine                            			*
*                                                                               			*
* Run:                                                                          			*
*	probabilistic_state_machine -p hmm_simulation/test_data/ -f state_machine -o sim_state_machine	*
*                                                                               			*
*                                                                               			*
*                               J. Savage                                       			*
*                                                                               			*
*                               FI-UNAM 2023                                    			*
*                               FI-UNAM 2023                                    			*
*                                                                               			*
*********************************************************************************************************/

//#define DEBUG 1 // Uncomment this line to see debuging data


// System include files
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#define NUM_MAX_OBS 1000
#define REAL float
#define NUM_STATES 1000
#define MAX_NUM_SENSORS 2048
#define NUM_MAX_CENTROIDS 1024
#ifndef PI
#define PI 3.1415926535f
#endif
#define NUM_MAX_CORR 10

typedef struct _Inputs_pr{
 char path[256];
 char pr_file[256];
 char obs_file[256];
 char output_file[256];
} Inputs_pr;


// Structures
typedef struct _obs_data{
	 int num;
         int states[1000];
	 int obs[1000];
	 int outputs[1000];
} Obs_data;

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


// Structures
typedef struct _raw{
        int flag;
         int region;
         float x,y,theta[MAX_NUM_SENSORS],sensors[MAX_NUM_SENSORS];
} Raw;



//Include local files
#include "hmm_simulation/random.h"


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
void hmm_initialize(struct hmm_database *hmm) {
        int i,j;

        hmm->index = 1;
        hmm->index_vit = -1;

        // It allocates the matrices used for the hmm evaluation
        if ((hmm->ais = (float **)alloc_matrix(hmm->num_states + 1, hmm->num_states + 1 )) == 0) {
                        printf("\n Memory allocation error ");
                        exit(1);
        }
        if ((hmm->bis = (float **)alloc_matrix(hmm->num_states + 1, hmm->num_obs_symbols + 1)) == 0) {
                        printf("\n Memory allocation error ");
                        exit(1);
        }
        if ((hmm->cis = (float **)alloc_matrix(hmm->num_states + 1, hmm->num_out_symbols + 1)) == 0) {
                        printf("\n Memory allocation error ");
                        exit(1);
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
void read_hmms(struct hmm_database *hmm, int flg_read,char *path)
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

   limits=n_states;


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







int get_inputs_probabilistic(int argc, char **argv, Inputs_pr *inputs)
{

 int i;

 // It sets default values 
 strcpy(inputs->pr_file,"state_machine");
 strcpy(inputs->obs_file,"sim_state_machine");
 strcpy(inputs->output_file,"evaluation_state_machine");
 strcpy(inputs->path,"../test_data/");


  // reads input parameters 
  if (argc>1) {
        for(i=1;i<argc;i++){
          if (!strcmp(argv[i],"-h")){

		printf("Sintax: %s -p path -f probabilistic file -o observation file -e evaluation output file\n",argv[0]);
                printf("examples:\n\n");
		printf("%s -p hmm_simulation/test_data/ -f state_machine -o example -e evaluation_state_machine\n\n",argv[0]); 
		printf("%s -p hmm_simulation/test_data/ -f state_machine -o sim_state_machine -e evaluation_state_machine\n\n",argv[0]); 

                exit(1);
          }
          else if (!strcmp(argv[i],"-p")){
                strcpy(inputs->path,argv[i+1]);
          }
          else if (!strcmp(argv[i],"-f")){
                strcpy(inputs->pr_file,argv[i+1]);
          }
          else if (!strcmp(argv[i],"-o")){
                strcpy(inputs->obs_file,argv[i+1]);
          }
          else if (!strcmp(argv[i],"-e")){
                strcpy(inputs->output_file,argv[i+1]);
          }
    }
  }
  else{

      printf("\nIt will use default values:\n");
  }


  printf("%s -p %s -f %s -o %s -e %s\n",argv[0],inputs->path,inputs->pr_file,inputs->obs_file,inputs->output_file);


  return(0);

}


/* Function that reads a simulated observation file */
void read_obs(Obs_data *obs_data, char *path, char *obs_file)
{
   FILE *fp2;
   int j,k;
   char input_file[400];
   int n_obs_symbols;
   int tmp;


   /* It opens the observation file */
   sprintf(input_file,"%s%s.obs",path,obs_file);
   #ifdef DEBUG
   printf("Reading the observation FILE: %s\n",input_file);
   #endif
   fp2=fopen(input_file,"r");
   if(fp2==0){
        printf("\n File %s does not exists\n",input_file);
        exit(0);
   }

   // It reads the number of observation symbols 
   fscanf(fp2,"%d",&n_obs_symbols);
   obs_data->num=n_obs_symbols;

    #ifdef DEBUG
   	printf("Num. symbols %d\n",n_obs_symbols);
    #endif



   // It reads the simulated states
   for(j=1;j<=n_obs_symbols;j++){
                fscanf(fp2,"%d",&tmp);
                obs_data->states[j]=tmp;
    		#ifdef DEBUG
                printf("\n states[%d] %d",j,obs_data->states[j]);
		#endif

  }

  for(j=1;j<=n_obs_symbols;j++){
                fscanf(fp2,"%d",&tmp);
                obs_data->obs[j]=tmp;
		#ifdef DEBUG
                printf("\n observations[%d] %d",j,obs_data->obs[j]);
		#endif
 }


 for(j=1;j<=n_obs_symbols;j++){
                fscanf(fp2,"%d",&tmp);
                obs_data->outputs[j]=tmp;
		#ifdef DEBUG
                printf("\n outputs[%d] %d",j,obs_data->outputs[j]);
		#endif
  }

}





int get_next_state_hmm(int o, int flg_old, struct hmm_database hmm, int state)
{
  int t,i,j,ob;
  float bigger=0;
  float sum=0;
  float add=0;
  int indice=0,tmay=0;
  static float delta_old[NUM_STATES];
  int psi[NUM_STATES];
  float delta[NUM_STATES];
  float trans;
  int next_state;
  int next_state_region;
  int k;


  ob=o;
#ifdef DEBUG
  printf(" observation %d previous state %d\n",ob,state);
#endif
  k=state;

  //it checks if its the first time 
  if(flg_old==1){
        bigger=0.;
        for(j=1;j<=hmm.num_states;j++){
                delta[j]=(double)hmm.pis[j]*hmm.bis[j][ob];
                if(delta[j]>bigger){
                          bigger=delta[j];
               }
               //printf("pis[%d] %f bis[%d][%d] %f\n",j,hmm.pis[j],j,ob,hmm.bis[j][ob]);
               //printf("delta[%d] %e\n",j,delta[j]);
                //next_state=state;
        }
  }
  else{
        // it gets the state according the HMM A matrix

        for(j=1;j<=hmm.num_states;j++){
            bigger=0.;
            for(i=1;i<=hmm.num_states;i++){
               //trans=delta_old[i]*(double)hmm.ais[i][j]*hmm.bis[j][ob];
               trans=delta_old[i]*(double)hmm.ais[i][j];
               //printf("delta_old[%d] %f trans %f\n",i,delta_old[i],trans);
               //printf("ais[%d,%d] %f\n",i,j,hmm.ais[i][j]);
               if(trans > bigger){
                          bigger=trans;
               }
            }
            //printf("\n");
            //delta[j]=bigger;
            //delta[j]=bigger*hmm.bis[j][ob];
            delta[j]=bigger*hmm.bis[j][ob];
            //printf("bis[%d][%d] %f\n",j,ob,hmm.bis[j][ob]);
            //delta[j]=bigger*hmm.bis[k][ob];
            //printf("bis[%d][%d] %f\n",k,ob,hmm.bis[k][ob]);
            //printf("delta[%d] %f bigger %f\n\n",j,delta[j],bigger);

         }
  }

  bigger=0.;
  sum=0;
  for(j=1;j<=hmm.num_states;j++){
        //printf("delta[%d] %f\n",j,delta[j]);
        sum= sum + delta[j];

        if(delta[j]>bigger){
                bigger=delta[j];
                next_state=j;
        }
  }


  add=0;
  // it saves the scaled deltas for the next iteration
  for(j=1;j<=hmm.num_states;j++){
        //delta_old[j]=delta[j]/bigger;
        delta_old[j]=delta[j]/sum;
        add = add + delta_old[j];
#ifdef DEBUG
        printf("probability next state[%d] %f\n",j,delta_old[j]);
#endif
   }
   //printf("add %f\n",add);


   //next_state_region=calculate_region(delta_old,hmm.num_states);

#ifdef DEBUG
   printf(" Viterbi best state %d\n",next_state);
   printf(" Viterbi prob. region state %d\n",next_state_region);
#endif

   //return(next_state_region);
   return(next_state);

}


/* Function that that calculate the first state from the pis */
int calculate_hmm_first_state(struct hmm_database hmm, int quantized_value)
{
 int i,j;
 float rand;
 float tmp;


 // it generates a Uniform random variable between 0 and 1
 rand=generaR(0.0,1.0);
#ifdef DEBUG
 printf("\nrandom %f\n",rand);
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


int get_next_state_hmm_viterbi(int ob, int flg_old, struct hmm_database hmm, int state)
{
  int t,i,j;
  float bigger=0;
  float sum=0;
  float add=0;
  int indice=0,tmay=0;
  static float delta_old[NUM_STATES];
  int psi[NUM_STATES];
  float delta[NUM_STATES];
  float trans;
  int next_state;
  int next_state_region;
  int k;



  #ifdef DEBUG
  printf("get_next_state observation %d previous state %d\n",ob,state);
  #endif
  k=state;

  //it checks if its the first time 
  if(flg_old==1){
        bigger=0.;
        for(j=1;j<=hmm.num_states;j++){
                delta[j]=(double)hmm.pis[j]*hmm.bis[j][ob];
                if(delta[j]>bigger){
                          bigger=delta[j];
               }
               //printf("pis[%d] %f bis[%d][%d] %f\n",j,hmm.pis[j],j,ob,hmm.bis[j][ob]);
               //printf("delta[%d] %e\n",j,delta[j]);
                //next_state=state;
        }
  }
  else{
        // it gets the state according the HMM A matrix

        for(j=1;j<=hmm.num_states;j++){
            bigger=0.;
            for(i=1;i<=hmm.num_states;i++){
               //trans=(double)hmm.ais[i][j]*hmm.bis[j][ob];
               trans=delta_old[i]*(double)hmm.ais[i][j]*hmm.bis[j][ob];
#ifdef DEBUG
               printf("delta_old[%d] %f prob_transition %f\n",i,delta_old[i],trans);
               printf("ais[%d,%d] %f\n",i,j,hmm.ais[i][j]);
#endif
               if(trans > bigger){
                          bigger=trans;
               }
            }
            //printf("\n");
            delta[j]=bigger;
            //delta[j]=bigger*hmm.bis[j][ob];
#ifdef DEBUG
            printf("bis[%d][%d] %f\n",j,ob,hmm.bis[j][ob]);
#endif
            //delta[j]=bigger*hmm.bis[k][ob];
            //printf("bis[%d][%d] %f\n",k,ob,hmm.bis[k][ob]);
#ifdef DEBUG
            printf("delta[%d] %f bigger %f\n\n",j,delta[j],bigger);
#endif

         }
  }

  bigger=0.;
  sum=0;
  for(j=1;j<=hmm.num_states;j++){
        //printf("delta[%d] %f\n",j,delta[j]);
        sum= sum + delta[j];

        if(delta[j]>bigger){
                bigger=delta[j];
                next_state=j;
        }
  }


  add=0;
  // it saves the scaled deltas for the next iteration
  for(j=1;j<=hmm.num_states;j++){
        //delta_old[j]=delta[j]/bigger;
        delta_old[j]=delta[j]/sum;
        add = add + delta_old[j];
#ifdef DEBUG
        printf("probability next state[%d] %f\n",j,delta_old[j]);
#endif
   }
#ifdef DEBUG
   printf("add %f\n",add);
#endif


   //next_state_region=calculate_region(delta_old,hmm.num_states);

#ifdef DEBUG
   //printf(" Viterbi best state %d\n",next_state);
   //printf(" Viterbi prob. region state %d\n",next_state_region);
#endif

   //return(next_state_region);
   return(next_state);

}


/* Function that calculates the HMM output from the C matrix */
int calculate_hmm_output(struct hmm_database hmm, int state, int obs)
{

 int i,j;
 float rand;
 float tmp,threshold=0.0001;
 int index;

 index= state;

 #ifdef DEBUG
 printf("Present state %d obs %d\n",state,obs);
 #endif


 // it generates a Uniform random variable between 0 and 1
 rand=generaR(0.0,1.0);
#ifdef DEBUG
 printf("output random %f \n",rand);
#endif


 tmp=hmm.cis[index][1];

#ifdef DEBUG
 printf("sum output 1 %f\n",tmp);
#endif

 for(j=1;j<=hmm.num_out_symbols;j++){
        if(rand <= tmp){
                i=j;
                j=hmm.num_out_symbols+1;
        } else{
                tmp= tmp + hmm.cis[index][j+1];
#ifdef DEBUG
                printf("sum output  %d sum %f\n",j+1,tmp);
#endif

                i=j;
        }
   }

#ifdef DEBUG
   printf("tmp %f random %f\n",tmp,rand);
#endif

/*
   if(tmp < threshold){
                rand=generaR(0.0,5.0);
                i=(int) rand; //it generates a random output 
#ifdef DEBUG
                printf("i %d\n",i);
#endif
   }
   else i--;
   //printf(" stochastic output symbol %d %s tmp %f\n",i,outputs[i],tmp);
*/

 return i;

}



// Engine that executes probabilistic state machines 
void exe_probabilistic_state_machine(Inputs_pr inputs, Obs_data obs_data, int step, int *present_state, int *output){

 static int states[NUM_STATES];
 static int previous_state=1;
 //Behavior output;
 int out_symbol;
 static int flg_read=1;
 static struct hmm_database hmm;
 static int num_states,num_inputs,num_outputs;
 static int Time=1;
 int quantized_value;
 int next_st;


#ifdef DEBUG
 printf("\n\n *********************State Machine HMM %d **********\n",step);
#endif

 quantized_value=obs_data.obs[step];

#ifdef DEBUG
 printf("Time %d observation %d\n",step,quantized_value);
#endif


 if(flg_read==1){

        // It reads the number of states, num. obs. symbols and nun. out symbols of the hmm 
        strcpy(hmm.objects_file,inputs.pr_file);
#ifdef DEBUG
        printf("HMM file %s\n", hmm.objects_file);
 	printf("Probabilistic state machine %s\n",inputs.pr_file);
#endif

        read_hmms(&hmm,0,inputs.path);

        //It creates the HMM structure
        hmm_initialize(&hmm);

        // It reads the complete hmm 
        read_hmms(&hmm,1,inputs.path);
        num_states=hmm.num_states;
        num_inputs=hmm.num_obs_symbols;
        num_outputs=hmm.num_out_symbols;

	#ifdef DEBUG
 	printf("\n\n *********************State Machine HMM %d **********\n",step);
	#endif

        // Initializes the random generator
        srandom((int)time((time_t *)NULL));
	Time=1;
	states[Time]=0;
        //states[Time]=calculate_hmm_first_state(hmm,quantized_value);
 	next_st=get_next_state_hmm_viterbi(quantized_value,flg_read, hmm,states[Time]);
	states[Time]=next_st;
	#ifdef DEBUG
        	printf("First  State %d \n",next_st);
	#endif

        flg_read=0;

 }

 *present_state=states[Time];

 // It calculates the output state
 *output=calculate_hmm_output(hmm,states[Time],quantized_value);

 #ifdef DEBUG
        printf("HMM present State[%d] %d output %d\n",Time, states[Time],*output);
 #endif

 // it calculates the next state
 next_st=get_next_state_hmm_viterbi(quantized_value,flg_read,hmm,states[Time]);

 Time++;
 states[Time]=next_st;

 #ifdef DEBUG
       printf("Viterbi next  State %d \n",next_st);
 #endif


}




// Main program
int main(int argc, char *argv[])
{

 Inputs_pr inputs;
 int num_steps;
 Obs_data obs;
 int j;
 int present_state;
 int states[NUM_STATES];
 int outputs[NUM_STATES];
 int cnt_states=0;
 int cnt_outputs=0;
 int output;
 FILE *fp2;
 char output_file[500];
 int num_corr=NUM_MAX_CORR;
 float r[NUM_MAX_CORR+1];
 float r_out[NUM_MAX_CORR+1];
 int i;
 float corr_total;
 float corr_out_total;
 float dif;


 // it gets line inputs 
 get_inputs_probabilistic(argc,argv,&inputs);


 // It reads the observation file
 read_obs(&obs,inputs.path, inputs.obs_file);

 for(j=1;j<=obs.num+num_corr+1;j++){
	states[j]=0;
	outputs[j]=0;
 }



 for(j=1;j<=obs.num;j++){

 	//it executes the probabilistic state machine
 	exe_probabilistic_state_machine(inputs,obs,j,&present_state,&output);
 	states[j]=present_state; 
	outputs[j]=output;

 }

 cnt_states=0;
 cnt_outputs=0;
 corr_total=0;
 corr_out_total=0;

 //Correlations 
 for(i=0;i<=num_corr;i++){

	r[i]=0;
	r_out[i]=0;

	for(j=1;j<=obs.num+1;j++){
		dif = states[j]-obs.states[j+i];
		r[i]= r[i] + dif*dif;
		dif = outputs[j]-obs.outputs[j+i];
		r_out[i]= r_out[i] + dif*dif;
	}
	
#ifdef DEBUG
	printf("r[%d] %f r_out[%d] %f\n",i,r[i],i,r_out[i]);
#endif
	r[i] = r[i]/(i + 1);
	r_out[i] = r_out[i]/(i + 1);
	corr_total = corr_total + r[i];
	corr_out_total = corr_out_total + r_out[i];
#ifdef DEBUG
	printf("scaled r[%d] %f r_out[%d] %f\n",i,r[i],i,r_out[i]);
#endif


 }



 for(j=1;j<=obs.num;j++){

	printf("%d state %d ",j,obs.states[j]);
	printf("output %d ",obs.outputs[j]);
	printf("input %d ",obs.obs[j]);
	printf("clt. state %d ",states[j]);
	printf("output %d\n",outputs[j]);
	if(obs.states[j] != states[j])cnt_states++;
	if(obs.outputs[j] != outputs[j])cnt_outputs++;

 }
 


 /* It opens the evaluation file */
 //sprintf(output_file,"%s%s.dat",inputs.path,inputs.output_file);
 sprintf(output_file,"%s%s.dat",inputs.path,inputs.output_file);
 fp2=fopen(output_file,"w");
 if(fp2==0){
        printf("\n File %s can not be created\n",output_file);
        exit(0);
 }

 //printf("corr_total %f corr_out_total %f\n",corr_total,corr_out_total);
 printf("Num. difference state %d\n",cnt_states);
 printf("Num. difference outputs %d\n",cnt_outputs);
 printf("\nOutput evaluation FILE: %s\n",output_file);
 corr_total= 1 / (cnt_states + 0.1);
 corr_out_total= 1 / (cnt_outputs + 0.1);
 //corr_total= corr_total / (cnt_states + 0.1);
 //corr_out_total= corr_out_total / (cnt_outputs + 0.1);
 printf("fitness_1 %f fitness_2 %f\n",corr_total,corr_out_total);
 //printf("corr_out_total %f corr_out_total %f\n",corr_out_total,corr_out_total);
 //fprintf(fp2,"%f %f\n",corr_total,corr_out_total);
 fprintf(fp2,"%f %f\n",corr_total,corr_out_total);
#ifdef DEBUG
 for(i=0;i<=num_corr;i++){
	printf("r[%d] %f r_out[%d] %f\n",i,r[i],i,r_out[i]);
 	//fprintf(fp2,"%f %f\n",r[i],r_out[i]);
 }
#endif

 //fprintf(fp2,"%d %d\n",cnt_states,cnt_outputs);
 fclose(fp2);


}



