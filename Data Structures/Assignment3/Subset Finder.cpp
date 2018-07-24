#include<cmath>
#include<iostream>
using namespace std;

/*
	Queue template class
*/

template <class T>
class Queue
{
	T* queue;
	int maxsize, size;
	int front;
	int rear;
public:
	Queue(int s = 10)
	{
		maxsize = s;
		size = 0;
		front = -1;
		rear = 0;
		queue = new T[maxsize];
	}
	~Queue()
	{
		delete[]queue;
	}
	bool isEmpty()
	{
		return (size == 0);
	}
	bool isFull()
	{
		return (size == maxsize);
	}
	bool enqueue(T data)
	{
		if (!isFull())
		{
			queue[rear] = data;
			rear = (rear + 1) % maxsize;
			size++;
			return true;
		}
		return false;
	}
	bool dequeue(T&data)
	{
		if (!isEmpty())
		{
			front = (front + 1) % maxsize;
			data = queue[front];
			size--;
			return true;
		}
		return false;
	}
};

/*
	Set Class
*/

class Set
{
private:
	int * array;
	int size;
	int fsize;

	/*
		extendArray Function
		double the size of the array
	*/
	void extendarray()
	{
		size *= 2;
		int *temp = new int[size];
		for (int i = 0; i < fsize; i++)
		{
			temp[i] = array[i];
		}
		delete[]array;
		array = temp;

	}
public:

	/*
		Parametric Constructor
	*/
	Set(int s)
	{
		size = s;
		fsize = 0;
		array = new int[size];
	}
	/*
		Default Constructor
	*/
	Set()
	{
		array = nullptr;
		size = fsize = 0;
	}
	/*
		Copy Constructor
	*/
	Set(const Set& obj)
	{
		fsize = 0;
		size = obj.size;
		array = new int[size];
		for (int i = 0; i < obj.fsize; i++)
		{
			array[i] = obj.array[i];
			fsize++;
		}
	}
	/*
		Destructor
	*/
	~Set()
	{
		delete[] array;
	}

	/*
		Assignment Operator Overload
		- Do deep copy
	*/
	const Set& operator=(const Set& obj)
	{
		fsize = 0;
		size = obj.size;
		delete[]array;
		array = new int[size];
		for (int i = 0; i < obj.fsize; i++)
		{
			array[i] = obj.array[i];
			fsize++;
		}
		return *this;
	}
	
	/*
		Prints the Set
	*/
	void output()
	{
		cout << "{ ";
		for (int i = 0; i < fsize; i++)
		{
			cout << array[i] << " ";
			if (i != fsize - 1)
			{
				cout << ", ";
			}
		}
		cout << " }" << endl;
	}


	/*
		add
		-insert new element at the end of the Set
	*/
	void add(int x)
	{
		if (fsize >= size)
			extendarray();
		array[fsize++] = x;
	}

	/*
		remove
		-Removes the last element of the Set
	*/
	void remove()
	{
		if (fsize > 0)
			fsize--;
	}

	/*
		getlast Function
		- Return the last element of the Set
	*/
	int getLast()
	{
		return array[fsize - 1];
	}
};


/*
	AllSubSet Function
	Find out all the non-empty subset of a set of form
	{1,2,3,...,n}
*/

void allSubSets(int n)
{
	int v = pow(2,n);
	Queue<Set> q(v);
	Set a(1);
	a.add(1);
	
	q.enqueue(a);
	int count = 1;
	while (!q.isEmpty())
	{
		Set s(1);
		q.dequeue(s);
		cout <<"Subset number "<< count++ <<" : "<< endl;
		s.output();
		if (s.getLast() < n)
		{
			Set r = s;
			r.remove();
			r.add(s.getLast() + 1);
			q.enqueue(r);
			s.add(s.getLast() + 1);
			q.enqueue(s);
		}
	}

}

/*
	Main Function
*/

int main()
{
	int n;
	cout << "Enter  nth term of set :";
	cin >> n;
	while (n <= 0)
	{
		system("cls");
		cout << " Please enter a number greater than 0 \n";
		cout << "Enter  nth term of set :";
		cin >> n;
	}
	allSubSets(n);
	return 0;
}