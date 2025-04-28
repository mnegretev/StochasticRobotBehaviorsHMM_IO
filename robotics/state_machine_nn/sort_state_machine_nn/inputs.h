

// it gets line inputs 
int get_inputs(int argc, char **argv, Inputs *inputs)
{

 int i;

 // It sets default values 
 strcpy(inputs->environment,"input_file");
 strcpy(inputs->path,"test_data/");
 strcpy(inputs->file,"rnn_fsm");
 strcpy(inputs->output,"output_nn");
 inputs->number_steps = 8;
 inputs->selection = 3;

  // reads input parameters 
  if (argc>1) {
        for(i=1;i<argc;i++){
          if (!strcmp(argv[i],"-h")){

                printf("Sintax: Sort_State_Machine_NN -p path_data -f input_file -o output_file -steps number_steps -nn nn_configuration_file -selection type_nn\n");
                printf("examples:\n");
                printf("./Sort_State_Machine_NN -p test_data/ -f input_file -o output_nn -steps 16 -nn rnn_fsm -selection 3\n");
                printf("./Sort_State_Machine_NN -p test_data/ -f input_file -o output_nn -steps 0 -nn feedforward -selection 1\n");
                exit(1);
          }
          else if (!strcmp(argv[i],"-p")){
                strcpy(inputs->path,argv[i+1]);
          }
          else if (!strcmp(argv[i],"-f")){
                strcpy(inputs->environment,argv[i+1]);
          }
          else if (!strcmp(argv[i],"-o")){
                strcpy(inputs->output,argv[i+1]);
          }
          else if (!strcmp(argv[i],"-nn")){
                strcpy(inputs->file,argv[i+1]);
          }
          else if (!strcmp(argv[i],"-steps")){
                inputs->number_steps=atoi(argv[i+1]);
          }
          else if (!strcmp(argv[i],"-selection")){
                inputs->selection=atoi(argv[i+1]);
          }

    }
  }
  else{

      printf("\nIt will use default values:\n");
  }

  printf("Sort_State_Machine_NN -p %s -f %s -o %s -steps %d -nn %s -selection %d \n",
	inputs->path,inputs->environment,inputs->output,inputs->number_steps,inputs->file,inputs->selection);

  return(0);

}



