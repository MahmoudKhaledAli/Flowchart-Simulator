#ifndef EDIT_STAT_H
#define EDIT_STAT_H

#include "Action.h"
#include "..\Statements\Connector.h"

//Edit a statement Action
//This class is responsible for 
//Editing a statement
//Calls the function edit in the class statement
class EditStat : public Action
{
public:
	EditStat(ApplicationManager *pAppManager);

	//No input needed
	virtual void ReadActionParameters();

	//Editing the selected statement
	virtual void Execute();

};

#endif