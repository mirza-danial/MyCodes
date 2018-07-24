#include<iostream>
#include<math.h>
#include"help.h"
#include<conio.h>
#include <fstream>
#define pi 3.1428571429
using namespace std;
int wid = 1, color1 = 0, color2 = 0, color3 = 0, Exit = 0;
bool pen = true;
int CordArray[10][4] = {0};
char LabArray[10] = { '\0' };
int counter(int value)
{
	int count = 2;
	while (value > 9)
	{
		value = value / 10;
		count++;
	}
	count++;
	return count;
}
int degree(float angle)//converts radian angle in degrees
{
	angle = angle*(180 / pi);
	return angle;
}
void pointer(float x, float y, float angle)//creates pointer
{
	while (angle>=2 * pi)
	{
		angle = angle - (2 * pi);
	}
	int degree_angle = degree(angle), Ax, Ay, Bx, By;
	if (degree_angle == 0 || degree_angle >355 && degree_angle <365)
	{
		Ax = x - 5;
		Ay = y + 5;
		Bx = x + 5;
		By = y + 5;
	}
	else if (degree_angle >40 && degree_angle <50)
	{
		Ax = x;
		Ay = y + 5;
		Bx = x - 5;
		By = y;
	}
	else if (degree_angle >85 && degree_angle <95)
	{
		Ax = x - 5;
		Ay = y - 5;
		Bx = x - 5;
		By = y + 5;
	}
	else if (degree_angle > 130 && degree_angle < 140)
	{
		Ax = x;
		Ay = y - 5;
		Bx = x - 5;
		By = y;
	}
	else if (degree_angle > 175 && degree_angle <185)
	{
		Ax = x + 5;
		Ay = y - 5;
		Bx = x - 5;
		By = y - 5;
	}
	else if (degree_angle > 220 && degree_angle < 230)
	{
		Ax = x + 5;
		Ay = y;
		Bx = x;
		By = y - 5;
	}
	else if (degree_angle > 265 && degree_angle < 275)
	{
		Ax = x + 5;
		Ay = y + 5;
		Bx = x + 5;
		By = y - 5;
	}
	else if (degree_angle > 310 && degree_angle < 320)
	{
		Ax = x;
		Ay = y + 5;
		Bx = x + 5;
		By = y;
	}
	myLine(Ax, Ay, x, y, 2, 0, 0, 255);
	myLine(Bx, By, x, y, 2, 0, 0, 255);
}
void pointeremove(float x, float y, float angle)//removes pointer
{

	while (angle>=2 * pi)
	{
		angle = angle - (2 * pi);
	}
	int degree_angle = degree(angle), Ax, Ay, Bx, By;
	if (degree_angle == 0 || degree_angle >355 && degree_angle <365)
	{
		Ax = x - 5;
		Ay = y + 5;
		Bx = x + 5;
		By = y + 5;
	}
	else if (degree_angle >40 && degree_angle <50)
	{
		Ax = x;
		Ay = y + 5;
		Bx = x - 5;
		By = y;
	}
	else if (degree_angle >85 && degree_angle <95)
	{
		Ax = x - 5;
		Ay = y - 5;
		Bx = x - 5;
		By = y + 5;
	}
	else if (degree_angle > 130 && degree_angle < 140)
	{
		Ax = x;
		Ay = y - 5;
		Bx = x - 5;
		By = y;
	}
	else if (degree_angle > 175 && degree_angle <185)
	{
		Ax = x + 5;
		Ay = y - 5;
		Bx = x - 5;
		By = y - 5;
	}
	else if (degree_angle > 220 && degree_angle < 230)
	{
		Ax = x + 5;
		Ay = y;
		Bx = x;
		By = y - 5;
	}
	else if (degree_angle > 265 && degree_angle < 275)
	{
		Ax = x + 5;
		Ay = y + 5;
		Bx = x + 5;
		By = y - 5;
	}
	else if (degree_angle > 310 && degree_angle < 320)
	{
		Ax = x;
		Ay = y + 5;
		Bx = x + 5;
		By = y;
	}
	myLine(Ax, Ay, x, y, 2, 255, 255, 255);
	myLine(Bx, By, x, y, 2, 255, 255, 255);

}
void centre_turtle(int &x1, int &y1, float &angle)
{
	x1 = 200;
	y1 = 200;
	angle = 0;
	pointer(x1, y1, angle);
}
void store_label(char array[], char label,int &index)
{
	array[index] = label;
	index++;
}
void store_coord(int label_array[][4], int coordx1, int coordy1, int coordx2, int coordy2, int &i)
{
		label_array[i][0] = coordx1;
		label_array[i][1] = coordy1;
		label_array[i][2] = coordx2;
		label_array[i][3] = coordy2;
}
void Move(char array[], int array2D[][4], char label,int value)
{
	int index = 0;
	int Cx1, Cy1, Cx2, Cy2;
	for (int i = 0; array[i] != '\0'; i++)
	{
		if (array[i] == label)
		{
			index = i;
			break;
		}
	}
	Cx1=array2D[index][0];
	Cy1 = array2D[index][1];
	Cx2 = array2D[index][2];
	Cy2 = array2D[index][3];
	/*gotoxy(0, 0);
	cout << Cx1 << " " << Cy1 << " " << Cx2 << " " << Cy2;*/
	myLine(Cx1, Cy1, Cx2, Cy2, wid, 255, 255, 255);
	myLine(Cx1+value, Cy1, Cx2+value, Cy2, wid, color1, color2, color3);
	array2D[index][0]=Cx1+value;
	array2D[index][1]=Cy1;
	array2D[index][2]=Cx2+value;
	array2D[index][3]=Cy2;
}
void width(char array[])//changes width of line
{
	wid = (atoi(array + 5));
	gotoxy(0, 0);
	cout << "THE WIDTH OF THE POINTER IS CHANGED TO " << wid;
}

