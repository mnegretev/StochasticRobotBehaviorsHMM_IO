/*

	genetics.h
       
*/


//DEFAULT VALUES
#define PTOUR 0.8
#define Lmin 0.0
#define Lmax 79.0
#define BIGx 0x7FFFFFFF
#define MAX_NUMBER_IND 2000
//#define PATH "/home/savage/observations/"
char PATH[300];

//#define PATH_VHDL "/home/savage/robots/genetics/genetics_state_machine/fgpa_implentation/"
char PATH_VHDL[300];

#define KF1 20.00 // fitness distance constant
#define KF2 10.00 // fitness number of steps constant
#define KF3 10.00 // fitness stuck constant
#define KF4 50.00 // fitness num_backward constant
#define K_MUTATION 0.05
#define K_CROSS 0.8
#define NUM_BEST 2
#define PORCENTAGE_NUM_BITS_MUT .20  // porcentage of bits that are mutated in an indivudual
#define PERCENTAGE_CROSS .1	// percentage of bits crossed if there is a cross between two individuals 
#define PERCENTAGE_MUT .1	// percentage of bits mutated if there is a mutation
#define CROSS_TYPE 3 // Crossing type 1: region z1 and z2, 2: Swap z1; 3: 2 regions z1 and z2, z2 and z4 
#define PERCENTAGE_SHARING .05 // Porcentage of the number of bits that should be different for fitness sharing
#define NUM_MAX_STATES 32
#define NUM_MAX_INPUTS 256
#define NUM_MAX_OUTPUTS 10
#define NUM_INPUTS_DESTINATION 4 // number of bits to the quantized destination -- -+ +- ++


typedef struct _cromosome_binary{
        float fitness;
        int *bits;
} cromosome_binary;



typedef struct _cromosome_potential{
        float fitness;
        float *variables;
} cromosome_potential;



typedef struct _cromosome{
        float fitness;
  	int **state;
	int **output;
} cromosome;



int **alloc_matrix_int(int row, int col)
{
    int i;
    int **m;

    m = (int **) malloc((unsigned) row*sizeof(int *));
    for (i=0; i<row; i++)
        m[i] = (int *) malloc((unsigned) col*sizeof(int));
    return m;
}

int *alloc_int(int row)
{
    int *m;

    m = (int *) malloc((unsigned) row*sizeof(int));
    return m;
}


float *alloc_float(int row)
{
    float *m;

    m = (float *) malloc((unsigned) row*sizeof(float));
    return m;
}




 //IT GENERATES RANDOM NUMBERS
float generaR(float LMin,float LMax){
float n;
int BIG= 0x7FFFFFFF;

  n=LMin+ ((float) random()/(float) BIG ) *(LMax-LMin);
  return n;
}


 // Initializes the random generator
void initialize_seed(){

 srandom((int)time((time_t *)NULL));
}



// IT CREATES THE INITIAL BINARY POPULATION
void create_pop_binary(int num_bits,int i, int **population){

  int p;

  for(p=0;p < num_bits;p++){
      population[i][p]=1 & random();
  }

}



// it sorts the population according to its fitness
void sort(int num_individuals,cromosome_binary *old_pop,int num_bits_individuals){

 int i,j,k,l;
 int tmp;
 float ftmp;


 for(l=0;l<num_individuals;l++){

        ftmp=old_pop[l].fitness;

        for(k=l+1;k<num_individuals;k++){
                if (ftmp < old_pop[k].fitness){

                        ftmp=old_pop[k].fitness;
                        old_pop[k].fitness=old_pop[l].fitness;
                        old_pop[l].fitness=ftmp;


                        for(i=0;i<num_bits_individuals;i++){
                               tmp=old_pop[k].bits[i];
                               old_pop[k].bits[i]= old_pop[l].bits[i];
                               old_pop[l].bits[i] = tmp;
                        }

                }

        }

  	printf("%d fitness %f\n",l,old_pop[l].fitness);

 }


}







// IT FINDS THE BEST INDIVIDUAL ACCORDING TO THE FITNESS

int find_best_binary(int num_individuals, cromosome *pop){

  float MaxFitness;
  int i,ibest;

  ibest=0;
  MaxFitness=pop[0].fitness;
  for(i=0;i< num_individuals;i++){
    if (pop[i].fitness> MaxFitness){
      ibest = i;
      MaxFitness = pop[i].fitness;
    }
  }
  return ibest;
}


// IT SELECTS THE INDIVIDUALS FROM THE POPULATION
int selecTourn_binary(cromosome *pop,int num_individuals){

   int i2,i1;
   float r;

    i2=(int)generaR(0.0,num_individuals);
    i1=(int)generaR(0.0,num_individuals);
    r=generaR(0.0,1);


    if (r < PTOUR){
      if (pop[i1].fitness > pop[i2].fitness)
        return i1;
      else
        return i2;
    }
    else{
      if (pop[i1].fitness > pop[i2].fitness)
        return i2;
      else
        return i1;
    }
}


// IT MUTATES AN INDIVIDUAL
int mutation_binary(cromosome_binary *new_pop, int index, float mut_factor, int num_bits_individuals, float porcentage_num_bits_mut){
  int lug;
  float num;
  float m;
  int i,j,k;
  int num_bits_mutation;

  num_bits_mutation=(int)(num_bits_individuals-1)*PERCENTAGE_MUT;
  if(num_bits_mutation==0)num_bits_mutation=1;


  i=(int)(num_bits_mutation*porcentage_num_bits_mut);
  if(i<=1)i=2;

  k= (int) generaR(0.0,i-1);

  for(j=0;j<= k; j++){
  
	i= (int) generaR(0.0,num_bits_individuals-1);
	new_pop[index].bits[i] = 1 - new_pop[index].bits[i];
  	printf("mutation individual %d num.mut %d bit %d\n",index,j,i);
  }

}


// IT CROSSOVERS BETWEEN TWO INDIVIDUALS
int crossover_binary(cromosome_binary *new_pop, int ind1, int ind2, float cross_factor, int num_bits_individuals){

  float num;
  static cromosome_binary temp;
  int i,j;
  static int flag=0;
  int z1,z2,temp_z;
  int num_bits_cross;
  int cross_type=CROSS_TYPE;
  int tmp;


  if(flag==0){
	temp.bits =  (int *) alloc_int(num_bits_individuals);
	flag=1;
  }


  num_bits_cross=(num_bits_individuals-1)*PERCENTAGE_CROSS;
  if(num_bits_cross<=1)num_bits_cross=2;

  switch(cross_type){
                case 1: 
  			z1=(int) generaR(0.0,num_bits_individuals-1);
  			z2=(int) generaR(0.0,num_bits_cross-1)+z1;
  			if(z2 > num_bits_individuals){
				z2=num_bits_individuals;
 			}

 			// it crosses the bits
 			printf("it cross bits from %d to %d of individuals %d %d\n",z1,z2,ind1,ind2);
 			for (i=z1;i<=z2;i++){
        			//temp.bits[i] = new_pop[ind1].bits[i];
        			tmp = new_pop[ind1].bits[i];
				new_pop[ind1].bits[i]=new_pop[ind2].bits[i];	
				new_pop[ind2].bits[i]=tmp;
 			}
                        break;

                case 2: 
			z1=(int) generaR(0.0,num_bits_individuals-1);
 			printf("it cross bits from 0 to %d and to the end of individuals %d %d\n",z1,ind1,ind2);
			for (i=0;i<z1;i++){
                                new_pop[ind2].bits[i]=new_pop[ind1].bits[i];
                        }
			for (i=z1;i<=num_bits_individuals;i++){
                                new_pop[ind1].bits[i]=new_pop[ind2].bits[i];
                        }
                        break;
	
                case 3: 
			z1=(int) generaR(0.0,num_bits_individuals-1);
                        z2=(int) generaR(0.0,num_bits_cross-1)+z1;
                        if(z2 > num_bits_individuals){
                                z2=num_bits_individuals;
                        }


			for (i=0;i<=num_bits_individuals;i++){
                                temp.bits[i]=new_pop[ind1].bits[i];
                        }

                        // it crosses the bits
                        printf("it cross bits from %d to %d of individuals %d to %d\n",z1,z2,ind2,ind1);
                        for (i=z1;i<=z2;i++){
                                new_pop[ind1].bits[i]=new_pop[ind2].bits[i];
                        }

			z1=(int) generaR(0.0,num_bits_individuals-1);
                        z2=(int) generaR(0.0,num_bits_cross-1)+z1;
                        if(z2 > num_bits_individuals){
                                z2=num_bits_individuals;
                        }

			// it crosses the bits
                        printf("it cross bits from %d to %d of individuals %d to %d\n",z1,z2,ind1,ind2);
                        for (i=z1;i<=z2;i++){
                                new_pop[ind2].bits[i]=temp.bits[i];
                        }
                        break;

                default:
                        break;
         }  

 

}



