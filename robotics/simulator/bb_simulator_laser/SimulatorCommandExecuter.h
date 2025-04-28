/* 
 * File:   SumCommandExecuter.cpp
 * Author: Mauricio Matamoros
 *
 * There are two kinds of command executers: SyncCommandExecuter and AsyncCommandExecuter.
 * SyncCommandExecuter: those are executed within the CommandManager's main thread context, they do not allow communications and shall return in a few milliseconds
 * AsyncCommandExecuter: those are executed in a separate thread, allow communications and may take long periods of time to execute.
 */

#ifndef __SIMULATOR_COMMAND_EXECUTER_H__
#define	__SIMULATOR_COMMAND_EXECUTER_H__

#include "uRobotics/api/Command.h"
#include "uRobotics/api/Response.h"
#include "uRobotics/api/SyncCommandExecuter.h"

class robotsensorCommandExecuter : public SyncCommandExecuter
{
public:
	robotsensorCommandExecuter(void);
	~robotsensorCommandExecuter(void);
	// This method indicates if the command executer requires parameters or not. It is recommended to be overloaded
	virtual bool parametersRequired() const;
	// This method executes the command. It must be overloaded
	virtual Response* SyncTask(const Command& command);
};



class readlaserCommandExecuter : public SyncCommandExecuter
{
public:
	readlaserCommandExecuter(void);
	~readlaserCommandExecuter(void);
	// This method indicates if the command executer requires parameters or not. It is recommended to be overloaded
	virtual bool parametersRequired() const;
	// This method executes the command. It must be overloaded
	virtual Response* SyncTask(const Command& command);
};


#endif // __SIMULATOR_COMMAND_EXECUTER_H__
