#ifndef MULTI_SEL_H
#define MULTI_SEL_H

#include "Action.h"
#include "..\Statements\Connector.h"
#include "..\Statements\Statement.h"

//Multiple Select Action
//This class is responsible for 
//Selecting multiple connectors and statement
//Sets the selected bool to true/flase
class MultiSelect : public Action
{
public:
	MultiSelect(ApplicationManager *pAppManager);

	//Getting statements coordinates to select from user
	virtual void ReadActionParameters();

	//Setting the previously selected statement/connector to NULL
	virtual void Execute();

};

#endif