// IT CROSSOVERS BETWEEN TWO INDIVIDUALS
int crossover_vasconcelos(cromosome *new_pop, int ind1, int ind2, float cross_factor, int num_bits_states, int num_bits_output, int num_bits_inputs){

  static cromosome temp;
  int i,j,k;
  static int flag=0;
  int z1,z2,temp_z;

  if(flag==0){

        temp.state =  (int **) alloc_matrix_int((2<<(num_bits_states+num_bits_inputs-1)),num_bits_states);
        temp.output =  (int **) alloc_matrix_int((2<<(num_bits_states+num_bits_inputs-1)),num_bits_output);
        flag=1;
  }

  //for(j=0;j < (2<<(num_bits_states+num_bits_inputs-1)); j++){

		j=(int) generaR(0.0,(2<<(num_bits_states+num_bits_inputs-1)));
		k= (int) generaR(0.0,(2<<(num_bits_states+num_bits_inputs-1)));
                z1=(int) generaR(0.0,num_bits_states);
                z2=(int) generaR(0.0,num_bits_states);
                if(z2 < z1){
                        temp_z=z2;
                        z2=z1;
                        z1=temp_z;
                }
                // it crosses the states bits
                printf("it crosses location %d %d states %d %d individuals %d %d\n",j,k,z1,z2,ind1,ind2);
                for (i=z1;i<=z2;i++){
                        temp.state[j][i] = new_pop[ind1].state[j][i];
                        new_pop[ind1].state[j][i]=new_pop[ind2].state[k][i];
                        new_pop[ind2].state[k][i]=temp.state[j][i];
                }


		j=(int) generaR(0.0,(2<<(num_bits_states+num_bits_inputs-1)));
		k= (int) generaR(0.0,(2<<(num_bits_states+num_bits_inputs-1)));
                z1=(int) generaR(0.0,num_bits_output);
                z2=(int) generaR(0.0,num_bits_output);
                if(z2 < z1){
                        temp_z=z2;
                        z2=z1;
                        z1=temp_z;
                }
                // it crosses the output bits
                printf("it crosses locations %d %d outputs %d %d individuals %d %d\n",j,k,z1,z2,ind1,ind2);
                for (i=z1;i<z2;i++){
                        temp.output[j][i] = new_pop[ind1].output[j][i];
                        new_pop[ind1].output[j][i]=new_pop[ind2].output[k][i];
                        new_pop[ind2].output[k][i]=temp.output[j][i];
                }

}
  





 
void print_state_output(int index, int num_bits_states, int num_bits_inputs, int num_bits_output, cromosome *pop){

  int i,j;

  printf("pop[%d] \n",index);
  for(j=0;j < (2<<(num_bits_states+num_bits_inputs-1)); j++){
  	for (i=0;i<num_bits_states;i++){
     		printf("%d ",pop[index].state[j][i]);
  	}
  	for (i=0;i<num_bits_output;i++){
     		printf("%d ",pop[index].output[j][i]);
  	}
  	printf("\n");
  }

}


void fprint_state_output(int index, int num_bits_states, int num_bits_inputs, int num_bits_output, cromosome *pop, char *file_individual){

  int i,j;
  FILE *fp;

  if ((fp=fopen(file_individual,"w"))==NULL){
                fprintf(stderr,"Error opening file %s\n",file_individual);
                exit(1);
  }

  printf("\n\npop %s\n",file_individual);
  fprintf(fp,"%d %d %d\n",num_bits_states,num_bits_output,num_bits_inputs);
  printf("%d %d %d\n",num_bits_states,num_bits_output,num_bits_inputs);

  for(j=0;j < (2<<(num_bits_states+num_bits_inputs-1)); j++){
        for (i=0;i<num_bits_states;i++){
                fprintf(fp,"%d ",pop[index].state[j][i]);
                printf("%d ",pop[index].state[j][i]);
        }
        for (i=0;i<num_bits_output;i++){
                fprintf(fp,"%d ",pop[index].output[j][i]);
                printf("%d ",pop[index].output[j][i]);
        }
        fprintf(fp,"\n");
        printf("\n");
  }

  fclose(fp);

}


void fprint_state_output_hmm(int index,cromosome_potential *pop, char *file_individual,int num_bits_inputs){

  int i,j;
  int num_states,num_symbols,num_outputs;
  float sum_prb;
  FILE *fp;
  int m,n;


  if ((fp=fopen(file_individual,"w"))==NULL){
                fprintf(stderr,"Error opening file %s\n",file_individual);
                exit(1);
  }

  num_states= pop[index].variables[0];
  num_symbols= pop[index].variables[1];
  num_outputs= pop[index].variables[2];



  //printf("\n\npop %s\n",file_individual);

  fprintf(fp,"%d\n",num_states);
  //printf("Num_states %d\n",num_states);
  fprintf(fp,"%d\n",num_symbols);
  //printf("Num_symbols %d\n",num_symbols);
  fprintf(fp,"%d\n\n",num_outputs);
  //printf("Num_outputs %d\n",num_outputs);

   m=3;
   // it saves pi
   sum_prb=0.0;
   for(n=1; n <= num_states; n++){
	fprintf(fp,"%f ",pop[index].variables[m]);
	//printf(" pop. %d pi[%d] %f\n",index,n,pop[index].variables[m]);
	sum_prb=sum_prb+pop[index].variables[m];
	m++;
   }
   fprintf(fp,"\n\n");
   //printf(" sum. prb Pi %f\n\n",sum_prb);

   // it saves the A matrix
  for(j=1; j <= num_states; j++){
  	sum_prb=0.0;
	for(n=1; n <= num_states; n++){
		fprintf(fp,"%f ",pop[index].variables[m]);
        	//printf(" pop. %d a[%d][%d] %f\n",index,j,n,pop[index].variables[m]);
        	sum_prb=sum_prb+pop[index].variables[m];
		m++;
   	}
   	fprintf(fp,"\n");
   	//printf(" sum. prb A %d %f\n\n",j,sum_prb);

  }
  fprintf(fp,"\n");


  // it saves the B matrix
  for(j=1; j <= num_states; j++){
        sum_prb=0.0;
        for(n=1; n <= num_symbols; n++){
                fprintf(fp,"%f ",pop[index].variables[m]);
                //printf(" pop. %d b[%d][%d] %f\n",index,j,n,pop[index].variables[m]);
                sum_prb=sum_prb+pop[index].variables[m];
		m++;
        }
        fprintf(fp,"\n");
   	//printf(" sum. prb B %d %f\n\n",j,sum_prb);
  }
  fprintf(fp,"\n");

    // it saves the C matrix
  for(j=1; j <= num_states*num_symbols; j++){
        sum_prb=0.0;
        for(n=1; n <= num_outputs; n++){
                fprintf(fp,"%f ",pop[index].variables[m]);
                //printf(" pop. %d C[%d][%d] %f\n",index,j,n,pop[index].variables[m]);
                sum_prb=sum_prb+pop[index].variables[m];
		m++;
        }
        fprintf(fp,"\n");
        //printf(" sum. prb C %d %f\n\n",j,sum_prb);
  }


  fclose(fp);

}


void fprint_potentials(int index,int num_variables, cromosome_potential *new_pop, char *file_individual){

  int i,j;
  FILE *fp;

  if ((fp=fopen(file_individual,"w"))==NULL){
                fprintf(stderr,"Error opening file %s\n",file_individual);
                exit(1);
  }

  printf("%s\n",file_individual);
  fprintf(fp,"D0-D1-E1-E2-ETA\n");

  for (i=0;i<num_variables;i++){
	fprintf(fp,"%f ",new_pop[index].variables[i]);
	printf("%f ",new_pop[index].variables[i]);
  }
  fprintf(fp,"\n");
  printf("\n");

  fclose(fp);

}



void fprint_nn(int index,int num_variables, cromosome_potential *new_pop, char *file_individual, int num_layers, int num_nn_recurrent, 
										  int *num_nn_layer, int num_inputs_delay){

  int i,j;
  FILE *fp;

  if ((fp=fopen(file_individual,"w"))==NULL){
                fprintf(stderr,"Error opening file %s\n",file_individual);
                exit(1);
  }

  printf("%s\n",file_individual);


  fprintf(fp,"%d\n",num_layers);
  printf("num_layers %d\n",num_layers);
  fprintf(fp,"%d\n",num_nn_recurrent);
  printf("num_nn_recurrent %d\n",num_nn_recurrent);
  fprintf(fp,"%d\n",num_inputs_delay);
  printf("num_inputs_delay %d\n",num_inputs_delay);

  for(i=1;i<=num_layers+1;i++){
  	fprintf(fp,"%d\n",num_nn_layer[i]);
  	printf("num_nn_layer[%d] %d\n",i,num_nn_layer[i]);
  }


  for (i=0;i<num_variables;i++){
        fprintf(fp,"%f\n",new_pop[index].variables[i]);
        printf("%f\n",new_pop[index].variables[i]);
  }

  fclose(fp);

}



