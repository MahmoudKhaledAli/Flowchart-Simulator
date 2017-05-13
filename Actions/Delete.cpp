#include "Delete.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Delete::Delete(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void Delete::ReadActionParameters()
{
	pManager->GetOutput()->ClearStatusBar();
	//No Input needed
}

void Delete::Execute()
{
	ReadActionParameters();
	Statement * const * StatList = pManager->GetStatList();
	Connector * const * ConnList = pManager->GetConList();
	int StatCount = pManager->GetStatCount();
	int ConnCount = pManager->GetConnCount();
	if (pManager->GetSelectedStatement()) //if only one statement is selected
	{
		pManager->RemoveStatement(pManager->GetSelectedStatement());
		pManager->SetSelectedStatement(NULL);
	}
	else if (pManager->GetSelectedConnector()) //if only one connector is collected
	{
		pManager->RemoveConnector(pManager->GetSelectedConnector());
		pManager->SetSelectedConnector(NULL);
	}
	else //In case of multiple selections
	{
		for (int i = 0; i < StatCount; i++) //Looping through the statements and deleteting the selected ones
		{
			if (StatList[i]->IsSelected())
			{
				pManager->RemoveStatement(StatList[i]); //Removing the statement if it selected
				i--; //We need to check the same index again because of shifting in the StatList array
			}
			//Updating the lists and counts
			StatList = pManager->GetStatList();
			ConnList = pManager->GetConList();
			StatCount = pManager->GetStatCount();
			ConnCount = pManager->GetConnCount();
		}
		for (int i = 0; i < ConnCount; i++)
		{
			if (ConnList[i]->IsSelected())
			{
				pManager->RemoveConnector(ConnList[i]); //Removing the connector
				i--;
			}
			StatList = pManager->GetStatList();
			ConnList = pManager->GetConList();
			StatCount = pManager->GetStatCount();
			ConnCount = pManager->GetConnCount();
		}
	}

}