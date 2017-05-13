#include "CmplxAssign.h"
#include "Cond.h"
#include <sstream>
#include <stack>

using namespace std;
bool IsVarName(string &Name)
{
	string Var;
	unsigned int i = 0;
	//Removing the spaces from the beginning of the string
	while (Name.at(i) == ' ')
		i++;
	Name = Name.substr(i);
	i = 0;
	if (Name.at(0) == '-')
	{
		Var = "-";
		i = 1;
		//Removing the spaces after the beginning of the negative sign
		while (Name.at(i) == ' ')
			i++;
		Name = Name.substr(i);
	}
	i = 0;
	//removing the spaces after the name
	while (Name.at(i) != ' ' && i < Name.size())
	{
		i++;
		if (i == Name.size())
			break;
	}
	Name = Name.substr(0, i);
	Var += Name;
	string Temp = Name;
	Name = Var;
	//A string is a valid variable name if it's first character is a letter
	return(Temp.at(0) > 'a' && Temp.at(0) < 'z' || Temp.at(0) > 'A' && Temp.at(0) < 'Z');
}

double EvaluateExpression(string Exp, const unordered_map<string, double> &Variables, bool &Valid, Output* pOut)
{
	//The function used is a recursive function that check for the last operator that should be evaluated according to operator precedence
	//The function then divied the expression into 2 expressions and is called recursively over each expressions
	//The function ends when the string has no operators, it either returns the value or the value of the variable in that string
	double Exp1;
	double Exp2;
	int LastOp = -1;
	stack<char> Brackets;
	int CountO = 0;
	int CountC = 0;
	int BracketC = 0;
	bool Bracket = false;
	LastOp = -1;
	char LastChar = ' ';
	int i = 0;
	if (Exp == "")
		return 0;
	while (Exp.at(i) == ' ')
		i++;
	Exp = Exp.substr(i);
	i = 0;
	int Size = Exp.size();
	if (Exp.at(Size - 1) == ' ')
		return EvaluateExpression(Exp.substr(0, Size - 1), Variables, Valid, pOut);
	if (Exp.at(0) == '(' && (Exp.at(Size - 1) == ')'))
	{
		Bracket = true;
		for (unsigned int i = 1; i < Exp.size() - 1; i++)
		{
			if (Exp.at(i) == '(')
			{
				BracketC++;
			}
			else if (Exp.at(i) == ')')
			{
				BracketC--;
				if (BracketC == -1)
					Bracket = false;
			}
		}
		if (Bracket)
			return EvaluateExpression(Exp.substr(1, Size - 2), Variables, Valid, pOut);
	}
	LastOp = -1;
	for (int i = 0; i < Size; i++)
	{
		if (Exp.at(i) == '(')
			Brackets.push('(');
		if (Exp.at(i) == ')' && !Brackets.empty())
			Brackets.pop();
		if (Exp.at(i) == '+' && Brackets.empty())
			LastOp = i;
		if (Exp.at(i) == '-' && Brackets.empty() && LastChar != '+' && LastChar != '-' && LastChar != '*' && LastChar != '/')
			LastOp = i;
		if (Exp.at(i) != ' ')
			LastChar = Exp.at(i);
	}
	if (LastOp != -1)
	{
		Exp1 = EvaluateExpression(Exp.substr(0, LastOp), Variables, Valid, pOut);
		Exp2 = EvaluateExpression(Exp.substr(LastOp + 1), Variables, Valid, pOut);
		if (Exp.at(LastOp) == '+')
			return Exp1 + Exp2;
		return Exp1 - Exp2;
	}
	/*LastOp = -1;
	while (!Brackets.empty())
		Brackets.pop();
	for (int i = 0; i < Size; i++)
	{
		if (Exp.at(i) == '(')
			Brackets.push('(');
		if (Exp.at(i) == ')' && !Brackets.empty())
			Brackets.pop();
		if (Exp.at(i) != ' ')
			LastChar = Exp.at(i);
		if (Exp.at(i) == '-' && Brackets.empty() && LastChar != '+' && LastChar != '-' && LastChar != '*' && LastChar != '/')
			LastOp = i;
	}
	if (LastOp != -1)
	{
		Exp1 = EvaluateExpression(Exp.substr(0, LastOp), Variables, Valid, pManager);
		Exp2 = EvaluateExpression(Exp.substr(LastOp + 1), Variables, Valid, pManager);
		return Exp1 - Exp2;
	}*/
	LastOp = -1;
	while (!Brackets.empty())
		Brackets.pop();
	for (int i = 0; i < Size; i++)
	{
		if (Exp.at(i) == '(')
			Brackets.push('(');
		if (Exp.at(i) == ')' && !Brackets.empty())
			Brackets.pop();
		if (Exp.at(i) == '*' && Brackets.empty())
			LastOp = i;
		if (Exp.at(i) == '/' && Brackets.empty())
			LastOp = i;
	}
	if (LastOp != -1)
	{
		Exp1 = EvaluateExpression(Exp.substr(0, LastOp), Variables, Valid, pOut);
		Exp2 = EvaluateExpression(Exp.substr(LastOp + 1), Variables, Valid, pOut);
		if (Exp.at(LastOp) == '*')
			return Exp1 * Exp2;
		if (Exp2 == 0)
		{
			Valid = false;
			pOut->PrintMessage("Error: Division By Zero");
			return 0;
		}
		return Exp1 / Exp2;
	}
	//LastOp = -1;
	//while (!Brackets.empty())
	//	Brackets.pop();
	//for (int i = 0; i < Size; i++)
	//{
	//	if (Exp.at(i) == '(')
	//		Brackets.push('(');
	//	if (Exp.at(i) == ')' && !Brackets.empty())
	//		Brackets.pop();
	//	if (Exp.at(i) == '/' && Brackets.empty())
	//		LastOp = i;
	//}
	//if (LastOp != -1)
	//{
	//	Exp1 = EvaluateExpression(Exp.substr(0, LastOp), Variables, Valid, pManager);
	//	Exp2 = EvaluateExpression(Exp.substr(LastOp + 1), Variables, Valid, pManager);
	//	return Exp1 / Exp2;
	//}
	if (IsVarName(Exp))
	{
		if (Exp.at(0) == '-')
		{
			if (Variables.count(Exp.substr(1)) == 0)
			{
				Valid = false;
				pOut->PrintMessage("Variable is being used in RHS without being declared");
				return 0;
			}
			return -Variables.find(Exp.substr(1))->second;
		}
		if (Variables.count(Exp) == 0)
		{
			pOut->PrintMessage("Variable is being used in RHS without being declared");
			Valid = false;
			return 0;
		}
		return Variables.find(Exp)->second;
	}
	const char* Expr = Exp.c_str();
	return atof(Expr);
}
bool ValidateExp(string Exp)
{
	//Checking for brackets
	int BracketsO = 0;
	int BracketsC = 0;
	for (unsigned int i = 0; i < Exp.size(); i++)
	{
		if (Exp.at(i) == '(')
			BracketsO++;
		if (Exp.at(i) == ')')
			BracketsC++;
		if (BracketsC > BracketsO)
			return false;
	}
	if (BracketsO != BracketsC)
		return false;
	//bool Operator = false;
	//for (unsigned int i = 0; i < Exp.size(); i++)
	//{
	//	while (Exp.at(i) == ' ' && i < Exp.size() - 1)
	//		i++;
	//	if (Exp.at(i) == '+' || Exp.at(i) == '-' || Exp.at(i) == '*' || Exp.at(i) == '/')
	//		Operator = true;
	//	else if (!(Exp.at(i) == '+' || Exp.at(i) == '-' || Exp.at(i) == '*' || Exp.at(i) == '/') && Operator)
	//		return false;
	//	else
	//		Operator = false;
	//}
	return true;
}

