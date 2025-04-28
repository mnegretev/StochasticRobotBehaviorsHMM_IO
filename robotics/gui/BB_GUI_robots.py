# GUI_robots.py 
'''
@author: Jesus Savage, UNAM-FI, 11-2014
'''

import os
import Tkinter as tk
import tkFileDialog
import tkMessageBox
from Tkinter import *
import math
from random import randrange, uniform
import time
import os
import serial
import time
from pyrobotics import BB
from pyrobotics.messages import Response, Command

#---------------------------------------------------------------------------------------
#	Global Variables

use_gui = True
gui = None
gui_planner = None
gui_example = None
debug = False
count = 0
DIM_CANVAS_X = 400
DIM_CANVAS_Y = 400
dim_x = 10.0
dim_y = 10.0
radio_robot = .03
pose_x = 4.0
pose_y = 3.0
pose_tetha = 0.0
mouse_1_x = 0.0
mouse_1_y = 0.0
mouse_2_x = 0.0
mouse_2_y = 0.0
mouse_3_x = 0.0
mouse_3_y = 0.0
num_pol = 0
polygons = []
flg_mov = 1
flg_sensor = 1
delay = .05
PATH = 'path'
File_Name = 'file_name'
File_Name_robot = 'file_name'
angle_robot = 0.0
sensor = "laser"
num_sensors = 2
flg_noise = 0
start_angle = -0.2
range_angle = 0.2
delta_angle = 0.0
flg_execute = 0
robot_command = "GoTo_State_Machine"
flg_robot = 0
process_line = "line"


#------------------------------------------------------------------------------------------
#	Blackboard Definitions



#	Blackboard Commands
cnt_alive = 0

def plotlaser(c):
        global flg_mov
        global flg_sensor
        global pose_x
        global pose_y
        global pose_tetha
        global gui_planner


        #print 'command plot laser: ' + c.params
        line = c.params
        #print 'params plot laser ', line,

	plotlasergui(line)

        answer = 'plot laser'
	return Response.FromCommandObject(c, True, answer)


def robotgui(c):
	global flg_mov
	global flg_sensor
	global pose_x
	global pose_y
	global pose_tetha
	global gui_planner
	global process_line


	#print 'command robot params: ' + c.params
    	line = c.params
    	words = line.split()
        name = words[0]
	pose_x = float(words[1])
	pose_y = float(words[2])
	pose_tetha = float(words[3])
	angle_robot = pose_tetha
	str_angle = ("%3.4f" % angle_robot).strip()
	#self.robot_angle.delete(0, END)
	#self.robot_angle.insert(0,str_angle)
	#self.robot_posex.delete(0, END)
	#self.robot_posex.insert (0, words[1] )
	#self.robot_posey.delete(0, END)
	#self.robot_posey.insert (0, words[2] )
	#str_num_steps = ("%4d" % num_steps).strip()
	#self.number_steps.delete(0, END)
	#self.number_steps.insert(0,str_num_steps)
	#num_steps = num_steps + 1

	#if flg_mov == 1:
       	#id = C.create_rectangle(0, 0, DIM_CANVAS_X, DIM_CANVAS_Y, fill= "blue")
      	#C.update_idletasks()
 	gui_planner.plot_robot() 
        #	self.read_file_map(0)

		#self.plot_robot()
		#if self.var_mov.get() == 0:
        	#	C.update_idletasks()
	#else:
        	#if flg_sensor == 0:
                	#C.update_idletasks()

	#if flg_mov == 1:
        	#time.sleep(delay/2.0) # delays seconds

	#process_line=line
	#gui_planner.process_command()


        answer_robot = 'robot ' + name + ' ' + str(pose_x) + ' ' + str(pose_y) + ' ' + str(pose_tetha)
	return Response.FromCommandObject(c, True, answer_robot)




def statusgui(c):
    print 'status gui'
    return Response.FromCommandObject(c, True, 'status_gui processing')

def busy(c):
    print 'busy: gui ' + c.params
    return Response.FromCommandObject(c, True, 'busy gui')

def alive(c):
    global cnt_alive

    answer_alive = 'alive: gui ' + str(cnt_alive)
    #print 'alive: base robot ' + str(cnt_alive)
    #print answer_alive
    cnt_alive = cnt_alive + 1
    return Response.FromCommandObject(c, True, answer_alive)

def finish(c):
    print 'finish: gui ' + c.params

    global pose_x
    global pose_y
    global pose_tetha

    line = c.params
    words = line.split()
    pose_x = float(words[3])
    pose_y = float(words[4])
    pose_tetha = float(words[5])
    angle_robot = pose_tetha


    return Response.FromCommandObject(c, True, 'finish gui')


fmap = {
        'statusgui' : statusgui,
        'alive' : alive,
        'busy' : busy,
        'plotlaser' : plotlaser,
        'robotgui' : robotgui,
        'finish' : (finish, True)
        }



