#include "End.h"
#include <sstream>

using namespace std;

End::End(Point C, string Comment)
{
	SetAll(C, Comment);
}

void End::SetAll(Point C, string Comment)
{
	this->Comment = Comment;

	Center = C;

	//	pConn = NULL;	//No connectors yet

	//Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	//Inlet.y = LeftCorner.y;

	Inlet.x = Center.x;
	Inlet.y = Center.y - UI.ASSGN_HI / 2;
}


void End::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawEnd(Center, UI.ASSGN_WDTH, UI.ASSGN_HI, Selected);

}


//This function should be called when LHS or RHS changes
void End::UpdateStatementText()
{
}

void End::Move(int XShift, int YShift)
{
	Center.x += XShift;
	Center.y += YShift;
	Inlet.x += XShift;
	Inlet.y += YShift;
}

bool End::OutOfBounds(Point Pt)
{
	return (Pt.x - UI.ASSGN_WDTH / 2 < 0 || Pt.x + UI.ASSGN_WDTH / 2 > UI.width || Pt.y - UI.ASSGN_HI / 2 < UI.TlBrWdth || (Pt.y + UI.ASSGN_HI / 2) > (UI.height - UI.StBrWdth));
}

bool End::InRange(Point Pt) const
{
	return(Pt.x > Center.x - UI.ASSGN_WDTH / 2 && Pt.x < Center.x + UI.ASSGN_WDTH / 2 && Pt.y > Center.y - UI.ASSGN_HI / 2 && Pt.y < Center.y + UI.ASSGN_HI / 2);
}

Statement* End::GetNextStatement(bool T) const
{
	return NULL; //End is the last statement
}

Point End::GetInlet() const
{
	return Inlet;
}

bool End::IsConnected(Connector * const * ConnList, int ConnCount) const
{
	//End statement doesn't have an outgoing connection
	bool ConnectedIn = false;
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i]->getDstStat() == this)//if this statment equals the destination 
		{
			ConnectedIn = true;
			break;
		}
	}
	return(ConnectedIn);
}

int End::GetNoOfConn(Connector * const * ConnList,int ConnCount) const
{
	int C = 0;
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i]->getDstStat() == this)
			C++;
	}
	return C;
}
Statement* End::GenerateCode(ostringstream &CodeFile, int&Indent)
{
	//The Statement End signals the end of the simulation, so in Code it is equivalent to the return statement
	//It returns a NULL pointer as it is the last statement to be generated
	for (int i = 0; i < Indent; i++)
		CodeFile << '\t';
	CodeFile << "return;";
	if (Comment != "")
		CodeFile << '\t' << "//" << Comment;
	CodeFile << endl;
	return NULL;
}

void End::Edit(Output*, Input*)
{

}

bool End::Simulate(Output*, Input*, bool &Val, unordered_map<string, double> &Variables, ostringstream &Output, ifstream &InputFile, int Choice) const
{
	return true;
}

void End::Save(ofstream &file)
{
	file << "END   " << ID << "   " << Center.x << "   " << Center.y << "   " <<'"' << Comment << '"' << endl;
}

void End::Load(ifstream&file)
{
	file >> Center.x >> Center.y;
	string comment;
	getline(file, comment);
	comment = comment.substr(5, comment.find_last_of('"') - 5);
	SetAll(Center, comment);
}

Statement* End::GetCopied()
{
	End*ptr=new End(Center,Comment);
	return ptr;
}

void End::SetPoint(Point position)
{
	Center.x=position.x;
	Center.y=position.y;

	Inlet.x = Center.x;
	Inlet.y = Center.y - UI.ASSGN_HI / 2;
}

Point End::GetPoint()
{
	return Center;
}