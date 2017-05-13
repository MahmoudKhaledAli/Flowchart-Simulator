#include "Write.h"
#include "Cond.h"
#include <sstream>

using namespace std;

Write::Write(bool Message, Point Lcorner, string T, string Comment)
{
	SetAll(Message, Lcorner, T, Comment);
}

void Write::SetAll(bool Message, Point Lcorner, string T, string Comment)
{
	Target = T;
	this->Comment = Comment;
	this->Message = Message;

	UpdateStatementText();

	LeftCorner = Lcorner;

	pConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

void Write::setTarget(const string &L)
{
	Target = L;
	UpdateStatementText();
}

void Write::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawWrite(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}


//This function should be called when LHS or RHS changes
void Write::UpdateStatementText()
{
	if (Target == "" || Message)	//No left handside ==>statement have no valid text yet
		Text = "Write";
	else if (!Message)
	{
		//Build the statement text: Left handside then equals then right handside
		ostringstream T;
		T << "Write " << Target;
		Text = T.str();
	}
}

bool Write::Simulate(Output* pOut, Input* pIn, bool &Val, unordered_map<string, double> &Variables, ostringstream &Output, ifstream &InputFile, int Choice) const
{
	//Checks if the write is a message or a variable
	if (Message)
	{
		ostringstream M;
		M << Target;
		Output << M.str();
		return true;
	}
	//checks for validity of target variable
	if (Variables.count(Target) == 0)
	{
		Val = false;
		pOut->PrintMessage("Variable is being used in Write Target without being declared");
		return true;
	}
	else if (Target == "")
	{
		Val = false;
		pOut->PrintMessage("Write Target is Invalid");
		return true;
	}
	ostringstream M;
	M << Target << " = " << Variables[Target];
	Output << M.str();
	return true;
}

void Write::Move(int XShift, int YShift)
{
	LeftCorner.x += XShift;
	LeftCorner.y += YShift;
	Inlet.x += XShift;
	Inlet.y += YShift;
	Outlet.x += XShift;
	Outlet.y += YShift;
}

bool Write::OutOfBounds(Point Pt)
{
	return (Pt.x - UI.ASSGN_WDTH / 2 - 10 < 0 || Pt.x + UI.ASSGN_WDTH / 2 + 10 > UI.width || Pt.y < UI.TlBrWdth || (Pt.y + UI.ASSGN_HI) >(UI.height - UI.StBrWdth));
}

bool Write::InRange(Point Pt) const
{

	return(Pt.y > LeftCorner.y && Pt.y < LeftCorner.y + UI.ASSGN_HI && (Pt.y>(-UI.ASSGN_HI / 10)*(Pt.x - LeftCorner.x + 10) + LeftCorner.y + UI.ASSGN_HI) && (Pt.y < (-UI.ASSGN_HI / 10)*(Pt.x - LeftCorner.x - UI.ASSGN_WDTH + 10) + LeftCorner.y + UI.ASSGN_HI));
}

Statement* Write::GetNextStatement(bool T) const
{
	return(pConn->getDstStat());
}

Statement* Write::GenerateCode(ostringstream &CodeFile, int &Indent)
{
	//Generating the code for write statement
	//Checking if the write is a message then we cout a string containing he message
	//if it's a variable then we just cout the variable
	for (int i = 0; i < Indent; i++)
		CodeFile << '\t';
	CodeFile << "cout << ";
	if (Message)
		CodeFile << '"';
	CodeFile << Target;
	if (Message)
		CodeFile << '"';
	CodeFile << ';';
	if (Comment != "")
		CodeFile << '\t' << "//" << Comment;
	CodeFile << endl;
	return(GetNextStatement(true));
}

Connector *Write::GetConn() const
{
	return pConn;
}

Point Write::GetInlet() const
{
	return Inlet;
}

Point Write::GetOutlet() const
{
	return Outlet;
}

void Write::SetConn(Connector* pConn)
{
	this->pConn = pConn;
}

bool Write::IsConnected(Connector* const * ConnList, int ConnCount) const
{
	bool ConnectedIn = false;
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i]->getDstStat() == this)
		{
			ConnectedIn = true;
			break;
		}
	}
	return(ConnectedIn && pConn);
}

void Write::Edit(Output* pOut, Input* pIn)
{
	pOut->PrintMessage("Editing Write Statement, Is the target a variable or a message (1-Var 2-Message): ");
	int Choice = int(pIn->GetValue(pOut));
	if (Choice == 1)
	{
		pOut->PrintMessage("Enter Target Variable:");
		Target = pIn->GetString(pOut);
		Message = false;
		setTarget(Target);
	}
	else
	{
		pOut->PrintMessage("Enter Message:");
		Target = pIn->GetString(pOut);
		Message = true;
		setTarget(Target);
	}
}

int Write::GetNoOfConn(Connector* const * ConnList, int ConnCount) const
{
	int C;
	if (pConn)
		C = 1;
	else
		C = 0;
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i]->getDstStat() == this)
			C++;
	}
	return C;
}

void Write::Save(ofstream &file)
{

	file << "WRITE   " << ID << "   " << LeftCorner.x << "   " << LeftCorner.y << "   " << Target << "   " << Message << "    " << '"' << Comment << '"' << endl;
}

void Write::Load(ifstream &file)
{
	string comment;
	file >> LeftCorner.x >> LeftCorner.y >> Target >> Message;
	getline(file, comment);
	comment = comment.substr(5, comment.find_last_of('"') - 5);
	SetAll(Message, LeftCorner, Target, comment);
}

Statement*Write::GetCopied()
{
	Write*ptr=new Write(Message,LeftCorner,Target,Comment);
	return ptr;
}

void Write::SetPoint(Point position)
{
	LeftCorner.x=position.x;
	LeftCorner.y=position.y;

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

Point Write::GetPoint()
{
	return LeftCorner;
}