#include "ros/ros.h"
//#include "visualization_msgs/Marker.h"

#include "planner_msgs/PlanningCmdClips.h"
#include "planner_msgs/planning_cmd.h"

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

#include "pcl_conversions/pcl_conversions.h"

using namespace boost::algorithm;

enum SMState {
	SM_INIT,
	SM_SAY_WAIT_FOR_DOOR,
	SM_WAIT_FOR_DOOR,
	SM_NAVIGATE_TO_THE_LOCATION,
	SM_SEND_INIT_CLIPS,
	SM_SCRIPT,
	SM_RUN_SM_CLIPS
};

ros::Publisher command_response_pub;
std::string testPrompt;
SMState state = SM_INIT;
bool runSMCLIPS = false;
bool startSignalSM = false;
planner_msgs::PlanningCmdClips initMsg;
planner_msgs::PlanningCmdClips initSpeech;

// This is for the attemps for a actions
std::string lastCmdName = "";
int numberAttemps = 0;

ros::ServiceClient srvCltGetTasks;
ros::ServiceClient srvCltInterpreter;
ros::ServiceClient srvCltWaitConfirmation;
ros::ServiceClient srvCltWaitForCommand;
ros::ServiceClient srvCltAnswer;

void validateAttempsResponse(planner_msgs::PlanningCmdClips msg) {
	lastCmdName = msg.name;
	if (msg.successful == 0
			&& (msg.name.compare("move_actuator") == 0
					|| msg.name.compare("find_object") == 0
					|| msg.name.compare("status_object") == 0)) {
		if (msg.name.compare(lastCmdName) != 0)
			numberAttemps = 0;
		else if (numberAttemps == 3) {
			msg.successful = 1;
			numberAttemps = 0;
		} else
			numberAttemps++;
	}
	command_response_pub.publish(msg);
}

void callbackCmdSpeech(const planner_msgs::PlanningCmdClips::ConstPtr& msg) {
	std::cout << testPrompt << "--------- Command Speech ---------"
			<< std::endl;
	std::cout << "name:" << msg->name << std::endl;
	std::cout << "params:" << msg->params << std::endl;

	planner_msgs::PlanningCmdClips responseMsg;
	responseMsg.name = msg->name;
	responseMsg.params = msg->params;
	responseMsg.id = msg->id;
	bool success = true;
	startSignalSM = true;

	if (!runSMCLIPS)
		success = false;

	success = success
			& ros::service::waitForService("/planning_rm/wait_command",
					50000);
	if (success) {
		planner_msgs::planning_cmd srv;
		srv.request.name = "test_wait";
		srv.request.params = "Ready";
		if (srvCltWaitForCommand.call(srv)) {
			std::cout << "Response of wait for command:" << std::endl;
			std::cout << "Success:" << (long int) srv.response.success
					<< std::endl;
			std::cout << "Args:" << srv.response.args << std::endl;
		} else {
			std::cout << testPrompt << "Failed to call service of wait_command"
					<< std::endl;
			responseMsg.successful = 0;
		}
		responseMsg.params = srv.response.args;
		responseMsg.successful = srv.response.success;
	} else {
		if (!runSMCLIPS) {
			initMsg = responseMsg;
			return;
		}
		std::cout << testPrompt << "Needed services are not available :'("
				<< std::endl;
		responseMsg.successful = 0;
	}
	if (runSMCLIPS) {
		validateAttempsResponse(responseMsg);
		//command_response_pub.publish(responseMsg);
	}
}

