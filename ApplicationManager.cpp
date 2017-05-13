#include "ApplicationManager.h"
#include "Actions\AddSmplAssign.h"
#include "Actions\AddVarAssign.h"
#include "Actions\AddCmplxAssign.h"
#include "Actions\AddOpAssign.h"
#include "Actions\AddCond.h"
#include "Actions\AddRead.h"
#include "Actions\AddStart.h"
#include "Actions\AddEnd.h"
#include "Actions\AddWrite.h"
#include "Actions\AddConnector.h"
#include "Actions\Delete.h"
#include "Actions\Edit.h"
#include "Actions\Select.h"
#include "Actions\Comment.h"
#include "Actions\SaveAction.h"
#include "Actions\LoadAction.h"
#include "Actions\Copy.h"
#include "Actions\Paste.h"
#include "Actions\Cut.h"
#include "Actions\Move.h"
#include "Actions\MultiSelect.h"
#include "Actions\Undo.h"
#include "Actions\Redo.h"
#include "Actions\Validate.h"
#include "Actions\Simulate.h"
#include "Actions\Step.h"
#include "Actions\Generate.h"
#include "GUI\Input.h"
#include "GUI\Output.h"

Point operator+(Point P1,Point P2)
{
	Point NewPoint;
	NewPoint.x=P1.x+P2.x;
	NewPoint.y=P1.y+P2.y;
	return NewPoint;
}

Point operator-(Point P1,Point P2)
{
	Point NewPoint;
	NewPoint.x=P1.x-P2.x;
	NewPoint.y=P1.y-P2.y;
	return NewPoint;
}

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	
	StatCount = 0;
	ConnCount = 0;
	PasteCount = 0;
//	PasteConnCount = 0;
	//StatID = 0;
	UndoCount = 1;
	ActCount = 0;
	TxtCount = 1;
//	CanUndo = false;
	SelectedStat = NULL;
	SelectedConn = NULL;
	PasteStat=NULL;
	ofstream Temp;
	Temp.open("\\Saved Graphs\\temp\\temp0.txt");
	Temp.close();
	//pSelectedStat = NULL;	//no Statement is selected yet
	//Initialized.reserve(200);
	
	//Create an array of Statement pointers and set them to NULL		
	for(int i=0; i<MaxCount; i++)
	{
		StatList[i] = NULL;	
		ConnList[i] = NULL;
	}

}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	
	Action* pAct = NULL;
	int Choice = 0;
	SaveAction Save(this, "\\temp\\temp" + to_string(UndoCount));
	bool SaveB = false;
	
	//According to ActioType, create the corresponding action object
	switch (ActType)
	{
		case ADD_SMPL_ASSIGN:
			pAct = new AddSmplAssign(this);
			SaveB = true;
			break;

		case ADD_OP_ASSIGN:
			pOut->PrintMessage("Select: 1-Single Operator, 2-Complex");
			Choice = int(pIn->GetValue(pOut));
			if (Choice == 1)
				pAct = new AddOpAssign(this);
			else
				pAct = new AddCmplxAssign(this);
			SaveB = true;
			break;

		case ADD_READ:
			pAct = new AddRead(this);
			SaveB = true;
			break;

		case ADD_START:
			pAct = new AddStart(this);
			SaveB = true;
			break;

		case CUT:
			pAct = new Cut(this);
			SaveB = true;
			break;

		case ADD_VAR_ASSIGN:
			pAct = new AddVarAssign(this);
			SaveB = true;
			break;

		case ADD_WRITE:
			pAct = new AddWrite(this);
			SaveB = true;
			break;

		case ADD_END:
			pAct = new AddEnd(this);
			SaveB = true;
			break;

		case ADD_CONDITION:
			pAct = new AddCond(this);
			SaveB = true;
			break;

		case ADD_CONNECTOR:
			pAct = new AddConnector(this);
			SaveB = true;
			break;

		case DEL:
			pAct = new Delete(this);
			SaveB = true;
			break;

		case EDIT:
			pAct = new Edit(this);
			SaveB = true;
			break;

		case MULTI_SELECT:
			pAct = new MultiSelect(this);
			break;

		case SELECT:
			pAct = new Select(this);
			break;

		case COM:
			pAct = new Comment(this);
			SaveB = true;
			break;

		case SAVE:
			pAct = new SaveAction(this);
			break;

		case LOAD:
			pAct = new LoadAction(this);
			SaveB = true;
			break;

		case UNDO:
			pAct = new Undo(this);
			//SaveB = true;
			break;

		case COPY:
			pAct = new Copy(this);
			break;

		case PASTE:
			pAct = new Paste(this);
			SaveB = true;
			break;

		case MOVE:
			pAct = new Move(this);
			SaveB = true;
			break;

		case REDO:
			pAct = new Redo(this);
			break;

		case VALIDATE:
			pAct = new Validate(this);
			break;

		case RUN:
			pAct = new Simulate(this);
			break;

		case STEP:
			pAct = new Step(this);
			break;

		case GENERATE:
			pAct = new Generate(this);
			break;

		case SIM_MODE:
			for (int i = 0; i < StatCount; i++)
			{
				StatList[i]->SetSelected(false);
			}
			for (int i = 0; i < ConnCount; i++)
			{
				ConnList[i]->SetSelected(false);
			}
			SelectedStat = NULL;
			SelectedConn = NULL;
			pOut->ClearStatusBar();
			pOut->CreateSimulationToolBar();
			break;


		case DSN_MODE:
			pOut->CreateDesignToolBar();
			break;

		case EXIT:
			///create Exit Action here
			
			break;
		
		case STATUS:
			return;
	}
	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
	}
	if (SaveB)
	{
		Save.Execute();
		UndoCount++;
		ActCount = UndoCount;
		TxtCount++;
	}
}



