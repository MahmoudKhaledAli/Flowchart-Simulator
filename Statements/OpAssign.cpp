#include "OpAssign.h"
#include"Cond.h"
#include <sstream>

using namespace std;

OpAssign::OpAssign(Point Lcorner, Operator Op, OperandType O1, OperandType O2, string LeftHS, double Op1, double Op2, string Ops1, string Ops2, string Comment)
{
	SetALL(Lcorner, Op, O1, O2, LeftHS, Op1, Op2, Ops1, Ops2, Comment);
}

void OpAssign::SetALL(Point Lcorner, Operator Op, OperandType O1, OperandType O2, string LeftHS, double Op1, double Op2, string Ops1, string Ops2, string Comment)
{
	LHS = LeftHS;
	this->Comment = Comment;
	Op1Type = O1;
	Op2Type = O2;
	this->Op = Op;
	switch (O1)
	{
	case Variable:
		Operand1Variable = Ops1;
		break;
	case Value:
		Operand1Value = Op1;
		break;
	}
	switch (O2)
	{
	case Variable:
		Operand2Variable = Ops2;
		break;
	case Value:
		Operand2Value = Op2;
		break;
	}

	UpdateStatementText();

	LeftCorner = Lcorner;

	pConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

void OpAssign::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}

void OpAssign::setOperand1Value(double O1)
{
	Op1Type = Value;
	Operand1Value = O1;
}

void OpAssign::setOperand1Variable(const string &O)
{
	Op1Type = Variable;
	Operand1Variable = O;
}

void OpAssign::setOperand2Value(double O2)
{
	Op2Type = Value;
	Operand2Value = O2;
}

void OpAssign::setOperand2Variable(const string &O)
{
	Op2Type = Variable;
	Operand2Variable = O;
}

void OpAssign::setOperator(Operator Op)
{
	this->Op = Op;
}


void OpAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}


//This function should be called when LHS or RHS changes
void OpAssign::UpdateStatementText()
{
	if (LHS == "")	//No left handside ==>statement have no valid text yet
		Text = "    = ";
	else
	{
		//Build the statement text: Left handside then equals then right handside
		ostringstream T;
		T << LHS << " = ";
		switch (Op1Type)
		{
		case Variable:
			T << Operand1Variable << " ";
			break;
		case Value:
			T << Operand1Value << " ";
			break;
		}
		switch (Op)
		{
		case PLUS:
			T << "+ ";
			break;
		case MINUS:
			T << "- ";
			break;
		case MULTIPLY:
			T << "* ";
			break;
		case DIVIDE:
			T << "/ ";
			break;
		}
		switch (Op2Type)
		{
		case Variable:
			T << Operand2Variable;
			break;
		case Value:
			T << Operand2Value;
			break;
		}

		Text = T.str();
	}
}

bool OpAssign::Simulate(Output* pOut, Input* pIn, bool &Val, unordered_map<string, double> &Variables, ostringstream &Output, ifstream &InputFile, int Choice) const
{
	//Checking for validity of LHS and operands
	if (LHS == "")
	{
		Val = false;
		pOut->PrintMessage("LHS is Invalid");
		return true;
	}
	double Value1;
	double Value2;
	double Result;
	switch (Op1Type)
	{
	case Variable:
		if (Variables.count(Operand1Variable) == 0)
		{
			Val = false;
			pOut->PrintMessage("Variable is being used in RHS without being declared");
			return true;
		}
		if (Operand1Variable == "")
		{
			Val = false;
			pOut->PrintMessage("Operand is invalid");
			return true;
		}
		Value1 = Variables[Operand1Variable];
		break;
	case Value:
		Value1 = Operand1Value;
		break;
	}


	switch (Op2Type)
	{
	case Variable:
		if (Variables.count(Operand2Variable) == 0)
		{
			Val = false;
			pOut->PrintMessage("Variable is being used in RHS without being declared");
			return true;
		}
		if (Operand2Variable == "")
		{
			Val = false;
			pOut->PrintMessage("Operand is invalid");
			return true;
		}
		Value2 = Variables[Operand2Variable];
		break;
	case Value:
		Value2 = Operand2Value;
		break;
	}

	switch (Op)
	{
	case PLUS:
		Result = Value1 + Value2;
		break;
	case MINUS:
		Result = Value1 - Value2;
		break;
	case DIVIDE:
		if (Value2 == 0)
		{
			Val = false;
			pOut->PrintMessage("Error: Division by Zero");
			return true;
		}
		Result = Value1 / Value2;
		break;
	case MULTIPLY:
		Result = Value1*Value2;
		break;
	}
	//Assigning the result of the operation to the variable on the LHS
	Variables[LHS] = Result;
	return true;
}