void callbackCmdInterpret(
		const planner_msgs::PlanningCmdClips::ConstPtr& msg) {
	std::cout << testPrompt << "--------- Command interpreter ---------"
			<< std::endl;
	std::cout << "name:" << msg->name << std::endl;
	std::cout << "params:" << msg->params << std::endl;

	planner_msgs::PlanningCmdClips responseMsg;
	responseMsg.name = msg->name;
	responseMsg.params = msg->params;
	responseMsg.id = msg->id;

	bool success = ros::service::waitForService("/planning_rm/interpreter",
			5000);
	if (success) {
		planner_msgs::planning_cmd srv;
		srv.request.name = "test_interprete";
		srv.request.params = "Ready to interpretation";
		if (srvCltInterpreter.call(srv)) {
			std::cout << "Response of interpreter:" << std::endl;
			std::cout << "Success:" << (long int) srv.response.success
					<< std::endl;
			std::cout << "Args:" << srv.response.args << std::endl;
			responseMsg.params = srv.response.args;
			responseMsg.successful = srv.response.success;
		} else {
			std::cout << testPrompt << "Failed to call service of interpreter"
					<< std::endl;
			responseMsg.successful = 0;
		}
	} else {
		std::cout << testPrompt << "Needed services are not available :'("
				<< std::endl;
		responseMsg.successful = 0;
	}
	validateAttempsResponse(responseMsg);
	//command_response_pub.publish(responseMsg);

}

void callbackCmdConfirmation(
		const planner_msgs::PlanningCmdClips::ConstPtr& msg) {
	std::cout << testPrompt << "--------- Command confirmation ---------"
			<< std::endl;
	std::cout << "name:" << msg->name << std::endl;
	std::cout << "params:" << msg->params << std::endl;

	planner_msgs::PlanningCmdClips responseMsg;
	responseMsg.name = msg->name;
	responseMsg.params = msg->params;
	responseMsg.id = msg->id;

	bool success = true;
    ros::service::waitForService("spg_say", 5000);
	success = success
			& ros::service::waitForService("/planning_rm/confirmation",
					5000);
	if (success) {
		std::string to_spech = responseMsg.params;
		boost::replace_all(to_spech, "_", " ");
		std::stringstream ss;
		ss << "Do you want me " << to_spech;
		std::cout << "------------- to_spech: ------------------ " << ss.str()
				<< std::endl;

		//JustinaHRI::waitAfterSay(ss.str(), 2500);

		planner_msgs::planning_cmd srv;
		srv.request.name = "test_confirmation";
		srv.request.params = responseMsg.params;
		if (srvCltWaitConfirmation.call(srv)) {
			std::cout << "Response of confirmation:" << std::endl;
			std::cout << "Success:" << (long int) srv.response.success
					<< std::endl;
			std::cout << "Args:" << srv.response.args << std::endl;
			if (srv.response.success)
				//JustinaHRI::waitAfterSay("Ok i start to execute the command",2000);
				std::cout << "Ok i start to execute the commnad" << std::endl;
			else
				//JustinaHRI::waitAfterSay("Repeate the command please", 2000);
				std::cout << "repeate the command please" << std::endl;

			responseMsg.params = srv.response.args;
			responseMsg.successful = srv.response.success;
		} else {
			std::cout << testPrompt << "Failed to call service of confirmation"
					<< std::endl;
			responseMsg.successful = 0;
			//JustinaHRI::waitAfterSay("Repeate the command please", 2000);
		}
	} else {
		std::cout << testPrompt << "Needed services are not available :'("
				<< std::endl;
		responseMsg.successful = 0;
	}
	validateAttempsResponse(responseMsg);
	//command_response_pub.publish(responseMsg);
}

void callbackCmdGetTasks(const planner_msgs::PlanningCmdClips::ConstPtr& msg) {
	std::cout << testPrompt << "--------- Command get tasks ---------"
			<< std::endl;
	std::cout << "name:" << msg->name << std::endl;
	std::cout << "params:" << msg->params << std::endl;

	planner_msgs::PlanningCmdClips responseMsg;
	responseMsg.name = msg->name;
	responseMsg.params = msg->params;
	responseMsg.id = msg->id;

	bool success = ros::service::waitForService("/planning_rm/get_task",
			5000);
	if (success) {
		planner_msgs::planning_cmd srv;
		srv.request.name = "cmd_task";
		srv.request.params = "Test of get_task module";
		if (srvCltGetTasks.call(srv)) {
			std::cout << "Response of get tasks:" << std::endl;
			std::cout << "Success:" << (long int) srv.response.success
					<< std::endl;
			std::cout << "Args:" << srv.response.args << std::endl;
			responseMsg.params = srv.response.args;
			responseMsg.successful = srv.response.success;
		} else {
			std::cout << testPrompt << "Failed to call get tasks" << std::endl;
			responseMsg.successful = 0;
		}
	} else {
		std::cout << testPrompt << "Needed services are not available :'("
				<< std::endl;
		responseMsg.successful = 0;
	}
	validateAttempsResponse(responseMsg);
	//command_response_pub.publish(responseMsg);
}

