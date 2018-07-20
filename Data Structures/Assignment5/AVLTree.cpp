#include<iostream>
#include<cmath>
using namespace std;
template <class T>
struct node{
	T data;
	node <T>*left;
	node<T>*right;
	int height;
};

template <class T>
class Queue
{
	T* queue;
	int maxsize, size;
	int front;
	int rear;
public:
	Queue(double s = 10)
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



template <class T>
class AVLtree
{
private:
	node<T>*root;
public:
	/*
	Default Constructor
	*/

	AVLtree()
	{
		root = nullptr;
	}

	/*
	Parametric Constructor
	*/
	AVLtree(T d)
	{
		root = new node<T>;
		root->data = d;
		root->height = 1;
		root->left = root->right = nullptr;
	}


	/*
	Get height of the node 
	return 0 if nullptr
	*/
	int geth(node<T> *r)
	{
		if (r == nullptr)
			return 0;
		else 
			return r->height;
	}
	/*
	rotate the given node
	towards right
	*/
	void rotateright(node<T>*&x)
	{
		node<T>*y = x->left;
		x->left = y->right;
		y->right = x;

		x->height = 1 + max(geth(x->left), geth(x->right));
		y->height = 1 + max(geth(y->left), geth(y->right));
		//x = y;
		if (x == root)
			root = y;
		else 
			x=y;
	}
	/*
	rotates the given node towards left
	*/
	void rotateleft(node<T>*&x)
	{
		
		node <T> *y= x->right;
		x->right = y->left;
		y->left = x;
		

		x->height = 1 + max(geth(x->left), geth(x->right));
		y->height = 1 + max(geth(y->left), geth(y->right));
		
		
		if (x == root)
			root = y;
		else
			x = y;
	}
	/*
	rotate the child node towards right
	and parent node towards left
	*/
	void Drotateleft(node<T>*&x)
	{
		rotateright(x->right);
		rotateleft(x);
	}
	
