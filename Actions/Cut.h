#ifndef CUT_H
#define CUT_H

#include "Action.h"
#include "..\Statements\Statement.h"
#include "..\Statements\Connector.h"

//Cut Action
//This class is responsible for 
// Cutting the selected statements and connectors
class Cut : public Action
{
public:
	Cut(ApplicationManager *pAppManager);

	//No input needed
	virtual void ReadActionParameters();

	virtual void Execute();

};

#endif