void fprint_state_output_vhdl(int num_bits_states, int num_bits_inputs, int num_bits_output, cromosome *pop, char *file_individual, int index){

  int i,j;
  FILE *fp;

  if ((fp=fopen(file_individual,"w"))==NULL){
                fprintf(stderr,"Error opening file %s\n",file_individual);
                exit(1);
  }

  printf("\n\nVHDL File %s\n",file_individual);

  fprintf(fp,"library ieee;\n");
  fprintf(fp,"use ieee.std_logic_1164.all;\n");
  fprintf(fp,"use ieee.std_logic_arith.all;\n");
  fprintf(fp,"use ieee.std_logic_unsigned.all;\n");
  fprintf(fp,"use ieee.numeric_std.all;\n");
  fprintf(fp,"entity memory_rom is\n");
  fprintf(fp,"	Port ( addr : in  STD_LOGIC_VECTOR (%d downto 0);\n",num_bits_states+num_bits_inputs-1);
  fprintf(fp,"		output : out  STD_LOGIC_VECTOR (%d downto 0));\n",num_bits_states+num_bits_output-1);
  fprintf(fp,"end memory_rom;\n\n");
  fprintf(fp,"architecture Behavioral of memory_rom is\n");
  fprintf(fp,"	type romtable is array (0 to %d) of std_logic_vector(%d downto 0);\n\n",
			(2<<(num_bits_states+num_bits_inputs-1))-1,num_bits_states+num_bits_output-1);
  fprintf(fp,"	constant romdata : romtable := (\n");

  for(j=0;j < (2<<(num_bits_states+num_bits_inputs-1))-1; j++){
	fprintf(fp,"		\"");
        for (i=0;i<num_bits_states;i++){
                fprintf(fp,"%d",pop[index].state[j][i]);
                //printf("%d ",pop[index].state[j][i]);
        }
        for (i=0;i<num_bits_output;i++){
                fprintf(fp,"%d",pop[index].output[j][i]);
                //printf("%d ",pop[index].output[j][i]);
        }
        fprintf(fp,"\",\n");
        //printf("\n");
  }

  fprintf(fp,"		\"");
  for (i=0;i<num_bits_states;i++){
                fprintf(fp,"%d",pop[index].state[j][i]);
                //printf("%d ",pop[index].state[j][i]);
  }
  for (i=0;i<num_bits_output;i++){
                fprintf(fp,"%d",pop[index].output[j][i]);
                //printf("%d ",pop[index].output[j][i]);
  }
  fprintf(fp,"\"\n");
  fprintf(fp,"		);\n\n");
  fprintf(fp,"begin\n");
  fprintf(fp,"  process (addr)\n");
  fprintf(fp,"  begin\n");
  fprintf(fp,"		output <= romdata (conv_integer(addr));\n");
  fprintf(fp,"  end process;\n");
  fprintf(fp,"end Behavioral;\n");

  fclose(fp);

}



void fprint_test_vhdl(int num_bits_states, int num_bits_inputs, int num_bits_output, cromosome *pop, char *file_individual){

  int i,j;
  FILE *fp;
  int index=0;

  if ((fp=fopen(file_individual,"w"))==NULL){
                fprintf(stderr,"Error opening file %s\n",file_individual);
                exit(1);
  }

  printf("\n\nVHDL File %s\n",file_individual);

  fprintf(fp,"library ieee;\n");
  fprintf(fp,"use ieee.std_logic_1164.all;\n");
  fprintf(fp,"use ieee.std_logic_arith.all;\n");
  fprintf(fp,"use ieee.std_logic_unsigned.all;\n");
  fprintf(fp,"use ieee.numeric_std.all;\n");
  fprintf(fp,"entity memory_rom is\n");
  fprintf(fp,"	Port ( addr : in  STD_LOGIC_VECTOR (%d downto 0);\n",num_bits_states+num_bits_inputs-1);
  fprintf(fp,"		output : out  STD_LOGIC_VECTOR (%d downto 0));\n",num_bits_states+num_bits_output-1);
  fprintf(fp,"end memory_rom;\n\n");
  fprintf(fp,"architecture Behavioral of memory_rom is\n");
  fprintf(fp,"	type romtable is array (0 to %d) of std_logic_vector(%d downto 0);\n\n",
			(2<<(num_bits_states+num_bits_inputs-1))-1,num_bits_states+num_bits_output-1);
  fprintf(fp,"	constant romdata : romtable := (\n");

  for(j=0;j < (2<<(num_bits_states+num_bits_inputs-1))-1; j++){
	fprintf(fp,"		\"");
        for (i=0;i<num_bits_states;i++){
                fprintf(fp,"%d",pop[index].state[j][i]);
                //printf("%d ",pop[index].state[j][i]);
        }
        for (i=0;i<num_bits_output;i++){
                fprintf(fp,"%d",pop[index].output[j][i]);
                //printf("%d ",pop[index].output[j][i]);
        }
        fprintf(fp,"\",\n");
        //printf("\n");
  }

  fprintf(fp,"		\"");
  for (i=0;i<num_bits_states;i++){
                fprintf(fp,"%d",pop[index].state[j][i]);
                //printf("%d ",pop[index].state[j][i]);
  }
  for (i=0;i<num_bits_output;i++){
                fprintf(fp,"%d",pop[index].output[j][i]);
                //printf("%d ",pop[index].output[j][i]);
  }
  fprintf(fp,"\"\n");
  fprintf(fp,"		);\n\n");
  fprintf(fp,"begin\n");
  fprintf(fp,"  process (addr)\n");
  fprintf(fp,"  begin\n");
  fprintf(fp,"		output <= romdata (conv_integer(addr));\n");
  fprintf(fp,"  end process;\n");
  fprintf(fp,"end Behavioral;\n");

  fclose(fp);

}





//FUNCTION TO CREATE A NEW POPULATION ACCORDING TO THE FITNESS 
void new_pop_binary(cromosome_binary *old_pop, cromosome_binary *new_pop, int num_bits_individuals, int num_individuals,
				 float mut_factor, float cross_factor,int num_best,float porcentage_num_bits_mut){

  int i,pts,j;
  int i1,i2,i3,i4;
  int ibest;
  int ii;
  float m_mut,m;
  float num;
  int k;
  float n_bits_mut;



  if (porcentage_num_bits_mut==0.0) n_bits_mut=PORCENTAGE_NUM_BITS_MUT;
  else n_bits_mut=porcentage_num_bits_mut;

  if (cross_factor==0.0) m=K_CROSS;
  else m=cross_factor;

  if (mut_factor==0.0) m_mut=K_MUTATION;
  else m_mut=mut_factor;

  for(k=0;k<num_best;k++){
    printf("it selects the best individuals %d \n",k);
        for (i=0;i<num_bits_individuals;i++){
                new_pop[k].bits[i]=old_pop[k].bits[i];
        }
  }

  for (i=num_best;i<num_individuals;i=i+2){

     // it selects two individuals from the old generation
     i1=generaR(1.0,num_individuals-1);
     i2=generaR(1.0,num_individuals-1);
     printf("%d it selects the individuals %d %d\n",i,i1,i2);

     for (ii=0;ii<num_bits_individuals;ii++){
                new_pop[i+1].bits[ii]=old_pop[i1].bits[ii];
                new_pop[i].bits[ii]=old_pop[i2].bits[ii];
     }


     // it crosses the individuals
     num= generaR(0.0,1.0);
     if (num<=m){
	//printf("it crosses individuals %d %d\n",i1,i2);
     	crossover_binary(new_pop,i+1,i,cross_factor,num_bits_individuals);
     }

     // it mutates the individuals
     num= generaR(0.0,1.0);
     if (num<=m_mut) { 
	printf("Mut. individual %d m_mut %f num %f \n",i,m_mut,num);
     	mutation_binary(new_pop,i, mut_factor,num_bits_individuals,n_bits_mut);
     }

     num= generaR(0.0,1.0);
     if (num<=m_mut) { 
	printf("Mut. individual %d m_mut %f num %f \n",i+1,m_mut,num);
     	mutation_binary(new_pop,i+1, mut_factor,num_bits_individuals,n_bits_mut);
     }

  }

}

