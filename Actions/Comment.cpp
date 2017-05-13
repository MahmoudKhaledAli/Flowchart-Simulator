#include "Comment.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Comment::Comment(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void Comment::ReadActionParameters()
{
	pManager->GetOutput()->ClearStatusBar();
	
	if (pManager->GetSelectedStatement()) //If only one statement is selected
	{
		//Reading the comment from the user
		pManager->GetOutput()->PrintMessage("Enter Comment: ");
		Com = pManager->GetInput()->GetString(pManager->GetOutput());
	}
}

void Comment::Execute()
{
	ReadActionParameters();

	if (pManager->GetSelectedStatement())
	{
		pManager->GetSelectedStatement()->SetSelected(false); //De-selecting the statement after commenting on it
		pManager->GetSelectedStatement()->SetCom(Com); //Setting the comment in the statement
		pManager->SetSelectedStatement(NULL); //No statement is selected now
	}

}