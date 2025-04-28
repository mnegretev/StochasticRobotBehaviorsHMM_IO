/********************************************************
*	basics_vqs_vision.h				*
*							*
*							*
*		University of Mexico U.N.A.M.		*
*			Jesus Savage			*
*							*
*				10/24/2003		*
*				11/20/2006		*
*********************************************************
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define VQ_DEBUG 
#define EPS 0.0001
#define NUM_MAX_MODIFICATIONS 300
#define NUM_MAX_ITERATIONS NUM_MAX_MODIFICATIONS*10
#define SHOW_DISTORTION 0
#define NUM_SONARS 16

#define NUM_CENTROIDS_SONAR 64
#ifndef PI
#define PI 3.141592654
#endif
#define NUM_MAX_CENTROIDS 1024
#define NUM_SONARS 16
#define INIT_ANGLE 0.19634954f
#define SIZE_LINE 10000
#define ROBOT_RADIO 2
#define EPS_ANGLE (float) (2*PI)/100.0f
#define NUM_LINE 30.0f
//#define VQ_DEBUG 
#define EPS 0.0001
#define NUM_SONARS 16
#define NUM_STATES 64
#define NULL_PROB 0.00001f  /* Null transition probability */
#define NULL_PROB_TRANS 0.0000f  /* Null transition probability */
#define NULL_PROB_OBS 0.00001f  /* Null transition probability */
#define ROBOTS_RADIO 2
#define THRESHOLD_LINE (float) ROBOTS_RADIO/4
#define NUM_MAX_OBSERVATIONS 100
#define LARGEST_POSITIVE 0x7fffffff
#define NUM_MAX_SENSORS 512
#define VQ_SPECS 1


extern char **alloc_matrix_char(int row,int col);
extern float **alloc_matrix(int row,int col),*alloc_vector(int len);
extern double **alloc_matrix_double(int row,int col),*alloc_vector_double(int len);
extern int *alloc_vector_int(int len),**alloc_matrix_int(int row, int col);
extern void free_matrix(float **m,int row);
extern void free_matrix_double(double **m,int row);
extern void free_matrix_int(int **m,int row);
extern void free_vector_double(double *trans);
extern void free_vector_int(int *q);


typedef struct _raw{
        int region;
        float x,y,theta,sensors[NUM_MAX_SENSORS];
} Raw;


typedef struct _centroid{
        int num;
        float x,y,theta,sensors[NUM_MAX_SENSORS];
} Centroid;


void show_help(char *file){
 char string[100];

 sprintf(string,"cat %s.hlp",file);
 system(string);

}



float get_distance_points(float x,float y,float x1,float y1){

 float distance;
 // it calculates the distance
 distance=(float)sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
 //printf("Distance: %f\n",distance);

 return(distance);
}



int get_closest_centroid(int num_centroids,Centroid *centroids,float x, float y){

 int i,id_cnt;
 float smallest_distance,distance;
 
 smallest_distance=get_distance_points(centroids[1].x,centroids[1].y,x,y);
 id_cnt=1;

 for(i=2;i<= num_centroids;i++){
	 distance=get_distance_points(centroids[i].x,centroids[i].y,x,y);
	 if(distance<smallest_distance){
		 smallest_distance=distance;
		 id_cnt=i;
	 }
 }

 return(id_cnt);
}


int get_centroid_place(int num_obs, Raw *observations, int num_centroids, Centroid *centroids){

 float x,y,theta;
 int i;
 
 x=observations[num_obs].x;
 y=observations[num_obs].y;
 theta=observations[num_obs].theta;

 i=get_closest_centroid(num_centroids,centroids,x,y);
 
 if(observations[num_obs].region != -1)
	 observations[num_obs].region=centroids[i].num;
 
 //printf("sc x:%.3f, y:%.3f,  rad:%.3f\n",x,y,theta);
 //printf("real closest centroid:%d\n",observations[num_obs].region);

 return(observations[num_obs].region);

}



 /* it reads the points */
int get_data_raw(char *input,Raw *vectors)
{
 int num_vectors=1,num_file=1;
 char str1[32],str2[32],input_file[300];
 FILE *fp2;
 float x,y,theta,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15,s16;
 int num,region;
 
 while(1){

        /* It opens the file that contains the data */
#ifndef LAPTOP
	 sprintf(input_file,"d:/observations/%s",input);
#else
	 sprintf(input_file,"c:/observations/%s",input);
#endif
        //printf("FILE: %s\n",input_file);

        fp2=fopen(input_file,"r");
        if(fp2==0){
             // printf("\n Can not open %s ",input_file);
             return(0);
        }


        /* it reads the data */
        while(1){
 	  if(fscanf(fp2,"%s%d%d%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%s",
           str1,&num,&region,&x,&y,&theta,&s1,&s2,&s3,&s4,&s5,&s6,&s7,&s8,
	       &s9,&s10,&s11,&s12,&s13,&s14,&s15,&s16,str2)==EOF){

                        fclose(fp2);
 			return(num_vectors);
          }

          vectors[num_vectors].region=region;
          vectors[num_vectors].x=x;
          vectors[num_vectors].y=y;
          vectors[num_vectors].theta=theta;
          vectors[num_vectors].sensors[1]=s1;
          vectors[num_vectors].sensors[2]=s2;
          vectors[num_vectors].sensors[3]=s3;
          vectors[num_vectors].sensors[4]=s4;
          vectors[num_vectors].sensors[5]=s5;
          vectors[num_vectors].sensors[6]=s6;
          vectors[num_vectors].sensors[7]=s7;
          vectors[num_vectors].sensors[8]=s8;
          vectors[num_vectors].sensors[9]=s9;
          vectors[num_vectors].sensors[10]=s10;
          vectors[num_vectors].sensors[11]=s11;
          vectors[num_vectors].sensors[12]=s12;
		  vectors[num_vectors].sensors[13]=s13;
          vectors[num_vectors].sensors[14]=s14;
          vectors[num_vectors].sensors[15]=s15;
          vectors[num_vectors].sensors[16]=s16;
                                                                                                        

/*
          printf("vectors[%d].region %d\n",
                        num_vectors,vectors[num_vectors].region);
	 
          printf("vectors[%d].x %f\n",num_vectors,vectors[num_vectors].x);
          printf("vectors[%d].y %f\n",num_vectors,vectors[num_vectors].y);
          printf("vectors[%d].theta %f\n",
                                num_vectors,vectors[num_vectors].theta);

          for(j=1;j<=NUM_SONARS;j++)
                printf("vectors[%d][%d] %f\n",num_vectors,j,
                                vectors[num_vectors].sensors[j]);
*/
         
          num_vectors++;

        }

 }

}

