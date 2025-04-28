/********************************************************
 *                                                      *
 *                                                      *
 *      state_machine_nn.h                              *
 *                                                      *
 *		Jesus Savage				*
 *		FI-UNAM					*
 *		5-5-2016                                *
 *		10-23-2023                              *
 *                                                      *
 ********************************************************/

#include "neural_networks_lib.h"
#define THRESHOLD_OUT 0.5


int calculate_nn_stochastic_output(neural_net nn, int n_o, int n_l)

{
 int i,j;
 float rand;
 float tmp,threshold=0.0001;
 float sum_prb= 0.0;
 float sum= 0.0;
 float x[256];


 // normalization
 for(i=1; i <= n_o; i++){
	/*if(nn.x[n_l][i] < 0.0) x[i] = 0.0;
	else if (nn.x[n_l][i] > 1.0) x[i] = 1.0;
	else x[i] = nn.x[n_l][i];*/
	x[i] = nn.x[n_l][i]+1.0;
	sum= sum + x[i];
#ifdef DEBUG
	printf("outputs nn.x[%d][%d] %f x[%d] %f \n",n_l,i,nn.x[n_l][i],i,x[i]);
#endif
 }


 for(i=1; i <= n_o; i++){
	x[i]= x[i]/sum;
	sum_prb= sum_prb + x[i];
#ifdef DEBUG
	printf("normalized outputs x[%d] %f\n",i,x[i]);
#endif
 }
#ifdef DEBUG
 printf(" sum. prb  %f\n\n",sum_prb);
#endif


 // it generates a Uniform random variable between 0 and 1
 rand=generaR(0.0,1.0);
#ifdef DEBUG
 printf("random %f\n",rand);
#endif


 tmp=x[1];
#ifdef DEBUG
 printf("ranges 1 sum %f\n",tmp);
#endif

 for(j=1;j<=n_o;j++){
        if(rand <= tmp){
                i=j;
		break;
        } else{
                tmp= tmp + x[j+1];
#ifdef DEBUG
                printf("ranges j %d sum %f\n",j+1,tmp);
#endif
                i=j;
        }
   }

   i--;
#ifdef DEBUG
   printf(" stochastic nn output symbol %d\n",i);
#endif
   return i;

}



// it converts a nn output to a robot's output
AdvanceAngle nn_symbol_output_old(neural_net nn, float advance, float angle, int pr_out){

 AdvanceAngle output;
 int n_o,n_l,i,j=1;
 int out;
 int power2;


 n_o=nn.num_outputs;
 n_l=nn.num_layers;
 power2=1;
 
 out=0;
 for(i=1;i<=n_o;i++){
        printf("outputs nn.x[%d][%d] %f\n",n_l,i,nn.x[n_l][i]);
        if(nn.x[n_l][i] > THRESHOLD_OUT){
		out = out + power2;
        }
	power2 = power2 *2;
 }

 printf("out binary %d\n",out);

 output=generate_output(out,advance,angle);


  return(output);

}



// it converts a nn output to a robot's output
AdvanceAngle nn_symbol_output(neural_net nn, float advance, float angle, int pr_out){

 AdvanceAngle output;
 int n_o,n_l,i,j=1;
 float biggest;
 int out;

 
 n_o=nn.num_outputs;
 n_l=nn.num_layers; 

 if(pr_out == 0){
 
	biggest = nn.x[n_l][1];
 
#ifdef DEBUG
	printf("outputs nn.x[%d][1] %f\n",n_l, nn.x[n_l][1]);
#endif

 
	for(i=2;i<=n_o;i++){
 	
#ifdef DEBUG
		printf("outputs nn.x[%d][%d] %f\n",n_l,i,nn.x[n_l][i]);
#endif
	
		if(nn.x[n_l][i] > biggest){
			biggest = nn.x[n_l][i];
			j = i;
		}
 	}

#ifdef DEBUG
 	printf("biggest %f index %d\n",biggest,j);
#endif
 	out = j-1;
#ifdef DEBUG
 	printf("index out %d\n",out);
#endif

 }
 else{
	// Stochastic output 
	out=calculate_nn_stochastic_output(nn,n_o,n_l);
 }

 output=generate_output(out,advance,angle);


  return(output);

}
                             



