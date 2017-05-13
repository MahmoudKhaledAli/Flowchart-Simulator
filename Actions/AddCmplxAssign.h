#ifndef ADD_CMPLX_ASSIGN_H
#define ADD_CMPLX_ASSIGN_H

#include "Action.h"
#include "..\Statements\CmplxAssign.h"

//Add Complex Assignment Statement Action
//This class is responsible for 
// 1 - Getting Assignment stat. coordinates from the user
// 2 - Creating an object of Assignment class and fill it parameters
// 3 - Adding the created object to the list of statements
class AddCmplxAssign : public Action
{
private:
	Point Position;	//Position where the user clicks to add the stat.
	string VariableName; //Name of the variable on the LHS
	string Expression;    //Arithmetic expression on the RHS
	string Com; //Comment on the statement
public:
	AddCmplxAssign(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();

};

#endif