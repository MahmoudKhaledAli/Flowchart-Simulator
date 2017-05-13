#include "EditConn.h"
#include "..\Statements\Cond.h"
#include "..\Statements\End.h"
#include "..\Statements\Start.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
EditConn::EditConn(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void EditConn::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	Connector* pConn = pManager->GetSelectedConnector();
	//Setting the connectors in the source statement to null in case the user wants to use the same source statement
	Cond* pCondSrc = dynamic_cast<Cond*>(pConn->getSrcStat());
	if (pCondSrc)
	{
		if (pConn == pCondSrc->GetYesConn())
			pCondSrc->SetYesConn(NULL);
		else
			pCondSrc->SetNoConn(NULL);
	}
	else
	{
		pConn->getSrcStat()->SetConn(NULL);
	}

	Point Click;
	Point St;

	Statement* pStat = NULL;
	Cond* pCond = NULL;
	int CondOut;

	pOut->PrintMessage("Editing Connector, Click New Source Statement: ");

	while (!pStat)
	{
		pIn->GetPointClicked(Click);
		pStat = pManager->GetStatement(Click);
		if (!pStat)
		{

		}
		else if (dynamic_cast<End*>(pStat))//if the src statement is end , cant be
		{
			pOut->PrintMessage("A connection cannot exit an End statement, select another statement: ");
			pStat = NULL;
		}
		else if (pStat->GetConn())//if there is already connector, cant be
		{
			pOut->PrintMessage("Statement already has a connector, select another statement: ");
			pStat = NULL;
		}
	}
	Src = pStat;
	bool Conditional = true;
	if (pCond = dynamic_cast<Cond*>(pStat))
	{
		pOut->PrintMessage("Select outlet for the conditional statement (1-Yes/2-No): ");
		while (Conditional)
		{
			CondOut = int(pIn->GetValue(pOut));
			if (CondOut == 1)
			{
				if (!pCond->GetYesConn())
				{
					Conditional = false;
					StartPt = pCond->GetYesOutlet();
					pCond->SetYesConn(pConn);
				}
				else
					pOut->PrintMessage("Outlet already used, Select outlet for the conditional statement (1-Yes/2-No): ");
			}
			else
			{
				if (!pCond->GetNoConn())
				{
					Conditional = false;
					EndPt = pCond->GetNoOutlet();
					pCond->SetNoConn(pConn);
				}
				else
					pOut->PrintMessage("Outlet already used, Select outlet for the conditional statement (1-Yes/2-No): ");
			}
		}

	}
	else
	{
		StartPt = pStat->GetOutlet();
		pStat->SetConn(pConn);
	}


	pOut->PrintMessage("Click the destination statement: ");

	pStat = NULL;
	while (!pStat)
	{
		pIn->GetPointClicked(Click);
		pStat = pManager->GetStatement(Click);
		if (!pStat)
		{

		}
		else if (dynamic_cast<Start *>(pStat))
		{
			pOut->PrintMessage("A connection cannot enter a start statement, select another statement: ");
			pStat = NULL;
		}
		else if (pStat == pConn->getSrcStat())
		{
			pOut->PrintMessage("A statement can't be connected to itself, select another statement: ");
			pStat = NULL;
		}
	}

	Dest = pStat;
	EndPt = pStat->GetInlet();//setting the endpoint of the connector with the inlet point of the destination statement

	pOut->ClearStatusBar();
}

void EditConn::Execute()
{
	ReadActionParameters();
	
	pManager->GetSelectedConnector()->Edit(StartPt,EndPt,Src,Dest);// calling the function in the connector to set the connector selected with the new parameters that was set by read action parameters
	pManager->GetSelectedConnector()->SetSelected(false);
	pManager->SetSelectedConnector(NULL);
}

