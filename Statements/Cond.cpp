#include "Cond.h"
#include <sstream>

using namespace std;

Cond::Cond(Point TCorner, string Operator, OperandType OpType, string LeftHS, double RightHSVal, string RightHSVar, string Comment)
{
	SetAll(TCorner, Operator, OpType, LeftHS, RightHSVal, RightHSVar, Comment);
}

void Cond::SetAll(Point TCorner, string Operator, OperandType OpType, string LeftHS, double RightHSVal, string RightHSVar, string Comment)
{
	LHS = LeftHS;
	switch (OpType)
	{
	case Value:
		RHSValue = RightHSVal;
		break;
	case Variable:
		RHSVariable = RightHSVar;
		break;
	}
	this->Comment = Comment;
	COperator = Operator;
	RHSType = OpType;

	UpdateStatementText();

	TopCorner = TCorner;

	pConnYes = NULL;	//No connectors yet
	pConnNo = NULL;

	Inlet.x = TopCorner.x;
	Inlet.y = TopCorner.y;

	OutletYes.x = Inlet.x + UI.COND_WDTH / 2;
	OutletYes.y = Inlet.y + (UI.COND_HI / 2);
	OutletNo.y = OutletYes.y;
	OutletNo.x = Inlet.x - UI.COND_WDTH / 2;
}

void Cond::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}

void Cond::setRHSVariable(const string &R)
{
	RHSVariable = R;
	UpdateStatementText();
}

void Cond::setRHSValue(double R)
{
	RHSValue = R;
	UpdateStatementText();
}

void Cond::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawConditonalStat(TopCorner, UI.COND_WDTH, UI.COND_HI, Text, Selected);

}


//This function should be called when LHS or RHS changes
void Cond::UpdateStatementText()
{
	if (LHS == "")	//No left handside ==>statement have no valid text yet
		Text = "    = ";
	else
	{
		//Build the statement text: Left handside then equals then right handside
		ostringstream T;
		T << LHS << ' ' << COperator << ' ';
		switch (RHSType)
		{
		case Value:
			T << RHSValue;
			break;
		case Variable:
			T << RHSVariable;
		}
		Text = T.str();
	}
}

bool Cond::Simulate(Output* pOut, Input* pIn, bool& Val, unordered_map<string, double>&Variables, ostringstream &Output, ifstream &InputFile, int Choice) const
{
	double RHSV;
	//Checking for validity of LHS and RHS
	if (LHS == "")
	{
		Val = false;
		pOut->PrintMessage("LHS is Invalid");
		return true;
	}
	if (RHSType == Variable && RHSVariable == "")
	{
		Val = false;
		pOut->PrintMessage("RHS is Invalid");
		return true;
	}
	//If the LHS hasn't been initialized yet then return an error
	if (Variables.count(LHS) == 0)
	{
		Val = false;
		pOut->PrintMessage("Variable is being used in LHS of a condition without being declared");
		return true;
	}
	switch (RHSType)
	{
	case Variable:
		if (Variables.count(RHSVariable) == 0)
		{
			Val = false;
			//If the RHS is not initialized yet
			pOut->PrintMessage("Variable is being used in RHS without being declared");
			return true;
		}
		RHSV = Variables[RHSVariable];
		break;
	case Value:
		RHSV = RHSValue;
	}
	//Simulating the condition and returning the corresponding value to be used in the simulate class to get the next statement
	if (COperator == "==")
		return(Variables[LHS] == RHSV);
	else if (COperator == "!=")
		return(Variables[LHS] != RHSV);
	else if (COperator == "<")
		return(Variables[LHS] < RHSV);
	else if (COperator == ">")
		return(Variables[LHS] > RHSV);
	else if (COperator == "<")
		return(Variables[LHS] < RHSV);
	else if (COperator == "<=")
		return(Variables[LHS] <= RHSV);
	else if (COperator == ">=")
		return(Variables[LHS] >= RHSV);
	else
		return false;
}

void Cond::Move(int XShift, int YShift)
{
	TopCorner.x += XShift;
	TopCorner.y += YShift;
	Inlet.x += XShift;
	Inlet.y += YShift;
	OutletYes.x += XShift;
	OutletYes.y += YShift;
	OutletNo.x += XShift;
	OutletNo.y += YShift;
}

bool Cond::OutOfBounds(Point Pt)
{
	return (Pt.x - UI.COND_WDTH / 2 < 0 || Pt.x + UI.COND_WDTH / 2 > UI.width || Pt.y < UI.TlBrWdth || (Pt.y + UI.COND_HI) >(UI.height - UI.StBrWdth));
}

bool Cond::InRange(Point Pt) const
{
	return(Pt.x > TopCorner.x - UI.COND_WDTH/2 && Pt.x < TopCorner.x + UI.COND_WDTH/2 && Pt.y > TopCorner.y && Pt.y < TopCorner.y + UI.COND_HI);
}

Statement* Cond::GetNextStatement(bool T) const
{
	if (T)
		return(pConnYes->getDstStat());
	return(pConnNo->getDstStat());
}

