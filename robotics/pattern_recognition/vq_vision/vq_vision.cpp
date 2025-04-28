//
// vq_vision.cpp
//
// This program finds a vector quantizer of a set of points that
// represent images' readings
//
//  J. Savage, 4-15-2009
//      FI- UNAM
//




#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


#include "../include_vision/basics_vqs_vision.h"
#include "new_allocate.h"




/* it gets line inputs */
void get_inputs(int argc, char **argv,int *num_regions, char *input, char *out_file, float *epsilon, char *path, char *objects_file)
{
 int i;

/* It sets default values */
 *epsilon=(float)EPS;
 *num_regions=64;
 strcpy(input,"top");
 strcpy(path,"/home/biorobotica/observations/cmucam/training_hsi/");
 strcpy(objects_file,"NULL");
 
 

  /* reads input parameters */
  if (argc>1) {
        for(i=1;i<argc;i++){
          if (!strcmp(argv[i],"-h")){
			printf("\n Usage: vq_vision -f object -m size_vq -e cnt_convergence -p path_data -g objects_file\n");
			printf("\n Usage: ./vq_vision -f top -m 4 -e 0.0001 -p ~/observations/cmucam/training_hsi/\n");
			printf("\n Usage: ./vq_vision -f all -m 4 -e 0.0001 -p ~/observations/cmucam/training_hsi/ -g vision_objects\n");
			exit(0);
          }
          if (!strcmp(argv[i],"-m")){
                *num_regions=atoi(argv[i+1]);
          }
          if (!strcmp(argv[i],"-e")){
                *epsilon=(float) atof(argv[i+1]);
          }
          if (!strcmp(argv[i],"-f")){
                strcpy(input,argv[i+1]);
          }
          if (!strcmp(argv[i],"-p")){
                strcpy(path,argv[i+1]);
          }
	  if (!strcmp(argv[i],"-g")){
                strcpy(objects_file,argv[i+1]);
          }

        }
  }
  else{
       printf("\n Using default values");
  }
 


 sprintf(out_file,"%svq_images_%s_%d.dat",path,input,*num_regions);
        
 


 printf("\n Input '%s' output '%s' num_regions %d epsilon %f path %s objects_file %s\n\n",
			input,out_file,*num_regions, *epsilon,path,objects_file);

}


int read_objects_name(char *objects_file,char **objects_name, char *path)
{
 char input_file[300],name[300];
 FILE *fp2;
 int i;


 /* It opens the file that contains the names of the objects to be recognized */
 sprintf(input_file,"%s%s.txt",path,objects_file);

 printf("Objects FILE: %s\n",input_file);

 fp2=fopen(input_file,"r");
 if(fp2==0){
             printf("\n Can not open %s ",input_file);
             return(0);
 }

 i=1;

 /* it reads the names */
 while(fscanf(fp2,"%s",name) != EOF){
         strcpy(objects_name[i],name);
         i++;
}

fclose(fp2);

return(i-1);

}





int main(int argc,char *argv[])
{
 int num_vectors,num_regions;
 char data_file[300],vq_file[300],object[300];
 float epsilon;
 Raw *vectors,*total_vectors;
 int size_vectors;
 char path[300];
 int num_file=1;
 int flag=1;
 int num_total_vectors=0;
 int i,j,k,l;
 char objects_file[300];
 char **objects_name;
 int num_objects;
 int flag_global=0;
 int num_files[100];


 if( (objects_name = (char **) alloc_matrix_char(100, 300)) == 0){
		printf("\n Memory allocation error ");
         	exit(0);
 }


 /* it gets line inputs */
 get_inputs(argc, argv,&num_regions,object,vq_file,&epsilon,path,objects_file);

 // It checks if it creates the VQ with all the objects' trainning data
 if(strcmp(objects_file,"NULL")){
 
	// it reads the names of the objects whose VQ will be created
 
 	num_objects=read_objects_name(objects_file,objects_name,path);

	flag_global=1;
 }
 else{
 	num_objects=1;
	strcpy(objects_name[1],object);
 }


 for(i=1;i<=num_objects;i++){
         	printf("objects %s\n",objects_name[i]);
 }

 

 /* it gets the number of vectors and their size*/
 for(i=1;i<=num_objects;i++){
 	num_file=1;
	flag=1;
 	while(flag){

 		sprintf(data_file,"%simages_training_%s_%d.raw",path,objects_name[i],num_file);
 		num_vectors=get_size_image_vectors(data_file,&size_vectors);
 		printf("%s num. vectors %d size vectors %d\n",data_file,num_vectors, size_vectors); 
	
       		if(num_vectors== 0){
			if(num_file==1){
            		 	printf("\n Can not open %s \n",data_file);
			 	exit(0);
			}
       			flag=0; 
	        	//printf("\ntotal num_vectors %d\n",num_total_vectors);
    		}
		else{
        		num_file++;
			num_total_vectors=num_total_vectors+num_vectors;
			num_files[i]=num_file;
		}
 	}
 }

 printf("\ntotal num_vectors %d\n",num_total_vectors);



/* it allocates raw vectors space */
 if((vectors = (Raw *) malloc( (num_total_vectors+1) * sizeof(Raw))) == NULL){
 	     	fprintf(stdout,"Allocation error: Raw vectors");
      		return(0);
 }

 if((total_vectors = (Raw *) malloc( (num_total_vectors+1) * sizeof(Raw))) == NULL){
                fprintf(stdout,"Allocation error: Raw vectors");
                return(0);
 }



/* it reads the image vectors */
 
 num_total_vectors=0;
 for(i=1;i<=num_objects;i++){
 	for(k=1;k<num_files[i];k++){

        	sprintf(data_file,"%simages_training_%s_%d.raw",path,objects_name[i],k);
		num_vectors= read_image_vectors(data_file,vectors);
        	printf("%s num. vectors %d\n",data_file,num_vectors);

		for(j=1;j<=num_vectors;j++){
               		num_total_vectors++;
			for(l=1;l<=size_vectors;l++){
				total_vectors[num_total_vectors].sensors[l]=vectors[j].sensors[l];
		 		//printf("total_vectors[%d].sensors[%d] %f\n",num_total_vectors,l,total_vectors[num_total_vectors].sensors[l]);
			}
			
		}

 	}
 }


 
 // Initializes the random generator
 srand((int)time((time_t *)NULL));
 
 /* It creates the vector quantizer */
 get_vq(total_vectors,num_total_vectors,size_vectors,num_regions,vq_file,epsilon);

 printf("\n*** output %s ***\n\n",vq_file);



}
