// potentials_3d.h

#include "constants_pot_3d.h"
//#include "../potentials/robot_functions.h"
#include "vector_functions_3d.h"



#define ROBOT_RADIO 1.5


// Global variables
/*float d0=D0;
float d1=D1;
float e1=E1;
float e2=E2;
float eta=ETA;
*/


// it reads the constants file
int read_pot_cnt_3d(char *PATH){
 FILE *fp;
 char file[300];
 char dummy[300];
 float Mag_Advance = 1.1;
 

 //sprintf(file,"%spot_cnt%2.1f.txt",PATH,Mag_Advance);
 sprintf(file,"%spot_cnt.txt",PATH);
#ifdef DEBUG
 printf("Potentials file %s\n",file); 
#endif
 if((fp=fopen(file,"r")) == NULL){
         printf("File %s can not be open\n",file);

	 sprintf(file,"%spot_cnt.txt",PATH);
 	 printf("it will use default potentials file %s\n",file);
   	 if((fp=fopen(file,"r")) == NULL){
         	printf("File %s can not be open\n",file);
         	exit(0);
 	}

 }


 fscanf(fp,"%s",dummy);
 fscanf(fp,"%f%f%f%f%f",&d0,&d1,&e1,&e2,&eta);
#ifdef DEBUG
 printf("dummy %s\n",dummy);
 printf("d0 %f d1 %f e1 %f e2 %f eta %f\n",d0,d1,e1,e2,eta);
#endif

 fclose(fp);

 return(1);

}


// Potential field navegation
//coord get_repulsion_force(int num_sensors,float *sensors,float theta,float *angle_sensors){
cord get_repulsion_force_3d(Inputs inputs, Raw obs){

	int j;
	cord repulsion_force,dif_vector;
	float x,y,theta_in;
	float mag,tmp,mag3;
	repulsion_force.xc=0;
	repulsion_force.yc=0;
	float angle;
	int num_sensors;
	float threshold;


	num_sensors = inputs.num_sensors;
	threshold = 0.8 * inputs.largest_value;

	
	for( j=0; j< num_sensors; j++) {
			//sensors[j] = obs.sensors[j];
        		//printf("j %d distance %f angle %f\n",j,obs.sensors[j],obs.theta[j]);
        		//printf("j %d distance-radio_robot %f\n",j,obs.sensors[j]- inputs.radio_robot);

			if(obs.sensors[j] < threshold){

				theta_in = obs.theta[j];
				x= (obs.sensors[j] - inputs.radio_robot) * (float) cos(theta_in);
				y= (obs.sensors[j] - inputs.radio_robot) * (float) sin (theta_in);
				//x= obs.sensors[j] * (float) cos(theta_in);
				//y= obs.sensors[j] * (float) sin (theta_in);
        			//printf("pos. obstacle x %f y %f\n",x,y);

				dif_vector.xc= - x;
				dif_vector.yc= - y;
				mag=magnitude_3d(dif_vector) + (float) 0.0001;
				//printf("d0 %f eta %f sensor %d %f mag %f\n",d0,eta,j,obs.sensors[j],mag);
				if(mag <=d0){
					tmp= (float) eta*(1/mag - 1/(float) d0);
					mag3=mag*mag*mag;
					dif_vector.xc= tmp * dif_vector.xc / mag3;
					dif_vector.yc= tmp * dif_vector.yc / mag3;
				}else
				{
					dif_vector.xc= 0;
					dif_vector.yc= 0;
				}

			}
			else{

        			//printf("There is not an obstacle\n");
				dif_vector.xc= 0;
                                dif_vector.yc= 0;
			}
			repulsion_force.xc= repulsion_force.xc + dif_vector.xc;
			repulsion_force.yc= repulsion_force.yc + dif_vector.yc;
			//printf("repulsion force sensor %d x %f y %f\n\n",j,dif_vector.xc,dif_vector.yc);

	}

	//printf("repulsion force total x %f y %f\n\n",repulsion_force.xc,repulsion_force.yc);


	mag=magnitude_3d(repulsion_force);
	angle=get_angle(0,repulsion_force.xc,repulsion_force.yc,0,0);
	//printf("rep.force mag %f angle %f\n",mag,angle);
	
	//angle=angle-theta;
	repulsion_force.xc= mag*(float) cos(angle);
	repulsion_force.yc= mag*(float) sin(angle);
	//printf("vector repulsion.force x %f y %f\n",repulsion_force.xc,repulsion_force.yc);
	return(repulsion_force);
}




cord get_attraction_force_3d(cord coord_robot,cord coord_destination,float intensity){

	cord attraction_force;
	float mag,angle;


	attraction_force=dif_vectors_3d(coord_robot,coord_destination);
	mag= (1/intensity) * magnitude_3d(attraction_force);
	//printf(" 1/intensity %f magnitude(attraction_force) %f mag %f\n",1/intensity,magnitude(attraction_force),mag);

	if(mag> d1){
		// F =(e2 * sx) / magnitud
		attraction_force=multiply_vector_scalar_3d(attraction_force,(float)  -E2);
		attraction_force=divide_vector_scalar_3d(attraction_force,mag);
		//printf("e2 %f\n",E2);

	}
	else{
		// F = e1 * sx
		attraction_force=multiply_vector_scalar_3d(attraction_force,(float)  -e1);
		//printf("e1 %f\n",e1);

	}
	
	//printf("atr.force x %f y %f\n",attraction_force.xc,attraction_force.yc);
	mag=magnitude_3d(attraction_force);
	angle=get_angle(0,attraction_force.xc,attraction_force.yc,0,0);
#ifdef DEBUG
	printf("atr.force mag %f angle%f\n",mag,angle);
#endif	
	attraction_force.xc=  -mag*(float) cos(angle);
	attraction_force.yc=  -mag*(float) sin(angle);
	//printf("vector atr.force x %f y %f\n",attraction_force.xc,attraction_force.yc);
	
	return(attraction_force);
}


