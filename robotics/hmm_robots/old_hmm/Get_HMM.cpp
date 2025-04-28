/********************************************************
*	Get_HMM.cpp					*
*							*
*	Compilation: make -f Makefile_Get_HHM 		*
*							*
*			Jesus Savage			*
*		University of Mexico U.N.A.M.		*
*							*
*				3/17/2016		*
*				3/17/2016		*
*********************************************************
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "../utilities/constants.h"
#include "../utilities/structures.h"
#include "../simulator/simulation.h"
#include "../utilities/utilities.h"
#include "../utilities/inputs.h"
#include "../state_machines/state_machine_avoidance.h"
#include "../state_machines/state_machine_destination.h"
#include "../state_machines/state_machine_avoidance_destination.h"
#include "../utilities/random.h"
#include "hmm_lib.h"
#include "viterbi.h"


#define ERROR .000001
#define THRESHOLD_MOV 0.004
#define THRESHOLD_ROT 0.03927
#define NUM_MAX_OBS 710
#define MAX_SIZE_TRAINING 1000

float K_INTENSITY;


/* it gets line inputs */
void get_inputs(int argc, char **argv, char *path, char *training_files, int *num_train, char *model_name)
{

 int i;


 strcpy(path,"../data/");
 strcpy(training_files,"training_random");
 *num_train = 10;
 strcpy(model_name,"avoid");


  /* reads input parameters */
  if (argc>1) {
        for(i=1;i<argc;i++){

          if (!strcmp(argv[i],"-h")){

  		printf("\nUsage:\n	Get_HMM -p path -f training_files -n number_of_training_files -m model_name\n\n");
  		printf("Example:\n	Get_HMM -p ../data/ -f training_random -n 10 -m avoid\n\n");
                exit(1);

          }
          else if (!strcmp(argv[i],"-p")){
                strcpy(path,argv[i+1]);
          }
          else if (!strcmp(argv[i],"-f")){
                strcpy(training_files,argv[i+1]);
          }
	  else if (!strcmp(argv[i],"-n")){
                *num_train=atoi(argv[i+1]);
	  }
          else if (!strcmp(argv[i],"-m")){
                strcpy(model_name,argv[i+1]);
          }

        }
  }
  else{
 	printf("\n Using default values");
  }
  
  printf("\nGet_HMM -p %s -f %s -n %d -m %s\n\n",path,training_files,*num_train,model_name);


 return;

}

