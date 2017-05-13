#include "Redo.h"
#include "LoadAction.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Redo::Redo(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void Redo::ReadActionParameters()
{
	//No Input needed
}

void Redo::Execute()
{
	if (pManager->GetUndo() < pManager->GetActCount())
	{
		LoadAction Load(pManager, "temp\\temp" + to_string(pManager->GetUndo()));
		Load.Execute();
		pManager->IncrementUndo();
	}

}

