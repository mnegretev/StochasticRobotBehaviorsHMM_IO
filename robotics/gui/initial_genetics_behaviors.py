# initial_genetics_behaviors.py
'''
@author: Jesus Savage, UNAM-FI, 8-2021
@author: Jesus Savage, UNAM-FI, 7-2023
'''



import sys
import math
import os


# Initial Path to be set in the GUI
INITIAL_PATH = '../../data/data_3/'
ORIGINAL_PATH = '../../data/original_data/'

ENVIRONMENT = 'random'
TESTING = 0


# VQ variables
# To create new VQ put this variable with 1
new_trainning = 0
#new_trainning = 1
#size_vq_ext = 8
size_vq_ext = 32
num_bits_symbols = int(math.log(size_vq_ext)/math.log(2))


# Worlds variables
#num_worlds = 13
num_worlds = 13
num_points_worlds = 4
#num_points_worlds = 10
num_obstacles = 20
size_obstacles = 0.22
#flg_worlds = 1 # put this flag to 1 if in every generation new environments are created
flg_worlds = 0 # put this flag to 1 if in every generation new environments are created
flg_save_worlds = 0 # put this flag to 1 if the best and worst worlds are saved


#Genetics variables
#num_individuals = 10 
#num_individuals = 20
num_individuals = 100
mutation_factor = 0.6
#mutation_factor = 0.6
cross_factor = 0.90
#cross_factor = 0.90
num_best_factor = 0.80  #porcentage_num_bits_mut
#num_best_factor = 0.80
#flg_set_first_new_generation = 1 # put this flag to 1 if a first new generation is created 
flg_set_first_new_generation = 0 # put this flag to 1 if a first new generation is created 

#General State Machine variables
num_outputs = 8
num_bits_outputs = int(math.log(num_outputs)/math.log(2))
#print "num_bits_outputs ", str(num_bits_outputs)
num_states = 16
num_bits_states = int(math.log(num_states)/math.log(2))
#print "num_bits_states ", str(num_bits_states)
num_bits_intensity = 2
num_bits_angle_light = 3
#num_bits_variables = 3
#num_bits_variables = 6
#print "num_bits_variables ",num_bits_variables
st_out = 1
nn_rec = 0
Meally = 0


if len (sys.argv) < 2 :
    print "\n**********************************************************************************************************"
    print "Usage: python GUI_behaviors.py num_behavior"
    print "Where num_behavior:"
    print "0 = Tests Best Behaviors"
    print "1 = Stochastic FSM outputs"
