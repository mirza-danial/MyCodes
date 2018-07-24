#include<iostream>
#include<fstream>
#include<cstring>
#include<stdlib.h>
#include"matrix.h"
#include<time.h>
using namespace std;
//********************************* CONSTRUCTORS ******************************
Matrix::Matrix()					//Defaoult Constructor
{
	m = nullptr;
	row = 0;
	col = 0;
}
Matrix::Matrix(const Matrix &obj)		// Copy Constructor
{
	m = nullptr;
	*this = obj;
}
Matrix::Matrix(char*array)			//Parametric Constructor
{
	int rows, columns, num, r = 0, c = 0;
	char values[100];
	fstream input;
	input.open(array);
	input >> rows;
	input >> columns;
	row = rows;
	col = columns;
	m = new int*[rows];
	for (int i = 0; i < rows; i++)
	{
		m[i] = new int[columns];
	}
	while (!input.eof())
	{
		input >> values;
		char*token = strtok(values, ",");
		while (token != NULL)
		{
			num = atoi(token);
			if (c < columns)
			{
				m[r][c] = num;
				c++;
			}
			token = strtok(NULL, ",");
		}
		c = 0; r++;
	}
}
Matrix::Matrix(int rows,int columns)				//Parametric Constructor
{
	col = columns;
	row = rows;
	m = new int*[rows];
	
	for (int i = 0; i < rows; i++)
	{
		m[i] = new int[columns];
		for (int j = 0; j < columns; j++)
		{

			m[i][j] = rand() % 99;
		}
	}	
}
//************************ OPERATOR OVERLOADING ****************************
const Matrix& Matrix::operator=(const Matrix &obj)
{
	int**temp = new int*[obj.row];
	for (int i = 0; i < obj.row; i++)
	{
		temp[i] = new int[obj.col];
		for (int j = 0; j < obj.col; j++)
		{
			temp[i][j] = obj.m[i][j];
		}
	}
	for (int i = 0; i < row; ++i)
	{
		delete[] m[i];
	}
	delete[]m;
	m = temp;
	col = obj.col;
	row = obj.row;
	return*this;
}
Matrix Matrix:: operator+(const Matrix& obj)		// SUPPOSING THAT ADDITION IS POSSIBLE As Required
{
	if (row == obj.row && col == obj.col)
	{
		Matrix temp(row,col);
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				temp.m[i][j] = m[i][j] + obj.m[i][j];
			}
		}
		return temp;
	}
}
Matrix Matrix:: operator-(const Matrix& obj)	// SUPPOSING THAT SUBTRACTION IS POSSIBLE As Required
{
	if (row == obj.row && col == obj.col)
	{
		Matrix temp(row, col);
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				temp.m[i][j] = m[i][j] - obj.m[i][j];
			}
		}
		return temp;
	}
}
bool Matrix::operator==(const Matrix& obj)
{
	if (row != obj.row || col != obj.col)
	{
		return false;
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (m[i][j] != obj.m[i][j])
			{
				return false;
			}
		}
	}
	return true;
}
bool Matrix::operator!=(const Matrix& obj)			//NOT REQUIRED IN HW4
{
	if (row != obj.row || col != obj.col)
	{
		return true;
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (m[i][j] != obj.m[i][j])
			{
				return true;
			}
		}
	}
	return false;
}
void Matrix::operator+=(int num)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			m[i][j] = num + m[i][j];
		}
	}
}
void Matrix::operator*=(int num)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			m[i][j] = num * m[i][j];
		}
	}
}
Matrix operator-(const Matrix & obj)
{
	for (int i = 0; i < obj.row; i++)
	{
		for (int j = 0; j < obj.col; j++)
		{
			obj.m[i][j] = -obj.m[i][j];
		}
	}
	return obj;
}
Matrix Matrix::operator*(const Matrix& obj)	// SUPPOSING THAT MULTIPLICATION IS POSSIBLE As Required
{
	if (col == obj.row)
	{
		int i, j, k;
		Matrix temp(row, obj.col);
		for (i = 0; i < row; ++i)
		{
			for (j = 0; j < obj.col; ++j)
			{
				temp.m[i][j] = 0;
				for (k = 0; k < col; ++k)
				{
					temp.m[i][j] += m[i][k] * obj.m[k][j];
				}
			}
		}
		return temp;
	}

}
int*Matrix::operator[](int num)
{
	return m[num];
}
//************************** FUNCTIONS ********************************************
void Matrix::transpose()
{
	int **array = new int*[col];
	for (int i = 0; i < col; i++)
	{
		array[i]= new int[row];
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			array[j][i] = m[i][j];
		}
	}
	for (int i = 0; i < row; i++)
	{
		delete[]m[i];
	}
	delete[]m;
	m = array;
	int temp = row;
	row = col;
	col = temp;
}

int Matrix::getNumRows()
{
	return row;
}
int Matrix::getNumCols()
{
	return col;
}
//******************************DESTRUCTOR*********************************
Matrix::~Matrix()
{
	if (m != nullptr)
	{
		for (int i = 0; i < row; i++)
		{
			delete[]m[i];
		}
		delete[]m;
	}
}