void colorChange(char array[])//changes color of line
{
	if (array[5] == 'y'&&array[6] == 'e'&&array[7] == 'l'&&array[8] == 'l'&&array[9] == 'o'&&array[10] == 'w')
	{
		color1 = 255;
		color2 = 255;
		color3 = 0;
		gotoxy(0, 0);
		cout << "COLOR IS CHANGED TO YELLOW";
	}
	else if (array[5] == 'b'&&array[6] == 'l'&&array[7] == 'u'&&array[8] == 'e')
	{
		color1 = 0;
		color2 = 0;
		color3 = 255;
		gotoxy(0, 0);
		cout << "COLOR IS CHANGED TO BLUE";
	}
	else if (array[5] == 'r'&&array[6] == 'e'&&array[7] == 'd')
	{
		color1 = 255;
		color2 = 0;
		color3 = 0;
		gotoxy(0, 0);
		cout << "COLOR IS CHANGED TO RED";

	}
	else if (array[5] == 'g'&&array[6] == 'r'&&array[7] == 'e'&&array[8] == 'e'&&array[9] == 'n')
	{
		color1 = 0;
		color2 = 255;
		color3 = 0;
		gotoxy(0, 0);
		cout << "COLOR IS CHANGED TO GREEN";

	}
	else if (array[5] == 'c'&&array[6] == 'y'&&array[7] == 'a'&&array[8] == 'n')
	{
		color1 = 0;
		color2 = 255;
		color3 = 255;
		gotoxy(0, 0);
		cout << "COLOR IS CHANGED TO CYAN";

	}
	else if (array[5] == 'o'&&array[6] == 'l'&&array[7] == 'i'&&array[8] == 'v'&&array[9] == 'e')
	{
		color1 = 128;
		color2 = 128;
		color3 = 0;
		gotoxy(0, 0);
		cout << "COLOR IS CHANGED TO OLIVE";

	}
	else if (array[5] == 'i'&&array[6] == 'n'&&array[7] == 'd'&&array[8] == 'i'&&array[9] == 'g'&&array[10] == 'o')
	{
		color1 = 75;
		color2 = 0;
		color3 = 130;
		gotoxy(0, 0);
		cout << "COLOR IS CHANGED TO INDIGO";

	}
	else if (array[5] == 'o'&&array[6] == 'r'&&array[7] == 'a'&&array[8] == 'n'&&array[9] == 'g'&&array[10] == 'e')
	{
		color1 = 255;
		color2 = 165;
		color3 = 0;
		gotoxy(0, 0);
		cout << "COLOR IS CHANGED TO ORANGE";

	}
	else if (array[5] == 'p'&&array[6] == 'i'&&array[7] == 'n'&&array[8] == 'k')
	{
		color1 = 255;
		color2 = 20;
		color3 = 147;
		gotoxy(0, 0);
		cout << "COLOR IS CHANGED TO PINK";

	}
	else if (array[5] == 'b'&&array[6] == 'l'&&array[7] == 'a'&&array[8] == 'c'&&array[9] == 'k')
	{
		color1 = 0;
		color2 = 0;
		color3 = 0;
		gotoxy(0, 0);
		cout << "COLOR IS CHANGED TO WHITE";

	}
}