/*

// It updates the hmm probabilities using the Viterbi algorithm
int update_hmm_viterbi(char *object,int num_images,int *num_vectors,int **obs, int num_states, char *path, int num_symbols)
{
 char output_file[250];
 int i,j,k,l,t;
 float tmp,lim,average;
 FILE *fp2,*fp1;
 int num_obs[NUM_STATES+1][NUM_MAX_CENTROIDS+1];
 int num_nds,ret_nodes[256];
 int num_states_obs[NUM_STATES+1];
 int state_obs[NUM_STATES+1][NUM_STATES+1];
 int t1;
 int inc,init,end;
 float **a,*pis,**b;
 double vit_prob[1024];
 int *q[256];
 int *vect,**vectk;
 int state[NUM_STATES+1][NUM_STATES+1];
 double p;




  // It allocates the matrices used for the hmm evaluation

  if((a =(float **)alloc_matrix(num_states+1, num_states+1 )) == 0){
         printf("\n Memory allocation error ");
         exit(1);
  }

  if((b =(float **)alloc_matrix(num_states+1,num_symbols+1)) == 0){
         printf("\n Memory allocation error ");
         exit(1);
  }

  if((pis =(float *)alloc_vector(num_states+1)) == 0){
         printf("\n Memory allocation error ");
         exit(1);
  }

  if((vect =(int *)alloc_vector_int(num_states+1)) == 0){
         printf("\n Memory allocation error ");
         exit(1);
  }

  if((vectk=(int **)alloc_matrix_int(num_states+1,num_symbols+1))==0){
         printf("\n Memory allocation error ");
         exit(1);
  }



 // it allocates the states vectors
 for(i=1;i<num_images;i++)
 if((q[i] = (int *) alloc_vector_int((num_vectors[i]+1))) == 0){
                printf("\n Memory allocation error: seq_states %d %d",i,num_vectors[i]);
                exit(0);
 }


 // it initializes some variables
 for(i=1;i<=num_states;i++){
        vect[i]=0;
        for(j=1;j<=num_states;j++){
                state[i][j]=0;
        }
        for(j=1;j<=num_symbols;j++){
                        vectk[i][j]=0;
        }

 }



 //It reads the HMM model 
 read_hmm_ais_bis_pis(object,a,pis,b,num_states,num_symbols,path);

 p=0;
 for(i=1;i<num_images;i++){

        // It calculates the best sequence of states using the Viterbi algorithm
        //  and the probability of a hmm given a symbol vector 
        vit_prob[i]=viterbi(obs[i],a,b,pis,num_vectors[i],num_states,q[i]);
        vit_prob[i]=exp(vit_prob[i]/100.);
        //printf("Viterbi probability %d %e\n",i,vit_prob[i]);
	p=p+vit_prob[i];

 	for(t=1;t<num_vectors[i];t++){
                state[q[i][t]][q[i][t+1]]++;
                vect[q[i][t]]++;
                vectk[q[i][t]][obs[i][t]]++;
                //printf("state[%d][%d] %d obs[%d][%d] %d\n",q[i][t],q[i][t+1],state[q[i][t]][q[i][t+1]],i,t,obs[i][t]);
        }
 }

 
 printf("total Viterbi probability %e\n",p/(num_images-1));

 // It updates the ais and bis /
 for(i=1;i<=num_states;i++){
                for(j=1;j<=num_states;j++){
                        if(vect[i] != 0)
                        a[i][j]=(float)(state[i][j]/(float)vect[i]);
                        else a[i][j]=0.;
                        //printf("a[%d][%d] %f\n",i,j,a[i][j]);
                }
                for(j=1;j<=num_symbols;j++){
                        if(vect[i] != 0)
                        	b[i][j]=(float)(vectk[i][j]/(float)vect[i]);
                        else 	b[i][j]=0.;
                	//printf("\n b[%d][%d] %f",i,j,b[i][j]);
                }
 }






 // It checks for probabilities values less than NULL_PROB and fixed it
 for(k=1;k<=num_states;k++){

        lim=0;
        for(l=1;l<=num_states;l++){
              if(a[k][l]<NULL_PROB){
                  a[k][l]=NULL_PROB;
                  lim=lim+1;
		  //printf("%d %d lim %f\n",k,l,lim);
	          //printf("a[%d][%d] %f\n",k,l,a[k][l]);
              }
        }
        // it fixes the probabilities in order that the total probability is 1 
        if(lim != 0){
          if(lim == num_states){
                printf("\n Please retrain the object several times \n");
                exit(0);
          }


          for(l=1;l<= num_states;l++)
            if((a[k][l]!=NULL_PROB)&&(a[k][l]>(lim*NULL_PROB)/(num_states-lim)))
                a[k][l]=a[k][l]-(lim*NULL_PROB)/(float)(num_states-lim);

        }

   }



 for(k=1;k<=num_states;k++){
        lim=0;
        for(l=1;l<=num_symbols;l++){
               if(b[k][l]<=NULL_PROB){
                  b[k][l]=(float) NULL_PROB;
                  lim++;
                }
        }

        //it fixes the probabilities in order that the total probability is 1
        if(lim != 0){
          for(l=1;l<= num_symbols;l++)
            if((b[k][l] > NULL_PROB)
              &(b[k][l] > ((lim*NULL_PROB)/(float)(num_symbols-lim)) )){

               b[k][l]=b[k][l]-(lim*(float)NULL_PROB)/(float)(num_symbols-lim);

            }

        }
 }



 // It saves the transition and initial probabilities 
 sprintf(output_file,"%s%s_%d_%d.prb",path,object,num_states,num_symbols);
 fp2=fopen(output_file,"w");
 if(fp2==0){
             printf("\n Can not open %s ",output_file);
             return(0);
 }



 for(j=1;j<=num_states;j++)fprintf(fp2,"%f ",pis[j]);
 fprintf(fp2,"\n");
 average=0;
 for(j=1;j<=num_states;j++){
        //printf(" pi[%d] %f\n",j,pis[j]);
        average+=pis[j];
 }
 //printf("sum pis %f\n",average);

 for(j=1;j<=num_states;j++){
        average=0;
        for(k=1;k<=num_states;k++){
                fprintf(fp2,"%f ",a[j][k]);
                //printf("\n a[%d][%d] %f",j,k,a[j][k]);

                average+=a[j][k];
        }
        fprintf(fp2,"\n");
        //printf("\nsum ais[%d] %f\n",j,average);
 }
 //printf("\n");

 for(j=1;j<=num_states;j++){
                average=0;
                for(k=1;k<=num_symbols;k++){
                     //printf("b[%d][%d] %f\n",j,k,b[j][k]);
                     average+=b[j][k];
                     fprintf(fp2,"%f ",b[j][k]);
                }
                //printf("\n");
                //printf("sum bis[%d] %f\n",j,average);
                fprintf(fp2,"\n");
 }

 fclose(fp2);

 //printf("NEW HMM FILE: %s\n",output_file);

}


*/

