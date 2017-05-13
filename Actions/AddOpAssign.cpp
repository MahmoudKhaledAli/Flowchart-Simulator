#include "AddOpAssign.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddOpAssign::AddOpAssign(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void AddOpAssign::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	pOut->PrintMessage("Operator Assignment Statement: Click to add the statement");

	pIn->GetPointClicked(Position);

	while (Position.x - UI.ASSGN_WDTH / 2 < 0 || Position.x + UI.ASSGN_WDTH / 2 > UI.width || Position.y < UI.TlBrWdth || (Position.y + UI.ASSGN_HI) >(UI.height - UI.StBrWdth))
	{
		pOut->PrintMessage("Statement out of bounds: Click again to add the statement");
		pIn->GetPointClicked(Position);
	}

	//Reading LHS and RHS and operator from the user
	int Type;
	string Operation;
	bool InValid = true;
	pOut->PrintMessage("Enter LHS (a variable): ");
	LHS = pIn->GetVariableName(pOut);
	//Getting the type of the first operand from the user
	pOut->PrintMessage("Enter type of first operand (1-variable/2-value): ");
	Type = int(pIn->GetValue(pOut));
	switch (Type)
	{
		//Assigning the operand to the corresponding data member
	case 1:
		Op1Type = Variable;
		pOut->PrintMessage("Enter First operand (a variable): ");
		Operand1Variable = pIn->GetVariableName(pOut);
		break;
	case 2:
		Op1Type = Value;
		pOut->PrintMessage("Enter First operand (a value): ");
		Operand1Value = pIn->GetValue(pOut);
		break;
	}
	//Getting the operator and making sure it's supported
	pOut->PrintMessage("Enter Operator: ");
	Operation = pIn->GetString(pOut);
	while (InValid)
	{
		if (Operation == "+")
		{
			Op = PLUS;
			InValid = false;
		}
		else if (Operation == "-")
		{
			Op = MINUS;
			InValid = false;
		}
		else if (Operation == "*")
		{
			Op = MULTIPLY;
			InValid = false;
		}
		else if (Operation == "/")
		{
			Op = DIVIDE;
			InValid = false;
		}
		else
		{
			pOut->PrintMessage("Invalid Operator, please enter a valid operator: ");
			Operation = pIn->GetString(pOut);
		}

	}
	//Getting the second operator
	pOut->PrintMessage("Enter type of second operand (1-variable/2-value): ");
	Type = int(pIn->GetValue(pOut));
	switch (Type)
	{
	case 1:
		Op2Type = Variable;
		pOut->PrintMessage("Enter Second operand (a variable): ");
		Operand2Variable = pIn->GetVariableName(pOut);
		break;
	default:
		Op2Type = Value;
		pOut->PrintMessage("Enter Second operand (a value): ");
		Operand2Value = pIn->GetValue(pOut);
		break;
	}

	//Reading comment from the user
	pOut->PrintMessage("Enter comment on the statement: ");
	Com = pIn->GetString(pOut);
	pOut->ClearStatusBar();

}

void AddOpAssign::Execute()
{
	ReadActionParameters();


	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;

	OpAssign *pAssign = new OpAssign(Corner, Op, Op1Type, Op2Type, LHS, Operand1Value, Operand2Value, Operand1Variable, Operand2Variable, Com);

	pManager->AddStatement(pAssign);
}