#    print "2 = HMM Meally"
    print "3 = FSM"
    print "4 = Reactive"
    print "5 = Reactive Stochastic"
    print "6 = Neural_Networks stochastic_outputs num_recurrent"
    print "		Example: python GUI_behaviors.py 6 0 0"
    print "		Example: python GUI_behaviors.py 6 1 0"
    print "		Example: python GUI_behaviors.py 6 0 4"
    print "		Example: python GUI_behaviors.py 6 1 4"
    print "7 = Potential fields num_bits_variables num_bits_fractions"
    print "		Example: python GUI_behaviors.py 7 16 8"
    print "		Example: python GUI_behaviors.py 7 8 7"
    print "8 = MDP"
    print "9 = Testing Evolved Populations num_behavior environment_type(0 = office, polygons)"
    print " "
    print "             Example for testing FSM behaviors: "
    print "             			python GUI_behaviors.py 9 3 0"
    print "             			python GUI_behaviors.py 9 3 1"
    print "             Example for testing Stochastic FSM behaviors: "
    print "             			python GUI_behaviors.py 9 1 0"
    print "             			python GUI_behaviors.py 9 1 1"
    print "             Example for testing pure Reactive behaviors: "
    print "             			python GUI_behaviors.py 9 4 0"
    print "             			python GUI_behaviors.py 9 4 1"
    print "             Example for testing stochastic Reactive behaviors: "
    print "             			python GUI_behaviors.py 9 5 0"
    print "             			python GUI_behaviors.py 9 5 1"
    print "             Example for testing input/state MDP behaviors: "
    print "             			python GUI_behaviors.py 9 8 0"
    print "             			python GUI_behaviors.py 9 8 1"
    print "             Example for testing input/state Moore behaviors: "
    print "             			python GUI_behaviors.py 9 11 0"
    print "             			python GUI_behaviors.py 9 11 1"
    print "             Example for testing input/state HMM Moore behaviors: "
    print "             			python GUI_behaviors.py 9 12 0"
    print "             			python GUI_behaviors.py 9 12 1"
    print "             Example for testing NN behaviors: "
    print "             			python GUI_behaviors.py 9 6 0 0 0"
    print "             			python GUI_behaviors.py 9 6 1 0 0"
    print "             Example for testing Stochastic NN behaviors: "
    print "             			python GUI_behaviors.py 9 6 0 1 0"
    print "             			python GUI_behaviors.py 9 6 1 1 0"
    print "             Example for testing Recurrent NN behaviors: "
    print "             			python GUI_behaviors.py 9 6 0 0 4"
    print "             			python GUI_behaviors.py 9 6 1 0 4"
    print "             Example for testing Recurrent Stochastic NN behaviors: "
    print "             			python GUI_behaviors.py 9 6 0 1 4"
    print "             			python GUI_behaviors.py 9 6 1 1 4"
    print "10 = Meally FSM Input/State"
    print "11 = Moore FSM Input/State"
    print "12 = HMM Moore"
    print "13 = HMM Moore State Machine"
    print "\n**********************************************************************************************************"
    sys.exit (1)


#for x in sys.argv:
     #print "Argument: ", x

num_behavior = int(sys.argv[1])
#print "Behavior ", str(num_behavior)

print "\n**********************************************************************************************************"

if num_behavior == 9:
	num_behavior = int(sys.argv[2])
	ENV = int(sys.argv[3])
	TESTING = 1
        if ENV == 0:
		#INITIAL_PATH = '/home/biorobotica/data/test_2/'
		INITIAL_PATH = '../../data/test_2/'
                #num_worlds = 9
                num_worlds = 9
                #ENVIRONMENT = 'random_office'
                ENVIRONMENT = 'test'
        else:
                #INITIAL_PATH = '/home/biorobotica/data/test_1/'
		INITIAL_PATH = '../../data/test_1/'
                num_worlds = 5
                #ENVIRONMENT = 'random_test'
                ENVIRONMENT = 'test'
        #print "* Testing ",ENVIRONMENT," environment                                                                             *"
#else:
        #print "* Evolving a behavior                                                                                   *"
		
if num_behavior == 0:
	print "*													*"
        print "* Testing behaviors:											*"
        print "* Select the behavior to test in the GUI's Test fields.							*"
	print "* Select the path's environment in the field Path.							*"
	print "* Select the environment in the field World and the robot's results in the field Robot Behavior.        *"
	print "* There are 14 environments: random, random_1, random_2,..., random_13. 				*"
	print "* When a new environment is selected push the Plot Map button to display it.				*"
	print "* To display the sensors select the check button Show sensors		 				*"
	print "* To display the movement of the robot step by step select the check button Show robot movements	*"
	print "* In the PLANNER window select the robot's origen with the mouse's left button.				*"
	print "* Select the robot's destination with the mouse's right button.						*"
	print "* After the robot reaches the destination with the mouse's right button select a new one.		*"
	print "* To see original evolved robot behaviors, select the button Use Path DEMO and then select the behavior.*"
	print "*													*"
        print "*********************************************************************************************************\n"
        BEHAVIOR = "fsm"
        BEST_BEHAVIOR = "state_machine.txt"
        transform_option = "state_machine"
        st_out = 0
        num_bh = 3
	#INITIAL_PATH = '/home/biorobotica/data/test_1/'
	#ORIGINAL_PATH = '/home/biorobotica/data/original_data/'
	INITIAL_PATH = '../../data/test_1/'
	ORIGINAL_PATH = '../../data/original_data/'
	Meally = 1
        num_individuals = 10
	num_worlds = 1
	TESTING = 1

