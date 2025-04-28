import os
import Tkinter as tk
import tkFileDialog
import tkMessageBox
from Tkinter import *



def toggleEvaluatePerformanceRobot(self):
        global PATH
        global File_Name
        global mouse_1_x
        global mouse_1_y
        global mouse_3_x
        global mouse_3_y
        global angle_robot
        global flg_plt
        global advance_robot
        global max_angle_robot
        global largest
        global new_generation
        global total_num_generations
        global num_training
        global previous_num_generations
	global C

	self.EvaluateButton['bg'] = 'red'
        self.EvaluateButton['activebackground'] = 'red'
        #C.update_idletasks()

	advance_robot = float(self.advance_robot.get())
        max_angle_robot = float(self.max_angle_robot.get())
        largest = float(self.largest.get())

	PATH = self.path.get()
        print 'EvaluatePerformanceRobot Robot PATH ',PATH
        File_Name = self.file.get()
        File_Name_cpy = File_Name

        # Probability file for adding noise
        file_name_prb = 'random_settings_advance_angle_sensors.dat'
        FILE_PRB = PATH + file_name_prb
        FILE = PATH + File_Name + '.ord'


        # Noise Ranges
        z = largest/100
        zdst = largest/1000
        y = 0.05*max_angle_robot
        x = 0.1*advance_robot


        # Worlds variables
        num_worlds = 1
        num_points_worlds = 10
        num_obstacles = 20
	size_obs = 0.08
	size_dx = 1.2
	size_dy = 1.2

	# Number of iterations
	iterations = 21 # Number of iterations to create num_worlds
	num = 41        # Number of times the adding noise is incremented
        inc_noise = 0.15 # increment of the noise, delta_noise = delta_noise + inc_noise
			# range_1 = -x*delta_noise
          		# range_2 = x*delta_noise

	inc_obs = 0.015 # increments of the obstacles' radio in the environments


        fit_average_hmm = 0.0
        fit_average_viterbi = 0.0
	fit_average_fsm = 0.0
	fit_average_fsm_human = 0.0
	fit_average_nn = 0.0
	fit_average_hmm_human = 0.0

        # it deletes previous HMM fitness file
        FILE_fitness_hmm = PATH + 'fitness_hmm.dat'
	command = "rm " + FILE_fitness_hmm
        print "Command delete: ", command
        status = os.system(command)

	# it deletes previous Viterbi fitness file
        FILE_fitness_viterbi = PATH + 'fitness_viterbi.dat'
        command = "rm " + FILE_fitness_viterbi
        print "Command delete: ", command
        status = os.system(command)


	# it deletes previous fitness FSM file
        FILE_fitness_fsm = PATH + 'fitness_fsm.dat'
        command = "rm " + FILE_fitness_fsm
        print "Command delete: ", command
        status = os.system(command)


        # It deletes the NN fitness file
        FILE_fitness_nn = PATH + 'fitness_nn.dat'
        command = "rm " + FILE_fitness_nn
        print "Command delete: ", command
        status = os.system(command)

	# it deletes previous fitness fsm human file
        FILE_fitness_fsm_human = PATH + 'fitness_fsm_human.dat'
        command = "rm " + FILE_fitness_fsm_human
        print "Command delete: ", command
        status = os.system(command)

	# it deletes previous fitness hmm human file
        FILE_fitness_hmm_human = PATH + 'fitness_hmm_human.dat'
        command = "rm " + FILE_fitness_hmm_human
        print "Command delete: ", command
        status = os.system(command)


	k = 1

	delta_size_obs = 0;
	delta_dx = 0;
	delta_dy = 0;

	for j in range(1, iterations+1):
        
	 print "\n +++++++++++++ WRL GENERATION ",str(j) + "  +++++++++++++++\n"

	 size_dx = size_dx + delta_dx
	 size_dy = size_dy + delta_dy
         command = "../generate/generate -f random -r 0.03 -m " + str(num_obstacles) + " -o " + str(size_obs) + " -dx " + str(size_dx) + " -dy " + str(size_dy) + " -nd " + str(num_points_worlds) + " -p " + PATH + " -n " + str(num_worlds) + " > " + PATH + "generate.dat"
         print "Command generate: ", command
         status = os.system(command)

	 size_obs = size_obs + inc_obs
	 delta_noise=0.0;

	 for l in range(1, num):

          print "\n *****************  TEST ",str(k) + "  ******************\n"
	  
	  print "delta noise ",str(delta_noise)

        # It generates the noise probability file
          #print 'Noise advance ',x,' angle ',y,' sensors ',z     
          file_prb = open(FILE_PRB,'w')
          # Uniform error for advance
          #range_1 = 0.0
          range_1 = -x*delta_noise
          range_2 = x*delta_noise
          value = '0 ' + str(range_1) + ' ' + str(range_2) + '\n'
          file_prb.write(value)
	  size_range=range_2*2
          # Uniform error for rotation
          range_1 = -y*delta_noise
          range_2 = y*delta_noise
          value = '0 ' + str(range_1) + ' ' + str(range_2) + '\n'
          file_prb.write(value)
          # Gausian error for sensor
          range_1 = z*delta_noise # mean
          range_2 = zdst*delta_noise # standar desviation
          value = '1 ' + str(range_1) + ' ' + str(range_2) + '\n'
          file_prb.write(value)
          file_prb.close()

	  delta_noise = delta_noise + inc_noise

          # It evaluates the human state machine
          self.robot_command.delete(0, END)
          self.robot_command.insert ( 0,"../motion_planner/GoTo_State_Machine")
          self.selection.delete(0, END)
          self.selection.insert ( 0, '4' )
          # it copies the human made state machine state_machine_obstacle_destination.txt
          command = "cp " + PATH + "state_machine_obstacle_destination.txt " + PATH + "state_machine_mem.txt"
          #print "cp command: ", command
          status = os.system(command)
          indi_STATE_MACHINE_HUMAN=self.evaluate_worlds(File_Name_cpy,num_worlds,1)
          #value = str(delta_size_obs) + " " + str(delta_noise) + " " + str(indi_STATE_MACHINE_HUMAN)
          value = str(size_obs) + " " + str(size_range) + " " + str(indi_STATE_MACHINE_HUMAN)
          command = "echo " + value + " >> " + FILE_fitness_fsm_human
          print "Command STATE MACHINE HUMAN: ", command
          status = os.system(command)
          # It copies the last *.raw  and *wrl files of this evaluation
          command = "cp " + PATH + File_Name_cpy + "_"+ str(num_worlds) + '.wrl '  + PATH + "fsm_human_" + str(k) + ".wrl"
          print "cp command FSM world: ", command
          status = os.system(command)
          command = "cp " + PATH + File_Name_cpy + "_"+ str(num_worlds) + '.raw '  + PATH + "fsm_human_" + str(k) + ".raw"
          print "cp command FSM raw: ", command
          status = os.system(command)
          print "Evaluation HUMAN FSM ",str(indi_STATE_MACHINE_HUMAN)
	  fit_average_fsm_human = fit_average_fsm_human + indi_STATE_MACHINE_HUMAN


         # It evaluates the best FSM state machine
          self.robot_command.delete(0, END)
          self.robot_command.insert ( 0,"../motion_planner/GoTo_State_Machine")
          self.selection.delete(0, END)
          self.selection.insert ( 0, '4' )
	  # it copies the genetics best state machine
          command = "cp " + PATH + "best_fsm.txt " + PATH + "state_machine_mem.txt"
          #print "cp Best FSM command: ", command
          status = os.system(command)
          indi_STATE_MACHINE=self.evaluate_worlds(File_Name_cpy,num_worlds,1)
          #value = str(delta_size_obs) + " " + str(delta_noise) + " " + str(indi_STATE_MACHINE)
          value = str(size_obs) + " " + str(size_range) + " " + str(indi_STATE_MACHINE)
          command = "echo " + value + " >> " + FILE_fitness_fsm
          print "Command STATE MACHINE: ", command
          status = os.system(command)
          # It copies the last *.raw  and *wrl files of this evaluation
          command = "cp " + PATH + File_Name_cpy + "_"+ str(num_worlds) + '.wrl '  + PATH + "fsm_" + str(k) + ".wrl"
          print "cp command FSM world: ", command
          status = os.system(command)
          command = "cp " + PATH + File_Name_cpy + "_"+ str(num_worlds) + '.raw '  + PATH + "fsm_" + str(k) + ".raw"
          print "cp command FSM raw: ", command
          status = os.system(command)
          print "Evaluation FSM ",str(indi_STATE_MACHINE_HUMAN)
          fit_average_fsm = fit_average_fsm + indi_STATE_MACHINE



	  # It evaluates the best NN state machine
	  self.robot_command.delete(0, END)
          self.robot_command.insert ( 0,"../state_machine_nn/GoTo_State_Machine_NN")
          self.selection.delete(0, END)
          self.selection.insert ( 0, '3' )
	  # it copies the best genetics NN
          command = "cp " + PATH + "best_nn.txt " + PATH + "rnn_fsm.txt"
          print "cp Best NN command: ", command
          status = os.system(command)
          indi_STATE_MACHINE_NN=self.evaluate_worlds(File_Name_cpy,num_worlds,1)
          #value = str(delta_size_obs) + " " + str(delta_noise) + " " + str(indi_STATE_MACHINE_NN)
          value = str(size_obs) + " " + str(size_range) + " " + str(indi_STATE_MACHINE_NN)
          command = "echo " + value + " >> " + FILE_fitness_nn
          print "Command STATE MACHINE NN: ", command
          status = os.system(command)
          # It copies the last *.raw  and *wrl files of this evaluation
          command = "cp " + PATH + File_Name_cpy + "_"+ str(num_worlds) + '.wrl '  + PATH + "nn_" + str(k) + ".wrl"
          print "cp command NN world: ", command
          status = os.system(command)
          command = "cp " + PATH + File_Name_cpy + "_"+ str(num_worlds) + '.raw '  + PATH + "nn_" + str(k) + ".raw"
          print "cp command NN raw: ", command
          status = os.system(command)
          print "Evaluation nn ",str(indi_STATE_MACHINE_NN)
          fit_average_nn = fit_average_nn + indi_STATE_MACHINE_NN


	  # It evaluates the best HMM state machine 
	  self.robot_command.delete(0, END)
          self.robot_command.insert ( 0,"../hmm_robots/GoTo_State_Machine_HMM")
          # It copies the Viterbi probability file to the probability file of the state machine
          name_viterbi = "hmm_best"
          command = "cp " + PATH + name_viterbi + ".prb " + PATH + "hmm_destination_avoidance_fsm.prb"
          print "cp Best HMM command: ", command
          status = os.system(command)
          indi_STATE_MACHINE_HMM=self.evaluate_worlds(File_Name_cpy,num_worlds,1)
          #value = str(delta_size_obs) + " " + str(delta_noise) + " " + str(indi_STATE_MACHINE_HMM)
          value = str(size_obs) + " " + str(size_range) + " " + str(indi_STATE_MACHINE_HMM)
          command = "echo " + value + " >> " + FILE_fitness_hmm
          print "Command STATE MACHINE HMM: ", command
          status = os.system(command)
          # It copies the last *.raw  and *wrl files of this evaluation
          command = "cp " + PATH + File_Name_cpy + "_"+ str(num_worlds) + '.wrl '  + PATH + "hmm_" + str(k) + ".wrl"
          print "cp command HMM world: ", command
          status = os.system(command)
          command = "cp " + PATH + File_Name_cpy + "_"+ str(num_worlds) + '.raw '  + PATH + "hmm_" + str(k) + ".raw"
          print "cp command HMM raw: ", command
          status = os.system(command)
          print "Evaluation HMM ",str(indi_STATE_MACHINE_HMM)
          fit_average_hmm = fit_average_hmm + indi_STATE_MACHINE_HMM


	  # It evaluates the Viterbi HMM state machine 
          self.robot_command.delete(0, END)
          self.robot_command.insert ( 0,"../hmm_robots/GoTo_State_Machine_HMM")
          # It copies the Viterbi probability file to the probability file of the state machine
	  name_viterbi = "hmm_viterbi.prb "
          command = "cp " + PATH + name_viterbi + PATH + "hmm_destination_avoidance_fsm.prb"
          print "cp HMM Viterbi command: ", command
          status = os.system(command)
          indi_STATE_MACHINE_VITERBI=self.evaluate_worlds(File_Name_cpy,num_worlds,1)
          #value = str(delta_size_obs) + " " + str(delta_noise) + " " + str(indi_STATE_MACHINE_VITERBI)
          value = str(size_obs) + " " + str(size_range) + " " + str(indi_STATE_MACHINE_VITERBI)
          command = "echo " + value + " >> " + FILE_fitness_viterbi
          print "Command VITERBI: ", command
          status = os.system(command)
          # It copies the last *.raw  and *wrl files of this evaluation
          command = "cp " + PATH + File_Name_cpy + "_"+ str(num_worlds) + '.wrl '  + PATH + "viterbi_" + str(k) + ".wrl"
          print "cp command Viterbi world: ", command
          status = os.system(command)
          command = "cp " + PATH + File_Name_cpy + "_"+ str(num_worlds) + '.raw '  + PATH + "viterbi_" + str(k) + ".raw"
          print "cp command Viterbi raw: ", command
          status = os.system(command)
          print "Evaluation VITERBI ",str(indi_STATE_MACHINE_VITERBI)
          fit_average_viterbi = fit_average_viterbi + indi_STATE_MACHINE_VITERBI

          # It evaluates the Human made HMM state machine 
          self.robot_command.delete(0, END)
          self.robot_command.insert ( 0,"../hmm_robots/GoTo_State_Machine_HMM")
          # It copies the Viterbi probability file to the probability file of the state machine
          name_viterbi = "hmm_destination_avoidance_fsm.000 "
          command = "cp " + PATH + name_viterbi + PATH + "hmm_destination_avoidance_fsm.prb"
          print "cp HMM Human command: ", command
          status = os.system(command)
          indi_STATE_MACHINE_HMM_HUMAN=self.evaluate_worlds(File_Name_cpy,num_worlds,1)
          value = str(size_obs) + " " + str(size_range) + " " + str(indi_STATE_MACHINE_HMM_HUMAN)
          command = "echo " + value + " >> " + FILE_fitness_hmm_human
          print "Command HMM Human: ", command
          status = os.system(command)
          # It copies the last *.raw  and *wrl files of this evaluation
          command = "cp " + PATH + File_Name_cpy + "_"+ str(num_worlds) + '.wrl '  + PATH + "hmm_human_" + str(k) + ".wrl"
          print "cp command HMM Human world: ", command
          status = os.system(command)
          command = "cp " + PATH + File_Name_cpy + "_"+ str(num_worlds) + '.raw '  + PATH + "hmm_human_" + str(k) + ".raw"
          print "cp command HMM Human raw: ", command
          status = os.system(command)
          print "Evaluation HMM Human ",str(indi_STATE_MACHINE_HMM_HUMAN)
          fit_average_hmm_human = fit_average_hmm_human + indi_STATE_MACHINE_HMM_HUMAN


          #print "\n ***********************************\n"
          k = k + 1

	 #delta_size_obs = delta_size_obs + inc_obs
	 inc_size = inc_obs * 1
	 delta_dx = delta_dx + inc_size
	 delta_dy = delta_dy + inc_size
	  
	

	self.EvaluateButton['bg'] = 'green'
        self.EvaluateButton['activebackground'] = 'green'


	print "\n ++++++++++++++++++++++++++++\n\n"
	fit_average_fsm_human = fit_average_fsm_human / (num-1) 
        print "Mean Evaluation HUMAN FSM ",str(fit_average_fsm_human)
	fit_average_hmm_human = fit_average_hmm_human / (num-1) 
        print "Mean Evaluation HUMAN HMM ",str(fit_average_hmm_human)
	fit_average_viterbi = fit_average_viterbi / (num-1) 
        print "Mean Evaluation VITERBI ",str(fit_average_viterbi)
	fit_average_fsm = fit_average_fsm / (num-1) 
        print "Mean Evaluation FSM ",str(fit_average_fsm)
	fit_average_hmm = fit_average_hmm / (num-1) 
        print "Mean Evaluation HMM ",str(fit_average_hmm)
	fit_average_nn = fit_average_nn / (num-1) 
        print "Mean Evaluation NN ",str(fit_average_nn)


	# It puts back the file names in the GUI
        self.file.delete(0, END)
        self.file.insert(0,File_Name)
        self.file_robot.delete(0, END)
        self.file_robot.insert(0,File_Name)

