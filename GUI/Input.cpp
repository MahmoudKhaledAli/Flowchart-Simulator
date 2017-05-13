#include "Input.h"
#include "Output.h"




Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
	//pOutputWind = pOW;
}

void Input::GetPointClicked(Point &P) const
{
	pWind->FlushMouseQueue();
	pWind->WaitMouseClick(P.x, P.y);	//Wait for mouse click
}

//void Input::GetPointClickedSim()
//{
//	Point P;
//	P.x = 0;
//	P.y = 0;
//	pOutputWind->FlushMouseQueue();
//	pOutputWind->WaitMouseClick(P.x, P.y);
//}

string Input::GetString(Output *pO) const 
{
	pWind->FlushKeyQueue();
	string Str;
	char Key;
	//pO->PrintMessage("Please enter a string");
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Str;
		if (Key == 8)	//BackSpace is pressed
		{
			if (Str.size() != 0)
				Str.resize(Str.size() - 1);
		}
		else
			Str += Key;
		pO->PrintMessage(Str);
	}
	
}

string Input::GetVariableName(Output* pO) const
{
	pWind->FlushKeyQueue();
	string Str;
	char Key;
	bool Num = false;
	//pO->PrintMessage("Please enter a string");
	while (1)
	{
		pWind->WaitKeyPress(Key);
		//if (Key == 27)	//ESCAPE key is pressed
		//	return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
		{
			if (Str.size() > 0)
				return Str;
		}
		else if (Key == 8)	//BackSpace is pressed
		{
			if (Str.size() != 0)
				Str.resize(Str.size() - 1);
		}
		else if (Key == ' ');
		else if (Key >= '0' && Key <= '9')
		{
			if (Num)
				Str += Key;
		}
		else if ((Key < 'a' || Key > 'z') && (Key < 'A' || Key > 'Z') && Key != '_');
		else
		{
			Str += Key;
		}
		if (Str.size() > 0)
			Num = true;
		else
			Num = false;
		pO->PrintMessage(Str);
	}
}

string Input::GetExpression(Output* pO) const
{
	pWind->FlushKeyQueue();
	string Str;
	char Key;
	int Bracket = 0;
	int Operators = 0;
	char LastKey = ' ';
	//pO->PrintMessage("Please enter a string");
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	//ESCAPE key is pressed
			return "0";	//returns nothing as user has cancelled label
		else if (Key == 13)	//ENTER key is pressed
		{
			if (Str.size() == 0)
				return "0";
			if (Bracket == 0)
				return Str;
		}
		else if (Key == 8)	//BackSpace is pressed
		{
			if (Str.size() != 0)
			{
				if (Str.at(Str.size() - 1) == '(')
					Bracket--;
				else if (Str.at(Str.size() - 1) == ')')
					Bracket++;
				else if (Str.at(Str.size() - 1) == '+' || Str.at(Str.size() - 1) == '-' || Str.at(Str.size() - 1) == '*' || Str.at(Str.size() - 1) == '/')
					Operators--;
				Str.resize(Str.size() - 1);
				if (Str.size() != 0)
					LastKey = Str.find_last_not_of(' ');
				else
					LastKey = ' ';
			}
		}
		else if (Key != '.' && (Key < '0' || Key > '9') && (Key < 'a' || Key > 'z') && (Key < 'A' || Key > 'Z') && Key != '+' && Key != '-' && Key != '*' && Key != '/' && Key != '(' && Key != ')' && Key != '_' && Key != ' ');
		else if (Key == '(')
		{
			Bracket++;
			Str += Key;
			LastKey = Key;
			Operators = 0;
		}
		else if (Key == ')')
		{
			if (Bracket > 0 && Operators == 0)
			{
				Bracket--;
				Str += Key;
				LastKey = Key;
				Operators = 0;
			}
		}
		else if (Key == '+' || Key == '/' || Key == '*')
		{
			if (Operators == 0 && Str.size() > 0 && LastKey != '(' && LastKey != '.')
			{
				Str += Key;
				LastKey = Key;
				Operators++;
			}
		}
		else if (Key == '-')
		{
			if (LastKey != '.')
			{
				Str += Key;
				LastKey = Key;
				Operators++;
			}
		}
		else
		{
			Str += Key;
			LastKey = Key;
			Operators = 0;
		}
		pO->PrintMessage(Str);
	}

}