elif num_behavior == 1:
	BEHAVIOR = "fsm_st"
	BEST_BEHAVIOR = "state_machine_mem_stochastic.txt"
	transform_option = "state_machine_stochastic"
        st_out = 1
	num_bh = 9
	num_bits_variables_fsm_st = 8
	if TESTING == 0:
		print "* Evolving a FSM behavior using stochastic outputs 	                            			 *"
                INITIAL_PATH = '../../data/data_12/'
		ORIGINAL_PATH = '../../data/original_data/'
        else:
                print "* Testing a deterministic FSM behavior using stochastic outputs                                            *"
                command = INITIAL_PATH + "copy_generations_fsm_st.sh"
                print "* command: ", command,"                                           *"
                status = os.system(command)
	size_vq_ext = 32
elif num_behavior == 2:
	BEHAVIOR = "hmm"
	print "* Evolving a Meally HMM behavior 		 	                            			 *"
	BEST_BEHAVIOR = "hmm_destination_avoidance_fsm.prb"
	transform_option = "state_machine_hmm"
	num_bh = 10
        st_out = 0
	num_bits_variables_hmm = 8
	num_states_hmm = 8
	Meally = 1
	num_individuals = 10 
elif num_behavior == 3:
	BEHAVIOR = "fsm"
	BEST_BEHAVIOR = "state_machine_mem.txt"
	transform_option = "state_machine"
	num_bh = 4
	st_out = 0
	if TESTING == 0:
		print "* Evolving a deterministic FSM behavior 	                            			         *"
		#INITIAL_PATH = '/home/biorobotica/data/data_3/'
		INITIAL_PATH = '../../data/data_3/'
		#num_worlds = 13
	else:
		print "* Testing a deterministic FSM behavior                                                           *"
		#INITIAL_PATH = '../../data/data_3/'
		command = INITIAL_PATH + "copy_generations_fsm.sh"
                print "* command: ", command,"                                           *"
                status = os.system(command)


	size_vq_ext = 32
	#ENVIRONMENT = 'random'
elif num_behavior == 4:
	BEHAVIOR = "reactive"
	BEST_BEHAVIOR = "reactive_table_vq.txt"
	transform_option = "reactive"
	st_out = 0
	num_bh = 8
	if TESTING == 0:
		print "* Evolving a reactive behavior 	                            			         		 *"
		#INITIAL_PATH = '/home/biorobotica/data/data_10/'
        	#ORIGINAL_PATH = '/home/biorobotica/data/data_10/'
		INITIAL_PATH = '../../data/data_10/'
        	ORIGINAL_PATH = '../../data/original_data/'
	else:
		print "* Testing a reactive behavior								*"
                command = INITIAL_PATH + "copy_generations_reactive.sh"
                print "* command: ", command,"                                           *"
                status = os.system(command)


	num_individuals = 100
	size_vq_ext = 32
elif num_behavior == 5:
        BEHAVIOR = "reactive_stochastic"
        BEST_BEHAVIOR = "stochastic_reactive_table_vq.prb"
        transform_option = "reactive_stochastic"
        st_out = 1
        num_bh = 8
	num_bits_variables_reactive_st = 8
	if TESTING == 0:
		print "* Evolving a reactive behavior using stochastic outputs:	                            	         *"
                INITIAL_PATH = '../../data/data_13/'
                ORIGINAL_PATH = '../../data/original_data/'
        else:
                print "* Testing an stochastic reactive behavior                                                            *"
                command = INITIAL_PATH + "copy_generations_reactive_st.sh"
                print "* command: ", command,"                                           *"
                status = os.system(command)
	size_vq_ext = 32