	/*
	rotate the child node towards left
	and parent node towards right
	*/
	void Drotateright(node<T>*&x)
	{
		rotateleft(x->left);
		rotateright(x);
	}
	/*
	removes the predecessor of the node 
	return its data 
	*/
	T removepredecessor(node<T> * &r)
	{
		node<T> * current = r->left;
		node<T> * parent = r;

		while (current->right != nullptr)
		{
			parent = current;
			current = current->right;
		}

		T temp = current->data;

		remove(r, current->data);

		return temp;


	}
	/*
	Get the balance factor of the given node
	*/
	int getBalance(node<T> * n)
	{
		if (n == nullptr)
			return 0;
		return (geth(n->left) - geth(n->right));
	}
	/*
	removes a node
	and perform rotations if needed
	*/
	bool remove(node<T> * &r, T d)
	{
		if (r == nullptr)
		{
			return false;
		}

		node<T> * current = r;
		node<T> * parent = r;
		Stack <node<T>*> s(r->height);

		while (current != nullptr && current->data != d)
		{
			parent = current;
			s.push(parent);
			if (current->data > d)
			{
				current = current->left;
			}
			else if (current->data < d)
			{
				current = current->right;
			}
		}

		if (current == nullptr)
		{
			return false;
		}

		if (current == root && (root->left==nullptr || root->right==nullptr))
		{
			
			if (root->left == nullptr)
			{
				current = current->right;
				delete root;
				root = current;
			}
			
			else
			{
				current = current->left;
				delete root;
				root = current;
			}
			return true;
		}

		if (current->left == nullptr && current->right == nullptr)
		{
			if (parent->left == current)
			{
				parent->left = nullptr;
			}
			else
			{
				parent->right = nullptr;
			}
			delete current;
		}
		else if (current->left == nullptr && current->right != nullptr)
		{
			if (parent->left == current)
			{
				parent->left = current->right;
			}
			else
			{
				parent->right = current->right;
			}
			delete current;
		}
		else if (current->left != nullptr && current->right == nullptr)
		{
			if (parent->left == current)
			{
				parent->left = current->left;
			}
			else
			{
				parent->right = current->left;
			}
			delete current;
		}
		else if (current->left != nullptr && current->right != nullptr)
		{
			current->data = removepredecessor(current);
			s.push(current);
		}


		node<T>* x;
		node<T>* p;
		node<T>*temp;
		int balancefact;
		bool value = false;
		while (!s.isEmpty())
		{
			s.pop(x);
			temp = x;
		
			balancefact = getBalance(x);

			if (balancefact > 1 && getBalance(x->left) >= 0)
				rotateright(x);


			if (balancefact > 1 && getBalance(x->left) < 0)
			{
				Drotateright(x);
			}

			if (balancefact < -1 && getBalance(x->right) <= 0)
				rotateleft(x);


			if (balancefact < -1 && getBalance(x->right) > 0)
			{
				Drotateleft(x);
			}

			x->height = 1 + max(geth(x->left), geth(x->right));
			value = s.pop(p);

			if (value)
			{
				s.push(p);
				if (p->left == temp)
					p->left = x;
				else
					p->right = x;
			}


		}


		return true;
	}
	/*
	calls working remove function
	*/
	bool remove(T d)
	{
		return remove( root,d);
	}
	/*
	prints the data item of  a node 
	*/
	void printdata(node<T> *r)
	{
		if (r != nullptr)
			cout << r->data << endl;
	}
	/*
	inserts a given number and perform rotation
	*/
	bool insert(T d)
	{
		node<T>*temp = new node<T>;
		temp->data = d;
		temp->left = temp->right = nullptr;
		temp->height = 1;


		if (root == nullptr)
		{
			root = temp;
			return  true;
		}

		else
		{
			Stack<node<T>* > s(root->height);

			node<T>*current = root;
			node<T>*parent=nullptr;
			while (current != nullptr)
			{
				parent = current;
				s.push(parent);
				if (current->data == d)
					return false;
				else if (current->data > d)
					current = current->left;
				else if (current->data < d)
					current = current->right;

			}

			if (d > parent->data)
				parent->right = temp;
			else
				parent->left = temp;

			node<T>* x;
			node<T>* p;
			int balancefact;
			bool value = false;
			while (!s.isEmpty())
			{
				s.pop(x);
				balancefact = geth(x->left) - geth(x->right);
				temp = x;

				if (balancefact == 2)
				{
					if (x->left->data > d)
						rotateright(x);
					else
						Drotateright(x);
					
				}
				else if (balancefact == -2)
				{
					if (x->right->data < d)
						rotateleft(x);
					else
						Drotateleft(x);

				}

				x->height = 1 + max(geth(x->left), geth(x->right));
				value=s.pop(p);
				
				if (value)
				{
					s.push(p);
					if (p->left == temp)
						p->left = x;
					else
						p->right = x;
				}
			}
		}
		return true;
	}
	/*
	returns maximum out of 2
	*/
	int max(int x, int y)
	{
		if (x > y)
			return x;
		return y;
	}


	
	/*
	prints a tree in a level wise form 
	each level of tree is printed in a row
	*/
	void print()
	{

		double n = geth(root);
		n--;
		double p = pow(2, n);
		Queue<node<T>*> q(p);
		node<T>* temp;
		q.enqueue(root);
		int count = 0;
		int var = 1;
		int a = 1;
	
		while (!q.isEmpty())
		{

			q.dequeue(temp);
			if (temp != nullptr)
			{
				q.enqueue(temp->left);
				q.enqueue(temp->right);

				cout << geth(temp) << " ; ";
				printdata(temp);
			}
		}
	}

	
	/*
	search a particular node
	returns its address if found
	returns nullptr if not found
	*/
	node<T> *search(T d)
	{
		if (root == nullptr)
			return nullptr;
		node<T> * current = root;
		while (current != nullptr && current->data != d)
		{
			if (current->data > d)
				current = current->left;
			else if (current->data < d)
				current = current->right;
		}
		return current;
	}
	/*
	destructor
	*/
	~AVLtree()
	{
		double n = geth(root);
		n--;
		double p = pow(2, n);
		Queue<node<T>*> q(p);
		node<T>* temp;
		q.enqueue(root);
		while (!q.isEmpty())
		{
			q.dequeue(temp);
			if (temp != nullptr)
			{
				if (temp->left !=nullptr)
					q.enqueue(temp->left);
				if (temp->right != nullptr)
					q.enqueue(temp->right);
				delete temp;
			}
		}

	}

};


void driver()
{
	int operation;
	int entry;
	bool loop = true;
	AVLtree<int> Tree;
	while (loop)
	{
		system("COLOR F0");
		cout << "************************************************* AVL Tree ********************************************************" << endl
			<< "1. Insert a new entry." << endl
			<< "2. Delete an existing entry." << endl
			<< "3. Search for an existing entry." << endl
			<< "Press 4 to exit " << endl
			<< "Enter a corresponding number to perform an operation  : ";
		cin >> operation;
		if (operation == 1)
		{
			system("COLOR F0");
			system("cls");
			cout << "************************************************* Insert A  New Entry ********************************************************" << endl;
			cout << "Enter the entry you want to insert : ";
			cin >> entry;

			if (Tree.insert(entry))
			{
				cout << entry << " is succesfully entered in tree";
				cout << endl << "Current Tree :" << endl;
				Tree.print();
			}
			else
				cout << "Operation Failed!";

			system("pause>NULL");

		}
		else if (operation == 2)
		{
			system("cls");
			system("COLOR C0");
			cout << "************************************************* Delete an Existiong Entry ********************************************************" << endl;
			cout << "Enter the value : ";
			cin >> entry;
			if (Tree.remove(entry))
			{
				cout << entry << " is successfully removed ";
				cout << endl << "Current Tree :" << endl;
				Tree.print();
			}
			else
				cout << "Operation Failed !";

			system("pause>NULL");
		}
		
		else if (operation == 3)
		{
			system("COLOR F0");
			system("cls");
			cout << "************************************************* Search ********************************************************" << endl;

			cout << "Enter a value : ";
			cin >> entry;
			node<int>* temp = Tree.search(entry);
			if (temp == nullptr)
				cout << "No such entry is present in tree !";
			else
			{
				cout << "This entry is present is tree" << endl;
				cout << "Details: " << endl;
				cout << "Height: " << temp->height<<endl;
				cout << "Left Child: ";
				Tree.printdata(temp->left);
				cout <<endl<< "Right Child: " ;
				Tree.printdata(temp->right);
			}

			system("pause>NULL");
		}
		
		else if (operation == 4)
		{
			loop = false;
		}
		else
		{
			cout << "Please enter a number corresponding to a certain operation  .";
		}
		system("cls");
	}


}

int main()
{
	driver();
	return 0;
}