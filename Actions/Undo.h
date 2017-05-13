#ifndef UNDO_H
#define UNDO_H

#include "Action.h"
#include<fstream>
#include<string>
using namespace std;

//Undo Action
//This class is responsible for loading the last saved file to undo the last action
class Undo : public Action
{
public:
	Undo(ApplicationManager *pAppManager);

	//No input needed
	virtual void ReadActionParameters();

	//Undoing the latest action by loading the file
	virtual void Execute();

};

#endif