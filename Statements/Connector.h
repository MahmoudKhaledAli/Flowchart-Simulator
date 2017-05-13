#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "..\GUI\UI_Info.h"
#include "..\GUI\output.h"

class Statement;
class ApplicationManager;
class Cond;
class End;
class Start;

class Connector	//a connector that connects two statements (Source & Destination)
{
private:
	bool Selected; //If the connector is selected
	Statement *SrcStat;	//The source statement of the connector
	Statement *DstStat;	//The destination statement of the connector
	Point StartPt;	//Start point of the connector
	Point EndPt;		//End point of the connector
public:
	Connector(){}
	Connector(Statement* Src, Statement* Dst, Point, Point);
	void SetAll(Statement* Src, Statement* Dst, Point, Point);

	void		setSrcStat(Statement *Src);
	Statement*	getSrcStat();	
	void		setDstStat(Statement *Dst);
	Statement*	getDstStat();

	void setStartPoint(Point P);
	Point getStartPoint() const;

	void setEndPoint(Point P);
	Point getEndPoint() const;

	void Draw(Output* pOut) const;

	bool InRange(Point P) const;
	bool IsSelected() const;
	void SetSelected(bool);

	void Edit(Point, Point, Statement*, Statement*);

	void Save(ofstream &);
	
	void UpdatePoints();
};

#endif