/*
coord get_attraction_force_images( float mag, float angle){
	coord attraction_force;

	attraction_force.xc= e1*mag*(float) cos(angle);
	attraction_force.yc= e1*mag*(float) sin(angle);
	//printf("vector atr.force x %f y %f\n",attraction_force.xc,attraction_force.yc);
	
	return(attraction_force);
}
*/



void get_dist_theta_3d(float x,float y,float angle,float x1,float y1,float *distance,float *theta){

 // it calculates the distance
 *distance=(float)sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
 //printf("Distance: %f\n",*distance);

 // it calculates the rotation angle
 *theta=get_ang(angle,x1,y1,x,y);
 //printf("rotation angle: %f\n",*theta);

}


AdvanceAngle potential_fields_3d(Inputs inputs, int quantized_attraction, float intensity, Raw obs)
{

 int num_sensors;	
 float sensors[NUM_LASERS+1];
 cord unit_vector;
 cord next_robot;
 cord repulsion_vector,attraction_vector;
 Behav pot_vector;
 cord tmp;
 float distance;
 cord get_unit_vector(Behavior Bvector);
 static int flag=0;
 AdvanceAngle pot;
 cord coord_robot;
 cord coor_destination;
 float delta;
 float theta;


 coord_robot.anglec = 0.0;
 coord_robot.xc = 0.0;
 coord_robot.yc = 0.0; 
 coord_robot.zc = 0.0; 



// Check how the quantized attraction value is generated in function quantize_destination in ..//utilities/utilities.h
#ifdef DEBUG
 printf("quantized destination %d \n",quantized_attraction);
#endif
 if(quantized_attraction == 1){
        coor_destination.xc= 1.0001;
        coor_destination.yc= 1.0001;
 }
 else if(quantized_attraction == 2){
        coor_destination.xc= 0.0001;
        coor_destination.yc= 1.0001;
 }
 else if(quantized_attraction == 3){
        coor_destination.xc= -1.0001;
        coor_destination.yc= -1.0001;
 }
 else if(quantized_attraction == 4){
        coor_destination.xc= -1.0001;
        coor_destination.yc= 0.0001;
 }
 if(quantized_attraction == 5){
        coor_destination.xc= -1.0001;
        coor_destination.yc= -1.0001;
 }
 else if(quantized_attraction == 6){
        coor_destination.xc= 0.0001;
        coor_destination.yc= -1.0001;
 }
 else if(quantized_attraction == 7){
        coor_destination.xc= 1.0001;
        coor_destination.yc= -1.0001;
 }
 else if(quantized_attraction == 0){
        coor_destination.xc= 0.0001;
        coor_destination.yc= 0.0001;
 }



// it reads the constants file the first time this function is called
 if(flag==0){
 	read_pot_cnt_3d(inputs.path);
	flag=1;
 }

 delta = 1.0*inputs.radio_robot; 

 // It calculates the repulsion and attraction forces

 repulsion_vector=get_repulsion_force_3d(inputs,obs);
 repulsion_vector.xc = - repulsion_vector.xc;
 repulsion_vector.yc = - repulsion_vector.yc;

 //printf("Position destination x %f y %f\n",coor_destination.xc,coor_destination.yc);
 attraction_vector= get_attraction_force_3d(coord_robot,coor_destination,intensity);
#ifdef DEBUG
 printf("attraction vector force x %f y %f\n",attraction_vector.xc,attraction_vector.yc);
#endif
 attraction_vector.xc =  intensity*attraction_vector.xc;
 attraction_vector.yc =  intensity*attraction_vector.yc;


 // It adds the attraction and repulsion vectors
 tmp=add_vectors_3d(repulsion_vector,attraction_vector);
#ifdef DEBUG
 printf("total vector force total x %f y %f\n",tmp.xc,tmp.yc);
#endif
	
 pot_vector.xc=tmp.xc;
 pot_vector.yc=tmp.yc;
 pot_vector.status=.500f;
 pot_vector.flg_vector=1;

 unit_vector=get_unit_vector_3d(pot_vector);
 pot_vector.xc=unit_vector.xc;
 pot_vector.yc=unit_vector.yc;
 //printf("unit vector force total x %f y %f\n",pot_vector.xc,pot_vector.yc);


 next_robot.xc = coord_robot.xc - delta*pot_vector.xc;
 next_robot.yc = coord_robot.yc - delta*pot_vector.yc;
 next_robot.zc = coord_robot.zc - delta*pot_vector.zc;

 //printf("Position robot x %f y %f\n",coord_robot.xc,coord_robot.yc);
 //printf("Next position robot x %f y %f\n",next_robot.xc,next_robot.yc);

 get_dist_theta_3d(coord_robot.xc,coord_robot.yc,coord_robot.anglec,next_robot.xc,next_robot.yc,&distance,&theta);

 //printf("Distance: %f\n",distance);
 //printf("rotation angle: %f\n",theta);


 if((fabs(theta) > PI/2) && (fabs(theta) < 3*PI/2)){
		theta = (PI - fabs(theta));
		distance = -distance;
 }


 //printf("Corrected distance: %f\n",distance);
 //printf("Corrected rotation angle: %f\n",theta);


 pot.distance = distance;
 pot.angle = theta;
 return pot;

}