int read_raw_file(char *data_file, int *obs, int *actions){

 FILE *fp;
 char string[300];
 int flg=1;
 float xd,yd,angle,distance;
 int num_sensors;
 float range;
 float initial;
 float sensor;
 int i;
 int num_vectors=0;
 char name[30];
 float x,y,angle_robot;
 coord coord_robot;
 coord coord_dest;
 int quantized_obs;
 int quantized_attraction;
 int quantized_intensity;
 Raw values;
 int ob;
 char outputs[10][15] = { "STOP","FORWARD","BACKWARD","LEFT","RIGHT"};

 /* It opens the raw file */
 fp=fopen(data_file,"r");
 if(fp==0){
        printf("\n File %s does not exists",data_file);
        exit(0);
 }

 while(flg){

	if(fscanf(fp,"%s",string) != EOF){
		
		//printf("%s",string);
	
		if(strcmp(string,"destination") == 0){
			fscanf(fp,"%f%f",&xd,&yd);
			//printf("Destination %f %f\n",xd,yd);
			coord_dest.xc=xd;
			coord_dest.yc=yd;
		}

		else if(strcmp(string,"robot") == 0){
                        fscanf(fp,"%s%f%f%f",name,&x,&y,&angle_robot);
                        //printf("Robot %s %f %f %f\n",name,x,y,angle_robot);    
			coord_robot.xc=x;
 			coord_robot.yc=y;
 			coord_robot.anglec=angle_robot;

                }
		
		else if(strcmp(string,"sensor") == 0){
		    fscanf(fp,"%s",string);
		    if(strcmp(string,"laser") == 0){
			fscanf(fp,"%d%f%f",&num_sensors,&range,&initial);
			for(i=0;i<num_sensors;i++){
                        	fscanf(fp,"%f",&sensor);
				values.sensors[i]=sensor;
			//	printf("sensor[%d] %f\n",i,values.sensors[i]);
			}
		    }
		    else if(strcmp(string,"light") == 0){
			fscanf(fp,"%d",&quantized_intensity);
        		//printf("quantized intensity %d \n",quantized_intensity);
		    }
	    	    else if(strcmp(string,"destination") == 0){
			fscanf(fp,"%d",&quantized_attraction);
        		//printf("quantized attraction %d \n",quantized_attraction);
                    }

		}

		else if(strcmp(string,"movement") == 0){
                        fscanf(fp,"%f%f",&angle,&distance);
                        //printf("Movement %f %f\n",angle,distance);    

			num_vectors++;

			//if( (distance == 0) && (angle == 0) )actions[num_vectors]=0; // stop
			if( (distance > 0) && (distance < THRESHOLD_MOV) &&
				 (angle > 0) && (angle < THRESHOLD_ROT) )actions[num_vectors]=0; // stop
			else if(distance > THRESHOLD_MOV) actions[num_vectors]=1; // forward 
			//else if((distance < 0) && (distance < -THRESHOLD_MOV)) actions[num_vectors]=2; // backward
			else if(distance < -THRESHOLD_MOV) actions[num_vectors]=2; // backward
			else if(angle > THRESHOLD_ROT) actions[num_vectors]=3; // turn left
                        else if(angle < -THRESHOLD_ROT) actions[num_vectors]=4; // turn backward

			//printf("%d action symbol %s\n",num_vectors,outputs[actions[num_vectors]]);

	

			quantized_obs=quantize_inputs(values,num_sensors);
			//printf("quantized inputs %d \n",quantized_obs);		

			//quantized_values[num_vectors] = (quantized_intensity << 4) + (quantized_obs << 2) + quantized_attraction;
			ob = (quantized_intensity << 4) + (quantized_obs << 2) + quantized_attraction;
			obs[num_vectors] = ob +1; // it is added 1 to avoid addressing symbol 0
			//printf("obs[%d] %d \n",num_vectors,obs[num_vectors]);		
			//printf("actions[%d] %d\n",num_vectors,actions[num_vectors]);		

                }


	}
	else flg=0;


 }

 fclose(fp);

 return(num_vectors);

}




 // it reads the observations
