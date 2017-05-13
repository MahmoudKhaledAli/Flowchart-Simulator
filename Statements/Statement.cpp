#include "Statement.h"
#include "Cond.h"

Statement::Statement()	
{ 
	Text = "";
	Selected = false;	
	Comment = "";
//	Looped = false;
	Generating = false;
}

void Statement::SetSelected(bool s)
{	Selected = s; }

bool Statement::IsSelected() const
{	return Selected; }

//bool Statement::Has2Connectors(ApplicationManager* pManager)
//{
//	Connector * const * ConnList = pManager->GetConList();
//	int ConnCount = pManager->GetConnCount();
//	int Conn = 0;
//	for (int i = 0; i < ConnCount; i++)
//	{
//		if (ConnList[i]->getDstStat() == this)
//			Conn++;
//	}
//	return(Conn>1);
//}

//bool Statement::InLoop(ApplicationManager* pManager, int * IDs)
//{
//	Connector * const * ConnList = pManager->GetConList();
//	int ConnCount = pManager->GetConnCount();
//	int StatCount = pManager->GetStatCount();
//	Statement* pStat = NULL;
//	Statement* pStatC;
//	if (Has2Connectors(pManager))
//	{
//		for (int i = 0; i < ConnCount; i++)
//		{
//			if (this == ConnList[i]->getDstStat())
//			{
//				pStat = ConnList[i]->getSrcStat();
//				for (int j = 0; j < StatCount; j++)
//				{
//					if (pStat->GetID() == IDs[i])
//					{
//						pStat = NULL;
//						break;
//					}
//				}
//			}
//		}
//	}
//	return(pStat != NULL);
//}

bool Statement::NoExitLoop()
{
	Statement* pStat = this;
	while (pStat)
	{
		if (dynamic_cast<Cond*>(pStat))
			return false;
		if (pStat->GetConn())
		{
			pStat = pStat->GetConn()->getDstStat();
			if (pStat)
			{
				if (pStat == this)
					return true;
			}
		}
		else
			pStat = NULL;
	}
	return false;
}

Point Statement::GetInlet() const
{
	return Point();
}

Point Statement::GetOutlet() const
{
	return Point();
}

void Statement::SetConn(Connector* pConn)
{

}

void Statement::SetID(int Id)
{
	ID = Id;
}

int Statement::GetID() const
{
	return ID;
}

void Statement::SetCom(const string &Com)
{
	Comment = Com;
}

string Statement::GetCom() const
{
	return Comment;
}

void Statement::DeclareVariable(ostringstream &Code, unordered_map<string, double> &Variables) const
{

}

string Statement::GetLHS() const
{
	return "";
}

Connector* Statement::GetConn() const
{
	return NULL;
}

string Statement::GetText() const
{
	return Text;
}