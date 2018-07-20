#include"L164204(shape).h"
#include<math.h>
#include"GP142.H"

//***************SHAPE******************
Shape::Shape()
{
	list = NULL;
	nop = 0;
	color = -1;
}
//*******************POLYGON*************************
polygon::polygon(point * LOP, const int np, int c, int fc)
{
	list = LOP;
	nop = np+1;
	color = c;
	fillColor = fc;
}
polygon::polygon()
{
	list = NULL;
	nop = 0;
	color = -1;
	fillColor = -1;
}
void polygon::fill(point p,int color)
{
	if (p.x != -1 && p.y != -1)
	{
		int c = GP142_GetColor(p.x, p.y);
		bucketFill(p.x, p.y, c, color);
		F.x = p.x;
		F.y = p.y;
		fcol = color;
	}
}
string polygon::getName()
{
	return "POLYGON";
}
int polygon::getNumOfPoints()
{
	return nop;
}
int& polygon::getcolor()
{
	return color;
}
point*&polygon::getlist()
{
	return list;
}
void polygon::draw()
{
	for (int i = 0; i < nop-1  && nop-1 >1; i++)
	{
		GP142_lineXY(color, list[i].x, list[i].y, list[i + 1].x, list[i + 1].y, 2);
	}
	GP142_lineXY(color, list[nop-1].x, list[nop-1].y, list[0].x, list[0].y, 2);
}
bool polygon::containPoint(point p)
{
	int   i, j ;
	bool  check = false;
	for (i = 0,j = nop -1 ; i < nop; j = i++)
	{
		if (list[i].y<p.y && list[j].y >= p.y || list[j].y<p.y && list[i].y >= p.y)
		{
			if (list[i].x + (p.y - list[i].y) / ((list[j].y - list[i].y)*(list[j].x - list[i].x))<p.x)
			{
				check = !check;
			}
		}
		
	}
	return check;
}

//*******************RECTANGLE************************
rectangle::rectangle(point*LOP, int c, int fc)
{
	list = LOP;
	nop = 2;
	color = c;
	fillColor = fc;
}
void rectangle::draw()
{
	GP142_lineXY(color, list[0].x-1, list[0].y, list[1].x, list[0].y, 2);
	GP142_lineXY(color, list[1].x, list[0].y, list[1].x, list[1].y, 2);
	GP142_lineXY(color, list[1].x, list[1].y, list[0].x, list[1].y, 2);
	GP142_lineXY(color, list[0].x, list[1].y, list[0].x, list[0].y+1, 2);
}
string rectangle::getName()
{
	return "RECTANGLE";
}
int rectangle::getNumOfPoints()
{
	return nop;
}
int& rectangle::getcolor()
{
	return color;
}
point*&rectangle::getlist()
{
	return list;
}
void rectangle::fill(point p, int color)
{
	if (p.x != -1 && p.y != -1)
	{
		int c = GP142_GetColor(p.x, p.y);
		bucketFill(p.x, p.y, c, color);
		F.x = p.x;
		F.y = p.y;
		fcol = color;
	}
}
bool rectangle::containPoint(point p)
{
	return polygon::containPoint(p);
}
//*******************CIRCLE***************************
Circle::Circle(point* LOP, int c, int fc)
{
	list = LOP;
	color = c;
	fillColor = fc;
	nop = 2;
	double val = (LOP[1].x - LOP[0].x)*(LOP[1].x - LOP[0].x) + (LOP[1].y - LOP[0].y)*(LOP[1].y - LOP[0].y);
	radius = sqrt(val);
	
}
string Circle::getName()
{
	return "CIRCLE";
}
int Circle::getNumOfPoints()
{
	return nop;
}
int& Circle::getcolor()
{
	return color;
}
point*&Circle::getlist()
{
	return list;
}
void Circle::fill(point p, int color)
{
	if (p.x != -1 && p.y != -1)
	{
		int c = GP142_GetColor(p.x, p.y);
		bucketFill(p.x, p.y, c, color);
		F.x = p.x;
		F.y = p.y;
		fcol = color;
	}
}
void Circle::draw()
{
	GP142_circleXY(color, list->x, list->y, radius);
}
bool Circle::containPoint(point p)
{
	if (((p.x - list[0].x)*(p.x - list[0].x) + (p.y - list[0].y)*(p.y - list[0].y)) <= radius*radius)
		return true;
	return false;
}
//*******************LINE*****************************
Line::Line(point *LOP, int c, bool s)
{
	list = LOP;
	nop = 2;
	color = c;
	style = s;
}

