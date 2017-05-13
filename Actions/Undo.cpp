#include "Undo.h"
#include "LoadAction.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Undo::Undo(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void Undo::ReadActionParameters()
{
	//No Input needed
}

void Undo::Execute()
{
	if (pManager->GetUndo() > 1)
	{
		LoadAction Load(pManager, "temp\\temp" + to_string(pManager->GetUndo() - 2));
		Load.Execute();
		pManager->DecrementUndo();
	}
	
}

