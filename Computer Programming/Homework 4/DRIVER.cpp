#include<iostream>
#include<fstream>
#include<cstring>
#include<stdlib.h>
#include"matrix.h"
#include<time.h>
using namespace std;
void printMatrix(Matrix& m)
{
	for (int i = 0; i < m.getNumRows(); i++)
	{
		for (int j = 0; j < m.getNumCols(); j++)
		{
			if (m[i][j] >= 0)
				cout << " ";
			cout << m[i][j];
			if (m[i][j]>9)
				cout << " ";
			else
				cout << "  ";
		}
		cout << endl;
	}
}
int main()
{
	Matrix m1;//empty 0x0 matrix
	srand(time(NULL));
	Matrix m2("mat1.txt"), m3("m3.txt");//read from files
	Matrix m5(5, 7);//create a 5x7 matrix with random values
	Matrix m6(2, 4);
	cout << "m2" << endl;
	printMatrix(m2);
	cout << "m3" << endl;
	printMatrix(m3);
	m1 = m2 + m3;//add matrices
	cout << "m1" << endl;
	printMatrix(m1);
	Matrix m4 = m2 - m3;//subtract matrices
	cout << "m4" << endl;
	printMatrix(m4);
	if (m1 == m4){
		cout << "m1 and m4 are equal matrices";
	}
	m5 = m1*m4;//matrix multiplication (assume compatability)
	cout << "m5"<<endl;
	printMatrix(m5);
	m5.transpose();//convert nxm to mxn matrix
	cout << "m5 transpoose" << endl;
	printMatrix(m5);
	m2 = -m2;//negates all elements of m2
	cout << "m2 = -m2" << endl;
	printMatrix(m2);
	m2 += 5;//adds 5 to all elements of m2
	cout << "m2 += 5" << endl;
	printMatrix(m2);
	m2 *= 5;//multiplies 5 to all elements of m2
	cout << "m2 *= 5" << endl;
	printMatrix(m2);
	return 0;
}