#include "Read.h"
#include "Cond.h"
#include <sstream>

using namespace std;

Read::Read(Point Lcorner, string T, string Comment)
{
	SetAll(Lcorner, T, Comment);
}

void Read::SetAll(Point Lcorner, string T, string Comment)
{
	Target = T;
	this->Comment = Comment;

	UpdateStatementText();

	LeftCorner = Lcorner;

	pConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

void Read::setTarget(const string &L)
{
	Target = L;
	UpdateStatementText();
}

void Read::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawRead(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}


//This function should be called when LHS or RHS changes
void Read::UpdateStatementText()
{
	if (Target == "")	//No left handside ==>statement have no valid text yet
		Text = "Read";
	else
	{
		//Build the statement text: Left handside then equals then right handside
		ostringstream T;
		T << "Read " << Target;
		Text = T.str();
	}
}

bool Read::Simulate(Output* pOut, Input* pIn, bool &Val, unordered_map<string, double> &Variables, ostringstream &Output, ifstream &InputFile, int Choice) const
{
	//Checking for valditiy of target
	if (Target == "")
	{
		Val = false;
		pOut->PrintMessage("Read Target is Invalid");
		return true;
	}
	double Value;
	//Checking if the user chose to read from the screen or from a file
	if (Choice == 2)
	{
		//Getting the value from the screen
		string Message = "Read Statement: Enter Value for Variable " + Target + ": ";
		pOut->PrintMessage(Message);
		Value = pIn->GetValue(pOut);
	}
	else
	{
		//Getting the value from the file
		InputFile >> Value;
	}
	//Assigning the value to the target variable
	Variables[Target] = Value;
	pOut->ClearStatusBar();
	return true;
}

void Read::Move(int XShift, int YShift)
{
	LeftCorner.x += XShift;
	LeftCorner.y += YShift;
	Inlet.x += XShift;
	Inlet.y += YShift;
	Outlet.x += XShift;
	Outlet.y += YShift;
}

bool Read::OutOfBounds(Point Pt)
{
	return (Pt.x - UI.ASSGN_WDTH / 2 - 10 < 0 || Pt.x + UI.ASSGN_WDTH / 2 + 10 > UI.width || Pt.y < UI.TlBrWdth || (Pt.y + UI.ASSGN_HI) >(UI.height - UI.StBrWdth));
}

bool Read::InRange(Point Pt) const
{
	
	return(Pt.y > LeftCorner.y && Pt.y < LeftCorner.y + UI.ASSGN_HI && (Pt.y>(-UI.ASSGN_HI / 10)*(Pt.x - LeftCorner.x + 10) + LeftCorner.y + UI.ASSGN_HI) && (Pt.y < (-UI.ASSGN_HI / 10)*(Pt.x - LeftCorner.x - UI.ASSGN_WDTH + 10) + LeftCorner.y + UI.ASSGN_HI));
}

Statement* Read::GetNextStatement(bool T) const
{
	return(pConn->getDstStat());
}

Point Read::GetInlet() const
{
	return Inlet;
}

Point Read::GetOutlet() const
{
	return Outlet;
}

void Read::SetConn(Connector* pConnector)
{
	pConn = pConnector;
}

Statement* Read::GenerateCode(ostringstream & CodeFile, int &Indent)
{
	//The Read statement is equivalent to cin in C++ Code and returns the next statement
	for (int i = 0; i < Indent; i++)
		CodeFile << '\t';
	CodeFile << "cin >> " << Target << ';';
	if (Comment != "")
		CodeFile << '\t' << "//" << Comment;
	CodeFile << endl;
	return GetNextStatement(true);
}

Connector* Read::GetConn() const
{
	return pConn;
}

bool Read::IsConnected(Connector * const * ConnList, int ConnCount) const
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

void Read::Edit(Output* pOut, Input* pIn)
{ 
	pOut->PrintMessage("Editing Read Statement, Enter Read Target (a variable): ");
	string VariableName = pIn->GetVariableName(pOut);
	setTarget(VariableName);

}

void Read::DeclareVariable(ostringstream &Code, unordered_map<string, double> &Variables) const
{
	if (Variables.count(Target) == 0)
	{
		Variables[Target] = 0;
		Code << "\tdouble " << Target << ';' << endl;
	}
}

int Read::GetNoOfConn(Connector* const * ConnList, int ConnCount) const
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

void Read::Save(ofstream &file)
{
	file << "READ   " << ID << "   " << LeftCorner.x << "   " << LeftCorner.y << "   " << Target << "   " << '"' << Comment << '"' << endl;
}

void Read::Load(ifstream&file)
{
	string comment;
	file >> LeftCorner.x >> LeftCorner.y >> Target;
	getline(file, comment);
	comment = comment.substr(5, comment.find_last_of('"') - 5);
	SetAll(LeftCorner, Target, comment);
}

Statement*Read::GetCopied()
{
	Read*ptr=new Read(LeftCorner,Target,Comment);
	return ptr;
}

void Read::SetPoint(Point position)
{
	LeftCorner.x=position.x;
	LeftCorner.y=position.y;

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

Point Read::GetPoint()
{
	return LeftCorner;
}