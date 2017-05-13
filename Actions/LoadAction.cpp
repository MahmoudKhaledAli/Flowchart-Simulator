#include "..\Statements\SmplAssign.h"
#include "..\Statements\VarAssign.h"
#include "..\Statements\Start.h"
#include "..\Statements\End.h"
#include "..\Statements\Read.h"
#include "..\Statements\Write.h"
#include "..\Statements\Cond.h"
#include "..\Statements\OpAssign.h"
#include "..\Statements\CmplxAssign.h"
#include "..\Statements\Connector.h"


#include "LoadAction.h"




#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

LoadAction::LoadAction(ApplicationManager *pAppManager, string Name) :Action(pAppManager)
{
	file = Name;
}

void LoadAction::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	if (file == "")
	{
		pOut->PrintMessage("Write the name of the file :");
		file = pIn->GetString(pOut);
	}



}

void LoadAction::Execute()
{
	ReadActionParameters();
	pManager->ClearGraph();
	infile.open("Saved Graphs\\" + file + ".txt");
	Load(infile);
	infile.close();
}

void LoadAction::Load(ifstream&file)
{

	Statement*ptr;
	Connector*ptr2;
	int ID;
	string name;
	int sCount;
	int cCount;
	infile >> sCount;
	for (int i = 0; i < sCount; i++)
	{
		infile >> name>>ID;
		if (name == "READ")
		{
			ptr=new Read();
		}
		else if (name == "WRITE")
		{
			ptr=new Write();
		}
		else if(name=="COND")
		{
			ptr=new Cond();
		}
		else if(name=="SNGLOP")
		{
			ptr=new OpAssign();
		}
		else if (name=="START")
		{
			ptr=new Start();
		}
		else if (name=="END")
		{
			ptr=new End();
		}
		else if (name=="SIMPLEASS")
		{
			ptr=new SmplAssign();
		}
		else if (name=="VARASS")
		{
			ptr=new VarAssign();
		}
		else if (name == "CMPASS")
		{
			ptr = new CmplxAssign();
		}


		ptr->Load(infile);
		pManager->AddStatement(ptr);
		ptr->SetID(ID);
		
	}
	infile>>cCount;
	for (int i = 0; i < cCount; i++)
	{	
		Point inletofconn;
		Point outletofconn;
		ptr2=new Connector();
		int id1;
		int id2;
		Statement*src;
		Statement*dst;
		int type;
		infile>>id1>>id2>>type;
		src=pManager->GetSearchedID(id1);
		dst=pManager->GetSearchedID(id2);
		if(type==0)
		{
			if(dynamic_cast<End*>(src)==NULL)
			{
				inletofconn=src->GetOutlet();//except end
				src->SetConn(ptr2);
			}
		}
		else //src is conditional
		{	if(type==1)//yes connector
			{
				Cond*conditional=dynamic_cast<Cond*>(src);
				inletofconn=conditional->GetYesOutlet();
				conditional->SetYesConn(ptr2);
			}
			else//no connector
			{
				Cond*conditional=dynamic_cast<Cond*>(src);
				inletofconn=conditional->GetNoOutlet();
				conditional->SetNoConn(ptr2);
			}
		}
		if(dynamic_cast<Start*>(dst)==NULL)
		{
			outletofconn=dst->GetInlet();//except start
		}
		ptr2->SetAll(src,dst,inletofconn,outletofconn);
		pManager->AddConn(ptr2);
	}

}

