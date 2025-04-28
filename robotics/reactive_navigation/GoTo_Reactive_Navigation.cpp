/********************************************************************************
*                                                                            	*
*  GoTo_State_Machine.cpp 		                              	     	*
*  ===================                                                       	*
*                                                                            	*
*  Description: 							     	*
*  It controls the movement of a robot using reactive control.		     	*
*  It uses a real robot or a simulated one.				     	*
*									     	*
*  Compile:								     	*
*	make 								     	*
*									     	*
*                               J. Savage                                    	*
*                                                                        	*
*                               FI-UNAM 2019                                 	*
********************************************************************************/

// System include files
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
// Robotics include files
#include "../utilities/constants.h"
#include "../utilities/structures.h"
#include "../simulator/simulation.h"
#include "../utilities/utilities.h"
#include "../utilities/random.h"
#include "../utilities/inputs.h"
#include "../state_machines/state_machine_avoidance.h"
#include "../state_machines/state_machine_destination.h"
#include "../state_machines/state_machine_avoidance_destination.h"
#include "../state_machines/state_machine_avoidance_destination_new.h"
#include "../potentials/potentials.h"
#include "reactive_navigation.h"



//Global variables
float K_GOAL=CNT_GOAL*MAG_ADVANCE;
float K_INTENSITY = 1.00*K_GOAL;


