#ifndef COPY_H
#define COPY_H

#include "Action.h"
#include "..\Statements\Statement.h"
#include "..\Statements\Connector.h"

//Copy Action
//This class is responsible for 
// Copying the selected statements and connectors
class Copy : public Action
{
public:
	Copy(ApplicationManager *pAppManager);

	//No input needed
	virtual void ReadActionParameters();

	virtual void Execute();

};

#endif