#ifndef MOVE_H
#define MOVE_H

#include "Action.h"
#include "..\Statements\Statement.h"
#include "..\Statements\Connector.h"

//Move Action
//This class is responsible for 
// Moving the selected statements and connectors
class Move : public Action
{
	private:
		Point Position;//to know where to move the selected statement
	public:
		Move(ApplicationManager *pAppManager);

		//Taking input from the user to know the position of moved the selected statements 
		virtual void ReadActionParameters();

		virtual void Execute();
};

#endif