int get_size_raw(char *input)
{
 int flag;
 int num_vectors=0,num_file=1;
 char str1[32],str2[32],input_file[300];
 FILE *fp2;
 float x,y,theta,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15,s16;
 
 int num,region;


 while(1){

        /* It opens the file that contains the raw data */
#ifndef LAPTOP
	 sprintf(input_file,"d:/observations/%s",input);
#else
	sprintf(input_file,"c:/observations/%s",input);
#endif
        //printf("FILE: %s\n",input_file);

        fp2=fopen(input_file,"r");
        if(fp2==0){
             printf("\n Can not open %s \n",input_file);
             return(0);
        }

        flag=1;

        /* it reads all the file to find the number of vectors */

          while(flag){

	 	if(fscanf(fp2,"%s%d%d%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%s",
            		str1,&num,&region,&x,&y,&theta,&s1,&s2,&s3,&s4,&s5,
			&s6,&s7,&s8,&s9,&s10,&s11,&s12,&s13,&s14,&s15,&s16,
                                                        str2)==EOF){

                        fclose(fp2);
                        flag=0;
 						return(num_vectors);
                }
                num_vectors++;
          }
 }

}



// it reads the sonar centroids
int read_sonar_centroids(char *str1, Centroid *vectors,int size_sonar,int num_sonars,int region){
 int num,num_vectors,j;
 char file_centroids[200];
 char dummy1[100];
 FILE *fpr;
 int flag;
 float s1;

#ifndef LAPTOP
 if(region==0)
	sprintf(file_centroids,"d:/observations/%s_vq_sonars_%d_%d.dat",str1,size_sonar,num_sonars);
 else
	sprintf(file_centroids,"d:/observations/%s_vq_sonars_%d_%d_%d.dat",str1,size_sonar,num_sonars,region);
#else
 if(region==0)
	sprintf(file_centroids,"c:/observations/%s_vq_sonars_%d_%d.dat",str1,size_sonar,num_sonars);
 else
	sprintf(file_centroids,"c:/observations/%s_vq_sonars_%d_%d_%d.dat",str1,size_sonar,num_sonars,region);

#endif

 printf("\n *** Sonar centroid %s\n",file_centroids);

 
 if((fpr=fopen(file_centroids,"r")) == NULL){
        printf("File %s can not be open\n",file_centroids);
        exit(0);
 }

 num_vectors=1;
 while(1){

	      if(fscanf(fpr,"%s%d",dummy1,&num)==EOF){
                        fclose(fpr);
 						return(num_vectors-1);
          }

		  for(j=1;j<=num_sonars;j++){
				fscanf(fpr,"%f",&s1);
				vectors[num_vectors].sensors[j]=s1;
				//printf("vectors[%d].sensors[%d] %f\n",num_vectors,j,vectors[num_vectors].sensors[j]);
		  }

		  flag=1;
		  while(flag==1){
			fscanf(fpr,"%s",dummy1);
			if(strcmp(")",dummy1) == 0)flag=0;
		  }
     
		  vectors[num_vectors].num=num;
	  
		  /*printf("sonar centroid[%d].num %d\n",
                        num_vectors,vectors[num_vectors].num);

          for(j=1;j<=NUM_SONARS;j++)
                printf("sonar centroid[%d][%d] %f\n",num_vectors,j,
                                vectors[num_vectors].sensors[j]);
		  */

	      num_vectors++;

 }


}


// it reads the vision centroids
int read_vision_centroids(char *str1, Centroid *centroids, int size_vectors, int size_quantizer,char *path){
 int num,num_vectors,j;
 char file_centroids[300];
 char dummy1[100];
 FILE *fpr;
 int flag;
 float s1;

 sprintf(file_centroids,"%svq_images_%s_%d.dat",path,str1,size_quantizer);

 //printf("\n *** Vision centroid %s\n",file_centroids);

 
 if((fpr=fopen(file_centroids,"r")) == NULL){
        printf("File %s can not be open\n",file_centroids);
        exit(0);
 }

 num_vectors=1;
 while(1){

	          if(fscanf(fpr,"%s%d",dummy1,&num)==EOF){
                        fclose(fpr);
 			return(num_vectors-1);
          	  }

		  for(j=1;j<=size_vectors;j++){
				fscanf(fpr,"%f",&s1);
				centroids[num_vectors].sensors[j]=s1;
				//printf("centroids[%d].sensors[%d] %f\n",num_vectors,j,centroids[num_vectors].sensors[j]);
		  }

		  flag=1;
		  while(flag==1){
			fscanf(fpr,"%s",dummy1);
			if(strcmp(")",dummy1) == 0)flag=0;
		  }
     
		  centroids[num_vectors].num=num;
	  
 	       	  //for(j=1;j<=size_vectors;j++)
				//printf("centroids[%d].sensors[%d] %f\n",num_vectors,j,centroids[num_vectors].sensors[j]);

	      	  num_vectors++;

 }


}


// it reads the centroids
int read_centroids(char *str1, Centroid *centroids, int size_vectors, int size_quantizer,char *path){
 int num,num_vectors,j;
 char file_centroids[300];
 char dummy1[100];
 FILE *fpr;
 int flag;
 float s1;

 sprintf(file_centroids,"%s%s_%d.dat",path,str1,size_quantizer);

 printf("\n *** Centroid %s\n",file_centroids);


 if((fpr=fopen(file_centroids,"r")) == NULL){
        printf("File %s can not be open\n",file_centroids);
        exit(0);
 }

 num_vectors=1;
 while(1){

                  if(fscanf(fpr,"%s%d",dummy1,&num)==EOF){
                        fclose(fpr);
                        return(num_vectors-1);
                  }

                  for(j=1;j<=size_vectors;j++){
                                fscanf(fpr,"%f",&s1);
                                centroids[num_vectors].sensors[j]=s1;
                                printf("centroids[%d].sensors[%d] %f\n",num_vectors,j,centroids[num_vectors].sensors[j]);
                  }

                  flag=1;
                  while(flag==1){
                        fscanf(fpr,"%s",dummy1);
                        if(strcmp(")",dummy1) == 0)flag=0;
                  }

                  centroids[num_vectors].num=num;

                  //for(j=1;j<=size_vectors;j++)
                                //printf("centroids[%d].sensors[%d] %f\n",num_vectors,j,centroids[num_vectors].sensors[j]);

                  num_vectors++;

 }


}





double abs1(double x)
{
 double y;
 if(x < (float) 0.0) y = - x;
 else y=x;
 return(y);
}


