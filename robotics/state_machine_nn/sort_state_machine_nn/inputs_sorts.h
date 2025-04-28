

// it gets line inputs 
int get_inputs(int argc, char **argv, Inputs *inputs)
{

 int i;

 // It sets default values 
 strcpy(inputs->environment,"input_file");
 strcpy(inputs->path,"test_data/");
 strcpy(inputs->output,"output_file");

  // reads input parameters 
  if (argc>1) {
        for(i=1;i<argc;i++){
          if (!strcmp(argv[i],"-h")){

                printf("Sintax: evaluate_sort -p path_data -f input_file -o output_file\n");
                printf("example:\n");
                printf("./evaluate_sort -p test_data/ -f input_file -o output_file\n");
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

    }
  }
  else{

      printf("\nIt will use default values:\n");
  }

  printf("Sort_State_Machine_NN -p %s -f %s -o %s\n",
	inputs->path,inputs->environment,inputs->output);

  return(0);

}



