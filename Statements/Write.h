#ifndef WRITE_H
#define WRITE_H

#include "Statement.h"

//write statement class
//The write statement writes a value
class Write : public Statement
{
private:
	string Target;	//Target variable of the statement (name of a variable)

	Connector *pConn;	//Write Stat. has one Connector to next statement

	Point Inlet;	//A point where connections enters this statement 
	Point Outlet;	//A point a connection leaves this statement

	Point LeftCorner;	//left corenr of the statement block.

	bool Message;

	virtual void UpdateStatementText();

public:
	Write(){};
	Write(bool Message, Point Lcorner, string LeftHS = "", string Comment = "");
	void SetAll(bool, Point, string, string);

	void setTarget(const string &T);

	virtual void Draw(Output* pOut) const;

	virtual bool Simulate(Output*, Input*, bool &Val, unordered_map<string, double> &Variables, ostringstream &Output, ifstream &InputFile, int Choice) const;
	virtual void Move(int, int);
	virtual bool OutOfBounds(Point);
	virtual bool InRange(Point) const;
	virtual Statement* GetNextStatement(bool = true) const;
	virtual Statement* GenerateCode(ostringstream &, int&);
	virtual Connector* GetConn() const;
	virtual Point GetInlet() const;
	virtual Point GetOutlet() const;
	virtual void SetConn(Connector*);
	virtual bool IsConnected(Connector* const * ConnList, int ConnCount) const;
	virtual void Edit(Output*, Input*);
	virtual int GetNoOfConn(Connector * const *, int) const;
	virtual void Save(ofstream &);
	virtual void Load(ifstream&);
	virtual Statement*GetCopied();
	virtual void SetPoint(Point Position);
	virtual Point GetPoint();
};

#endif