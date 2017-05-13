#include "Edit.h"
#include "EditConn.h"
#include "EditStat.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Edit::Edit(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void Edit::ReadActionParameters()
{
	pManager->GetOutput()->ClearStatusBar();
	//No Input needed
}

void Edit::Execute()
{
	ReadActionParameters();
	Action* pEdit = NULL;
	if (pManager->GetSelectedStatement()) //If a statement is selected
	{
		pEdit = new EditStat(pManager); //creating an object of Edit Statement class
	}
	else if (pManager->GetSelectedConnector()) //If a connector is selected
	{
		pEdit = new EditConn(pManager); //creating an object of Edit Connector Class
	}

	if (pEdit != NULL)
	{
		pEdit->Execute(); //Excuting the resulting action
		delete pEdit;
	} //Deleting the action

}

