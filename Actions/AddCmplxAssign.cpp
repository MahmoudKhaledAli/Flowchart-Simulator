#include "AddCmplxAssign.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddCmplxAssign::AddCmplxAssign(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void AddCmplxAssign::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	pOut->PrintMessage("Complex Assignment Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	//Checking if out of bounds
	while (Position.x - UI.ASSGN_WDTH / 2 < 0 || Position.x + UI.ASSGN_WDTH / 2 > UI.width || Position.y < UI.TlBrWdth || (Position.y + UI.ASSGN_HI) >(UI.height - UI.StBrWdth))
	{
		pOut->PrintMessage("Statement out of bounds: Click again to add the statement");
		pIn->GetPointClicked(Position);
	}

	//Reading LHS and RHS from the user
	pOut->PrintMessage("Enter LHS (a variable): ");
	VariableName = pIn->GetVariableName(pOut);
	pOut->PrintMessage("Enter RHS (arithmetic expression): ");
	Expression = pIn->GetExpression(pOut);
	while (!ValidateExp(Expression))
	{
		pOut->PrintMessage("Invalid Expression, please enter a valid expression: ");
		Expression = pIn->GetString(pOut);
	}
	//Reading comment from the user
	pOut->PrintMessage("Enter comment on the statement: ");
	Com = pIn->GetString(pOut);
	pOut->ClearStatusBar();

}

void AddCmplxAssign::Execute()
{
	ReadActionParameters();


	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;

	CmplxAssign *pAssign = new CmplxAssign(Corner, VariableName, Expression, Com);

	pManager->AddStatement(pAssign);
}