CmplxAssign::CmplxAssign(Point Lcorner, string LeftHS, string RightHS, string Comment)
{
	SetAll(Lcorner, LeftHS, RightHS, Comment);
}

void CmplxAssign::SetAll(Point Lcorner, string LeftHS, string RightHS, string Comment)
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

void CmplxAssign::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}

void CmplxAssign::setRHS(const string &R)
{
	RHS = R;
	UpdateStatementText();
}


void CmplxAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}


//This function should be called when LHS or RHS changes
void CmplxAssign::UpdateStatementText()
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

bool CmplxAssign::Simulate(Output* pOut, Input* pIn, bool &Val, unordered_map<string, double> &Variables, ostringstream &Output, ifstream &Input, int Choice) const
{
	if (LHS == "")
	{
		Val = false;
		pOut->PrintMessage("LHS is Invalid");
		return true;
	}
	//Calling the function to evalute the expression
	double Result = EvaluateExpression(RHS, Variables, Val, pOut);
	//Assigning the value returned to the variable on the LHS
	Variables[LHS] = Result;
	return true;
}

void CmplxAssign::Move(int XShift, int YShift)
{
	LeftCorner.x += XShift;
	LeftCorner.y += YShift;
	Inlet.x += XShift;
	Inlet.y += YShift;
	Outlet.x += XShift;
	Outlet.y += YShift;
}

