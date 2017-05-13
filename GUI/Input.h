#ifndef INPUT_H
#define INPUT_H

#include "..\DEFS.h"
#include "UI_Info.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"

class Output;
class Input		//The application manager should have a pointer to this class
{
private:
	window *pWind;	//Pointer to the Graphics Window
//	window *pOutputWind; //Point to the Output Window
public:
	Input(window *pW);		//Consturctor
	void GetPointClicked(Point &P) const;//Gets coordinate where user clicks

	//void GetPointClickedSim();
	
	double GetValue(Output* pO) const;	// Reads a double value from the user 

	string GetString(Output* pO) const ; //Returns a string entered by the user

	string GetVariableName(Output* pO) const;

	string GetExpression(Output* pO) const; //Returns an arithmetic expression entered by the user

	ActionType GetUserAction() const; //Reads the user click and maps it to an action

	~Input();
};

#endif