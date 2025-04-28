/*

        neural_networks.h

*/

//#define NUM_MAX_LAYERS 10
#define NUM_MAX_NN 40
#define RADIO_WHEEL 0.2 // Wheel's radio robot
#define DISTANCE_AXES 0.6 // Axes distance beteen wheels 

/*
typedef struct _weights{
	//float w[NUM_MAX_NN][NUM_MAX_NN];
	float **w;
} weights;



typedef struct _neural_net{
	char file[300];
	int num_layers; // number of layers
	int num_inputs; // number of inputs
	int num_outputs; // number of outputs
	int num_neurons_layer[NUM_MAX_LAYERS]; // number of neurons per layer
	int num_recurrent; // number of recurrent neurons <= num_outputs
	int num_inputs_delayed; // number of delayed inputs
	weights layer[NUM_MAX_LAYERS]; // weights between layers
	float **x; // inputs and outputs between layers
	float **prev_x; // previous inputs
} neural_net;

*/



int *alloc_int(int row)
{
    int *m;

    m = (int *) malloc((unsigned) row*sizeof(int));
    return m;
}


int **alloc_matrix_int(int row, int col)
{
    int i;
    int **m;

    m = (int **) malloc((unsigned) row*sizeof(int *));
    for (i=0; i<row; i++)
        m[i] = (int *) malloc((unsigned) col*sizeof(int));
    return m;
}



float *alloc_float(int row)
{
    float *m;

    m = (float *) malloc((unsigned) row*sizeof(float));
    return m;
}


float **alloc_matrix_float(int row, int col)
{
    int i;
    float **m;

    m = (float **) malloc((unsigned) row*sizeof(float *));
    for (i=0; i<row; i++)
        m[i] = (float *) malloc((unsigned) col*sizeof(float));
    return m;
}


//It reads the weights of the NN
void read_neural_net(FILE *fpr, neural_net *nn, int num){

 int i,j,k;
 int flag=1;
 float w;
 int num_weights=0;

 // It reads the header of the NN
 for(j=0;j<num;j++){
	fscanf(fpr,"%d",&i);
	//printf("%d %d\n",j,i);
 }

 printf("Num. layers %d\n",nn->num_layers);
 for(j=0;j<nn->num_layers;j++){

		//printf("num_neurons_layer[%d] %d\n",j,nn->num_neurons_layer[j]);
        	for(i=0;i<nn->num_neurons_layer[j];i++){
			nn->x[j][i]=0.0;	
                       
			//printf("num_neurons_layer[%d] %d\n",j+1,nn->num_neurons_layer[j+1]);
 
			for(k=0;k<=nn->num_neurons_layer[j+1];k++){
				if(fscanf(fpr,"%f",&w) == EOF){
					flag=0;
					//break;
					printf("Not enough data");
					exit(0);
				}
				else{
					nn->layer[j].w[i][k]=w;
					num_weights++;
					//nn->layer[j].w[i][k]=(float)k;
					//printf("weight %f layer %d w[%d][%d] %f\n",w,j,i,k,nn->layer[j].w[i][k]);
				}	
			}
		}		
		nn->x[j][i]= 0.0; 
		nn->x[j][0]=-1.0; // bias
		//printf(" flag_init %d nn->x[%d][0] %f\n",flag_init,j,nn->x[j][0]);
 }

 nn->x[j][0]=-1.0; // bias
 printf("Num. Weights %d\n",num_weights);

}


// it prints the nn weight or the xs values
void print_values_nn(neural_net nn, int flg){

 int i,j,k;

 if(flg==0){
 	printf("Num. layers %d\n",nn.num_layers);
 	for(i=0;i<=nn.num_layers;i++){
       		printf("num_neurons layer %d %d \n",i,nn.num_neurons_layer[i]);
 	}
	
 	printf("num_inputs %d\nnum_outputs %d\nnum_recurrent %d\nnum_delayed_inputs %d\n",
				nn.num_inputs,nn.num_outputs,nn.num_recurrent,nn.num_inputs_delayed);

 	for(j=0;j<=nn.num_layers-1;j++)
		for(i=0;i<nn.num_neurons_layer[j];i++)
			for(k=0;k<=nn.num_neurons_layer[j+1];k++){
				printf("layer %d w[%d][%d] %f\n",j,i,k,nn.layer[j].w[i][k]);
 	}
 }
 else{
	for(j=0;j<=nn.num_layers;j++)
        for(i=0;i<=nn.num_neurons_layer[j];i++){
		printf("x[%d][%d] %f\n",j,i,nn.x[j][i]);
 	}
 }

}