bool CmplxAssign::OutOfBounds(Point Pt)
{
	return (Pt.x - UI.ASSGN_WDTH / 2 < 0 || Pt.x + UI.ASSGN_WDTH / 2 > UI.width || Pt.y < UI.TlBrWdth || (Pt.y + UI.ASSGN_HI) >(UI.height - UI.StBrWdth));
}

bool CmplxAssign::InRange(Point Pt) const
{
	return(Pt.x > LeftCorner.x && Pt.x<LeftCorner.x + UI.ASSGN_WDTH && Pt.y>LeftCorner.y && Pt.y < LeftCorner.y + UI.ASSGN_HI);
}

Statement* CmplxAssign::GetNextStatement(bool T) const
{
	return(pConn->getDstStat());
}

Statement* CmplxAssign::GenerateCode(ostringstream &CodeFile, int &Indent)
{
	//Generating the code equivalent to the statement
	for (int i = 0; i < Indent; i++)
		CodeFile << '\t';
	CodeFile << Text << ';';
	if (Comment != "")
		CodeFile << '\t' << "//" << Comment;
	CodeFile << endl;
	//Returning the next statement
	return(GetNextStatement(true));
}

string CmplxAssign::GetLHS() const
{
	return LHS;
}

Connector* CmplxAssign::GetConn() const
{
	return pConn;
}

Point CmplxAssign::GetInlet() const
{
	return Inlet;
}

Point CmplxAssign::GetOutlet() const
{
	return Outlet;
}

bool CmplxAssign::IsConnected(Connector * const * ConnList, int ConnCount) const
{
	//Checking if a connector has this statement as a destination statement
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

void CmplxAssign::Edit(Output* pOut, Input* pIn)
{
	//Reading LHS and RHS from the user
	pOut->PrintMessage("Editing Complex Assignment Statement, Enter LHS (a variable): ");
	string VariableName = pIn->GetVariableName(pOut);
	pOut->PrintMessage("Enter RHS (arithmetic expression): ");
	string Expression = pIn->GetExpression(pOut);
	while (!ValidateExp(Expression))
	{
		pOut->PrintMessage("Invalid Expression, please enter a valid expression: ");
		Expression = pIn->GetString(pOut);
	}
	setRHS(Expression);
	setLHS(VariableName);
}

void CmplxAssign::DeclareVariable(ostringstream &Code, unordered_map<string, double> &Variables) const
{
	//If the statement was not declared before
	if (Variables.count(LHS) == 0)
	{
		Variables[LHS] = 0;
		Code << "\tdouble " << LHS << ';' << endl;
	}
}

void CmplxAssign::SetConn(Connector* pConn)
{
	this->pConn = pConn;
}

int CmplxAssign::GetNoOfConn(Connector * const * ConnList,int ConnCount) const
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

void CmplxAssign::Save(ofstream &file)
{
	file << "CMPASS   " << ID << "   " << LeftCorner.x << "   " << LeftCorner.y << "   " << LHS << "   " << '"' << RHS << '"' << "   " << '"' << Comment << '"' << endl;
}

void CmplxAssign::Load(ifstream&file)
{
	string Line;
	file >> LeftCorner.x >> LeftCorner.y >> LHS;
	getline(file, Line);
	Line = Line.substr(Line.find_first_of('"') + 1);
	RHS = Line.substr(0, Line.find_first_of('"'));
	Line = Line.substr(Line.find_first_of('"') + 1);
	Line = Line.substr(Line.find_first_of('"') + 1);
	Comment = Line.substr(0, Line.find_first_of('"'));
	SetAll(LeftCorner, LHS, RHS, Comment);
}

Statement* CmplxAssign::GetCopied()
{
	CmplxAssign*ptr = new CmplxAssign(LeftCorner, LHS, RHS, Comment);
	return ptr;
}

void CmplxAssign::SetPoint(Point position)
{
	LeftCorner.x = position.x;
	LeftCorner.y = position.y;

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

Point CmplxAssign::GetPoint()
{
	return LeftCorner;
}