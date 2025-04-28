# initial_genetics.py
'''
@author: Jesus Savage, UNAM-FI, 6-2020
'''



import sys
import math


# Initial Path to be set in the GUI
#INITIAL_PATH = '../data/'
INITIAL_PATH = '/home/biorobotica/data/data_15/'
#INITIAL_PATH = '/home/biorobotica/data/data_4/'

# VQ variables
# To create new VQ put this variable with 1
new_trainning = 0
#new_trainning = 1
size_vq_ext = 8
num_bits_symbols = int(math.log(size_vq_ext)/math.log(2))


# Worlds variables
num_worlds = 13
#num_worlds = 13
num_points_worlds = 4
#num_points_worlds = 10
num_obstacles = 20
size_obstacles = 0.22
#flg_worlds = 1 # put this flag to 1 if in every generation new environments are created
flg_worlds = 0 # put this flag to 1 if in every generation new environments are created
flg_save_worlds = 0 # put this flag to 1 if the best and worst worlds are saved


#Genetics variables
num_individuals = 100 
#num_individuals = 100
mutation_factor = 0.6
#mutation_factor = 0.6
cross_factor = 0.90
#cross_factor = 0.90
num_best_factor = 0.80
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
num_bits_variables = 6
#print "num_bits_variables ",num_bits_variables
st_out = 1
nn_rec = 0


if len (sys.argv) < 2 :
    print "Usage: python GUI_robots_single_HMM.py num_behavior"
    print "Where num_behavior:"
    print "1 = Stochastic FSM outputs"
    print "2 = HMM"
    print "3 = FSM"
    print "4 = Reactive"
    print "5 = Reactive Stochastic"
    print "6 = Neural Networks st_out num_recurrent"
    print "		Example: python GUI_robots_single_HMM.py 6 1 3"
    print "		Example: python GUI_robots_single_HMM.py 6 0 3"
    print "		Example: python GUI_robots_single_HMM.py 6 1 0"
    print "7 = Potential fields num_bits_variables num_bits_fractions"
    print "		Example: python GUI_robots_single_HMM.py 7 16 8"
    print "		Example: python GUI_robots_single_HMM.py 7 8 7"
    print "8 = MDP"
    sys.exit (1)


#for x in sys.argv:
     #print "Argument: ", x

num_behavior = int(sys.argv[1])
if num_behavior == 1:
	print "\n******************************************************************************\n"
	print "Evolving a FSM behavior using stochastic outputs"
	print "\n******************************************************************************\n"
	BEHAVIOR = "fsm_st"
	BEST_BEHAVIOR = "state_machine_mem_stochastic.txt"
	transform_option = "state_machine_stochastic"
        st_out = 1
	num_bh = 9
elif num_behavior == 2:
	print "\n******************************************************************************\n"
    	print "Evolving a behavior using HMMs"
	print "\n******************************************************************************\n"
	BEHAVIOR = "hmm"
	BEST_BEHAVIOR = "hmm_destination_avoidance_fsm.prb"
	transform_option = "state_machine_hmm"
	num_bh = 10
        st_out = 0
elif num_behavior == 3:
	print "\n******************************************************************************\n"
    	print "Evolving a deterministic FSM behavior"
	print "\n******************************************************************************\n"
	BEHAVIOR = "fsm"
	BEST_BEHAVIOR = "state_machine_mem.txt"
	transform_option = "state_machine"
	num_bh = 4
	st_out = 0
elif num_behavior == 4:
	print "\n******************************************************************************\n"
    	print "Evolving a reactive behavior"
	print "\n******************************************************************************\n"
	BEHAVIOR = "reactive"
	BEST_BEHAVIOR = "reactive_table_vq.txt"
	transform_option = "reactive"
	st_out = 0
	num_bh = 8
elif num_behavior == 5:
	print "\n******************************************************************************\n"
        print "Evolving a reactive behavior using stochastic outputs"
	print "\n******************************************************************************\n"
        BEHAVIOR = "reactive_stochastic"
        BEST_BEHAVIOR = "stochastic_reactive_table_vq.prb"
        transform_option = "reactive_stochastic"
        st_out = 1
        num_bh = 8