// it moves the robot from the origen to the destination using reactive control
int go_to(Inputs inputs)
{
 char file_obs[250];
 char world_file[250];
 float theta=0;
 int j;
 int i=0,k;
 FILE *fpw;
 Raw observations;
 int num_obs=1;
 float distance1;
 coord coord_robot;
 coord coord_dest;
 int flg;
 int debug=0;
 float xmv,ymv,thetamv;
 int quantized_obs;
 int quantized_attraction;
 int quantized_intensity;
 float intensity = 1.0;
 AdvanceAngle mov_vector;
 int next_state;
 int next_state_avoidance=0, next_state_destination=0, next_state_avoidance_destination=0;
 int next_state_fsm_engine=1;
 int state=0;
 AdvanceAngle DistTheta;
 AdvanceAngle mov_vector_avoidance;
 AdvanceAngle mov_vector_destination;
 AdvanceAngle mov_vector_avoidance_destination;
 AdvanceAngle mov_vector_fsm_engine;
 AdvanceAngle mov_vector_potential_fields;
 int selection = 3;
 float largest_value;
 int flg_noise=1;
 float noise_advance,noise_angle;
 int label_quantize_outputs=0;
 int flg_result;


// it reads the environment file
 sprintf(world_file,"%s%s.wrl",inputs.path,inputs.environment);
 read_environment(world_file,debug);

 // it opens the observation's sensor file to be plot by the graphical interface
 sprintf(file_obs,"%s%s.raw",inputs.path,inputs.environment);
 printf("\nobservations file: %s\n",file_obs);
 if((fpw=fopen(file_obs,"w")) == NULL){
	printf("File %s can not be open\n",file_obs);
       	return(0);
 }	


 fprintf(fpw,"( radio_robot %f )\n",inputs.radio_robot);
 printf("\n Radio robot %f \n",inputs.radio_robot);

 coord_robot.xc=inputs.xo;
 coord_robot.yc=inputs.yo;
 coord_robot.anglec=inputs.angle_robot;
 fprintf(fpw,"( origen %f %f %f )\n",inputs.xo,inputs.yo,inputs.angle_robot);
 printf("( origen %f %f %f )\n",inputs.xo,inputs.yo,inputs.angle_robot);

 
 selection=inputs.selection; 
 largest_value=inputs.largest_value;
 flg_noise=inputs.noise;

 //K_GOAL=CNT_GOAL*largest_value;
 K_GOAL=1.7*CNT_GOAL*inputs.Mag_Advance;
 K_INTENSITY = 1.00*K_GOAL;



 // it moves the robot to the final destination
 flg=0;
 coord_dest.xc=inputs.xd;
 coord_dest.yc=inputs.yd;
 fprintf(fpw,"( destination %f %f )\n",inputs.xd,inputs.yd);
 printf("( destination %f %f )\n",inputs.xd,inputs.yd);
	
 while(flg == 0){

	printf("\n\n ************************************************************\n");

        distance1=distance(coord_robot,coord_dest);
	// it checks if the robot reached its destination
	if( distance1 < K_GOAL){
		printf(" reached distance destination %f\n",distance1);
                flg= 1;
        }
        printf("distance destination %f threshold %f\n",distance1,K_GOAL);


        // it saves the robot's position
	fprintf(fpw,"( robot Justina %f %f %f )\n",coord_robot.xc,coord_robot.yc,coord_robot.anglec);
	printf("%d Pose robot %f %f %f \n",num_obs,coord_robot.xc,coord_robot.yc,coord_robot.anglec);

	// it gets data from the simulator or the real robot, this function is in ../simulator/simulation.h
        get_sensor_values(coord_robot,inputs.theta_sensor,inputs.range_sensor,&observations,inputs.num_sensors,largest_value);

        if(flg_noise==1) 
		// it adds noise to the sensors 
		add_noise_obs(&observations,inputs.num_sensors,inputs.path);

        // it saves the sensor data to be plot by Python/TK
        write_obs_sensor(fpw,observations,inputs.sensor,inputs.num_sensors,inputs.theta_sensor,inputs.range_sensor);

	// It quantizes the inputs in file ~/robotics/utilities/utilities.h
	quantized_obs=quantize_inputs(observations,inputs.num_sensors);
	//printf("quantized inputs %d\n",quantized_obs);

	// It quantizes the destination in file ~/robotics/utilities/utilities.h
	quantized_attraction=quantize_destination(coord_robot,coord_dest);
	//printf("quantized destination %d \n",quantized_attraction);
	fprintf(fpw,"( sensor destination %d )\n",quantized_attraction);

	// It quantizes the intensity of the destination in file ~/robotics/utilities/utilities.h
 	quantized_intensity = quantize_intensity(coord_robot,coord_dest,&intensity);
 	//printf("intensity %f quantized intensity %d \n",intensity,quantized_intensity);
	fprintf(fpw,"( sensor light %d )\n",quantized_intensity);


	mov_vector_fsm_engine = reactive_control(quantized_obs, quantized_attraction,
                        quantized_intensity, inputs.Mag_Advance,inputs.max_angle,inputs.path,selection);

        //printf("movement fsm_engine: angle  %f distance %f\n",mov_vector_fsm_engine.angle,
                                                                                //mov_vector_fsm_engine.distance);
        DistTheta.angle=mov_vector_fsm_engine.angle;
        DistTheta.distance=mov_vector_fsm_engine.distance;



	if(flg_noise==1){
		// it adds noise to the movement 
        	get_random_advance_angle(&noise_advance,&noise_angle,inputs.path);
		//printf("angle %f\n",DistTheta.angle);
		DistTheta.angle = DistTheta.angle + noise_angle;
		//printf("angle + noise %f\n",DistTheta.angle);
		//printf("distance %f\n",DistTheta.distance);
		DistTheta.distance = DistTheta.distance + noise_advance;
		//printf("distance + noise %f\n",DistTheta.distance);
 	}

        printf("movement: angle  %f distance %f\n",DistTheta.angle,DistTheta.distance);
        // it saves the robot's actions
        fprintf(fpw,"( movement %f %f )\n",DistTheta.angle,DistTheta.distance);

	// It moves the robot to the desire angle and distance	
	flg_result=mvrobot(DistTheta,&coord_robot);

	/*
	if(selection == 7)	
	if(flg_result==0){

                // It recovers the original angle       
                DistTheta.distance=0.0;
                DistTheta.angle = -DistTheta.angle;
                mvrobot(DistTheta,&coord_robot);
        }
	*/


        num_obs++;
        if(num_obs > inputs.number_steps) flg=1;

 }

 fprintf(fpw,"( distance %f )\n",distance1);
 fprintf(fpw,"( num_steps %d )\n",num_obs);
 fclose(fpw);

 return(num_obs);
}




// Main program
int main(int argc, char *argv[])
{

 Inputs inputs;
 int num_steps;


 /* it gets line inputs */
 get_inputs(argc,argv,&inputs);

 //it sends the robot to the asked position
 num_steps=go_to(inputs);

 return 0;

}


