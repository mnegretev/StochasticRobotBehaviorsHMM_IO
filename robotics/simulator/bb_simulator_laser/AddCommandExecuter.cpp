#include "AddCommandExecuter.h"

#include <cstdlib>
#include <string>
#include <sstream>
#include <uRobotics/api/Parser.h>
#include <uRobotics/utilities/Scanner.h>

using namespace Robotics::Utilities;


// In the constructor may be defined the name of the command this command executer manages
AddCommandExecuter::AddCommandExecuter(void) :
SyncCommandExecuter("add"){}

AddCommandExecuter::~AddCommandExecuter(void){}

// In order to sum, parameters are required so this method returns true.
bool AddCommandExecuter::parametersRequired() const{
	return true;
}

// This method performs the sum
Response* AddCommandExecuter::SyncTask(const Command& command){
	double a, b;
	size_t cc = 0;
	std::stringstream ss;

	// Get the first number from the command parameters
	Scanner::xtractDouble(command.parameters, cc, a);
	// Skip spaces that separate both numbers
	Scanner::skipSpaces(command.parameters, cc);
	// Get the second number from the command parameters
	Scanner::xtractDouble(command.parameters, cc, b);
	// Write the result to the console output
	std::cout << "Add:" << a << " + " << b << " = " << (a+b) << std::endl;
	std::cout.flush();
	// Convert the result of the sum to a string
	ss << (a+b);
	// Generate the response for the command
	Response* r = Response::createFromCommand(command, true);
	// Update parameters with result
	r->parameters = ss.str();
	return r;
}


