#include<iostream>
using namespace std;

/*
	POSTION CLASS STORES LOCATION OF QUEEN
	IN X AND Y FORMAT
*/
class position
{
public:
	int x;
	int y;
	position()
	{
		x = 0; y = 0;
	}
	position(int a, int b)
	{
		x = a;
		y = b;
	}

	friend ostream& operator<<(ostream& osObj, const position& pObj)
	{
		osObj << "Queen number " << pObj.x << " is placed in column number " << pObj.y << endl;
		return osObj;
	}
};

/*
	STACK TEMPLATE CLASS
*/

template<class T>
class Stack
{
private:
	int size;
	T*stack;
	int stkptr;
public:
	/*
		CONSTRUCTOR
	*/
	Stack(int s)		
	{
		size = s;
		stkptr = 0;
		stack = new T[size];
	}
	/*
		DESTRUCTOR
	*/
	~Stack()
	{
		delete[]stack;
	}
	/*
		COPY CONSTRUCTOR
	*/
	Stack(const Stack& obj)
	{
		size = obj.size;
		stkptr = obj.stkptr;
		stack = new T[size];
		for (int i = 0; i < stkptr; i++)
		{
			stack[i] = obj.stack[i];
		}
	}
	/*
		ASSIGNMENT OPERATOR
	*/
	const Stack& operator=(const Stack& obj)
	{
		size = obj.size;
		stkptr = obj.stkptr;
		for (int i = 0; i < stkptr; i++)
		{
			stack[i] = obj.stack[i];
		}

		return *this;
	}
	/*
		PRINT FUNCTION
		PRINTS WHOLE STACK
	*/
	void print()
	{
		for (int i = 0; i < stkptr; i++)
		{
			cout << stack[i];
		}
		cout << endl;
	}

	/*
		Stack Functions
	*/
	bool isEmpty()
	{
		return (stkptr == 0);
	}
	bool isFull()
	{
		return (stkptr == size);
	}
	bool push(T data)
	{
		if (!isFull())
		{
			stack[stkptr] = data;
			stkptr++;
			return true;
		}
		return false;
	}
	bool pop(T& data)
	{
		if (!isEmpty())
		{
			stkptr--;
			data = stack[stkptr];
			return true;
		}
		return false;
	}
	T top()
	{
		if (!isEmpty())
		{
			return stack[stkptr - 1];
		}
	}
};

/*
	TRAVERSE FUNCTION  TAKES COLUMN AND STACK AS PARAMETERS AND 
	CHECK FOR POSSIBLE SOLUTION ONWARDS FROM THE GIVEN 
	POSITION OF COLUMN THEN CHANGES THE VALUE OF
	COLUMN ACCORDINGLY

	The function returns false when:
		-row is greater than the total number of rows in system
		-col is greater than the total number of columns in system
		-No possible solution is found
*/

bool traverse(int& row, int& col,const Stack<position> &s,int n)
{
	if (row > n || col > n)			
		return false;

	Stack<position> temp = s;
	int count=1;
	bool flag;

	for (int c=col+1; c <= n; c++)
	{
		count = 1;
		temp = s;
		flag = true;
		while (!temp.isEmpty())
		{
			position a;
			temp.pop(a);
			if (c == a.y || c == a.y + count || c == a.y - count)
			{
				flag = false;
				break;
			}
			count++;
		}
		if (flag == true)
		{
			col = c;
			return true;
		}



	}
	return false;
}
/*
	NQUEEN FUNCTION 
*/
void NQueen(int n)
{
	int count = 1;
	Stack<position> s(n);
	int row = 1, col = 0;

	while (!(s.isEmpty()) || (row == 1 && col <= n))
	{
		while (traverse(row, col, s, n))
		{
			position p(row, col);
			row++;
			col = 0;
			s.push(p);
		}
		if (s.isFull())
		{
			cout <<"Solution number "<<count << " : " << endl;
			count++;
			s.print();
			cout << endl;
		}

		if (!traverse(row, col, s, n))
		{
			position p;
			s.pop(p);
			row = p.x;
			col = p.y;
		}
	}
}


/*
	MAIN FUNCTION
*/
int main()
{
	int n;
	cout << "Enter size of the board : ";
	cin >> n;
	while (n <= 0)
	{
		system("cls");
		cout << " Please enter a number greater than 0 \n";
		cout << "Enter size of the board : ";
		cin >> n;
	}
	cout << "Following are the possible solutions of the problem :"<<endl;
	NQueen(n);
	return 0;
}