elif num_behavior == 6:
	if len (sys.argv) < 3 :

		print "* Evolving neural networks:										 *"
		print "* Usage:python GUI_behaviors.py 6 stochastic_outputs num_recurrent					 *"
    		print "* Example: python GUI_behaviors.py 6 0 0								 *"
    		print "* Example: python GUI_behaviors.py 6 1 0								 *"
    		print "* Example: python GUI_behaviors.py 6 0 4								 *"
    		print "* Example: python GUI_behaviors.py 6 1 4								 *"
		print "**********************************************************************************************************\n" 

    		sys.exit (1)

	
	#print "\n******************************************************************************\n"
	

   	if TESTING == 0:
		st_out = int(sys.argv[2])
		num_recurrent = int(sys.argv[3])
	else:
		st_out = int(sys.argv[4])
		num_recurrent = int(sys.argv[5])
		
	if st_out == 0:
		# Not stochastic outputs
		if num_recurrent == 0:
        		BEHAVIOR = "nn"
			BEST_BEHAVIOR = "nn.txt"
			nn_rec = 0
        		transform_option = BEHAVIOR 
			if TESTING == 0:
				print "* Evolving a non recurrent neural network behavior with no stochastic outputs			 *"
                		INITIAL_PATH = '../../data/data_1/'
                		ORIGINAL_PATH = '../../data/original_data/'
				size_vq_ext = 32
        		else:
				num_bh = 11
        			st_out = 0
        			flg_vq = 1
				num_variables_nn=0

                		print "* Testing a non recurrent neural network behavior                                                        *"
                		command = INITIAL_PATH + "copy_generations_nn.sh"
                		print "* command: ", command,"                                           *"
                		status = os.system(command)
				size_vq_ext = 32
		else:
			BEHAVIOR = "rnn"
			BEST_BEHAVIOR = "rnn.txt"
			nn_rec = 1
        		transform_option = BEHAVIOR 
			if TESTING == 0:
				print "* Evolving a recurrent neural network behavior with no stochastic outputs			 *"
                                INITIAL_PATH = '../../data/data_2/'
                                ORIGINAL_PATH = '../../data/original_data/'
				size_vq_ext = 32
                        else:
				num_bh = 11
        			st_out = 0
        			flg_vq = 1
				num_variables_nn=0
                                print "* Testing a recurrent neural network behavior                                                        *"
                                command = INITIAL_PATH + "copy_generations_rnn.sh"
                                print "* command: ", command,"                                           *"
                                status = os.system(command)
				size_vq_ext = 32

        else:
		# Stochastic outputs
		if num_recurrent == 0:
        		BEHAVIOR = "nn_st"
			BEST_BEHAVIOR = "nn_st.txt"
			nn_rec = 0
        		transform_option = BEHAVIOR 
			if TESTING == 0:
				print "* Evolving a non recurrent neural network behavior with stochastic outputs			 *"
                                INITIAL_PATH = '../../data/data_5/'
                                ORIGINAL_PATH = '../../data/original_data/'
				size_vq_ext = 32
                        else:
				num_bh = 11
				st_out = 1
                                flg_vq = 1
                                num_variables_nn=0

                                print "* Testing a non recurrent neural network behavior with stochastic outputs                               *"
                                command = INITIAL_PATH + "copy_generations_nn_st.sh"
                                print "* command: ", command,"                                           *"
                                status = os.system(command)
				size_vq_ext = 32

		else:
			BEHAVIOR = "rnn_st"
			BEST_BEHAVIOR = "rnn_st.txt"
			nn_rec = 1
        		transform_option = BEHAVIOR 
			if TESTING == 0:
				print "* Evolving a recurrent neural network behavior with stochastic outputs				 *"
                                INITIAL_PATH = '../../data/data_11/'
                                ORIGINAL_PATH = '../../data/original_data/'
				size_vq_ext = 32
                        else:
                                print "* Testing a non recurrent neural network behavior with stochastic outputs                               *"

				num_bh = 11
                                flg_vq = 1
                                num_variables_nn=0

                                command = INITIAL_PATH + "copy_generations_rnn_st.sh"
                                print "* command: ", command,"                                           *"
                                status = os.system(command)
				size_vq_ext = 32




	#print "\n******************************************************************************\n"
        #print "st_out ",st_out
        #print "num_recurrent ",num_recurrent
	num_layers = 2
	#num_layers = 6
        num_inputs_delayed = 0
        num_nn_layer = range(10)
	flg_real_data=1 # 0 quantized data; 1 real data
	if flg_real_data == 0:
		#num_inputs_sensors = 5 + num_bits_symbols # quantized values of destination & intensity & binary obstacles 
		num_inputs_sensors = num_bits_symbols # quantized values of quadrant destination & intensity & obstacles 
        	num_nn_layer[0] = num_inputs_sensors * ( 1 + num_inputs_delayed) + num_recurrent
	else:
		num_inputs_sensors = 18 # real values of destination & intensity & 16 sensor values 
        	num_nn_layer[0] = 18 + num_recurrent

	#print "num_inputs_sensors " + str(num_inputs_sensors)
        #num_nn_layer[1] = 10
        #num_nn_layer[2] = 5
        #num_nn_layer[3] = 10
        #num_nn_layer[4] = 5
        #num_nn_layer[5] = 10
        #num_nn_layer[6] = num_outputs + num_recurrent


	num_nn_layer[1] = 40
        num_nn_layer[2] = num_outputs + num_recurrent




        num_variables_nn=0
        for i in range(0, num_layers):
                num_variables_nn=num_nn_layer[i]*(num_nn_layer[i+1]+1)+num_variables_nn;
	 	#print "num_nn_layer[",i,"] ",num_nn_layer[i]
        	#print "Num. Variables NN ",i," ",num_variables_nn
	#print "num_nn_layer[",i,"] ",num_nn_layer[i]
        #print "Num. Variables NN",num_variables_nn
        num_bh = 11
	#num_bits_variables = 8
	#num_outputs = num_bits_outputs

	layers = str(num_nn_layer[1])
        #print "num_layers ",num_layers, " layers ",layers
        for ll in range(2, num_layers):
                 #print "num_nn_layer[",str(ll),"] = ",str(num_nn_layer[ll])
                 layers = layers + " " + str(num_nn_layer[ll])
                 #print "layers ",layers


        #print "layers ",layers

   #else:


