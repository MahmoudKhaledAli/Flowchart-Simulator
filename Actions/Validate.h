#ifndef VALIDATE_H
#define VALIDATE_H

#include "Action.h"
#include "..\Statements\Start.h"
#include "..\Statements\End.h"
#include "..\Statements\Cond.h"


//Validate Action
//This class is responsible for :
// Validating the flow chart
class Validate : public Action
{
private:
	bool Valid; //Bool to determine if the chart is valid
public:
	Validate(ApplicationManager *pAppManager);

	//No input needed
	virtual void ReadActionParameters();

	//Validating the condition
	virtual void Execute();

	bool IsValid(){ return Valid; }

	
};

#endif