//FUNCTION TO CREATE A NEW POPULATION ACCORDING TO THE FITNESS 
void new_pop_vasconcelos(cromosome_binary *old_pop, cromosome_binary *new_pop, int num_bits_individuals, int num_individuals,
                                 float mut_factor, float cross_factor,int num_best,float porcentage_num_bits_mut){

  int i,pts,j;
  int i1,i2,i3,i4;
  int ibest;
  int ii;
  float m_mut,m;
  float num;
  int k;
  int upper,l;
  float n_bits_mut;


  if (porcentage_num_bits_mut==0.0) n_bits_mut=PORCENTAGE_NUM_BITS_MUT;
  else n_bits_mut=porcentage_num_bits_mut;


  if (cross_factor==0.0) m=K_CROSS;
  else m=cross_factor;

  if (mut_factor==0.0) m_mut=K_MUTATION;
  else m_mut=mut_factor;

  // it selects the N individuals from the old generation
  for(k=0;k<num_individuals;k++){
    printf("It leaves the same individual %d\n",k);
    for (i=0;i<num_bits_individuals;i++){
                new_pop[k].bits[i]=old_pop[k].bits[i];
		//printf("%d ",new_pop[k].bits[i]);
    }
    //printf("\n");
  }

  upper= (num_individuals/2) + num_individuals % 2;
  for (i=0,k=1,l=num_individuals; i< upper ;i++,k++,l=l+2){

     // it selects two individuals from the old generation
     i1=i;
     i2=num_individuals-i-1;
     printf("\nGenerating individuals %d %d\n",l,l+1);
     printf("%d it selects the individuals %d %d\n",i,i1,i2);

     for (ii=0;ii<num_bits_individuals;ii++){
                new_pop[l+1].bits[ii]=old_pop[i1].bits[ii];
                new_pop[l].bits[ii]=old_pop[i2].bits[ii];
     }


     // it crosses the individuals
     num= generaR(0.0,1.0);
     if (num<=m){
        printf("it crosses individuals %d %d\n",i1,i2);
        crossover_binary(new_pop,l,l+1,cross_factor,num_bits_individuals);
     }

     // it mutates the individuals
     num= generaR(0.0,1.0);
     if (num<=m_mut) {
        printf("Mut. individual %d m_mut %f num %f \n",l,m_mut,num);
        mutation_binary(new_pop,l, mut_factor,num_bits_individuals,n_bits_mut);
     }

     num= generaR(0.0,1.0);
     if (num<=m_mut) {
        printf("Mut. individual %d m_mut %f num %f \n",l-1,m_mut,num);
        mutation_binary(new_pop,l+1, mut_factor,num_bits_individuals,n_bits_mut);
     }

  }

  if((num_individuals % 2)== 0){
   i1=num_individuals;
   l--;

   printf("\nGenerating last individual %d\n",l);
   for (ii=0;ii<num_bits_individuals;ii++){
                new_pop[l].bits[ii]=old_pop[i1].bits[ii];
   }

  }

}

//FUNCTION TO CREATE A NEW POPULATION ACCORDING TO THE FITNESS 
/*void new_pop_vasconcelos(cromosome *old_pop, cromosome *new_pop, int num_bits_states, int num_bits_inputs, int num_bits_output, 
				int num_individuals, float mut_factor, float cross_factor){

  int i,pts,j,k,l;
  int i1,i2,i3,i4;
  int ibest;
  int ii;
  float num,m,upper;
  float m_mut;


  if (cross_factor==0.0) m=K_CROSS;
  else m=cross_factor;

  if (mut_factor==0.0) m_mut=K_MUTATION;
  else m_mut=mut_factor;



  // it selects the N individuals from the old generation
  for (i=0;i<num_individuals;i++){
     for(j=0;j < (2<<(num_bits_states+num_bits_inputs-1)); j++){
        for (ii=0;ii<num_bits_states;ii++){
                new_pop[i].state[j][ii]=old_pop[i].state[j][ii];
        }
        for (ii=0;ii<num_bits_output;ii++){
                new_pop[i].output[j][ii]=old_pop[i].output[j][ii];
        }
     }
  }


  upper= (num_individuals/2) + num_individuals % 2;
  for (i=0,k=1,l=num_individuals; i< upper ;i++,k++,l=l+2){

     // it selects two individuals from the old generation
     i1=i;
     i2=num_individuals-i;
     printf("\nGenerating individuals %d %d\n",l-1,l);
     for(j=0;j < (2<<(num_bits_states+num_bits_inputs-1)); j++){
        for (ii=0;ii<num_bits_states;ii++){
                new_pop[l-1].state[j][ii]=old_pop[i1].state[j][ii];
                new_pop[l].state[j][ii]=old_pop[i2].state[j][ii];
        }
        for (ii=0;ii<num_bits_output;ii++){
                new_pop[l-1].output[j][ii]=old_pop[i1].output[j][ii];
                new_pop[l].output[j][ii]=old_pop[i2].output[j][ii];
        }
     }

     // it crosses the individuals
     num= generaR(0.0,1.0);
     if (num<=m){
	printf("\nCrosses individuals %d %d\n",i1,i2);
     	crossover_vasconcelos(new_pop,l-1,l,cross_factor,num_bits_states,num_bits_output,num_bits_inputs);
     }


     // it mutates the individuals
     num= generaR(0.0,1.0);
     if (num<=m_mut) mutation_binary(new_pop,l-1, mut_factor,num_bits_states,num_bits_output,num_bits_inputs);

     num= generaR(0.0,1.0);
     if (num<=m_mut) mutation_binary(new_pop,l, mut_factor,num_bits_states,num_bits_output,num_bits_inputs);

     //print_state_output(i-1,num_bits_states,num_bits_inputs,num_bits_output,new_pop);
     //print_state_output(i,num_bits_states,num_bits_inputs,num_bits_output,new_pop);

  }


 if((num_individuals % 2)== 0){
   i1=num_individuals;
   l--;

   printf("\nGenerating last individual %d\n",l);
     for(j=0;j < (2<<(num_bits_states+num_bits_inputs-1)); j++){
        for (ii=0;ii<num_bits_states;ii++){
                new_pop[l].state[j][ii]=old_pop[i1].state[j][ii];
        }
        for (ii=0;ii<num_bits_output;ii++){
                new_pop[l].output[j][ii]=old_pop[i1].output[j][ii];
        }
     }



}


}

*/



 //FUNCTION THAT EVALUE THE FITNESS
void setFit(cromosome_binary *indiv, int y,int nSteps,float dist, int num_stuck, int num_backward){
    double eps=1e-6;

    indiv[y].fitness= KF1/(dist+1.0) + KF2/(float)nSteps + KF3/((float)num_stuck + 1.0) + KF4/((float)num_backward + 1.0);


}


//FUNCTION THAT READS THE PARAMETERS FOR THE FUNCTION genera
void genera(char *args[],float flg_vsc){

  int num_individuals,num_bits_individuals;
  FILE *fp;
  char file_name[300],file_population[300];
  int i,j,k;
  int **population;



  strcpy(PATH,args[3]);
  // It gets the argument data
  num_individuals=atoi(args[4]);
  if(flg_vsc==1)num_individuals=num_individuals*2;

  if (num_individuals> MAX_NUMBER_IND) {
    printf("Increase MAX_NUMBER_IND in file genetics.h \n");
    exit(1);
  }

  num_bits_individuals=atoi(args[5]);
  strcpy(file_name,PATH);
  strcat(file_name,args[6]);

  // It opens the population file
  sprintf(file_population,"%s.dat",file_name);
  fp=fopen(file_population,"w");
  printf("\n\nPopulation file %s\n",file_population);

  // it initializes the seed for the random number generator
 initialize_seed();
 

  printf("num_individuals %d num_bits_individuals %d\n",num_individuals,num_bits_individuals); 

  population = (int **) alloc_matrix_int(num_individuals+1,num_bits_individuals+1);

  for(i=0;i<num_individuals;i++){

  	create_pop_binary(num_bits_individuals,i,population);

	for(k=0; k < num_bits_individuals;k++){ 
		printf("%d ",population[i][k]);
		fprintf(fp,"%d ",population[i][k]);
	}

	fprintf(fp,"\n");
	printf("\n");
 }

 fclose(fp);

}


 // it reads the file's population and its performance 
void  read_pop_binary(char *file_name, cromosome_binary *old_pop, int num_individuals, int num_bits_individuals){

 FILE *fpr,*fpp;
 char file_population[300];
 char file_fitness[300];
 int i,j,k;
 int num_states,num_output,num_inputs;
 int x;
 float distance;
 int num_stuck;
 int num_tries;
 int num_backward;
 float fitness;

 // It opens the population file	
 sprintf(file_population,"%s.dat",file_name);
 if ((fpp=fopen(file_population,"r"))==NULL){
 	     	printf("\nError opening file %s\n",file_population);
      		exit(1);
 }
 printf("\n\nRead population %s\n",file_population);

// It opens the population fitness
 sprintf(file_fitness,"%sfitness.dat",PATH);
 if ((fpr=fopen(file_fitness,"r"))==NULL){
                printf("Error opening file %s\n",file_fitness);
                exit(1);
 }


 for(k=0;k<num_individuals;k++){

	// It reads the fitness for each individual
	fscanf(fpr,"%f",&fitness);

	// It sets the individual's fitting value
	//setFit(old_pop,k,num_tries,distance,num_stuck,num_backward);
	old_pop[k].fitness=fitness;
        //printf("\n%s fitness %f\n",file_fitness,old_pop[k].fitness);

	//printf("Old population\n");
       	for(i=0;i<num_bits_individuals;i++){

                	if(fscanf(fpp,"%d",&x) == EOF)
                       	 	break;
                	else{
                        	old_pop[k].bits[i]= x;
        			//printf("%d ",old_pop[k].bits[i]);
                	}
       	}
	//printf("\n");

        //printf("%s fitness %f\n",file_fitness,old_pop[k].fitness);
 }

 fclose(fpp);
 fclose(fpr);

}