Point Cond::GetInlet() const
{
	return Inlet;
}

Point Cond::GetYesOutlet() const
{
	return OutletYes;
}

Point Cond::GetNoOutlet() const
{
	return OutletNo;
}

void Cond::SetYesConn(Connector* pConnector)
{
	pConnYes = pConnector;
}

void Cond::SetNoConn(Connector* pConnector)
{
	pConnNo = pConnector;
}

Statement* Cond::GenerateCode(ostringstream &CodeFile, int &Indent)
{
	int OrgIndent = Indent;
	SetGenerating(true);
	ostringstream Yes;
	ostringstream No;
	Statement* pStat1 = pConnYes->getDstStat();
	Statement* pStat2 = pConnNo->getDstStat();
	Statement* NoStart = pStat2;
	++Indent;
	bool Same = pStat1 == pStat2;
	bool LoopYes = false;
	bool LoopNo = false;
	//Looping through the statements from the yes branch and the no branch and checking:
	//1-if it's a condition
	//2-if it's a loop from the yes branch
	//3-if it's a loop from the no branch
	while (pStat1 != pStat2 && pStat1 != NULL)
	{
		pStat2 = NoStart;
		No.str("");
		No.clear();
		while (pStat2 != NULL && !pStat2->IsGenerating())
		{
			if (pStat1 == pStat2)
			{
				Same = true;
				break;
			}
			if (!pStat2->IsGenerating())
				pStat2 = pStat2->GenerateCode(No, Indent);
			else
				break;
			if (pStat1 == pStat2)
			{
				Same = true;
				break;
			}
			else if (pStat2 == this)
			{
				LoopNo = true;
				break;
			}
		}
		if (Same)
			break;
		if (pStat1->IsGenerating())
			break;
		if (!Same && !LoopNo)
		{
			pStat1 = pStat1->GenerateCode(Yes, Indent);
		}
		else if (LoopNo)
		{
			break;
		}
		if (pStat1 == this)
		{
			LoopYes = true;
			break;
		}
	}
	Indent = OrgIndent;
	for (int i = 0; i < Indent; i++)
		CodeFile << '\t';
	if (Same)
	{
		CodeFile << "if (" << Text << ')';
		if (Comment != "")
			CodeFile << '\t' << "//" << Comment;
		CodeFile << endl;
		for (int i = 0; i < Indent; i++)
			CodeFile << '\t';
		CodeFile << "{\n";
		CodeFile << Yes.str() << "\n";
		for (int i = 0; i < Indent; i++)
			CodeFile << '\t';
		CodeFile << "}\n";
		for (int i = 0; i < Indent; i++)
			CodeFile << '\t';
		CodeFile << "else\n";
		for (int i = 0; i < Indent; i++)
			CodeFile << '\t';
		CodeFile << "{\n" << No.str() << "\n";
		for (int i = 0; i < Indent; i++)
			CodeFile << '\t';
		CodeFile << "}" << endl;
		SetGenerating(false);
		return pStat1;
	}
	else if (LoopYes)
	{
		CodeFile << "while (" << Text << ")";
		if (Comment != "")
			CodeFile << '\t' << "//" << Comment;
		CodeFile << endl;
		for (int i = 0; i < Indent; i++)
			CodeFile << '\t';
		CodeFile << "{\n";
		CodeFile << Yes.str();
		for (int i = 0; i < Indent; i++)
			CodeFile << '\t';
		CodeFile << "}\n";
		SetGenerating(false);
		return GetNoConn()->getDstStat();
	}
	else if (LoopNo)
	{
		CodeFile << "while (!(" << Text << "))";
		if (Comment != "")
			CodeFile << '\t' << "//" << Comment;
		CodeFile << endl;
		for (int i = 0; i < Indent; i++)
			CodeFile << '\t';
		CodeFile << "{\n";
		CodeFile << No.str();
		for (int i = 0; i < Indent; i++)
			CodeFile << '\t';
		CodeFile << "}\n";
		SetGenerating(false);
		return GetYesConn()->getDstStat();
	}
	if (pStat1)
	{
		if (pStat1->IsGenerating())
		{
			pStat1->SetGenerating(false);
			CodeFile << "if (" << Text << ")";
			if (Comment != "")
				CodeFile << '\t' << "//" << Comment;
			CodeFile << endl;
			for (int i = 0; i < Indent; i++)
				CodeFile << '\t';
			CodeFile << "{\n";
			CodeFile << Yes.str() << "\n";
			for (int i = 0; i < Indent; i++)
				CodeFile << '\t';
			CodeFile << "}\n";
			for (int i = 0; i < Indent; i++)
				CodeFile << '\t';
			CodeFile << "else\n";
			for (int i = 0; i < Indent; i++)
				CodeFile << '\t';
			CodeFile << "{\n" << No.str() << "\n";
			for (int i = 0; i < Indent; i++)
				CodeFile << '\t';
			CodeFile << "}" << endl;
			return pStat1;
		}
	}
	if (pStat2)
	{
		if (pStat2->IsGenerating())
		{
			pStat2->SetGenerating(false);
			CodeFile << "if (" << Text << ")";
			if (Comment != "")
				CodeFile << '\t' << "//" << Comment;
			CodeFile << endl;
			for (int i = 0; i < Indent; i++)
				CodeFile << '\t';
			CodeFile << "{\n";
			CodeFile << Yes.str() << "\n";
			for (int i = 0; i < Indent; i++)
				CodeFile << '\t';
			CodeFile << "}\n";
			for (int i = 0; i < Indent; i++)
				CodeFile << '\t';
			CodeFile << "else\n";
			for (int i = 0; i < Indent; i++)
				CodeFile << '\t';
			CodeFile << "{\n" << No.str() << "\n";
			for (int i = 0; i < Indent; i++)
				CodeFile << '\t';
			CodeFile << "}" << endl;
			return pStat2;
		}
	}
	return NULL;
}

