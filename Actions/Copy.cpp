#include "Copy.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Copy::Copy(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void Copy::ReadActionParameters()
{
	pManager->GetOutput()->ClearStatusBar();
	//No Input needed
}

void Copy::Execute()
{	
//	pManager->SetPasteConnList();
	int countofselected=pManager->GetSelectedCount();
	Statement*Stat=pManager->GetSelectedStatement();
	if(countofselected==1)
	{
		Statement*Stat2;
		Stat2=Stat->GetCopied();
		pManager->SetPasteStat(Stat2);
	}
	else if(countofselected > 1)
	{
		pManager->SetPasteList();
		pManager->SetPasteStat(NULL);
	}

}