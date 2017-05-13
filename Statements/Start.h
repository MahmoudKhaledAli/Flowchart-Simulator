#ifndef START_H
#define START_H

#include "Statement.h"

//Start statement class
//The start statement is the start point of a flow chart
class Start : public Statement
{
private:
	Connector *pConn;	//Simple Assignment Stat. has one Connector to next statement

	//Point Inlet;	//A point where connections enters this statement 
	Point Outlet;	//A point a connection leaves this statement

	Point Center;	//left corenr of the statement block.

	virtual void UpdateStatementText();

public:
	Start(){}
	Start(Point C, string Comment = "");
	void SetAll(Point, string);

	virtual void Draw(Output* pOut) const;

	virtual bool Simulate(Output*, Input*, bool &Val, unordered_map<string, double> &Variables, ostringstream &Output, ifstream &InputFile, int Choice) const;
	virtual void Move(int, int);		//Move the Statement on the flowchart
	virtual bool OutOfBounds(Point);		
	virtual bool InRange(Point) const;
	virtual Statement* GetNextStatement(bool = true) const;
	virtual Point GetOutlet() const;
	virtual void SetConn(Connector*);
	virtual Statement* GenerateCode(ostringstream &, int&);
	virtual Connector* GetConn() const;
	virtual bool IsConnected(Connector * const * ConnList, int ConnCount) const;
	virtual void Edit(Output*, Input*);
	virtual int GetNoOfConn(Connector*const*, int) const;
	virtual void Save(ofstream &);
	virtual void Load(ifstream&);
	virtual Statement*GetCopied();
	virtual void SetPoint(Point Position);
	virtual Point GetPoint();
};

#endif