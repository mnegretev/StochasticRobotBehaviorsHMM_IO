/********************************************************
 *                                                      *
 *                                                      *
 *      state_machine_nn.h                             *
 *                                                      *
 *		Jesus Savage				*
 *		FI-UNAM					*
 *		5-5-2016                                *
 *                                                      *
 ********************************************************/

#define THRESHOLD 0.5


// it converts a binary output to a robot's output
Behavior nn_symbol_output(neural_net nn, float advance, float angle){

 Behavior output;
 int n_o,n_l,i,j=1;
 float biggest;
 int out;

 
 n_o=nn.num_outputs;
 n_l=nn.num_layers; 
 biggest = nn.x[n_l][1];
 //printf("nn.x[%d][1] %f\n",n_l, nn.x[n_l][1]);

 for(i=2;i<=n_o;i++){
 	//printf("nn.x[%d][%d] %f\n",n_l,i,nn.x[n_l][i]);
	if(nn.x[n_l][i] > biggest){
		biggest = nn.x[n_l][i];
		j = i;
	}
 }

 //printf("biggest %f index %d\n",biggest,j);
 out = j-1;
	
 switch(out){

	case 0: // Stop
                output.xc=0.0f;
                output.yc=0.0f;
                printf("Action STOP\n");
                break;

        case 1: // Forward
                output.xc=advance;
                output.yc=0.0f;
                printf("Action FORWARD\n");
                break;

        case 2: // backward
                output.xc=-advance;
                output.yc=0.0f;
                printf("Action BACKWARD\n");
                break;

        case 3:// Turn left
                output.xc=0.0f;
                output.yc=angle;
                printf("Action LEFT\n");
                break;

        case 4: // Turn right
                output.xc=0.0f;
                output.yc=-angle;
                printf("Action RIGHT\n");
                break;

        default:printf("Output %d not defined used STOP\n", out);
                output.xc=0;
                output.yc=0;
                break;
  }

  return(output);

}
                             



// Engine that executes recurrent neural networks state machines 
AdvanceAngle state_machine_destination_nn(int dest,int intensity, int obstacles, float Mag_Advance,
			float max_angle, char *individual, char *path, int flg_noise, int selection){

 AdvanceAngle gen_vector;
 static int previous_state=1;
 static int flg_old=1;
 Behavior output;
 int out_symbol;
 static int flg_read=1;
 static neural_net nn;
 static int Time;
 int i,k;


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

 printf("obstacles %d intensity %d dest %d\n",obstacles,intensity,dest);
 nn.x[0][1]=float(dest)/4.;
 nn.x[0][2]=float(obstacles)/4.;
 nn.x[0][3]=float(intensity)/4.;

 for(k=nn.num_inputs+1,i=nn.num_recurrent;k <= nn.num_inputs+nn.num_recurrent;k++,i--){
         printf("%d present state[%d] %f\n",Time,i,nn.x[0][k]);
 }



 // Evaluates de NN to find the output and next state 
 //print_values_nn(nn,1);
 evaluate(&nn);
 //print_values_nn(nn,1);

 // it calculates the output
 output=nn_symbol_output(nn,Mag_Advance,max_angle);
 gen_vector.distance=output.xc;
 gen_vector.angle=output.yc;
 printf("Outputs gen_vector.distance  %f gen_vector.angle %f\n",gen_vector.distance,gen_vector.angle);

 for(k=nn.num_outputs+1,i=nn.num_recurrent;k <= nn.num_outputs+nn.num_recurrent;k++,i--){
         printf("%d next_state[%d] %f\n",Time,i,nn.x[nn.num_layers][k]);
 }

 Time++;

 return gen_vector;

}
 


