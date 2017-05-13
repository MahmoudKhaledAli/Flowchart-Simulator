#ifndef COMMENT_H
#define COMMENT_H

#include "Action.h"
#include "..\Statements\Statement.h"

//Comment Action
//This class is responsible for 
// Getting a string from the user and assigning it to the Comment member of the selected statement
class Comment : public Action
{
private:
	string Com; //The comment entered by the user
public:
	Comment(ApplicationManager *pAppManager);

	//Reading the string
	virtual void ReadActionParameters();

	//Assigning the string to the comment
	virtual void Execute();

};

#endif