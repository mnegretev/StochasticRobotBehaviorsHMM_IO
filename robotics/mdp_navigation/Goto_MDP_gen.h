/********************************************************************************
*                                                                            	*
*  GoTo_MDP_gen.h 			                              	     	*
*  ===================                                                       	*
*                                                                            	*
*  Description: 							     	*
*  It controls the movement of a robot using MDPs.			     	*
*  It uses a real robot or a simulated one.				     	*
*									     	*
*									     	*
*                               J. Savage, S. Muñoz                           	*
*                                                                        	*
*                               FI-UNAM 2020                                 	*
********************************************************************************/

#define PATH "../data/"
#define CENTROID_FILE "vq_images_laser"


int Num_backward=0;


// Constants definitions
#define COMMAND_TO_RUN "../mdp_stalin/mdpnav -g 1 -e 0.0008 -f "
#define COMMAND_CP "cp policy.txt "

#include "state_machine_mdp.h"



// it moves the robot from the origen to the destination using MDP state machines, it calls mdp programs
AdvanceAngle go_to_mdp_gen(Inputs inputs, int num_obs, int dest, int intensity, Raw observations) 
{

 static int flg=0;
 static int flg_read=1;
 static char last_action=' ';
 static int Time = 1;
 char file_mdp[250];
 AdvanceAngle mov_vector_destination;
 AdvanceAngle DistTheta;
 static struct mdp_database mdp;
 static int flg_omnidirectional;
 int j;
 int i=0,k;
 static float largest_value;
 char command[250];
 static char policy_file[200];
 char action;
 static char previous_action='N';
 static float rewards[25];



 if(flg==0){

 	/* It reads the mdp */
 	strcpy(mdp.objects_file,"mdp_environment");
 	printf("MDPfile %s\n", mdp.objects_file);
	// Function read_mdps in state_machine_mdp.h
 	read_mdps(&mdp,inputs.path);
	printf("Rewards %f %f %f \n",mdp.reward_0,mdp.reward_1,mdp.reward_2);
	rewards[0] = mdp.reward_0;
	rewards[1] = mdp.reward_1;
	rewards[2] = mdp.reward_2;

 	flg_omnidirectional=inputs.omni;
	largest_value=inputs.largest_value;
	flg=1;
 }

// It generates the mdp policy
 printf("MDP num_obs %d\n",num_obs);
 if((num_obs == 1) || (Time == NUM_POLICY) || (last_action == 'X')){


		// It generates the ocupancy grid for the mdp, function in file ~/robotics/utilities/utilities.h
		printf("Rewards %f %f %f \n",rewards[0],rewards[1],rewards[2]);
 		printf("MDP ocupancy num_obs %d\n",num_obs);
		ocupancy_grid_mdp(observations,inputs.num_sensors,dest,&mdp,largest_value,rewards);
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


 // It calculates the robot's movement using a MDP state machine
 action=state_machine_destination_mdp(dest, intensity, inputs.path, previous_action,mdp,flg_read);

 flg_read=0;
 printf("Executed action %c\n",action);
 last_action=action;
	
 mov_vector_destination = mdp_output(action, inputs.Mag_Advance,inputs.max_angle);
 printf("movement destination: angle  %f distance %f\n",mov_vector_destination.angle,mov_vector_destination.distance);

 previous_action=action;
 Time++;

 return(mov_vector_destination);

}



// it moves the robot from the origen to the destination using MDP state machines, it calls mdp functions
AdvanceAngle go_to_mdp_gen_stalin(Inputs inputs, int num_obs, int dest, int intensity, Raw observations)
{

 static int flg=0;
 static int flg_read=1;
 static char last_action=' ';
 static int Time = 1;
 char file_mdp[250];
 AdvanceAngle mov_vector_destination;
 AdvanceAngle DistTheta;
 static struct mdp_database mdp;
 static int flg_omnidirectional;
 int j;
 int i=0,k;
 static float largest_value;
 char command[250];
 static char policy_file[200];
 char action;
 static char previous_action='N';
 float angle_mdp;
 static char mdp_grid_file[250];
 static float rewards[25];


 if(flg==0){

        /* It reads the mdp */
        strcpy(mdp.objects_file,"mdp_environment");
#ifdef DEBUG
        printf("MDPfile %s\n", mdp.objects_file);
#endif
	// Function read_mdps in state_machine_mdp.h
        read_mdps(&mdp,inputs.path);
	/*rewards[0] = 1.00;
        rewards[1] = 0.04;
        rewards[2] = 2.04;*/
	printf("Rewards %f %f %f \n",mdp.reward_0,mdp.reward_1,mdp.reward_2);
        rewards[0] = mdp.reward_0;
        rewards[1] = mdp.reward_1;
        rewards[2] = mdp.reward_2;



        flg_omnidirectional=inputs.omni;
        largest_value=inputs.largest_value;
        sprintf(mdp_grid_file,"%smdp_environment_grid.mdp",inputs.path);
        sprintf(policy_file,"%spolicy.txt",inputs.path);
        flg=1;
 }

// It generates the mdp policy
 //printf("MDP num_obs %d\n",num_obs);
 if((num_obs == 1) || (Time == NUM_POLICY) || (last_action == 'X')){


                // It generates the ocupancy grid for the mdp, function in file ~/robotics/utilities/utilities.h
                //printf("MDP ocupancy num_obs %d\n",num_obs);
                ocupancy_grid_mdp(observations,inputs.num_sensors,dest,&mdp,largest_value,rewards);
                write_mdps(mdp,inputs.path);

		// mdpnav -g 1 -e 0.0008 -f 
		/*
                sprintf(command,"%s%smdp_environment_grid.mdp",COMMAND_TO_RUN,inputs.path);
                printf("COMMAND: %s\n",command);
                system(command);
                printf("Done.\n");
                sprintf(command,"%s%spolicy.txt",COMMAND_CP,inputs.path);
                printf("COMMAND CP: %s\n",command);
                system(command);
                printf("Done.\n");
		*/

		//mdpnav_function ../mdp_stalin/mdpnav_function.h
		mdpnav_function(mdp, mdp_grid_file, policy_file);

                // it reads the policy table
                //sprintf(policy_file,"%spolicy.txt",inputs.path);
		// function read_policy in state_machine_mdp.h
                read_policy(mdp.num_rows,mdp.num_columns,policy_file,&mdp);
#ifdef DEBUG
                for(j=1;j<=mdp.num_rows;j++){
                        for(k=1;k<=mdp.num_columns;k++){
                                printf("policy_table[%d][%d] %c\n",j,k,mdp.policy[j][k]);
                        }
                }
#endif
                flg_read=1;
                Time=1;
 }


 // It calculates the robot's movement using a MDP state machine
 action=state_machine_destination_mdp(dest, intensity, inputs.path, previous_action,mdp,flg_read);
 
 flg_read=0;
#ifdef DEBUG
 printf("Executed action %c\n",action);
#endif
 last_action=action;
       
 // function mdp_output in state_machine_mdp.h 
 mov_vector_destination = mdp_output(action, inputs.Mag_Advance,inputs.max_angle);
#ifdef DEBUG
 printf("movement destination: angle  %f distance %f\n",mov_vector_destination.angle,mov_vector_destination.distance);
#endif

 previous_action=action;
 Time++;

 return(mov_vector_destination);

}