string Cond::GetLHS() const
{
	return LHS;
}

Connector *Cond::GetYesConn() const
{
	return pConnYes;
}

Connector *Cond::GetNoConn() const
{
	return pConnNo;
}

Connector* Cond::GetConn() const
{
	if (pConnYes && pConnNo)
		return pConnYes;
	return NULL;
}

bool Cond::IsConnected(Connector * const * ConnList, int ConnCount) const
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
	return(ConnectedIn && pConnYes && pConnNo);
}

void Cond::Edit(Output* pOut, Input* pIn)
{
	//Reading LHS and RHS from the user
	int Type;
	bool InValid = true;
	pOut->PrintMessage("Enter LHS (a variable): ");
	LHS = pIn->GetVariableName(pOut);

	pOut->PrintMessage("Enter Operator: ");
	COperator = pIn->GetString(pOut);
	while (InValid)
	{
		if (COperator == "==")
		{
			InValid = false;
		}
		else if (COperator == "!=")
		{
			InValid = false;
		}
		else if (COperator == "<")
		{
			InValid = false;
		}
		else if (COperator == ">")
		{
			InValid = false;
		}
		else if (COperator == ">=")
		{
			InValid = false;
		}
		else if (COperator == "<=")
		{
			InValid = false;
		}
		else
		{
			pOut->PrintMessage("Invalid Operator, please enter a valid operator: ");
			COperator = pIn->GetString(pOut);
		}

	}

	pOut->PrintMessage("Enter type of RHS (1-variable/2-value): ");
	Type = int(pIn->GetValue(pOut));
	switch (Type)
	{
	case 1:
		RHSType = Variable;
		pOut->PrintMessage("Enter RHS (a variable): ");
		RHSVariable = pIn->GetVariableName(pOut);
		break;
	case 2:
		RHSType = Value;
		pOut->PrintMessage("Enter RHS (a value): ");
		RHSValue = pIn->GetValue(pOut);
		break;
	}

	UpdateStatementText();
}

int Cond::GetNoOfConn(Connector* const * ConnList, int ConnCount) const
{
	int C = 0;
	if (pConnYes)
		C++;
	if (pConnNo)
		C++;
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i]->getDstStat() == this)
			C++;
	}
	return C;
}

bool Cond::NoExitLoop()
{
	return false;
}

void Cond::Save(ofstream&file)
{
	file << "COND" << "    " << ID << "    " << TopCorner.x << "    " << TopCorner.y << "    " << RHSType << "    " << LHS << "    ";
	if (RHSType == Variable)
	{
		file << COperator << "    " << RHSVariable << "    " << '"' << Comment << '"' << endl;
	}
	else
	{
		file << COperator << "    " << RHSValue << "    " << '"' << Comment << '"' << endl;
	}
}

void Cond::Load(ifstream&infile)
{
	int id;
	int a;
	int b;
	Point corner;
	string LHS;
	double RHSValue;
	string RHSVariable;
	string COperator;
	string comment = "";
	int RHSType;
	infile >> a >> b >> RHSType >> LHS >> COperator;
	corner.x = a;
	corner.y = b;
	if (RHSType == 0)
	{
		infile >> RHSVariable;
		RHSValue = 0;
	}
	else
	{
		infile >> RHSValue;
		RHSVariable = "";
	}
	getline(infile, comment);
	int s = comment.find_first_of('"');
	comment = comment.substr(5, comment.find_last_of('"') - 5);
	SetAll(corner, COperator, (OperandType)RHSType, LHS, RHSValue, RHSVariable, comment);
}

Statement* Cond::GetCopied()
{
	Cond*ptr=new Cond(TopCorner,COperator,RHSType,LHS,RHSValue,RHSVariable,Comment);
	return ptr;
}

void Cond::SetPoint(Point position)
{
	TopCorner.x=position.x;
	TopCorner.y=position.y;

	Inlet.x = TopCorner.x;
	Inlet.y = TopCorner.y;

	OutletYes.x = Inlet.x + UI.COND_WDTH / 2;
	OutletYes.y = Inlet.y + (UI.COND_HI / 2);
	OutletNo.y = OutletYes.y;
	OutletNo.x = Inlet.x - UI.COND_WDTH / 2;
}

Point Cond::GetPoint()
{
	return TopCorner;
}