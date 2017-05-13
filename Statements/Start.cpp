#include "Start.h"
#include <sstream>

using namespace std;

Start::Start(Point C, string Comment)
{
	SetAll(C, Comment);
}

void Start::SetAll(Point C, string Comment)
{
	this->Comment = Comment;


	Center = C;

	pConn = NULL;	//No connectors yet

	//Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	//Inlet.y = LeftCorner.y;

	Outlet.x = Center.x;
	Outlet.y = Center.y + UI.ASSGN_HI / 2;
}


void Start::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawStart(Center, UI.ASSGN_WDTH, UI.ASSGN_HI, Selected);

}


//This function should be called when LHS or RHS changes
void Start::UpdateStatementText()
{
}

void Start::Move(int XShift, int YShift)
{
	Center.x += XShift;
	Center.y += YShift;
	Outlet.x += XShift;
	Outlet.y += YShift;
}

bool Start::OutOfBounds(Point Pt)
{
	return (Pt.x - UI.ASSGN_WDTH / 2 < 0 || Pt.x + UI.ASSGN_WDTH / 2 > UI.width || Pt.y - UI.ASSGN_HI / 2 < UI.TlBrWdth || (Pt.y + UI.ASSGN_HI / 2) > (UI.height - UI.StBrWdth));
}

bool Start::InRange(Point Pt) const
{
	return(Pt.x > Center.x - UI.ASSGN_WDTH / 2 && Pt.x < Center.x + UI.ASSGN_WDTH / 2 && Pt.y > Center.y - UI.ASSGN_HI / 2 && Pt.y < Center.y + UI.ASSGN_HI / 2);
}

Statement* Start::GetNextStatement(bool T) const
{
	return(pConn->getDstStat());
}

Point Start::GetOutlet() const
{
	return Outlet;
}

void Start::SetConn(Connector* pConnector)
{
	pConn = pConnector;
}

Statement* Start::GenerateCode(ostringstream &CodeFile, int &Indent)
{
	//Start statement does not generate any code
	return GetNextStatement(true);
}

Connector* Start::GetConn() const
{
	return pConn;
}

bool Start::IsConnected(Connector * const * ConnList, int ConnCount) const
{
	return (pConn != NULL);
}

bool Start::Simulate(Output*, Input*, bool &Val, unordered_map<string, double> &Variables, ostringstream &Output, ifstream &InputFile, int Choice) const
{
	return true;
}

int Start::GetNoOfConn(Connector* const * ConnList, int ConnCount) const
{
	if (pConn) 
		return 1; 
	return 0;
}

void Start::Edit(Output*, Input*)
{

}

void Start::Save(ofstream &file)
{
	file << "START   " << ID << "   " << Center.x << "   " << Center.y <<  "   " << '"' << Comment << '"' << endl;
}

void Start::Load(ifstream&file)
{
	file >> Center.x >> Center.y;
	string comment;
	getline(file, comment);
	comment = comment.substr(5, comment.find_last_of('"') - 5);
	SetAll(Center, comment);
}

Statement* Start::GetCopied()
{
	Start*ptr=new Start(Center,Comment);
	return ptr;
}

void Start::SetPoint(Point position)
{
	Center.x=position.x;
	Center.y=position.y;

	
	Outlet.x = Center.x;
	Outlet.y = Center.y + UI.ASSGN_HI / 2;
}

Point Start::GetPoint()
{
	return Center;
}