#include "Generate.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Generate::Generate(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void Generate::ReadActionParameters()
{
	//No input needed from user to simullate the flow chart
}

void Generate::Execute()
{
	ReadActionParameters();
	//Creating a validate action first
	Validate ValAction(pManager);
	ValAction.Execute();
	//If the chart is invalid, no code can be generated
	if (!ValAction.IsValid())
		return;
	pManager->GetOutput()->ClearStatusBar();
	int StatCount = pManager->GetStatCount();
	int ConnCount = pManager->GetConnCount();
	Statement * const * StatList = pManager->GetStatList();
	Connector * const * ConnList = pManager->GetConList();
	Statement *pStat;
	//Looping through the statements to find the start statement
	for (int i = 0; i < StatCount; i++)
	{
		pStat = StatList[i];
		if (dynamic_cast<Start*>(pStat))
			break;
	}
	//The code file to be saved
	ofstream CodeFile;
	//The ostringstream passed as a parameter to the virtual function GenerateCode
	ostringstream Code;
	//Opening the code file
	CodeFile.open("Generated Code\\C++ Code.txt");
	CodeFile << "#include <iostream>" << endl << "using namespace std;" << endl << endl;
	if (pStat->GetCom() != "")
		CodeFile << "//" + pStat->GetCom() << endl;
	CodeFile << "void main()" << endl << "{" << endl;
	unordered_map<string, double> Variables; //List of all variables using a map for declaration
	Variables.reserve(StatCount);
	for (int i = 0; i < StatCount; i++)
	{
		StatList[i]->DeclareVariable(Code, Variables);
	}
	Variables.clear(); //Map no longer needed after declaring the variables
	int Indent = 1; //The Original indent of the code is one tab character
	while (pStat)
	{
		pStat = pStat->GenerateCode(Code, Indent); //Calling the virtual function GenerateCode of each statement
	}

	for (int i = 0; i < StatCount; i++)
	{
		StatList[i]->SetGenerating(false); //After finishing we make sure that Generating is false for all statements in case we want to generate again
	}

	CodeFile << Code.str() << "\n}";
	//Closing the code file
	CodeFile.close();
	pManager->GetOutput()->PrintMessage("C++ Code File Saved to GeneratedCode\\C++ Code.txt");
}