// Engine that executes recurrent neural networks state machines using the unquantized input data
AdvanceAngle state_machine_destination_nn(float dest,float intensity, Raw observations, float Mag_Advance,
			float max_angle, char *path, int flg_noise, int size_vq, int num_bits_vq, int num_sensors, int pr_out, int nn_rec){


 AdvanceAngle gen_vector;
 static int previous_state=1;
 static int flg_old=1;
 AdvanceAngle output;
 int out_symbol;
 static int flg_read=1;
 static neural_net nn;
 static int Time;
 int i,j,k;
 char individual[100];
 int shift;



 if(nn_rec == 0)
	if(pr_out == 0)
 		strcpy(individual,"nn");
	else
 		strcpy(individual,"nn_st");
 else
	if(pr_out == 0)
 		strcpy(individual,"rnn");
	else
 		strcpy(individual,"rnn_st");
		


 if(flg_read==1){


        /* It reads the nn's basic information */
	strcpy(nn.file,individual);
        printf("NN file %s\n", nn.file);
        read_nn(&nn,0,path);

	//It creates the NN structure
        nn_initialize(&nn);

        // It reads the complete NN 
        read_nn(&nn,1,path);
	print_values_nn(nn,0); // it prints the weights
	print_values_nn(nn,1); // it prints the xs values

	flg_read=0;

	// Initializes the random generator
        srandom((int)time((time_t *)NULL));
	Time=1;

 }

 printf("angle destination %f light intensity %f\n",dest,intensity);

 nn.x[0][1]=dest;
 nn.x[0][2]=intensity;
 
 printf("nn.x[0][1] %f \nnn.x[0][2] %f\n",nn.x[0][1],nn.x[0][2]);


 for(i=3,j=0; j < num_sensors; i++,j++){
 	nn.x[0][i]= observations.sensors[j];
	printf("nn.x[0][%d] %f\n",i,nn.x[0][i]); 
 }




 for(k=nn.num_inputs+1,i=nn.num_recurrent;k <= nn.num_inputs+nn.num_recurrent;k++,i--){
         printf("%d present state[%d] %f\n",Time,i,nn.x[0][k]);
 }



 for(k=nn.num_inputs+1,i=nn.num_recurrent;k <= nn.num_inputs+nn.num_recurrent;k++,i--){
	 if(nn.x[0][k] > 0.5) printf("%d binary present state[%d] 1\n", Time,i);
	 else printf("%d binary present state[%d] 0\n", Time,i);
 }



 // Evaluates de NN to find the output and next state 
 print_values_nn(nn,1);
 evaluate(&nn);
 print_values_nn(nn,1);

 // it calculates the output
 gen_vector=nn_symbol_output(nn,Mag_Advance,max_angle, pr_out);
 printf("Outputs gen_vector.distance  %f gen_vector.angle %f\n",gen_vector.distance,gen_vector.angle);

 for(k=nn.num_outputs+1,i=nn.num_recurrent;k <= nn.num_outputs+nn.num_recurrent;k++,i--){
         printf("%d next_state[%d] %f\n",Time,i,nn.x[nn.num_layers][k]);
 }

 Time++;

 return gen_vector;

}



