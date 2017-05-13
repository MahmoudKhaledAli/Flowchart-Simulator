#include "SmplAssign.h"
#include "Cond.h"
#include <sstream>

using namespace std;

SmplAssign::SmplAssign(Point Lcorner, string LeftHS, double RightHS, string Comment)
{
	SetAll(Lcorner, LeftHS, RightHS, Comment);
}

void SmplAssign::SetAll(Point Lcorner, string LeftHS, double RightHS, string Comment)
{
	LHS = LeftHS;
	RHS = RightHS;
	this->Comment = Comment;

	UpdateStatementText();

	LeftCorner = Lcorner;

	pConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

void SmplAssign::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}

void SmplAssign::setRHS(double R)
{
	RHS = R;
	UpdateStatementText();
}


void SmplAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
	
}


//This function should be called when LHS or RHS changes
void SmplAssign::UpdateStatementText()
{
	if(LHS=="")	//No left handside ==>statement have no valid text yet
		Text = "    = ";
	else
	{
		//Build the statement text: Left handside then equals then right handside
		ostringstream T;
		T<<LHS<<" = "<<RHS;	
		Text = T.str();	 
	}
}

bool SmplAssign::Simulate(Output* pOut, Input* pIn, bool& Val, unordered_map<string, double> &Variables, ostringstream &Output, ifstream &Input, int Choice) const
{
	//Checking for validity of LHS
	if (LHS == "")
	{
		Val = false;
		pOut->PrintMessage("LHS is Invalid");
		return true;
	}
	//Assigning the value to the variable
	Variables[LHS] = RHS;
	return true;
}

void SmplAssign::Move(int XShift, int YShift)
{
	LeftCorner.x += XShift;
	LeftCorner.y += YShift;
	Inlet.x += XShift;
	Inlet.y += YShift;
	Outlet.x += XShift;
	Outlet.y += YShift;
}

bool SmplAssign::OutOfBounds(Point Pt)
{
	return (Pt.x - UI.ASSGN_WDTH / 2 < 0 || Pt.x + UI.ASSGN_WDTH / 2 > UI.width || Pt.y < UI.TlBrWdth || (Pt.y + UI.ASSGN_HI) >(UI.height - UI.StBrWdth));
}

bool SmplAssign::InRange(Point Pt) const
{
	return(Pt.x > LeftCorner.x && Pt.x<LeftCorner.x + UI.ASSGN_WDTH && Pt.y>LeftCorner.y && Pt.y < LeftCorner.y + UI.ASSGN_HI);
}

Statement* SmplAssign::GetNextStatement(bool T) const
{
	return(pConn->getDstStat());
}


Point SmplAssign::GetInlet() const
{
	return Inlet;
}

Point SmplAssign::GetOutlet() const
{
	return Outlet;
}

void SmplAssign::SetConn(Connector* pConnector)
{
	pConn = pConnector;
}

Statement* SmplAssign::GenerateCode(ostringstream &CodeFile, int &Indent)
{
	//Equivalent code is the text of the assignment
	for (int i = 0; i < Indent; i++)
		CodeFile << '\t';
	CodeFile << Text << ';';
	if (Comment != "")
		CodeFile << '\t' << "//" << Comment;
	CodeFile << endl;
	return GetNextStatement(true);
}

string SmplAssign::GetLHS() const
{
	return LHS;
}

Connector* SmplAssign::GetConn() const
{
	return pConn;
}

bool SmplAssign::IsConnected(Connector * const * ConnList, int ConnCount) const
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

void SmplAssign::Edit(Output* pOut, Input* pIn)
{
	//Reading LHS and RHS from the user
	pOut->PrintMessage("Editing Simple Assignment Statement, Enter LHS (a variable): ");
	string VariableName = pIn->GetVariableName(pOut);
	pOut->PrintMessage("Enter RHS (a value): ");
	double Value = pIn->GetValue(pOut);
	setLHS(VariableName);
	setRHS(Value);
}

void SmplAssign::DeclareVariable(ostringstream &Code, unordered_map<string, double> &Variables) const
{
	if (Variables.count(LHS) == 0)
	{
		Variables[LHS] = 0;
		Code << "\tdouble " << LHS << ';' << endl;
	}
}

int SmplAssign::GetNoOfConn(Connector* const * ConnList,int ConnCount) const
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

void SmplAssign::Save(ofstream &file)
{
	file << "SIMPLEASS   " << ID << "   " << LeftCorner.x << "   " << LeftCorner.y << "   " << LHS << "   " << RHS << "   " << '"' << Comment << '"' << endl;
}

void SmplAssign::Load(ifstream&file)
{
	string comment;
	file >> LeftCorner.x >> LeftCorner.y >> LHS >> RHS;
	getline(file, comment);
	comment = comment.substr(5, comment.find_last_of('"') - 5);
	SetAll(LeftCorner, LHS, RHS, comment);
}

Statement*SmplAssign::GetCopied()
{
	SmplAssign*ptr=new SmplAssign(LeftCorner,LHS,RHS,Comment);
	return ptr;
}

void SmplAssign::SetPoint(Point position)
{
	LeftCorner.x=position.x;
	LeftCorner.y=position.y;
	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

Point SmplAssign::GetPoint()
{
	return LeftCorner;
}