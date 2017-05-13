#include "Move.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Move::Move(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void Move::ReadActionParameters()
{
	pManager->GetOutput()->ClearStatusBar();
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	pOut->PrintMessage("Move : Click To Choose The Position of Move ");

	pIn->GetPointClicked(Position);

	while (Position.x - UI.ASSGN_WDTH / 2 < 0 || Position.x + UI.ASSGN_WDTH / 2 > UI.width || Position.y < UI.TlBrWdth || (Position.y + UI.ASSGN_HI) >(UI.height - UI.StBrWdth))
	{
		pOut->PrintMessage("Statement out of bounds: Click again to add the statement");
		pIn->GetPointClicked(Position);
	}
}

void Move::Execute()
{	
	ReadActionParameters();
	int statcount =pManager->GetStatCount();
	Statement*const*StatList=pManager->GetStatList();
	pManager->RelativeMove(Position);
	pManager->UpdateConnectors();
}

