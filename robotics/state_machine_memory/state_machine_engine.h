/********************************************************
 *                                                      *
 *                                                      *
 *      state_machine_engine.h                          *
 *                                                      *
 *                    J. Savage, UNAM			*
 *		      March 2011			*
 *		      July  2013                        *
 *                                                      *
 *                                                      *
 ********************************************************/

#define NUM_MAX_MEMORY 65535 // 2 >> 16
#define THRS_LASER 5.0 // threshold for the average of input values
#define KF1 1000.00 // fitness distance constant
#define KF2 700.00 // fitness number of steps constant
#define KF3 300.00 // fitness stuck constant
#define KF4 2000.00 // fitness num_backward constant
#define KF5 1000.00 // fitness origen constant
//#define START_LASER 4 // 
//#define NUM_RANGE_LASER_32 16 // #define NUM_LASERS 682



typedef struct _memory_state_machine{
        int state;
        int output;
} memory_state_machine;


 //FUNCTION THAT EVALUE THE FITNESS
float getFit(int nSteps,float dist, int num_stuck, int num_backward, float dist_origen){
 
 float fitness;

 fitness= KF1/(dist+1.0) + KF2/(float)nSteps + KF3/((float)num_stuck + 1.0) + KF4/((float)num_backward + 1.0)
		+ KF5*dist_origen;

 return(fitness);

}



int  read_state_machine(char *file,int *num_in,int *num_bits_out,int *memory_state,int *memory_output){

 int i,j;
 FILE *fpr;
 int flag=1;
 int x,num_bits_state,num_bits_output,num_inputs;
 int state=0,output=0;


 printf("File %s\n",file);
 
 if((fpr=fopen(file,"r")) == NULL){
        printf("File %s can not be open\n",file);
        exit(0);
 }

 fscanf(fpr,"%d",&num_bits_state);
 fscanf(fpr,"%d",&num_bits_output);
 fscanf(fpr,"%d",&num_inputs);
 printf(" Num. bits state %d num. bits output %d num_inputs %d \n",
				num_bits_state,num_bits_output,num_inputs);

 j=0;
 while(flag){
	for(i=1;i<=num_bits_state;i++){
		
        	if(fscanf(fpr,"%d",&x) == EOF)
                	flag=0;
        	else{
        	        state= (x << (num_bits_state-i)) + state;
        	}
	}

	for(i=1;i<=num_bits_output;i++){

                if(fscanf(fpr,"%d",&x) == EOF)
                        flag=0;
                else{
                        output= (x << (num_bits_output-i)) + output;
                }
        }

	memory_state[j]=state;
	memory_output[j]=output;

	state=0;
	output=0;

        //printf("memory[%d].state %d output %d\n",j,memory_state[j],memory_output[j]);

	j++;

	if(j==NUM_MAX_MEMORY){
		printf(" Increase constant NUM_MAX_MEMORY in file state_machine_engine.h\n");
		exit(0);
	}


 }

 for(i=j;i< (2<<(num_bits_state+num_inputs-1)); i++){
	
	memory_state[i]=0;
	memory_output[i]=0;
        //printf("memory[%d].state %d output %d\n",i,memory_state[i],memory_output[i]);

 }


 fclose(fpr);

 *num_in=num_inputs; 
 *num_bits_out=num_bits_output;
 
 return(2<<(num_bits_state+num_inputs-1));

}


// it converts a binary output to a robot's output
Behavior table_output(int out, int num_bits_out){

  Behavior output;
  float angle=(float) (PI/(4.0*15.0));
  float advance;
  int bits_mag,mag,bits_dir,dir;


  advance= Mag_Advance/15.00; // mag = {0 ... 15} 

  // The output bits dn dn-1 are the direction
  // dn-2 ...do gives the magnitud 

 bits_mag = (2<<(num_bits_out-3))-1;
 mag = bits_mag & out;
 bits_dir = 3<<(num_bits_out-2);
 dir = (bits_dir & out) >> (num_bits_out-2);

 printf("bits_mag %x bits_dir %x\n",bits_mag,bits_dir);
 printf("out %x dir %x mag %x\n",out,dir,mag);

 // output.xc has the movements magnitud
 // output.yc has the angle

  switch(dir){

        case 0: // Forward
                output.xc=advance*mag;
                output.yc=0.0f;
                printf("FORWARD\n");
                break;

        case 1:// Turn left
                output.xc=0.0f;
                output.yc=angle*mag;
                printf("LEFT\n");
                break;

        case 2: // Turn right
                output.xc=0.0f;
                output.yc=-angle*mag;
                printf("RIGHT\n");
                break;

        case 3: // backward
                output.xc=-advance*mag;
                output.yc=0.0f;
                Num_backward++;
                printf("BACKWARD\n");
                break;

        default:printf("\nOutput %d not defined", out);
                output.xc=0;
                output.yc=0;

  }

  return(output);

}


