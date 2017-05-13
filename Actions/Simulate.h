#ifndef SIM_H
#define SIM_H

#include "Action.h"
#include "..\Statements\Start.h"
//#include "..\Statements\End.h"
#include "..\Actions\Validate.h"


//Simulate Action
//This class is responsible for :
// Validating the flow chart then simulating it
class Simulate : public Action
{
public:
	Simulate(ApplicationManager *pAppManager);

	//No input needed
	virtual void ReadActionParameters();

	//Validating then simulating the flow chart and displaying the output
	virtual void Execute();


};

#endif