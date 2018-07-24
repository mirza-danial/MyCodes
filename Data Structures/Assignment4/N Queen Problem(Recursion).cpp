#include<iostream>
using namespace std;

void PrintSolution(int arr[], int n, int &solNum)
{
	cout <<"Solution "<< ++solNum<<endl;
	for (int i = 0; i < n; i++)
	{
		cout << "Queen number " << i + 1 << " is placed in column number " << arr[i]<<endl;
	}
	cout << endl;
}
bool Check(int arr[],int row,int col)
{
	int count = 1;
	for (int i = row -2; i >= 0; i--)
	{
		if (arr[i] == col || arr[i] == col + count || arr[i] == col - count)
		{
			return false;
		}
		count++;
	}
	return true;
}
void nQueen(int arr[],int boardSize,int rowNum,int &solCount)
{
	if (rowNum == boardSize + 1)
	{
		PrintSolution(arr, boardSize, solCount);
	}

	else
	{
		for (int i = 1; i <= boardSize; i++)
		{
			if (Check(arr, rowNum, i ))
			{
				arr[rowNum - 1] = i;
				nQueen(arr, boardSize, rowNum + 1, solCount);
			}
		}
	}
}

int main()
{
	int n;
	cout << "Enter the size of the board : ";
	cin >> n;
	while (n < 1)
	{
		system("cls");
		cout << "Board size cannot be nagative or zero !" << endl << "Enter the size of the board : ";
		cin >> n;
	}
	int*arr = new int[n];
	int a = 0;
	nQueen(arr, n, 1, a);

	delete[] arr;
}