elif num_behavior == 7:
        if len (sys.argv) < 3 :

		print "* Evolving a potential field behavior:                                                           	 *"
                print "* Usage:python GUI_behaviors.py 7 num_bits_variables num_bits_fractions					 *"
                print "* Example: python GUI_behaviors.py 7 16 8								 *"
                print "* Example: python GUI_behaviors.py 7 8 7								 *"
		print "**********************************************************************************************************\n" 

                sys.exit (1)


	num_bits_variables_pot = int(sys.argv[2])
        num_bits_variables_pot_float = int(sys.argv[3])
	num_variables_pot = 5
	BEHAVIOR = "potentials"
        BEST_BEHAVIOR = "pot_cnt.txt"
        transform_option = BEHAVIOR
	num_bh = 5
	st_out = 0
        #print "Evolving constants for a potential field behavior"

	if TESTING == 0:
		print "* Evolving a potential field behavior                                                         		 *"
                INITIAL_PATH = '../../data/data_4/'
                ORIGINAL_PATH = '../../data/original_data/'
        else:
		print "* Testing a potential field behavior                                                         		 *"
                command = INITIAL_PATH + "copy_generations_potential.sh"
                print "* command: ", command,"                                           *"
                status = os.system(command)



elif num_behavior == 8:
        BEHAVIOR = "mdp"
        BEST_BEHAVIOR = "mdp_environment.mdp"
        transform_option = "mdp"
        st_out = 0
        num_bh = 12
	num_bits_variables_mdp = 8
        num_bits_variables_mdp_float = 7
	num_variables_mdp = 72 + 4 # 9 prb X 8 actions + 3 rewards and gamma
	num_individuals = 100
	if TESTING == 0:
		print "* Evolving a mdp behavior                                                           			 *"
		#INITIAL_PATH = '/home/biorobotica/data/data_7/'
		#ORIGINAL_PATH = '/home/biorobotica/data/data_7/'
		INITIAL_PATH = '../../data/data_7/'
        	ORIGINAL_PATH = '../../data/original_data/'
	else:
		print "* Testing a mdp behavior                                                           			 *"
                command = INITIAL_PATH + "copy_generations_mdp.sh"
                print "* command: ", command,"                                           *"
                status = os.system(command)

	size_vq_ext = 8
