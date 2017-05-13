#ifndef PASTE_H
#define PASTE_H

#include "Action.h"
#include "..\Statements\Statement.h"
#include "..\Statements\Connector.h"

#include "..\GUI\UI_Info.h"

//Paste Action
//This class is responsible for 
// Pasting the selected statements and connectors
class Paste : public Action
{
	private:
		Point Position;//to know where to paste the selected statement
	public:
		Paste(ApplicationManager *pAppManager);

		//Taking input from the user to know the position of pasting the selected statements 
		virtual void ReadActionParameters();

		virtual void Execute();

};

#endif