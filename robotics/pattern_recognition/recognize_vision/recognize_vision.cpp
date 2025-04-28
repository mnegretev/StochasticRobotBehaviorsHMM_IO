//
// recognize_vision.cpp
//
// This program recognizes an image pattern using vector quantizers of a set of points that
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
#include "../vq_vision/new_allocate.h"

/* it gets line inputs */

int get_inputs(int argc, char **argv, char *objects_file,char *in_file,int *size_vq, char *path)
{
 int i;

 /* It sets default values */
 strcpy(objects_file,"vision_objects_rgb");
 strcpy(in_file,"images_test_hub_0");
 *size_vq=32;
 strcpy(path,"/home/biorobotica/observations/cmucam/training_hsi/");




  /* reads input parameters */
  if (argc>1) {
        for(i=1;i<argc;i++){
          if (!strcmp(argv[i],"-h")){
			  printf("recognize_vision -h\n");
			  printf("-f specifies the objects' file\n");
			  printf("-s specifies the processed image's file\n");
			  printf("-m specifies the size of the quantizer\n");
			  printf("-p specifies the path\n");
			  printf("-h shows this message\n");
			  printf("example:\n ./recognize_vision -f vision_objects -s images_test_hub_0 -m 4 -p /home/biorobotica/observations/cmucam/training_hsi/\n");
			
			  exit(1);  
          }
          if (!strcmp(argv[i],"-p")){
                strcpy(path,argv[i+1]);
          }
          if (!strcmp(argv[i],"-s")){
                strcpy(in_file,argv[i+1]);
          }
          if (!strcmp(argv[i],"-f")){
                strcpy(objects_file,argv[i+1]);
          }
	  if(!strcmp(argv[i],"-m")){
                *size_vq=atoi(argv[i+1]);
                if(*size_vq > NUM_CENTROIDS_SONAR){
                        printf("\n Increase constant NUM_CENTROIDS_SONAR >= %d\n",*size_vq);
                        exit(1);
                }
          }
       }
  }
  else{
	  printf("Using default values \n");  
  }

 printf("recognize_vision -f %s -s %s -m %d -p %s \n",objects_file,in_file,*size_vq,path);
 
 return(0);

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



double quantize_image(char **objects_name, Raw *vectors,int num_vectors,int size_vectors,int id_obj,int size_quantizer, char *path)
{
 int cnt_errors=0;
 float error=0.0f, error_real=0.0f;
 int num_centroids_vision;
 Centroid *centroids_vision;
 double t_distance=0;
 float log_lrg_negative=-10;



 /* it reads the centroids */
 /* it allocates centroids space */
 if((centroids_vision = (Centroid *)
            malloc( (NUM_MAX_CENTROIDS+1) * sizeof(Centroid))) == NULL){
      		fprintf(stdout,"Allocation error: centroids");
      		exit(0);
 }

 num_centroids_vision=
			read_vision_centroids(objects_name[id_obj],centroids_vision,size_vectors,size_quantizer,path);


	

 t_distance=quantize_vectors_vision(centroids_vision,num_vectors,vectors,num_centroids_vision,size_vectors);

 return(t_distance);

}







int main(int argc, char *argv[])
{

 char objects_file[300],in_file[300],**objects_name;
 int size_vq;
 int num_vectors;
 Centroid *centroids;
 double bigger,tdistance[NUM_MAX_CENTROIDS];
 int index=1,i;
 int num_objects;
 int size_vectors=0;
 Raw *vectors;
 char path[300];
 char data_file[300];

 
 
 /* it gets line inputs */
 get_inputs(argc,argv,objects_file,data_file,&size_vq,path);
 

 // it reads the names of the objects to be recognized
 if( (objects_name = (char **) alloc_matrix_char(30, 300)) == 0){
         printf("\n Memory allocation error ");
         exit(0);
 }

 num_objects=read_objects_name(objects_file,objects_name,path);

 for(i=1;i<=num_objects;i++){
	 printf("objects %s\n",objects_name[i]);
 }



 //it reads each the objects VQs 
 if((centroids = (Centroid *) malloc( (num_objects+1) * sizeof(Centroid))) == NULL){
      fprintf(stdout,"Allocation error: centroids");
      exit(0);
 }


/* it reads the image vectors */
 /* it gets the number of vectors and their size*/
 sprintf(in_file,"%s%s.raw",path,data_file);
 num_vectors=get_size_image_vectors(in_file,&size_vectors);
 printf("%s num. vectors %d size vectors %d\n",in_file,num_vectors, size_vectors);


 printf("Num. vectors %d size vectors %d\n",num_vectors, size_vectors); 

/* it allocates raw vectors space */
 if((vectors = (Raw *) malloc( (num_vectors+1) * sizeof(Raw))) == NULL){
 	     	fprintf(stdout,"Allocation error: Raw vectors");
      		return(0);
}

/* it reads the input image vectors */
 read_image_vectors(in_file,vectors);




 bigger=LARGEST_POSITIVE;

 for(i=1;i<=num_objects;i++){
	tdistance[i]=quantize_image(objects_name,vectors,num_vectors,size_vectors,i,size_vq,path);
 
	if(tdistance[i]<bigger){
          bigger=tdistance[i];
          index=i;
										
	}

	//printf("object %s distance %f\n",objects_name[i],tdistance[i]);

 }


 printf("\n\n ****** Winner object %s %f ***** \n",objects_name[index],tdistance[index]);
 for(i=1;i<=num_objects;i++){
	 printf("object %s distance %f\n",objects_name[i],tdistance[i]);
 }



}