elif num_behavior == 10:
        BEHAVIOR = "infsm"
        BEST_BEHAVIOR = "input_state_machine_mem.txt"
        transform_option = "in_state_machine"
        num_bh = 13
        st_out = 0
	if TESTING == 0:
		print "* Evolving a deterministic Meally FSM input/state behavior"
		#INITIAL_PATH = '/home/biorobotica/data/data_8/'
        	#ORIGINAL_PATH = '/home/biorobotica/data/data_8/'
		INITIAL_PATH = '../../data/data_8/'
                ORIGINAL_PATH = '../../data/original_data/'
	else:
                print "* Testing a deterministic Meally FSM input/state behavior"
                # It copies the last ../data/data_8/input_state_machine_mem.txt 
                #command = "cp ../../data/data_8/" + BEST_BEHAVIOR + " " + INITIAL_PATH
		command = INITIAL_PATH + "copy_generations_infsm_meally.sh"
                print "cp command: ", command
                status = os.system(command)		

        #num_worlds = 13
	num_individuals = 100
	size_vq_ext = 32
        #ENVIRONMENT = 'random'
elif num_behavior == 11:
        BEHAVIOR = "infsm"
        BEST_BEHAVIOR = "input_state_machine_mem.txt"
        transform_option = "in_state_machine"
        num_bh = 14
        st_out = 0
	if TESTING == 0:
        	print "* Evolving a deterministic Moore FSM input state behavior                                                      *"
		#INITIAL_PATH = '/home/biorobotica/data/data_9/'
        	#ORIGINAL_PATH = '/home/biorobotica/data/data_9/'
		INITIAL_PATH = '../../data/data_9/'
                ORIGINAL_PATH = '../../data/original_data/'
	else:
                print "* Testing a deterministic Moore FSM input/state behavior"
                # It copies the last ../data/data_9/input_state_machine_mem.txt 
                #command = "cp ../../data/data_9/" + BEST_BEHAVIOR + " " + INITIAL_PATH
		command = INITIAL_PATH + "copy_generations_infsm_moore.sh"
                print "cp command: ", command
                status = os.system(command)


        #num_worlds = 13
        num_individuals = 100
	#size_vq_ext = 8
	size_vq_ext = 32
        #ENVIRONMENT = 'random'
elif num_behavior == 12:
	BEHAVIOR = "hmm"
	BEST_BEHAVIOR = "hmm_destination_avoidance_fsm.prb"
	transform_option = "state_machine_hmm"
	num_bh = 15
        st_out = 0
	num_bits_variables_hmm = 8
	num_states_hmm = 8
	Meally = 0
	num_individuals = 100 
	if TESTING == 0:
		print "* Evolving a Moore HMM behavior 		 	                            			 *"
		#INITIAL_PATH = '/home/biorobotica/data/data_6/'
        	#ORIGINAL_PATH = '/home/biorobotica/data/data_6/'
		INITIAL_PATH = '../../data/data_6/'
                ORIGINAL_PATH = '../../data/original_data/'
	else:
		print "* Testing a Moore HMM behavior								*"
                command = INITIAL_PATH + "copy_generations_hmm_moore.sh"
                print "* command: ", command,"						 *"
                status = os.system(command)

	#size_vq_ext = 8
	size_vq_ext = 32
	flg_vq = 1
elif num_behavior == 13:
        print "* Evolving a Moore HMM State Machine behavior                                                            *"
        BEHAVIOR = "hmm_state_machine"
        BEST_BEHAVIOR = "hmm_fsm.prb"
        transform_option = "hmm_state_machine"
        num_bh = 16
        st_out = 0
        num_bits_variables_hmm = 16
        num_states_hmm = 4
        Meally = 0
	flg_vq = 1
        num_individuals = 100
        if TESTING == 0:
                INITIAL_PATH = '../../data/data_18/'
                ORIGINAL_PATH = '../../data/original_data/'
        else:
                print "* Testing a Moore HMM State Machine behavior                                                           *"
                command = INITIAL_PATH + "copy_generations_hmm_moore_fsm.sh"
                print "* command: ", command,"                                           *"
                status = os.system(command)

        size_vq_ext = 8