void callbackCmdNavigation(
		const planner_msgs::PlanningCmdClips::ConstPtr& msg) {
	std::cout << testPrompt << "--------- Command Navigation ---------"
			<< std::endl;
	std::cout << "name:" << msg->name << std::endl;
	std::cout << "params:" << msg->params << std::endl;

	planner_msgs::PlanningCmdClips responseMsg;
	responseMsg.name = msg->name;
	responseMsg.params = msg->params;
	responseMsg.id = msg->id;

	std::vector<std::string> tokens;
	std::string str = responseMsg.params;
	split(tokens, str, is_any_of(" "));

	/// Aqui va el codigo para la navegacion

	responseMsg.successful = 1;
	validateAttempsResponse(responseMsg);
	//command_response_pub.publish(responseMsg);
}

void callbackCmdAnswer(const planner_msgs::PlanningCmdClips::ConstPtr& msg) {

	std::cout << testPrompt << "--------- Command answer a question ---------"
			<< std::endl;
	std::cout << "name:" << msg->name << std::endl;
	std::cout << "params:" << msg->params << std::endl;

	planner_msgs::PlanningCmdClips responseMsg;
	responseMsg.name = msg->name;
	responseMsg.params = msg->params;
	responseMsg.id = msg->id;

	std::stringstream ss;
	std::vector<std::string> tokens;
	std::string str = responseMsg.params;
	split(tokens, str, is_any_of(" "));

	
	responseMsg.successful = 1;
	
	validateAttempsResponse(responseMsg);
	//command_response_pub.publish(responseMsg);
}

void callbackCmdFindObject(
		const planner_msgs::PlanningCmdClips::ConstPtr& msg) {
	std::cout << testPrompt << "--------- Command find Object or Person ---------"
			<< std::endl;
	std::cout << "name:" << msg->name << std::endl;
	std::cout << "params:" << msg->params << std::endl;

	planner_msgs::PlanningCmdClips responseMsg;
	responseMsg.name = msg->name;
	responseMsg.params = msg->params;
	responseMsg.id = msg->id;

	std::vector<std::string> tokens;
	std::string str = responseMsg.params;
	split(tokens, str, is_any_of(" "));
	std::stringstream ss;
	
	bool success;

		std::cout << testPrompt << "find: " << tokens[0] << std::endl;

		ss.str("");
		if (tokens[0] == "person") {
			/// Aqui va el codigo para encontrar una persona desconocida
			ss << responseMsg.params << " " << 1 << " " << 1 << " " << 1;
			success = true;
		}  else if (tokens[0] == "specific") {
			/// Aqui va el codigo para encontrar una persona en especifico 
			ss << "find_spc_person " << tokens[0] << " " << tokens[1];
			success = true;
		} else {
			geometry_msgs::Pose pose; /// variable para almacenar coordenadas del objeto
			bool withLeftOrRightArm; /// bandera para saber con que mano tomar el objeto

			pose.position.x = 0.0;
			pose.position.y = 0.0;
			pose.position.z = 0.0;
			withLeftOrRightArm = true;

			//// aqui va el codigo para encontrar el objeto

			if(withLeftOrRightArm)
				ss << responseMsg.params << " " << pose.position.x << " " << pose.position.y << " " << pose.position.z << " left";
			else
				ss << responseMsg.params << " " << pose.position.x << " " << pose.position.y << " " << pose.position.z << " right";
			success = true;
		}
		responseMsg.params = ss.str();
	if (success)
		responseMsg.successful = 1;
	else
		responseMsg.successful = 0;
	
	validateAttempsResponse(responseMsg);
}