//==================================================================================//
//						Statements Management Functions								//
//==================================================================================//
//Add a statement to the list of statements
void ApplicationManager::AddStatement(Statement *pStat)
{
	if (StatCount < MaxCount)
	{
		int StatID = 0;
		StatList[StatCount++] = pStat;
		while (GetSearchedID(++StatID));
		pStat->SetID(StatID);
	}
	
}

////////////////////////////////////////////////////////////////////////////////////
Statement *ApplicationManager::GetStatement(Point P) const
{
	//If this point P(x,y) belongs to a statement return a pointer to it.
	//otherwise, return NULL
	Statement* pStat = NULL;
	for (int i = 0; i < StatCount; i++)
	{
		if (StatList[i]->InRange(P))
			pStat = StatList[i];
	}

	///Add your code here to search for a statement given a point P(x,y)	

	return pStat;
}

void ApplicationManager::RemoveStatement(Statement* pStat)
{
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i]->getDstStat() == pStat || ConnList[i]->getSrcStat() == pStat)//looping on the connector list and checking if this statement is related to the src and dst or not to be removed
		{
			RemoveConnector(ConnList[i]);
			--i;
		}
	}
	for (int i = 0; i < StatCount; i++)
	{
		if (StatList[i] == pStat)
		{
			delete pStat;
			StatList[i] = StatList[--StatCount];
			StatList[StatCount] = NULL;
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////
//Returns the selected statement
Statement * ApplicationManager::GetSelectedStatement() const
{	return SelectedStat;	}

////////////////////////////////////////////////////////////////////////////////////
//Set the statement selected by the user
void ApplicationManager::SetSelectedStatement(Statement *pStat)
{
	SelectedStat = pStat;
}


//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	if (UI.AppMode == SIMULATION);
	else
	{
		pOut->ClearDrawArea();
		pOut->ClearStatusBar();
		if (SelectedStat)
			pOut->PrintMessage(SelectedStat->GetCom());
	}
	//Draw all statements
	for(int i=0; i<StatCount; i++)
		StatList[i]->Draw(pOut);
	
	//Draw all connections
	for(int i=0; i<ConnCount; i++)
		ConnList[i]->Draw(pOut);

}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
Statement * const * ApplicationManager::GetStatList() const
{
	return StatList;
}
Connector * const * ApplicationManager::GetConList() const
{
	return ConnList;
}
int ApplicationManager::GetStatCount() const
{
	return StatCount;
}
int ApplicationManager::GetConnCount() const
{
	return ConnCount;
}
////////////////////////////////////////////////////////////////////////////////////


//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<StatCount; i++)
		delete StatList[i];
	for(int i=0; i<StatCount; i++)
		delete ConnList[i];
	delete pIn;
	delete pOut;
	ClearPasteStat();
	for (int i = 0; i < TxtCount; i++)
	{
		string Name = "Saved Graphs\\temp\\temp" + to_string(i) + ".txt";
		remove(Name.c_str());
	}
	
}

