#include "VarAssign.h"
#include "Cond.h"
#include <sstream>

using namespace std;

VarAssign::VarAssign(Point Lcorner, string LeftHS, string RightHS, string Comment)
{
	SetAll(Lcorner, LeftHS, RightHS, Comment);
}

void VarAssign::SetAll(Point Lcorner, string LeftHS, string RightHS, string Comment)
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

void VarAssign::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}

void VarAssign::setRHS(const string &R)
{
	RHS = R;
	UpdateStatementText();
}


void VarAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}


//This function should be called when LHS or RHS changes
void VarAssign::UpdateStatementText()
{
	if (LHS == "")	//No left handside ==>statement have no valid text yet
		Text = "    = ";
	else
	{
		//Build the statement text: Left handside then equals then right handside
		ostringstream T;
		T << LHS << " = " << RHS;
		Text = T.str();
	}
}

bool VarAssign::Simulate(Output* pOut, Input* pIn, bool &Val, unordered_map<string, double> &Variables, ostringstream &Output, ifstream &Input, int Choice) const
{
	//Checking for validity
	if (LHS == "")
	{
		Val = false;
		pOut->PrintMessage("LHS is Invalid");
		return true;
	}
	if (RHS == "")
	{
		Val = false;
		pOut->PrintMessage("RHS is invalid");
		return true;
	}
	if (Variables.count(RHS) == 0)
	{
		Val = false;
		pOut->PrintMessage("Variable is being used in RHS without being declared");
		return true;
	}
	//Assigns the value of the variable on RHS to the variable on the LHS
	Variables[LHS] = Variables[RHS];
	return true;
}

void VarAssign::Move(int XShift, int YShift)
{
	LeftCorner.x += XShift;
	LeftCorner.y += YShift;
	Inlet.x += XShift;
	Inlet.y += YShift;
	Outlet.x += XShift;
	Outlet.y += YShift;
}

bool VarAssign::OutOfBounds(Point Pt)
{
	return (Pt.x - UI.ASSGN_WDTH / 2 < 0 || Pt.x + UI.ASSGN_WDTH / 2 > UI.width || Pt.y < UI.TlBrWdth || (Pt.y + UI.ASSGN_HI) >(UI.height - UI.StBrWdth));
}

bool VarAssign::InRange(Point Pt) const
{
	return(Pt.x > LeftCorner.x && Pt.x<LeftCorner.x + UI.ASSGN_WDTH && Pt.y>LeftCorner.y && Pt.y < LeftCorner.y + UI.ASSGN_HI);
}

Statement* VarAssign::GetNextStatement(bool T) const
{
	return(pConn->getDstStat());
}

Statement* VarAssign::GenerateCode(ostringstream &CodeFile, int &Indent)
{
	for (int i = 0; i < Indent; i++)
		CodeFile << '\t';
	CodeFile << Text << ';';
	if (Comment != "")
		CodeFile << '\t' << "//" << Comment;
	CodeFile << endl;
	return(GetNextStatement(true));
}

string VarAssign::GetLHS() const
{
	return LHS;
}

Connector* VarAssign::GetConn() const
{
	return pConn;
}

Point VarAssign::GetInlet() const
{
	return Inlet;
}

Point VarAssign::GetOutlet() const
{
	return Outlet;
}

bool VarAssign::IsConnected(Connector* const * ConnList, int ConnCount) const
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

void VarAssign::Edit(Output* pOut, Input* pIn)
{
	//Reading LHS and RHS from the user
	pOut->PrintMessage("Editing Variable Assignment Statement, Enter LHS (a variable): ");
	string VariableName = pIn->GetVariableName(pOut);
	pOut->PrintMessage("Enter RHS (a variable): ");
	string VariableName2 = pIn->GetVariableName(pOut);
	setRHS(VariableName2);
	setLHS(VariableName);
}

void VarAssign::DeclareVariable(ostringstream &Code, unordered_map<string, double> &Variables) const
{
	if (Variables.count(LHS) == 0)
	{
		Variables[LHS] = 0;
		Code << "\tdouble " << LHS << ';' << endl;
	}
}

void VarAssign::SetConn(Connector* pConn)
{
	this->pConn = pConn;
}

int VarAssign::GetNoOfConn(Connector* const * ConnList, int ConnCount) const
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

void VarAssign::Save(ofstream &file)
{
	file << "VARASS   " << ID << "   " << LeftCorner.x << "   " << LeftCorner.y << "   " << LHS << "   " << RHS << "   " << '"' << Comment << '"' << endl;
}

void VarAssign::Load(ifstream&file)
{
	string comment;
	file >> LeftCorner.x >> LeftCorner.y >> LHS >> RHS;
	getline(file, comment);
	comment = comment.substr(5, comment.find_last_of('"') - 5);
	SetAll(LeftCorner, LHS, RHS, comment);
}

Statement*VarAssign::GetCopied()
{
	VarAssign*ptr=new VarAssign(LeftCorner,LHS,RHS,Comment);
	return ptr;
}

void VarAssign::SetPoint(Point position)
{
	LeftCorner.x=position.x;
	LeftCorner.y=position.y;

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

Point VarAssign::GetPoint()
{
	return LeftCorner;
}