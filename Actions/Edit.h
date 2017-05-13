#ifndef EDIT_H
#define EDIT_H

#include "Action.h"
#include "..\Statements\Connector.h"

//Edit Action
//This class is responsible for 
//Editing a connector a statement
//Calls the function edit in the class connector or statement
class Edit : public Action
{
public:
	Edit(ApplicationManager *pAppManager);

	//no input needed
	virtual void ReadActionParameters();

	//Creating an action of Edit Connector or Edit Statement
	virtual void Execute();

};

#endif