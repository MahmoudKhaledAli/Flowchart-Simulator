#include "EditStat.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
EditStat::EditStat(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void EditStat::ReadActionParameters()
{
	pManager->GetOutput()->ClearStatusBar();
	//No Input needed
}

void EditStat::Execute()
{
	pManager->GetSelectedStatement()->Edit(pManager->GetOutput(),pManager->GetInput());
	pManager->GetSelectedStatement()->SetSelected(false); //De-selecting the statement
	pManager->SetSelectedStatement(NULL);
}

