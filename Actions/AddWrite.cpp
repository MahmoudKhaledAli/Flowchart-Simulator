#include "AddWrite.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddWrite::AddWrite(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void AddWrite::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	pOut->PrintMessage("Write Statement: Click to add the statement");
	pIn->GetPointClicked(Position);
	//Checking if out of bounds
	while (Position.x - UI.ASSGN_WDTH / 2 - 10 < 0 || Position.x + UI.ASSGN_WDTH / 2 + 10 > UI.width || Position.y < UI.TlBrWdth || (Position.y + UI.ASSGN_HI) >(UI.height - UI.StBrWdth))
	{
		pOut->PrintMessage("Statement out of bounds: Click again to add the statement");
		pIn->GetPointClicked(Position);
	}


	//Reading target type from user (Variable or a message)
	pOut->PrintMessage("Is the target a variable or a message (1-Var 2-Message): ");
	int Choice = int(pIn->GetValue(pOut));
	if (Choice == 1)
	{
		pOut->PrintMessage("Enter Target Variable: ");
		VariableName = pIn->GetString(pOut);
		Message = false;
	}
	else
	{
		pOut->PrintMessage("Enter Message: ");
		VariableName = pIn->GetString(pOut);
		Message = true;
	}
	pOut->PrintMessage("Enter comment on the statement: ");
	Com = pIn->GetString(pOut);
	pOut->ClearStatusBar();

}

void AddWrite::Execute()
{
	ReadActionParameters();


	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;

	Write *pAssign = new Write(Message, Corner, VariableName, Com);

	pManager->AddStatement(pAssign);

}

