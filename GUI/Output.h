#ifndef OUPTUT_H
#define OUPTUT_H

#include "Input.h"

class Output	//The application manager should have a pointer to this class
{
private:	
	window* pWind;	//Pointer to the Graphics Window
	//window* pWindOut; //Pointer to the Output Window
public:
	Output();	

	window* CreateWind(int, int, int , int);
//	void CreateOutputWindow();
	//void CloseOutputWindow();
	void CreateDesignToolBar();	//Tool bar of the design mode
	void CreateSimulationToolBar();//Tool bar of the simulation mode

	void CreateStatusBar();

	Input* CreateInput(); //creates a pointer to the Input object	
	void ClearStatusBar();	//Clears the status bar
	void ClearDrawArea();	//Clears the drawing area
	void ClearToolBar();    //Clears the tool bar area

	// -- Statements Drawing Functions
	void DrawAssign(Point Left, int width, int height, string Text, bool Selected = false);
	void DrawConditonalStat(Point Upper, int width, int height, string Text, bool Seleted = false);
	void DrawRead(Point Left, int width, int height, string Text, bool Selected = false);
	void DrawWrite(Point Left, int width, int height, string Text, bool Selected = false);
	void DrawStart(Point Center, int width, int height, bool Selected = false);
	void DrawEnd(Point Center, int width, int height, bool Selected = false);
	void DrawConnector(Point Start, Point End, bool Selected = false);

	void DrawOutput(int Count, string Out);
	void DrawWatch(int Count, string Out);
	void ClearWatch(int Count, string Out);

	//TODO: Add similar functions for drawing all other statements.
	//		e.g. DrawCondtionalStat(......), DrawStart(......), DrawEnd(.......), ...etc
	//		Decide the parameters that should be passed to each of them

		
	void PrintMessage(string msg);	//Prints a message on Status bar
	//void PrintOutput(string Out); //Prints the simulation output
	void PrintValue(double D); //Prints a value on Status bar
	
	~Output();
};

#endif