// it reads the file's population and its performance 
void  read_pop_binary_transform(char *file_name, cromosome_binary *old_pop, int num_individuals, int num_bits_individuals){

 FILE *fpp;
 char file_population[300];
 char file_fitness[300];
 int i,j,k;
 int num_states,num_output,num_inputs;
 int x;
 float distance;
 int num_stuck;
 int num_tries;
 int num_backward;
 float fitness;

 // It opens the population file        
 sprintf(file_population,"%s.dat",file_name);
 if ((fpp=fopen(file_population,"r"))==NULL){
                printf("\nError opening file %s\n",file_population);
                exit(1);
 }
 printf("\n\nRead population %s\n",file_population);


 for(k=0;k<num_individuals;k++){

        for(i=0;i<num_bits_individuals;i++){

                        if(fscanf(fpp,"%d",&x) == EOF)
                                break;
                        else{
                                old_pop[k].bits[i]= x;
                                printf("%d ",old_pop[k].bits[i]);
                        }
        }
        printf("\n");

        //printf("%s fitness %f\n",file_fitness,old_pop[k].fitness);
 }

 fclose(fpp);

}




// it generates a new population 
void descend_binary(char *args[],int nargc, int type){

  int num_individuals,num_bits_individuals;
  FILE *fp;
  char file_name[300],file_individual[300],file_name_old[300];
  int i,j,k;
  cromosome_binary new_pop[MAX_NUMBER_IND],old_pop[MAX_NUMBER_IND];
  float mut_factor=0.0,cross_factor=0.0;
  int num_best=NUM_BEST;
  float num_best_factor;
  char file_population[300];
  float porcentage_num_bits_mut=0.0;


  // It gets the argument data
  strcat(PATH,args[2]);
  printf("PATH %s \n",PATH);

  num_individuals=atoi(args[3]);
  if (num_individuals> MAX_NUMBER_IND) {
    printf("Increase MAX_NUMBER_IND in file genetics.h \n");
    exit(1);
  }
  num_bits_individuals=atoi(args[4]);
  strcpy(file_name,PATH);
  strcpy(file_name_old,PATH);
  strcat(file_name_old,"old_");
  strcat(file_name,args[5]);
  strcat(file_name_old,args[5]);

  printf("num_individuals %d num_bits_individuals %d\n",num_individuals,num_bits_individuals);

	
  if (nargc>6){
      mut_factor=atof(args[6]);
       printf("Mutation %f\n",mut_factor);	   
  }   
  if (nargc>7){
      cross_factor=atof(args[7]);      
      printf("Cross %f \n",cross_factor);
  } 
  if (nargc>8){
      num_best_factor=atof(args[8]);
      num_best=num_best_factor*num_individuals;
      printf("Num_best factor %f num_best %d \n",num_best_factor,num_best);
  }


  if (nargc>9){
      porcentage_num_bits_mut=atof(args[9]);
      printf("Porcentage Num_bits_mutation %f \n",porcentage_num_bits_mut);
  }





  if(type==1)num_individuals=num_individuals*2;

  for(i=0;i< num_individuals+2;i++){
  	old_pop[i].bits =  (int *) alloc_int(num_bits_individuals);
  	new_pop[i].bits =  (int *) alloc_int(num_bits_individuals);
  }

 
  //printf("Read the file with population %s \n",file_name);
  read_pop_binary(file_name,old_pop,num_individuals,num_bits_individuals);
   
  // it sorts the population according to its fitness
  sort(num_individuals,old_pop,num_bits_individuals);

  // it generates a new population 
  if(type==0)
  	new_pop_binary(old_pop,new_pop,num_bits_individuals,num_individuals,mut_factor,cross_factor,num_best,porcentage_num_bits_mut);
  else
  	new_pop_vasconcelos(old_pop,new_pop,num_bits_individuals,num_individuals/2,mut_factor,cross_factor,num_best,porcentage_num_bits_mut);


  // it saves the old population
  sprintf(file_population,"%s.dat",file_name_old);
  printf("Old population %s\n",file_population);
  if ((fp=fopen(file_population,"w"))==NULL){
                printf("Error opening file %s\n",file_individual);
                exit(1);
  }
  
  for(i=0;i<num_individuals;i++){
        for(k=0; k < num_bits_individuals;k++){
                //printf("%d ",old_pop[i].bits[k]);
                fprintf(fp,"%d ",old_pop[i].bits[k]);
        }
        fprintf(fp,"\n");
        //printf("\n");
 }

 fclose(fp);

 // it saves the new population
 sprintf(file_population,"%s.dat",file_name);
 printf("New population %s\n",file_population);
 if ((fp=fopen(file_population,"w"))==NULL){
                printf("Error opening file %s\n",file_individual);
                exit(1);
 }

 for(i=0;i<num_individuals;i++){
        for(k=0; k < num_bits_individuals;k++){
                //printf("%d ",new_pop[i].bits[k]);
                fprintf(fp,"%d ",new_pop[i].bits[k]);
 	}

        fprintf(fp,"\n");
        //printf("\n");
 }

 fclose(fp);

 // It writes the fitness file of the old population
 sprintf(file_individual,"%sfitness_generation.dat",PATH);
 printf("Fitness file %s\n",file_individual); 
 if ((fp=fopen(file_individual,"w"))==NULL){
                printf("Error opening file %s\n",file_individual);
                exit(1);
 }

 //printf("\n\npop %s\n",file_individual);
 for(i=0;i<num_individuals;i++){
  	fprintf(fp,"%s_%d.dat %f\n",file_name_old,i,old_pop[i].fitness);
 }

 fclose(fp);

}



// it generates a new population 
/*void descend_vasconcelos(char *args[],int nargc){

  int num_individuals,num_bits_states,num_bits_output,num_bits_inputs;
  FILE *fp;
  char file_name[300],file_individual[300],file_name_old[300];
  int i,j,k;
  cromosome new_pop[MAX_NUMBER_IND],old_pop[MAX_NUMBER_IND];
  float mut_factor=0.0,cross_factor=0.0;



  // It gets the argument data
  num_individuals=atoi(args[2]);
  if (num_individuals> MAX_NUMBER_IND) {
    printf("Increase MAX_NUMBER_IND in file gen_asm.h \n");
    exit(1);
  }
  num_bits_states=atoi(args[3]);
  num_bits_output=atoi(args[4]);
  num_bits_inputs=atoi(args[5]);
  strcpy(file_name,PATH);
  strcpy(file_name_old,PATH);
  strcat(file_name_old,"old_");
  strcat(file_name,args[6]);
  strcat(file_name_old,args[6]);

  printf("num_individuals %d num_bits_states %d num_bits_output %d num_bits_inputs %d\n",
        num_individuals,num_bits_states,num_bits_output,num_bits_inputs);


	
  if (nargc>7){
      mut_factor=atof(args[7]);
       printf("Mutation %f\n",mut_factor);	   
  }   
  if (nargc>8){
      cross_factor=atof(args[8]);      
      printf("Cross %s \n",args[8]);
  } 

  num_individuals=num_individuals*2;
  for(i=0;i< num_individuals;i++){
  	old_pop[i].state =  (int **) alloc_matrix_int((2<<(num_bits_states+num_bits_inputs-1)),num_bits_states);
  	old_pop[i].output =  (int **) alloc_matrix_int((2<<(num_bits_states+num_bits_inputs-1)),num_bits_output);
  	new_pop[i].state =  (int **) alloc_matrix_int((2<<(num_bits_states+num_bits_inputs-1)),num_bits_states);
  	new_pop[i].output =  (int **) alloc_matrix_int((2<<(num_bits_states+num_bits_inputs-1)),num_bits_output);
  }

 
  printf("Read the file with population %s \n",file_name);
  read_pop_binary(file_name,old_pop,num_bits_states,num_bits_inputs,num_bits_output,num_individuals);

  // it sorts the population according to its fitness
  sort(num_individuals,old_pop,num_bits_states,num_bits_inputs,num_bits_output);
   
  // it generates a new population 
  new_pop_vasconcelos(old_pop,new_pop,num_bits_states,num_bits_inputs,num_bits_output,num_individuals/2,mut_factor,cross_factor);


  for(i=0;i<num_individuals;i++){
	// it saves the old population
        sprintf(file_individual,"%s_%d.dat",file_name_old,i);
  	fprint_state_output(i,num_bits_states,num_bits_inputs,num_bits_output,old_pop,file_individual);

  }

  for(i=0;i<num_individuals;i++){

	// it saves the new population
        sprintf(file_individual,"%s_%d.dat",file_name,i);
  	fprint_state_output(i,num_bits_states,num_bits_inputs,num_bits_output,new_pop,file_individual);

  }

  // It writes the VHDL file
 sprintf(file_individual,"%smemory_rom.vhd",PATH_VHDL);
 fprint_state_output_vhdl(num_bits_states,num_bits_inputs,num_bits_output,new_pop,file_individual);

 // It writes the fitness file of the old population
 sprintf(file_individual,"%sfitness_population.dat",PATH);
 printf("\nFitness file %s\n",file_individual); 
 if ((fp=fopen(file_individual,"w"))==NULL){
                printf("Error opening file %s\n",file_individual);
                exit(1);
 }

 //printf("\n\npop %s\n",file_individual);
 for(i=0;i<num_individuals;i++){
  	fprintf(fp,"%s_%d.dat %f\n",file_name_old,i,old_pop[i].fitness);
  	//printf("%s_%d.dat %f\n",file_name_old,i,old_pop[i].fitness);
 }

 fclose(fp);

  
}

*/

