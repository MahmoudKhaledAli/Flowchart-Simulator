#include "Output.h"


Output::Output()
{
	//Initialize user interface parameters
	UI.width = 902;
	UI.height = 700;
	UI.wx = 15;
	UI.wy =15;

	UI.AppMode = DESIGN;	//Design Mode is the default mode

	UI.StBrWdth = 50;
	UI.TlBrWdth = 100;
	UI.MnItWdth = 82;

	UI.DrawClr = BLUE;
	UI.HiClr = RED;
	UI.MsgClr = RED;

	UI.ASSGN_WDTH = 150;
	UI.ASSGN_HI = 50;

	UI.COND_WDTH = 180;
	UI.COND_HI = 80;

	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Programming Techniques Project");
	
	pWind->SetPen(RED,3);
	CreateDesignToolBar();
	CreateStatusBar();
}


Input* Output::CreateInput()
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y)
{
	return new window(wd, h, x, y);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar()
{
	pWind->DrawLine(0, UI.height-UI.StBrWdth, UI.width, UI.height-UI.StBrWdth);

}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the Design Menu
void Output::CreateDesignToolBar()
{
	UI.AppMode = DESIGN;	//Design Mode
	int i=0;

	ClearToolBar();

	//fill the tool bar 
	//You can draw the tool bar icons in any way you want.
	pWind->DrawImage("images\\DesignToolBar.jpg", 0, 0);
	

	//Draw a line under the toolbar
	pWind->DrawLine(0, UI.TlBrWdth, UI.width, UI.TlBrWdth);	

}


void Output::CreateSimulationToolBar()
{
	UI.AppMode = SIMULATION;	//Simulation Mode
	///TODO: add code to create the simulation tool bar

	ClearToolBar();

	//fill the tool bar
	pWind->DrawImage("images\\SimToolBar.jpg", 0, 0);

	//Draw a line under the toolbar
	pWind->DrawLine(0, UI.TlBrWdth, UI.width, UI.TlBrWdth);

}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(RED, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.height - UI.StBrWdth, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearDrawArea()
{
	pWind->SetPen(RED, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.TlBrWdth, UI.width, UI.height - UI.StBrWdth);
	
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearToolBar()
{
	pWind->SetPen(RED, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.TlBrWdth);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::PrintMessage(string msg)	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgClr, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int) (UI.StBrWdth/1.5), msg);
}

void Output::PrintValue(double D)
{
	ClearStatusBar();

	//First clear the status bar

	pWind->SetPen(UI.MsgClr, 50);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawDouble(10, UI.height - (int)(UI.StBrWdth / 1.5), D);
}

//======================================================================================//
//								Statements Drawing Functions								//
//======================================================================================//

//Draw assignment statement and write the "Text" on it
void Output::DrawAssign(Point Left, int width, int height, string Text, bool Selected)
{
	if(Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HiClr,3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawClr,3);	//use normal color

	//Draw the statement block rectangle
	pWind->DrawRectangle(Left.x, Left.y, Left.x + width, Left.y + height);
		
	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Left.x+width/4-25, Left.y + height/4, Text);

}

void Output::DrawConditonalStat(Point Upper, int width, int height, string Text, bool Selected)
{
	int arrx[4];
	int arry[4];
	arrx[0] = Upper.x;
	arry[0] = Upper.y;
	arrx[1] = Upper.x + width / 2;
	arry[1] = Upper.y + height / 2;
	arrx[2] = Upper.x;
	arry[2] = Upper.y + height;
	arrx[3] = Upper.x - width / 2;
	arry[3] = Upper.y + height / 2;
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HiClr, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawClr, 3);	//use normal color
	//Draw the conditional block diamond
	pWind->DrawPolygon(arrx,arry,4);

	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Upper.x - width / 2 - 25, Upper.y + height / 2 - 20, "NO");
	pWind->DrawString(Upper.x + width / 2 + 2, Upper.y + height / 2 - 20, "YES");
	pWind->DrawString(Upper.x - width / 4, Upper.y + height / 3, Text);
}

void Output::DrawRead(Point Left, int width, int height, string Text, bool Selected)
{
	int arrx[4];
	int arry[4];
	arrx[0] = Left.x;
	arry[0] = Left.y;
	arrx[1] = arrx[0] + width;
	arrx[2] = arrx[1] - 10;
	arrx[3] = arrx[0] - 10;
	arry[1] = arry[0];
	arry[2] = arry[1] + height;
	arry[3] = arry[2];
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HiClr, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawClr, 3);	//use normal color

	pWind->DrawPolygon(arrx, arry, 4);
	pWind->DrawLine(arrx[0] - 30, arry[0],arrx[0],arry[0]);
	pWind->DrawLine(arrx[0] - 10, arry[0] - 10, arrx[0], arry[0]);
	pWind->DrawLine(arrx[0] - 10, arry[0] + 10, arrx[0], arry[0]);
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(arrx[0]+(width/4),arry[0]+(height/4), Text);

}

