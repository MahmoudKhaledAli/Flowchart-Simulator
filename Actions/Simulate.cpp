#include "Simulate.h"
#include "..\Statements\Write.h"


#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Simulate::Simulate(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void Simulate::ReadActionParameters()
{
	//No input needed from user to simullate the flow chart
}

void Simulate::Execute()
{
	ReadActionParameters();
	pManager->GetOutput()->ClearDrawArea();
	pManager->UpdateInterface();
	//Creating a validate action
	Validate ValAction(pManager);
	ValAction.Execute();
	if (!ValAction.IsValid())
		return;
	//If the chart is not valid, it can't be simulated
//	pManager->GetOutput()->CreateOutputWindow();
	ofstream OutputFile; //ofstream for the output file
	string FileName; //Desired Name of the input file
	OutputFile.open("IO Files\\Output.txt"); //Opening the output file
	pManager->GetOutput()->ClearStatusBar();
	//Asking the user if the input should be taken from the screen or from a file
	pManager->GetOutput()->PrintMessage("Do you want to read input from the screen or from a file (1-File/2-Screen):");
	int Choice = int(pManager->GetInput()->GetValue(pManager->GetOutput()));
	if (Choice == 1)
	{
		//If the user choses a file, we get the name of the file to be loaded
		pManager->GetOutput()->PrintMessage("Enter Filename: ");
		FileName = pManager->GetInput()->GetString(pManager->GetOutput());
	}
	else
		Choice = 2;
	pManager->GetOutput()->ClearStatusBar();
	ifstream InputFile; //Stream for the input file
	//Opening the file with the file name chosen
	InputFile.open("IO Files\\" + FileName + ".txt");
	int StatCount = pManager->GetStatCount();
	int ConnCount = pManager->GetConnCount();
	Statement * const * StatList = pManager->GetStatList();
	Connector * const * ConnList = pManager->GetConList();
	unordered_map<string, double> Variables; //List of all variables using a map
	Variables.reserve(StatCount);
	ostringstream OutputString;
	Statement *pStat;
	//Search for the start statement to begin the simulation
	for (int i = 0; i < StatCount; i++)
	{
		pStat = StatList[i];
		if (dynamic_cast<Start*>(pStat))
			break;
	}
	//To check for the validity of the simulation
	bool Valid = true;
	//Count to be used in producing the output
	int Count = 0;
	Statement* pStatPrev;

	while (pStat && Valid)
	{
		pStatPrev = pStat;
		//Simulating the statement and chosing the next statement to simulate based on its result
		pStat = pStat->GetNextStatement(pStat->Simulate(pManager->GetOutput(), pManager->GetInput(), Valid, Variables, OutputString, InputFile, Choice));
		if (Valid)
		{
			//If the simulation is still valid we produce the output
			pManager->GetOutput()->DrawOutput(Count, OutputString.str());
			OutputFile << OutputString.str(); //Each time we add the produced string to the output file
			if (dynamic_cast<Write*>(pStatPrev))
				OutputFile << endl; //we only go to a new line if the statement was a write statement
		}
		if (dynamic_cast<Write*>(pStat)) //If the last statement was a write statement we increment the count of number of lines of the output
			Count++;
		OutputString.str(""); //Clearing the produced string
		OutputString.clear();
	}
	ostringstream Watch;
	int CountW = 0;
	if (Valid)
	{
		pManager->GetOutput()->PrintMessage("Output File Saved to: IO Files\\Output.txt");
		for (auto& x : Variables)
		{
			Watch << x.first << " = " << x.second;
			pManager->GetOutput()->DrawWatch(CountW++, Watch.str());
			Watch.str("");
			Watch.clear();
		}
	}
	Variables.clear(); //Clearing the map of variables
	OutputFile.close(); //Closing both files
	InputFile.close();
//	Point P;
//	pManager->GetInput()->GetPointClickedSim();
//	pManager->GetOutput()->CloseOutputWindow();
}

