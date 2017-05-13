#ifndef GEN_H
#define GEN_H

#include "Action.h"
#include "..\Statements\Start.h"
//#include "..\Statements\End.h"
#include "..\Actions\Validate.h"
#include "..\Statements\OpAssign.h"
#include "..\Statements\Read.h"
#include "..\Statements\SmplAssign.h"
#include "..\Statements\VarAssign.h"


//Generate Action
//This class is responsible for :
// Generating a code file from the flow chart
class Generate : public Action
{
public:
	Generate(ApplicationManager *pAppManager);

	//No input needed
	virtual void ReadActionParameters();

	//Validating the flow chart then generating the code for each statement
	virtual void Execute();


};

#endif