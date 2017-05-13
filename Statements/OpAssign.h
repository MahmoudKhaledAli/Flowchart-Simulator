#ifndef OP_ASSIGN_H
#define OP_ASSIGN_H

#include "Statement.h"

//Operator Assignment statement class
//The operator assignment statement assigns a variable to an operation

enum Operator
{
	PLUS,
	MINUS,
	MULTIPLY,
	DIVIDE,
};

enum OperandType
{
	Variable,
	Value,
};

class OpAssign : public Statement
{
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	Operator Op; //type of operator
	OperandType Op1Type; //type of first operand (variable or value)
	OperandType Op2Type; //type of second operand (variable or value)
	double Operand1Value; //if the first operand is a value
	double Operand2Value; //if the second operand is a value
	string Operand1Variable; //if the first operand is a variable
	string Operand2Variable; //if the second operand is a variable

	Connector *pConn;	//Operator Assignment Stat. has one Connector to next statement

	Point Inlet;	//A point where connections enters this statement 
	Point Outlet;	//A point a connection leaves this statement

	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();

public:
	OpAssign(){}
	OpAssign(Point Lcorner, Operator Op, OperandType O1, OperandType O2, string LeftHS = "", double Op1 = 0, double Op2 = 0, string Ops1 = "", string Ops2 = "", string Comment = "");
	void SetALL(Point Lcorner, Operator Op, OperandType O1, OperandType O2, string LeftHS, double Op1, double Op2, string Ops1, string Ops2, string Comment);

	void setLHS(const string &L);
	void setOperator(Operator O);
	void setOperand1Variable(const string &O1);
	void setOperand2Variable(const string &O2);
	void setOperand1Value(double O1);
	void setOperand2Value(double O2);

	virtual void Draw(Output* pOut) const;

	virtual bool Simulate(Output*, Input*, bool &Val, unordered_map<string, double> &Variables, ostringstream &Output, ifstream &InputFile, int Choice) const;
	virtual void Move(int, int);
	virtual bool OutOfBounds(Point);
	virtual bool InRange(Point) const;
	virtual Statement* GetNextStatement(bool = true) const;
	virtual Point GetInlet() const;
	virtual Point GetOutlet() const;
	virtual void SetConn(Connector*);
	virtual Statement* GenerateCode(ostringstream &, int&);
	virtual Connector* GetConn() const;
	virtual bool IsConnected(Connector * const * ConnList, int ConnCount) const;
	virtual void Edit(Output*, Input*);
	virtual void DeclareVariable(ostringstream &, unordered_map<string, double> &Variables) const;
	virtual int GetNoOfConn(Connector * const *, int) const;
	virtual void Save(ofstream &);
	string SetOpString(Operator);
	virtual void Load(ifstream&);
	Operator SetStringOp(string);
	virtual Statement*GetCopied();
	virtual void SetPoint(Point Position);
	virtual Point GetPoint();
};

#endif