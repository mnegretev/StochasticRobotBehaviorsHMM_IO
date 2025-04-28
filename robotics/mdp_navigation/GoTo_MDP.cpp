/********************************************************************************
*                                                                            	*
*  GoTo_MDP.cpp 			                              	     	*
*  ===================                                                       	*
*                                                                            	*
*  Description: 							     	*
*  It controls the movement of a robot using MDPs.			     	*
*  It uses a real robot or a simulated one.				     	*
*									     	*
*  Compile:								     	*
*	make -f Makefile_GoTo_MDP						*
*									     	*
*                               J. Savage, S. Muñoz                           	*
*                                                                        	*
*                               FI-UNAM 2015                                 	*
********************************************************************************/

#define PATH "../data/"
#define CENTROID_FILE "vq_images_laser"


int Num_backward=0;


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
#include "../vq/vq.h"
#include "../utilities/utilities.h"
#include "../utilities/inputs.h"
#include "../state_machines/state_machine_avoidance.h"
#include "../state_machines/state_machine_destination.h"
#include "../state_machines/state_machine_avoidance_destination.h"
#include "../utilities/random.h"
#include "state_machine_mdp.h"



// Constants definitions
#define COMMAND_TO_RUN "../mdp_stalin/mdpnav -g 1 -e 0.0008 -f "
#define COMMAND_CP "cp policy.txt "


//Global variables
float K_GOAL=1*CNT_GOAL*MAG_ADVANCE;
float K_INTENSITY = 1.00*K_GOAL;