/* gets the distance of the vectors */
double distance_vector_itself(int q,float *vector,double *distance)
{
 int m;

 *distance=0;

 for(m=1;m<=q;m++){
        *distance = *distance + vector[m]*vector[m];
 }

 *distance= (float) sqrt(*distance);
 /* printf("\n distance %f",*distance);*/

 return(*distance);
}




/* gets the distance of the vectors */
double distance_vector(int q,float vector[],float vector_pattern[],double *distance)
{
 int m;
 
 *distance=0;

 for(m=1;m<=q;m++){

        *distance = *distance + (vector[m]-vector_pattern[m])*(vector[m]-vector_pattern[m]);
        //printf("\n distance_vector vector %f vector_patt %f",vector[m],vector_pattern[m]);
 }

 *distance=sqrt(*distance);
 //printf("\n distance %f",*distance);

 return(*distance);
}


/* finds the closest lpc pattern to the input correlations */
void find_closest_pattern(float vector[],float **vector_patterns,int q,
						  int num_patterns,double *distance_smallest,
                                int *index_smallest)
{
 int i;
 double dist,smallest;
 int index;

 //printf("\n 1");
 distance_vector(q,vector,vector_patterns[1],&smallest);
 index=1;

 for(i=2;i<num_patterns+1;i++){
        //printf("\n %d",i);
        distance_vector(q,vector,vector_patterns[i],&dist);

        if(dist < smallest){
                smallest=dist;
                index=i;
        }
 }
 *distance_smallest=smallest;
 *index_smallest=index;

}



// generates a uniform random variable
float generaR(float Min,float Max){
 float n;
 //int BIG= 0x7FFFFFFF;
 int BIG= RAND_MAX;

#ifdef LINUX
 n=Min+ ((float) random()/(float) BIG ) *(Max-Min);
#else
 n=Min+ ((float) rand()/(float) BIG ) *(Max-Min);
#endif

 return n;
}




//#define MOD1 (float) 0.99999;
//#define MOD2 (float) 1.00001;
#define MOD1 (float) 0.999999;
#define MOD2 (float) 1.000001;

