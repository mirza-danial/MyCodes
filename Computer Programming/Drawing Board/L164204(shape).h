#include<string>
#include<vector>
using namespace std;
struct point{
	int x=-1;
	int y=-1;
};

class Shape
{
protected:
	string name;
	point*list;
	int color;
	int nop;
	point F;
	int fcol;
public:
	Shape();
	virtual string getName() = 0;
	virtual point*& getlist() = 0;
	virtual int& getcolor() = 0;
	virtual int getFx() = 0;
	virtual int getFy() = 0;
	virtual int getfcol() = 0;
	virtual int getNumOfPoints() = 0;
	virtual void draw()=0;
	virtual char* getsentence()=0 ;
	virtual bool containPoint(point)=0;
	virtual void fill(point p, int color)=0;

};


class polygon : public Shape
{
protected:
	int fillColor;
public:
	polygon();
	char* getsentence(){ return "\0"; }
	string getName();
	point*& getlist();
	int getFx(){ return F.x; }
	int getFy(){ return F.y; }
	int getfcol(){ return fcol; }
	int& getcolor();
	int getNumOfPoints();
	polygon(point * LOP,const int np, int c, int fc);
	void fill(point p,int color);
	void draw();
	bool containPoint(point);
};


class OpenShape : public Shape 
{
protected:
	bool style;
public:
	OpenShape();
	string getName();
	char* getsentence(){ return "\0"; }
	int distance(point a, point b);
	point*& getlist();
	int getFx(){ return F.x; }
	int getFy(){ return F.y; }
	int getfcol(){ return fcol; }
	int getNumOfPoints();
	int &getcolor();
	void fill(point p,int color) ;
	void draw();
	bool containPoint(point);
};


class Text : public Shape
{
	int size;
	char *sentence;
public:
	Text(vector<char>arr, int c, point p, int s);
	char* getsentence(){ return sentence; }
	int& getcolor(){ return color; }
	string getName(){ return "TEXT"; }
	int getFx(){ return F.x; }
	int getFy(){ return F.y; }
	int getfcol(){ return fcol; }
	point*& getlist(){ return list; }
	void fill(point p, int color);
	int getNumOfPoints(){ return size; }
	void draw();
	bool containPoint(point p);
};


class Circle : public Shape
{
	int fillColor;
	double radius;
public:
	Circle(point* LOP, int c, int fc);
	char* getsentence(){ return "\0"; }
	int& getcolor();
	string getName();
	int getFx(){ return F.x; }
	int getFy(){ return F.y; }
	int getfcol(){ return fcol; }
	int getNumOfPoints();
	point*& getlist();
	void fill(point p, int color);
	void draw();
	bool containPoint(point);
};


class rectangle : public polygon
{

public:
	int &getcolor();
	rectangle(point*LOP,int c, int fc);
	char* getsentence(){ return "\0"; }
	void draw();
	string getName();
	int getFx(){ return F.x; }
	int getFy(){ return F.y; }
	int getfcol(){ return fcol; }
	int getNumOfPoints();
	point*& getlist();
	void fill(point p, int color);
	bool containPoint(point);
};
class Line : public OpenShape
{
public:
	int &getcolor();
	
	Line(point *LOP, int c, bool s);
	void fill(point p,int color) ;
	char* getsentence(){ return "\0"; }
	void draw();
	int getNumOfPoints();
	int getFx(){ return F.x; }
	int getFy(){ return F.y; }
	int getfcol(){ return fcol; }
	string getName();
	point*& getlist();
	bool containPoint(point);
};

class Curve : public OpenShape
{
public:
	Curve(point *LOP,int np, int c, bool s);
	int &getcolor();
	void fill(point p, int);
	void draw();
	char* getsentence(){ return "\0"; }
	int getFx(){ return F.x; }
	int getFy(){ return F.y; }
	int getfcol(){ return fcol; }
	int getNumOfPoints();
	string getName();
	point*& getlist();
	bool containPoint(point);
};