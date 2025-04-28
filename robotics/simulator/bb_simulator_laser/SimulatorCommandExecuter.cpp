#include "SimulatorCommandExecuter.h"

#include <cstdlib>
#include <string>
#include <sstream>
#include <uRobotics/api/Parser.h>
#include <uRobotics/utilities/Scanner.h>
#include "../utilities/structures.h"


#define MAX_NUM_CHARACTERS 1500
extern coord coord_robot;
extern Inputs inputs;
extern int flg_SENSOR;
extern char *get_laser_values();



using namespace Robotics::Utilities;

// In the constructor may be defined the name of the command this command executer manages
robotsensorCommandExecuter::robotsensorCommandExecuter(void) :
SyncCommandExecuter("robotsensor"){}

robotsensorCommandExecuter::~robotsensorCommandExecuter(void){}

// parameters are required so this method returns true.
bool robotsensorCommandExecuter::parametersRequired() const{
	return true;
}

// This method performs the sum
Response* robotsensorCommandExecuter::SyncTask(const Command& command){
	double x, y, tetha;
	size_t cc = 0;
	//std::stringstream ss;
	std::string ss;

        char line[300];
        char answer_command[300];
        char **strings;
        int num_words;
        char cr[3];
        char ** process_string(char *,int , int *);
        bool success;
        Response *rspPtr;
        std::string parameters;

	cr[0]='\n';

	std::cout << "robotsensor " << command.parameters << std::endl;

        strcpy(line,command.parameters.c_str());
        strcat(line,cr);

        strings=process_string(line,MAX_NUM_CHARACTERS,&num_words);

        //printf("string sensor %s\n",strings[1]);
        coord_robot.xc=atof(strings[1]);
        coord_robot.yc=atof(strings[2]);
        coord_robot.anglec=atof(strings[3]);
        printf("answer robot position x %f y  %f angle %f\n",coord_robot.xc,coord_robot.yc,coord_robot.anglec);
        sprintf(answer_command,"answer robot position x %f y  %f angle %f\n",coord_robot.xc,coord_robot.yc,coord_robot.anglec);
        flg_SENSOR=1;
        printf("flg_sensor %d\n",flg_SENSOR);


	ss = answer_command;
	// Generate the response for the command
	Response* r = Response::createFromCommand(command, true);
	// Update parameters with result
	//r->parameters = ss.str();
	r->parameters = ss;
	return r;
}


// In the constructor may be defined the name of the command this command executer manages
readlaserCommandExecuter::readlaserCommandExecuter(void) :
SyncCommandExecuter("readlaser"){}

readlaserCommandExecuter::~readlaserCommandExecuter(void){}

// parameters are required so this method returns true.
bool readlaserCommandExecuter::parametersRequired() const{
	return true;
}

// This method performs the sum
Response* readlaserCommandExecuter::SyncTask(const Command& command){
	double x, y, tetha;
	size_t cc = 0;
	//std::stringstream ss;
	std::string ss;

        char line[300];
	char *answer;
        char answer_command[300];
        char **strings;
        int num_words;
        char cr[3];
        char ** process_string(char *,int , int *);
        bool success;
        Response *rspPtr;
        std::string parameters;

	cr[0]='\n';

	//std::cout << "readlaser " << command.parameters << std::endl;

        strcpy(line,command.parameters.c_str());
        strcat(line,cr);

        strings=process_string(line,MAX_NUM_CHARACTERS,&num_words);

        //printf("string sensor %s\n",strings[1]);
        coord_robot.xc=atof(strings[1]);
        coord_robot.yc=atof(strings[2]);
        coord_robot.anglec=atof(strings[3]);
        //printf("get laser robot position x %f y  %f angle %f\n",coord_robot.xc,coord_robot.yc,coord_robot.anglec);

	answer=get_laser_values();
        //printf("get laser values %s\n",answer);
	ss = answer;

	// Generate the response for the command
	Response* r = Response::createFromCommand(command, true);
	// Update parameters with result
	r->parameters = ss;

	return r;
}