/* It creates the vector quantizer */
int get_vq(Raw *vectors,int num_vectors,int vectors_size,int vq_size,
								char *vq_file,float epsilon)
{
 float **dist,distance();
 float dt,c99,c101;
 double difference,prev_difference;
 float *vector,modifier[3],*aux,eps;
 double dtli,dtl,num_spaces,nlmax,*aux1,power_2();
 double **rn,dmin;
 float **vector_patterns;
 int kj,*point,num_iterations,nl,l,lmin,bigger,*numdist,i,j,k,kk;
 int flag_part,ini,ifin;
 FILE *fp1;
 int *index_vectors;
 int flag_partition;
 

 /* It allocates the vectors and matrix used */

 if( (rn = (double **) alloc_matrix_double(vq_size+1, vectors_size+1)) == 0){
         printf("\n Memory allocation error ");
         exit(0);
 }

 if( (vector_patterns = (float **)alloc_matrix
					 (vq_size+1,vectors_size+1)) == 0){
         printf("\n Memory allocation error ");
         exit(0);
 }

 if( (dist = (float **)alloc_matrix(vq_size+1,vq_size+1)) == 0){
         printf("\n Memory allocation error ");
         exit(0);
 }

 
 if( (aux = (float *) alloc_vector(vectors_size+1)) == 0){
         printf("\n Memory allocation error ");
         exit(0);
 }

 if( (vector = (float *) alloc_vector(vectors_size+1)) == 0){
         printf("\n Memory allocation error ");
         exit(0);
 }
  
 if( (aux1 = (double *) alloc_vector_double(vectors_size+1)) == 0){
         printf("\n Memory allocation error ");
         exit(0);
 }
  
 
 if( (point= (int *) alloc_vector_int(vq_size+1)) == 0){
         printf("\n Memory allocation error ");
         exit(0);
 }

 
 if( (numdist= (int *) alloc_vector_int(vq_size+1)) == 0){
         printf("\n Memory allocation error ");
         exit(0);
 }

 if( (index_vectors= (int *) alloc_vector_int(num_vectors+1)) == 0){
         printf("\n Memory allocation error ");
         exit(0);
 }




 /* It opens the vq file */
 fp1=fopen(vq_file,"w");
 if(fp1==0){
	printf("\n Error in opening %s",vq_file);
	exit(0);
 }

 


 /* It initializes some variables */
 num_iterations=0;
 eps=(float) epsilon;		
 difference=0;
 nlmax= vq_size;
 num_spaces= vq_size;
 ini=1;
 flag_part=SHOW_DISTORTION;
 for(k=1;k<= vq_size;k++){
	point[k]=0;
 	numdist[k]=0;
 }
 for(i=1;i<=vectors_size;i++){
	aux[i]=0.0;
	aux1[i]=0.0;
 }

 modifier[1]=MOD1;
 modifier[2]=MOD2;
 c99=MOD1;
 c101=MOD2;
 dtli=(float)0.0;


 /* It finds the Main Ceptral Centroide */

 nl=2;
 kk=1;

 ifin=num_vectors;
 for(j=1;j<=ifin;j++){
	//printf("\n Vector %d",j);
	for(i=1;i<=vectors_size;i++){
	  aux1[i]=aux1[i]+ vectors[j].sensors[i];
	  //printf("\n vect[%d][%d] %f aux1 %f",j,i,vectors[j].sensors[i],aux1[i]);
 	}
 }
 
 printf("\n Number of vectors %d \n",ifin);
 
 for(i=1;i<=vectors_size;i++){
		aux[i]=(float)(aux1[i]/ifin);
		//printf("\n aux1[%d] %f average %f",i,aux1[i],aux[i]);
 }


 /* Modify the Space */
 for(j=1;j<3;j++){
	/* It modifies the centriod */
		
        for(i=1;i<=vectors_size;i++){
             vector_patterns[j][i]=aux[i]*modifier[j];
			 //printf("centroid[%d][%d] %5.15f\n",j,i,vector_patterns[j][i]);
        }
 }

 /*for(i=1;i<=vectors_size;i++){
	printf("aux[%d] %5.15f centroid[1][%d] %5.15f centroid[2][%d] %5.15f\n",
		i,aux[i],i,vector_patterns[1][i],i,vector_patterns[2][i]);       
 }
printf("\n type something\n");
scanf("%d",&j);*/



/* Separate the spaces into new partitions */
 while(nl<=nlmax){
	  dt=0.0;
	  dtl=0.0;
	  flag_partition=0;

	  for(k=1;k<=nl;k++){
		point[k]=0;
		numdist[k]=0;
 		for(i=1;i<=vectors_size;i++)rn[k][i]=0.0;
	  }

	  for(l=1;l<ifin;l++){
		/* It selects one vector */
 		for(i=1;i<=vectors_size;i++){
		  vector[i]=vectors[l].sensors[i];
          //printf("\n vectors[%d].sensors[%d] %5.12f",l,i,vectors[l].sensors[i]);
 		}

	       /* Find the vector_pattern that is closest to the vector */
	       find_closest_pattern(vector,vector_patterns,vectors_size,nl,
								&dmin,&lmin);

		index_vectors[l]=lmin;
		numdist[lmin]++;
		point[lmin]++;
		dt=(float)(dt+dmin);
		dtl=dtl+log(dmin+1.);
		if(flag_part)
			printf("\n %d index %d distortion %f total_dist %f",
				l,lmin,dmin,dtl);

		/* It adds the vectors in one region together */
		for(i=1;i<=vectors_size;i++)rn[lmin][i]=rn[lmin][i]+vector[i];

	  }

	  prev_difference=difference;
	  difference =  abs1((dtl-dtli));

#ifdef VQ_DEBUG 
	  printf("\n\n Epsilon %f Iteration %d",eps,num_iterations);
	  printf("\n\n Iteration %d",num_iterations);
	  for(l=1;l<nl+1;l++){
		printf("\n Space %d num.vect %d",l,point[l]);
	  }
	  printf("\n dist. %e previous dist. %e",dtl,dtli);
	  printf("\n difference %e prev_difference %e\n",
			difference,prev_difference);

#endif
	  /* It checks if there were partitions without vectors */
	  for(k=1;k<nl+1;k++){
	    if(numdist[k]==0){
#ifdef VQ_DEBUG 
		printf("\n '%d'is a partition without vectors",k);
#endif
		flag_partition=1;
	  	/*It finds the partion with more vectors to split it
		  into two parts */
		bigger=point[1];
		kj=1;

		for(i=2;i<nl+1;i++){
			if(point[i]> bigger){
				kj=i;
				bigger=point[i];
			}
		}

		if(num_iterations> NUM_MAX_MODIFICATIONS){
			c99=c99*MOD2;
			c101=c101*MOD1;
			kj=(int) (generaR(1,nl));
			printf("\nc99 %f c101 %f random %d",c99,c101,kj);
		}

		for(i=1;i<=vectors_size;i++){
			rn[k][i]=(rn[kj][i]*c99)/(numdist[kj]);
			rn[kj][i]=(rn[kj][i]*c101);
		  	/*printf("\n rn[%d][%d] %f", k,i,rn[k][i]);
		  	printf("\n rn[%d][%d] %f", kj,i,rn[kj][i]);*/
		}

		numdist[k]=1;
		point[k]=1;
	     }

	  }



	/* It checks if we finally found the optimum space separation */
	  //printf("\n abs1(dtl-dtli) %f ",abs1((dtl-dtli)));
	  //printf("\n abs1(difference-prev_difference) %f ",abs1(difference-prev_difference));
	  
	if(   (abs1((dtl-dtli)) >= eps) & (abs1(difference-prev_difference) >= eps) | (flag_partition == 1))
	{

  	    for(k=1;k<nl+1;k++){
			/* It updates the centroids */
			//printf("\n centroid[%d]",k);
			for(i=1;i<=vectors_size;i++){
				vector_patterns[k][i]=(float)rn[k][i]/numdist[k];
				//printf(" %f",vector_patterns[k][i]);
            }

	     }

	    num_iterations++;
	    if(num_iterations > NUM_MAX_ITERATIONS){
			eps=(float)(eps+epsilon);		
			num_iterations=0;
	    }
	    dtli=dtl;	/* dtl = total distortion */
    }
	/* An optimum partition was found */
	else{
       num_iterations=1;
	   kk=1;

	   for(k=1;k < nl+1;k++){

                /* It updates the centroids */
                for(i=1;i<=vectors_size;i++){
                        vector[i]=(float)rn[k][i]/numdist[k];

                }

	   			/* Save the patterns or modify the space */
				if(nl==vq_size){
					fprintf(fp1,"(centroid %d",k); 	
					for(i=1;i<=vectors_size;i++){
						//printf("\n %s vq[%d][%d]= %f",vq_file,k,i,vector[i]);
						fprintf(fp1," %f",vector[i]);
					}
					fprintf(fp1," )\n");
					//printf("\n");
				}

				else{
				/* Modify Again the Space */
 					for(j=1;j<3;j++){
                		/* It modifies the centroid */
						if(flag_part)printf("\n centroid[%d]",kk);
                		for(i=1;i<=vectors_size;i++){
                        			vector_patterns[kk][i]=aux[i]*modifier[j];
									if(flag_part)printf(" %f",vector_patterns[kk][i]);
                		}
						kk++;
 					}
				}
	   }
	   nl=nl+nl;
	   dtli=0.0;
 	   c99=modifier[1];
 	   c101=modifier[2];
 	   /*eps=epsilon + .001;*/

    }
 }


 fclose(fp1);



#ifdef VQ_SPECS 

 char index_file[128];
 char file_name[256];
 FILE *fp3;
 FILE *fp2;
 float big;
 float smallest = 0x7fffff;
 int index = 1;
 float distante;
 double dist_vect;
 int ind[4097];
 float temp;
 float menor;



 /* It opens the index file */
 sprintf(index_file,"%s_index",vq_file);
 fp3=fopen(index_file,"w");
 if(fp3==0){
	printf("\n Error in opening %s",index_file);
	exit(0);
 }


/* It saves each vector and its centroid */
 for(l=1;l<ifin;l++){
      fprintf(fp3,"(vector %d %d",l,index_vectors[l]);
      for(i=1;i<=vectors_size;i++){
		  
          fprintf(fp3," %f",vectors[l].sensors[i]);
      }
      fprintf(fp3," )\n");
 }


 big=0;

 /* It opens the space file */
 strcpy(file_name,vq_file);
 strcat(file_name,"_spa");
 fp2=fopen(file_name,"w");
 if(fp2==0){
        printf("\n Error in opening %s",file_name);
        exit(0);
 }

 /* It saves the number of vectors in each partion */
 for(i=1;i<=num_spaces;i++){
	/*printf("\n Space %d num.vect %d",i,point[i]);*/
	fprintf(fp2," Space %d num.vect %d\n",i,point[i]);

	for(k=1;k<=vectors_size;k++){
	  vector[k]=(float)rn[i][k];
 	}

	for(j=1;j<=num_spaces;j++){

		distance_vector(vectors_size,vector,vector_patterns[j], &dist_vect);
		dist[i][j]=(float)dist_vect;
		if(dist[i][j] > big)big=dist[i][j];
	}
 }
 
 /*printf("\n");*/
 fclose(fp2);



 /* It finds the distance between the centroids */

 /* It opens the distance file */
 strcpy(file_name,vq_file);
 strcat(file_name,"_dis");
 fp1=fopen(file_name,"w");
 if(fp1==0){
        printf("\n Error in opening %s",file_name);
        exit(0);
 }

 for(i=1;i<=num_spaces;i++){

        for(j=1;j<=num_spaces;j++){

		if(i==j){
			distance_vector_itself(vectors_size,vector_patterns[i], &dist_vect);
                	if(dist_vect < smallest){
				smallest=(float) dist_vect;
				index = i;
				printf("smallest %d %f\n",index,smallest);
			}

                	dist[i][j]=(float) dist_vect;
			printf("dist[%d][%d] %f \n",i,j,dist[i][j]);
		}
		else distance_vector(vectors_size,vector_patterns[i],vector_patterns[j], &dist_vect);
                dist[i][j]=(float) dist_vect;
		fprintf(fp1,"%f\n",dist[i][j]);
		//printf("dist[%d][%d] %f \n",i,j,dist[i][j]);
		//fprintf(fp2,"%d %d %f\n",i,j,dist[i][j]);
        }
 }

 fclose(fp1);

 printf("smallest %d %f\n",index,smallest);

 dist[index][index]=100000.0;
 for(i=1;i<=num_spaces;i++) printf("dist[%d][%d] %f \n",index,i,dist[index][i]);

 for(i=1;i<=num_spaces;i++){
	menor = dist[index][i];
 	for(j=1;j<=num_spaces;j++){
		if( menor > dist[index][j]){
			ind[i]=j;
			menor = dist[index][j];
			//printf("j %d menor %f\n",j,menor);
		} 
	}	
	//if(ind[i] == 0) ind[i]=num_spaces;
	if(ind[i] == 0) ind[i]=i;
	dist[index][ind[i]]=1000000 +1;
	//printf("sort dist[%d][%d] %f \n",index,i,dist[index][i]);
	printf("index ind[%d] %d\n",i,ind[i]);
 }


  /* It opens the sort file */
 strcpy(file_name,vq_file);
 strcat(file_name,"_srt");
 fp2=fopen(file_name,"w");
 if(fp2==0){
        printf("\n Error in opening %s",file_name);
        exit(0);
 }


fprintf(fp2,"(centroid %d",index);
for(j=1;j<=vectors_size;j++){
                //printf("vq[%d][%d]= %f\n",index,j,vector_patterns[index][j]);
                fprintf(fp2," %f",vector_patterns[index][j]);
}
fprintf(fp2," )\n");

for(i=1;i<num_spaces;i++) {
	fprintf(fp2,"(centroid %d",ind[i]);
        for(j=1;j<=vectors_size;j++){
       		//printf("vq[%d][%d]= %f \n",ind[i],j,vector_patterns[ind[i]][j]);
                fprintf(fp2," %f",vector_patterns[ind[i]][j]);
         }
         fprintf(fp2," )\n");
}

 fclose(fp2);

#endif



 /* It deallocates the vectors */
 free_matrix_double(rn,vq_size+1);
 free_matrix(vector_patterns,vq_size+1);
 /*free_matrix(dist,vq_size+1);*/
 /*free_vector(aux);*/
/*
 free_vector(vector);
 free_vector_double(aux1);
 free_vector_int(point);
 free_vector_int(numdist);
 free_vector(lpc);
 free_vector(reflex_coff);
*/
 
 return 1;

}


                                                                               
int get_size(char *input)
{
 int flag;
 int num_vectors=0,num_file=1;
 char str1[32],str2[32],input_file[300];
 FILE *fp2;
 float x,y,theta,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15,s16;
 int num,centroid;
                                                                               
                                                                               
 while(1){
                                                                               
        /* It opens the file that contains the data */
#ifndef LAPTOP
	 sprintf(input_file,"d:/observations/sonar_%s_%d.raw",input,num_file);
#else
	sprintf(input_file,"c:/observations/sonar_%s_%d.raw",input,num_file);
#endif
        printf("FILE: %s\n",input_file);
                                                                               
        fp2=fopen(input_file,"r");
        if(fp2==0){
             if(num_file==1)
             printf("\n Can not open %s \n",input_file);
             //printf("\ntotal num_vectors %d\n",num_vectors);
             return(num_vectors);
        }
        num_file++;
                                                                               
        flag=1;
                                                                               
        /* it reads all the file to find the number of vectors */
        while(flag){

		if(fscanf(fp2,"%s%d%d%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%s",
            		str1,&num,&centroid,&x,&y,&theta,&s1,&s2,&s3,&s4,&s5,&s6,&s7,&s8,
					&s9,&s10,&s11,&s12,&s13,&s14,&s15,&s16,str2)==EOF){
                                                                                                        
                        fclose(fp2);
                        flag=0;
                }
                num_vectors++;

        }
                                                                               
 }
                                                                               
}
                                                                               
                                                                               




                                                                               
 /* it reads the points */