// Engine that executes recurrent neural networks state machines 
void state_machine_nn(char *file_nn,nn_inputs n_inputs,int test,nn_inputs *n_outputs,int flg_noise,int selection,
				char *path,int num_steps){


 static int previous_state=1;
 static int flg_old=1;
 static int flg_read=1;
 static neural_net nn;
 static int Time;
 int i,j,k,l;
 int sum, power,num;
 int num_inputs;


 if(flg_read==1){

        /* It reads the nn's archictecture configuration */
	strcpy(nn.file,file_nn);
        printf("NN file %s\n", nn.file);
        read_nn(&nn,0,path);

	//It creates the NN structure
        nn_initialize(&nn);

        // It reads the complete NN 
        read_nn(&nn,1,path);
	print_values_nn(nn,0); // it prints the weights

	flg_read=0;

	// Initializes the random generator
        srandom((int)time((time_t *)NULL));
	Time=1;


 }


 //num_inputs=n_inputs.num_inputs*n_inputs.num_bits_inputs;
 num_inputs=n_inputs.num_inputs;

 /*for(k=1;k<=num_inputs;k++){
	nn.x[0][k]=n_inputs.xb[test][k];
        printf("%d",n_inputs.xb[test][k]);
 }*/


 for(k=1;k<=num_inputs;k++){
	nn.x[0][k]=n_inputs.x[test][k]/10.0;
        printf("%f\n",nn.x[0][k]);
 }

 printf("\n");

 for(k=nn.num_inputs+1,i=nn.num_recurrent;k <= nn.num_inputs+nn.num_recurrent;k++,i--){
 	nn.x[0][k]=0.0;
       	printf("initial state[0] %f\n",nn.x[0][k]);
 }


 for(i=1;i<=num_steps;i++){

	printf("step %d\n",i); 
 	print_values_nn(nn,1);

	printf("\n ---- evaluate ----\n");

	// Evaluates de NN to find the outputs and next state 
 	evaluate(&nn);
	for(k=nn.num_inputs+1;k <= nn.num_inputs+nn.num_recurrent;k++){
        	printf("present state[%d] %f\n",i,nn.x[nn.num_layers][k]);
 	}
	printf("\n ---- evaluate ----\n");
	// it prints the layers input values
 	print_values_nn(nn,1);

 }

 /*
 for(k=1;k <= nn.num_inputs;k++){
		//n_outputs->x[test][k]=nn.x[nn.num_layers][k];
        	//printf("nn_output[%d] %f\n",k,n_outputs->x[test][k]);

		if(nn.x[nn.num_layers][k] > THRESHOLD) 
			n_outputs->xb[test][k]=1;
		else
			n_outputs->xb[test][k]=0;

        	//printf("nn_output[%d] %f binary %d\n",k,nn.x[nn.num_layers][k],n_outputs->xb[test][k]);
 }


 l=1;
 for(k=1;k <= n_inputs.num_inputs*n_inputs.num_bits_inputs;k=k+n_inputs.num_bits_inputs){

	sum = n_outputs->xb[test][k+n_inputs.num_bits_inputs-1];
	//printf("n_outputs.xb[%d] %d\n",k+n_inputs.num_bits_inputs-1,n_outputs->xb[test][k+n_inputs.num_bits_inputs-1]);
	power = 2;
	i=k+n_inputs.num_bits_inputs-1;
 	for (j=1;j<n_inputs.num_bits_inputs;j++){
			//printf("n_outputs.xb[%d] %d\n",i-j,n_outputs->xb[test][i-j]);
                        num = power * n_outputs->xb[test][i-j];
			sum = sum + num;
			power = power * 2;
        }
	n_outputs->x[test][l] = sum;	
       	printf("nn_output[%d] %d\n",l,n_outputs->x[test][l]);
	l++;

 }

 */


 for(k=1;k <= nn.num_inputs;k++){
		printf("nn.x[%d] %f \n", k, nn.x[nn.num_layers][k]);
		if (nn.x[nn.num_layers][k] < 0) n_outputs->x[test][k] = 0;
		else n_outputs->x[test][k] = int (nn.x[nn.num_layers][k] * 10.0);
        	printf("nn_output[%d] %d\n",k,n_outputs->x[test][k]);
 }

 return;

}