def ActuatorHandler(sv):
  global C
  global pose_x
  global pose_y
  global radio_robot
  global pose_tetha
  global gui_planner
  global flg_robot


  #print '[ACTUATOR] ',
  #print sv.varName
  #print sv.svType
  #if sv.size >= 0:
    #print sv.size
  #print sv.data
  line = sv.data


  words = line.split()
  
  if len(words) > 1:
	#print 'words[1] ',words[1]
        if words[1] == "robot":
                pose_x = float(words[3])
                pose_y = float(words[4])
                pose_tetha = float(words[5])
                angle_robot = pose_tetha
		#print "pose x " + str(pose_x) + " y " + str(pose_y)


  		CNT=5.0
  		X = ( DIM_CANVAS_X * pose_x ) / dim_x
  		Y = DIM_CANVAS_Y - ( DIM_CANVAS_Y * pose_y ) / dim_y
  		ROBOT_radio = ( DIM_CANVAS_X * radio_robot ) / dim_x
  		X1 = X - ROBOT_radio/2
  		Y1 = Y - ROBOT_radio/2
  		X2 = X + ROBOT_radio/2
  		Y2 = Y + ROBOT_radio/2
  		oval = C.create_oval(X1,Y1,X2,Y2, outline="black",fill="red", width=1)
  		x1 = pose_x
  		y1 = pose_y
  		angle_robot = pose_tetha
  		tetha = angle_robot + start_angle
  		x2 = x1 + (dim_x/25)*math.cos(angle_robot)
  		y2 = y1 + (dim_y/25)*math.sin(angle_robot)
  		# it plots a line
  		X1 = ( DIM_CANVAS_X * x1 ) / dim_x
  		Y1 = DIM_CANVAS_Y - ( DIM_CANVAS_Y * y1 ) / dim_y
  		X2 = ( DIM_CANVAS_X * x2 ) / dim_x
  		Y2 = DIM_CANVAS_Y - ( DIM_CANVAS_Y * y2 ) / dim_y
  		line = C.create_line(X1,Y1,X2,Y2,fill="black", arrow="last")
  		C.update_idletasks()
		flg_robot = 1

	else:
	       if words[1] == "mv":
                	distance = float(words[2])
                	angle = float(words[3])
			s = "answer mv " + str(distance) + " " + str(angle)
                	#BB.WriteSharedVar(BB.SharedVarTypes.STRING, 'sensor', s)
                	#print "sensor " + s

	       else:
			#( finish motion_planner 0.371814 0.779874 0.185400 6 0.050980)
			if words[1] == "finish":
				pose_x = float(words[3])
	                	pose_y = float(words[4])
                		pose_tetha = float(words[5])
                		angle_robot = pose_tetha
                		#print "pose x " + str(pose_x) + " y " + str(pose_y)





def GuiHandler(sv):
  #print '[GUI] ',
  #print sv.varName
  #print sv.svType
  #if sv.size >= 0:
    #print sv.size
  #print sv.data
  a = 0


def SensorHandler(sv):
  global C
  global pose_x
  global pose_y
  global radio_robot
  global pose_tetha
  global gui_planner
  global flg_robot
  global start_angle
  global delta_angle


  #print '[SENSOR] ',
  #print sv.varName
  #print sv.svType
  #if sv.size >= 0:
    #print sv.size
  #print sv.data
  line = sv.data


  words = line.split()

  if len(words) > 1:
        #print 'words[1] ',words[1]
        if words[1] == "sensor":

		#( sensor laser 2 0.400000 -0.200000 0.059984 0.090483 )
		num = int(words[3])
		range_angle =  float(words[4])
		start_angle = float(words[5])
  		#print "sensor num ",num
  		#print "sensor range_angle ",range_angle
  		#print "sensor start_angle ",start_angle

  		x1 = pose_x
  		y1 = pose_y
		angle_robot = pose_tetha
  		#print "sensor pose tetha ",pose_tetha

  		tetha = angle_robot + start_angle
  		#print "Origen Tetha ", tetha

  		data = [0] * (len(words) - 6)


                if num == 1:
                        delta_angle = range_angle
                else:
                        delta_angle = range_angle / (num - 1)
		#print "sensor delta ",delta_angle

  		j=0
		#print "len words ",len(words)
  		for i in range(6, len(words) - 1):
          		#print words[i]
          		#print "Tetha ", j," ",tetha
          		data[j] = float(words[i])
          		x2 = x1 + data[j]*math.cos(tetha)
          		y2 = y1 + data[j]*math.sin(tetha)
			# it plots a line
                	X1 = ( DIM_CANVAS_X * x1 ) / dim_x
                	Y1 = DIM_CANVAS_Y - ( DIM_CANVAS_Y * y1 ) / dim_y
                	X2 = ( DIM_CANVAS_X * x2 ) / dim_x
                	Y2 = DIM_CANVAS_Y - ( DIM_CANVAS_Y * y2 ) / dim_y
                	line = C.create_line(X1,Y1,X2,Y2,fill="blue", arrow="last")
          		#self.plot_line(x1,y1,x2,y2,"blue",0)
			id = C.create_rectangle(X2,Y2,X2+1,Y2+1, fill= "white", outline="white")
                	C.update_idletasks()

          		j=j+1
          		tetha = tetha + delta_angle


def plotlasergui(line):
  global C
  global pose_x
  global pose_y
  global radio_robot
  global pose_tetha
  global gui_planner
  global flg_robot
  global start_angle
  global delta_angle


  #print 'plotlasergui ',
  #print line


  words = line.split()

  if len(words) > 1:
        #print 'words[1] ',words[1]
        if words[1] == "sensor":

		#( sensor laser 2 0.400000 -0.200000 0.059984 0.090483 )
		num = int(words[3])
		range_angle =  float(words[4])
		start_angle = float(words[5])
  		#print "sensor num ",num
  		#print "sensor range_angle ",range_angle
  		#print "sensor start_angle ",start_angle

  		x1 = pose_x
  		y1 = pose_y
		angle_robot = pose_tetha
  		#print "sensor pose tetha ",pose_tetha

  		tetha = angle_robot + start_angle
  		#print "Origen Tetha ", tetha

  		data = [0] * (len(words) - 6)


                if num == 1:
                        delta_angle = range_angle
                else:
                        delta_angle = range_angle / (num - 1)
		#print "sensor delta angle ",delta_angle

  		j=0
		#print "len words ",len(words)
  		for i in range(6, len(words) - 1):
          		#print "range ",words[i]
          		#print "Tetha ", j," ",tetha
          		data[j] = float(words[i])
          		x2 = x1 + data[j]*math.cos(tetha)
          		y2 = y1 + data[j]*math.sin(tetha)
			# it plots a line
                	X1 = ( DIM_CANVAS_X * x1 ) / dim_x
                	Y1 = DIM_CANVAS_Y - ( DIM_CANVAS_Y * y1 ) / dim_y
                	X2 = ( DIM_CANVAS_X * x2 ) / dim_x
                	Y2 = DIM_CANVAS_Y - ( DIM_CANVAS_Y * y2 ) / dim_y
                	line = C.create_line(X1,Y1,X2,Y2,fill="blue", arrow="last")
          		#self.plot_line(x1,y1,x2,y2,"blue",0)
			id = C.create_rectangle(X2,Y2,X2+1,Y2+1, fill= "white", outline="white")
                	C.update_idletasks()

          		j=j+1
          		tetha = tetha + delta_angle





