/********************************************************
 *                                                      *
 *                                                      *
 *      state_machine_engine.h		          	*
 *                                                      *
 *		Jesus Savage				*
 *		FI-UNAM					*
 *		26-6-2016                               *
 *                                                      *
 ********************************************************/

//#define NUM_BITS_INPUTS 10
#define NUM_MAX_INPUTS 8192// 2 >> NUM_BITS_INPUTS+NUM_BITS_STATES
#define NUM_BITS_OUTPUTS 3 // bits to decode 8 outputs: STOP, BACKWARD, FORWARD, TURN_LEFT, TURN_RIGHT, etc
#define NUM_MAX_OUTPUTS 16
#define NUM_BITS_INTENSITY 2
#define NUM_BITS_DEST_ANGLE 3
#define NUM_MAX_MEMORY 65535 // 2 >> 16
#define NUM_MAX_MEMORY_INPUT 1024 // 2 >> 10

    
typedef struct _memory_state_machine{
        int state;
        int output;
} memory_state_machine;


/*
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

*/



int  read_state_machine(char *file,int *memory_state,int *num_bits_out,int *num_in,int *memory_output){

 int i,j;
 FILE *fpr;
 int flag=1;
 int x,num_bits_state,num_bits_output,num_inputs;
 int state=0,output=0;

#ifdef DEBUG
 printf("File %s\n",file);
#endif


 if((fpr=fopen(file,"r")) == NULL){
        printf("File %s can not be open\n",file);
        exit(0);
 }

 fscanf(fpr,"%d",&num_bits_state);
 fscanf(fpr,"%d",&num_bits_output);
 fscanf(fpr,"%d",&num_inputs);
#ifdef DEBUG
 printf(" Num. bits state %d num. bits output %d num_inputs %d \n",
                                num_bits_state,num_bits_output,num_inputs);
#endif

 j=1;
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
#ifdef DEBUG
       	printf("memory[%d] state %d output %d\n",j,memory_state[j],memory_output[j]);
#endif

        state=0;
        output=0;


        j++;

        if(j==NUM_MAX_MEMORY){
                printf(" Increase constant NUM_MAX_MEMORY in file ~/robotics/state_machines/state_machine_engine.h\n");
                exit(0);
        }


 }

 j--;
#ifdef DEBUG
 printf("Num. memory locations %d\n",j-1);
 printf("Num. total memory %d\n",2<<(num_bits_state+num_inputs-1));
#endif

 for(i=j;i< (2<<(num_bits_state+num_inputs-1)); i++){

        memory_state[i]=0;
        memory_output[i]=0;
#ifdef DEBUG
        printf("memory[%d] state %d output %d\n",i,memory_state[i],memory_output[i]);
#endif

 }


 fclose(fpr);

 *num_in=num_inputs;
 *num_bits_out=num_bits_output;

 return(2<<(num_bits_state+num_inputs-1));

}



int  read_state_machine_stochastic(char *file,int *memory_state,int *num_in,pr_table *memory_output_pr){

 int i,j,k;
 FILE *fpr;
 int flag=1;
 int x,num_bits_state,num_bits_output,num_inputs;
 int state=0,output=0;
 int num_variables;
 float var;
 float average;


#ifdef DEBUG
 printf("File %s\n",file);
#endif


 if((fpr=fopen(file,"r")) == NULL){
        printf("File %s can not be open\n",file);
        exit(0);
 }

 fscanf(fpr,"%d",&num_bits_state);
 fscanf(fpr,"%d",&num_variables);
 fscanf(fpr,"%d",&num_inputs);

#ifdef DEBUG
 printf(" Num. bits state %d num. variables %d num_inputs %d \n", num_bits_state,num_variables,num_inputs);
#endif



 j=1;
 while(flag){
        for(i=1;i<=num_bits_state;i++){

                if(fscanf(fpr,"%d",&x) == EOF)
                        flag=0;
                else{
                        state= (x << (num_bits_state-i)) + state;
                }
        }

        memory_state[j]=state;

#ifdef DEBUG
        printf("memory[%d] state %d pr_output ",j,memory_state[j]);
#endif

	average=0;
        for(i=1;i<=num_variables;i++){

                if(fscanf(fpr,"%f",&var) == EOF)
                        flag=0;
                else{
                	memory_output_pr->ais[j][i]=var;
#ifdef DEBUG
                	printf("%f ",memory_output_pr->ais[j][i]);
#endif
                	average+=memory_output_pr->ais[j][i];
        	}
	}
#ifdef DEBUG
	printf("\n");
#endif
       	//printf("%d.- sum memory_output_pr %f\n",j,average);
        state=0;
        j++;

        if(j==NUM_MAX_MEMORY){
                printf(" Increase constant NUM_MAX_MEMORY in file ~/robotics/state_machines/state_machine_engine.h\n");
                exit(0);
        }


 }

 j--;
#ifdef DEBUG
 printf("Num. memory locations %d\n",j-1);
 printf("Num. total memory %d\n",2<<(num_bits_state+num_inputs-1));
#endif



 /*for(i=j;i< (2<<(num_bits_state+num_inputs-1)); i++){

        memory_state[i]=0;
	printf("memory[%d] state %d ",i,memory_state[i]);

	for(k=1;k<=num_variables;k++){
		memory_output_pr->ais[i][j]=0.0;
		printf("%f ",memory_output_pr->ais[i][j]);
	}
	printf("\n");
 }
*/

 fclose(fpr);

 *num_in=num_inputs;

 memory_output_pr->num_outputs=num_variables;

 return(2<<(num_bits_state+num_inputs-1));

}