double Input::GetValue(Output* pO) const	// Reads a double value from the user 
{
	///TODO: add code to read a double value from the user and assign it to D
	pWind->FlushKeyQueue();
	double D = 0;
	
	//pO->PrintMessage("Please enter a value");
	string Str;
	bool Point = true;
	bool Neg = true;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	//ESCAPE key is pressed
			Str="0";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
		{
			if (Str.size() == 0)
				Str = "0";
			if (Str[0] == '-' && Str[1] == '.')
				Str = "0";
			break;
		}
		if (Key == 8)	//BackSpace is pressed
		{
			if (Str.size() != 0)
			{
				if (Str[Str.size() - 1] == '.')
					Point = true;
				if (Str.size() == 1)
					Neg = true;
				Str.resize(Str.size() - 1);
			}
		}
		if ((Key >= 48 && Key <= 57) || (Key == 46 && Point == true) || (Key == '-' && Neg == true))
		{
			Str += Key;
			if (Neg)
				Neg = false;
			if (Key == 46)
				Point = false;
		}
		pO->PrintMessage(Str);
	}
	
	const char* Value = Str.c_str();
	return atof(Value);
	//Read a double value from the user
	
	return D;
}


//ActionType Input::GetUserAction() const
//{	
//	//This function reads the position where the user clicks to determine the desired action
//
//	int x,y;
//	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
//
//	if(UI.AppMode == DESIGN )	//application is in design mode
//	{
//		//[1] If user clicks on the Toolbar
//		if ( y >= 0 && y < UI.TlBrWdth)
//		{	//Check whick Menu item was clicked
//			if( x >= 0 && x < UI.MnItWdth  )
//				return ADD_SMPL_ASSIGN;
//			if( x >= UI.MnItWdth && x < 2* UI.MnItWdth  )		
//				return ADD_CONDITION;
//			if( x >= UI.MnItWdth && x < 3* UI.MnItWdth  )		
//				return EXIT;
//
//			return DSN_TOOL;	//a click on empty part of the tool bar
//		
//		}
//		
//		//[2] User clicks on the drawing area
//		if ( y >= UI.TlBrWdth && y < UI.height - UI.StBrWdth)
//		{
//			return SELECT;	//user want to select/unselect a statement in the flowchart
//		}
//		
//		//[3] User clicks on the status bar
//		return STATUS;
//	}
//	else	//Application is in Simulation mode
//	{
//		return SIM_MODE;	//This should be changed after creating the compelete simulation bar 
//	}
//
//}
//

ActionType Input::GetUserAction() const
{	
	//This function reads the position where the user clicks to determine the desired action

	int x,y;
	clicktype Click;
	pWind->FlushMouseQueue();
	Click = pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(UI.AppMode == DESIGN )	//application is in design mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.TlBrWdth)
		{	
			//Check whick Menu item was clicked
			//This assumes that menu items are lined up horizontally
			int ClickedItem = (x / UI.MnItWdth) + (11 * ((2*y) / (UI.TlBrWdth)));
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
			switch (ClickedItem)
			{
			case ITM_SMPL_ASSIGN: return ADD_SMPL_ASSIGN;
			case ITM_VAR_ASSIGN: return ADD_VAR_ASSIGN;
			case ITM_OP_ASSIGN: return ADD_OP_ASSIGN;
			case ITM_COND: return ADD_CONDITION;
			case ITM_READ: return ADD_READ;
			case ITM_WRITE: return ADD_WRITE;
			case ITM_START: return ADD_START;
			case ITM_END: return ADD_END;
			case ITM_CONNECTOR: return ADD_CONNECTOR;
			case ITM_EDIT: return EDIT;
			case ITM_DEL: return DEL;
			case ITM_MOVE: return MOVE;
			case ITM_COMM: return COM;
			case ITM_COPY: return COPY;
			case ITM_CUT: return CUT;
			case ITM_PASTE: return PASTE;
			case ITM_SAVE: return SAVE;
			case ITM_LOAD: return LOAD;
			case ITM_MULTI_SELECT: return MULTI_SELECT;
			case ITM_SIM_MODE: return SIM_MODE;
			case ITM_UNREDO:
				if (Click == LEFT_CLICK)
					return UNDO;
				else
					return REDO;
				break;
			case ITM_EXIT: return EXIT;	
			default: return DSN_TOOL;
			}
		}
	
		//[2] User clicks on the drawing area
		if ( y >= UI.TlBrWdth && y < UI.height - UI.StBrWdth)
		{
			return SELECT;	//user want to select/unselect a statement in the flowchart
		}
		
		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//Application is in Simulation mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.TlBrWdth)
		{
			//Check whick Menu item was clicked
			//This assumes that menu items are lined up horizontally
			int ClickedItem = (x / UI.MnItWdth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
			switch (ClickedItem)
			{
			case ITM_VLDTE: return VALIDATE;
			case ITM_RUN: return RUN;
			case ITM_STP: return STEP;
			case ITM_GNRTE: return GENERATE;
			case ITM_DSN_MODE: return DSN_MODE;
			case ITM_EXIT2: return EXIT;
			default: return DSN_TOOL;
			}
		}

		else if (y >= UI.height - UI.StBrWdth)
			return STATUS;
		else
			return SIM_MODE;
	}


}
Input::~Input()
{
}
