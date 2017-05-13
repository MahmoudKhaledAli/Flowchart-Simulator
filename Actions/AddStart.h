#ifndef ADD_START_H
#define ADD_START_H

#include "Action.h"
#include "..\Statements\Start.h"

//Add Start Statement Action
//This class is responsible for 
// 1 - Getting Start stat. coordinates from the user
// 2 - Creating an object of Start class
// 3 - Adding the created object to the list of statements
class AddStart : public Action
{
private:
	Point Position;	//Position where the user clicks to add the stat.
	string Com; //Comment on the statement
public:
	AddStart(ApplicationManager *pAppManager);

	//Read Start statements position
	virtual void ReadActionParameters();

	//Create and add an start statement to the list of statements
	virtual void Execute();

};

#endif