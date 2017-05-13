#ifndef ADD_CONN_H
#define ADD_CONN_H

#include "Action.h"
#include "..\Statements\Connector.h"
#include "..\Statements\Start.h"
#include "..\Statements\End.h"
#include "..\Statements\Cond.h"

//Add Connector Action
//This class is responsible for 
// 1 - Getting coordinates of the 2 statements from the user
// 2 - Creating an object of connector class and fill it parameters
// 3 - Adding the created object to the list of connectors
class AddConnector : public Action
{
private:
	Statement* Source;	//Source statement
	Statement* Destination; //Destination statements
	Point StartPt; //Start point
	Point EndPt; //End Point
	int CondOut; //Flag for chosing the inlet in case the source statement is a condition statement
public:
	AddConnector(ApplicationManager *pAppManager);

	//Getting source and desitnation statements
	virtual void ReadActionParameters();

	//Create and add a connector to the list
	virtual void Execute();

};

#endif