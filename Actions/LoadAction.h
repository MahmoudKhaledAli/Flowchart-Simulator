#ifndef LOAD_H
#define LOAD_H

#include "Action.h"
#include<fstream>
#include<string>
using namespace std;

//Load Action
//This class is responsible for getting the file name and loading the corresponding chart from the file
class LoadAction : public Action
{
private:
	ifstream infile;//name of the file to load from 
	string file;
public:
	LoadAction(ApplicationManager *pAppManager, string Name = "");

	//Read File name from the user
	virtual void ReadActionParameters();

	//Loading the corresponding file
	virtual void Execute();
	void Load(ifstream&);// checks the name of the stat to call load from its function

};

#endif