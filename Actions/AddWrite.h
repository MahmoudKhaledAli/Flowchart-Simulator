#ifndef ADD_WRITE_H
#define ADD_WRITE_H

#include "Action.h"
#include "..\Statements\Write.h"

//Add write Statement Action
//This class is responsible for 
// 1 - Getting Write stat. coordinates from the user
// 2 - Creating an object of Write class and fill it parameters
// 3 - Adding the created object to the list of statements
class AddWrite : public Action
{
private:
	Point Position;	//Position where the user clicks to add the stat.
	string VariableName; //Name of the variable
	string Com; //Comment on the statement
	bool Message; //To determine wether the target is a message or a variable name
public:
	AddWrite(ApplicationManager *pAppManager);

	//Read write statements position
	virtual void ReadActionParameters();

	//Create and add an write statement to the list of statements
	virtual void Execute();

};

#endif