void ApplicationManager::AddConn(Connector* pConn)
{
	if (ConnCount < MaxCount)
		ConnList[ConnCount++] = pConn;
}

Connector* ApplicationManager::GetConnector(Point P) const
{
	Connector* pConn = NULL;
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i]->InRange(P))
			pConn = ConnList[i];
	}
	return pConn;
}

Connector * ApplicationManager::GetSelectedConnector() const
{
	return SelectedConn;
}

void ApplicationManager::SetSelectedConnector(Connector* pConn)
{
	SelectedConn = pConn;
}

void ApplicationManager::RemoveConnector(Connector* pConn)
{
	Statement* pStat = pConn->getSrcStat();
	Cond* pCond;
	if (pCond = dynamic_cast<Cond*>(pStat))//checking if the source statement is conditional or not
	{
		if (pConn == pCond->GetYesConn())
			pCond->SetYesConn(NULL);
		else
			pCond->SetNoConn(NULL);
	}
	else
		pStat->SetConn(NULL);
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i] == pConn)
		{
			delete pConn;
			ConnList[i] = ConnList[--ConnCount];
			ConnList[ConnCount] = NULL;
			break;
		}
	}
}

void ApplicationManager::Save(ofstream & outfile)
{
	outfile << StatCount << endl;
	for (int i = 0; i < StatCount; i++)
	{
		StatList[i]->Save(outfile);// calling save function for each statement
	}
	outfile << ConnCount << endl;
	for (int i = 0; i < ConnCount; i++)
	{
		ConnList[i]->Save(outfile);// calling save of the connector
	}
}


Statement*ApplicationManager::GetSearchedID(int id)
{
	for (int i = 0; i < StatCount; i++)
	{
		if (id == StatList[i]->GetID())
		{
			return StatList[i];
		}
	}
	return NULL;
}

void ApplicationManager::ClearGraph()
{
	//Removing a statement removes its connections so we don't need to remove the connecotrs
	for (int i = 0; i < StatCount; i++)
	{
		RemoveStatement(StatList[i]);
	}
	StatCount = 0;
	ConnCount = 0;
//	StatID = 0;
	SelectedStat = NULL;
	SelectedConn = NULL;
}

int ApplicationManager::GetUndo() const
{
	return UndoCount;
}

void ApplicationManager::DecrementUndo()
{
	UndoCount--;
}

void ApplicationManager::IncrementUndo()
{
	UndoCount++;
}

//void ApplicationManager::SetCanUndo(bool C)
//{
//	CanUndo = C;
//}
//
//bool ApplicationManager::IsUndo() const
//{
//	return CanUndo;
//}

int ApplicationManager::GetActCount() const
{
	return ActCount;
}

//void ApplicationManager::IncrementActCount()
//{
//	ActCount++;
//}
//
//void ApplicationManager::SetActCount(int C)
//{
//	ActCount = C;
//}


Statement * ApplicationManager::GetPasteStat()
{
	return PasteStat;
}

void ApplicationManager::SetPasteStat(Statement * Paste)
{
	if(PasteStat!=NULL)
		delete PasteStat;
	PasteStat=Paste;
}

int ApplicationManager::GetSelectedCount()
{
	int count =0;
	for (int i = 0; i < StatCount; i++)
	{
		if(StatList[i]->IsSelected())
		{
			count++;
		}
	}
	return count;
}

void ApplicationManager::AddPasteStat(Statement * stat)
{
	if (PasteCount < MaxCount)
	{
		PasteList[PasteCount++] = stat;
	}
	
}

Statement ** ApplicationManager::GetPasteList()
{
	return PasteList;
}

