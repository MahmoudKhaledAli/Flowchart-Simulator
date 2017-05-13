#ifndef DEFS_H
#define DEFS_H

//This file contais some global constants and definitions to be used in the project.

enum ActionType //The actions supported (you can add more if needed)
{
	ADD_SMPL_ASSIGN,//Add simple assignment statement
	ADD_VAR_ASSIGN,	//Add variable assignment statement
	ADD_OP_ASSIGN, //Add a single operator assignment statement
	ADD_CONDITION, //Add a conditional statement (for if and while-loop statements)
	ADD_READ,// Add a read statement
	ADD_WRITE,//Add a write statement
	ADD_START,//Add start statement
	ADD_END,//Add end statement

	ADD_CONNECTOR, //Add a connector between two statements

	EDIT,	//Edit
	
	SELECT,		//Select a statement, a connector

	DEL,		//Delete a figure(s)
	MOVE,		//Move a figure(s)
	COM,		//Comment on a statement
	COPY,       //Copy a statement(s)
	CUT,        //Cut a statement(s)
	PASTE,      //Paste a statement(s)

	SAVE,		//Save the whole graph to a file
	LOAD,		//Load a graph from a file
	MULTI_SELECT, //select multiple statements
	EXIT,		//Exit the application
	STATUS,		//A click on the status bar
	DSN_TOOL,	//A click on an empty place in the design tool bar
	DSN_MODE,	//Switch to Design mode
	SIM_MODE,	//Switch to simulatiom mode
	UNDO,       //Undo Last Action
	REDO,       //Redo Last Action

	VALIDATE, //validate flow chart
	GENERATE, //generate code file
	RUN,      //run the flow chart
	STEP,     //step by step mode(skip to next step)

};

enum  MODE	//Modes of operation
{
	DESIGN,
	SIMULATION
};

enum DsgnMenuItem //The items of the design menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you change the menu items order, change the order here too
	ITM_SMPL_ASSIGN,//simple assignment statement
	ITM_VAR_ASSIGN,//variable assignment statement
	ITM_OP_ASSIGN,//single operator assignment statement
	ITM_COND,//conditional statement
	ITM_READ,//read statement
	ITM_WRITE,//write statement
	ITM_START,//start statement
	ITM_END,//end statement
	ITM_CONNECTOR,//connector

	ITM_EDIT,//Edit
	ITM_DEL,//Delete
	ITM_MOVE,//Move
	ITM_COMM,//Comment
	ITM_COPY,//Copy
	ITM_CUT,//Cut
	ITM_PASTE,//Paste
	ITM_SAVE,//Save
	ITM_LOAD,//Load
	ITM_MULTI_SELECT,//Multiple select
	ITM_SIM_MODE,//switch to sim mode
	ITM_UNREDO, //Undo or Redo


	ITM_EXIT,		//Exit
	
	//TODO: Add more items names here
	
	ITM_DSN_CNT		//no. of design menu items ==> This should be the last line in this enum
	
};


enum SimMenuItem //The items of the simulation menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	ITM_VLDTE,  //Validate flow chart
	ITM_RUN,	//Run
	ITM_STP,	//Step by step
	ITM_STOP,   //Stop step by step mode
	ITM_GNRTE,  //Generate code file
	ITM_DSN_MODE, //Switch to design mode
	ITM_EXIT2,   //Exit
	
	//TODO:Add more items names here
	
	ITM_SIM_CNT		//no. of simulation menu items ==> This should be the last line in this enum
	
};




#ifndef NULL
#define NULL 0
#endif

#endif