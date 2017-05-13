#include "Step.h"
#include "..\Statements\Write.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Step::Step(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void Step::ReadActionParameters()
{
	//No input needed from user to simullate the flow chart
}

void Step::Execute()
{
	ReadActionParameters();
	pManager->GetOutput()->ClearDrawArea();
	pManager->UpdateInterface();
	Validate ValAction(pManager);
	ValAction.Execute();
	if (!ValAction.IsValid())
		return;
	//Creating the validate action and stopping if the chart is not valid
	pManager->GetOutput()->ClearStatusBar();
	ofstream OutputFile; //Ofstream for the output file
	string FileName; //Desired name of the input file
	OutputFile.open("IO Files\\Output.txt"); //opening the output file
	pManager->GetOutput()->ClearStatusBar();
	//Asking the user if the input will be taken from the screen or a file
	pManager->GetOutput()->PrintMessage("Do you want to read input from the screen or from a file (1-File/2-Screen):");
	int Choice = int(pManager->GetInput()->GetValue(pManager->GetOutput()));
	if (Choice == 1)
	{
		//reading the file name from the user
		pManager->GetOutput()->PrintMessage("Enter Filename: ");
		FileName = pManager->GetInput()->GetString(pManager->GetOutput());
	}
	else
		Choice = 2;
	pManager->GetOutput()->ClearStatusBar();
	ifstream InputFile; //Stream for the input file
	//Opening the file with the chosen filename
	InputFile.open("IO Files\\" + FileName + ".txt");
	int StatCount = pManager->GetStatCount();
	int ConnCount = pManager->GetConnCount();
	Statement * const * StatList = pManager->GetStatList();
	Connector * const * ConnList = pManager->GetConList();
	unordered_map<string, double> Variables; //List of all variables using a map
	Variables.reserve(StatCount);
	ostringstream OutputString;
	Statement *pStat;
	//Searching for the start statement
	for (int i = 0; i < StatCount; i++)
	{
		pStat = StatList[i];
		if (dynamic_cast<Start*>(pStat))
			break;
	}
	//Validity of the simulation
	bool Valid = true;

	Point Click; //user input
	int ClickedItm; //number of clicked itm
	bool Stop = false; //True if the user choses to stop the simulation
	bool Continue = false; //True if the user choses to continue the simulation and exit step by step mode
	bool StepByStep = true; //True if the simulation is in step by step mode
	int Count = 0; //Count of number of lines of output
	int CountW; //Count of number of lines of the watch
	ostringstream Watch;
	while (pStat && Valid && !Stop)
	{
		if (StepByStep) //If the simulation is in step by step mode
		{
			//Making the current statement selected and drawing it
			pStat->SetSelected(true);
			pStat->Draw(pManager->GetOutput());
		}
		//Setting continue to false
		Continue = false;
		while (!Continue && StepByStep)
		{
			pManager->GetInput()->GetPointClicked(Click);
			//Getting user input
			ClickedItm = Click.x / UI.MnItWdth;
			if (Click.y < 100 && ClickedItm > 0 && ClickedItm < 4)
			{
				switch (ClickedItm)
				{
					//If the user choses to continue the simulation
				case ITM_RUN:
					StepByStep = false;
					pStat->SetSelected(false);
					pStat->Draw(pManager->GetOutput());
					break;

					//if the user choses to continue to next step
				case ITM_STP:
					Continue = true;
					pStat->SetSelected(false); //deselecting the statement
					pStat->Draw(pManager->GetOutput());
					break;

					//if the user choses to stop the simulation
				case ITM_STOP:
					Stop = true;
					Continue = true;
					StepByStep = false;
					pStat->SetSelected(false);
					pStat->Draw(pManager->GetOutput());
					break;

					//if no valid input is given
				default:
					pStat->SetSelected(false);
					pStat->Draw(pManager->GetOutput());
					break;
				}

			}
		}
		//If the user didn't chose to stop
		if (!Stop)
		{
			CountW = 0;
			//Simulating th next statement
			pStat = pStat->GetNextStatement(pStat->Simulate(pManager->GetOutput(), pManager->GetInput(), Valid, Variables, OutputString, InputFile, Choice));
			if (Valid)
				//Drawing the output string
				pManager->GetOutput()->DrawOutput(Count, OutputString.str());
			else
			{
				//If the user chose to stop the app is no longer in step by step mode
				StepByStep = false;
			}
			//If it's a write statement increase the number of lines in the output
			if (dynamic_cast<Write*>(pStat))
				Count++;
			//Clearing the string
			OutputString.str("");
			OutputString.clear();
			//If still in step by step mode
			if (StepByStep)
			{
				//Looping through the map of variables and displaying its value in the watch
				for (auto& x : Variables)
				{
					Watch << x.first << " = " << x.second;
					pManager->GetOutput()->DrawWatch(CountW++, Watch.str());
					Watch.str("");
					Watch.clear();
				}
			}
			//If not is step by step mode we clear the watch by sending it an empty string
			else
			{
				for (auto& x : Variables)
				{
					Watch << x.first << " = " << x.second;
					pManager->GetOutput()->ClearWatch(CountW++, Watch.str());
					Watch.str("");
					Watch.clear();
				}
			}
		}
		//If the user didn't chose to stop we print the watch as well
		else
		{
			CountW = 0;
			for (auto& x : Variables)
			{
				Watch << x.first << " = " << x.second;
				pManager->GetOutput()->ClearWatch(CountW++, Watch.str());
				Watch.str("");
				Watch.clear();
			}
		}

	}
	//If the simulation was valid we display the output string
	if (Valid && !Stop)
	{
		pManager->GetOutput()->PrintMessage(OutputString.str());
		pManager->GetOutput()->PrintMessage("Output File Saved to: IO Files\\Output.txt");
	}
	Variables.clear();
	OutputFile.close();
	InputFile.close();
}