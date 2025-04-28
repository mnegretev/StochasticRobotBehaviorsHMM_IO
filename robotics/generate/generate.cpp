
/*****************************************************************************
*                                                                            *
*  generate.cpp 	       	                                     	     *
*  ======================                                                    *
*                                                                            *
*  Description: 							     *
*  It generates random environments with obstacles and random origens	     *
*  and destinations.					             	     *
*  									     *
* Compile: make 		                                             *
* 							     		     *
*  Usage:								     * 
* generate -f file -n number_worlds -r robot's_radio (dm) -m number obstacles*
*     -o obstacles_radio (dm) -p path -dx DimX -dy Dimy -nd num_destinations *
*    									     *
* generate -f random -n 10 -r 1 -m 20 -o 2 -p /home/savage/observations	     *
* 		-dx 50 -dy 50 -rx 10 -ry 25 -destx 40 -desty 40 -nd 10	     *
*                               	 	                             *
*                               J. Savage                                    *
*                               	 	                             *
*                               FI-UNAM Oct-2013                             *
*                               	 	                             *
*****************************************************************************/

// Include files
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

//#include "/home/savage/tcltk/tk8.4.5/ROC2/defines_ROC2.h"

#define PI 3.1415926535f
#define CNT_ROBOT 1.5 
#define CNT_OBS 1.5
#define CNT_SIZE 3
#define INI_PNT 4
#define END_PNT 8
#define NUM_MAX_ORIGIN 200
#define NUM_MAX_OBS 100
#define WIDHT_WALL 0.010
#define NUM_MAX_REJECTIONS 100
#define NUM_MAX_REJECTIONS_Origen_Destination 1000

