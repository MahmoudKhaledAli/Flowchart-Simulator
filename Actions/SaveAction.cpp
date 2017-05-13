#include "SaveAction.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

SaveAction::SaveAction(ApplicationManager *pAppManager, string Name):Action(pAppManager)
{
	file = Name;
}

void SaveAction::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	if (file == "")
	{
		pOut->PrintMessage("Write the name of the file :");
		file = pIn->GetString(pOut);
	}

}

void SaveAction::Execute()
{
	ReadActionParameters();
	outfile.open("Saved Graphs\\" + file +".txt");// asking the user about the file name
	pManager->Save(outfile);// save function is a function in the application manager which calls a save function in each statement
	outfile.close();// closing the filde after saving
}

