#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<ctime>
#include<Windows.h>
using namespace std;
void gotoxy(int x, int y)//THIS FUNCTION WAS GIVEN TO US BY OUR ITC INSTRUCTOR FOR OUR PROJECT
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}
int *shrinkarray(int arr1[], int &size, int index)//THIS FUNCTION SHRINKS ARRAY AND UPDATE SIZE
{
	int*arr2 = new int[size - 1];
	int i, j = 0;
	for (i = 0; i < index; i++)
	{
		arr2[j] = arr1[i];
		j++;
	}
	for (i = index + 1; i < size; i++)
	{
		arr2[j] = arr1[i];
		j++;
	}

	delete[]arr1;
	size = size - 1;
	return arr2;
}
void intializearray(int array[], int size)//THIS FUNCTION WILL INTIALIZES ARRAY  IN THE BEGINING
{
	for (int i = 0; i < size; i++)
	{
		array[i] = i + 1;
	}
}
int findlargest(int array[], int size)//THIS FUNCTION RETURNS LARGEST NUMBER IN ARRAY
{
	int large = array[0];
	for (int i = 0; i < size; i++)
	{
		if (large < array[i])
		{
			large = array[i];
		}
		
	}
	return large; 
}

int * makeintarray(int n)//THIS FUNCTION CREATES AN INTEGER ARRAY OF GIVEN SIZE ON HEAP
{
	if (n == 0)
		return nullptr;
	int*array = new int[n];
	return array;
}
int *extendarray(int arr1[], int &size, int index, int inc)//THIS FUNCTION INCREASES SIZE OF ARRAY AND UPDATE SIZE
{
	int * arr2 = new int[size + inc];
	int j = 0;
	int i;
	for (i = 0; i <= index; i++)
	{
		arr2[j] = arr1[i];
		j++;
	}
	int largest = findlargest(arr1, size);
	for (int a = 1; a <= inc; a++)
	{
		arr2[j] = largest + a;
		j++;
	}
	for (; i < size; i++)
	{
		arr2[j] = arr1[i];
		j++;
	}


	delete[]arr1;

	size = size + inc;
	return arr2;
}
void makerectangle(int array[], int &size, int index, bool kill)//THIS FUNCTION MAKES RECTANGULAR ARRANGMENT AND SHOW KILLED AND CURRENT PERSON
{
	bool var=true;
	int l, b;
	int n = size;
	if (size % 2 != 0)
	{
		n++;
	}
	HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hconsole, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	
	n = n / 2;
	if (n % 2 == 0)
	{
		l = n / 2;
		b = l;
	}
	else
	{
		b = n / 2;
		l = b + 1;
	}
	int x = 10, y = 10, count = 1;
	if (kill == false)
	{
		for (int i = 0; i < size; i++)
		{
			gotoxy(x, y);
			if (array[i] != 0)
			{
				if (i == index)
				{
					SetConsoleTextAttribute(hconsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
					cout << array[i];
					SetConsoleTextAttribute(hconsole, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				}
				else
				{
					cout << array[i];
				}
			}
			else
			{
				cout << " ";
			}
			if (count >= 1 && count <= l)
			{
				x = x + 3;
			}
			if (count > l && count <= l + b)
			{
				y = y + 3;
			}
			if (count > l + b && count <= (2 * l) + b)
			{
				x = x - 3;
			}
			if (count > (2 * l) + b && count <= ((2 * l) + (2 * b)))
			{
				y = y - 3;
			}
			count++;

		}
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			gotoxy(x, y);
			if (array[i] != 0)
			{
				if (i == index)
				{
					SetConsoleTextAttribute(hconsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
					cout << array[i];
					SetConsoleTextAttribute(hconsole, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				}
				else
				{
					cout << array[i];
				}
			}
			else
			{
				cout << " ";
				
			}
			if (count >= 1 && count <= l)
			{
				x = x + 3;
			}
			if (count > l && count <= l + b)
			{
				y = y + 3;
			}
			if (count > l + b && count <= (2 * l) + b)
			{
				x = x - 3;
			}
			if (count > (2 * l) + b && count <= ((2 * l) + (2 * b)))
			{
				y = y - 3;
			}
			count++;

		}
	}

}
int main()
{
	int initialpeople, arraysize, p, r,cp;
	cout << "ENTER THE INITIAL NUMBER OF PEOPLE:";
	cin >> initialpeople;
	if (initialpeople == 0)
	{
		cout << "ARE YOU KIDDING ME";
		return 0;
	}
	else if (initialpeople == 1)
	{
		cout << " 1 is winner";
		return 0;
	}
	arraysize = initialpeople;
	int *array=makeintarray(arraysize);
	intializearray(array, arraysize);
	srand((unsigned int)time(NULL));
	p = 5 + (rand() % 8);
	r = 1 + (rand() % (2*arraysize));
	cp = 0 + (rand() % (arraysize - 1));
	int addcount = 0, killcount = 0, kill = 0;
	makerectangle(array, arraysize, cp, false);
	Sleep(500);
	system("cls");
	while (arraysize>1)
	{ 
		if (killcount != r)
		{
			makerectangle(array, arraysize, cp, false);
			Sleep(500);
			system("cls");
		}
		if (killcount == r)
		{/*
			srand((unsigned int)time(NULL));*/
			r = 1 + (rand() % (2*arraysize));
			makerectangle(array, arraysize, cp, true);
			Sleep(500);
			system("cls");
			array=shrinkarray(array, arraysize, cp);
			killcount = 0;
			kill++;
		}
		
		if (addcount == p && kill<7) 
		{
	/*		srand((unsigned int)time(NULL));*/
			int randomindex = 0 + (rand() % (arraysize - 1));
			/*srand((unsigned int)time(NULL));*/
			int increase =1 + (rand() % 5);
			array=extendarray(array,arraysize,randomindex,increase);
			cp++;
			addcount = 0;
		}
		cp++;
		
		if (cp >= arraysize)
		{
			cp = 0;
		}
		
		killcount++;
		addcount++;
		
	}
	cout << array[0] << " is winner";
}