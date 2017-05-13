#include "Select.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Select::Select(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void Select::ReadActionParameters()
{
	int StatCount = pManager->GetStatCount();
	int ConnCount = pManager->GetConnCount();
	Statement * const * StatList = pManager->GetStatList();
	Connector * const * ConnList = pManager->GetConList();
	//De-selecting all previously connected statements and connectors
	for (int i = 0; i < ConnCount; i++)
	{
		ConnList[i]->SetSelected(false);
	}

	for (int i = 0; i < StatCount; i++)
	{
		StatList[i]->SetSelected(false);
	}
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->ClearStatusBar();
	pManager->UpdateInterface();
	pOut->PrintMessage("Selecting A Statement or a Connector: Click a figure to select it, click anywhere to exit: ");
	pIn->GetPointClicked(Click);
	pOut->ClearStatusBar();
}

void Select::Execute()
{
	ReadActionParameters();
	//Setting the selected figures to null
	pManager->SetSelectedStatement(NULL);
	pManager->SetSelectedConnector(NULL);
	pManager->SetSelectedStatement(pManager->GetStatement(Click));
	if (pManager->GetStatement(Click))
	{
		pManager->GetStatement(Click)->SetSelected(true); //setting the selected statement to true
	}
	else
	{
		pManager->SetSelectedConnector(pManager->GetConnector(Click));
		if (pManager->GetConnector(Click))
			pManager->GetConnector(Click)->SetSelected(true); //setting the selected connector to true
	}


}

