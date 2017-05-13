#ifndef COND_H
#define COND_H

#include "Statement.h"
#include "OpAssign.h"

//Conditional statement class
//The Conditional statement evaluates a condition and choses the direction of the flow chart

class Cond : public Statement
{
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	double RHSValue;	//Right Handside (Value)
	string RHSVariable;
	string COperator;

	OperandType RHSType;

	Connector *pConnYes;	//Connector in case the statement is true
	Connector *pConnNo;     //Connector in case the statement is false

	Point Inlet;	//A point where connections enters this statement 
	Point OutletYes;	//A point a connection leaves this statement in true case
	Point OutletNo;     //A point a connection leaves this statement in false case

	Point TopCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();

public:
	Cond(){}
	Cond(Point TCorner, string Operator, OperandType OpType, string LeftHS = "", double RightHSVal = 0, string RightHSVar = "", string Comment = "");
	void SetAll(Point, string, OperandType, string, double, string, string);

	void setLHS(const string &L);
	void setRHSVariable(const string &R);
	void setRHSValue(double R);

	virtual void Draw(Output* pOut) const;

	virtual bool Simulate(Output*, Input*, bool &Val, unordered_map<string, double> &Variables, ostringstream &Output, ifstream &InputFile, int Choice) const;
	virtual void Move(int, int);
	virtual bool OutOfBounds(Point);
	virtual bool InRange(Point) const;
	virtual Statement* GetNextStatement(bool = true) const;
	Point GetYesOutlet() const;
	Point GetNoOutlet() const;
	virtual Point GetInlet() const;
	virtual void SetYesConn(Connector*);
	virtual void SetNoConn(Connector*);
	Statement* GenerateCode(ostringstream &, int&);
	virtual string GetLHS() const;
	Connector* GetYesConn() const;
	Connector* GetNoConn() const;
	virtual Connector* GetConn() const;
	virtual bool IsConnected(Connector * const * ConnList, int ConnCount) const;
	virtual void Edit(Output*, Input*);
	virtual int GetNoOfConn(Connector * const *, int) const;
	virtual bool NoExitLoop();
	virtual void Save(ofstream &);
	virtual void Load(ifstream&);
	virtual Statement*GetCopied();
	virtual void SetPoint(Point Position);
	virtual Point GetPoint();
};

#endif