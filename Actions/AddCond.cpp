#include "AddCond.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddCond::AddCond(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void AddCond::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	pOut->PrintMessage("Conditional Statement: Click to add the statement");

	pIn->GetPointClicked(Position);

	//Checking if the assignment will go out of bounds

	while (Position.x - UI.COND_WDTH / 2 < 0 || Position.x + UI.COND_WDTH / 2 > UI.width || Position.y < UI.TlBrWdth || (Position.y + UI.COND_HI) >(UI.height - UI.StBrWdth))
	{
		pOut->PrintMessage("Statement out of bounds: Click again to add the statement");
		pIn->GetPointClicked(Position);
	}

	//Reading LHS and RHS and Operator from the user
	int Type;
	string COperator;
	bool InValid = true; //To check for the validity of the operator
	pOut->PrintMessage("Enter LHS (a variable): ");
	LHS = pIn->GetVariableName(pOut);

	pOut->PrintMessage("Enter Operator: ");
	COperator = pIn->GetString(pOut);
	//Looping until the user enters a supported operator
	while (InValid)
	{
		if (COperator == "==")
		{
			InValid = false;
		}
		else if (COperator == "!=")
		{
			InValid = false;
		}
		else if (COperator == "<")
		{
			InValid = false;
		}
		else if (COperator == ">")
		{
			InValid = false;
		}
		else if (COperator == ">=")
		{
			InValid = false;
		}
		else if (COperator == "<=")
		{
			InValid = false;
		}
		else
		{
			pOut->PrintMessage("Invalid Operator, please enter a valid operator: ");
			COperator = pIn->GetString(pOut);
		}

	}

	COp = COperator;
	//Reading RHS from the user
	pOut->PrintMessage("Enter type of RHS (1-variable/2-value): ");
	Type = int(pIn->GetValue(pOut));
	switch (Type)
	{
	case 1:
		RHSType = Variable;
		pOut->PrintMessage("Enter RHS (a variable): ");
		RHSVariable = pIn->GetVariableName(pOut);
		break;
	default:
		RHSType = Value;
		pOut->PrintMessage("Enter RHS (a value): ");
		RHSValue = pIn->GetValue(pOut);
		break;
	}

	//Reading comment from the user
	pOut->PrintMessage("Enter comment on the statement: ");
	Com = pIn->GetString(pOut);
	pOut->ClearStatusBar();

}

void AddCond::Execute()
{
	ReadActionParameters();


	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x;
	Corner.y = Position.y;

	Cond *pCond = new Cond(Corner, COp, RHSType, LHS, RHSValue, RHSVariable, Com);

	pManager->AddStatement(pCond);
}

