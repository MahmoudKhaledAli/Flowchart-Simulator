#include "Cut.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Cut::Cut(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void Cut::ReadActionParameters()
{
	pManager->GetOutput()->ClearStatusBar();
	//No Input needed
}

void Cut::Execute()
{	
//	pManager->SetPasteConnList();//connectors

	Statement*const*StatList=pManager->GetStatList();
	Connector*const*ConnList=pManager->GetConList();
	Statement*Stat=pManager->GetSelectedStatement();
	int countofselected=pManager->GetSelectedCount();
	if(countofselected==1)
	{
		Statement*Stat2;
		Stat2=Stat->GetCopied();
		pManager->RemoveStatement(Stat);
		pManager->SetPasteStat(Stat2);
		pManager->SetSelectedStatement(NULL);
	}
	else if(countofselected > 1)
	{
		pManager->SetPasteList();
		for (int i = 0; i < pManager->GetStatCount(); i++)
		{
			if(StatList[i]->IsSelected())
			{
				pManager->RemoveStatement(StatList[i]);
				--i;
			}
		}
		pManager->SetPasteStat(NULL);
		for (int i = 0; i <pManager->GetConnCount(); i++)//connectors
		{
			if(ConnList[i]->IsSelected())
			{
				pManager->RemoveConnector(ConnList[i]);
				--i;
			}
		}
	}
}

//////
//////int countofselected=pManager->GetSelectedCount();
//////	Statement*Stat=pManager->GetSelectedStatement();
//////	Statement* PasteList[100];
//////	if(countofselected==1)
//////	{
//////		Statement*Stat2;
//////		Stat2=Stat->GetCopied();
//////		pManager->SetPasteStat(Stat2);
//////	}
//////	else if(countofselected > 1)
//////	{
//////		pManager->SetPasteList();
//////	}


//if(Stat!=NULL)
//	{
//		Statement*Stat2;
//		Stat2=Stat->GetCopied();
//		pManager->RemoveStatement(Stat);
//		pManager->SetPasteStat(Stat2);
//		pManager->SetSelectedStatement(NULL);
//	}