// it moves the robot from the origen to the destination using state machines
int go_to(Inputs inputs)
{
 char file_obs[250];
 char file_mdp[250];
 char world_file[250];
 char command[250];
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
 AdvanceAngle mov_vector;
 int next_state;
 int next_state_avoidance=1, next_state_destination=1, next_state_avoidance_destination=1;
 int state=1;
 AdvanceAngle DistTheta;
 AdvanceAngle mov_vector_avoidance;
 AdvanceAngle mov_vector_destination;
 AdvanceAngle mov_vector_avoidance_destination;
 int selection = 3;
 float largest_value;
 int flg_noise=0;
 float noise_advance,noise_angle;
 float intensity;
 char action;
 char previous_action='N';
 int flg_read=1;
 struct mdp_database mdp;
 char policy_file[200];
 int flg_result;
 int flg_omnidirectional;
 char last_action=' ';
 int Time=1;
 float angle_light;
 int flg_vq = 0;


 // It starts the random generator
 srandom((int)time((time_t *)NULL));


 /* It reads the mdp */
 strcpy(mdp.objects_file,"mdp_environment");
 printf("MDPfile %s\n", mdp.objects_file);
 read_mdps(&mdp,inputs.path);


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
 //printf("\nRadio robot %f \n",inputs.radio_robot);

 coord_robot.xc=inputs.xo;
 coord_robot.yc=inputs.yo;
 coord_robot.anglec=inputs.angle_robot;
 fprintf(fpw,"( origen %f %f %f )\n",inputs.xo,inputs.yo,inputs.angle_robot);
 printf("( origen %f %f %f )\n",inputs.xo,inputs.yo,inputs.angle_robot);


 flg_omnidirectional=inputs.omni;
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




	// it gets data from the simulator or the real robot, this function is in ../simulator/simulation.h
        get_sensor_values(coord_robot,inputs.theta_sensor,inputs.range_sensor,&observations,inputs.num_sensors,largest_value);
	printf("Inputs largets value %f\n",largest_value);
       // it adds noise to the sensors 
        //if(flg_noise==1) add_noise_obs(&observations,inputs.num_sensors,inputs.path);
	if(flg_noise==1) {
                printf("intensity %f angle light %f \n",intensity,angle_light);
                // it adds noise to the sensors, function in ../utilities/random.h
                add_noise_obs(&observations,&intensity,&angle_light,inputs.num_sensors,inputs.path);
                printf("with noise intensity %f angle light %f \n",intensity,angle_light);
        }




        // it saves the robot's position
	fprintf(fpw,"( robot Justina %f %f %f )\n",coord_robot.xc,coord_robot.yc,coord_robot.anglec);
	//printf("%d Pose robot %f %f %f \n",num_obs,coord_robot.xc,coord_robot.yc,coord_robot.anglec);

        // it saves the sensor data to be plot by Python/TK
        write_obs_sensor(fpw,observations,inputs.sensor,inputs.num_sensors,inputs.theta_sensor,inputs.range_sensor);

	// It quantizes the destination in file ~/robotics/utilities/utilities.h
	//quantized_attraction=quantize_destination(coord_robot,coord_dest);
        // FIX HERE
        quantized_attraction=quantize_destination(coord_robot,coord_dest,&angle_light,flg_vq);
        //printf("quantized destination %d \n",quantized_attraction);


	fprintf(fpw,"( sensor destination %d )\n",quantized_attraction);


	// It generates the mdp policy
	//if((num_obs == 1) || ((num_obs % NUM_POLICY)==0) || (last_action == 'X')){
	if((num_obs == 1) || (Time == NUM_POLICY) || (last_action == 'X')){
		// It generates the ocupancy grid for the mdp, function in file ~/robotics/utilities/utilities.h
		ocupancy_grid_mdp(observations,inputs.num_sensors,quantized_attraction,&mdp,largest_value,coord_robot.anglec);
		write_mdps(mdp,inputs.path);

		sprintf(command,"%s%smdp_environment_grid.mdp",COMMAND_TO_RUN,inputs.path);	
		printf("COMMAND: %s\n",command);
        	system(command);
        	printf("Done.\n");
		sprintf(command,"%s%spolicy.txt",COMMAND_CP,inputs.path);	
		printf("COMMAND CP: %s\n",command);
        	system(command);
        	printf("Done.\n");

		// it reads the policy table
 		sprintf(policy_file,"%spolicy.txt",inputs.path);
 		read_policy(mdp.num_rows,mdp.num_columns,policy_file,&mdp);
 		for(j=1;j<=mdp.num_rows;j++){
    			for(k=1;k<=mdp.num_columns;k++){
                        	printf("policy_table[%d][%d] %c\n",j,k,mdp.policy[j][k]);
    			}
 		}
		flg_read=1;
		Time=1;
	}

	// It quantizes the intensity of the destination in file ~/robotics/utilities/utilities.h
 	//quantized_intensity = quantize_intensity(coord_robot,coord_dest,&intensity);
	// FIX HERE
        quantized_intensity = quantize_intensity(coord_robot,coord_dest,&intensity,flg_vq);
        printf("intensity %f quantized intensity %d \n",intensity,quantized_intensity);
	fprintf(fpw,"( sensor light %d )\n",quantized_intensity);



	// It calculates the robot's movement using a MDP state machine
	action=state_machine_destination_mdp(quantized_attraction, quantized_intensity,
								inputs.path, previous_action,mdp,flg_read);

	flg_read=0;
	printf("Executed action %c\n",action);
	last_action=action;
	
	mov_vector_destination = mdp_output(action, inputs.Mag_Advance,inputs.max_angle,coord_robot.anglec);

	printf("movement destination: angle  %f distance %f\n",mov_vector_destination.angle,mov_vector_destination.distance);
        // it saves the robot's actions
	fprintf(fpw,"( movement %f %f )\n",mov_vector_destination.angle,mov_vector_destination.distance);



	// It moves the robot to the desire angle and distance	

	DistTheta.angle=mov_vector_destination.angle;
 	DistTheta.distance=mov_vector_destination.distance;

	 if(flg_noise==1){
                get_random_advance_angle(&noise_advance,&noise_angle,inputs.path);
                //printf("angle %f\n",DistTheta.angle);
                DistTheta.angle = DistTheta.angle + noise_angle;
                //printf("angle + noise %f\n",DistTheta.angle);
                //printf("distance %f\n",DistTheta.distance);
                DistTheta.distance = DistTheta.distance + noise_advance;
                //printf("distance + noise %f\n",DistTheta.distance);
        }


	flg_result=mvrobot(DistTheta,&coord_robot);
	printf("%d Pose robot %f %f %f \n",num_obs,coord_robot.xc,coord_robot.yc,coord_robot.anglec);


	if(flg_result==0){
		if(flg_omnidirectional == 1){
			// It recovers the original angle       
                        printf("It keeps the angle\n");
                        DistTheta.distance=0.0;
                        DistTheta.angle = -DistTheta.angle;
                        mvrobot(DistTheta,&coord_robot);
		}
		else{
			if((num_obs % NUM_POLICY)==0)
				printf("It changes the angle\n");
			else{
				// It recovers the original angle	
				printf("It keeps the angle\n");
				DistTheta.distance=0.0;
        			DistTheta.angle = -DistTheta.angle;
				mvrobot(DistTheta,&coord_robot);
			}
		}
	}


	printf("%d Pose robot %f %f %f \n",num_obs,coord_robot.xc,coord_robot.yc,coord_robot.anglec);


	previous_action=action;

        distance1=distance(coord_robot,coord_dest);
	printf("num_obs %d Time %d\n",num_obs,Time);
        num_obs++;
	Time++;


	// it checks if the robot reached its destination
	// K_GOAL = 0.12;
	/*if( distance1 < K_GOAL){

		printf(" reached distance destination %f\n",distance1);
                flg= 1;

       }

       printf("distance destination %f threshold %f\n",distance1,K_GOAL);
	*/


       if(num_obs > inputs.number_steps) flg=1;
       if(action=='X') {
		flg_read=0;
	}
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


