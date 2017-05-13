#ifndef REDO_H
#define REDO_H

#include "Action.h"
#include<fstream>
#include<string>
using namespace std;

//Redo Action
//This class is responsible for loading the file to redo an action
class Redo : public Action
{
public:
	Redo(ApplicationManager *pAppManager);

	//No input needed
	virtual void ReadActionParameters();

	//Loading the correct file
	virtual void Execute();

};

#endif