// it gets the magnitude of two vectors
float magnitude(float x1,float y1,float x2,float y2){

 float dif;

 dif= (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
 dif= sqrt(dif);

 return(dif);

}

 //IT GENERATES RANDOM NUMBERS
float generaR(float LMin,float LMax){
float n;
int BIG= 0x7FFFFFFF;

  n=LMin+ ((float) random()/(float) BIG ) *(LMax-LMin);
  return n;
}


void init_file(FILE *fp,char *name,float dimx,float dimy,int num)
{

 fprintf(fp,";******************************************************************************\n");
 fprintf(fp,";* File: %s_%d.wrl				     			      *\n",name,num);
 fprintf(fp,";* Purpose: Definition of the forbidden and allowed areas in the Robot's      *\n");
 fprintf(fp,";*          world. These areas are derivated from the objects in the	      *\n");
 fprintf(fp,";*	    world.				      			      *\n");
 fprintf(fp,";******************************************************************************\n");
 fprintf(fp," \n");
 fprintf(fp,"( dimensions %s %f %f )\n",name,dimx,dimy);
 fprintf(fp," \n");

 fprintf(fp,"( polygon wall external_wall_1 0.00 0.00 0.00 %f %f %f %f 0.00 )\n",
					dimy-WIDHT_WALL,WIDHT_WALL,dimy-WIDHT_WALL,WIDHT_WALL);

 fprintf(fp,"( polygon wall external_wall_2 0.00 %f 0.00 %f %f %f %f %f )\n",
					dimy-WIDHT_WALL,dimy,dimx,dimy,dimx,dimy-WIDHT_WALL);

 fprintf(fp,"( polygon wall external_wall_3 %f 0.00 %f %f %f %f %f 0.00 )\n",
					dimx-WIDHT_WALL,dimx-WIDHT_WALL,dimy,dimx,dimy,dimx);

 fprintf(fp,"( polygon wall external_wall_4 0.00 0.00 0.00 %f %f %f %f 0.00 )\n",
						WIDHT_WALL,dimx,WIDHT_WALL,dimx);


}


#define DIM_CANVAS_X 600
#define DIM_CANVAS_Y 600
float convert_coor_TK(float x, float y, float dimx, float dimy, float *xs,float *ys){

 float scale_x,scale_y,Y;

 scale_x= DIM_CANVAS_X/dimx;
 scale_y= DIM_CANVAS_Y/dimy;

 Y = dimy - y;
 *xs= x*scale_x;
 *ys= Y*scale_y;

}



// it generates the worlds
void generate_env(char *environment,int num_env,float radio_robot,int num_obstacles,float radio_obstacle,char *path,
	float dimx, float dimy, float pose_x, float pose_y, float dest_x, float dest_y, int num_dest)
{

 int i,j,k,l,m;
 char world[600];
 char file[600];
 FILE *fp;
 float x,y,tetha,delta_tetha;
 int n;
 float nf;
 float xc,yc;
 float Xg,Yg;
 float hyp;
 float margin;
 float XC[NUM_MAX_OBS],YC[NUM_MAX_OBS];
 float Xo[NUM_MAX_ORIGIN],Yo[NUM_MAX_ORIGIN];
 float Xd[NUM_MAX_ORIGIN],Yd[NUM_MAX_ORIGIN];
 float xo,yo,xd,yd;
 float value,value_d;
 float margin_obs;
 int flag;
 int num_rej=1;
 float xos,yos,xds,yds;
 int num_rej_origen;
 float margin_origen_destination;



 margin_origen_destination=radio_robot*CNT_ROBOT;
 margin= radio_robot*CNT_ROBOT + radio_obstacle;
 margin_obs= radio_robot*CNT_ROBOT + radio_obstacle*CNT_OBS;
 sprintf(world,"%s%s",path,environment);

 for(i=1; i <= num_env;i++){

	sprintf(file,"%s_%d.wrl",world,i);
	fp=fopen(file,"w");
	if(fp==0){
        	printf("\n File %s can not be created\n",file);
        	exit(0);
   	}
	
      	printf("Environment %s \n",file);
	init_file(fp,environment,dimx,dimy,i);
	l=1;

 	// it generates a Uniform random variable to get the number of poligons' points 
	nf=generaR(INI_PNT,END_PNT);
	n=int(nf);
 	delta_tetha= 2*PI / n;
	printf("n %d delta_tetha %f\n",n,delta_tetha);

	tetha= delta_tetha;
	xc=generaR(margin,dimx-margin);
	yc=generaR(margin,dimy-margin);
	hyp= generaR(radio_obstacle/CNT_SIZE,radio_obstacle);
	x= (hyp * cos(tetha)) + xc;
	y= (hyp * sin(tetha)) + yc;
	Xg= x;
	Yg= y;
	XC[l]=Xg;
	YC[l]=Yg;

	printf("Polygon 1 point 1 X %f Y %f\n",Xg,Yg);
	fprintf(fp,"( polygon obstacle obs_1 %f %f ",Xg,Yg);

	for(j=1; j < num_obstacles; j++){

		for(k=2; k <= n ; k++){

			tetha= tetha + delta_tetha;
			hyp= generaR(radio_obstacle/CNT_SIZE,radio_obstacle);
               		x= (hyp * cos(tetha)) + xc;
               		y= (hyp * sin(tetha)) + yc;
               		Xg= x;
               		Yg= y;
                	
			printf("Polygon %d point %d X %f Y %f\n",j,k,Xg,Yg);
			fprintf(fp,"%f %f ",Xg,Yg);
		}
		fprintf(fp,")\n");

		flag=1;
		num_rej=1;

		while(flag == 1){
	 	
 			// it generates a Uniform random variable to get the number of poligons' points 
			nf=generaR(INI_PNT,END_PNT);
			n=int(nf);
 			delta_tetha= 2*PI / n;
			//printf("n %d delta_tetha %f\n",n,delta_tetha);

			tetha= delta_tetha;
			xc=generaR(margin,dimx-margin);
			yc=generaR(margin,dimy-margin);
			hyp= generaR(radio_obstacle/2,radio_obstacle);
			x= (hyp * cos(tetha)) + xc;
			y= (hyp * sin(tetha)) + yc;
			Xg= x;
			Yg= y;

			for(m=1;m <= l;m++){
				value = magnitude(Xg,Yg,XC[m],YC[m]);

				if(value < margin_obs){
					flag=1;
					printf("Rejected obstacle to close to obstacle %d num.rejects  %d x %f y %f distance %f\n",m,num_rej,Xg,Yg,value);
					num_rej++;
					break;
				}
				else flag=0;
			
			}
		
			if(num_rej > NUM_MAX_REJECTIONS)flag=0;
	

		}

		if(num_rej > NUM_MAX_REJECTIONS){
				printf("To many obstacle rejections %d\n",num_rej);
				fclose(fp);
				j=num_obstacles;
		}
		else{
			l++;
			printf("Polygon %d point 1 X %f Y %f\n",l,Xg,Yg);
			fprintf(fp,"( polygon obstacle  obs_%d %f %f ",l,Xg,Yg);
			XC[l]=Xg;
			YC[l]=Yg;
		}
	}

	// finish last point
	if(num_rej < NUM_MAX_REJECTIONS){
		for(k=2; k <= n ; k++){

                        tetha= tetha + delta_tetha;
                        hyp= generaR(radio_obstacle/2,radio_obstacle);
                        x= (hyp * cos(tetha)) + xc;
                        y= (hyp * sin(tetha)) + yc;
                        Xg= x;
                        Yg= y;

                        printf("Polygon %d point %d X %f Y %f\n",j,k,Xg,Yg);
                        fprintf(fp,"%f %f ",Xg,Yg);
        	}
        	fprintf(fp," )\n");
		fclose(fp);
	}

 	k=0;
	num_rej_origen=1;

 	for(j=1; j <= num_dest; j++){

  	        printf("destination %d\n",j);	
		flag=1;
  		num_rej=1;

		while(flag == 1){

			// it generates an origen and checks that it is a valid one
			//xo=generaR(2*margin,dimx-.2*margin);
       			//yo=generaR(2*margin,dimy-.2*margin);
			xo=generaR(margin_origen_destination,dimx-margin_origen_destination);
       			yo=generaR(margin_origen_destination,dimy-margin_origen_destination);
			printf("%d origen %f %f \n",j,xo,yo);
			for(m=1;m <= l;m++){
                                value = magnitude(xo,yo,XC[m],YC[m]);

                                if(value < margin_obs){
					flag=1;
                                        printf("Rejected origen %f %f num_rejected %d\n",xo,yo,num_rej);
                                        num_rej++;
                                        if(num_rej > NUM_MAX_REJECTIONS_Origen_Destination){
                                                flag=0;
                                        }
                                        break;
                                }else flag=0;

                        }

		}

		flag = 1;
		num_rej=1;
  		while(flag == 1){

			// it generates destination and checks that it is a valid one
			//xd=generaR(2*margin,dimx-.2*margin);
        		//yd=generaR(2*margin,dimy-.2*margin);
			xd=generaR(margin_origen_destination,dimx-margin_origen_destination);
       			yd=generaR(margin_origen_destination,dimy-margin_origen_destination);
			printf("%d destination %f %f \n",j,xd,yd);

			value = magnitude(xo,yo,xd,yd);

			//if(value > 4*margin_obs) 
			if(value > 2*margin_obs) 
			for(m=1;m <= l;m++){
				value_d = magnitude(xd,yd,XC[m],YC[m]);

				if(value_d < margin_obs){
					flag=1;
					//printf("Rejected origen %f %f destination x %f y %f distance %f num.rejections %d\n",xo,yo,xd,yd,value,num_rej);
					num_rej++;
					if(num_rej > NUM_MAX_REJECTIONS_Origen_Destination){
						flag=0;
					}
					break;
				}else flag=0;

			}
  		}

  		if(num_rej < NUM_MAX_REJECTIONS_Origen_Destination){
  			k++;
  			Xo[k]=xo;
  			Yo[k]=yo;
  			Xd[k]=xd;
  			Yd[k]=yd;
  		}
  		else{
			num_rej_origen++;
		}
		
  		if(num_rej_origen > NUM_MAX_REJECTIONS_Origen_Destination)  break;

    	}

        if(k== 0) printf("There were not origen destination points\n");
	else {
		sprintf(file,"%s_%d.ord",world,i);
        	fp=fopen(file,"w");
        	if(fp==0){
                	printf("\n File %s can not be created\n",file);
                	exit(0);
        	}

                printf("\n File %s contains the origen and destination files \n",file);
		fprintf(fp,"%d\n",k);

    		for(j=1; j <= k; j++){
			printf("%d Xo %f Yo %f Xd %f Yd %f\n",j,Xo[j],Yo[j],Xd[j],Yd[j]);
			//convert_coor_TK(Xo[j],Yo[j],dimx,dimy,&xos,&yos);
 			//convert_coor_TK(Xd[j],Yd[j],dimx,dimy,&xds,&yds);
			//printf("TK %d Xo %f Yo %f Xd %f Yd %f\n",j,xos,yos,xds,yds);

			fprintf(fp,"%f\n%f\n%f\n%f\n",Xo[j],Yo[j],Xd[j],Yd[j]);
			//fprintf(fp,"%f\n%f\n%f\n%f\n",xos,yos,xds,yds);

    		}
	
		fclose(fp);
	}

 }


}




/* it gets line inputs */
int get_inputs(int argc, char **argv, char *environment,int *num_env, float *radio_robot, int *num_obstacles, float *radio_obstacles, 
		char *path, float *dimx, float *dimy, float *posex, float *posey, float *dx, float *dy, int *num_dest)
{

 int i;
                                                                                
 /* It sets default values */
 strcpy(environment,"random");
 *num_env=1;
 *radio_robot=.030;
 *num_obstacles=20;
 *radio_obstacles=.05;
 strcpy(path,"../data/");
 *dimx=1.0;
 *dimy=1.0;
 *posex=0.15;
 *posey=0.15;
 *dx=0.90;
 *dy=0.90;
 *num_dest=5;

 

  /* reads input parameters */
  if (argc>1) {
        for(i=1;i<argc;i++){
          if (!strcmp(argv[i],"-h")){
                                                                                
                printf("Sintax: generate -f file -n number_worlds -r robot's_radio -m number obstacles -o obstacles_radio  -p path -dx Dim_env_X  -dy Dim_env_y  -nd num_destinations \n");
                printf("example: generate -f random -n 1 -r 0.03 -m 20 -o 0.02 -p ../data -dx 1.0 -dy 1.0 -nd 10\n\n");
                exit(1);
          }
          else if (!strcmp(argv[i],"-f")){
                strcpy(environment,argv[i+1]);
          }
	  else if (!strcmp(argv[i],"-n")){
	        *num_env=atoi(argv[i+1]);
          }
          else if (!strcmp(argv[i],"-dx")){
	        *dimx=atof(argv[i+1]);
	  }
          else if (!strcmp(argv[i],"-dy")){
	        *dimy=atof(argv[i+1]);
	  }
          else if (!strcmp(argv[i],"-destx")){
	        *dx=atof(argv[i+1]);
	  }
          else if (!strcmp(argv[i],"-desty")){
	        *dy=atof(argv[i+1]);
	  }
          else if (!strcmp(argv[i],"-ry")){
	        *posey=atof(argv[i+1]);
	  }
          else if (!strcmp(argv[i],"-rx")){
	        *posex=atof(argv[i+1]);
	  }
          else if (!strcmp(argv[i],"-r")){
	        *radio_robot=atof(argv[i+1]);
	  }
	  else if (!strcmp(argv[i],"-m")){
	        *num_obstacles=atoi(argv[i+1]);
          }
	  else if (!strcmp(argv[i],"-nd")){
	        *num_dest=atoi(argv[i+1]);
          }
          else if (!strcmp(argv[i],"-o")){
	        *radio_obstacles=atof(argv[i+1]);
	  }
          else if (!strcmp(argv[i],"-p")){
                strcpy(path,argv[i+1]);
	  }
       
    }
  }
  else{
                                                                                
      printf("\nIt will use default values:\n");
  }

 if( *num_obstacles > NUM_MAX_OBS) *num_obstacles = NUM_MAX_OBS + 1;
 if( *num_dest > NUM_MAX_ORIGIN) *num_dest = NUM_MAX_ORIGIN + 1;
                                                                                
  printf("generate -f %s -n %d -r %f -m %d -o %f -p %s -dx %f -dy %f -nd %d\n",
	environment,*num_env,*radio_robot,*num_obstacles,*radio_obstacles,path,*dimx,*dimy,*num_dest);
 
  return(0);
                                                                                
}
 



// Main program
int main(int argc, char *argv[])
{

 int num_env,num_obstacles;
 float radio_robot,radio_obstacle;
 char environment[300];
 char path[300];
 float dimx,dimy,posex,posey;
 float destx,desty;
 int num_dest;

 
 /* it gets line inputs */
 get_inputs(argc,argv,environment,&num_env,&radio_robot,&num_obstacles,&radio_obstacle,path,&dimx,&dimy,
	&posex,&posey,&destx,&desty,&num_dest);

 // Initializes the random generator
 srandom((int)time((time_t *)NULL));

 // it generates the random environments
 generate_env(environment,num_env,radio_robot,num_obstacles,radio_obstacle,path,dimx,dimy,
			posex,posey,destx,desty,num_dest);


 return 0;

}


