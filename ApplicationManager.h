#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include<unordered_map>
#include <iostream>

#include "Statements\Statement.h"

class Input;
class Output;

//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxCount = 200 };	//Max no of statements/connectors in a single flowchart

private:
	int StatCount;		//Actual number of statements
	int ConnCount;		//Actual number of connectors
	int PasteCount;     //Actual number of pasted statements
	//int PasteConnCount;
	//int StatID;         //Counter for the ID of statements
	//int SelectedStatCount; //Number of selected statements
	//int SelectedConnCount; //Number of selected connectors
	int UndoCount;
//	bool CanUndo;
	int ActCount;
	int TxtCount;
	Statement* StatList[MaxCount];	//List of all statements (Array of pointers)
	Connector* ConnList[MaxCount];	//List of all connectors (Array of pointers)

	Statement * SelectedStat; 
	Connector * SelectedConn; 

	Statement * PasteStat;//Pointer to the copied statlist from getcopied function to use it in the paste 
	Statement* PasteList[MaxCount];//List of statements to be pasted

	//Connector* PasteConnList[MaxCount];

	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;

public:	
	ApplicationManager(); 
	~ApplicationManager();
	
	// -- Actions Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction() const;
	void ExecuteAction(ActionType) ; //Creates an action and executes it
	
	// -- Statements/Connector Management Functions
	void AddStatement(Statement* pStat); //Adds a new Statement to the Flowchart
	void RemoveStatement(Statement* pStat); //Removes a Statement from the Flowchart
	Statement *GetStatement(Point P) const;	//search for a statement where point P belongs

	void AddConn(Connector* pConn); //Adds a new Connector to the Flowchart
	void RemoveConnector(Connector* pConn); //Removes a Connector from the Flowchart
	Connector *GetConnector(Point P) const;	//search for a Connector where point P belongs
	void UpdateConnectors();//update each connector with new parameters 

	Statement * GetSelectedStatement() const;	//Returns the list of selected statements
	void SetSelectedStatement(Statement *pStat); //Adding a statement to the list of selected statements

	int GetSelectedCount();

	Connector * GetSelectedConnector() const; //Returns the list of selected connectors
	void SetSelectedConnector(Connector *pConn); //Adding a connector to the list of selected connectors

	Statement *GetPasteStat();//Returns the Paste list
	void SetPasteStat(Statement * Paste);//Setting the paste statement which is needed to be copied 
	void AddPasteStat(Statement * stat);//to add in pastelist 
	void ClearPasteStat(); //To clear the paste list

	void IncrementUndo();//Increment the undo counter
	void DecrementUndo();//Decrement the undo counter
	int GetUndo() const;//return the undo counter 
//	bool IsUndo() const;
//	void SetCanUndo(bool);

	int GetActCount() const;
//	void IncrementActCount();
//	void SetActCount(int);

	
		
	// -- Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output
	int GetStatCount() const; 
	int GetConnCount() const;
	Statement * const * GetStatList() const;
	Connector * const * GetConList() const;
	Statement ** GetPasteList();
	Statement* GetSearchedID(int);//return a pointer to a statement with this id
	void Save(ofstream&);//loops on each statement to call save function in it
	void ClearGraph();
	void UpdateInterface() const;	//Redraws all the drawing window
	void SetPasteList();
	Statement* GetLeastY();//return a pointer to the statement with least y in the statlist
	Statement* GetLeastYSelected();//return a pointer to the selected statement with least y 
	void SetPasteCount(int c);
	int GetPasteCount();
	//void SetPasteConnList();
	//Connector**GetPasteConnList();
	//void AddPasteConn(Connector*ptr);
	//void SetPasteConnCount(int c);
	//int GetPasteConnCount();

	void RelativeMove(Point Position);//sets the point of each stat wwith the new position
	void RelativePasteStatement(Point LeastY, Point Position, int countofselected);// sets the statements in paste list with the new positions
	//void RelativePasteConnector(Point LeastY, Point Position);
};

#endif