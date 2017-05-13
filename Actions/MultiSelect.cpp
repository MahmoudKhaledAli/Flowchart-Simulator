#include "MultiSelect.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
MultiSelect::MultiSelect(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void MultiSelect::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->ClearStatusBar();
	Point Click;
	pOut->PrintMessage("Selecting Multiple Statements/Connectors: Click a figure to select it, click anywhere to exit: ");
	Statement* pStat = NULL;
	Connector* pConn = NULL;
	//Getting the user input and selecting the statements until the user click on an empty space
	do
	{
		pIn->GetPointClicked(Click);
		pStat = pManager->GetStatement(Click);
		if (pStat)
		{
			pStat->SetSelected(!pStat->IsSelected());
			int countofselected=pManager->GetSelectedCount();//hesham
			if(countofselected == 1) //hesham
				pManager->SetSelectedStatement(pStat);
			else if(countofselected > 1)
				pManager->SetSelectedStatement(NULL);
		}
		pConn = pManager->GetConnector(Click);
		if (pConn)
			pConn->SetSelected(!pConn->IsSelected());
		pManager->UpdateInterface();
		pOut->PrintMessage("Selecting Multiple Statements/Connectors: Click a figure to select it, click anywhere to exit: ");
	}
	while (pStat != NULL || pConn != NULL);

	pOut->ClearStatusBar();
}

void MultiSelect::Execute()
{
	if (pManager->GetSelectedStatement()) //De-selecting the previously selected statement
	{		pManager->GetSelectedStatement()->SetSelected(false);
		pManager->SetSelectedStatement(NULL);
	}
	if (pManager->GetSelectedConnector()) //De-selecting the previously selected connector
	{
		pManager->GetSelectedConnector()->SetSelected(false);
		pManager->SetSelectedConnector(NULL);
	}
	pManager->UpdateInterface();
	ReadActionParameters();
}