def Initialize():
	global BB
	global gui_planner
	global robotgui


    	BB.Initialize(2050, fmap)

    	BB.Start()


    	BB.CreateSharedVar(BB.SharedVarTypes.STRING, 'gui')
    	BB.WriteSharedVar(BB.SharedVarTypes.STRING, 'gui', 'initial_value')

        BB.SubscribeToSharedVar('sensor',SensorHandler, subscriptionType='writeothers', reportType='content')
        BB.SubscribeToSharedVar('gui',GuiHandler, subscriptionType='writeothers', reportType='content')
        BB.SubscribeToSharedVar('actuator',ActuatorHandler, subscriptionType='writeothers', reportType='content')

	
	BB.SetReady()


def init_BB():

	global BB

	Initialize()


#-------------------------------------------------------------------------------------------
#	TK Definitions

planner = tk.Tk()
planner.wm_title('PLANNER')
C = tk.Canvas(planner, bg="green", height=DIM_CANVAS_X, width=DIM_CANVAS_Y)


class PLANNER(object):
   

    def __init__(self):

	global C   
	global DIM_CANVAS_X 
	global DIM_CANVAS_Y
	global dim_x
	global dim_y
	global x
	global y
	global radio_robot
	global pose_x
	global pose_y
	global pose_tetha
	global BB
	global sv

 
	def callback_mouse_1(event):
		global mouse_1_x
		global mouse_1_y
		global angle_robot
		global pose_x
		global pose_y


		#print "clicked 1 at", event.x, event.y
		id = C.create_rectangle(event.x, event.y, event.x+1, event.y+1, fill= "black")
		x = (dim_x * event.x) / DIM_CANVAS_X
		y = (dim_y * (DIM_CANVAS_Y-event.y)) / DIM_CANVAS_Y
		print "left button x ", x, " y ", y
		mouse_1_x = x
		mouse_1_y = y
        	angle_robot = float(self.robot_angle.get())

		pose_x = mouse_1_x
		pose_y = mouse_1_y
		print "Mouse 1 pose x " + str(pose_x) + " y " + str(pose_y)



		# it shares the mouse 1 values
		s = "mouse 1 x " + str(x)  + " y "  + str(y)  + " angle "  + str(angle_robot)
		BB.WriteSharedVar(BB.SharedVarTypes.STRING, 'gui', s)
		BB.WriteSharedVar(BB.SharedVarTypes.STRING, 'sensor', s)
		print "send shared ",s

 
	def callback_mouse_2(event):
		global mouse_2_x
		global mouse_2_y

		#print "clicked 2 at", event.x, event.y
		id = C.create_rectangle(event.x, event.y, event.x+1, event.y+1, fill= "green", outline='yellow')
		x = (dim_x * event.x) / DIM_CANVAS_X
		y = (dim_y * (DIM_CANVAS_Y-event.y)) / DIM_CANVAS_Y
		print "middle button x ", x, " y ", y
		mouse_2_x = x
		mouse_2_y = y

		# it shares the mouse 2 values
		s = "mouse 2 x " + str(x)  + " y "  + str(y)
		BB.WriteSharedVar(BB.SharedVarTypes.STRING, 'gui', s)
		print "send shared ",s


    
	def callback_mouse_3(event):
		global mouse_1_x
		global mouse_1_y
		global mouse_3_x
		global mouse_3_y
		global pose_x
		global pose_y
		global pose_tetha


		#print "clicked 3 at", event.x, event.y
		id = C.create_rectangle(event.x, event.y, event.x+1, event.y+1, fill= "red", outline='red')
		x = (dim_x * event.x) / DIM_CANVAS_X
		y = (dim_y * (DIM_CANVAS_Y-event.y)) / DIM_CANVAS_Y
		print "right button x ", x, " y ", y
		mouse_3_x = x
		mouse_3_y = y



		# it shares the mouse 3 values
		s = "mouse 3 x " + str(x)  + " y "  + str(y)
		BB.WriteSharedVar(BB.SharedVarTypes.STRING, 'gui', s)
		print "send shared ",s

		if flg_execute == 1:
			print "Mouse pose x " + str(pose_x) + " y " + str(pose_y)
			mouse_1_x = pose_x
        		mouse_1_y = pose_y

			angle_robot = pose_tetha
                        str_angle = ("%3.4f" % angle_robot).strip()
                        self.robot_angle.delete(0, END)
                        self.robot_angle.insert(0,str_angle)
                        self.robot_posex.delete(0, END)
                        self.robot_posex.insert (0, pose_x )
                        self.robot_posey.delete(0, END)
                        self.robot_posey.insert (0, pose_y )

			if self.var_mov.get() == 0:
                                C.update_idletasks()

			self.togglePlotExecute()
			


	def initial(self):
       		global PATH
		global File_Name
		global File_Name_robot
       		global flg_mov
       		global flg_sensor
		global delay
		
 
		self.topLevelWindow = tk.Tk()
        	self.topLevelWindow.wm_title('GUI_ROBOTS')
        	#self.topLevelWindow.bind_all('<KeyPress-Return>', self.run)


		# Plot Robot button
        	self.RobotButton = tk.Button(self.topLevelWindow, width = 20, text = 'Plot Robot', bg = 'green', activebackground = 'green', command = self.togglePlotRobot)
		self.countRobot = 0
		# Plot Sensor button
        	self.ExecuteButton = tk.Button(self.topLevelWindow, width = 20, text = 'Execute Robot Command ', bg = 'green', activebackground = 'green', command = self.togglePlotExecute)
		self.countExecute = 0
		# Plot Map button
        	self.MapButton = tk.Button(self.topLevelWindow, width = 20, text = 'Plot Map', bg = 'green', activebackground = 'green', command = self.togglePlotMap)
		self.countMap = 0
		# Plot Path button
        	self.PathButton = tk.Button(self.topLevelWindow, width = 20, text = 'Plot Path', bg = 'green', activebackground = 'green', command = self.togglePlotPath)
		self.countPath = 0
		# Plot Test button
        	self.TestButton = tk.Button(self.topLevelWindow, width = 20, text = 'Plot test', bg = 'green', activebackground = 'green', command = self.togglePlotTest)
      		# Path files entry 
		self.label_path = tk.Label(self.topLevelWindow,text =  'Path'' Files')
        	self.path = tk.Entry(self.topLevelWindow, width = 30, foreground='green',background='blue')
		self.path.insert ( 0, '/home/savage2/robotics/data/' )
		PATH = self.path.get()
      		# World's File entry 
		self.label_file = tk.Label(self.topLevelWindow,text =  'World File (.wrl) ')
        	self.file = tk.Entry(self.topLevelWindow, width = 30, foreground='green',background='blue')
		self.file.insert ( 0, 'empty' )
		File_Name = self.file.get()
      		# Robot's File entry 
		self.label_file_robot = tk.Label(self.topLevelWindow,text =  'Robot File (.raw) ')
        	self.file_robot = tk.Entry(self.topLevelWindow, width = 30, foreground='green',background='blue')
		self.file_robot.insert ( 0, 'empty' )
		File_Name_robot = self.file_robot.get()
		# Check button movement
		self.var_mov = IntVar()
		def command_mov():
			#print "Checkbutton variable is", self.var_mov.get()
			if self.var_mov.get() == 0:
				self.Movement.select()
                		self.var_mov.set(1)
			else:
				self.Movement.deselect()
                		self.var_mov.set(0)
		self.Movement = tk.Checkbutton(self.topLevelWindow, text="Show robot Movement", variable= self.var_mov,command=command_mov)
		self.Movement.select()
		self.var_mov.set(1)
		#print 'flg_mov ',  self.var_mov.get()
      		# Delay's plot robot entry 
		self.label_delay = tk.Label(self.topLevelWindow,text =  'Delay plotting')
        	self.delay = tk.Entry(self.topLevelWindow, width = 8, foreground='green',background='blue')
		self.delay.insert ( 0, '0.04' )
		delay = float(self.delay.get())
		# Check button sensor
                self.var_sensor = IntVar()
                def command_sensor():
                        if self.var_sensor.get() == 0:
                                self.sensor.select()
                                self.var_sensor.set(1)
                        else:
                                self.sensor.deselect()
                                self.var_sensor.set(0)
                self.sensor = tk.Checkbutton(self.topLevelWindow, text="show sensors", variable= self.var_sensor,command=command_sensor)
                self.sensor.select()
                self.var_sensor.set(1)

                # Check button add_noise
                self.add_noise = IntVar()
                def command_add_noise():
                        if self.add_noise.get() == 0:
                                self.noise.select()
                                self.add_noise.set(1)
                        else:
                                self.noise.deselect()
                                self.add_noise.set(0)
                self.noise = tk.Checkbutton(self.topLevelWindow, text="add noise", variable= self.add_noise,command=command_add_noise)
                self.noise.deselect()
                self.add_noise.set(0)



      		# Number of sensors 
		self.label_num_sensors = tk.Label(self.topLevelWindow,text =  'Num. Sensors')
        	self.num_sensors = tk.Entry(self.topLevelWindow, width = 8, foreground='green',background='blue')
		self.num_sensors.insert ( 0, '2' )
		num_sensors = self.num_sensors.get()
      		# Origen angle sensor 
		self.label_origen_angle = tk.Label(self.topLevelWindow,text =  'Origen angle sensor ')
        	self.origen_angle = tk.Entry(self.topLevelWindow, width = 8, foreground='green',background='blue')
		self.origen_angle.insert ( 0, '-0.2000' )
		origen_angle = self.origen_angle.get()
      		# Range angle sensor 
		self.label_range_angle = tk.Label(self.topLevelWindow,text =  'Range angle sensor ')
        	self.range_angle = tk.Entry(self.topLevelWindow, width = 8, foreground='green',background='blue')
		self.range_angle.insert ( 0, '0.4000' )
		range_angle = self.range_angle.get()
      		# Robot's magnitude advance  
		self.label_advance_robot = tk.Label(self.topLevelWindow,text =  "Robot's magnitude advance")
        	self.advance_robot = tk.Entry(self.topLevelWindow, width = 8, foreground='green',background='blue')
		self.advance_robot.insert(0,'0.040')
		advance_robot = self.advance_robot.get()
		 # Robot's maximum angle  
                self.label_max_angle_robot = tk.Label(self.topLevelWindow,text =  "Robot's maximum turn angle")
                self.max_angle_robot = tk.Entry(self.topLevelWindow, width = 8, foreground='green',background='blue')
                self.max_angle_robot.insert(0,'0.5854')
                max_angle_robot = self.max_angle_robot.get()
      		# Robot's radio  
		self.label_radio_robot = tk.Label(self.topLevelWindow,text =  "Robot's radio")
        	self.radio_robot = tk.Entry(self.topLevelWindow, width = 8, foreground='green',background='blue')
		self.radio_robot.insert ( 0, '0.03' )
		radio_robot = self.radio_robot.get()
      		# Robot's pose x  
		self.label_robot_posex = tk.Label(self.topLevelWindow,text =  "Robot's pose x")
        	self.robot_posex = tk.Entry(self.topLevelWindow, width = 8, foreground='green',background='blue')
		self.robot_posex.insert ( 0, '0.4000' )
		pose_x = self.robot_posex.get()
      		# Robot's pose y  
		self.label_robot_posey = tk.Label(self.topLevelWindow,text =  "Robot's pose y")
        	self.robot_posey = tk.Entry(self.topLevelWindow, width = 8, foreground='green',background='blue')
		self.robot_posey.insert ( 0, '0.5000' )
		pose_y = self.robot_posey.get()
      		# Robot's angle  
		self.label_robot_angle = tk.Label(self.topLevelWindow,text =  "Robot's angle")
        	self.robot_angle = tk.Entry(self.topLevelWindow, width = 8, foreground='green',background='blue')
		self.robot_angle.insert ( 0, '0.000' )
		pose_tetha = self.robot_angle.get()
      		# Robot's command  
		self.label_robot_command = tk.Label(self.topLevelWindow,text =  "Robot's command")
        	self.robot_command = tk.Entry(self.topLevelWindow, width = 30, foreground='green',background='blue')
		self.robot_command.insert ( 0,"GoTo_State_Machine")
		robot_command = self.robot_command.get()
      		# Number of steps  
		self.label_number_steps = tk.Label(self.topLevelWindow,text =  "Number of Steps")
        	self.number_steps = tk.Entry(self.topLevelWindow, width = 8, foreground='green',background='blue')
		self.number_steps.insert ( 0, '100' )
		number_steps = self.number_steps.get()
      		# Selection of behavior  
		self.label_selection = tk.Label(self.topLevelWindow,text =  "Behaviour Selection")
        	self.selection = tk.Entry(self.topLevelWindow, width = 8, foreground='green',background='blue')
		self.selection.insert ( 0, '3' )
		selection = self.selection.get()
      		# Largest value sensor  
		self.label_largest = tk.Label(self.topLevelWindow,text =  "Largest value sensor")
        	self.largest = tk.Entry(self.topLevelWindow, width = 8, foreground='green',background='blue')
		self.largest.insert ( 0, '0.3' )
		largest = self.largest.get()
		 # Add noise
                flg_noise = self.add_noise.get()

	

