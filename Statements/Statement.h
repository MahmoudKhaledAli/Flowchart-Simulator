#ifndef STATEMENT_H
#define STATEMENT_H

#include "..\defs.h"
#include "Connector.h"
//class Output;
#include "..\GUI\Output.h"
#include "..\ApplicationManager.h"
#include <string>
#include <fstream>
#include <sstream>

class ApplicationManager;

//Base class for all Statements


class Statement
{
protected:
	int ID;			//Each Statement has an ID
	string Text;	//Statement text (e.g.  "X = 5" OR "if(salary > 3000)" and so on )
	bool Selected;	//true if the statement is selected on the folwchart
	string Comment; //Comment on the statement
	bool Generating; //true if the statement is currently being generated in the Generate Code Action


	virtual void UpdateStatementText() = 0;	//is called when any part of the stat. is edited	

	/// Add more parameters if needed.

public:
	void SetGenerating(bool G) { Generating = G; }
	bool IsGenerating() const { return Generating; }
	Statement();
	void SetSelected(bool s);
	bool IsSelected() const;

	virtual void Draw(Output* pOut) const  = 0 ;	//Draw the statement
	
	

	///TODO:The following functions should be supported by the Statement class
	///		It should then be overridden by each derived Statement
	///		Decide the parameters that you should pass to each function and its return type	


	virtual void Save(ofstream &OutFile) = 0;	//Save the Statement parameters to a file
	virtual void Load(ifstream &Infile) = 0;	//Load the Statement parameters from a file
	virtual void Move(int, int) = 0;		//Move the Statement on the flowchart
	virtual void Edit(Output* pOut, Input* pIn) = 0;		//Edit the Statement parameter
	virtual Statement* GenerateCode(ostringstream &Code, int &Indent) = 0;	//write the statement code to a file
	virtual bool Simulate(Output*, Input*, bool &Val, unordered_map<string, double> &Variables, ostringstream &Output, ifstream &InputFile, int Choice) const = 0;	//Execute the statement in the simulation mode
	//virtual void PrintInfo(Output* pOut) = 0;	//print all Statement info on the status bar
	virtual bool OutOfBounds(Point) = 0; //Find if a point will make the statement out of bounds
	virtual bool InRange(Point) const = 0; //Find if a point belongs in the statement
	virtual Statement* GetNextStatement(bool = true) const = 0; //Returns the next statement in the simulation mode
	virtual Point GetInlet() const; //Returns the inlet point
	virtual Point GetOutlet() const; //Returns the outlet point (except for conditional)
	virtual void SetConn(Connector*); //Sets the outgoing connector (except for conditional)
	void SetID(int Id); //Set the statement ID
	int GetID() const; //Returns the statement ID
	virtual string GetLHS() const; //Returns the LHS of the statement
	virtual Connector* GetConn() const; //Returns the outgoing connector
	virtual bool IsConnected(Connector* const * ConnList, int ConnCount) const = 0; //Checks if the statement is properly connected
	virtual void DeclareVariable(ostringstream &Code, unordered_map<string, double> &Variables) const; //Declare the LHS variable in the code generation
	string GetText() const; //Returns the text of the statement
	virtual int GetNoOfConn(Connector * const * ConnList, int ConnCount) const = 0; //returns the number of connections
	void SetCom(const string &Com); //Sets the statement comment
	string GetCom() const; //returns the statement comment
	virtual bool NoExitLoop(); //Checks if the statement is the start of a loop with no exit condition
	virtual Statement*GetCopied()=0;//set new statement of each type of the statement
	virtual void SetPoint(Point Position)=0;// update the point of each statement
	virtual Point GetPoint()=0;
	/*void SetLooped(bool T){ Looped = T; }


	bool IsLooped(){ return Looped; }
*/
	//bool InLoop(ApplicationManager*, int*);
	
	///TODO: Add more functions if needed
};

#endif