int get_data(char *input,int flg_snr,float **vectors,int region)
{
 int flag;
 int num_vectors=1,num_file=1;
 char str1[32],str2[32],input_file[300];
 FILE *fp2;
 float x,y,theta,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15,s16;
 int num,centroid;
// int j;                                                                           
                                                                               
 while(1){
                                                                               
        /* It opens the file that contains the data */
#ifndef LAPTOP
		sprintf(input_file,"d:/observations/sonar_%s_%d.raw",input,num_file);
#else
		sprintf(input_file,"c:/observations/sonar_%s_%d.raw",input,num_file);
#endif
        //printf("FILE: %s\n",input_file);
                                                                               
        fp2=fopen(input_file,"r");
        if(fp2==0){
             // printf("\n Can not open %s ",input_file);
             printf("\ntotal num_vectors %d\n",num_vectors);
             return(num_vectors-1);
        }
        num_file++;
                                                                               
        flag=1;
                                                                               
      /* it reads the data */
      while(flag){

		  if(fscanf(fp2,"%s%d%d%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%s",
            str1,&num,&centroid,&x,&y,&theta,
                &s1,&s2,&s3,&s4,&s5,&s6,&s7,&s8,&s9,&s10,&s11,&s12,&s13,&s14,
                                                        &s15,&s16,str2)==EOF){
                        fclose(fp2);
                        flag=0;
          }


		  if(centroid==region){

			vectors[num_vectors][1]=s1;
			vectors[num_vectors][2]=s2;
			vectors[num_vectors][3]=s3;
			vectors[num_vectors][4]=s4;
			vectors[num_vectors][5]=s5;
			vectors[num_vectors][6]=s6;
			vectors[num_vectors][7]=s7;
			vectors[num_vectors][8]=s8;
			vectors[num_vectors][9]=s9;
			vectors[num_vectors][10]=s10;
			vectors[num_vectors][11]=s11;
			vectors[num_vectors][12]=s12;
			vectors[num_vectors][13]=s13;
			vectors[num_vectors][14]=s14;
			vectors[num_vectors][15]=s15;
			vectors[num_vectors][16]=s16;
                                                                               
			// It checks if uses also x,y and theta
			if(flg_snr == 1){
                        vectors[num_vectors][17]=x;
                        vectors[num_vectors][18]=y;
                        vectors[num_vectors][19]=theta;
			}
			// It checks if uses also x,y
			else if(flg_snr == 2){
                        vectors[num_vectors][17]=x;
                        vectors[num_vectors][18]=y;
			}
                                                                               
			//for(j=1;j<=NUM_SONARS;j++)
              //  printf("region %d vectors[%d][%d] %f\n",region,num_vectors,j,vectors[num_vectors][j]);
			
			num_vectors++;
		  }
                                                                               
   }
                                                                               
 }
 
 
 return(num_vectors-1);

}
                                                                               


 /* it reads the points */