string Line::getName()
{
	return "LINE";
}
int Line::getNumOfPoints()
{
	return nop;
}
int &Line::getcolor()
{
	return color;
}
point*&Line::getlist()
{
	return list;
}
void Line::fill(point p,int c)
{
	color = c;
	draw();
}
void Line::draw()
{
	if (style)
		GP142_lineXY(color, list[0].x, list[0].y, list[1].x, list[1].y, 2);
	else
		dottedLine(list[0].x,list[0].y, list[1].x,list[1].y, color);
}
bool Line::containPoint(point p)
{
	if (distance(p, list[0]) + distance(list[1], p) == distance(list[1], list[0]))
		return true;
	return false;
}
//*******************CURVE****************************
Curve::Curve(point *LOP, int np, int c, bool s)
{
	list = LOP;
	nop = np+1;
	color = c;
	style = s;
}
void Curve::fill(point p, int c)
{
	
	color = c;
	draw();
}
string Curve::getName()
{
	return "CURVE";
}
int Curve::getNumOfPoints()
{
	return nop;
}
int &Curve::getcolor()
{
	return color;
}
point*&Curve::getlist()
{
	return list;
}
void Curve::draw()
{
	if (style)
	{
		for (int i = 0; i < nop - 1 && nop - 1 >1; i++)
		{
			GP142_lineXY(color, list[i].x, list[i].y, list[i + 1].x, list[i + 1].y, 2);
		}
	}
	else
	{
		for (int i = 0; i<nop - 1 && nop - 1>1; i++)
		{
			dottedLine(list[i].x, list[i].y, list[i + 1].x, list[i + 1].y, color);
		}
	}
}
bool Curve::containPoint(point p)
{
	for (int i = 0; i < nop - 1; i++)
	{
		if (distance(p, list[i]) + distance(list[i+1], p) == distance(list[i+1], list[i]))
			return true;
	}
	return false;
} 
//*******************OPENSHAPE**********************
OpenShape::OpenShape()
{
	list = NULL;
	nop = 0;
	color = -1;
}

string OpenShape::getName()
{
	return "CURVE";
}
int OpenShape::getNumOfPoints()
{
	return nop;
}
int &OpenShape::getcolor()
{
	return color;
}
int OpenShape::distance(point a, point b)
{
	int val = (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
	int ans= sqrt(val);
	return ans;
}
point*&OpenShape::getlist()
{
	return list;
}
bool OpenShape::containPoint(point p)
{
	return 0;
}
void OpenShape::draw()
{

}
void OpenShape::fill(point p, int)
{

}
//*******************TEXT**********************
Text::Text(vector<char> arr, int c, point p, int s)
{
	
	size = s;
	sentence = new char[size+1];
	for ( int i= 0; i < size; i++)
	{
		sentence[i] = arr[i];
	}
	sentence[size] = '/0';
	color = c;
	list = new point;
	list[0] = p;
}
void Text::draw()
{
	char c[2] = { '/0' };
	int v = list[0].x;
	for (int i = 0; i < size; i++)
	{
		c[0] = sentence[i];
		GP142_textXY(color, v, list[0].y, 20, c);
		v += 13;
		if (c[0] == 'm' || c[0] == 'w' || c[0] == 'W' || c[0] == 'N' || c[0] == 'M')
			v += 5;
		if (c[0] == 'i' || c[0] == 'l' || c[0] == 'I' || c[0] == 'j')
			v -= 5;
	}
}
bool Text::containPoint(point p)
{
	if (p.x >= list[0].x && p.x <= (list[0].x + size * 13) && p.y >= list[0].y && p.y <= (list[0].y + 20))
	{
		return true;
	}
	return false;
}
void Text::fill(point p, int c)
{
	color = c;
	draw();

}