#--------------------------- G R I D S ------------------------------------------------------------- 


		self.label_robot_command.grid({'row':0, 'column': 0})        
		self.robot_command.grid({'row':0, 'column': 1})        
        	self.ExecuteButton.grid({'row':4, 'column': 0})
		self.label_path.grid({'row':1, 'column': 0})        
		self.path.grid({'row':1, 'column': 1})        
		self.label_file.grid({'row':2, 'column': 0})        
		self.file.grid({'row':2, 'column': 1})        
		self.label_file_robot.grid({'row':3, 'column': 0})        
		self.file_robot.grid({'row':3, 'column': 1})        
		self.label_delay.grid({'row':0, 'column': 3})        
		self.delay.grid({'row':0, 'column': 4})        
        	self.MapButton.grid({'row':5, 'column': 0})
        	self.RobotButton.grid({'row':6, 'column': 0})
		self.Movement.grid({'row':0, 'column': 2})
		self.sensor.grid({'row':1, 'column': 2})
		self.noise.grid({'row':2, 'column': 2})
		self.label_num_sensors.grid({'row':1, 'column': 3})        
		self.num_sensors.grid({'row':1, 'column': 4})        
		self.label_origen_angle.grid({'row':2, 'column': 3})        
		self.origen_angle.grid({'row':2, 'column': 4})        
		self.label_range_angle.grid({'row':3, 'column': 3})        
		self.range_angle.grid({'row':3, 'column': 4})        
		self.label_radio_robot.grid({'row':4, 'column': 3})        
		self.radio_robot.grid({'row':4, 'column': 4})        
		self.label_advance_robot.grid({'row':5, 'column': 3})        
		self.advance_robot.grid({'row':5, 'column': 4})        
		self.label_max_angle_robot.grid({'row':6, 'column': 3})        
		self.max_angle_robot.grid({'row':6, 'column': 4})        
		self.label_robot_posex.grid({'row':4, 'column': 1})        
		self.robot_posex.grid({'row':4, 'column': 2})        
		self.label_robot_posey.grid({'row':5, 'column': 1})        
		self.robot_posey.grid({'row':5, 'column': 2})        
		self.label_robot_angle.grid({'row':6, 'column': 1})        
		self.robot_angle.grid({'row':6, 'column': 2})        
		self.label_number_steps.grid({'row':7, 'column': 3})        
		self.number_steps.grid({'row':7, 'column': 4})        
		self.label_selection.grid({'row':7, 'column': 1})        
		self.selection.grid({'row':7, 'column': 2})        
		self.label_largest.grid({'row':8, 'column': 1})        
		self.largest.grid({'row':8, 'column': 2})        
    
   
