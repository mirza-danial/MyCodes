#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;
/*
	Global Variables 
	-savedSeq stores the sequence of vertices in 
	 the case when there exists a hamiltonian cycle
	-result stores the final distance if solution exists
*/
vector<int> savedSeq;
int result;


/*
	node struct for LinkedList
*/
template <class type>

struct node													//Template Structure of Node
{
	type data;
	node* next;
};


//****************************  Iterator Class*************************************
template<class t>
class Iterator
{
private:
	node<t>*current;
public:
	Iterator(node<t>* n = nullptr)				//constructor
	{
		current = n;
	}
	t&operator*()							//return data at iterator						
	{
		return current->data;
	}
	Iterator<t>&operator++()					//Increment operator overload
	{
		if (current != nullptr)
		{
			current = current->next;
		}
		return *this;
	}
	bool operator!=(Iterator<t>&it)				//Not equal operator overload
	{
		return  !(current == it.current);
	}
	node<t>*currentNode()						//Function that return current pointer of iterator
	{
		return current;
	}
};

//****************************  Linked List **************************************

template<class T>
class List
{
	node<T>*head;					//list head
public:
	List()					//default constructor
	{
		head = nullptr;
	}
	~List()				//Destructor
	{
		node<T> * temp = head;
		while (temp != nullptr)
		{
			node<T>*del = temp;
			temp = temp->next;
			delete del;
		}
	}


	Iterator<T> begin()				//Begin Function points iterator at start of list and return
	{
		Iterator<T> it(head);
		return it;

	}

	Iterator<T> end()				//Points iterator at nullptr and return 
	{
		Iterator<T> it;
		return it;
	}

	void insert(Iterator<T> it, T d)		//Insert a data after provided iterator value 
	{
		if (it.currentNode() != nullptr)
		{
			node<T>*current = it.currentNode();
			node<T>* temp = new node<T>;
			temp->data = d;
			temp->next = current->next;
			current->next = temp;
		}
	}

	T remove(Iterator<T> it)				//Remove data value after iterator value
	{
		T d;
		if (head != nullptr && it.currentNode() != nullptr)
		{
			node<T>*current = it.currentNode();
			if (current->next != nullptr)
			{
				d = current->next->data;
				node<T>*temp = current->next;
				current->next = temp->next;
				delete temp;
			}
		}
		return d;
	}

	void insertAtStart(T d)					//insert a data member at the start of the list
	{
		node<T>* temp = new node<T>;
		temp->data = d;
		temp->next = head;
		head = temp;
	}

	void insertAtEnd(T d)
	{
		node<T>*temp = new node<T>;
		temp->data = d;
		temp->next = nullptr;
		if (isEmpty())
		{
			head = temp;
		}
		else
		{
			node<T>*curr = head;
			while (curr->next != nullptr)curr = curr->next;
			curr->next = temp;
		}
	}

	T removeFromStart()						//remove member from start of the list
	{
		T d;
		if (head != nullptr)
		{
			node<T>*temp = head;
			d = head->data;
			head = head->next;
			delete temp;
		}
		return d;
	}

	bool isEmpty()							//return that whether list is empty or not
	{
		return (head == nullptr);
	}
};


//****************************  AdjListNode **************************************
/*	
	Object List of AdjListNode will be created to store weighta and value simultaneously
*/
class AdjListNode
{
public:
	int weight;
	int value;
};


//**************************** AdjencencyList **************************************
class AdjencencyList
{
private:
	List<AdjListNode>*L;		// Array of Linked List of Type AdjListNode
	int v;						//No of Vertices in Graph
	bool w;						//Is graph weighted or not?
public:
	/*
	Destructor for class
	*/
	~AdjencencyList()
	{
		delete[] L;
	}
	/*
	Functions return true when graph weighted otherwise false
	*/
	bool isWeighted()
	{
		return w;
	}
	/*
	Function Inputs data from file with certain format 
	for weighted format is
	3			no. of vertices
	1			is graph weighted or not
	0,1,4,2,11		vertices adjacent to 0 with weights of edge from 0 to that vertice next to vertex after ,
	1,2,6
	2,0,11
	
	for unweighted
	3			no. of vertices
	1			is graph weighted or not
	0,1			list of vertices adjacent to 0 seperated by comma
	1,2
	2,0
	*/