// it converts a binary output to a robot's output
Behavior table_output_destination(int dir){

  Behavior output;
  float angle=(float) (PI/(4.0*15.0));
  float advance;
  int mag;
  float mag_angle;
 

  advance= Mag_Advance*1.00;
  mag=1;
  mag_angle=8.0;


  switch(dir){

        case 0: // Stop
                output.xc=0.0f;
                output.yc=0.0f;
                printf("STOP\n");
                break;

        case 1: // Forward
                output.xc=advance*mag;
                output.yc=0.0f;
                printf("FORWARD\n");
                break;

        case 2: // backward
                output.xc=-advance*mag;
                output.yc=0.0f;
                Num_backward++;
                printf("BACKWARD\n");
                break;

        case 3:// Turn left
                output.xc=0.0f;
                output.yc=angle*mag_angle;
                printf("LEFT\n");
                break;

        case 4: // Turn right
                output.xc=0.0f;
                output.yc=-angle*mag_angle;
                printf("RIGHT\n");
                break;

        default:printf("Output %d not defined used STOP\n", dir);
                output.xc=0;
                output.yc=0;
                break;
  }

  return(output);

}



// it calculates the next state and output
void  get_new_state(memory_state_machine *memory,int state,int input, int num_bits_inputs, int *next_state, Behavior *output, int num_bits_output, int mode){
 
 int index;
 int out;
 Behavior value;

 index= ((state << num_bits_inputs) + input) & 0xffff ;

 *next_state=memory[index].state;
 out=memory[index].output; 
 printf("index %d next_state %d out %d\n",index,*next_state,out); 

 if( mode == ARBITER){
	value.xc=out;
        value.yc=0;

 }
 else{ 
	// it converts a binary output to a robot's output
	value=table_output(out,num_bits_output);
 }

 *output=value;

}


 // It quantizes the inputs, fix this later 2-1-11
int quantize_inputs(float *vector, int size){

 int value=0;
 int i;

 for(i=1;i<=size;i++){
	if(vector[i] < THRS_LASER)
		value = (value << 1) + 1;
	else
		value = (value << 1) + 0;
        
	//printf("value %d\n",value);
 }

 return(value);

}





// Engine to execute algorithmic state machines 
Behavior  state_machine_engine(char *sensor, int num_sensors, int *num_obs, Raw observations, int reset, char *individual, int num_ind, int mode, int flg_read){

 Behavior gen_vector;
 static int state[NUM_MAX_BEHAVIORS];
 float angle=(float) (1.5708/2.0);
 static int num_steps=0;
 static float left,right;
 float theta;
 int **state_memory;
 centroid centroids[NUM_MAX_CENTROIDS];
 static memory_state_machine memory[NUM_MAX_BEHAVIORS][NUM_MAX_MEMORY];
 float sensors[16];
 int quantized_value;
 int next_state;
 Behavior output;
 static int num_bits_input[NUM_MAX_BEHAVIORS];
 static int num_bits_output[NUM_MAX_BEHAVIORS];
 int i,j;
 static int start[NUM_MAX_BEHAVIORS][16],end[NUM_MAX_BEHAVIORS][16];
 static int flg=0;
 float average; 
 int range=NUM_LASERS; // #define NUM_LASERS 682





 printf("\n\n *******************************\nNum IND %d Reset %d\n",num_ind,reset);

 if(reset==1){
        state[num_ind]=0;
        num_steps=0;
 }




 if(flg_read==1){
	//num_bits_output[num_ind]=read_state_machine(individual,memory[num_ind],&num_bits_input[num_ind]);
 
	range=NUM_LASERS/(num_bits_input[num_ind]*2);
	printf("num_ind %d %d range %d \n",num_ind,num_bits_input[num_ind],range);

	for(i=num_bits_input[num_ind]/2+1,j=1;i<=num_bits_input[num_ind];i++,j++){
                start[num_ind][j]=num_sensors/2+ START_LASER + (j-1)*range;
                //end[num_ind][j]=num_sensors/2+ START_LASER +j*NUM_RANGE_LASER_32;
                end[num_ind][j]=start[num_ind][j]+1;
		printf("num_ind %d %d range laser %d %d\n",num_ind,j,start[num_ind][j],end[num_ind][j]);
        }  

	for(i=1;i<=num_bits_input[num_ind]/2;i++,j++){
		start[num_ind][j]=num_sensors/2 - START_LASER - (i-1)*range;
		//end[num_ind][j]=num_sensors/2 - START_LASER - (i-1)*NUM_RANGE_LASER_32;
		end[num_ind][j]=start[num_ind][j]+1;
		printf("num_ind %d %d range laser %d %d\n",num_ind,j,start[num_ind][j],end[num_ind][j]);
	}  


 }

 printf("\n\nSME Present State: %d \n", state[num_ind]);

 for(i=1; i <= num_bits_input[num_ind] ;i++){
		get_average_laser(observations,start[num_ind][i],end[num_ind][i],&average);
		sensors[i]=average;
		//printf("%d range laser %d %d\n",i,start[i],end[i]);
 		printf("sensors[%d] %f \n",i,sensors[i]);
 }



 // It quantizes the inputs
 quantized_value=quantize_inputs(sensors,num_bits_input[num_ind]);
 printf("quantized inputs %d\n",quantized_value); 

 // it calculates the next state and output
 get_new_state(memory[num_ind],state[num_ind],quantized_value,num_bits_input[num_ind],&next_state,&output,num_bits_output[num_ind],mode);

 gen_vector.xc=output.xc;
 gen_vector.yc=output.yc;
 gen_vector.status=1.00;
 gen_vector.flg_vector=0;

 state[num_ind]=next_state;

 printf("Ind. %d SME Next State: %d\n output.xc  %f output.yc %f\n",num_ind,state[num_ind],gen_vector.xc,gen_vector.yc);

 return gen_vector;

}


