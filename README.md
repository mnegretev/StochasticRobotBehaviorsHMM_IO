# Software for the manuscript Stochastic Robot Behaviors through Hidden Markov Models with Inputs and Outputs

This repository contains codes and libraries to reproduce the results presented in the manuscript entitled Stochastic Robot Behaviors through Hidden Markov Models with Inputs and Outputs, submited for review to the Jornal of Intelligent and Robotic Systems.

### Requirements

* Ubuntu 16 or 18
* Python 2.7

### Installation

* $ git clone https://github.com/mnegretev/StochasticRobotBehaviorsHMM_IO
* $ cd StochasticRobotBehaviorsHMM_IO/robotics
* $ ./behaviors_make

### Testing

* $ cd ~/StochasticRobotBehaviorsHMM_IO/robotics/gui

By default, the main program shows the available options:

* $ python GUI_behaviors.py

Examples:

* Testing polygons obstacles: `python GUI behaviors.py 0 1`
* Testing office environments: `python GUI behaviors.py 0 0`

A more extensive explanation of available commands and options can be found [here](README_GUI.pdf)