// State Machine engine 
AdvanceAngle state_machine_engine(int obs, int dest, int intensity, int state, int *next_state,float Mag_Advance,float max_angle,
					char *path, int num_bits_vq){

 AdvanceAngle gen_vector;
 static int *mem_state,*mem_output;
 static int flg_read=1;
 static int num_bits_input=NUM_BITS_INPUTS,num_bits_output=NUM_BITS_OUTPUTS;
 int size_mem;
 int index;
 int out;
 Behavior value;
 int input;
 char state_machine_file_name[300];
 int num_bits_intensity = NUM_BITS_INTENSITY;
 int num_bits_dest_angle = NUM_BITS_DEST_ANGLE;
 


 if(flg_read==1){
        mem_state= (int *) malloc((unsigned) NUM_MAX_MEMORY*sizeof(int));
        mem_output= (int *) malloc((unsigned) NUM_MAX_MEMORY*sizeof(int));
	sprintf(state_machine_file_name,"%sstate_machine_mem.txt",path);

        size_mem=read_state_machine(state_machine_file_name,mem_state,&num_bits_output,&num_bits_input,mem_output);

	flg_read=0;
 }

#ifdef DEBUG
 printf("quantized intensity %d laser %d angle_dest %d\n",intensity,obs,dest);
#endif
 //input = (intensity << 4) + (obs << 2) + dest;
 //input = (intensity << (num_bits_dest_angle+num_bits_vq)) + (obs << num_bits_dest_angle) + dest;
 input = obs;
#ifdef DEBUG
 printf("present state %d input %d\n",state,input);
#endif
 index= (((state ) << num_bits_input) + input+1) & 0xffff ;

 *next_state=mem_state[index];
 out=mem_output[index];
#ifdef DEBUG
 printf("index %d next_state %d out %d\n",index,*next_state,out);
#endif

 // /home/biorobotica/robotics/utilities/utilities.h //
 gen_vector=generate_output(out,Mag_Advance,max_angle);

 //printf("Next State: %d\n", *next_state);
 return gen_vector;


}



// State Machine engine 
AdvanceAngle state_machine_engine_stochastic(int obs, int dest, int intensity, int state, int *next_state,float Mag_Advance,float max_angle,
                                        char *path, int num_bits_vq){

 AdvanceAngle gen_vector;
 static int *mem_state,*mem_output;
 static pr_table pr_output;
 static int flg_read=1;
 static int num_bits_input=NUM_BITS_INPUTS,num_bits_output=NUM_BITS_OUTPUTS;
 int size_mem;
 int index;
 int out;
 Behavior value;
 int input;
 char state_machine_file_name[300];
 int num_bits_intensity = NUM_BITS_INTENSITY;
 int num_bits_dest_angle = NUM_BITS_DEST_ANGLE;
 int num_inputs = NUM_MAX_INPUTS;
 int num_outputs = NUM_MAX_OUTPUTS;



 if(flg_read==1){
        mem_state= (int *) malloc((unsigned) NUM_MAX_MEMORY*sizeof(int));
	
	// It allocates the matriz used for the actions' generations
 	if ((pr_output.ais = (float **)alloc_matrix(num_inputs + 1, num_outputs + 1 )) == 0) {
                        printf("\n Memory allocation error ");
                        exit(1);
 	}


        sprintf(state_machine_file_name,"%sstate_machine_mem_stochastic.txt",path);

        size_mem=read_state_machine_stochastic(state_machine_file_name,mem_state,&num_bits_input,&pr_output);

        flg_read=0;
 }

#ifdef DEBUG
 printf("quantized intensity %d laser %d angle_dest %d\n",intensity,obs,dest);
#endif

 //input = (intensity << 4) + (obs << 2) + dest;
 //input = (intensity << (num_bits_dest_angle+num_bits_vq)) + (obs << num_bits_dest_angle) + dest;
 input = obs;

#ifdef DEBUG
 printf("present state %d input %d\n",state,input);
#endif

 index= (((state ) << num_bits_input) + input+1) & 0xffff ;

 *next_state=mem_state[index];
 
 // Function calculate_stochastic_action_output in /robotics/reactive_navigation/reactive_navigation.h
 out=calculate_stochastic_action_output(pr_output, index);

#ifdef DEBUG
 printf("index %d next_state %d stochastic out %d\n",index,*next_state,out);
#endif

 // /home/biorobotica/robotics/utilities/utilities.h //
 gen_vector=generate_output(out,Mag_Advance,max_angle);

 //printf("Next State: %d\n", *next_state);
 return gen_vector;


}