	void Input()
	{
		char values[100];
		int num, index;
		fstream input;
		input.open("file.txt");
		input >> v;
		input >> w;
		AdjListNode n;
		n.weight = -1;
		L = new List<AdjListNode>[v];
		if (!w)
		{
			while (!input.eof())
			{
				input >> values;
				char*token = strtok(values, ",");
				index = atoi(token);
				token = strtok(NULL, ",");

				while (token != NULL)
				{
					num = atoi(token);
					n.value = num;
					if (num < v && num>=0)
						L[index].insertAtStart(n);
					token = strtok(NULL, ",");
				}

			}
		}
		else
		{

			while (!input.eof())
			{
				input >> values;
				char*token = strtok(values, ",");
				index = atoi(token);
				token = strtok(NULL, ",");

				while (token != NULL)
				{
					num = atoi(token);
					n.value = num;
					token = strtok(NULL, ",");
					num = atoi(token);
					n.weight = num;
					if (num < v && num >= 0)
						L[index].insertAtStart(n);
					
					token = strtok(NULL, ",");
				}

			}
		}
		
	
	}
	/*
	Functions output Adjencency List on Console
	*/
	void Output()
	{
		cout << "No. Of Veritices : ";
		cout << v;
		if (w)
			cout << endl << "The Graph is Weighted"<<endl;
		else
			cout << endl << "The Graph is Unweighted"<<endl;
		
		Iterator<AdjListNode>it;
		for (int i = 0; i < v; i++)
		{
			for (it = L[i].begin(); it != L[i].end(); it++)
			{
			
				if (w)
				{
					cout << i << " -- " << (*it).weight << " --> " << (*it).value<<endl;
				}
				else
				{
					cout << i << " --> " << (*it).value<<endl;
				}
			}
		}
	}

	/*
	Question 2
	Hamiltonian Cycle
	return true when hamiltonian cycle exists else false 
	and if such cycle exists update global variables
	*/
	friend bool HamiltonianCycle(  AdjencencyList &obj)
	{
		if (obj.v == 1)
		{
			savedSeq.push_back(0);
			return true;
		}
		int*sequence = new int[obj.v];
		bool *visited = new bool[obj.v];
		for (int i = 0; i < obj.v; i++)
		{
			visited[i] = false;
		}
		vector<int> seq;
		bool temp=obj.unweightedCycle(0,visited,seq,0);
		savedSeq = seq;
		
		return temp;
	}
	/*
	Helper of HamiltonianCycle()
	*/
	bool unweightedCycle(int i, bool * visited, vector <int> &seq, int start)
	{
		
		visited[i] = true;
		seq.push_back(i);
		Iterator<AdjListNode> it;
		bool temp=false,rvalue=false;
		int a;
		for (it = L[i].begin(); it != L[i].end(); it++)
		{
			if (!visited[(*it).value])
			{
				temp=unweightedCycle((*it).value, visited, seq, start);
			}
			else
			{
				if (seq.size() == v)
				{
					if ((*it).value == start)
					{
						temp = true;
						savedSeq = seq;
					}
					else
						temp = false;
				}
				
			}
			if (temp == true)
				return true;
		}
		visited[i] = false;
		seq.pop_back();
		if (i == 0)
			return false;
		
	}

	/*
	Question 3
	MinHamiltonianCycle
	returns true if a Hamiltonian cycle exist else false
	if many of such solutions exists it update values of global variables according to the shortest path
	*/
	friend bool MinHamiltonianCycle(AdjencencyList &obj)
	{
		if (obj.v == 1)
		{
			savedSeq.push_back(0);
			result = 0;
			return true;
		}
		int*sequence = new int[obj.v];
		bool *visited = new bool[obj.v];
		for (int i = 0; i < obj.v; i++)
		{
			visited[i] = false;
		}
		vector<int> seq;
		int sol = 65536;
		int w = 0;
		bool temp = obj.weightedCycle(0, visited, seq, 0,sol,w);	
		result = sol;
		return temp;
	}
	/*
	Helper of MinHamiltonianCycle()
	*/
	bool weightedCycle(int i, bool * visited, vector <int> &seq, int start,int &sol,int w)
	{
		
		visited[i] = true;
		seq.push_back(i);
		Iterator<AdjListNode> it;
		bool temp = false,rvalue=false;
		int a;
		for (it = L[i].begin(); it != L[i].end(); it++)
		{
			if (!visited[(*it).value])
			{
				w = w + (*it).weight;
				temp = weightedCycle((*it).value, visited, seq, start,sol,w);
				w = w - (*it).weight;
				
			}
			else
			{
				if (seq.size() == v)
				{
					if ((*it).value == start)
					{
						temp = true;
						if (w + (*it).weight< sol)
						{
							sol = w + (*it).weight;
							savedSeq = seq;
						}
					}
					
				}

			}
			if (temp)
				rvalue = true;
			
		}
		visited[i] = false;
		seq.pop_back();
		return rvalue;
	
	}

};

	
//***************************** Main****************************************
void main()
{
	AdjencencyList a;
	a.Input();
	a.Output();
	if (a.isWeighted())
	{
		if (MinHamiltonianCycle(a))
		{
			cout << "Solution Exists . " <<endl<< "The Minimum Distance is :";
			cout << result<<endl;
			for (int i = 0; i < savedSeq.size(); i++)
				cout << savedSeq[i] << "-->";
			cout << 0 << endl;
		}
		else
			cout << "No Solution Exists !";
	}
	else
	{
		if (HamiltonianCycle(a))
		{
			cout << "Solution Exists. "<<endl;
			for (int i = 0; i < savedSeq.size(); i++)
				cout << savedSeq[i] << "-->";
			cout << 0;
		
		}
		else
			cout << "No Solution Exists !";

	}
}