void Output::DrawWrite(Point Left, int width, int height, string Text, bool Selected)
{
	int arrx[4];
	int arry[4];
	arrx[0] = Left.x;
	arry[0] = Left.y;
	arrx[1] = arrx[0] + width;
	arrx[2] = arrx[1] - 10;
	arrx[3] = arrx[0] - 10;
	arry[1] = arry[0];
	arry[2] = arry[1] + height;
	arry[3] = arry[2];
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HiClr, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawClr, 3);	//use normal color

	pWind->DrawPolygon(arrx, arry, 4);
	pWind->DrawLine(arrx[2], arry[2], arrx[2]+30, arry[2]);
	pWind->DrawLine(arrx[2]  + 20 , arry[2] -10, arrx[2] + 30, arry[2]);
	pWind->DrawLine(arrx[2] +20, arry[2] + 10, arrx[2] + 30, arry[2]);
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(arrx[0] + (width / 4), arry[0] + (height / 4), Text);
}

void Output::DrawStart(Point Center, int width, int height, bool Selected)
{
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HiClr, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawClr, 3);	//use normal color
	pWind->DrawEllipse(Center.x - width / 2, Center.y - height / 2, Center.x + width / 2, Center.y + height / 2);
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Center.x - width / 6, Center.y-4, "Start");
}

void Output::DrawEnd(Point Center, int width, int height, bool Selected)
{

	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HiClr, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawClr, 3);	//use normal color
	pWind->DrawEllipse(Center.x - width / 2, Center.y - height / 2, Center.x + width / 2, Center.y + height / 2);
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Center.x - width / 6, Center.y - 4, "End");
}

void Output::DrawConnector(Point Start, Point End, bool Selected)
{
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HiClr, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawClr, 3);	//use normal color
	pWind->DrawLine(Start.x,Start.y,End.x,Start.y);
	pWind->DrawLine(End.x,Start.y,End.x,End.y);

	if (Start.y <= End.y)
	{
		pWind->DrawLine(End.x - 10, End.y - 10, End.x, End.y);
		pWind->DrawLine(End.x + 10, End.y - 10, End.x, End.y);
	}
	
	else
	{
		pWind->DrawLine(End.x, End.y, End.x - 10, End.y + 10);
		pWind->DrawLine(End.x, End.y, End.x + 10, End.y + 10);
	}


}

//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}

void Output::DrawOutput(int Count, string Out)
{
	pWind->SetPen(UI.HiClr, 3);
	pWind->DrawString(2, UI.TlBrWdth + Count * 15 - 10, Out);
}

void Output::DrawWatch(int Count, string Out)
{
	pWind->SetPen(UI.DrawClr, 3);
	int Eq = 0;
	for (int i = 0; i < Out.size(); i++)
	{
		if (Out[i] == '=')
			Eq = i;
	}
	string O = Out.substr(0, Eq);
	int W;
	int H;
	int WClear;
	pWind->GetStringSize(WClear, H, O + "= 0.999999");
	pWind->GetStringSize(W, H, Out);
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(UI.width - (WClear + 20), UI.TlBrWdth + Count * 15 + 2, UI.width, UI.TlBrWdth + Count * 15 + 18);
	pWind->SetPen(UI.DrawClr, 3);
	pWind->DrawString(UI.width - (W + 20), UI.TlBrWdth + Count * 15 + 2, Out);
}

void Output::ClearWatch(int Count, string Out)
{
	pWind->SetPen(UI.DrawClr, 3);
	int Eq = 0;
	for (int i = 0; i < Out.size(); i++)
	{
		if (Out[i] == '=')
			Eq = i;
	}
	string O = Out.substr(0, Eq);
	int W;
	int H;
	int WClear;
	pWind->GetStringSize(WClear, H, O + "= 0.999999");
	pWind->GetStringSize(W, H, Out);
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(UI.width - (WClear + 20), UI.TlBrWdth + Count * 15 + 2, UI.width, UI.TlBrWdth + Count * 15 + 18);
}

//
//void Output::CreateOutputWindow()
//{
//	pWindOut = new window(700, 700, 15, 15);
//	pWindOut->ChangeTitle("Simulation Output");
//}
//
//void Output::CloseOutputWindow()
//{
//	delete pWindOut;
//}
//
//void Output::PrintOutput(string Out)
//{
//	pWindOut->SetPen(UI.MsgClr, 50);
//	pWindOut->SetFont(20, BOLD, BY_NAME, "Arial");
//	pWindOut->DrawString(10, 10, Out);
//}