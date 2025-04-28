/************************************************
*	serial_cf.cpp				*
*						*
*	This program sends and receives 	*
*	data to/from a usb serial port		*
*						*
*	Compile: make				*
*						*
*		J. Savage			*
*		UNAM				*
*						*
*						*
*			5/30/18			*
*************************************************/


#include <stdio.h>

#define MAX_NUM_CHARACTERS 1000
#define NUM_STABLE 10
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

// global variables
int fd1,fd2;

extern void *read_serial_port(void *arg);

/* it gets line inputs */
int get_inputs(int argc, char **argv, char *port, int *baud, char *path, char *file_name, int *num_samples, float *distance)
{
 int i;
                                                                                
 /* It sets default values */
 //strcpy(port,"/dev/ttyACM0");
 strcpy(port,"/dev/ttyUSB1");
 *baud=9600;
 strcpy(path,"../sensor_data/");
 strcpy(file_name,"test_1");
 *num_samples= 100;
 *distance= 100.00; 
                                                                                
  /* reads input parameters */
  if (argc>1) {
        for(i=1;i<argc;i++){
          if (!strcmp(argv[i],"-h")){
      
		printf("Sintax: serial_cf -p port -b baudage -t path -f file -n number_samples -r real_distance \n");
     		printf("example:\nserial_cf -p /dev/ttyUSB0 -b 9600 -t ../sensor_data/ -f test_1 -n 200 -r 100.00 \n");
     		printf("Default:\nserial_cf -p /dev/ttyUSB0 -b 9600 -t ../sensor_data/ -f test_1 -n 200 -r 100.00 \n");
                exit(1);
          }
          if (!strcmp(argv[i],"-p")){
                strcpy(port,argv[i+1]);
          }
          if (!strcmp(argv[i],"-b")){
                *baud= atoi(argv[i+1]);
          }
          if (!strcmp(argv[i],"-n")){
                *num_samples= atoi(argv[i+1]);
          }
          if (!strcmp(argv[i],"-r")){
                *distance= atof(argv[i+1]);
          }
	  else if (!strcmp(argv[i],"-f")){
                strcpy(file_name,argv[i+1]);
          }
	  else if (!strcmp(argv[i],"-t")){
                strcpy(path,argv[i+1]);
          }

       }
  }
  else{

      printf("It will use default values: \n");

  }

  printf("serial_cf -p port -b *baud -t path -f file_name -n *num_samples -r *distance \n");
                                                                                
 return(0);
                                                                                
}

extern char receive_terminal(char *);


int main(int argc, char *argv[])
{
 char s[MAX_NUM_CHARACTERS],c;
 char line[MAX_NUM_CHARACTERS],command[MAX_NUM_CHARACTERS];
 int ptr,flag,baud;
 pthread_t a_thread;
 char port[32];
 char path[32];
 char file_name[32];
 char file_obs[100];
 int open_terminal(char *,int);
 int getline(char *,int);
 int send_terminal(char *);
 int close_terminal(void);
 int num_samples;
 float distance;
 int i;
 FILE *fpw;


 /* it gets line inputs */
 get_inputs(argc,argv,port,&baud,path,file_name,&num_samples,&distance);


 /* it opens the serial port */
   if( (fd2=open_terminal(port,baud) ) == 0) {

	printf("Device not connected\n");
        exit(1);
 }
 
 // it opens the data file
 sprintf(file_obs,"%s%s.dat",path,file_name);
 printf("data file: %s\n",file_obs);
 if((fpw=fopen(file_obs,"w")) == NULL){
        printf("File %s can not be open\n",file_obs);
        return(0);
 }


 printf("\n waiting for the data to be stable \n");
 for(i=1;i < NUM_STABLE;i++){
  receive_terminal(line);
 }


 printf("\n Collecting %d samples \n",num_samples);
 for(i=1;i <= num_samples;i++){
  	receive_terminal(line);
 	printf("%d %f %s",i,distance,line);
	fprintf(fpw,"%f %s",distance,line);
 	//printf("%d %f %s",i,distance+float(i*1.80),line);
	//fprintf(fpw,"%f %s",distance+float(i*1.80),line);
 }


 
 close_terminal();
 fclose(fpw);
 

}