int  read_state_machine_input_state(char *file, int *memory_test_1, int *memory_test_2, int *memory_state_true, int *memory_state_false, int *memory_output_true, int *memory_output_false, int Meally){

 int i,j;
 FILE *fpr;
 int flag=1;
 int x,num_bits_states,num_bits_outputs,num_bits_inputs;
 int state_false=0,state_true=0,output_false=0,output_true=0;
 int test_1=0,test_2=0;

#ifdef DEBUG
 printf("File %s\n",file);
#endif


 if((fpr=fopen(file,"r")) == NULL){
        printf("File %s can not be open\n",file);
        exit(0);
 }

 fscanf(fpr,"%d",&num_bits_states);
// num_bits_inputs = Num.Bits.Intensity + Num.Bits.Light.Quadrant + Num.Bits.VQ = 2+3+5=10
 fscanf(fpr,"%d",&num_bits_inputs);
 fscanf(fpr,"%d",&num_bits_outputs);
#ifdef DEBUG
 printf(" Num. bits states %d num. bits inputs %d num_bits_outputs %d \n",
                                num_bits_states,num_bits_inputs,num_bits_outputs);
#endif

 j=1;
 while(flag){

	for(i=1;i<=num_bits_inputs;i++){

                if(fscanf(fpr,"%d",&x) == EOF)
                        flag=0;
                else{
                        test_1 = (x << (num_bits_inputs-i)) + test_1;
                }
        }

	for(i=1;i<=num_bits_inputs;i++){

                if(fscanf(fpr,"%d",&x) == EOF)
                        flag=0;
                else{
                        test_2 = (x << (num_bits_inputs-i)) + test_2;
                }
        }


	for(i=1;i<=num_bits_states;i++){

                if(fscanf(fpr,"%d",&x) == EOF)
                        flag=0;
                else{
                        state_false = (x << (num_bits_states-i)) + state_false;
                }
        }


        for(i=1;i<=num_bits_states;i++){

                if(fscanf(fpr,"%d",&x) == EOF)
                        flag=0;
                else{
                        state_true = (x << (num_bits_states-i)) + state_true;
                }
        }


        for(i=1;i<=num_bits_outputs;i++){

                if(fscanf(fpr,"%d",&x) == EOF)
                        flag=0;
                else{
                        output_false = (x << (num_bits_outputs-i)) + output_false;
#ifdef DEBUG
			//printf("output false %d %d\n",x,output_false);
#endif
                }
        }


	for(i=1;i<=num_bits_outputs;i++){

                if(fscanf(fpr,"%d",&x) == EOF)
                        flag=0;
                else{
                        output_true = (x << (num_bits_outputs-i)) + output_true;
#ifdef DEBUG
			//printf("output true %d %d\n",x,output_true);
#endif
                }
	}

	if(Meally == 0){
	     output_true = output_false;
	}

        memory_test_1[j]=test_1;
        memory_test_2[j]=test_2;
        memory_state_false[j]=state_false+1;
        memory_state_true[j]=state_true+1;
        memory_output_false[j]=output_false;
        memory_output_true[j]=output_true;
#ifdef DEBUG
	if(flag==1)
        printf("memory[%d] test_1 %d test_2 %d state_false %d state_true %d output_false %d output_true %d\n",j,memory_test_1[j], memory_test_2[j],
			memory_state_false[j],memory_state_true[j],memory_output_false[j],memory_output_true[j]);
#endif

	test_1=0;
	test_2=0;
        state_false=0;
        state_true=0;
        output_false=0;
        output_true=0;


        j++;

        if(j==NUM_MAX_MEMORY_INPUT){
                printf(" Increase constant NUM_MAX_MEMORY_INPUT in file ~/robotics/state_machines/state_machine_engine.h\n");
                exit(0);
        }


 }

 j--;
#ifdef DEBUG
 printf("Num. memory locations %d\n",j-1);
 printf("Num. total memory %d\n",2<<(num_bits_states-1));
#endif

 for(i=j;i< (2<<(num_bits_states-1)); i++){

	memory_test_1[i]=0;
	memory_test_2[i]=0;
        memory_state_false[i]=1;
        memory_state_true[i]=1;
        memory_output_false[i]=0;
        memory_output_true[i]=0;


#ifdef DEBUG
        printf("memory[%d] test_1 %d test_2 %d state_false %d state_true %d output_false %di output_true %d\n",i,memory_test_1[i],memory_test_2[i],
			memory_state_false[i],memory_state_true[i],memory_output_false[i],memory_output_true[i]);
#endif

 }


 fclose(fpr);

 //*num_in=num_inputs;
 //*num_bits_out=num_bits_output;

 return(2<<(num_bits_states-1));

}



                 
// State Machine engine using a input/state table architecture 
AdvanceAngle state_machine_engine_input_state(int obs, int dest, int intensity, int state, int *next_state,float Mag_Advance,float max_angle,
                                        char *path, int num_bits_vq, int Meally){

 AdvanceAngle gen_vector;
 static int *mem_state_true,*mem_state_false;
 static int *mem_output_true,*mem_output_false;
 static int *mem_test_1,*mem_test_2;
 static int flg_read=1;
 static int num_bits_input=NUM_BITS_INPUTS,num_bits_output=NUM_BITS_OUTPUTS;
 int size_mem;
 int index;
 int out;
 Behavior value;
 int input;
 char state_machine_file_name[300];
 int num_bits_intensity = NUM_BITS_INTENSITY;
 int num_bits_dest_angle = NUM_BITS_DEST_ANGLE;
 int test_1,test_2,dummy;
 int next_st;



 if(flg_read==1){
        mem_state_true= (int *) malloc((unsigned) NUM_MAX_MEMORY_INPUT*sizeof(int));
        mem_state_false= (int *) malloc((unsigned) NUM_MAX_MEMORY_INPUT*sizeof(int));
        mem_output_true= (int *) malloc((unsigned) NUM_MAX_MEMORY_INPUT*sizeof(int));
        mem_output_false= (int *) malloc((unsigned) NUM_MAX_MEMORY_INPUT*sizeof(int));
        mem_test_1= (int *) malloc((unsigned) NUM_MAX_MEMORY_INPUT*sizeof(int));
        mem_test_2= (int *) malloc((unsigned) NUM_MAX_MEMORY_INPUT*sizeof(int));
        sprintf(state_machine_file_name,"%sinput_state_machine_mem.txt",path);

        size_mem=read_state_machine_input_state(state_machine_file_name,mem_test_1,mem_test_2,mem_state_true,mem_state_false,mem_output_true,mem_output_false,Meally);

        flg_read=0;
 }

#ifdef DEBUG
 printf("quantized intensity %d quadrant_dest %d laser_VQ %d\n",intensity,dest,obs);
#endif
 //input = (intensity << (num_bits_dest_angle+num_bits_vq)) + (obs << num_bits_dest_angle) + dest;
 //input = (intensity << (num_bits_dest_angle+num_bits_vq)) + (dest << num_bits_vq) + obs;
 input = obs;
#ifdef DEBUG
 printf("present state %d input %d\n",state,input);
#endif

 test_1 = mem_test_1[state];
 test_2 = mem_test_2[state];
 if (test_1 > test_2){
	dummy = test_1;
	test_1 = test_2;
	test_2 = dummy;
} 

#ifdef DEBUG
 printf("test_1 %d test_2 %d\n",test_1,test_2);
#endif

 if((input >= test_1) && (input <= test_2)){
	next_st = mem_state_true[state];
	out = mem_output_true[state];
	#ifdef DEBUG
 	printf("next TRUE state %d true output %d\n",next_st,out);
	#endif
 }
 else{
	next_st = mem_state_false[state];
        out = mem_output_false[state]; 
	#ifdef DEBUG
 	printf("next FALSE state %d false output %d\n",next_st,out);
	#endif
 }	

 *next_state=next_st;
#ifdef DEBUG
 printf("test_1 %d test_2 %d next_state %d out %d\n",test_1,test_2,*next_state,out);
#endif

 // /home/biorobotica/robotics/utilities/utilities.h //
 gen_vector=generate_output(out,Mag_Advance,max_angle);

 //printf("Next State: %d\n", *next_state);
 return gen_vector;


}