// it evaluates the neural net
void evaluate(neural_net *nn){

 int i,j,k,m;
 int ini_blk,end_blk;
 float temp;

 for(i=0; i < nn->num_layers;i++){
	for(j=1;j <= nn->num_neurons_layer[i+1];j++){ 

		temp=0;
		//printf("calculating neuron out %d in layer %d\n",j,i+1);
		for(k=0;k < nn->num_neurons_layer[i];k++){
			temp= nn->x[i][k]*nn->layer[i].w[k][j]+temp;
			//printf("neuron in %d layer %d\n",k,i);
			//printf("x[%d][%d] %f w[%d][%d] %f\n",i,k,nn->x[i][k],k,j,nn->layer[i].w[k][j]);
		}

		//printf("sum_product %f\n",temp);
		temp= tanh(temp);
		//printf("no-linear-function %f\n",temp);

		nn->x[i+1][j]=temp;
		//printf("forward x[%d][%d] %f\n",i+1,j,nn->x[i+1][j]);

	}
 }

 // it feedbacks the recurrent values
 for(k=nn->num_outputs+1,i=nn->num_inputs+1;k <= nn->num_outputs+nn->num_recurrent;k++,i++){
                        nn->x[0][i]=nn->x[nn->num_layers][k];
			//printf(" recurrent feedback x[0][%d] x[%d][%d] %f\n",
					//i,nn->num_layers,k,nn->x[nn->num_layers][k]);
 }

 // it puts the delayed values as inputs
 if(nn->num_inputs_delayed != 0){

	 //printf(" num_inputs %d num delayed %d\n",nn->num_inputs,nn->num_inputs_delayed);
	// it starts with the last block
	ini_blk=nn->num_inputs+nn->num_recurrent+1+nn->num_inputs*(nn->num_inputs_delayed-2); 
	end_blk=nn->num_inputs+nn->num_recurrent+1+nn->num_inputs*(nn->num_inputs_delayed-1); 
	//printf(" ini_blk %d end_blk %d\n",ini_blk,end_blk);

 	for(m=1;m <= nn->num_inputs_delayed-1;m++){
 		for(i=ini_blk,k = end_blk,j=1;j <= nn->num_inputs;k++,i++,j++){
                        nn->x[0][k]=nn->x[0][i];
			//printf(" feedback x[0][%d] x[0][%d] %f\n",k,i,nn->x[0][i]);
 		}
		ini_blk=ini_blk-nn->num_inputs;
		end_blk=end_blk-nn->num_inputs;
	}

	// it copies the first block
	ini_blk=1;
	end_blk=nn->num_inputs+nn->num_recurrent+1;
 	for(i=ini_blk,k=end_blk,j=1;j <= nn->num_inputs;k++,i++,j++){
                nn->x[0][k]=nn->x[0][i];
		//printf(" feedback x[0][%d] x[0][%d] %f\n",k,i,nn->x[0][i]);
                //nn->x[0][k]=nn->x[0][i] - nn->prev_x[0][i];
		nn->prev_x[0][i]=nn->x[0][i];
 	}

 }
			
			
}


/*
void calculate_speeds(float wl,float wr,float *v, float *w){

 *v = PI*RADIO_WHEEL*(wl+wr);
 *w = 2*PI*RADIO_WHEEL*(-wl+wr)/DISTANCE_AXES;

}
*/



// it initializes the NN
void nn_initialize(neural_net *nn) {

 int i,j,k;
 int biggest;


 nn->num_inputs=nn->num_neurons_layer[0];
 i= nn->num_layers;
 nn->num_outputs=nn->num_neurons_layer[i];
 k=nn->num_recurrent + nn->num_neurons_layer[0]*(1+nn->num_inputs_delayed);
 nn->num_neurons_layer[0]=k;

 //printf("Num. Neurons inputs+recurrent+delayed_inputs %d\n",nn->num_neurons_layer[0]);

 // It allocates the matrices used for the NN evaluation

 if (( nn->prev_x =  (float **) alloc_matrix_float(nn->num_layers+1, k*10)) == 0) {
                        printf("\n Memory allocation error ");
                        exit(1);
 }



 if (( nn->layer[0].w =  (float **) alloc_matrix_float(k+1, nn->num_neurons_layer[1]+1)) == 0) {
                        printf("\n Memory allocation error ");
                        exit(1);
 }


 for(j=1;j < nn->num_layers;j++){
        if(( nn->layer[j].w = (float **) alloc_matrix_float(nn->num_neurons_layer[j]+1, nn->num_neurons_layer[j+1]+1)) == 0) {
                       	printf("\n Memory allocation error ");
                       	exit(1);
	}

 }

 if ((nn->layer[j].w =  (float **) alloc_matrix_float(nn->num_neurons_layer[j-1]+1, nn->num_neurons_layer[j]+nn-> num_recurrent+1)) == 0) {
                        printf("\n Memory allocation error ");
                        exit(1);
 }       

 nn->num_neurons_layer[j]=nn->num_neurons_layer[j]+nn->num_recurrent;

 biggest = nn->num_neurons_layer[0];
 for(i=2;i<=nn->num_layers;i++){
        if(nn->num_neurons_layer[i] > biggest){
                biggest = nn->num_neurons_layer[i];
                j = i;
        }
 }
 //printf("biggest num.layers %d index %d\n",biggest,j);

 if (( nn->x =  (float **) alloc_matrix_float(nn->num_layers+1, biggest*3)) == 0) {
                        printf("\n Memory allocation error ");
                        exit(1);
 }


 //printf("Num. Neurons outputs+recurrent[%d] %d\n",j,nn->num_neurons_layer[j]);

}