void get_observations(char *path, char *training_files, int num, int **observations, int **actions, int *num_total_vectors){

 int i,j;
 char data_file[300];
 int num_vectors;


/* it gets the number of vectors and their size*/
 for(i=1;i<=num;i++){

	sprintf(data_file,"%s%s_%d.raw",path,training_files,i);
        num_vectors=read_raw_file(data_file,observations[i],actions[i]);
        //printf("%s num. vectors %d \n",data_file,num_vectors);
        num_total_vectors[i]=num_vectors;

	/*
	for(j=1;j <= num_total_vectors[i];j++){
		printf("observations[%d][%d] %d ",i,j,observations[i][j]);                
                printf("actions[%d][%d] %d\n",i,j,actions[i][j]);
	}
	*/

 }

}




// It retrains the HMM 
void retrain_hmm(char *initial_hmm_file, char *path, char *training_files, int num_train){

 int flg_inputs=1;
 struct hmm_database hmm;
 int num_states,num_inputs,num_outputs;
 int *observations[MAX_SIZE_TRAINING];
 int *actions[MAX_SIZE_TRAINING];
 int *num_total_vectors;
 int i,j,k;


 // It allocates memory space
 if(num_train >= MAX_SIZE_TRAINING){
	printf("Increase the size of variable observations in function retrain_hmm > %d \n",num_train);
	exit(0);
 }


 for(k=1;k<=num_train+1;k++){
 	if((observations[k] = (int *) alloc_vector_int(NUM_MAX_OBS) ) == 0){
         	printf("\n Memory allocation error: observations ");
         	exit(0);
 	}

 	if((actions[k] = (int *) alloc_vector_int(NUM_MAX_OBS) ) == 0){
         	printf("\n Memory allocation error: actions ");
         	exit(0);
 	}
 }

 if((num_total_vectors = (int *) alloc_vector_int(NUM_MAX_OBS) ) == 0){
         	printf("\n Memory allocation error: num_total_vectors ");
         	exit(0);
 }


 // Initializes the random generator
 srandom((int)time((time_t *)NULL));

 /* It reads the number of states, num. obs. symbols and nun. out symbols of the hmm */
 strcpy(hmm.objects_file,initial_hmm_file);
 printf("HMM file %s\n", hmm.objects_file);
 read_hmms(&hmm,0,path,flg_inputs);

 //It creates the HMM structure
 hmm_initialize(&hmm);

 /* It reads the complete hmm */
 read_hmms(&hmm,1,path,flg_inputs);
 num_states=hmm.num_states;
 num_inputs=hmm.num_obs_symbols;
 num_outputs=hmm.num_out_symbols;

 // it reads the observations
 get_observations(path,training_files,num_train,observations,actions,num_total_vectors);

/*
 for(i=1;i<=num_train;i++){
         for(j=1;j <= num_total_vectors[i];j++){
                printf("observations[%d][%d] %d ",i,j,observations[i][j]);
                printf("actions[%d][%d] %d\n",i,j,actions[i][j]);
        }
 }
*/



 update_HMM_Viterbi(path,observations,actions,num_total_vectors,num_train,&hmm);

 for(k=1;k<=num_train+1;k++){
 	free_vector_int(observations[k]);
 	free_vector_int(actions[k]);
 }
 free_vector_int(num_total_vectors);

}



main(int argc,char *argv[])
{

 int num_train;
 char path[300];
 char training_files[300];
 char model_name[128];
 char initial_hmm_file[300];


 // it gets line inputs 
 get_inputs(argc,argv,path,training_files,&num_train,model_name);

 // it retrains the HMM model 
 retrain_hmm(model_name,path,training_files,num_train);


}