int read_data(char *input,Raw *vectors)
{
 int num_vectors;
 char input_file[300],data[300];
 FILE *fp2;
 float x,y,theta;
 int num,region;
 int i;
 //int j;

                                                                              
        /* It opens the file that contains the data */
#ifndef LAPTOP
 sprintf(input_file,"d:/observations/%s.raw",input);
#else
 sprintf(input_file,"c:/observations/%s.raw",input);
#endif
        
 printf("FILE: %s\n",input_file);
                                        

 //sprintf(input_file,"%sobservations/%s",input);
 //printf("FILE: %s\n",input_file);

 fp2=fopen(input_file,"r");
 if(fp2==0){
             printf("\n Can not open %s ",input_file);
             return(0);
 }

 i=1;
 num_vectors=1;

 /* it reads the data */
 while(fscanf(fp2,"%s",data) != EOF){
		
			if(strcmp("(obs",data) == 0){
				fscanf(fp2,"%d%d%f%f%f",&num,&region,&x,&y,&theta);
				vectors[num_vectors].region=region;
				vectors[num_vectors].x=x;
				vectors[num_vectors].y=y;
				vectors[num_vectors].theta=theta;
				i=1;
				fscanf(fp2,"%s",data);
			}

			if(strcmp(")",data) != 0){
				vectors[num_vectors].sensors[i]=(float) atof(data);
				i++;
			}
			else{
				/*printf("vectors[%d].region %d\n",
                        num_vectors,vectors[num_vectors].region);
		        printf("vectors[%d].x %f\n",num_vectors,vectors[num_vectors].x);
				printf("vectors[%d].y %f\n",num_vectors,vectors[num_vectors].y);
				printf("vectors[%d].theta %f\n",
                                num_vectors,vectors[num_vectors].theta);

				for(j=1;j<i;j++)
                printf("vectors[%d][%d] %f\n",num_vectors,j,
                                vectors[num_vectors].sensors[j]);
				*/

				num_vectors++;
			}

 }

 fclose(fp2);
 return(num_vectors-1);

}


 /* it reads the points */
int read_region_data(char *input,Raw *vectors,int centroid, char *dir)
{
 int num_vectors=1,num_file=1,flag=1;
 char input_file[300],data[300];
 FILE *fp2;
 float x,y,theta;
 int num,region;
 int i;
 //int j;



 while(1){
                                                                               
        /* It opens the file that contains the data */

	sprintf(input_file,"%s%s_%d.raw",dir,input,num_file);
	printf("FILE: %s\n",input_file);
                                                                               
    fp2=fopen(input_file,"r");
    if(fp2==0){
             if(num_file==1)
             printf("\n Can not open %s \n",input_file);
             //printf("\ntotal num_vectors %d\n",num_vectors);
             return(num_vectors);
    }
    
	num_file++;
                                                                               
    flag=1;
     
    while(flag){

		
		 
		 /* it reads the data */
		if(fscanf(fp2,"%s",data) != EOF){
		
			if(strcmp("(obs",data) == 0){
				fscanf(fp2,"%d%d%f%f%f",&num,&region,&x,&y,&theta);
				if(region==centroid || centroid==0){
					vectors[num_vectors].region=region;
					vectors[num_vectors].x=x;
					vectors[num_vectors].y=y;
					vectors[num_vectors].theta=theta;
					i=1;
					fscanf(fp2,"%s",data);
				}
			}

			if(strcmp(")",data) != 0){
				if(region==centroid || centroid==0){
					vectors[num_vectors].sensors[i]=(float) atof(data);
					//printf("vectors[%d].sensors[%d] %f\n",num_vectors,i,vectors[num_vectors].sensors[i]);
					i++;
				}
			}
			else{
				if(region==centroid || centroid==0){
					//printf("vectors[%d].region %d\n",
                      //  num_vectors,vectors[num_vectors].region);
					//printf("vectors[%d].x %f\n",num_vectors,vectors[num_vectors].x);
					//printf("vectors[%d].y %f\n",num_vectors,vectors[num_vectors].y);
					//printf("vectors[%d].theta %f\n",
                      //          num_vectors,vectors[num_vectors].theta);

					//for(j=1;j<i;j++)
					//	printf("vectors[%d][%d] %f\n",num_vectors,j,
                      //          vectors[num_vectors].sensors[j]);

					num_vectors++;
				}
			}

		}
		else flag=0;
	}

	fclose(fp2);
 
 }
 
 return(num_vectors);


}






 /* it reads the points */