else:
	print "Behavior does not exist"
	print "Usage: python GUI_behaviors.py num_behavior"
    	print "Where num_behavior:"
    	print "0 = Tests Behaviors"
    	print "1 = Stochastic FSM outputs"
    	print "2 = HMM"
    	print "3 = FSM"
    	print "4 = Reactive"
    	print "5 = Reactive Stochastic"
    	print "6 = Neural_Networks stochastic_outputs num_recurrent"
    	print "             Example: python GUI_behaviors.py 6 0 0"
    	print "             Example: python GUI_behaviors.py 6 1 0"
    	print "             Example: python GUI_behaviors.py 6 0 4"
    	print "             Example: python GUI_behaviors.py 6 1 4"
    	print "7 = Potential fields num_bits_variables num_bits_fractions"
    	print "             Example: python GUI_behaviors.py 7 16 8"
    	print "             Example: python GUI_behaviors.py 7 8 7"
    	print "8 = MDP"
    	print "9 = Testing Evolved Populations num_behavior environment_type(0 = office, polygons)"
    	print "    Remember to first copy from the path where were generated the behavior population the following files:          "
    	print "    1. avoid_behavior*.dat, example: cp ../data_7/avoid_mdp_*.dat ../test_2 "
    	print "    2. num_generations_behavior*.dat, example: cp ../data_7/num_generations_mdp.dat ../test_2 "
	print " "
	print " Examples"
    	print "             Example for testing FSM behaviors: "
    	print "             			python GUI_behaviors.py 9 3 0"
    	print "             			python GUI_behaviors.py 9 3 1"
    	print "             Example for testing pure Reactive behaviors: "
    	print "             			python GUI_behaviors.py 9 4 0"
    	print "             			python GUI_behaviors.py 9 4 1"
    	print "             Example for testing input/state MDP behaviors: "
    	print "             			python GUI_behaviors.py 9 8 0"
    	print "             			python GUI_behaviors.py 9 8 1"
    	print "             Example for testing input/state Moore behaviors: "
    	print "             			python GUI_behaviors.py 9 11 0"
    	print "             			python GUI_behaviors.py 9 11 1"
    	print "             Example for testing input/state HMM Moore behaviors: "
    	print "             			python GUI_behaviors.py 9 12 0"
    	print "             			python GUI_behaviors.py 9 12 1"
    	print "10 = Meally FSM Input/State"
    	print "11 = Moore FSM Input/State"
    	print "12 = HMM Moore"
	print "**********************************************************************************************************\n" 

    	sys.exit (1)
	
if num_behavior != 0:
	if TESTING == 0:
		print "*                                                                                                        *"
		print "* To continue evolving individuals:									 *"
		print "* 	1. Put the number of generations in the Number of Generations field.                             *"
		print "* 	2. Push the button Genetic Algorithm to start the selected behavior evolution.                   *"
		print "*                                                                                                        *"
		print "* If a complete new generation will be created, select the check button New generation.                  *"
		print "*                                                                                                        *"
		print "**********************************************************************************************************\n" 
	else:
		print "* 	1. Push the button Test Generation to start the selected behavior testing.                       *"
		print "**********************************************************************************************************\n" 


PREVIOUS_BEHAVIOR = BEHAVIOR
PREVIOUS_BEST_BEHAVIOR = BEST_BEHAVIOR
Previous_bh = num_bh

#print "Behavior ",BEHAVIOR
#print "Previous Behavior ",PREVIOUS_BEHAVIOR
#print "Previous Best Behavior ",PREVIOUS_BEST_BEHAVIOR

#print "Behavior ", str(num_bh)
