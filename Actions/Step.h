#ifndef STP_H
#define STP_H

#include "Action.h"
#include "..\Statements\Start.h"
//#include "..\Statements\End.h"
#include "..\Actions\Validate.h"


//Step by Step Action
//This class is responsible for :
// Simulating the flow chart in step by step mode and displaying the watch
class Step : public Action
{
public:
	Step(ApplicationManager *pAppManager);

	//No input needed
	virtual void ReadActionParameters();

	//Simulating the statements and waiting for user input
	virtual void Execute();


};

#endif