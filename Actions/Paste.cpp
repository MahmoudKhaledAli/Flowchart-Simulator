#include "Paste.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Paste::Paste(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void Paste::ReadActionParameters()
{
	pManager->GetOutput()->ClearStatusBar();
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	pOut->PrintMessage("Paste : Click To Choose The Position of Pasting ");

	pIn->GetPointClicked(Position);

	while (Position.x - UI.ASSGN_WDTH / 2 < 0 || Position.x + UI.ASSGN_WDTH / 2 > UI.width || Position.y < UI.TlBrWdth || (Position.y + UI.ASSGN_HI) >(UI.height - UI.StBrWdth))
	{
		pOut->PrintMessage("Statement out of bounds: Click again to add the statement");
		pIn->GetPointClicked(Position);
	}
}

void Paste::Execute()
{	
	ReadActionParameters();
	int countofselected=pManager->GetPasteCount();
	if(countofselected==1||pManager->GetPasteStat()!=NULL)
	{ 
		Statement*Stat;//pointer to get the pasted statement in it
		Stat=pManager->GetPasteStat();
		Statement*NewStat=Stat->GetCopied();
		NewStat->SetPoint(Position);
		pManager->AddStatement(NewStat);//adding the statement in the stat list to be considered while drawing
	}
	else if(countofselected>1)
	{	
		Statement *LeastYStat= pManager->GetLeastY();
		Point LeastY= LeastYStat->GetPoint();//reference point

		pManager->RelativePasteStatement(LeastY, Position, countofselected);

//		pManager->RelativePasteConnector(LeastY, Position);

	}
}