elif num_behavior == 6:
	if len (sys.argv) < 3 :

		print "Usage:python GUI_robots_single_HMM.py 6 st_out num_recurrent"
    		print "Example: python GUI_robots_single_HMM.py 6 1 3"
    		print "Example: python GUI_robots_single_HMM.py 6 0 3"
    		print "Example: python GUI_robots_single_HMM.py 6 1 0"
    		sys.exit (1)

	print "\n******************************************************************************\n"
	st_out = int(sys.argv[2])
	num_recurrent = int(sys.argv[3])


	if st_out == 0:
		# Not stochastic outputs
		if num_recurrent == 0:
        		BEHAVIOR = "nn"
			BEST_BEHAVIOR = "nn.txt"
			nn_rec = 0
        		transform_option = BEHAVIOR 
			print "Evolving a non recurrent neural network behavior with no stochastic outputs"
		else:
			BEHAVIOR = "rnn"
			BEST_BEHAVIOR = "rnn.txt"
			nn_rec = 1
        		transform_option = BEHAVIOR 
			print "Evolving a recurrent neural network behavior with no stochastic outputs"
        else:
		# Stochastic outputs
		if num_recurrent == 0:
        		BEHAVIOR = "nn_st"
			BEST_BEHAVIOR = "nn_st.txt"
			nn_rec = 0
        		transform_option = BEHAVIOR 
			print "Evolving a non recurrent neural network behavior with stochastic outputs"
		else:
			BEHAVIOR = "rnn_st"
			BEST_BEHAVIOR = "rnn_st.txt"
			nn_rec = 1
        		transform_option = BEHAVIOR 
			print "Evolving a recurrent neural network behavior with stochastic outputs"


	print "\n******************************************************************************\n"
        print "st_out ",st_out
        print "num_recurrent ",num_recurrent
	num_layers = 6
        num_inputs_delayed = 0
        num_nn_layer = range(10)
	flg_real_data=0
	if flg_real_data == 0:
		num_inputs_sensors = 5 + num_bits_symbols # quantized values of destination & intensity & binary obstacles 
        	num_nn_layer[0] = num_inputs_sensors * ( 1 + num_inputs_delayed) + num_recurrent
	else:
		num_inputs_sensors = 18 # real values of destination & intensity & 16 sensor values 
        	num_nn_layer[0] = 18 + num_recurrent

	print "num_inputs_sensors " + str(num_inputs_sensors)
        num_nn_layer[1] = 10
        num_nn_layer[2] = 5
        num_nn_layer[3] = 10
        num_nn_layer[4] = 5
        num_nn_layer[5] = 10
        num_nn_layer[6] = num_outputs + num_recurrent
        #num_nn_layer[3] = 0

        num_variables_nn=0
        for i in range(0, num_layers):
                num_variables_nn=num_nn_layer[i]*(num_nn_layer[i+1]+1)+num_variables_nn;
	 	print "num_nn_layer[",i,"] ",num_nn_layer[i]
        	print "Num. Variables NN ",i," ",num_variables_nn
	#print "num_nn_layer[",i,"] ",num_nn_layer[i]
        print "Num. Variables NN",num_variables_nn
        num_bh = 11
	#num_bits_variables = 8
	#num_outputs = num_bits_outputs

	layers = str(num_nn_layer[1])
        #print "num_layers ",num_layers, " layers ",layers
        for ll in range(2, num_layers):
                 #print "num_nn_layer[",str(ll),"] = ",str(num_nn_layer[ll])
                 layers = layers + " " + str(num_nn_layer[ll])
                 #print "layers ",layers


        print "layers ",layers

elif num_behavior == 7:
        if len (sys.argv) < 3 :

                print "Usage:python GUI_robots_single_HMM.py 7 num_bits_variables num_bits_fractions"
                print "Example: python GUI_robots_single_HMM.py 7 16 8"
                print "Example: python GUI_robots_single_HMM.py 7 8 7"
                sys.exit (1)

        print "\n******************************************************************************\n"
	print "Evolving a potential field behavior"
	print "\n******************************************************************************\n"

	num_bits_variables_pot = int(sys.argv[2])
        num_bits_variables_pot_float = int(sys.argv[3])
	num_variables_pot = 5
	BEHAVIOR = "potentials"
        BEST_BEHAVIOR = "pot_cnt.txt"
        transform_option = BEHAVIOR
	num_bh = 5
	st_out = 0
        print "Evolving constants for a potential field behavior"

elif num_behavior == 8:
        print "\n******************************************************************************\n"
        print "Evolving a mdp behavior"
        print "\n******************************************************************************\n"
        BEHAVIOR = "mdp"
        BEST_BEHAVIOR = "mdp_environment.mdp"
        transform_option = "mdp"
        st_out = 0
        num_bh = 12
	num_bits_variables_mdp = 8
        num_bits_variables_mdp_float = 7
	num_variables_mdp = 72
	#INITIAL_PATH = '/home/biorobotica/data/data_3/'
	INITIAL_PATH = '/home/biorobotica/data/data_14/'


else:
	print "Behavior not exist"
	print "Usage: python GUI_robots_single_HMM.py num_behavior"
    	print "Where num_behavior:"
    	print "1 = Stochastic FSM outputs"
    	print "2 = HMM"
    	print "3 = FSM"
    	print "4 = Reactive"
    	print "5 = Reactive Stochastic"
    	print "6 = Neural Networks st_out num_recurrent"
    	print "		Example: python GUI_robots_single_HMM.py 6 1 3"
    	print "		Example: python GUI_robots_single_HMM.py 6 0 3"
    	print "		Example: python GUI_robots_single_HMM.py 6 1 0"
    	print "7 = Potential fields num_bits_variables num_bits_fractions"
	print "		Example: python GUI_robots_single_HMM.py 7 16 8"
        print "		Example: python GUI_robots_single_HMM.py 7 8 7"
    	print "8 = MDP"


    	sys.exit (1)





#print "Behavior ", str(num_bh)
