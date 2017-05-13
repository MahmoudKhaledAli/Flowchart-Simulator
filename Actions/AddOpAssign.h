#ifndef ADD_OP_ASSIGN_H
#define ADD_OP_ASSIGN_H

#include "Action.h"
#include "..\Statements\OpAssign.h"

//Add Operator Assignment Statement Action
//This class is responsible for 
// 1 - Getting Assignment stat. coordinates from the user
// 2 - Creating an object of Assignment class and fill it parameters
// 3 - Adding the created object to the list of statements
class AddOpAssign : public Action
{
private:
	Point Position;
	string LHS;	//Left Handside of the assignment (name of a variable)
	Operator Op; //type of operator
	OperandType Op1Type; //type of first operand (variable or value)
	OperandType Op2Type; //type of second operand (variable or value)
	double Operand1Value; //if the first operand is a value
	double Operand2Value; //if the second operand is a value
	string Operand1Variable; //if the first operand is a variable
	string Operand2Variable; //if the second operand is a variable
	string Com; //Comment on the statement
public:
	AddOpAssign(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();

};

#endif