void callbackAskFor(const planner_msgs::PlanningCmdClips::ConstPtr& msg) {
	std::cout << testPrompt << "--------- Command Ask for ---------"
			<< std::endl;
	std::cout << "name:" << msg->name << std::endl;
	std::cout << "params:" << msg->params << std::endl;

	planner_msgs::PlanningCmdClips responseMsg;
	responseMsg.name = msg->name;
	responseMsg.params = msg->params;
	responseMsg.id = msg->id;

	/*std::stringstream ss;
	 ss << responseMsg.params << " " << "table";
	 responseMsg.params = ss.str();*/
	responseMsg.successful = 1;
	validateAttempsResponse(responseMsg);
	//command_response_pub.publish(responseMsg);
}

void callbackStatusObject(
		const planner_msgs::PlanningCmdClips::ConstPtr& msg) {
	std::cout << testPrompt << "--------- Command Status object ---------"
			<< std::endl;
	std::cout << "name:" << msg->name << std::endl;
	std::cout << "params:" << msg->params << std::endl;

	planner_msgs::PlanningCmdClips responseMsg;
	responseMsg.name = msg->name;
	responseMsg.params = msg->params;
	responseMsg.id = msg->id;

	std::stringstream ss;
	ss << responseMsg.params << " " << "open";

	//Aqui va el codigo para saber si el robot esta 
	//en buena posición para tomar el objeto


	responseMsg.params = ss.str();
	responseMsg.successful = 0;
	validateAttempsResponse(responseMsg);
	//command_response_pub.publish(responseMsg);
}

void callbackMoveActuator(
		const planner_msgs::PlanningCmdClips::ConstPtr& msg) {
	std::cout << testPrompt << "--------- Command Move actuator ---------"
			<< std::endl;
	std::cout << "name:" << msg->name << std::endl;
	std::cout << "params:" << msg->params << std::endl;

	planner_msgs::PlanningCmdClips responseMsg;
	responseMsg.name = msg->name;
	responseMsg.params = msg->params;
	responseMsg.id = msg->id;

	std::vector<std::string> tokens;
	std::string str = responseMsg.params;
	split(tokens, str, is_any_of(" "));
	bool armFlag = true;

	if(tokens[4] == "false")
			armFlag = false; // armFlag se vuelve falso si se va a usar la mano derecha para sujetar el objeto
	
	// Aqui va el código para calcular la cinematica inversa y sujetar el objeto
	

	responseMsg.successful = 1;

	validateAttempsResponse(responseMsg);
	//command_response_pub.publish(responseMsg);
}

void callbackDrop(const planner_msgs::PlanningCmdClips::ConstPtr& msg) {
	std::cout << testPrompt << "--------- Command Drop ---------" << std::endl;
	std::cout << "name:" << msg->name << std::endl;
	std::cout << "params:" << msg->params << std::endl;

	planner_msgs::PlanningCmdClips responseMsg;
	responseMsg.name = msg->name;
	responseMsg.params = msg->params;
	responseMsg.id = msg->id;

	std::vector<std::string> tokens;
	std::string str = responseMsg.params;
	split(tokens, str, is_any_of(" "));
	std::stringstream ss;
	bool armFlag = true;
	bool succes;

	if(tokens[2] == "false")
			armFlag = false;

	if(tokens[0] == "person")
		std::cout << "Handover object to person " << std::endl;
		// aqui va el codigo para entregar un objeto a una persona
	else if(tokens[0] == "object"){
		ss.str("");
		ss << "I am going to deliver the " << tokens[1];
		// aqui va el codigo para dejar un objeto en un lugar
	}
	
	responseMsg.successful = 1;

	validateAttempsResponse(responseMsg);
}