void OpAssign::Move(int XShift, int YShift)
{
	LeftCorner.x += XShift;
	LeftCorner.y += YShift;
	Inlet.x += XShift;
	Inlet.y += YShift;
	Outlet.x += XShift;
	Outlet.y += YShift;
}

bool OpAssign::OutOfBounds(Point Pt)
{
	return (Pt.x - UI.ASSGN_WDTH / 2 < 0 || Pt.x + UI.ASSGN_WDTH / 2 > UI.width || Pt.y < UI.TlBrWdth || (Pt.y + UI.ASSGN_HI) >(UI.height - UI.StBrWdth));
}

bool OpAssign::InRange(Point Pt) const
{
	return(Pt.x > LeftCorner.x && Pt.x<LeftCorner.x + UI.ASSGN_WDTH && Pt.y>LeftCorner.y && Pt.y < LeftCorner.y + UI.ASSGN_HI);
}

Statement* OpAssign::GetNextStatement(bool T) const
{
	return(pConn->getDstStat());
}

Point OpAssign::GetInlet() const
{
	return Inlet;
}

Point OpAssign::GetOutlet() const
{
	return Outlet;
}

void OpAssign::SetConn(Connector* pConnector)
{
	pConn = pConnector;
}

Statement* OpAssign::GenerateCode(ostringstream & CodeFile, int &Indent)
{ 
	//The equivalent code is the text of the statement and returns the next statement
	for (int i = 0; i < Indent; i++)
		CodeFile << '\t';
	CodeFile << Text << ';';
	if (Comment != "")
		CodeFile << '\t' << "//" << Comment;
	CodeFile << endl;
	return GetNextStatement(true);
}

Connector* OpAssign::GetConn() const
{
	return pConn;
}

bool OpAssign::IsConnected(Connector * const * ConnList, int ConnCount) const
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

void OpAssign::Edit(Output* pOut, Input* pIn)
{
	//Reading LHS and RHS from the user
	int Type;
	string Operation;
	bool InValid = true;
	pOut->PrintMessage("Editing Operator Assignment Statement, Enter LHS (a variable): ");
	LHS = pIn->GetVariableName(pOut);
	pOut->PrintMessage("Enter type of first operand (1-variable/2-value): ");
	Type = int(pIn->GetValue(pOut));
	switch (Type)
	{
	case 1:
		Op1Type = Variable;
		pOut->PrintMessage("Enter First operand (a variable): ");
		Operand1Variable = pIn->GetVariableName(pOut);
		break;
	case 2:
		Op1Type = Value;
		pOut->PrintMessage("Enter First operand (a value): ");
		Operand1Value = pIn->GetValue(pOut);
		break;
	}

	pOut->PrintMessage("Enter Operator: ");
	Operation = pIn->GetString(pOut);
	while (InValid)
	{
		if (Operation == "+")
		{
			Op = PLUS;
			InValid = false;
		}
		else if (Operation == "-")
		{
			Op = MINUS;
			InValid = false;
		}
		else if (Operation == "*")
		{
			Op = MULTIPLY;
			InValid = false;
		}
		else if (Operation == "/")
		{
			Op = DIVIDE;
			InValid = false;
		}
		else
		{
			pOut->PrintMessage("Invalid Operator, please enter a valid operator: ");
			Operation = pIn->GetString(pOut);
		}

	}

	pOut->PrintMessage("Enter type of second operand (1-variable/2-value): ");
	Type = int(pIn->GetValue(pOut));
	switch (Type)
	{
	case 1:
		Op2Type = Variable;
		pOut->PrintMessage("Enter Second operand (a variable): ");
		Operand2Variable = pIn->GetVariableName(pOut);
		break;
	case 2:
		Op2Type = Value;
		pOut->PrintMessage("Enter Second operand (a value): ");
		Operand2Value = pIn->GetValue(pOut);
		break;
	}
	UpdateStatementText();
}

