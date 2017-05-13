#include "AddEnd.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddEnd::AddEnd(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void AddEnd::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	pOut->PrintMessage("End Statement: Click to add the statement");
	pIn->GetPointClicked(Position);
	//Checking that the statement is not out of bounds
	while (Position.x - UI.ASSGN_WDTH / 2 < 0 || Position.x + UI.ASSGN_WDTH / 2>UI.width || Position.y < UI.TlBrWdth || (Position.y + UI.ASSGN_HI) >(UI.height - UI.StBrWdth))
	{
		pOut->PrintMessage("Statement out of bounds: Click again to add the statement");
		pIn->GetPointClicked(Position);
	}
	//Reading comment from the user
	pOut->PrintMessage("Enter comment on the statement: ");
	Com = pIn->GetString(pOut);
	pOut->ClearStatusBar();

}

void AddEnd::Execute()
{
	ReadActionParameters();


	//Calculating centre of the circle
	Point Centre;
	Centre.x = Position.x;
	Centre.y = Position.y + UI.ASSGN_HI / 2;

	End *pAssign = new End(Centre, Com);

	pManager->AddStatement(pAssign);

}