void callbackUnknown(const planner_msgs::PlanningCmdClips::ConstPtr& msg) {
	std::cout << testPrompt << "--------- Command unknown ---------"<< std::endl;
	std::cout << "name:" << msg->name << std::endl;
	std::cout << "params:" << msg->params << std::endl;

	planner_msgs::PlanningCmdClips responseMsg;
	responseMsg.name = msg->name;
	responseMsg.params = msg->params;
	responseMsg.id = msg->id;

	responseMsg.successful = 1;
	validateAttempsResponse(responseMsg);
	//command_response_pub.publish(responseMsg);
}


void callbackAskPerson(const planner_msgs::PlanningCmdClips::ConstPtr& msg) {
	std::cout << testPrompt << "--------- Command ask for person ---------"
			<< std::endl;
	std::cout << "name:" << msg->name << std::endl;
	std::cout << "params:" << msg->params << std::endl;

	planner_msgs::PlanningCmdClips responseMsg;
	responseMsg.name = msg->name;
	responseMsg.params = msg->params;
	responseMsg.id = msg->id;

	bool success = true;

		std::string to_spech = responseMsg.params;
		boost::replace_all(to_spech, "_", " ");
		std::stringstream ss;
		ss << "Hello, " << to_spech << " is your name";
		std::cout << "------------- to_spech: ------------------ " << std::endl;
		std::cout << ss.str() << std::endl;
		if (success){
				ss.str("");
				ss << "Hello " << to_spech;
				responseMsg.successful = 1;
				std::cout << ss.str() << std::endl;				
			}
		else{
				ss.str("");
				ss << to_spech << ", I try to find you again ";
				std::cout << ss.str() << std::endl;
				responseMsg.successful = 0;
			}

	validateAttempsResponse(responseMsg);
	//command_response_pub.publish(responseMsg);
}

