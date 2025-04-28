/********************************************************
*							*
*  viterbi.h						*
*							*
*			J. Savage			*
*							*
*			FI-UNAM				*
*			Jun-2016			*
*							*
*********************************************************/


#define EPSILON 0.0000001
#define NUM_ITER 300
#define HIGH_NUM_VECTORS 512


// It updates the hmm probabilities using the Viterbi algorithm

void  update_HMM_Viterbi(char *path,int **observations, int **actions, int *num_total_vectors, int num_train, hmm_database *hmm){

 int i,j,k=0;
 double probability,total_probability=0.0,previous_probability=0.0;
 int flag=1;
 int *q[HIGH_NUM_VECTORS];
 int num_states;
 int num_symbols;
 int num_outputs;


 num_states=hmm->num_states;
 num_symbols=hmm->num_obs_symbols;
 num_outputs=hmm->num_out_symbols;


 // it allocates memory for the states
 for(i=1;i<=num_train+1;i++)
        if((q[i] = (int *) alloc_vector_int((num_total_vectors[i]+1))) == 0){
                printf("\n Memory allocation error: seq_states %d %d",i,num_total_vectors[i]);
                exit(0);
        }


 while(flag){

    printf("\n****************************************************************\n");
    for(i=1;i<=num_states;i++){
    	for(j=1;j<=num_states;j++){
                        printf("a[%d][%d] %f\n",i,j,hmm->ais[i][j]);
    	}
    	for(j=1;j<=num_symbols;j++){
                        printf("b[%d][%d] %f\n",i,j,hmm->bis[i][j]);
   	}
     }




    for(i=1;i<=num_train;i++){

	probability=viterbi(observations[i],hmm->ais,hmm->bis,hmm->pis,num_total_vectors[i], 
									hmm->num_states, hmm->seq_states);
	total_probability = probability + total_probability;

	printf("%d.- Probabilty %e\n",i,probability);

	if(num_total_vectors[i] > HIGH_NUM_VECTORS){
		printf("Change constant HIGH_NUM_VECTORS to a a value higher than %d\n",num_total_vectors[i]);
		exit(1);
	}
	else	
           for(j=1;j <= num_total_vectors[i];j++){
                //printf("observations[%d][%d] %d ",i,j,observations[i][j]);
                //printf("actions[%d][%d] %d ",i,j,actions[i][j]);
		q[i][j]=hmm->seq_states[j];
                //printf(" state %d \n",q[i][j]);
           }

    }

    printf("Iteration %d previous probabilty %e ",k,previous_probability);
    printf("probabilty population %e\n",total_probability);
    printf("diference %f\n",fabs(total_probability - previous_probability));
    if(fabs(total_probability - previous_probability) < EPSILON){
	flag=0;
    }
    else{ 

   		get_statistics_HMM(num_train,num_total_vectors,observations,hmm,q,actions);

		previous_probability = total_probability;
		total_probability = 0;
		k++;
		if(k > NUM_ITER)flag=0;
    }

 }


 fprint_hmm(path,hmm);

 //for(k=1;k<=num_train+1;k++){
        //free_vector_int(q[k]);
 //}


}



