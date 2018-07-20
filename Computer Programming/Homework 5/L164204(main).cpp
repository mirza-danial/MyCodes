#include<iostream>
#include"L164204(shape).h"
#include<math.h>
#include<fstream>
#include"gp142.h"
#include<vector>
using namespace std;
#define px -680				//button menu upper right corner
#define py 330
#define cx 650				//color menu center
#define cy 280
#define cd 25				//difference after each circle
#define cr 10				// radius of each circle
#define FALSE 0
#define TRUE  1
Shape** allShapes = new Shape*[1];		//Main AllShapes Array
int tsize = 1;							//Total size of allShapes
int fsize = 0;							//Filled size of allShapes
bool Outside(point mouse)		// Function to check whether point is out of allowed screen or not
{
	if (mouse.x<px + 70 || mouse.x>cx - 50 || mouse.y < py - 650 || mouse.y >py)
		return true;
	return false;
}
void extendArray(point*&obj, int &size, int& fsize)		//extends points array 
{
	point*newArr = new point[size * 2];
	for (int i = 0; i < fsize; i++)
	{
		newArr[i] = obj[i];
	}
	delete obj;
	obj = newArr;
	size = 2 * size;
}
void extendAllShapes(Shape**&obj, int &size, int& fsize)	//extends allShapes array 
{
	Shape**newArr = new Shape*[size * 2];
	for (int i = 0; i < fsize; i++)
	{
		newArr[i] = obj[i];
	}
	delete[]obj;
	obj = newArr;
	size = 2 * size;
}
void shrinkAllShapes(Shape**&obj, int &size,int &fsize, int& index)		//Shrinks Allshapes array by deleteing particular shape
{
	Shape**newArr = new Shape*[size];
	int i,j=0;
	for ( i = 0; i < index; i++)
	{
		newArr[j] = obj[i];
		j++;
	}
	
	for (i = index + 1; i < fsize; i++)
	{
		newArr[j] = obj[i];
		j++;
	}
	delete obj[index];
	delete[] obj;
	
	obj = newArr;
	fsize--;
}
void Load()			//Loads file
{
	ifstream fin;
	int Fx, Fy, FCOL;
	fin.open("drawing.pb");
	string name,fazool;
	vector<char> ch;
	char sent[500];
	int c; int np;
	int s = 0;
	point*p;
	while (getline(fin, name))
	{
		
		fin >> c;
		getline(fin, fazool);
		fin >> np;
		getline(fin, fazool);
		if (name == "TEXT")
		{
			fin.getline(sent, 500);
			for (int i = 0; i < np; i++)
			{
				ch.push_back(sent[i]);
			}
			s = np;
			np = 1;
		}
		p = new point[np];
		for (int i = 0; i < np; i++)
		{
			fin >> p[i].x;
			getline(fin, fazool);
			fin >> p[i].y;
			getline(fin, fazool);
		}
		fin >> Fx;
		getline(fin, fazool);
		fin >> Fy;
		getline(fin, fazool);
		fin >> FCOL;
		getline(fin, fazool);
		if (fsize == tsize)
		{
			extendAllShapes(allShapes, tsize, fsize);
		}
		if (name == "RECTANGLE")
		{
			allShapes[fsize] = new rectangle(p, c, 0);
			allShapes[fsize]->draw();
			if (Fx != -1 || Fy != -1)
			{
				point r;
				r.x = Fx, r.y = Fy;
				allShapes[fsize]->fill(r, FCOL);
			}
			fsize++;
		}
		else if (name == "LINE")
		{
			allShapes[fsize] = new Line(p, c, 1);
			allShapes[fsize]->draw();
			if (Fx != -1 || Fy != -1)
			{
				point r;
				r.x = Fx, r.y = Fy;
				allShapes[fsize]->fill(r, FCOL);
			}
			fsize++;
		}
		else if (name == "CURVE")
		{
			allShapes[fsize] = new Curve(p, np-1, c, 1);
			allShapes[fsize]->draw();
			if (Fx != -1 || Fy != -1)
			{
				point r;
				r.x = Fx, r.y = Fy;
				allShapes[fsize]->fill(r, FCOL);
			}
			fsize++;
		}
		else if (name == "POLYGON")
		{
			allShapes[fsize] = new polygon(p, np-1, c, 0);
			allShapes[fsize]->draw();
			if (Fx != -1 || Fy != -1)
			{
				point r;
				r.x = Fx, r.y = Fy;
				allShapes[fsize]->fill(r, FCOL);
			}
			fsize++;
		}
		else if (name == "CIRCLE")
		{
			allShapes[fsize] = new Circle(p,c,0);
			allShapes[fsize]->draw();
			if (Fx != -1 || Fy != -1)
			{
				point r;
				r.x = Fx, r.y = Fy;
				allShapes[fsize]->fill(r, FCOL);
			}
			fsize++;
		}
		else if (name == "TEXT")
		{
			allShapes[fsize] = new Text(ch, c, p[0], s);
			allShapes[fsize]->draw();
			fsize++;
			for (int i = 0; i < s; i++)
			{
				ch.pop_back();
			}
		}
	}

}
void createWindow()			//Creates window and buttons menu
{

	int y1 = py;
	for (int i = 0; i < 650; i++)
	{
		GP142_lineXY(WHITE, px + 70, y1, cx - 50, y1, 1);
		y1--;
	}
	point cord,a;
	cord.x = px; cord.y = py;
	int val=50;
	for (int i = 0; i < 11; i++)
	{
		a.x = cord.x + val; a.y = cord.y - val;
		GP142_rectangleXY(22, cord.x, cord.y,a.x,a.y, 4);
		bucketFill(cord.x + 2, cord.y - 2, 0, 1);
		if (i == 0)
		{
			GP142_rectangleXY(0, cord.x + 10, cord.y - 15, a.x - 10, a.y + 15, 2);
		}
		else if (i == 1)
		{
			GP142_circleXY(0, cord.x + 25, cord.y - 25, 10);
		}
		else if (i == 2)
		{
			GP142_lineXY(0, cord.x + 10, cord.y - 10, a.x - 10, a.y + 10, 2);
		}
		else if (i == 3)
		{
			GP142_lineXY(0, cord.x + 10, cord.y - 10, cord.x + 20, cord.y - 20, 2);
			GP142_lineXY(0, cord.x + 20, cord.y - 20,cord.x+30,cord.y-20,2);
			GP142_lineXY(0, cord.x + 30, cord.y - 20, a.x - 10, a.y + 15, 2);
		}
		else if (i == 4)
		{
			GP142_lineXY(0, cord.x + 20, cord.y - 20, cord.x + 30, cord.y - 20, 2);
			GP142_lineXY(0, cord.x + 30, cord.y - 20, a.x - 10, a.y + 15, 2);
			GP142_lineXY(0, a.x - 10, a.y + 15, cord.x + 10, cord.y - 40, 2);
			GP142_lineXY(0, cord.x + 10, cord.y - 40, cord.x + 20, cord.y - 20, 2);
		}
		else if (i == 5)
		{
			GP142_textXY(0, cord.x + 18, cord.y - 40 ,25,"T");
		}
		else if (i == 6)
		{
			GP142_textXY(0, cord.x + 18, cord.y - 40, 25, "B");
		}
		else if (i == 7)
		{
			GP142_textXY(0, cord.x + 18, cord.y - 40, 25, "E");
		}
		else if (i == 8)
		{
			GP142_textXY(0, cord.x + 18, cord.y - 40, 25, "S");
		}
		else if (i == 9)
		{
			dottedLine( cord.x + 10, cord.y - 10, a.x - 10, a.y + 10,0 );
		}
		else if (i == 10)
		{
			dottedLine(cord.x + 10, cord.y - 10, cord.x + 20, cord.y - 20, 0);
			dottedLine(cord.x + 20, cord.y - 20, cord.x + 30, cord.y - 20, 0);
			dottedLine(cord.x + 30, cord.y - 20, a.x - 10, a.y + 15, 0);
		}
		cord.y -= val+10;
	}
	point b;
	b.x = cx; b.y = cy;
	for (int i = 0; i < 24; i++)
	{
		GP142_circleXY(1, b.x, b.y, cr);
		bucketFill(b.x, b.y,0 ,i );
		b.y -= cd;
	}
	GP142_circleXY(1, cx, cy + 40, cr+10);
}
bool insideCircle( point p,int c_x,int c_y, int r)	//checks a point is inside circle or not , used while changing color
{
	if (((p.x - c_x)*(p.x - c_x) + (p.y - c_y)*(p.y - c_y)) <= r*r)
		return true;
	return false;
}
void message()					// prints a message in the begining
{
	int a = -200, b = 100,var=13;
	GP142_textXY(WHITE, a+var*0, b, 20, "D");
	GP142_textXY(WHITE, a + var * 1, 100, 20, "o");
	GP142_textXY(WHITE, a + var * 2, 100, 20, " ");
	GP142_textXY(WHITE, a + var * 3, 100, 20, "Y");
	GP142_textXY(WHITE, a + var * 4, 100, 20, "o");
	GP142_textXY(WHITE, a + var * 5, 100, 20, "u");
	GP142_textXY(WHITE, a + var * 6, 100, 20, " ");
	GP142_textXY(WHITE, a + var * 7, 100, 20, "W");
	GP142_textXY(WHITE, a + var * 8+4, 100, 20, "a");
	GP142_textXY(WHITE, a + var * 9, 100, 20, "n");
	GP142_textXY(WHITE, a + var * 10, 100, 20, "t");
	GP142_textXY(WHITE, a + var * 11, 100, 20, " ");
	GP142_textXY(WHITE, a + var * 12, 100, 20, "T");
	GP142_textXY(WHITE, a + var * 13, 100, 20, "o");
	GP142_textXY(WHITE, a + var * 14, 100, 20, " ");
	GP142_textXY(WHITE, a + var * 15, 100, 20, "L");
	GP142_textXY(WHITE, a + var * 16, 100, 20, "o");
	GP142_textXY(WHITE, a + var * 17, 100, 20, "a");
	GP142_textXY(WHITE, a + var * 18, 100, 20, "d");
	GP142_textXY(WHITE, a + var * 19, 100, 20, " ");
	GP142_textXY(WHITE, a + var * 20, 100, 20, "P");
	GP142_textXY(WHITE, a + var * 21, 100, 20, "r");
	GP142_textXY(WHITE, a + var * 22, 100, 20, "e");
	GP142_textXY(WHITE, a + var * 23, 100, 20, "v");
	GP142_textXY(WHITE, a + var * 24, 100, 20, "i");
	GP142_textXY(WHITE, a + var * 25-3, 100, 20, "o");
	GP142_textXY(WHITE, a + var * 26, 100, 20, "u");
	GP142_textXY(WHITE, a + var * 27, 100, 20, "s");
	GP142_textXY(WHITE, a + var * 28, 100, 20, " ");
	GP142_textXY(WHITE, a + var * 29, 100, 20, "F");
	GP142_textXY(WHITE, a + var * 30, 100, 20, "i");
	GP142_textXY(WHITE, a + var * 31-3, 100, 20, "l");
	GP142_textXY(WHITE, a + var * 32-5, 100, 20, "e");
	GP142_textXY(WHITE, a + var * 33 - 5, 100, 20, "?");
}
void COLOR(point mouse,int &color)		//checks the color menu and changes the color
{
	point p;
	p.x = cx; p.y = cy + 40;
	for (int i = 0; i < 24; i++)
	{
		if (insideCircle(mouse, cx, cy - cd*i, cr))
		{
			color = i;
			
			bucketFill(p.x, p.y, GP142_GetColor(p.x, p.y), color);
		}
	}
	
}
int main(void)
{
	
	int quit;                   /* Track whether the user has asked to quit */
	int event;                  /* Holds GP142 events                       */
	point mouse;       
	char key_pressed;
	int color = 0;
	bool l=false;
	/* Open a blank GP142 graphics window.*/

	GP142_open();
	GP142_rectangleXY(22, -400, 200, 400, -200, 4);
	message();
	GP142_rectangleXY(22, 130, -50, 230 , -50 - 50, 3);
	GP142_textXY(WHITE, 130 + 50, -50 - 30, 20, "N");
	GP142_rectangleXY(22, -200, -50, -200 + 100, -50 - 50, 3);
	GP142_textXY(WHITE, -200 + 50, -50 - 30, 20, "Y");
	event = GP142_await_event(&mouse.x, &mouse.y, &key_pressed);
	while (true)
	{
		
		if (mouse.x >= 130 && mouse.x <= 230 && mouse.y <= -50 && mouse.y >= -100)
		{
			l = false;
			break;
		}
		else if (mouse.x >= -200 && mouse.x <= -100 && mouse.y <= -50 && mouse.y >= -100)
		{
			l = true;
			break;
		}
		else 
			event = GP142_await_event(&mouse.x, &mouse.y, &key_pressed);
	}
	createWindow();
	if (l)
	{
		Load();
	}
	quit = FALSE;

	while (!quit)
	{
		/* Get the next event */
		event = GP142_await_event(&mouse.x, &mouse.y, &key_pressed);
		/* Decide what kind of event we got */
		if (event == GP142_MOUSE)
		{
		
			
			if (fsize == tsize)			// extends allShapes if needed
			{
				extendAllShapes(allShapes, tsize, fsize);
			}
			if (mouse.x >= px && mouse.x <= px + 50 && mouse.y <= py && mouse.y >= py - 50)//BUTTON 1  Rectangle
			{
				GP142_rectangleXY(5, px, py, px + 50, py - 50,4);
				point*list;
				list = new point[2];
				for (int i = 0; i < 2; i++)
				{
					do				// checks user donot use any event other than left click
					{
						event = GP142_await_event(&mouse.x, &mouse.y, &key_pressed);
						while (Outside(mouse))   // checks if point is in allowed area
						{
							event = GP142_await_event(&mouse.x, &mouse.y, &key_pressed);
						}
						list[i] = mouse;
					} while (event != GP142_MOUSE);
				}
				allShapes[fsize] = new rectangle(list, color, 0);
				allShapes[fsize]->draw();
				fsize++;
				GP142_rectangleXY(22, px, py, px + 50, py - 50, 4);
			}
			else if (mouse.x >= px && mouse.x <= px + 50 && mouse.y <= py-50-10 && mouse.y >= py - 50-50-10)//BUTTON 2
			{
				GP142_rectangleXY(5, px, py - 60, px + 50, py - 110,4);
				point*list = new point[];
				list = new point[2];
				for (int i = 0; i < 2; i++)
				{
					event = GP142_await_event(&mouse.x, &mouse.y, &key_pressed);
					while (Outside(mouse))
					{
						event = GP142_await_event(&mouse.x, &mouse.y, &key_pressed);
					}
					list[i] = mouse;
				}
				allShapes[fsize] = new Circle(list, color, 0);
				allShapes[fsize]->draw();
				fsize++;
				GP142_rectangleXY(22, px, py - 60, px + 50, py - 110, 4);
			}
			else if (mouse.x >= px && mouse.x <= px + 50 && mouse.y <= py - 100 - 20 && mouse.y >= py - 150- 20)//BUTTON 3
			{
				GP142_rectangleXY(5, px, py - 120, px + 50, py - 170, 4);
				point*list;
				list = new point[2];
				for (int i = 0; i < 2; i++)
				{
					do
					{
						event = GP142_await_event(&mouse.x, &mouse.y, &key_pressed);
						while (Outside(mouse))
						{
							event = GP142_await_event(&mouse.x, &mouse.y, &key_pressed);
						}
						list[i] = mouse;
					} while (event != GP142_MOUSE);
				}
				allShapes[fsize] = new Line(list, color, true);
				allShapes[fsize]->draw();
				fsize++;
				GP142_rectangleXY(22, px, py - 120, px + 50, py - 170, 4);
			}
			else if (mouse.x >= px && mouse.x <= px + 50 && mouse.y <= py - 150 - 30 && mouse.y >= py - 200 - 30)//BUTTON 4
			{
				GP142_rectangleXY(5, px, py - 180, px + 50, py - 230, 4);
				point*list = new point[1];
				int size = 1;
				int fs = 0;
				while (event != GP142_RightClick)
				{
					if (fs == size)
					{
						extendArray(list, size, fs);
					}
					event = GP142_await_event(&mouse.x, &mouse.y, &key_pressed);
					while (Outside(mouse))
					{
						event = GP142_await_event(&mouse.x, &mouse.y, &key_pressed);
					}
					if (event == GP142_MOUSE)
					{
						list[fs] = mouse;
						fs++;
					}
				}
				allShapes[fsize] = new Curve(list, fs - 1, color, true);
				allShapes[fsize]->draw();
				fsize++;
				GP142_rectangleXY(22, px, py - 180, px + 50, py - 230, 4);
			}
			else if (mouse.x >= px && mouse.x <= px + 50 && mouse.y <= py - 200 - 40 && mouse.y >= py - 250 - 40)//BUTTON 5
			{
				GP142_rectangleXY(5, px, py - 240, px + 50, py - 290, 4);
				point*list = new point[1];
				int size = 1;
				int fs = 0;
				while (event!=GP142_RightClick)
				{
					if (fs == size)
					{
						extendArray(list, size, fs);
					}
					event = GP142_await_event(&mouse.x, &mouse.y, &key_pressed);
					while (Outside(mouse))
					{
						event = GP142_await_event(&mouse.x, &mouse.y, &key_pressed);
					}
					if (event == GP142_MOUSE)
					{
						list[fs] = mouse;
						fs++;
					}
				}
				allShapes[fsize] = new polygon(list,fs-1,color,-1);
				allShapes[fsize]->draw();
				fsize++;
				GP142_rectangleXY(22, px, py - 240, px + 50, py - 290, 4);
			}
			else if (mouse.x >= px && mouse.x <= px + 50 && mouse.y <= py - 250 - 50 && mouse.y >= py - 300 - 50)//BUTTON 6
			{
				GP142_rectangleXY(5, px, py - 300, px + 50, py - 350, 4);
				point p;
				int size=0;
				vector<char> c;
				event = GP142_await_event(&mouse.x, &mouse.y, &key_pressed);
				while (Outside(mouse))
				{
					event = GP142_await_event(&mouse.x, &mouse.y, &key_pressed);
				}
				if (event ==GP142_MOUSE)
					p.x = mouse.x, p.y = mouse.y;
				event = GP142_await_event(&mouse.x, &mouse.y, &key_pressed);
				while (event == GP142_KBD && key_pressed != 13)
				{
					c.push_back(key_pressed);
					event = GP142_await_event(&mouse.x, &mouse.y, &key_pressed);
					size++;
				}
				allShapes[fsize] = new Text(c, color, p, size);
				allShapes[fsize]->draw();
				fsize++;
				GP142_rectangleXY(22, px, py - 300, px + 50, py - 350, 4);
				
				
			}
			else if (mouse.x >= px && mouse.x <= px + 50 && mouse.y <= py - 300 - 60 && mouse.y >= py - 350 - 60)//BUTTON 7
			{
				GP142_rectangleXY(5, px, py - 360, px + 50, py - 350 -60, 4);
				event = GP142_await_event(&mouse.x, &mouse.y, &key_pressed);
				while (Outside(mouse) && !(mouse.x >= px && mouse.x <= px + 50 && mouse.y <= py - 300 - 60 && mouse.y >= py - 350 - 60))
				{
					event = GP142_await_event(&mouse.x, &mouse.y, &key_pressed);
				}
				do{
		
				
					for (int i = 0; i < fsize; i++)
					{
						if (allShapes[i]->containPoint(mouse))
						{
							allShapes[i]->fill(mouse, color);
						}
					}
					event = GP142_await_event(&mouse.x, &mouse.y, &key_pressed);
					while (Outside(mouse) && !(mouse.x >= px && mouse.x <= px + 50 && mouse.y <= py - 300 - 60 && mouse.y >= py - 350 - 60))
					{
						event = GP142_await_event(&mouse.x, &mouse.y, &key_pressed);
					}
				} while (!(mouse.x >= px && mouse.x <= px + 50 && mouse.y <= py - 300 - 60 && mouse.y >= py - 350 - 60));
				GP142_rectangleXY(22, px, py - 360, px + 50, py - 350 - 60, 4);
			}
			else if (mouse.x >= px && mouse.x <= px + 50 && mouse.y <= py - 350 - 70 && mouse.y >= py - 400 - 70)//BUTTON 8
			{
				GP142_rectangleXY(5, px, py - 420, px + 50, py - 400 - 70, 4);
				event = GP142_await_event(&mouse.x, &mouse.y, &key_pressed);
				while (Outside(mouse) && !(mouse.x >= px && mouse.x <= px + 50 && mouse.y <= py - 350 - 70 && mouse.y >= py - 400 - 70))
				{
					event = GP142_await_event(&mouse.x, &mouse.y, &key_pressed);
				}
				do
				{
					for (int i = 0; i < fsize; i++)
					{
						if (allShapes[i]->containPoint(mouse))
						{
							point*list = allShapes[i]->getlist();
							delete[] allShapes[i]->getlist();
							shrinkAllShapes(allShapes, tsize, fsize, i);
							
						}
					}
					createWindow();
					for (int i = 0; i < fsize; i++)
					{
						allShapes[i]->draw();
					}
					point p;
					for (int i = 0; i < fsize; i++)
					{
						p.x = allShapes[i]->getFx();
						p.y = allShapes[i]->getFy();
						allShapes[i]->fill(p, allShapes[i]->getfcol());
					}
					GP142_rectangleXY(5, px, py - 420, px + 50, py - 400 - 70, 4);
					event = GP142_await_event(&mouse.x, &mouse.y, &key_pressed);
					while (Outside(mouse) && !(mouse.x >= px && mouse.x <= px + 50 && mouse.y <= py - 350 - 70 && mouse.y >= py - 400 - 70))
					{
						event = GP142_await_event(&mouse.x, &mouse.y, &key_pressed);
					}
				} while (!(mouse.x >= px && mouse.x <= px + 50 && mouse.y <= py - 350 - 70 && mouse.y >= py - 400 - 70));
				GP142_rectangleXY(22, px, py - 420, px + 50, py - 400 - 70, 4);
			}
			else if (mouse.x >= px && mouse.x <= px + 50 && mouse.y <= py - 400 - 80 && mouse.y >= py - 450 - 80)//BUTTON 9
			{
				GP142_rectangleXY(5, px, py - 480, px + 50, py - 450 - 80, 4);
				Sleep(1000);
				GP142_rectangleXY(22, px, py - 480, px + 50, py - 450 - 80, 4);
				ofstream fout;
				fout.open("drawing.pb");
				for (int i = 0; i < fsize; i++)
				{
					string name = allShapes[i]->getName();
					if (name == "TEXT")
					{
						fout << allShapes[i]->getName() << endl;
						fout << allShapes[i]->getcolor() << endl;
						fout << allShapes[i]->getNumOfPoints() << endl;
						fout << allShapes[i]->getsentence() << endl;
						point*arr = allShapes[i]->getlist();
						fout << arr[0].x << endl;
						fout << arr[0].y << endl;
						

						fout << allShapes[i]->getFx()<<endl;
						fout << allShapes[i]->getFy()<<endl;
						fout << allShapes[i]->getfcol()<<endl;
					}
					else
					{
						fout << allShapes[i]->getName() << endl;
						fout << allShapes[i]->getcolor() << endl;
						int a = allShapes[i]->getNumOfPoints();
						fout << a << endl;
						point*arr = allShapes[i]->getlist();
						for (int j = 0; j < a; j++)
						{
							fout << arr[j].x << endl;
							fout << arr[j].y << endl;
						}
						
						fout << allShapes[i]->getFx() << endl;
						fout << allShapes[i]->getFy() << endl;
						fout << allShapes[i]->getfcol() << endl;
					}
				}
				fout.close();
			}
			else if (mouse.x >= px && mouse.x <= px + 50 && mouse.y <= py - 450 - 90 && mouse.y >= py - 500 - 90)//BUTTON 9
			{
				GP142_rectangleXY(5, px, py - 450-90, px + 50, py - 500 - 90, 4);
				point*list;
				list = new point[2];
				for (int i = 0; i < 2; i++)
				{
					do
					{
						event = GP142_await_event(&mouse.x, &mouse.y, &key_pressed);
						while (Outside(mouse))
						{
							event = GP142_await_event(&mouse.x, &mouse.y, &key_pressed);
						}
						list[i] = mouse;
					} while (event != GP142_MOUSE);
				}
				allShapes[fsize] = new Line(list, color, false);
				allShapes[fsize]->draw();
				fsize++;
				GP142_rectangleXY(22, px, py - 450 - 90, px + 50, py - 500 - 90, 4);
			}
			else if (mouse.x >= px && mouse.x <= px + 50 && mouse.y <= py - 500 - 100 && mouse.y >= py - 550 - 100)//BUTTON 10
			{
				GP142_rectangleXY(5, px, py - 500 - 100, px + 50, py - 550 - 100, 4);
				point*list = new point[1];
				int size = 1;
				int fs = 0;
				while (event != GP142_RightClick)
				{
					if (fs == size)
					{
						extendArray(list, size, fs);
					}
					event = GP142_await_event(&mouse.x, &mouse.y, &key_pressed);
					while (Outside(mouse))
					{
						event = GP142_await_event(&mouse.x, &mouse.y, &key_pressed);
					}
					if (event == GP142_MOUSE)
					{
						list[fs] = mouse;
						fs++;
					}
				}
				allShapes[fsize] = new Curve(list, fs - 1, color, false);
				allShapes[fsize]->draw();
				fsize++;
				GP142_rectangleXY(22, px, py - 500 - 100, px + 50, py - 550 - 100, 4);

			}
			/* COLOR CHANGING */
			COLOR(mouse,color);
			
			
		}
		else if (event == GP142_QUIT)
		{
			quit = TRUE;
		}
	}  /* end event loop */
	for (int i = 0; i < fsize; i++)
	{
		delete allShapes[i];
	}
	delete[] allShapes;
	
	/* Close the graphics window and exit */
	GP142_close();
	return 0;

}