void ApplicationManager::SetPasteList()
{
	if(PasteCount != 0)
	{
		for (int i = 0; i < PasteCount; i++)
		{
			delete PasteList[i];
		}
	}
	PasteCount=0;
	for (int i = 0; i < StatCount; i++)
	{
		if(StatList[i]->IsSelected())
		{
			AddPasteStat(StatList[i]->GetCopied());
		}
	}
}

Statement* ApplicationManager::GetLeastY()
{	
	if(PasteCount>0)
	{
		Statement*ptr=PasteList[0];
		for (int i = 0; i < PasteCount; i++)
		{
			if(PasteList[i]->GetPoint().y<ptr->GetPoint().y)
			{
				ptr=PasteList[i];
			}
		}
		return ptr;
	}
	else
	{
		return NULL;
	}
}

void ApplicationManager::SetPasteCount(int n)
{
	PasteCount=n;
}

int ApplicationManager::GetPasteCount()
{
	return PasteCount;
}

//void ApplicationManager::SetPasteConnList()
//{
//	for (int i = 0; i < ConnCount; i++)
//	{
//		if(ConnList[i]->IsSelected())
//		{
//			if(ConnList[i]->getSrcStat()->IsSelected() && ConnList[i]->getDstStat()->IsSelected())
//			{
//				//Connector*  ptr = new Connector(ConnList[i]->getSrcStat(),ConnList[i]->getDstStat(),ConnList[i]->getStartPoint(),ConnList[i]->getEndPoint());
//				//AddPasteConn(ptr);				
//			}
//		}
//	}
//}

//Connector** ApplicationManager::GetPasteConnList()
//{
//	return PasteConnList;      
//}
//
//void ApplicationManager::AddPasteConn(Connector*ptr)
//{
//	PasteConnList[PasteConnCount]=ptr;
//	PasteConnCount++;
//}
//
//void ApplicationManager::SetPasteConnCount(int c)
//{
//	PasteConnCount=c;
//}
//
//int ApplicationManager::GetPasteConnCount()
//{
//	return PasteConnCount;
//}

Statement*ApplicationManager::GetLeastYSelected()
{	
	Statement*ptr=NULL;
	for (int i = 0; i < StatCount; i++)
	{
		if(StatList[i]->IsSelected())
		{
			if(ptr==NULL || StatList[i]->GetPoint().y<ptr->GetPoint().y)
			{
				ptr=StatList[i];
			}
		}
	}
	return ptr;
}

void ApplicationManager::UpdateConnectors()
{
	for (int i = 0; i < ConnCount; i++)
	{
		ConnList[i]->UpdatePoints();
	}
}

void ApplicationManager::RelativeMove(Point Position)
{
	Point LeastY = GetLeastYSelected()->GetPoint();
	Point Diff;
	for (int i = 0; i < StatCount; i++)
	{
		if(StatList[i]->IsSelected())
		{
			Diff =StatList[i]->GetPoint() - LeastY;
			StatList[i]->SetPoint(Diff + Position);
		}
	}
}

void ApplicationManager::RelativePasteStatement(Point LeastY, Point Position, int countofselected)
{
	for (int i = 0; i <countofselected ; i++)
	{	
		Point Diff;
		Diff=PasteList[i]->GetPoint()-LeastY;
		PasteList[i]->SetPoint(Diff+Position);
		AddStatement(PasteList[i]->GetCopied());
	}
}

//void ApplicationManager::RelativePasteConnector(Point LeastY, Point Position)
//{
//	for (int i = 0; i <GetPasteConnCount() ; i++)
//	{	
//		Point Diff1;
//		Point Diff2;
//		Diff1=PasteConnList[i]->getStartPoint()-LeastY;
//		Diff2=PasteConnList[i]->getEndPoint()-LeastY;
//		PasteConnList[i]->setStartPoint(Diff1+Position);
//		PasteConnList[i]->setEndPoint(Diff2+Position);
//		Connector*  ptr = new Connector(PasteConnList[i]->getSrcStat(),PasteConnList[i]->getDstStat(),PasteConnList[i]->getStartPoint(),PasteConnList[i]->getEndPoint());
//		AddConn(ptr);
//	}
//}

void ApplicationManager::ClearPasteStat()
{
	if (PasteCount != 0)
	{
		for (int i = 0; i < PasteCount; i++)
		{
			delete PasteList[i];
		}
	}
}