void transform(cromosome_binary *old_pop, cromosome *new_pop, int num_bits_states, int num_bits_inputs, int num_bits_output, int num_individuals){

  int i,j;
  int k,l;

  for(k=0;k<num_individuals;k++){
    i=0;
    printf("Individuals %d \n",k);
    for(j=0;j < (2<<(num_bits_states+num_bits_inputs-1)); j++){
        for (l=0;l<num_bits_states;l++){
                new_pop[k].state[j][l]=old_pop[k].bits[i];
		printf("%d ",new_pop[k].state[j][l]);
		i++;
        }
        for (l=0;l<num_bits_output;l++){
                new_pop[k].output[j][l]=old_pop[k].bits[i];
                printf("%d ",new_pop[k].output[j][l]);
		i++;
        }
	printf("\n");
    }
  }

}



// it transforms the bits to an structure that the potential field uses  
void  transform_pts(cromosome_binary *old_pop,cromosome_potential *new_pop,int num_bits_variables,int num_bits_fractions,int num_bits_individuals,
			int num_individuals, int num_variables){

  int i,j;
  int k,l;
  int bits[100];
  float var,frac2;
  int m=0;

  
  frac2= 2 << num_bits_fractions;

  for(k=0;k<num_individuals;k++){
    i=0;
    //printf("Individual %d \n",k);
    // first it gets the most significant bits
    for(m=0; m < num_variables; m++){
    	//printf("variable %d ",m);
    	for(j=0;j < num_bits_variables; j++){
		bits[j]=old_pop[k].bits[i];
		//printf("%d",bits[j]);
        	i++;
    	} 
  
    	var=0;
    	for(j=num_bits_variables-1,l=0;j >= 1; j--,l++){
		var=bits[j]*(2 << l)+var;
    	} 

	if(bits[j]==0) var= var/frac2 ;
  	else var= -var/frac2 ;

    	new_pop[k].variables[m]=var;
    	//printf(" %f\n ",new_pop[k].variables[m]);
   }

  }

}



// it transforms the bits to an structure that the potential field uses  
void  transform_pts_hmm(cromosome_binary *old_pop,cromosome_potential *new_pop, int num_variables,
		int num_bits_variables, int num_individuals, int num_states, int num_outputs, int num_symbols){

  int i,j;
  int k,l;
  int bits[100];
  float var,frac2=1.0;
  int m=0;
  //int num_states,num_inputs,num_outputs;
  int vari;
  float sum;
  int ini,n,nn;
  float sum_prb;




  for(k=0;k<num_individuals;k++){
    printf("Individual %d \n",k);

  // it gets first num_states
  	i=0;

  	new_pop[k].variables[0]=num_states;
	//printf("\nnum_states %d\n",num_states);
	if(num_states > NUM_MAX_STATES){
		printf("Increse NUM_MAX_STATES > %d in genetics.h \n",num_states);
		exit(0);
	}

	printf("num_bits_variables %d\n",num_bits_variables);
  	
  	new_pop[k].variables[1]=num_symbols;
	//printf("Num. Symbols %d\n",num_symbols);

  	new_pop[k].variables[2]=num_outputs;

	//printf("\nnum_outputs %d\n",num_outputs);
	if(num_outputs > NUM_MAX_OUTPUTS){
		printf("Increse NUM_MAX_OUTPUTS > %d in genetics.h \n",num_outputs);
		exit(0);
	}

	printf("\n\nNum_states %d num_symbols %d num_outputs %d\n",num_states,num_symbols,num_outputs);

 
	// it gets the components of Pi
	m=3;
	sum=0.0;
	ini=m-1;

	for(n=1; n <= num_states; n++){
        	for(j=0;j < num_bits_variables; j++){
                	bits[j]=old_pop[k].bits[i];
                	//printf("%d",bits[j]);
                	i++;
        	}
 
        	var=0;
        	for(j=num_bits_variables-1,l=0;j >= 1; j--,l++){
                	var=bits[j]*(2 << l)+var;
        	}

        	var= var/frac2 + 0.001 ;
		sum=sum+var;
        	new_pop[k].variables[m]=var;
        	//printf(" pop. %d var[%d] %f\n ",k,m,new_pop[k].variables[m]);
		m++;
	}


	sum_prb=0.0;
	// normalization
	for(n=1; n <= num_states; n++){
        	new_pop[k].variables[ini+n]=new_pop[k].variables[ini+n]/sum;
		sum_prb= sum_prb + new_pop[k].variables[ini+n];
        	printf(" pop. %d pi[%d] %f\n",k,n,new_pop[k].variables[ini+n]);
		
	}
	printf(" sum. prb Pi %f\n\n",sum_prb);

	// it gets the components of A
        for(nn=1; nn <= num_states; nn++){
         
	 ini=m-1;
       	 sum=0.0;
         
	 for(n=1; n <= num_states; n++){


                for(j=0;j < num_bits_variables; j++){
                        bits[j]=old_pop[k].bits[i];
                        //printf("%d",bits[j]);
                        i++;
                }

                var=0;
                for(j=num_bits_variables-1,l=0;j >= 1; j--,l++){
                        var=bits[j]*(2 << l)+var;
                }

                var= var/frac2 + 0.001 ;
                sum=sum+var;
                new_pop[k].variables[m]=var;
                //printf(" pop. %d var[%d] %f\n ",k,m,new_pop[k].variables[m]);
                m++;
         }


         sum_prb=0.0;
         // normalization
         for(n=1; n <= num_states; n++){
                new_pop[k].variables[ini+n]=new_pop[k].variables[ini+n]/sum;
                sum_prb= sum_prb + new_pop[k].variables[ini+n];
                printf(" pop. %d a[%d][%d] %f\n",k,nn,n,new_pop[k].variables[ini+n]);

         }
         printf(" sum. prb A %d %f\n\n",nn,sum_prb);

	}


	// it gets the components of B
        for(nn=1; nn <= num_states; nn++){
         
         ini=m-1;
         sum=0.0;
         
         for(n=1; n <= num_symbols; n++){


                for(j=0;j < num_bits_variables; j++){
                        bits[j]=old_pop[k].bits[i];
                        //printf("%d",bits[j]);
                        i++;
                }

                var=0;
                for(j=num_bits_variables-1,l=0;j >= 1; j--,l++){
                        var=bits[j]*(2 << l)+var;
                }

                var= var/frac2  + 0.001;
                sum=sum+var;
                new_pop[k].variables[m]=var;
                //printf(" pop. %d var[%d] %f\n ",k,m,new_pop[k].variables[m]);
                m++;
         }


         sum_prb=0.0;
         // normalization
         for(n=1; n <= num_symbols; n++){
                new_pop[k].variables[ini+n]=new_pop[k].variables[ini+n]/sum;
                sum_prb= sum_prb + new_pop[k].variables[ini+n];
                printf(" pop. %d b[%d][%d] %f\n",k,nn,n,new_pop[k].variables[ini+n]);

         }
         printf(" sum. prb B %d %f\n\n",nn,sum_prb);

        }

	 // it gets the components of C
        for(nn=1; nn <= num_states*num_symbols; nn++){

         ini=m-1;
         sum=0.0;

         for(n=1; n <= num_outputs; n++){

                for(j=0;j < num_bits_variables; j++){
                        bits[j]=old_pop[k].bits[i];
                        //printf("%d",bits[j]);
                        i++;
                }

                var=0;
                for(j=num_bits_variables-1,l=0;j >= 1; j--,l++){
                        var=bits[j]*(2 << l)+var;
                }

                var= var/frac2  + 0.001;
                sum=sum+var;
                new_pop[k].variables[m]=var;
                //printf(" pop. %d var[%d] %f\n ",k,m,new_pop[k].variables[m]);
                m++;
         }


         sum_prb=0.0;
         // normalization
         for(n=1; n <= num_outputs; n++){
                new_pop[k].variables[ini+n]=new_pop[k].variables[ini+n]/sum;
                sum_prb= sum_prb + new_pop[k].variables[ini+n];
                printf(" pop. %d c[%d][%d] %f\n",k,nn,n,new_pop[k].variables[ini+n]);

         }
         printf(" sum. prb C %d %f\n\n",nn,sum_prb);

        }

        printf("Individual %d ",k);
  	printf("Num. variables %d num.var used %d\n",num_variables,m-3);

  }



}