#___________________________________________________________________________________________________ 




    	#C.delete(polygon)
    	C.bind("<Button-1>", callback_mouse_1)
    	C.bind("<Button-2>", callback_mouse_2)
    	C.bind("<Button-3>", callback_mouse_3)
    	C.pack()
    	initial(self)
    	self.read_file_map(1)
	global flg_robot

	#while True:
	if flg_robot == 1:
			
                	angle_robot = 3.1416

			str_angle = ("%3.4f" % angle_robot).strip()
                	self.robot_angle.delete(0, END)
                	self.robot_angle.insert(0,str_angle)
			flg_robot = 0



    def plot_test(self):
	global C


	id = C.create_rectangle(0, 0, DIM_CANVAS_X, DIM_CANVAS_Y, fill= "blue")
    	coord = 10, 50, 40, 80
    	arc = C.create_arc(coord, start=0, extent=150, fill="red")
    	points = [150, 100, 200, 120, 240, 180, 210, 200, 150, 150, 100, 200]
    	polygon = C.create_polygon(points, outline='black', fill='red', width=1)
    	points = [1.50, 1.00, 2.00, 1.20, 2.40, 1.80, 2.10, 2.00, 1.50, 1.50, 1.00, 2.00]
    	self.plot_polygon(6, points)
    	oval = C.create_oval(300, 300, 380, 380, outline="black", fill="red", width=2)
    	line = C.create_line(30, 300, 100, 280,  fill="red", arrow="last")
    	self.plot_robot()


    def plot_polygon(self,num, data):
	global C

	XY= data
	#print "plot_polygon ",num
	for i in range(0, num):
		j=i*2 
		
		#print "data j ",j," x",data[j]," y ",data[j+1]
		X = ( DIM_CANVAS_X * data[j] ) / dim_x
		Y = DIM_CANVAS_Y - ( DIM_CANVAS_Y * data[j+1] ) / dim_y
		XY[j]=X;
		XY[j+1]=Y;
		#print "j ",j," X",XY[j]," Y ",XY[j+1]

	polygon = C.create_polygon(XY, outline='black', fill='red', width=1)
	return polygon

    def plot_line(self,x1,y1,x2,y2,color,flg):
        global C

        #print "plot_line "

        #print "x1 ",x1," y1 ",y1
        X1 = ( DIM_CANVAS_X * x1 ) / dim_x
        Y1 = DIM_CANVAS_Y - ( DIM_CANVAS_Y * y1 ) / dim_y
        #print "X1 ",X1," Y1 ",Y1

        #print "x2 ",x2," y2 ",y2
        X2 = ( DIM_CANVAS_X * x2 ) / dim_x
        Y2 = DIM_CANVAS_Y - ( DIM_CANVAS_Y * y2 ) / dim_y
        #print "X2 ",X2," Y2 ",Y2

	if flg == 1:
		line = C.create_line(X1,Y1,X2,Y2,fill=color, arrow="last")
	else:
		line = C.create_line(X1,Y1,X2,Y2,fill=color)
		id = C.create_rectangle(X2,Y2,X2+1,Y2+1, fill= "white", outline="white")


    def plot_robot(self):
        global C
	global radio_robot
	global pose_tetha
	global dim_x
	global dim_y

        global DIM_CANVAS_X
        global DIM_CANVAS_Y
        global radio_robot
        global pose_x
        global pose_y
        global pose_tetha





	CNT=5.0
	#print "plot robot pose_tetha ",pose_tetha
	X = ( DIM_CANVAS_X * pose_x ) / dim_x
	Y = DIM_CANVAS_Y - ( DIM_CANVAS_Y * pose_y ) / dim_y
	ROBOT_radio = ( DIM_CANVAS_X * radio_robot ) / dim_x
	X1 = X - ROBOT_radio/2
	Y1 = Y - ROBOT_radio/2
	X2 = X + ROBOT_radio/2
	Y2 = Y + ROBOT_radio/2
	#print "X1 ", X1, " Y1 ", Y1
	#print "X2 ", X2, " Y2 ", Y2
	oval = C.create_oval(X1,Y1,X2,Y2, outline="black",fill="red", width=1)
	#X1 = X 
	#Y1 = Y
	#Y2 = Y - CNT*ROBOT_radio*math.sin(pose_tetha)
	#print "sen ", pose_tetha, " = ",math.sin(pose_tetha)
	#line = C.create_line(X1,Y1,X2,Y2,fill="black", arrow="last")


	x1 = pose_x
        y1 = pose_y
	angle_robot = pose_tetha
        tetha = angle_robot + start_angle
        x2 = x1 + (dim_x/25)*math.cos(angle_robot)
        y2 = y1 + (dim_y/25)*math.sin(angle_robot)
        self.plot_line(x1,y1,x2,y2,"black",1)

	#str_angle = ("%3.4f" % angle_robot).strip()
        #gui_planner.robot_angle.delete(0, END)
        #gui_planner.robot_angle.insert(0,str_angle)




    def read_file_map(self,flg):
        global pose_x
        global pose_y
        global pose_tetha
        global C
        global num_pol
        global polygons
	global PATH
	global dim_x 
	global dim_y


        id = C.create_rectangle(0, 0, DIM_CANVAS_X, DIM_CANVAS_Y, fill= "green")

	PATH = self.path.get()
	File_Name = self.file.get()

	#print 'Path ',PATH 
	#print 'File ',File_Name

	FILE = PATH + File_Name + '.wrl'

        file = open(FILE, 'r')

        for line in file:
                #print line,
                words = line.split()
                data = words
                #print len(words)
                #for i in range(0, len(words)):
                        #print words[i]
		if len(words) > 1:
			if words[0] == ";(":
				j=0
			elif words[1] == "dimensions":
				dim_x = float(words[3])
				dim_y = float(words[4])
				#print 'dim_x ',dim_x, 'dim_y ',dim_y


                	elif words[1] == "polygon":
                        	j=0
                        	data = [0] * (len(words) - 5)
                        	for i in range(4, len(words) -1):
                                	#print words[i]
                                	data[j] = float(words[i])
                                	j=j+1

                        	j=j+1
                        	num = j / 2
				if flg == 1:
                        		polygons.append(self.plot_polygon(num,data))
                        		num_pol = num_pol + 1
				else:
					self.plot_polygon(num,data)

    def process_command(self):

	global pose_x
        global pose_y
        global pose_tetha
        global C
        global num_pol
        global polygons
        global flg_mov
        global flg_sensor
        global delay
        global dim_x
        global dim_y
        global angle_robot

	line = process_line
	print 'process_command ', line,

	words = line.split()

	if len(words) > 1:
		#if words[1] == "robot":
                        pose_x = float(words[1])
                        pose_y = float(words[2])
                        pose_tetha = float(words[3])
                        angle_robot = pose_tetha
                        str_angle = ("%3.4f" % angle_robot).strip()
                        self.robot_angle.delete(0, END)
                        self.robot_angle.insert(0,str_angle)
                        self.robot_posex.delete(0, END)
                        self.robot_posex.insert (0, words[3] )
                        self.robot_posey.delete(0, END)
                        self.robot_posey.insert (0, words[4] )
                        str_num_steps = ("%4d" % num_steps).strip()
                        self.number_steps.delete(0, END)
                        self.number_steps.insert(0,str_num_steps)
                        num_steps = num_steps + 1

                        if flg_mov == 1:
                                id = C.create_rectangle(0, 0, DIM_CANVAS_X, DIM_CANVAS_Y, fill= "green")
                                self.read_file_map(0)

                        self.plot_robot()
                        if self.var_mov.get() == 0:
                                C.update_idletasks()
                        else:
                                if flg_sensor == 0:
                                        C.update_idletasks()

                        if flg_mov == 1:
                                time.sleep(delay/2.0) # delays seconds


    def read_file(self,flg):
	global pose_x
	global pose_y
	global pose_tetha
	global C
	global num_pol
	global polygons
	global flg_mov
	global flg_sensor
	global delay
	global dim_x
	global dim_y
	global angle_robot
	global radio_robot
	global delta_angle
	global start_angle


	PATH = self.path.get()
        File_Name_robot = self.file_robot.get()
        FILE = PATH + File_Name_robot + '.raw'
        file = open(FILE, 'r')
	
	C.update_idletasks() # it updates the ide data
	delay = float(self.delay.get())
	flg_mov = self.var_mov.get()
	flg_sensor = self.var_sensor.get()
	number_steps = self.number_steps.get()
        num_steps = 1

	for line in file:
    		#print line,
		words = line.split()
		data = words
		#print len(words)
		#for i in range(0, len(words)):
			#print words[i]
		if len(words) > 1:
		  if words[0] == ";(":
                                j=0

		  elif words[1] == "polygon":
			j=0
			data = [0] * (len(words) - 5)
                        for i in range(4, len(words) -1):
				#print words[i]
				data[j] = float(words[i])
				j=j+1 
				
			j=j+1 
			num = j / 2
			if flg == 1:
                        	polygons.append(self.plot_polygon(num,data))
                        	num_pol = num_pol + 1
                        else:
                        	self.plot_polygon(num,data)


		  elif words[1] == "dimensions":
                                dim_x = float(words[3])
                                dim_y = float(words[4])
                                #print 'dim_x ',dim_x, 'dim_y ',dim_y

		  elif words[1] == "radio_robot":
                                radio_robot = float(words[2])
                                #print 'radio robot ',radio_robot

    			
		  elif words[1] == "delete":
			for i in range(0,num_pol):
				C.delete(polygons[i])

		  elif words[1] == "robot":
			pose_x = float(words[3])
			pose_y = float(words[4])
			pose_tetha = float(words[5])
			angle_robot = pose_tetha
			str_angle = ("%3.4f" % angle_robot).strip()
			self.robot_angle.delete(0, END)
        		self.robot_angle.insert(0,str_angle)
			self.robot_posex.delete(0, END)
			self.robot_posex.insert (0, words[3] )
			self.robot_posey.delete(0, END)
			self.robot_posey.insert (0, words[4] )
			str_num_steps = ("%4d" % num_steps).strip()
			self.number_steps.delete(0, END)
        		self.number_steps.insert(0,str_num_steps)
			num_steps = num_steps + 1

			if flg_mov == 1:
				id = C.create_rectangle(0, 0, DIM_CANVAS_X, DIM_CANVAS_Y, fill= "green")
				self.read_file_map(0)

			self.plot_robot()
			if self.var_mov.get() == 0:
				C.update_idletasks()
			else:
				if flg_sensor == 0:
					C.update_idletasks()



			if flg_mov == 1:
				time.sleep(delay/2.0) # delays seconds

		  elif words[1] == "sensor":
		     if flg_sensor == 1:
			if flg_mov == 1:
				id = C.create_rectangle(0, 0, DIM_CANVAS_X, DIM_CANVAS_Y, fill= "green")
				self.read_file_map(0)

			self.plot_robot()

			num = int(words[3])

			range_angle = float(words[4])
			start_angle = float(words[5])
			if num == 1:
				delta_angle = range_angle 
			else:
				delta_angle = range_angle / (num - 1)
			#print "num ", num, "Range Measurments ", range_angle
			#print "Start angle ", start_angle, " Delta Angle ", delta_angle

			x1 = pose_x 
       			y1 = pose_y
			tetha = angle_robot + start_angle
			x2 = x1 + (dim_x/10)*math.cos(angle_robot)
                        y2 = y1 + (dim_y/10)*math.sin(angle_robot)
                        #self.plot_line(x1,y1,x2,y2,"red",1)
			#print "sensor pose tetha ",pose_tetha
			#print "sensor angle_robot ",angle_robot
			#print "Origen Tetha ", tetha
			#print "sen ", tetha, " = ",math.sin(tetha)

			data = [0] * (len(words) - 5)
			j=0
                        for i in range(6, len(words) -1):
                                #print words[i]
				#print "Tetha ", j," ",tetha
                                data[j] = float(words[i])
        			x2 = x1 + data[j]*math.cos(tetha)
        			y2 = y1 + data[j]*math.sin(tetha)
				self.plot_line(x1,y1,x2,y2,"blue",0)
                                j=j+1
				tetha = tetha + delta_angle
				#print "sen ", tetha, " = ",math.sin(tetha)


			C.update_idletasks()
			if flg_mov == 1:
				time.sleep(delay/2.0) # delays seconds

	file.close()
	self.number_steps.delete(0, END)
       	self.number_steps.insert(0,number_steps)



