#ifndef ADD_COND_H
#define ADD_COND_H

#include "Action.h"
#include "..\Statements\Cond.h"

//Add Conditional Statement Action
//This class is responsible for 
// 1 - Getting Conditional stat. coordinates from the user
// 2 - Creating an object of Cond class and fill it parameters
// 3 - Adding the created object to the list of statements
class AddCond : public Action
{
private:
	Point Position;
	string LHS;	//Left Handside of the assignment (name of a variable)
	OperandType RHSType; //type of RHS (variable or value)
	string COp; //Operator
	double RHSValue; //if the RHS is a value
	string RHSVariable; //if the RHS is a variable
	string Com; //Comment on the statement
public:
	AddCond(ApplicationManager *pAppManager);

	//Read parameters of conditional stat
	virtual void ReadActionParameters();

	//creating object of condition stat type
	virtual void Execute();

};

#endif