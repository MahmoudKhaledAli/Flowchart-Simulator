#ifndef SMPL_ASSIGN_H
#define SMPL_ASSIGN_H

#include "Statement.h"

//Simple Assignment statement class
//The simple assignment statement assigns a variable to a value
class SmplAssign : public Statement
{
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	double RHS;	//Right Handside (Value)
	
	Connector *pConn;	//Simple Assignment Stat. has one Connector to next statement

	Point Inlet;	//A point where connections enters this statement 
	Point Outlet;	//A point a connection leaves this statement

	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();
	
public:
	SmplAssign(){}
	SmplAssign(Point Lcorner, string LeftHS = "", double RightHS = 0, string Comment = "");
	void SetAll(Point, string, double, string);

	void setLHS(const string &L);
	void setRHS(double R);

	virtual void Draw(Output* pOut) const;

	virtual bool Simulate(Output*, Input*, bool &Val, unordered_map<string, double> &Variables, ostringstream &Output, ifstream &InputFile, int Choice) const;
	virtual void Move(int, int);
	virtual bool OutOfBounds(Point);
	virtual bool InRange(Point) const;
	virtual Statement* GetNextStatement(bool = true) const;
	virtual Point GetOutlet() const;
	virtual Point GetInlet() const;
	virtual void SetConn(Connector*);
	virtual Statement* GenerateCode(ostringstream &, int&);
	virtual string GetLHS() const;
	virtual Connector* GetConn() const;
	virtual bool IsConnected(Connector * const * ConnList, int ConnCount) const;
	virtual void Edit(Output*, Input*);
	virtual void DeclareVariable(ostringstream&, unordered_map<string, double> &Variables) const;
	virtual int GetNoOfConn(Connector * const *, int) const;
	virtual void Save(ofstream &);
	virtual void Load(ifstream&);
	virtual Statement*GetCopied();
	virtual void SetPoint(Point Position);
	virtual Point GetPoint();

};

#endif