void OpAssign::DeclareVariable(ostringstream &Code, unordered_map<string, double> &Variables) const
{
	//Declaring the LHS variable in Generate Code
	if (Variables.count(LHS) == 0)
	{
		Variables[LHS] = 0;
		Code << "\tdouble " << LHS << ';' << endl;
	}
}

int OpAssign::GetNoOfConn(Connector* const * ConnList, int ConnCount) const
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

string OpAssign::SetOpString(Operator op)
{
	if (op == PLUS)
	{
		return "PLUS";
	}
	else if (op == MINUS)
	{
		return "MINUS";
	}
	else if (op == MULTIPLY)
	{
		return "MULTIPLY";
	}
	else
	{
		return "DIVIDE";
	}
}

Operator OpAssign::SetStringOp(string op)
{
	if (op == "PLUS")
	{
		return PLUS;
	}
	else if (op == "MINUS")
	{
		return PLUS;
	}
	else if (op == "MULTIPLY")
	{
		return MULTIPLY;
	}
	else
	{
		return DIVIDE;
	}
}

void OpAssign::Save(ofstream &file)
{
	string OP;
	OP = SetOpString(Op);

	file << "SNGLOP   " << ID << "   " << LeftCorner.x << "   " << LeftCorner.y << "   " << Op1Type << "    " << Op2Type << "    " << LHS << "   ";
	if ((Op1Type == Value) && (Op2Type == Value))
	{
		file << Operand1Value << "   " << OP << "   " << Operand2Value;
	}
	else if ((Op1Type == Value) && (Op2Type == Variable))
	{
		file << Operand1Value << "   " << OP << "   " << Operand2Variable;
	}
	else if ((Op1Type == Variable) && (Op2Type == Value))
	{
		file << Operand1Variable << "   " << OP << "   " << Operand2Value;
	}
	else{ file << Operand1Variable << "   " << OP << "   " << Operand2Variable; }
	file << "   " << '"' << Comment << '"' << endl;
}

void OpAssign::Load(ifstream&file)
{
	Point tLeftCorner;
	string tLHS;
	string tOp;
	int tOp1Type;
	int tOp2Type;
	double tOperand1Value;
	double tOperand2Value;
	string tOperand1Variable;
	string tOperand2Variable;
	string tComment;
	Operator tOP;

	file >> tLeftCorner.x >> tLeftCorner.y >> tOp1Type >> tOp2Type >> tLHS;

	if ((tOp1Type == Value) && (tOp2Type == Value))
	{
		file >> tOperand1Value >> tOp >> tOperand2Value;
		tOperand1Variable = "";
		tOperand2Variable = "";

	}
	else if ((tOp1Type == Value) && (tOp2Type == Variable))
	{
		file >> tOperand1Value >> tOp >> tOperand2Variable;
		tOperand1Variable = "";
		tOperand2Value = 0;
	}
	else if ((tOp1Type == Variable) && (tOp2Type == Value))
	{
		file >> tOperand1Variable >> tOp >> tOperand2Value;
		tOperand2Variable = "";
		tOperand1Value = 0;
	}
	else
	{
		file >> tOperand1Variable >> tOp >> tOperand2Variable;
		tOperand1Value = 0;
		tOperand2Value = 0;
	}
	getline(file, tComment);
	tComment = tComment.substr(5, tComment.find_last_of('"') - 5);
	tOP = SetStringOp(tOp);
	SetALL(tLeftCorner, tOP, (OperandType)tOp1Type, (OperandType)tOp2Type, tLHS, tOperand1Value, tOperand2Value, tOperand1Variable, tOperand2Variable, tComment);
	//(Point Lcorner, Operator Op, OperandType O1, OperandType O2, string LeftHS, double Op1, double Op2, string Ops1, string Ops2, string Comment)
}

Statement* OpAssign::GetCopied()
{
	OpAssign*ptr=new OpAssign(LeftCorner,Op,Op1Type,Op2Type,LHS,Operand1Value,Operand2Value,Operand1Variable,Operand2Variable,Comment);
	return ptr;
}

void OpAssign::SetPoint(Point position)
{
	LeftCorner.x=position.x;
	LeftCorner.y=position.y;

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

Point OpAssign::GetPoint()
{
	return LeftCorner;
}