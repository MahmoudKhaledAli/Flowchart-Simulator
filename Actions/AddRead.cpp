#include "AddRead.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddRead::AddRead(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void AddRead::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	pOut->PrintMessage("Read Statement: Click to add the statement");
	pIn->GetPointClicked(Position);//position : takes position from user 
	//Checking if out of bounds
	while (Position.x - UI.ASSGN_WDTH / 2 - 10 < 0 || Position.x + UI.ASSGN_WDTH / 2 + 10 > UI.width || Position.y < UI.TlBrWdth || (Position.y + UI.ASSGN_HI) >(UI.height - UI.StBrWdth))
	{
		pOut->PrintMessage("Statement out of bounds: Click again to add the statement");
		pIn->GetPointClicked(Position);
	}


	//Reading Target Variable from the user
	pOut->PrintMessage("Enter Read Target (a variable): ");
	VariableName = pIn->GetVariableName(pOut);
	//Reading comment from the user
	pOut->PrintMessage("Enter comment on the statement: ");
	Com = pIn->GetString(pOut);
	pOut->ClearStatusBar();

}

void AddRead::Execute()
{
	ReadActionParameters();


	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;

	Read *pAssign = new Read(Corner, VariableName, Com);

	pManager->AddStatement(pAssign);//finally it puts the new read in the statement list
	
}

