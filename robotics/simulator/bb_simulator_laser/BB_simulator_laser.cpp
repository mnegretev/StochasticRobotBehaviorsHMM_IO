/********************************************************************************
*                                                                               *
*  BB_simulator_laser.cpp                                                             *
*  ===================                                                          *
*                                                                               *
*  Description:                                                                 *
*  It simulates sensors' readings and communicates them using the Blackboard    *
*                                                                               *
*                                                                               *
*                               J. Savage                                       *
*                                                                               *
*                               FI-UNAM 4-3-2015                                *
*                                                                               *
********************************************************************************/


// Contant definitions
#define PORT 2020 // change the value of PORT accordingly
#define MAX_NUM_CHARACTERS 1500

// global variables
int flg_ACTUATOR=0;
int flg_SENSOR=0;
int flg_START=0;
float answer_distance;
float answer_angle;

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include "Module.h"
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h> 
// Class that manages shared variable updates
#include <uRobotics/api/SharedVariableSubscriptionReport.h>
// Wrappers for shared variables
#include <uRobotics/api/psv/StringSharedVariable.h>
#include "../utilities/structures.h"

coord coord_robot;
Inputs inputs;



// Robotics include files
#include "../utilities/constants.h"
#include "../simulator/simulation.h"
#include "../utilities/utilities.h"
#include "../utilities/inputs.h"
// Include Blackboard setup
#include "../BB_utilities/setup_BB_C++.h"




// Thread
void *sensor_thread(void *arg)
{

 char world_file[250];
 int j;
 Raw observations;
 //static int flg=0;
 int num_obs=1;
 char line[MAX_NUM_CHARACTERS*30];
 char tmp[MAX_NUM_CHARACTERS];
 char wait[10];

    

 printf("flg_sensor %d\n",flg_SENSOR);

 while(1){
        if(flg_SENSOR == 0){
                usleep(1);
        }
        else{
                flg_SENSOR = 0;

		 // it reads the environment everytime is selected by the GUI
 		if(flg_ENVIRONMENT==1){
			sprintf(world_file,"%s%s.wrl",inputs.path,inputs.environment);
			printf("Environment %s\n",world_file);
        		read_environment(world_file,0);
			flg_ENVIRONMENT=0;
 		}	

    
                printf("type %d Pose robot %f %f %f \n",num_obs,coord_robot.xc,coord_robot.yc,coord_robot.anglec);
		//scanf("%s",wait);
	

        	get_sensor_values(coord_robot,inputs.theta_sensor,inputs.range_sensor,&observations,inputs.num_sensors,inputs.largest_value);

		// ( sensor laser 2 0.400000 -0.200000 0.160162 0.175607 )
		sprintf(line,"( sensor laser %d %f %f ",inputs.num_sensors,inputs.range_sensor,inputs.theta_sensor);

		for(j=0;j<inputs.num_sensors;j++){
        		//printf("%d %f\n",j,observations.sensors[j]);
			sprintf(tmp,"%2.2f ",observations.sensors[j]);
			strcat(line,tmp);
		}

		strcat(line,")");
		//printf("line %s\n",line);


		 // it sends the sensing data
 		/*send_command_sensor(line);
		boost::this_thread::sleep(boost::posix_time::milliseconds(100));
 		send_command_sensor(line);
		boost::this_thread::sleep(boost::posix_time::milliseconds(100));
 		send_command_sensor(line);
		boost::this_thread::sleep(boost::posix_time::milliseconds(100));
		num_obs++;*/

 	}

 }


}


// Thread that starts the go_to behavior
char * get_laser_values(void )
{

 char world_file[250]= " ";
 static char environment[250]= " ";
 int j;
 Raw observations;
 //static int flg=0;
 int num_obs=1;
 static char *line;
 char tmp[MAX_NUM_CHARACTERS];
 char wait[10];
 static int flg=1;
 char cr[3];


 //printf("Environment %s\n",inputs.environment);
 cr[0]='\n';

 // it reads the environment everytime is selected by the GUI
 //if(flg==1){
 if(strcmp(environment,inputs.environment) != 0){
	sprintf(world_file,"%s%s.wrl",inputs.path,inputs.environment);
	//printf("Environment %s\n",world_file);
       	read_environment(world_file,0);
	line = (char *) malloc((unsigned) MAX_NUM_CHARACTERS*30*sizeof(char *));
	strcpy(environment,inputs.environment);
	//flg=0;
 }	

    
 //printf("get_laser_values %d Pose robot %f %f %f \n",num_obs,coord_robot.xc,coord_robot.yc,coord_robot.anglec);

 get_sensor_values(coord_robot,inputs.theta_sensor,inputs.range_sensor,&observations,inputs.num_sensors,inputs.largest_value);

 // ( sensor laser 2 0.400000 -0.200000 0.160162 0.175607 )
 sprintf(line,"( sensor laser %d %f %f ",inputs.num_sensors,inputs.range_sensor,inputs.theta_sensor);

 for(j=0;j<inputs.num_sensors;j++){
        	//printf("%d %f\n",j,observations.sensors[j]);
		sprintf(tmp,"%2.2f ",observations.sensors[j]);
		strcat(line,tmp);
 }

 strcat(line,")");
 //strcat(line,cr);

 //printf("getlaservalues line %s",line);

 // it sends the sensing data
 return line;

}



int main(int argc, char *argv[])
{
	Module *module;
	pthread_t a_thread;


	// Configure the module to run on PORT
	module=init_BB_sensor_actuator_gui(PORT);

	 // It sets a thread for executing the commands
        //pthread_create(&a_thread, NULL, sensor_thread, NULL);

	// it waits forever
	while(1){
		usleep(1);
	}

}

