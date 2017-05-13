#ifndef SAVE_H
#define SAVE_H

#include "Action.h"
#include<fstream>
#include<string>
using namespace std;

//Save Action
//This class is responsible for saving the chart to a text file
class SaveAction: public Action
{
private:
	ofstream outfile;//file to save in
	string file; // name of the file (req. from the user)
public:
	SaveAction(ApplicationManager *pAppManager, string Name = "");

	//Read File name
	virtual void ReadActionParameters();
	
	//Saving the lists of connectors and statements
	virtual void Execute() ;
	
};

#endif