#------------------------------------------------------------------------------------------

# Functions that handle the buttons
    def togglePlotRobot(self):
	global pose_x
	global pose_y
	global pose_tetha
	global PATH
        global File_Name
        global File_Name_robot
	global flg_mov
	global flg_sensor
	global delay

 
 
	self.RobotButton['bg'] = 'red'
       	self.RobotButton['activebackground'] = 'red'


	# uniform gives you a floating-point value
	#pose_x = uniform(0, dim_x)
	#pose_y = uniform(0, dim_y)
	#pose_tetha = uniform(0, 2*3.1416)
	#self.plot_robot()

        C.update_idletasks()

	PATH = self.path.get()
        #print 'Plot Robot PATH ',PATH

        File_Name = self.file.get()
        #print 'Plot Robot File_Name ',File_Name

        File_Name_robot = self.file_robot.get()
        #print 'Plot Robot File_Name_robot ',File_Name_robot

	flg_mov = self.var_mov.get()
	#print 'Plot Robot flg_mov ',flg_mov

	flg_sensor = self.var_sensor.get()
	#print 'Plot Robot flg_sensor ',flg_sensor

	delay = float(self.delay.get())
	#print 'Plot Robot delay ',delay

	self.read_file_map(0)
	self.read_file(1)

    	self.RobotButton['bg'] = 'green'
       	self.RobotButton['activebackground'] = 'green'



    def togglePlotMap(self):
	global PATH
	global File_Name
	global pose_tetha

 
 
       	self.MapButton['bg'] = 'red'
       	self.MapButton['activebackground'] = 'red'
	
	C.update_idletasks()

	PATH = self.path.get()
        #print 'Plot Map PATH ',PATH

        File_Name = self.file.get()
        #print 'Plot Map File_Name ',File_Name

	flg_mov = self.var_mov.get()
        #print 'Plot Robot flg_mov',flg_mov

	flg_sensor = self.var_sensor.get()
	#print 'Plot Robot flg_sensor ',flg_sensor

	self.read_file_map(0)

      	self.MapButton['bg'] = 'green'
       	self.MapButton['activebackground'] = 'green'

	pose_tetha = 0
        str_angle = "0.00000"
        self.robot_angle.delete(0, END)
        self.robot_angle.insert(0,str_angle)


    def togglePlotExecute(self):
       
	global mouse_1_x
        global mouse_1_y
	global mouse_3_x
        global mouse_3_y
	global angle_robot
	global sensor
	global num_sensors 
	global flg_noise
	global start_angle 
	global range_angle
	global flg_execute
	global pose_x
	global pose_y
	global pose_tetha
	global radio_robot
	global advance_robot
	global max_angle_robot
	global robot_command


	flg_execute = 1 

       	self.ExecuteButton['bg'] = 'red'
       	self.ExecuteButton['activebackground'] = 'red'

	C.update_idletasks()

	angle_robot = pose_tetha
	flg_noise = self.add_noise.get()
	num_sensors = self.num_sensors.get()
        origen_angle = self.origen_angle.get()
        range_angle = self.range_angle.get()
        angle_robot = float(self.robot_angle.get())
        radio_robot = float(self.radio_robot.get())
        advance_robot = float(self.advance_robot.get())
        max_angle_robot = float(self.max_angle_robot.get())
	flg_sensor = self.var_sensor.get()
        number_steps = self.number_steps.get()
	selection = self.selection.get()
	largest = self.largest.get()
	PATH = self.path.get()
        #print 'Plot Robot PATH ',PATH
        File_Name = self.file.get()
        #print 'Plot Robot File_Name ',File_Name
        File_Name_robot = self.file_robot.get()
        #print 'Plot Robot File_Name_robot ',File_Name_robot

	robot_command = self.robot_command.get()
	origin = " -x " + str(mouse_1_x) + " -y " + str(mouse_1_y) + " -a " + str(angle_robot)
	destination = " -v " + str(mouse_3_x) + " -z " + str(mouse_3_y)
	rest = " -s " + sensor + " -n " + num_sensors + " -t " + origen_angle + " -r " + range_angle + " -radio " + str(radio_robot) + " -advance " + str(advance_robot) + " -MaxAngle " + str(max_angle_robot) + " -steps " + number_steps + " -selection " + selection + " -largest " + largest + " -p " + PATH + " -e " + File_Name  + " -noise " + str(flg_noise)
	command = robot_command + origin + destination + rest + " > test.dat "
	print "Command: ", command
	
	#status = os.system(command)

	BB.WriteSharedVar(BB.SharedVarTypes.STRING, 'gui', command)



	C.update_idletasks()

        flg_mov = self.var_mov.get()
        #print 'Plot Robot flg_mov ',flg_mov

        flg_sensor = self.var_sensor.get()
        #print 'Plot Robot flg_sensor ',flg_sensor

        delay = float(self.delay.get())
        #print 'Plot Robot delay ',delay

        self.read_file_map(0)
        self.read_file(1)


      	self.ExecuteButton['bg'] = 'green'
       	self.ExecuteButton['activebackground'] = 'green'

	mouse_1_x = pose_x
	mouse_1_y = pose_y


    def togglePlotPath(self):
       	global num_pol
	global polygons
 
       	if self.countPath == 1:
       		self.PathButton['bg'] = 'green'
       		self.PathButton['activebackground'] = 'green'
       	else:
       		self.PathButton['bg'] = 'red'
       		self.PathButton['activebackground'] = 'red'
		self.countPath = 0

	#print 'PlotPath num_pol ' + str(num_pol)

	for i in range(0,num_pol):
		C.delete(polygons[i])




    def togglePlotTest(self):
	self.plot_test()
        



#-----------------------------------------------------
#  MAIN


if __name__ == '__main__':
    init_BB()
    gui_planner = PLANNER()
    tk.mainloop()