void transform_state_machine_old(char *args[],int nargc){

  int num_individuals,num_bits_states,num_bits_output,num_bits_inputs;
  int num_bits_individuals;
  FILE *fp;
  char file_name[300],file_individual[300],file_name_old[300];
  int i,j,k;
  cromosome new_pop[MAX_NUMBER_IND];
  cromosome_binary old_pop[MAX_NUMBER_IND];
  int num_best=NUM_BEST;
  float num_best_factor;


  // It gets the argument data
  strcat(PATH,args[2]);
  printf("PATH %s \n",PATH);
  num_individuals=atoi(args[3]);
  if (num_individuals> MAX_NUMBER_IND) {
    printf("Increase MAX_NUMBER_IND in file genetics.h \n");
    exit(1);
  }
  num_bits_states=atoi(args[4]);
  num_bits_output=atoi(args[5]);
  num_bits_inputs=atoi(args[6]);
  num_bits_individuals=atoi(args[7]);
  strcpy(file_name,PATH);
  strcpy(file_name_old,PATH);
  strcat(file_name_old,"old_");
  strcat(file_name,args[8]);
  strcat(file_name_old,args[8]);



  for(i=0;i< num_individuals;i++){
        old_pop[i].bits =  (int *) alloc_int(num_bits_individuals+1);
  }

  for(i=0;i< num_individuals;i++){
        new_pop[i].state =  (int **) alloc_matrix_int((2<<(num_bits_states+num_bits_inputs+1)),num_bits_states);
        new_pop[i].output =  (int **) alloc_matrix_int((2<<(num_bits_states+num_bits_inputs+1)),num_bits_output);
  }


  //printf("Read the file with population %s \n",file_name);
  read_pop_binary_transform(file_name,old_pop,num_individuals,num_bits_individuals);

  // it transforms the bits to an structure that the state machine uses  
  transform(old_pop,new_pop,num_bits_states,num_bits_inputs,num_bits_output,num_individuals);

  for(i=0;i<num_individuals;i++){
        // it saves the new population
        sprintf(file_individual,"%s_%d.dat",file_name,i);
        fprint_state_output(i,num_bits_states,num_bits_inputs,num_bits_output,new_pop,file_individual);

  }

  // It writes the VHDL file
 sprintf(file_individual,"%smemory_rom.vhd",PATH_VHDL);
 fprint_state_output_vhdl(num_bits_states,num_bits_inputs,num_bits_output,new_pop,file_individual,0);

}


void transform_state_machine(char *args[],int nargc){

  int num_individuals,num_bits_states,num_bits_output,num_bits_inputs;
  int num_bits_individuals;
  FILE *fp;
  char file_name[300],file_individual[300],file_name_old[300];
  int i,j,k;
  cromosome new_pop[MAX_NUMBER_IND];
  cromosome_binary old_pop[MAX_NUMBER_IND];
  int num_best=NUM_BEST;
  float num_best_factor;


  // It gets the argument data
  strcat(PATH,args[2]);
  printf("PATH %s \n",PATH);
  num_individuals=atoi(args[3]);
  if (num_individuals> MAX_NUMBER_IND) {
    printf("Increase MAX_NUMBER_IND in file genetics.h \n");
    exit(1);
  }

  num_bits_states=atoi(args[4]);
  num_bits_output=atoi(args[5]);
  num_bits_inputs=atoi(args[6]);
  num_bits_individuals=atoi(args[7]);
  strcpy(file_name,PATH);
  strcpy(file_name_old,PATH);
  strcat(file_name_old,"old_");
  strcat(file_name,args[8]);
  strcat(file_name_old,args[8]);



  for(i=0;i< num_individuals;i++){
        old_pop[i].bits =  (int *) alloc_int(num_bits_individuals+1);
  }

  for(i=0;i< num_individuals;i++){
        new_pop[i].state =  (int **) alloc_matrix_int((2<<(num_bits_states+num_bits_inputs+1)),num_bits_states);
        new_pop[i].output =  (int **) alloc_matrix_int((2<<(num_bits_states+num_bits_inputs+1)),num_bits_output);
  }


  //printf("Read the file with population %s \n",file_name);
  read_pop_binary_transform(file_name,old_pop,num_individuals,num_bits_individuals);

  // it transforms the bits to an structure that the state machine uses  
  transform(old_pop,new_pop,num_bits_states,num_bits_inputs,num_bits_output,num_individuals);

  for(i=0;i<num_individuals;i++){
        // it saves the new population
        sprintf(file_individual,"%s_%d.dat",file_name,i);
        fprint_state_output(i,num_bits_states,num_bits_inputs,num_bits_output,new_pop,file_individual);

  }

}


void transform_state_machine_hmm(char *args[],int nargc){

  int num_individuals,num_bits_states,num_bits_output,num_bits_inputs;
  int num_bits_individuals;
  FILE *fp;
  char file_name[300],file_individual[300],file_name_old[300];
  char file_name_hmm[300];
  int i,j,k;
  cromosome_potential new_pop[MAX_NUMBER_IND];
  cromosome_binary old_pop[MAX_NUMBER_IND];
  int num_best=NUM_BEST;
  float num_best_factor;
  int num_variables;
  int num_bits_variables;
  int num_states,num_outputs;
  int num_symbols;



  // It gets the argument data
  strcat(PATH,args[2]);
  printf("PATH %s \n",PATH);

  num_individuals=atoi(args[3]);
  if (num_individuals> MAX_NUMBER_IND) {
    printf("Increase MAX_NUMBER_IND in file genetics.h \n");
    exit(1);
  }


  num_bits_variables=atoi(args[4]);
  num_states=atoi(args[5]);
  num_symbols=atoi(args[6]);
  num_outputs=atoi(args[7]);

  strcpy(file_name,PATH);
  strcpy(file_name_old,PATH);
  strcpy(file_name_hmm,PATH);
  strcat(file_name_old,"old_");
  strcat(file_name_hmm,"hmm_");
  strcat(file_name,args[8]);
  strcat(file_name_old,args[8]);
  strcat(file_name_hmm,args[8]);

  num_variables= num_states * (1 + num_states + num_symbols + num_symbols*num_outputs);
  num_bits_individuals = num_bits_variables * num_variables;
  num_variables = num_variables + 3;
  printf("Num. variables %d num.bits_individuals %d\n",num_variables,num_bits_individuals);

  for(i=0;i< num_individuals;i++){
        old_pop[i].bits =  (int *) alloc_int(num_bits_individuals);
  }

  for(i=0;i< num_individuals;i++){
        new_pop[i].variables =  (float *) alloc_float(num_variables);
  }


  //printf("Read the file with population %s \n",file_name);
  read_pop_binary_transform(file_name,old_pop,num_individuals,num_bits_individuals);

  // it transforms the bits to an structure that the hmm uses  
  transform_pts_hmm(old_pop,new_pop,num_variables,num_bits_variables,num_individuals,
                        num_states,num_outputs,num_symbols);

  for(i=0;i<num_individuals;i++){
        // it saves the new population
        sprintf(file_individual,"%s_%d.dat",file_name_hmm,i);
        fprint_state_output_hmm(i,new_pop,file_individual,num_bits_inputs);
  }


}





void transform_potentials(char *args[],int nargc){

  int num_individuals,num_variables,num_bits_fractions;
  int num_bits_individuals,num_bits_variables;
  FILE *fp;
  char file_name[300],file_individual[300],file_name_old[300];
  char file_out[300];
  int i,j,k;
  cromosome_potential new_pop[MAX_NUMBER_IND];
  cromosome_binary old_pop[MAX_NUMBER_IND];
  float mut_factor=0.0,cross_factor=0.0;
  int num_best=NUM_BEST;
  float num_best_factor;


  // It gets the argument data
  strcat(PATH,args[2]);
  printf("PATH %s \n",PATH);
  num_individuals=atoi(args[3]);
  if (num_individuals> MAX_NUMBER_IND) {
    printf("Increase MAX_NUMBER_IND in file genetics.h \n");
    exit(1);
  }
  num_bits_variables=atoi(args[4]);
  num_bits_fractions=atoi(args[5]);
  num_variables=atoi(args[6]);
  strcpy(file_name,PATH);
  strcpy(file_out,PATH);
  strcat(file_out,"pot_");
  strcat(file_name,args[7]);
  strcat(file_out,args[7]);
  strcpy(file_name_old,PATH);
  strcat(file_name_old,"old_");
  strcat(file_name_old,args[7]);



  num_bits_individuals=num_bits_variables*num_variables;

  for(i=0;i< num_individuals;i++){
        old_pop[i].bits =  (int *) alloc_int(num_bits_individuals);
  }

  for(i=0;i< num_individuals;i++){
        new_pop[i].variables =  (float *) alloc_float(num_variables);
  }


  //printf("Read the file with population %s \n",file_name);
  read_pop_binary_transform(file_name,old_pop,num_individuals,num_bits_individuals);

  // it transforms the bits to an structure that the potential field uses  
  transform_pts(old_pop,new_pop,num_bits_variables,num_bits_fractions,num_bits_individuals,num_individuals,num_variables);


  for(i=0;i<num_individuals;i++){
        // it saves the new population
        sprintf(file_individual,"%s_%d.dat",file_out,i);
        fprint_potentials(i,num_variables,new_pop,file_individual);

  }


}


