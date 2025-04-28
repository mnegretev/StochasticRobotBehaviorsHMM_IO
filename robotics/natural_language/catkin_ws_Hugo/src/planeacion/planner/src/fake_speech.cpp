#include "ros/ros.h"

#include "planner_msgs/PlanningCmdClips.h"
#include "planner_msgs/planning_cmd.h"
#include "planner_msgs/RecognizedSpeech.h"

#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/thread/thread.hpp"
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include "geometry_msgs/Pose2D.h"
#include "geometry_msgs/Twist.h"

#include <iostream>
#include <vector>
#include <ctime>
#include <map>
#include <sstream> 
#include <string>

using namespace boost::algorithm;


enum SMState {
	SM_INIT,
    SM_SEND_SPEECH,
    SM_CLEAR_MSG
};

ros::Publisher speech_recog_response;

SMState state=SM_INIT;

planner_msgs::RecognizedSpeech fake_recog;

int main(int argc, char **argv){

    ros::init(argc, argv, "fake_speesch_node");
    ros::NodeHandle n;
    ros::Rate rate(10);
	
    speech_recog_response = n.advertise<planner_msgs::RecognizedSpeech>("/recognizedSpeech", 1);
    std::string recog_string;

    while (ros::ok()) {
        switch (state){
            case SM_INIT:
                std::cout << "Ingresa un comando :" << std::endl;
                std::getline(std::cin,recog_string);
                state=SM_SEND_SPEECH;
                //std::cout << "String leida: " <<  recog_string << std::endl;
            break;
            case SM_SEND_SPEECH:
                //std_msgs::String str;
                //str.data = recog_string;
                fake_recog.hypothesis.push_back(recog_string);
                fake_recog.confidences.push_back(0.9);
                speech_recog_response.publish(fake_recog);
                state = SM_CLEAR_MSG;
            break;
            case SM_CLEAR_MSG:
                fake_recog.hypothesis.clear();
                fake_recog.confidences.clear();
                state = SM_INIT;
            break;

        }
    }
		rate.sleep();
		ros::spinOnce();
}

