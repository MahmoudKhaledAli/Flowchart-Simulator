#ifndef EDIT_CONN_H
#define EDIT_CONN_H

#include "Action.h"
#include "..\Statements\Connector.h"

//Edit a Connector Action
//This class is responsible for 
//Getting the new source and desitnation statements from the user
//Calls the function edit in the class connector and passing the new parameters
class EditConn : public Action
{
private:
	Point StartPt; //Start point of the connector
	Point EndPt; //End point of the connector 
	Statement* Src; //Source statement
	Statement* Dest; //Destination statement
public:
	EditConn(ApplicationManager *pAppManager);
	
	//Getting the new statements
	virtual void ReadActionParameters();

	//Editing the selected connector
	virtual void Execute();

};

#endif