// it reads the neural net, header and weights
void read_nn(neural_net *nn, int flg_read,char *path)
{
   FILE *fpr;
   float average,tmp;
   int i,j;
   static int k=0;
   char input_file[300];
   int n_states,n_obs_symbols,n_out_symbols;
   int n_bits_inputs;
   int limits;
   int num;


   /* It opens the NN file */
   sprintf(input_file,"%s%s.txt",path,nn->file);
   //printf("Reading NN FILE: %s\n",input_file);
   fpr=fopen(input_file,"r");
   if(fpr==0){
        printf("\n File %s does not exists",input_file);
        exit(0);
   }

   if(flg_read==0) {

   		// It reads the header: number of layers, num. recurrent, num. values delayed and num. of weiths per layer
   		fscanf(fpr,"%d",&num);
   		nn->num_layers=num;
		k++;
   		fscanf(fpr,"%d",&num);
   		nn->num_recurrent=num;
		k++;
   		fscanf(fpr,"%d",&num);
   		nn->num_inputs_delayed=num;
		k++;

		for(i=0;i<=nn->num_layers;i++){
                	fscanf(fpr,"%d",&num);
			k++;
                	nn->num_neurons_layer[i]= num;
                	printf("num_neurons_layer[%d] %d\n",i,nn->num_neurons_layer[i]);

                	if(num > NUM_MAX_NN){
                        	printf("Change constant NUM_MAX_NN in file neural_networks.h to %d\n", num+1);
                        	exit(0);
                	}
        	}

                fclose(fpr);
                printf("Num.layers %d num.recurrent %d Num.inputs_delayed %d\n",nn->num_layers,nn->num_recurrent,					nn->num_inputs_delayed);
                return;
   }

   // it read the weights
   read_neural_net(fpr,nn,k);
 
   return;


}


// it reads the inputs
void read_inputs(nn_inputs *n_inputs, char *input_file,nn_inputs *n_outputs)
{
   FILE *fpr;
   int i,j,k,l;
   int n_bits_inputs;
   int num;
   int binary[65];
   int bit;


   /* It opens the NN inputs file */
   printf("Reading NN FILE: %s\n",input_file);
   fpr=fopen(input_file,"r");
   if(fpr==0){
        printf("\n File %s does not exists\n",input_file);
        exit(0);
   }


  // It reads the header: number of tests, number of inputs, number of bits per input
  fscanf(fpr,"%d",&num);
  n_inputs->num_tests=num;
  n_outputs->num_tests=num;
  fscanf(fpr,"%d",&num);
  n_inputs->num_inputs=num;
  n_outputs->num_inputs=num;
  fscanf(fpr,"%d",&num);
  n_inputs->num_bits_inputs=num;
  n_outputs->num_bits_inputs=num;

  printf("Num. tests %d Num. Inputs %d Num.Bits %d\n",n_inputs->num_tests,n_inputs->num_inputs,n_inputs->num_bits_inputs);

  if(( n_inputs->x =  (int **) alloc_matrix_int(n_inputs->num_tests+1, n_inputs->num_inputs+1)) == 0) {
                        printf("\n Memory allocation error ");
                        exit(1);
  }

  if(( n_inputs->xb =  (int **) alloc_matrix_int(n_inputs->num_tests+1, n_inputs->num_inputs*n_inputs->num_bits_inputs+1)) == 0) {
                        printf("\n Memory allocation error ");
                        exit(1);
  }

  if(( n_outputs->x =  (int **) alloc_matrix_int(n_inputs->num_tests+1, n_inputs->num_inputs+1)) == 0) {
                        printf("\n Memory allocation error ");
                        exit(1);
  }

  if(( n_outputs->xb =  (int **) alloc_matrix_int(n_inputs->num_tests+1, n_inputs->num_inputs*n_inputs->num_bits_inputs+1)) == 0) {
                        printf("\n Memory allocation error ");
                        exit(1);
  }


  for(i=1;i<=n_inputs->num_tests;i++){
	
	l=1;

 	for(j=1;j<=n_inputs->num_inputs;j++){
		fscanf(fpr,"%d",&num);
        	n_inputs->x[i][j]= num;
        	//printf("x[%d][%d] = %d ",i,j,n_inputs->x[i][j]);
		for (k=1;k<=n_inputs->num_bits_inputs;k++){
			bit = num & 1;
			num = num >> 1;
			binary[k] = bit;
			//printf("b[%d] %d\n",k,binary[k]);
		}	

		for (k=n_inputs->num_bits_inputs;k > 0 ;k--){
			//printf("%d",binary[k]);
			n_inputs->xb[i][l]= binary[k];
			l++;
		}

		//printf("\n");
        }
	
	//printf("\n");

	//for(k=1;k<l;k++){
		//printf("%d",n_inputs->xb[i][k]);

	//}
	//printf("\n");
 }

 fclose(fpr);


 return;


}