int main(int argc, char **argv) {

	ros::init(argc, argv, "gpsr_test");
	ros::NodeHandle n;
	ros::Rate rate(10);

	srvCltGetTasks = n.serviceClient<planner_msgs::planning_cmd>("/planning_rm/get_task");
	srvCltInterpreter = n.serviceClient<planner_msgs::planning_cmd>("/planning_rm/interpreter");
	srvCltWaitConfirmation = n.serviceClient<planner_msgs::planning_cmd>("/planning_rm/confirmation");
	srvCltWaitForCommand = n.serviceClient<planner_msgs::planning_cmd>("/planning_rm/wait_command");
	srvCltAnswer = n.serviceClient<planner_msgs::planning_cmd>("/planning_rm/answer");

	ros::Subscriber subCmdSpeech = n.subscribe("/planning_rm/cmd_speech", 1, callbackCmdSpeech);
	ros::Subscriber subCmdInterpret = n.subscribe("/planning_rm/cmd_int", 1, callbackCmdInterpret);
	ros::Subscriber subCmdConfirmation = n.subscribe("/planning_rm/cmd_conf", 1, callbackCmdConfirmation);
	ros::Subscriber subCmdGetTasks = n.subscribe("/planning_rm/cmd_task", 1, callbackCmdGetTasks);

	ros::Subscriber subCmdNavigation = n.subscribe("/planning_rm/cmd_goto", 1, callbackCmdNavigation);
	ros::Subscriber subCmdAnswer = n.subscribe("/planning_rm/cmd_answer", 1, callbackCmdAnswer);
	ros::Subscriber subCmdFindObject = n.subscribe("/planning_rm/cmd_find_object", 1, callbackCmdFindObject);
	ros::Subscriber subCmdAskFor = n.subscribe("/planning_rm/cmd_ask_for", 1, callbackAskFor);
	ros::Subscriber subCmdStatusObject = n.subscribe("/planning_rm/cmd_status_object", 1, callbackStatusObject);
	ros::Subscriber subCmdMoveActuator = n.subscribe("/planning_rm/cmd_move_actuator", 1, callbackMoveActuator);
	ros::Subscriber subCmdDrop = n.subscribe("/planning_rm/cmd_drop", 1, callbackDrop);
	ros::Subscriber subCmdUnknown = n.subscribe("/planning_rm/cmd_unknown", 1, callbackUnknown);
	ros::Subscriber subAskPerson = n.subscribe("/planning_rm/cmd_ask_person", 1, callbackAskPerson);

	command_response_pub = n.advertise<planner_msgs::PlanningCmdClips>("/planning_rm/command_response", 1);

	while (ros::ok()) {

		switch (state) {
		case SM_INIT:
			if (startSignalSM) {
				std::cout << "I will start the Robot test" << std::endl;
				state = SM_SAY_WAIT_FOR_DOOR;
			}
			break;
		case SM_SAY_WAIT_FOR_DOOR:
			initMsg.successful = false;
			runSMCLIPS = true;
			//initMsg.params = "Inicializa SM";
			command_response_pub.publish(initMsg);
			state = SM_RUN_SM_CLIPS;
			break;
		
		case SM_SCRIPT:
			initSpeech.successful = false;
			runSMCLIPS = true;
			
			//inicializar nombre del mensaje y su ID
			initSpeech.name = "cmd_set_task";
			initSpeech.id = 10;

			//nombre del plan y numero de pasos
			initSpeech.params = "plan-1021 8" ;
			initSpeech.successful = true;
			command_response_pub.publish(initSpeech);
			boost::this_thread::sleep(boost::posix_time::milliseconds(400));
			ros::spinOnce();

			//Mensaje de Navegación a la cocina
			initSpeech.params = "robot update_object_location location kitchen 1" ;
			initSpeech.successful = true;
			command_response_pub.publish(initSpeech);
			boost::this_thread::sleep(boost::posix_time::milliseconds(400));
			ros::spinOnce();

			//Navegación a el living room
			initSpeech.params = "robot update_object_location location bedroom 2" ;
			initSpeech.successful = true;
			command_response_pub.publish(initSpeech);
			boost::this_thread::sleep(boost::posix_time::milliseconds(400));
			ros::spinOnce();

			//Find specific person in room
			initSpeech.params = "robot find_person_in_room barbara office 3" ;
			initSpeech.successful = true;
			command_response_pub.publish(initSpeech);
			boost::this_thread::sleep(boost::posix_time::milliseconds(400));
			ros::spinOnce();
			
			//Find unknown person in room
			initSpeech.params = "robot find_person_in_room fridge 4" ;
			initSpeech.successful = true;
			command_response_pub.publish(initSpeech);
			boost::this_thread::sleep(boost::posix_time::milliseconds(400));
			ros::spinOnce();

			//grasp object
			initSpeech.params = "robot get_object apple counter 5" ;
			initSpeech.successful = true;
			command_response_pub.publish(initSpeech);
			boost::this_thread::sleep(boost::posix_time::milliseconds(400));
			ros::spinOnce();

			//handover object to person
			initSpeech.params = "robot handover_object apple 6" ;
			initSpeech.successful = true;
			command_response_pub.publish(initSpeech);
			boost::this_thread::sleep(boost::posix_time::milliseconds(400));
			ros::spinOnce();

			//grasp object
			initSpeech.params = "robot get_object paprika drawer 7" ;
			initSpeech.successful = true;
			command_response_pub.publish(initSpeech);
			boost::this_thread::sleep(boost::posix_time::milliseconds(400));
			ros::spinOnce();
			
			//deliver object in location
			initSpeech.params = "robot deliver_in_position paprika bar 8" ;
			initSpeech.successful = true;
			command_response_pub.publish(initSpeech);
			boost::this_thread::sleep(boost::posix_time::milliseconds(400));
			ros::spinOnce();

			//Tarea de finalizacion
			initSpeech.params = "Final" ;
			initSpeech.successful = false;
			command_response_pub.publish(initSpeech);
			boost::this_thread::sleep(boost::posix_time::milliseconds(400));
			ros::spinOnce();

			state = SM_RUN_SM_CLIPS;
			break;
		case SM_RUN_SM_CLIPS:
			break;
		}

		rate.sleep();
		ros::spinOnce();
	}


	return 0;

}