// it calculates the next state and output
void  get_new_state_destination(memory_state_machine *memory,int state,int input, int num_bits_inputs, int *next_state, Behavior *output,int flg, hmm_database hmm,int quant_obs){

 int index;
 int out;
 Behavior value;

 index= ((state << num_bits_inputs) + input) & 0xffff ;

 *next_state=memory[index].state;
 out=memory[index].output;
 printf("index %d next_state %d out %d\n",index,*next_state,out);

 // /home/savage/robots/state_machine/state_machine.h
 value=get_output(out,0,hmm,state,quant_obs);

 // it converts a binary output to a robot's output
 value=get_output(out,flg,hmm,state,quant_obs);
 //value=table_output_destination(out);

 *output=value;

}




// Engine to execute algorithmic state machines 
Behavior  state_machine_engine_destination(char *sensor, int num_sensors, int *num_obs, Raw observations, int reset, char *individual, int num_ind, int mode, int flg_read, int flg_noise,coord coor_destination, int flg_out_prb, char *path){

 Behavior gen_vector;
 static int num_bits_attraction[NUM_MAX_BEHAVIORS];
 static int num_bits_intensity[NUM_MAX_BEHAVIORS];
 static int state[NUM_MAX_BEHAVIORS];
 float angle=(float) (1.5708/2.0);
 static int num_steps=0;
 static float left,right;
 float theta;
 int **state_memory;
 centroid centroids[NUM_MAX_CENTROIDS];
 static memory_state_machine memory[NUM_MAX_BEHAVIORS][NUM_MAX_MEMORY];
 int *mem_state,*mem_output;
 memory_state_machine *mem;
 float sensors[16];
 int quantized_value;
 int next_state;
 Behavior output;
 static int num_bits_input[NUM_MAX_BEHAVIORS];
 static int num_inputs[NUM_MAX_BEHAVIORS];
 static int num_bits_output[NUM_MAX_BEHAVIORS];
 int i,j;
 static int start[NUM_MAX_BEHAVIORS][16],end[NUM_MAX_BEHAVIORS][16];
 static int flg=0;
 float average; 
 int range=NUM_LASERS; // #define NUM_LASERS 682
 int flag_destination=1;
 coord coord_robot;
 int quantized_attraction;
 int quantized_total;
 int size_mem;
 int quantized_intensity;
 static struct hmm_database hmm;
 int num_outputs;


 printf("\n\n *******************************\n\n");
 //printf("\n\n *******************************\nNum IND %d Reset %d\n",num_ind,reset);

 if(reset==1){
        state[num_ind]=0;
        num_steps=0;
 }




 if(flg_read==1){
	mem_state= (int *) malloc((unsigned) NUM_MAX_MEMORY*sizeof(int));
	mem_output= (int *) malloc((unsigned) NUM_MAX_MEMORY*sizeof(int));
	size_mem=read_state_machine(individual,&num_bits_input[num_ind],&num_bits_output[num_ind],mem_state,mem_output);

 	for(i=0;i<size_mem;i++){
		memory[num_ind][i].state=mem_state[i];
		memory[num_ind][i].output=mem_output[i];
	 	printf("memory[%d] state %d ",i,memory[num_ind][i].state);
	 	printf("output  %d\n",memory[num_ind][i].output);
 	}

	free( (int *) mem_state);
	free( (int *) mem_output);

 	num_bits_attraction[num_ind]=2;
 	num_bits_intensity[num_ind]=1;
	num_bits_input[num_ind] = num_bits_input[num_ind] - 3;
 
        if(num_bits_input[num_ind] >= 2){

		range=NUM_LASERS/(num_bits_input[num_ind]*2);
        	printf("\nnum_bits_inputs %d range %d \n",num_bits_input[num_ind],range);

        	for(i=num_bits_input[num_ind]/2+1,j=1;i<=num_bits_input[num_ind];i++,j++){
                	start[num_ind][j]=num_sensors/2 + (j-1)*range;
                	end[num_ind][j]=start[num_ind][j]+ j*range -1;
                	printf("%d range laser %d %d\n",j,start[num_ind][j],end[num_ind][j]);
        	}	

        	for(i=1;i<=num_bits_input[num_ind]/2;i++,j++){
                	end[num_ind][j]=num_sensors/2 - 1 - (i-1)*range;
                	start[num_ind][j]=end[num_ind][j] - i*range -1;
                	printf("%d range laser %d %d\n",j,start[num_ind][j],end[num_ind][j]);
        	}

	}	

	// Initializes the random generator
        srandom((int)time((time_t *)NULL));


        if(flg_out_prb == 1){

                // It reads the probabilities of the random outputs, the file has an hmm structure
                /* It reads the number of states, num. obs. symbols and nun. out symbols of the hmm */
                strcpy(hmm.objects_file,"fsm_memory");
                printf("HMM file %s\n", hmm.objects_file);
                read_hmms(&hmm,0,path);

                //It creates the HMM
                hmm_initialize(&hmm);

                /* It reads the complete hmm */
                read_hmms(&hmm,1,path);
                num_outputs=hmm.num_out_symbols;

        }


 }

 printf("\n\nSME Present State: %d \n", state[num_ind]);


 for(i=1; i <= num_bits_input[num_ind];i++){
                get_average_laser(observations,start[num_ind][i],end[num_ind][i],&average);
                sensors[i]=average;
                //printf("%d range laser %d %d\n",i,start[i],end[i]);
                printf("sensors[%d] %f \n",i,sensors[i]);
 }

 // It quantizes the inputs
 if(num_bits_input[num_ind] > 0) quantized_value=quantize_inputs(sensors,num_bits_input[num_ind]);
 else quantized_value=0;
 printf("quantized sensors %d \n",quantized_value);


 // it senses the destination
 // it gets the robot's position
 coordinates_robot("Ryu",&coord_robot);
 quantized_attraction=quantize_destination_angle(coord_robot,coor_destination);
 printf("quantized destination %d \n",quantized_attraction);

 // It quantizes the intensity of the destination 
 quantized_intensity = quantize_intensity(coord_robot,coor_destination);
 printf("quantized intensity %d \n",quantized_intensity);



 // add noise to the quantized values
 if(flg_noise==1){
        quantized_attraction=change_bits_random(quantized_attraction,num_bits_attraction[num_ind]);
        quantized_value=change_bits_random(quantized_value,num_bits_input[num_ind]);
	quantized_intensity = change_bits_random(quantized_intensity,num_bits_intensity[num_ind]);
        printf("noised quantized_intensity %d quantized destination %d quantized sensors %d\n",
                quantized_intensity,quantized_attraction,quantized_value);
 }

 // It joints the obstacles and destination quantized sensors
 quantized_total= (quantized_intensity << 4) +(quantized_value << 2) + quantized_attraction;
 printf("quantized inputs %d %d %d %d\n",quantized_intensity,quantized_value,quantized_attraction,quantized_total);
 quantized_value = quantized_total;

 // it calculates the next state and output
 get_new_state_destination(memory[num_ind],state[num_ind],quantized_value,
			num_bits_input[num_ind]+num_bits_attraction[num_ind] + num_bits_intensity[num_ind],&next_state,&output,flg_out_prb,hmm,
			quantized_total);

 gen_vector.xc=output.xc;
 gen_vector.yc=output.yc;
 gen_vector.status=1.00;
 gen_vector.flg_vector=0;

 state[num_ind]=next_state;

 printf("Ind. %d SME Next State: %d\n output.xc  %f output.yc %f\n",num_ind,state[num_ind],gen_vector.xc,gen_vector.yc);

 return gen_vector;

}