void radian(float &angle)//converts angles in radian
{
	angle = angle*(pi / 180);
}
void forward(int &x1, int &y1, int &x2, int &y2, float &angle, int val, bool &pen, int &Cx1, int &Cy1, int &Cx2, int &Cy2)//forward
{
	pointeremove(x1, y1,angle);

	x2 = x1 + (val*sin(angle));
	y2 = y1 - (val*cos(angle));
	if (pen == true){
		myLine(x1, y1, x2, y2, wid, color1, color2, color3);
	}
	Cx1 = x1; Cy1 = y1; Cx2 = x2; Cy2 = y2;
	x1 = x2; y1 = y2;
	pointer(x1, y1,angle);
}
void backword(int &x1, int &y1, int &x2, int &y2, float &angle, int val, bool &pen, int &Cx1, int &Cy1, int &Cx2, int &Cy2)//moves backwards
{

	pointeremove(x1, y1,angle);
	x2 = x1 - (val*sin(angle));
	y2 = y1 + (val*cos(angle));
	if (pen == true){
		myLine(x1, y1, x2, y2, wid, color1, color2, color3);
	}
	Cx1 = x1; Cy1 = y1; Cx2 = x2; Cy2 = y2;
	x1 = x2; y1 = y2;
	pointer(x1, y1,angle);
}
void right(float direction, float &angle)//turns right
{
	while (direction > 360)//standarize angle
	{
		direction = direction - 360;
	}
	radian(direction);
	angle = angle + direction;//judges new angle
}
void left(float direction, float &angle)//turns left
{
	while (direction > 360)//standarize angle
	{
		direction = direction - 360;
	}
	direction = 360 - direction;
	radian(direction);
	angle = angle + direction;//judge new direction
}
void MoveBackArray(char array[], int index)//moves whole array backwards by one index
{
	int ind = index + 1;

	while (array[ind] != '\0')
	{
		array[index] = array[ind];
		index++;
		ind++;
	}
	array[ind] = '\0';

}
void RemoveSpace(char array[])//removes spaces by moving whole array back
{

	int count = 0;

	for (int i = 0; array[i] != '\0'; i++)
	{
		if (array[i] != ' ') count++;
	}

	for (int i = 0; array[i] != '\0'; i++)
	{
		while (array[i] == ' ')
		{
			MoveBackArray(array, i);

		}
	}
	array[count] = '\0';

}
void remove_s(char array[])//removes spaces in begining of array
{
	for (int op = 0;/* array[i] != '\0'*/array[op] >= 'a' && array[op] <= 'z' || array[op] >= 'A' && array[op] <= 'Z'; op++)
	{
		while (array[op] == ' ')
		{
			MoveBackArray(array, op);

		}
	}
}
void history(char ar2[][1000], int &rowno)//stores commands in 2D array and shows command history
{

	int i = rowno - 1;
	myLine(0, 400, 1350, 400, 3, 255, 255, 255);
	gotoxy(0,26 ); cout << "Command History  :\n";
	int j = 28;
	gotoxy(2, j);
	while (i > -1)
	{
		cout << ar2[i]<<"\t||\t"; i--;
	}
}
void clearscreen(int &x1, int &y1, float &angle, char ar2[][1000], int &rowno)//clears screen when command is given
{
	myRect(-1, -1, 1020, 1400, 0, 128, 128, 0, 128, 128);
	myRect(10, 30, 1300, 350, 0, 0, 255, 255, 255, 255);
	/*myRect(0, 30, 700, 350, 0, 0, 255, 255, 255, 255);*/
	myRect(120, 365, 700, 390, 255, 255, 255, 0, 128, 128);
	gotoxy(0, 0);
	cout << "Screen has been cleared:";
	gotoxy(0, 23);
	cout << "COMMAND PROMTP:";
	gotoxy(0, 26); cout << "Command History  :\n";
	history(ar2, rowno);
	x1 = 200; y1 = 200; angle = 0;
	pointer(x1, y1, angle);
}
void repeat(char ar[], int &x1, int &y1, int &x2, int &y2, int &value, float &angle, bool &pen, float &direction, char ar2[][1000], int &rowno, int Cx1, int Cy1, int Cx2, int Cy2)//repeats commands
{
	int i = 0;
	int z = atoi(ar + 6);
	cout << z << endl;
	int j;
	char array[10];

	for (int x = 1; x <= z; x++){
		i = 0;
		while (ar[i] != '[') i++;

		i++;
		while (ar[i] != ']'){

			/*arr[0] = ar[i], i++;
			arr[1] = ar[i], i++;
			j = 2;
			*/
			j = 0;

			while (ar[i] >= 'a' && ar[i] <= 'z' || ar[i] >= 'A' && ar[i] <= 'Z') {
				array[j] = ar[i];
				j++, i++;
			}
			while (ar[i] <= '9'&&ar[i] >= '0') {
				array[j] = ar[i];
				j++, i++;
			}

			array[j] = '\0';
			if ((array[0] == 'f'&&array[1] == 'd') || (array[0] == 'f'&&array[1] == 'o'&&array[2] == 'r'&&array[3] == 'w'&&array[4] == 'a'&&array[5] == 'r'&&array[6] == 'd'))
			{
				if (array[0] == 'f'&&array[1] == 'd')
				{
					value = atoi(array + 2);
				}
				else
				{
					value = atoi(array + 7);
				}
				forward(x1, y1, x2, y2, angle, value, pen,Cx1,Cy1,Cx2,Cy2);
				gotoxy(0, 0);
				cout << "Cursor have moved " << value << " pixels forward\n";
			}
			else if ((array[0] == 'b'&&array[1] == 'k') || (array[0] == 'b'&&array[1] == 'a'&&array[2] == 'c'&&array[3] == 'k'&&array[4] == 'w'&&array[5] == 'a'&&array[6] == 'r'&&array[7] == 'd'))
			{
				if (array[0] == 'b'&&array[1] == 'k')
				{
					value = atoi(array + 2);
				}
				else
				{
					value = atoi(array + 8);
				}
				backword(x1, y1, x2, y2, angle, value, pen,Cx1, Cy1, Cx2, Cy2);
				gotoxy(0, 0);
				cout << "Cursor have moved " << value << " pixels backward\n";

			}
			else if (array[0] == 'r'&&array[1] == 't')
			{
				direction = atoi(array + 2);
				if ((int)direction % 45 == 0)
				{
					pointeremove(x1, y1, angle);
					right(direction, angle);
					gotoxy(0, 0);
					cout << "Direction have been changed to " << direction/**(180/pi)*/ << " degrees to the right\n";
					pointer(x1, y1, angle);
				}
				else
				{
					gotoxy(0, 0);
					cout << "Angle should be the multiple of 45 degree:";
				}
			}

			else if (array[0] == 'l'&&array[1] == 't')
			{
				direction = atoi(array + 2);
				if ((int)direction % 45 == 0)
				{
					pointeremove(x1, y1, angle);
					left(direction, angle);
					gotoxy(0, 0);
					cout << "Direction have been changed to " <</*360- */direction/**(180 / pi)*/ << " degrees to the left\n";
					pointer(x1, y1, angle);
				}
				else
				{
					gotoxy(0, 0);
					cout << "Angle should be the multiple of 45 degree:";
				}
				

			}
			else if (array[0] == 'p'&&array[1] == 'u')
			{
				pen = false;
				gotoxy(0, 0);
				cout << "Pen is up now\n";
			}
			else if (array[0] == 'p'&&array[1] == 'd')
			{
				pen = true;
				gotoxy(0, 0);
				cout << "Pen is down now\n";
			}
			else if (array[0] == 'c'&&array[1] == 'o'&&array[2] == 'l'&&array[3] == 'o'&&array[4] == 'r')
			{
				colorChange(array);
			}
			else if (array[0] == 'w'&&array[1] == 'i'&&array[2] == 'd'&&array[3] == 't'&&array[4] == 'h')
			{
				width(array);
			}
			else if (array[0] == 'c'&&array[1] == 's')
			{
				clearscreen(x1, y1, angle, ar2, rowno);
			}
			else if (array[0] == 'c'&&array[1] == 'i'&&array[2] == 'r'&&array[3] == 'c'&&array[4] == 'l'&&array[5] == 'e')
			{
				value = atoi(array + 6);
				myEllipse(x1 - value, y1 - value, x1 + value, y1 + value, color1, color2, color3);
				pointer(x1, y1, angle);
				gotoxy(0, 0);
				cout << "Circle of radius " << value << " is drawn\n";
			}
			else if (array[0] == 'M'&&array[1] == 'o'&&array[2] == 'v'&&array[3] == 'e')
			{
			}
			else if (array[0] == 'E'&&array[1] == 'x'&&array[2] == 'i'&&array[3] == 't')
			{
				Exit = 1;
			}
			else
			{
				gotoxy(0, 0);
				cout << "Wrong command ! I dont know this command\n";
			}
		}	

	}


}
void store_in_td(char ar[], char ar2[][1000], int &rowno)//stores entered commands in 2D array
{
	
	strcpy_s(ar2[rowno], ar);
	rowno++;


}
void save(char ar[], char ar2[][1000],int rowno)//envokes save function
{
	
	int i = 0;
	int x = rowno-2;
	while (x > 101)i++,x--;
	  // rowno-2;
	ofstream save("file.txt");
	for (; i < rowno - 1; i++)
		save << ar2[i]<< endl;

}
void load(char array[], int &x1, int &y1, int &x2, int &y2, float angle, int value, bool &pen, char ar2[][1000], int &rowno, int Cx1, int Cy1 , int Cx2, int Cy2 )//envokes load functions
{

	char filename[30];
	int i = 0;
	while (array[i] != '\"'){
		i++;
	}
	int j = 0;
	while (array[i] != '\0'){

		filename[j] = array[i];
		j++; i++;
		
	}
	filename[j] = '\0';
	ifstream thefile("file.txt");

	while (thefile >> array){

		remove_s(array);
		if (array[1] != ' ')
		{
			RemoveSpace(array);
			float direction;
			if ((array[0] == 'f'&&array[1] == 'd') || (array[0] == 'f'&&array[1] == 'o'&&array[2] == 'r'&&array[3] == 'w'&&array[4] == 'a'&&array[5] == 'r'&&array[6] == 'd'))
			{
				if (array[0] == 'f'&&array[1] == 'd')
				{
					value = atoi(array + 2);
				}
				else
				{
					value = atoi(array + 7);
				}
				forward(x1, y1, x2, y2, angle, value, pen,Cx1,Cy1,Cx2,Cy2);
				gotoxy(0, 0);
				cout << "Cursor have moved " << value << " pixels forward\n";
			}
			else if ((array[0] == 'b'&&array[1] == 'k') || (array[0] == 'b'&&array[1] == 'a'&&array[2] == 'c'&&array[3] == 'k'&&array[4] == 'w'&&array[5] == 'a'&&array[6] == 'r'&&array[7] == 'd'))
			{
				if (array[0] == 'b'&&array[1] == 'k')
				{
					value = atoi(array + 2);
				}
				else
				{
					value = atoi(array + 8);
				}
				backword(x1, y1, x2, y2, angle, value, pen,Cx1, Cy1, Cx2, Cy2);
				gotoxy(0, 0);
				cout << "Cursor have moved " << value << " pixels backward\n";

			}
			else if (array[0] == 'r'&&array[1] == 't')
			{
				direction = atoi(array + 2);
				if ((int)direction % 45 == 0)
				{
					pointeremove(x1, y1, angle);
					right(direction, angle);
					gotoxy(0, 0);
					cout << "Direction have been changed to " << direction << " degrees to the right\n";
					pointer(x1, y1, angle);
				}
				else
				{
					gotoxy(0, 0);
					cout << "Angle should be the multiple of 45 degree:";
				}
			}

			else if (array[0] == 'l'&&array[1] == 't')
			{
				direction = atoi(array + 2);
				if ((int)direction % 45 == 0)
				{
					pointeremove(x1, y1, angle);
					left(direction, angle);
					gotoxy(0, 0);
					cout << "Direction have been changed to " <<direction<< " degrees to the left\n";
					pointer(x1, y1, angle);
				}
				else
				{
					gotoxy(0, 0);
					cout << "Angle should be the multiple of 45 degree:";
				}
				
			}
			else if (array[0] == 'p'&&array[1] == 'u')
			{
				pen = false;
				gotoxy(0, 0);
				cout << "Pen is up now\n";
			}
			else if (array[0] == 'p'&&array[1] == 'd')
			{
				pen = true;
				gotoxy(0, 0);
				cout << "Pen is down now\n";
			}
			else if (array[0] == 'r'&&array[1] == 'e'&&array[2] == 'p'&&array[3] == 'e'&&array[4] == 'a'&&array[5] == 't')
			{
				repeat(array, x1, y1, x2, y2, value, angle, pen, direction, ar2, rowno,Cx1,Cy1,Cx2,Cy2);
			}
			else if (array[0] == 'c'&&array[1] == 'o'&&array[2] == 'l'&&array[3] == 'o'&&array[4] == 'r')
			{
				colorChange(array);
			}
			else if (array[0] == 'w'&&array[1] == 'i'&&array[2] == 'd'&&array[3] == 't'&&array[4] == 'h')
			{
				width(array);
			}
			else if (array[0] == 'c'&&array[1] == 's')
			{
				clearscreen(x1, y1, angle, ar2, rowno);
			}
			else if (array[0] == 'c'&&array[1] == 'i'&&array[2] == 'r'&&array[3] == 'c'&&array[4] == 'l'&&array[5] == 'e')
			{
				value = atoi(array + 6);
				myEllipse(x1 - value, y1 - value, x1 + value, y1 + value, color1, color2, color3);
				pointer(x1, y1, angle);
				gotoxy(0, 0);
				cout << "Circle of radius " << value << " is drawn\n";
			}
			else if (array[0] == 'M'&&array[1] == 'o'&&array[2] == 'v'&&array[3] == 'e')
			{
			}
			else if (array[0] == 'E'&&array[1] == 'x'&&array[2] == 'i'&&array[3] == 't')
			{
				Exit = 1;
			}
			else
			{
				gotoxy(0, 0);
				cout << "Wrong command ! I dont know this command\n";
			}
		}
		else
		{
			gotoxy(0, 0);
			cout << "Wrong command ! I dont know this command\n";
		}


	}
}
void ReadInput(char array[], int &x1, int &y1, int &x2, int &y2, int &value, float &angle, bool &pen, char arr2d[][1000],int &rowno)
{
	/*int CordArray[10][4] = { '\0' };*/
	int Cx1=0, Cx2=0, Cy2=0, Cy1=0;
	int label_array_index = 0;
	/*char LabArray[10] = { '\0' };*/
	char label;
	int character_index;
	remove_s(array);
	if (array[1] != ' ')
	{
		RemoveSpace(array);
		float direction;
		if ((array[0] == 'f'&&array[1] == 'd') || (array[0] == 'f'&&array[1] == 'o'&&array[2] == 'r'&&array[3] == 'w'&&array[4] == 'a'&&array[5] == 'r'&&array[6] == 'd'))
		{
			
			if (array[0] == 'f'&&array[1] == 'd')
			{
				value = atoi(array + 2);
				forward(x1, y1, x2, y2, angle, value, pen, Cx1, Cy1, Cx2, Cy2);
				character_index = counter(value);
				store_coord(CordArray, Cx1, Cy1, Cx2, Cy2,label_array_index);
				label = array[character_index];
				store_label(LabArray, label, label_array_index);
				/*gotoxy(0, 0);
				for (int i = 0; i < 4; i++)cout << CordArray[0][i];
				cout<<LabArray[0];*/
			}
			else
			{
				value = atoi(array + 7);
				forward(x1, y1, x2, y2, angle, value, pen, Cx1, Cy1, Cx2, Cy2);
			}

			gotoxy(0, 0);
			cout << "Cursor have moved " << value << " pixels forward\n";
		}
		else if ((array[0] == 'b'&&array[1] == 'k') || (array[0] == 'b'&&array[1] == 'a'&&array[2] == 'c'&&array[3] == 'k'&&array[4] == 'w'&&array[5] == 'a'&&array[6] == 'r'&&array[7] == 'd'))
		{
			if (array[0] == 'b'&&array[1] == 'k')
			{
			/*	value = atoi(array + 2);*/
				value = atoi(array + 2)/2;
				backword(x1, y1, x2, y2, angle, value, pen, Cx1, Cy1, Cx2, Cy2);
				character_index = counter(value);
				store_coord(CordArray, Cx1, Cy1, Cx2, Cy2, label_array_index);
				label = array[character_index];
				store_label(LabArray, label, label_array_index);
			}
			else
			{
				value = atoi(array + 8);
			}
			backword(x1, y1, x2, y2, angle, value, pen, Cx1, Cy1, Cx2, Cy2);
			gotoxy(0, 0);
			cout << "Cursor have moved " << value << " pixels backward\n";

		}
		else if (array[0] == 'r'&&array[1] == 't')
		{
			direction = atoi(array + 2);
			if ((int)direction % 45 == 0)
			{
				pointeremove(x1, y1, angle);
				right(direction, angle);
				gotoxy(0, 0);
				cout << "Direction have been changed to " << direction/**(180/pi)*/ << " degrees to the right\n";
				pointer(x1, y1, angle);
			}
			else
			{
				gotoxy(0, 0);
				cout << "Angle should be the multiple of 45 degree:";
			}
		}

		else if (array[0] == 'l'&&array[1] == 't')
		{
			direction = atoi(array + 2);
			if ((int)direction % 45 == 0)
			{
				pointeremove(x1, y1, angle);
				left(direction, angle);
				gotoxy(0, 0);
				cout << "Direction have been changed to " <<direction << " degrees to the left\n";
				pointer(x1, y1, angle);
			}
			else
			{
				gotoxy(0, 0);
				cout << "Angle should be the multiple of 45 degree:";
			}
			
		}
		else if (array[0] == 'p'&&array[1] == 'u')
		{
			pen = false;
			gotoxy(0, 0);
			cout << "Pen is up now\n";
		}
		else if (array[0] == 'p'&&array[1] == 'd')
		{
			pen = true;
			gotoxy(0, 0);
			cout << "Pen is down now\n";
		}
		else if (array[0] == 'r'&&array[1] == 'e'&&array[2] == 'p'&&array[3] == 'e'&&array[4] == 'a'&&array[5] == 't')
		{
			repeat(array, x1, y1, x2, y2, value, angle, pen, direction, arr2d, rowno,Cx1,Cy1,Cx2,Cy2);
		}
		else if (array[0] == 'c'&&array[1] == 'o'&&array[2] == 'l'&&array[3] == 'o'&&array[4] == 'r')
		{
			colorChange(array);
		}
		else if (array[0] == 'w'&&array[1] == 'i'&&array[2] == 'd'&&array[3] == 't'&&array[4] == 'h')
		{
			width(array);
		}
		else if (array[0] == 'c'&&array[1] == 's')
		{
			clearscreen(x1, y1, angle, arr2d, rowno);
		}
		else if (array[0] == 'c'&&array[1] == 'i'&&array[2] == 'r'&&array[3] == 'c'&&array[4] == 'l'&&array[5] == 'e')
		{
			value = atoi(array + 6);
			myEllipse(x1 - value, y1 - value, x1 + value, y1 + value, color1, color2, color3);
			pointer(x1, y1, angle);
			gotoxy(0, 0);
			cout << "Circle of radius " << value << " is drawn\n";
		}
		else if (array[0] == 's'&&array[1] == 'a'&&array[2] == 'v'&&array[3] == 'e')
		{
			save(array, arr2d, rowno);
		}
		else if (array[0] == 'L' || array[0] == 'l'&&array[1] == 'o'&&array[2] == 'a'&&array[3] == 'd')
		{
			load(array, x1, y1, x2, y2, angle, value, pen, arr2d, rowno,Cx1,Cy1,Cx2,Cy2);
			gotoxy(0, 0);
			
		}
		else if (array[0] == 'M'&&array[1] == 'o'&&array[2] == 'v'&&array[3] == 'e')
		{
			char L = array[4];
			value = atoi(array + 5);
			Move(LabArray, CordArray, L, value);
			gotoxy(0, 0);
			cout << "THE LABELLED LINES ARE MOVED";
		}
		else if (array[0] == 'c'&&array[1] == 't')
		{
			pointeremove(x1, y1, angle);
			centre_turtle(x1, y1, angle);
			gotoxy(0, 0);
			cout << "Pointer is now centered";
		}
		else if (array[0] == 'E'&&array[1] == 'x'&&array[2] == 'i'&&array[3] == 't')
		{
			Exit = 1;
		}
		else
		{
			gotoxy(0, 0);
			cout << "Wrong command ! I dont know this command\n";
		}
	}
	else
	{
		gotoxy(0, 0);
		cout << "Wrong command ! I dont know this command\n";
	}
	

}
int inputArray(char array[], int &x1, int &y1, int &x2, int &y2, float angle, int value, bool &pen,char arr2d[][1000])
{
	int rowno=0;
	while (Exit == 0)
	{
		gotoxy(0, 23);
		myRect(120, 365, 700, 390, 255, 255, 255, 0, 128, 128);
		cout << "COMMAND PROMTP:";
		gotoxy(0, 26); cout << "Command History  :\n";
		history(arr2d, rowno);
		gotoxy(16, 23);
		cin.getline(array, 100);
		store_in_td(array,arr2d,rowno);
		ReadInput(array, x1, y1, x2, y2, value, angle, pen,arr2d,rowno);
		_getch();
		system("cls");
	}
	if (Exit == 1)
	{
		int j = 45;
		myRect(500, 0, 1020, 1400, 0, 128, 128, 0, 128, 128);
		system("cls");
		myRect(0, 0, 2000, 2000, 0, 128, 128, 0, 128, 128);
		char arrayC[10] = { 'T', 'H', 'A', 'N', 'K', ' ', 'Y', 'O', 'U', '\0' };
		for (int i = 0; arrayC[i] != '\0'&&i < 9; i++)
		{

			gotoxy(j, 10);
			Sleep(200);
			cout << arrayC[i];
			j++;
		}
		cout << endl;
		///*system("cls");
		//myRect(0, 0, 700, 390, 0, 128, 128, 0, 128, 128);
		//gotoxy(45, 10);
		//cout << "THAN*/K YOU";
		return 0;
	}
}
void Menu(char array[], int &x1, int &y1, int &x2, int &y2, float angle, int value, char arr2d[][1000])
{
	
	cout << "\t\t\t\t\t\tLOGO PROGRAMMING" << endl;
	cout << "Use these COMMANDS:\n1-fd or forward\n2-bk or backward\n3-rt\n4-lt\n5-repeat\n6-pu\n6-pd\n7-color\n8-width\n9-cs\n10-circle\n11-width\n12-save\n13-Load\n14-Move\n15-Exit";
	_getch();
	system("cls");
	gotoxy(0, 23);
	myLine(0, 400, 1350, 400, 3, 255, 255, 255);
	myRect(10, 30, 1300, 350, 0, 0, 255, 255, 255, 255);
	/*myRect(0, 30, 700, 350, 0, 0, 255, 255, 255, 255);*/
	pointer(x1, y1, angle);
	inputArray(array, x1, y1, x2, y2, angle, value, pen,arr2d);
}
int main()
{
	system("COLOR 3F");
	myRect(-1, -1, 1020, 1400, 0, 128, 128, 0, 128, 128);
	float angle = 0;
	char array[100] = "\0";
	char arr2d[1000][1000];
	int x1 = 200, y1 = 200, x2 = 0, y2 = 0, value = 0;
	Menu(array, x1, y1, x2, y2, angle, value, arr2d);
	gotoxy(0, 23);
	myRect(0, 30, 700, 350, 0, 0, 255, 255, 255, 255);
	pointer(x1, y1, angle);
	cout << "COMMAND PROMTP:";
	inputArray(array, x1, y1, x2, y2, angle, value, pen,arr2d);
	system("pause");
	return 0;
}
