#ifndef ADD_READ_H
#define ADD_READ_H

#include "Action.h"
#include "..\Statements\Read.h"

//Add Read Statement Action
//This class is responsible for 
// 1 - Getting Read stat. coordinates from the user
// 2 - Creating an object of Read class and fill it parameters
// 3 - Adding the created object to the list of statements
class AddRead : public Action
{
private:
	Point Position;	//Position where the user clicks to add the stat.
	string VariableName; //Name of the variable
	string Com; //Comment on the statement
public:
	AddRead(ApplicationManager *pAppManager);

	//Read Read statements position
	virtual void ReadActionParameters();

	//Create and add an Read statement to the list of statements
	virtual void Execute();

};

#endif