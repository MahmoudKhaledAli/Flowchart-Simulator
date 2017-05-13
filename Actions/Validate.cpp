#include "Validate.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Validate::Validate(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void Validate::ReadActionParameters()
{
	//No input needed from user to validate the flow chart
}

void Validate::Execute()
{
	ReadActionParameters();
	int StatCount = pManager->GetStatCount();
	int ConnCount = pManager->GetConnCount();
	Statement * const * StatList = pManager->GetStatList();
	Connector * const * ConnList = pManager->GetConList();
	//bool StatementRHS = true;
	bool StartE = false;
	bool EndE = false;
	bool OneStart = false;
	bool OneEnd = false;
	//bool ConnectedIn;
	//bool ConnectedOut;
	bool ConnectedGraph = true;
	int i = 0;
//	Statement* pStat;
	Output *pOut = pManager->GetOutput();
	Start* pStart;
	End* pEnd;

	//Checking for start and end statements
	for (int i = 0; i < StatCount; i++)
	{
		pStart = dynamic_cast<Start*>(StatList[i]);
		pEnd = dynamic_cast<End*>(StatList[i]);
		if (pStart != NULL)
		{
			if (OneStart == false) //if there was no start statement before
			{
				StartE = true;
				OneStart = true;
			}
			else //if there was a start statement before
				StartE = false;
		}
		else if (pEnd != NULL)
		{
			if (OneEnd == false) //if there was no end statement before
			{
				EndE = true;
				OneEnd = true;
			}
			else //if there was an end statement before
				EndE = false;
		}
	}
	if (!(StartE && EndE))
	{
		pOut->PrintMessage("Not Valid: Chart has more than one start/end statement or none at all");
		Valid = false;
		return;
	}


	//Checking if all the statements are connected
	for (int i = 0; i < StatCount; i++)
	{
		ConnectedGraph = StatList[i]->IsConnected(ConnList, ConnCount);
		if (!ConnectedGraph)
		{
			pOut->PrintMessage("Not Valid: Chart is not connected properly");
			Valid = false;
			return;
		}
	}

	//Checking for a loop with no exit condition
	//Mahmoud
	for (int i = 0; i < StatCount; i++)
	{
		if (StatList[i]->NoExitLoop())
		{
			pOut->PrintMessage("Not Valid: Loop with no Exit Condition Detected");
			Valid = false;
			return;
		}

	}

	pOut->PrintMessage("Flow Chart is Valid");
}

