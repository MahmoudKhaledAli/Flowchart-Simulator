#include "Connector.h"
#include "..\ApplicationManager.h"
#include "..\Statements\Cond.h"
#include "..\Statements\End.h"
#include "..\Statements\Start.h"

Connector::Connector(Statement* Src, Statement* Dst, Point Start, Point End)
//When a connector is created, it must have a source statement and a destination statement
//There are no free connectors in the folwchart
{
	SetAll(Src, Dst, Start, End);
}

void Connector::SetAll(Statement* Src, Statement* Dst, Point Start, Point End)
{
	SrcStat = Src;
	DstStat = Dst;
	this->StartPt = Start;
	this->EndPt = End;
	Selected = false;
}

void Connector::setSrcStat(Statement *Src)
{	SrcStat = Src;	}

Statement* Connector::getSrcStat()
{	return SrcStat;	}

void Connector::setDstStat(Statement *Dst)
{	DstStat = Dst;	}

Statement* Connector::getDstStat()
{	return DstStat;	}


void Connector::setStartPoint(Point P)
{	StartPt = P;	}

Point Connector::getStartPoint() const
{	return StartPt;	}

void Connector::setEndPoint(Point P)
{	EndPt = P;	}

Point Connector::getEndPoint() const
{	return EndPt;	}

bool Connector::IsSelected() const
{	return Selected; }

void Connector::Draw(Output* pOut) const
{
	///TODO: Call output to draw a connector from SrcStat to DstStat on the output window
	pOut->DrawConnector(StartPt, EndPt, Selected);
}

bool Connector::InRange(Point P) const
{
	if (StartPt.x > EndPt.x)
	{
		if (StartPt.y > EndPt.y)
		{
			return((P.x <= StartPt.x && P.x >= EndPt.x && (P.y >= StartPt.y - 3 && P.y <= StartPt.y + 3)) || (P.y <= StartPt.y && P.y >= EndPt.y && (P.x >= EndPt.x - 3 && P.x <= EndPt.x + 3)));
		}
		else
			return((P.x <= StartPt.x && P.x >= EndPt.x && (P.y >= StartPt.y - 3 && P.y <= StartPt.y + 3)) || (P.y >= StartPt.y && P.y <= EndPt.y && (P.x >= EndPt.x - 3 && P.x <= EndPt.x + 3)));
	}
	else
	{
		if (StartPt.y > EndPt.y)
			return((P.x >= StartPt.x && P.x <= EndPt.x && (P.y >= StartPt.y - 3 && P.y <= StartPt.y + 3)) || (P.y <= StartPt.y && P.y >= EndPt.y && (P.x >= EndPt.x - 3 && P.x <= EndPt.x + 3)));
		else
			return((P.x >= StartPt.x && P.x <= EndPt.x && (P.y >= StartPt.y - 3 && P.y <= StartPt.y + 3)) || (P.y >= StartPt.y && P.y <= EndPt.y && (P.x >= EndPt.x - 3 && P.x <= EndPt.x + 3)));
	}
}

void Connector::Edit(Point St, Point En, Statement* Src, Statement* Dest)
{
	StartPt = St;
	EndPt = En;
	SrcStat = Src;
	DstStat = Dest;
}

void Connector::SetSelected(bool T)
{
	Selected = T;
}

void Connector::Save(ofstream&file)
{
	file << SrcStat->GetID() << "    " << DstStat->GetID() << "    ";
	Cond* ptr = dynamic_cast<Cond*>(SrcStat);
	if (ptr != NULL)
	{
		if (ptr->GetYesConn() == this)
		{
			file << 1;
		}
		else
		{
			file << 2;
		}
	}
	else{ file << 0; }
	file << endl;
}

void Connector::UpdatePoints()
{	

	if(this->SrcStat->IsSelected())
	{
		if(dynamic_cast<Cond*>(SrcStat)!=NULL)
		{
			Cond*conditional=dynamic_cast<Cond*>(SrcStat);
			if(conditional->GetYesConn()==this)
			{
				StartPt=conditional->GetYesOutlet();
			}
			else
			{
				StartPt=conditional->GetNoOutlet();
			}
		}
		else
		{
			StartPt=SrcStat->GetOutlet(); // except end
		}
	}
	if(this->DstStat->IsSelected())
	{
		EndPt=DstStat->GetInlet(); //except start
	}
}