// Engine that executes recurrent neural networks state machines using the quantized input data
AdvanceAngle state_machine_destination_nn_vq(int dest,int intensity, int obstacles, float Mag_Advance,
			float max_angle, char *path, int flg_noise, int size_vq, int num_bits_vq, int pr_out, int nn_rec){

 AdvanceAngle gen_vector;
 static int previous_state=1;
 static int flg_old=1;
 AdvanceAngle output;
 int out_symbol;
 static int flg_read=1;
 static neural_net nn;
 static int Time;
 int i,j,k;
 char individual[100];
 int shift;


 if(nn_rec == 0)
	if(pr_out == 0)
 		strcpy(individual,"nn");
	else
 		strcpy(individual,"nn_st");
 else
	if(pr_out == 0)
 		strcpy(individual,"rnn");
	else
 		strcpy(individual,"rnn_st");
		

 if(flg_read==1){


        /* It reads the nn's basic information */
	strcpy(nn.file,individual);
#ifdef DEBUG
        printf("NN file %s\n", nn.file);
#endif
        read_nn(&nn,0,path);

	//It creates the NN structure
        nn_initialize(&nn);

        // It reads the complete NN 
        read_nn(&nn,1,path);
#ifdef DEBUG
	print_values_nn(nn,0); // it prints the weights
	print_values_nn(nn,1); // it prints the xs values
#endif

	flg_read=0;

	// Initializes the random generator
        srandom((int)time((time_t *)NULL));
	Time=1;

 }

 //printf("angle destination %d light intensity %d obstacles %d\n",dest,intensity,obstacles);
 //printf("Size vq %d\n",size_vq);


/* 
 shift = dest;
 j=1;
 for(i=1; i < NUM_BITS_DEST_ANGLE +1 ; i++){
 	//nn.x[0][i]= float(shift & 1);
 	if (float(shift & 1)== 1) nn.x[0][i] = 0.90;
	else nn.x[0][i]= 0.1;
	shift = shift >> 1;
#ifdef DEBUG
	printf("nn.x[0][%d] %f\n",i,nn.x[0][i]); 
#endif
 }

 j=i;
 shift = intensity;
 for(i=j; i < NUM_BITS_INTENSITY + j ; i++){
        //nn.x[0][i]= float(shift & 1);
	if (float(shift & 1)== 1) nn.x[0][i] = 0.90;
        else nn.x[0][i]= 0.1;
        shift = shift >> 1;
#ifdef DEBUG
        printf("nn.x[0][%d] %f\n",i,nn.x[0][i]);
#endif
 }


 j=i;
*/

 j=1;
 shift = obstacles;
 for(i=j; i < num_bits_vq + j; i++){
 	//nn.x[0][i]= float(shift & 1);
	if (float(shift & 1)== 1) nn.x[0][i] = 0.90;
        else nn.x[0][i]= 0.1;
	shift = shift >> 1;
#ifdef DEBUG
	printf("nn.x[0][%d] %f\n",i,nn.x[0][i]); 
#endif
 }


#ifdef DEBUG
 for(k=nn.num_inputs+1,i=nn.num_recurrent;k <= nn.num_inputs+nn.num_recurrent;k++,i--){
         printf("%d present state[%d] %f\n",Time,i,nn.x[0][k]);
 }
 for(k=nn.num_inputs+1,i=nn.num_recurrent;k <= nn.num_inputs+nn.num_recurrent;k++,i--){
	 if(nn.x[0][k] > 0.5) printf("%d binary present state[%d] 1\n", Time,i);
	 else printf("%d binary present state[%d] 0\n", Time,i);
 }
#endif



 // Evaluates de NN to find the output and next state 
#ifdef DEBUG
 print_values_nn(nn,1);
#endif
 evaluate(&nn);
#ifdef DEBUG
 print_values_nn(nn,1);
#endif

 // it calculates the output
 gen_vector=nn_symbol_output(nn,Mag_Advance,max_angle, pr_out);

#ifdef DEBUG
 printf("Outputs gen_vector.distance  %f gen_vector.angle %f\n",gen_vector.distance,gen_vector.angle);
 for(k=nn.num_outputs+1,i=nn.num_recurrent;k <= nn.num_outputs+nn.num_recurrent;k++,i--){
         printf("%d next_state[%d] %f\n",Time,i,nn.x[nn.num_layers][k]);
 }
#endif

 Time++;

 return gen_vector;

}



