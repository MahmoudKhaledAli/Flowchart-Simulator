#include "AddConnector.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddConnector::AddConnector(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void AddConnector::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	pOut->PrintMessage("Add a connector: Click the source statement: ");

	Point Click;
	Point St;

	Statement* pStat = NULL;
	Cond* pCond = NULL;
//	int O;
	//Getting the source statement from the user and handling all cases
	while (!pStat)
	{
		pIn->GetPointClicked(Click);
		pStat = pManager->GetStatement(Click);
		if (!pStat) //If the point clicked doesn't belong to a statement
		{

		}
		else if (dynamic_cast<End*>(pStat)) //If the selected statement is an End Statement
		{
			pOut->PrintMessage("A connection cannot exit an End statement, select another statement: ");
				pStat = NULL;
		}
		else if (pStat->GetConn()) //If the selected statement already has connector
		{
			pOut->PrintMessage("Statement already has a connector, select another statement: ");
			pStat = NULL;
		}
	}
	Source = pStat;
	bool Conditional = true; // to determine if the user chose a valid outlet
	//if the source statement is a conditional, we get input from the user to determine which inlet to use
	if (pCond = dynamic_cast<Cond*>(pStat))
	{
		pOut->PrintMessage("Select outlet for the conditional statement (1-Yes/2-No): ");
		while (Conditional)
		{
			CondOut = int(pIn->GetValue(pOut)); //Number for the inlet of the connector
			if (CondOut == 1)
			{
				if (!pCond->GetYesConn()) //If the condition has no connectors from that outlet
				{
					Conditional = false;
					StartPt = pCond->GetYesOutlet();
				}
				else
					pOut->PrintMessage("Outlet already used, Select outlet for the conditional statement (1-Yes/2-No): ");
			}
			else
			{
				if (!pCond->GetNoConn())
				{
					Conditional = false;
					StartPt = pCond->GetNoOutlet();
				}
				else
					pOut->PrintMessage("Outlet already used, Select outlet for the conditional statement (1-Yes/2-No): ");
			}
		}
		
	}
	else
		StartPt = pStat->GetOutlet(); //setting the starting point of the connector to the outlet of the statement


	pOut->PrintMessage("Click the destination statement: ");
	//Getting the destination statement from the user
	pStat = NULL;
	while (!pStat)
	{
		pIn->GetPointClicked(Click);
		pStat = pManager->GetStatement(Click);
		if (!pStat)
		{

		}
		else if (dynamic_cast<Start *>(pStat)) //if the selected statement is a start statement
		{
			pOut->PrintMessage("A connection cannot enter a start statement, select another statement: ");
				pStat = NULL;
		}
		else if (pStat == Source) //if the selected statement is the same as the source statement
		{
			pOut->PrintMessage("A statement can't be connected to itself, select another statement: ");
			pStat = NULL;
		}
	}

	Destination = pStat;
	EndPt = pStat->GetInlet();

	pOut->ClearStatusBar();

}

void AddConnector::Execute()
{
	ReadActionParameters();


	//Creating a new connector
	Connector *pConn = new Connector(Source, Destination, StartPt, EndPt);
	Cond* pCond;
	//Setting the connector in case of a conditional statement
	if (pCond = dynamic_cast<Cond*>(Source))
	{
		if (CondOut == 1)
			pCond->SetYesConn(pConn);
		else
			pCond->SetNoConn(pConn);
	}
	else
		Source->SetConn(pConn);
	//Adding the created connector to the list of connectors
	pManager->AddConn(pConn);
}

