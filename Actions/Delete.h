#ifndef DELETE_H
#define DELETE_H

#include "Action.h"
#include "..\Statements\Statement.h"
#include "..\Statements\Connector.h"

//Delete Action
//This class is responsible for 
// Delete the selected statements and connectors
class Delete : public Action
{
public:
	Delete(ApplicationManager *pAppManager);

	//No input needed
	virtual void ReadActionParameters();

	//deleting the selected statements and connectors
	virtual void Execute();

};

#endif