int get_size_region_data(char *input, int centroid, char *dir)
{
 int num_vectors=1,num_file=1;
 char input_file[300],data[300];
 FILE *fp2;
 float x,y,theta;
 int num,region;
 int i,flag=1;

 while(1){
                                                                               
        /* It opens the file that contains the data */

	 sprintf(input_file,"%s%s_%d.raw",dir,input,num_file);

        
	printf("FILE: %s\n",input_file);
                                                                               
    fp2=fopen(input_file,"r");
    if(fp2==0){
             if(num_file==1)
             printf("\n Can not open %s \n",input_file);
             //printf("\ntotal num_vectors %d\n",num_vectors);
             return(num_vectors);
    }
    
	num_file++;
                                                                               
    flag=1;
     

    /* it reads all the file to find the number of vectors */
    while(flag){

		 i=1;
		 

		 /* it reads the data */
		if(fscanf(fp2,"%s",data) != EOF){
		
			if(strcmp("(obs",data) == 0){
				fscanf(fp2,"%d%d%f%f%f",&num,&region,&x,&y,&theta);
				if((region==centroid) || (centroid==0)){
					i=1;
					fscanf(fp2,"%s",data);
				}
			}

			if(strcmp(")",data) != 0){
				if((region==centroid) || (centroid==0)){
					i++;
				}
			}
			else{
				if((region==centroid) || (centroid==0))num_vectors++;
			}

		}
		else flag=0;
	
	}
	fclose(fp2);
 
 }
	
 return(num_vectors);

}



 /* */
int get_size_data(char *input)
{
 int num_vectors=1;
 char input_file[300],data[300];
 FILE *fp2;
 float x,y,theta;
 int num,region;
 int i,flag=1;


                                                                               
        /* It opens the file that contains the data */
#ifndef LAPTOP
 sprintf(input_file,"d:/observations/%s.raw",input);
#else
 sprintf(input_file,"c:/observations/%s.raw",input);
#endif
        
 printf("FILE: %s\n",input_file);
                                                                               
 fp2=fopen(input_file,"r");
 if(fp2==0){
             printf("\n Can not open %s \n",input_file);
             //printf("\ntotal num_vectors %d\n",num_vectors);
             exit(0);
 }
                                                                                   
 flag=1;
     

 /* it reads all the file to find the number of vectors */
 while(flag){

		 i=1;
		 

		 /* it reads the data */
		if(fscanf(fp2,"%s",data) != EOF){
		
			if(strcmp("(obs",data) == 0){
					fscanf(fp2,"%d%d%f%f%f",&num,&region,&x,&y,&theta);
					i=1;
					fscanf(fp2,"%s",data);
			}

			if(strcmp(")",data) != 0){
					i++;
			}
			else{
				num_vectors++;
			}
		}
		else flag=0;
	
 }

 fclose(fp2);
 	
 return(num_vectors-1);

}



int get_size_image_vectors(char *input, int *size_vectors)
{
 int num_vectors=1;
 char input_file[300],data[300];
 FILE *fp2;
 int i;
 

                                                                               
 sprintf(input_file,"%s",input);
        
 //printf("Getting size of FILE: %s\n",input_file);
                                                                               
 fp2=fopen(input_file,"r");
 if(fp2==0){
             printf("\n Can not open %s \n",input_file);
             //printf("\ntotal num_vectors %d\n",num_vectors);
             return(0);
 }
                                                                                   
     
 /* it reads all the file to find the number of vectors */
 while(fscanf(fp2,"%s",data) != EOF){
		 

		 /* it reads the data */
			if(strcmp("(",data) == 0){
					i=1;
			}

			if(strcmp(")",data) == 0){
					*size_vectors=i-2;
					num_vectors++;
					//i=1;
			}
			else{
				i++;
			}
		
	
 }

 fclose(fp2);
 
 //printf(" Num. Vectors %d size vectors %d\n",num_vectors,*size_vectors);

 return(num_vectors-1);

}




/* it reads the image vectors */
int read_image_vectors(char *input, Raw *vectors)
{
 int num_vectors=1;
 char input_file[300],data[300];
 FILE *fp2;
 int i=1;
 

                                                                               
/* It opens the file that contains the data */
 sprintf(input_file,"%s",input);
        
 //printf("Reading FILE: %s\n",input_file);
                                                                               
 fp2=fopen(input_file,"r");
 if(fp2==0){
             printf("\n Can not open %s \n",input_file);
             //printf("\ntotal num_vectors %d\n",num_vectors);
             exit(0);
 }
                                                                                   
     
 /* it reads the image's vectors */
 while(fscanf(fp2,"%s",data) != EOF){
		 
		  //printf("data %s %d\n",data,i);

		 /* it reads the data */
			if(strcmp("(",data) == 0){
					i=1;
			}

			else if(strcmp(")",data) == 0){
					num_vectors++;
					i=1;
			}
			else{
				vectors[num_vectors].sensors[i]=(float) atof(data);
				//printf("vectors[%d].sensors[%d] %3.15f\n",num_vectors,i,vectors[num_vectors].sensors[i]);
				i++;
			}
	
 }

 fclose(fp2);
 
 //printf(" Num. Vectors %d\n",num_vectors);

 return(num_vectors-1);

}




double power_2(int num,int times)
{
 int i,time1;
 double y;

 y=(double)num;
 time1=times;
 for(i=1;i<time1;i++){
        y=(double)(y*num);
 }
 return(y);
}

 
float get_distance_sonar(Centroid c,Raw v, int flg_sonar, int num_sonars){
 int i;
 float distance;

 distance=0;

 if(flg_sonar==1){
	// it calculates the distance for x,y and theta
 	distance+=(c.x-v.x)*(c.x-v.x);
	distance+=(c.y-v.y)*(c.y-v.y);
	distance+=(c.theta-v.theta)*(c.theta-v.theta);
 }
 else if(flg_sonar==2){
	// it calculates the distance for x,y and theta
 	distance+=(c.x-v.x)*(c.x-v.x);
	distance+=(c.y-v.y)*(c.y-v.y);
}

 for(i=1;i<=num_sonars;i++){
 	// it calculates the distance for each of the sonars
 	distance+=(c.sensors[i]-v.sensors[i])*(c.sensors[i]-v.sensors[i]);
 }
 distance=(float) sqrt(distance);
 //printf("Distance: %f\n",distance);
 return(distance);
}


// it gets the closest centroid for a raw data
int get_closest_centroid_sonar(Centroid *centroids,Raw vector,int flg_sonar,int num_centroids_sonar,
								int num_sonars, float *dst){

 int i,id_cnt;
 float smallest_distance,distance;

 smallest_distance=get_distance_sonar(centroids[1],vector,flg_sonar,num_sonars);
 id_cnt=1;

 for(i=2;i <= num_centroids_sonar;i++){
         distance=get_distance_sonar(centroids[i],vector,flg_sonar,num_sonars);
         if(distance<smallest_distance){
                 smallest_distance=distance;
                 id_cnt=i;
         }
 }

 *dst=smallest_distance;
 return(id_cnt);
}
    

