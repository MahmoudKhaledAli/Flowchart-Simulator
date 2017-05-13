#ifndef SEL_H
#define SEL_H

#include "Action.h"
#include "..\Statements\Connector.h"
#include "..\Statements\Statement.h"

//Select Action
//This class is responsible for 
//Selecting a connector a statement
//Getting the coordinates from the user and setting the selected statement/connector to selected
class Select : public Action
{
private:
	Point Click;
public:
	Select(ApplicationManager *pAppManager);

	//Getting statement/connector coordinates to select from user
	virtual void ReadActionParameters();

	//Setting all previously selected statements/connectors to NULL
	virtual void Execute();

};

#endif