void transform_nn(char *args[],int nargc){

  int num_individuals,num_variables=0,num_bits_fractions;
  int num_bits_individuals,num_bits_variables;
  FILE *fp;
  char file_name[300],file_individual[300],file_name_old[300];
  char file_out[300];
  int i,j,k;
  cromosome_potential new_pop[MAX_NUMBER_IND];
  cromosome_binary old_pop[MAX_NUMBER_IND];
  float mut_factor=0.0,cross_factor=0.0;
  int num_best=NUM_BEST;
  float num_best_factor;
  int num_layers,num_nn_recurrent,flg_weight_recurrent,num_nn_layer[20];
  int num_inputs_delay;
  int nn_1,nn_last;



  // It gets the argument data
  strcat(PATH,args[2]);
  printf("PATH %s \n",PATH);
  num_individuals=atoi(args[3]);
  if (num_individuals> MAX_NUMBER_IND) {
    printf("Increase MAX_NUMBER_IND in file genetics.h \n");
    exit(1);
  }
  num_bits_variables=atoi(args[4]);
  num_bits_fractions=atoi(args[5]);
  printf("num.bits %d num.fractions %d\n",num_bits_variables,num_bits_fractions);
  strcpy(file_name,PATH);
  strcpy(file_out,PATH);
  strcat(file_out,"nn_");
  strcat(file_name,args[6]);
  strcat(file_out,args[6]);
  strcpy(file_name_old,PATH);
  strcat(file_name_old,"old_");
  strcat(file_name_old,args[6]);
  num_layers=atoi(args[7]);
  num_nn_recurrent=atoi(args[8]);
  printf("num.layers %d num.recurrent %d\n",num_layers,num_nn_recurrent);
//  flg_weight_recurrent=atoi(args[9]);
  num_inputs_delay=atoi(args[9]);
  printf("num_inputs_delay %d\n",num_inputs_delay);

  for(i=1;i<=num_layers+1;i++){
  	num_nn_layer[i]=atoi(args[9+i]);
  	printf("nn_layer[%d] %s \n",i,args[9+i]);
  }


  nn_1= num_nn_layer[1];
  nn_last= num_nn_layer[num_layers+1];
  num_nn_layer[1] = num_nn_layer[1] * ( 1 + num_inputs_delay) + num_nn_recurrent;
  num_nn_layer[num_layers+1] = num_nn_layer[num_layers+1] +  num_nn_recurrent;
//  num_variables=(num_nn_layer[2]+num_nn_recurrent+(num_nn_layer[2]*num_inputs_delay) ) * (num_nn_layer[3]+1);
  num_variables=0;
  for(i=1;i<=num_layers;i++){
  	num_variables=num_nn_layer[i]*(num_nn_layer[i+1]+1)+num_variables;
  }
  //num_variables=(num_nn_layer[i+1]+num_nn_recurrent+1)*(num_nn_layer[i])+num_variables;
  printf("Num. Variables %d\n",num_variables);
  num_bits_individuals=num_bits_variables*num_variables;
  printf("Num_bits_individuals %d\n",num_bits_individuals);

  num_nn_layer[1]=nn_1;
  num_nn_layer[num_layers+1]=nn_last;


/*
        num_nn_layer[0] = num_inputs_sensors * ( 1 + num_inputs_delayed) + num_recurrent
        num_nn_layer[1] = 5
        num_nn_layer[2] = num_outputs + num_recurrent

	num_variables = (num_nn_layer[1]+num_recurrent+(num_nn_layer[1]*num_inputs_delayed) ) * (num_nn_layer[2]+1);
        for i in range(0, num_layers-1):
                num_variables=num_nn_layer[i]*(num_nn_layer[i+1]+1)+num_variables;
        num_variables=(num_nn_layer[i+1]+num_recurrent+1)*(num_nn_layer[i])+num_variables;
        print "Num. Variables ",num_variables

        num_bits_individuals_nn = num_bits_variables_nn*num_variables;

*/


  for(i=0;i< num_individuals;i++){
        old_pop[i].bits =  (int *) alloc_int(num_bits_individuals);
  }

  for(i=0;i< num_individuals;i++){
        new_pop[i].variables =  (float *) alloc_float(num_variables);
  }


  //printf("Read the file with population %s \n",file_name);
  read_pop_binary_transform(file_name,old_pop,num_individuals,num_bits_individuals);

  // it transforms the bits to an structure that the nn uses  
  transform_pts(old_pop,new_pop,num_bits_variables,num_bits_fractions,num_bits_individuals,num_individuals,num_variables);


  for(i=0;i<num_individuals;i++){
        // it saves the new population
        sprintf(file_individual,"%s_%d.dat",file_out,i);
        fprint_nn(i,num_variables,new_pop,file_individual,num_layers,num_nn_recurrent,num_nn_layer,num_inputs_delay);

  }


}


// it changes the fitness with fitness sharing
void sharing(int num_individuals,cromosome_binary *old_pop,int num_bits_individuals){

 int i,j,k,l;
 float tmp;
 float ftmp;
 float percentage;
 int num_sharing;
 FILE *fp;
 char file[300];


 // It re_writes the fitness file
 sprintf(file,"%spopulation_sharing.dat",PATH);
 printf("Population sharing  file %s\n",file);
 if ((fp=fopen(file,"w"))==NULL){
                printf("Error opening file %s\n",file);
                exit(1);
 }



 percentage= num_bits_individuals * PERCENTAGE_SHARING;

 for(l=0;l<num_individuals;l++){

        ftmp=0.0;
	num_sharing=0;

        for(k=0;k<num_individuals;k++){
		tmp=0;
                for(i=0;i<num_bits_individuals;i++){
                      tmp= tmp + abs(old_pop[l].bits[i] - old_pop[k].bits[i]);
                }
		if(tmp < percentage){
			ftmp= ftmp + (1.0 - (tmp/percentage));
			//ftmp= ftmp + (1.0 - ((tmp/percentage)*(tmp/percentage)));
			num_sharing++;
		}

        }

        printf("%d fitness %f ",l,old_pop[l].fitness);

	old_pop[l].fitness= old_pop[l].fitness/ftmp;

        printf("num. sharing %d sharing fitness %f\n",num_sharing,old_pop[l].fitness);
        fprintf(fp,"%d\n",num_sharing);

 }

 fclose(fp);

}



// it changes the fitness with fitness sharing 
void fitness_sharing(char *args[],int nargc, int type){

  int num_individuals,num_bits_individuals;
  FILE *fp;
  char file_name[300],file_individual[300],file_name_old[300];
  int i,j,k;
  cromosome_binary new_pop[MAX_NUMBER_IND],old_pop[MAX_NUMBER_IND];
  float mut_factor=0.0,cross_factor=0.0;
  int num_best=NUM_BEST;
  float num_best_factor;
  char file_population[300];
  float porcentage_num_bits_mut=0.0;


  // It gets the argument data
  strcat(PATH,args[3]);
  num_individuals=atoi(args[4]);
  if (num_individuals> MAX_NUMBER_IND) {
    printf("Increase MAX_NUMBER_IND in file genetics.h \n");
    exit(1);
  }
  num_bits_individuals=atoi(args[5]);
  strcpy(file_name,PATH);
  strcpy(file_name_old,PATH);
  strcat(file_name_old,"old_");
  strcat(file_name,args[6]);
  strcat(file_name_old,args[6]);

  printf("num_individuals %d num_bits_individuals %d\n",num_individuals,num_bits_individuals);


  if(type==1)num_individuals=num_individuals*2;

  for(i=0;i< num_individuals+2;i++){
        old_pop[i].bits =  (int *) alloc_int(num_bits_individuals);
        new_pop[i].bits =  (int *) alloc_int(num_bits_individuals);
  }


  //printf("Read the file with population %s \n",file_name);
  read_pop_binary(file_name,old_pop,num_individuals,num_bits_individuals);

  // it changes the fitness according to fittness sharing
  sharing(num_individuals,old_pop,num_bits_individuals);


  for(i=0;i<num_individuals;i++){
        for(k=0; k < num_bits_individuals;k++){
                //printf("%d ",old_pop[i].bits[k]);
        }
  }


 // It re_writes the fitness file
 sprintf(file_individual,"%sfitness.dat",PATH);
 printf("Fitness file %s\n",file_individual);
 if ((fp=fopen(file_individual,"w"))==NULL){
                printf("Error opening file %s\n",file_individual);
                exit(1);
 }

 //printf("\n\npop %s\n",file_individual);
 for(i=0;i<num_individuals;i++){
        fprintf(fp,"%f\n",old_pop[i].fitness);
 }

 fclose(fp);

}