/* It quantizes the sonar data */
double quantize_vectors_sonar(Centroid *centroids,int num_vectors,
					Raw *vectors,int *observations, int flg_sonar,int num_centroids_sonar,int num_sonars)
{
 int i;
 double total_distance=0;
 float distance;

 for(i=1;i<=num_vectors;i++){
	observations[i]=get_closest_centroid_sonar(centroids,vectors[i],flg_sonar,num_centroids_sonar,num_sonars,&distance);
	total_distance=total_distance+distance;
 }
 
 return(total_distance);
}


/* It quantizes the image vectors */
double quantize_vectors_vision(Centroid *centroids,int num_vectors, Raw *vectors,int num_centroids_vision,
																							int size_vectors)
{
 int i;
 double total_distance=0;
 float distance;
 int flg_sonar=0;

 for(i=1;i<=num_vectors;i++){
	get_closest_centroid_sonar(centroids,vectors[i],flg_sonar,num_centroids_vision,size_vectors,&distance);
	total_distance=total_distance+distance;
 }
 
 return(total_distance);
}


double quantize_vectors_sonar_distances(Centroid *centroids,int num_vectors,
					Raw *vectors,int *observations, int flg_sonar,int num_centroids_sonar,int num_sonars,float *distances)
{
 int i;
 double total_distance=0;
 float distance;

 for(i=1;i<=num_vectors;i++){
	observations[i]=get_closest_centroid_sonar(centroids,vectors[i],flg_sonar,num_centroids_sonar,num_sonars,&distance);
	total_distance=total_distance+distance;
	distances[observations[i]]=distances[observations[i]]+distance;
 }
 
 return(total_distance);
}


// it reads the region centroids
int read_centroids_regions(char *str1, Centroid *vectors,int o_nsts){
 int num,num_vectors;
 char file_centroids[200];
 float x,y;
 char dummy1[100],dummy2[100];
 FILE *fpr;
 

#ifndef LAPTOP
 sprintf(file_centroids,"d:/observations/%s_vq_regions_%d.dat",str1,o_nsts);
#else
 sprintf(file_centroids,"c:/observations/%s_vq_regions_%d.dat",str1,o_nsts);
#endif

 //printf("Region vector quantizer %s\n",file_centroids);


 if((fpr=fopen(file_centroids,"r")) == NULL){
        printf("File %s can not be open\n",file_centroids);
        return(0);
 }

 num_vectors=1;
 while(1){
		if((fscanf(fpr,"%s%d%f%f%s",dummy1,&num,&x,&y,dummy2))==EOF){
            fclose(fpr);
 			return(num_vectors-1);
          }
          //vectors[num_vectors].num=num;
		  vectors[num_vectors].num=num_vectors;
          vectors[num_vectors].x=x;
          vectors[num_vectors].y=y;
		  //printf("%d pose centroids x %f y %f\n",
			//		vectors[num_vectors].num,vectors[num_vectors].x,vectors[num_vectors].y);
		  num_vectors++;
 }
 return(num_vectors-1);
}


void quantize_vectors_place(char *str1,int num_vectors,Raw *vectors, int num_states)
{

 int i,num_centroids;
 Centroid centroids[NUM_MAX_CENTROIDS];

 // it reads the place´s centroids
 //num_centroids=read_centroids_place(str1,centroids);
 num_centroids=read_centroids_regions(str1,centroids,num_states);
 
 for(i=1 ;i<= num_vectors; i++){
	get_centroid_place(i, vectors, num_centroids, centroids);

 }

}




int read_centroids_place(char *str1, Centroid *centroids, int num_states){
 int flag,num,i;
 char file_centroids[100];
 float x,y;
 char dummy1[100],dummy2[100];
 FILE *fpr;

#ifndef LAPTOP
 sprintf(file_centroids,"d:/observations/%s_vq_regions_%d.dat",str1,num_states);
#else
 sprintf(file_centroids,"c:/observations/%s_vq_regions_%d.dat",str1,num_states);
#endif

 //strcat(file_centroids,str1);
 //strcat(file_centroids,"_vq_regions_");
 //strcat(file_centroids,str1);
 //strcat(file_centroids,".fac"); 

 //printf("Region vector quantizer %s\n",file_centroids);

 if((fpr=fopen(file_centroids,"r")) == NULL){
	printf("File %s can not be open\n",file_centroids);
	exit(0);
 }

 flag=1;
 i=1;
 while(flag){
	if(fscanf(fpr,"%s %d %f %f %s",dummy1,&num,&x,&y,dummy2) == EOF)
		flag=0;
	else{
		centroids[i].num=num;
		centroids[i].x=x;
		centroids[i].y=y;
		//printf("%d pose centroids x %f y %f\n",centroids[i].num,centroids[i].x,centroids[i].y);
		i++;
	}

 }

 fclose(fpr);
 return(i-1); 

}


float abs1(float x)
{
 float y;
 if(x < (float) 0.0)y = - x;
 else y=x;
 return(y);
}



/* gets the distance of the vectors */
float distance_vector(int q,float *vector,float *vector_pattern,float *distance)
{
 int m;

 *distance=0;

 for(m=1;m<=q;m++){
        *distance = *distance +
                (vector[m]-vector_pattern[m])*(vector[m]-vector_pattern[m]);
        /*printf("\n vector %f vector_patt %f",vector[m],vector_pattern[m]);*/
 }

 *distance= (float) sqrt(*distance);
 /* printf("\n distance %f",*distance);*/

 return(*distance);
}





float get_distance(Centroid c,Raw v, int size_vectors){
 int i;
 float distance;

 distance=0;


 for(i=1;i<=size_vectors;i++){
        // it calculates the distance for each of the sonars
        distance+=(c.sensors[i]-v.sensors[i])*(c.sensors[i]-v.sensors[i]);
 }
 distance=(float) sqrt(distance);
 //printf("Distance: %f\n",distance);
 return(distance);
}





// it gets the closest centroid for a raw data
int get_closest_centroid(Centroid *centroids,Raw vector, int num_centroids, int size_vectors){

 int i,id_cnt;
 float smallest_distance,distance;

 smallest_distance=get_distance(centroids[1],vector,size_vectors);
 id_cnt=1;

 for(i=2;i <= num_centroids ;i++){
         distance=get_distance(centroids[i],vector,size_vectors);
         if(distance<smallest_distance){
                 smallest_distance=distance;
                 id_cnt=i;
         }
 }

 return(id_cnt);
}



/* It quantizes the data */
void quantize_vectors(Centroid *centroids,int num_vectors,
                                        Raw *vectors,int *observations, int num_centroids, int size_vectors)
{
 int i;

 for(i=1;i<=num_vectors;i++){
        observations[i]=get_closest_centroid(centroids,vectors[i],num_centroids,size_vectors);
        //printf("obs[%d] %d\n",i,observations[i]);
 }

}


