
#include<iostream>
#include<time.h>
using namespace std;
//***************************** NODE **********************************
struct node
{
	int data;
	node* next;
};


//***************************** Class Iterator*************************
class Iterator{
private:
	node* current;
public:
	Iterator(node*n = nullptr)			//paratmetric cnstructor
	{
		current = n;
	}
	Iterator &operator++()				//++ operator overload : move the iterator to next node
	{
		if (current != nullptr)
		{
			current = current->next;
		}
		return *this;
	}
	node*operator*()					//Returns the current node
	{
		return current;
	}
	bool operator!=(Iterator& listIt)	//checks the equality
	{
		return !(current == listIt.current);
	}
};
//*********************************** CLass LinkedList************************************
class CLinkedList
{
private:
	node*head;
	node*tail;
public:
	CLinkedList()		// Default Constructor
	{
		head = nullptr;
	}
	void insertNode(int d)		// inserts a new node at the end of the linked list
	{
		node*temp = new node;
		temp->data = d;
		if (head == nullptr)	//if list is empty head points at tail which points at temp
		{
			head = tail = temp;
		}
		else					//if list not empty new node is inserted at end of the lis
		{
			tail->next = temp;
			tail = temp;
		}
		tail->next = head;
	}
	int reomoveNode(Iterator& it)		//removes next of the node pointed by iterator and return its data
	{
		if (head != nullptr && head != tail)		//removes unless list contain only one element
		{
			//cout << "head" << head->data << endl;
			//cout << "tail" << tail->data << endl;
			int value;
			node*temp = *it;
			if (temp->next == head)		// if head is the one to be removed
			{
				head = head->next;
			}
			else if (temp->next == tail)	// if tail is to be removed
			{
				tail = temp;
			}
			node*del = temp->next;
			temp->next = del->next;
			value = del->data;
			delete del;
			return value;
		}
	}
	Iterator start()		//return a pointer pointing at head
	{
		Iterator ListIt(head);
		return ListIt;
	}
	Iterator end()			// return a pointer pointing at end
	{
		Iterator ListIt(tail);
		return ListIt;
	}
	bool OneLeft()		//return true when list contain only one element
	{
		return (head == tail && head != nullptr);
	}
	~CLinkedList()
	{
		delete head;	// deletes head only because at the end of the game the only existing node will be head 
	}
};

//********************************* Class Game *******************************************
class Game
{
	int persons;		// number of people
public:
	Game(int size)		//parameric constructor
	{
		persons = size;
	}
	void startGame()	//game starts
	{
		if (persons > 0)		//check person should be greater than zero
		{
			srand(time(NULL));			//generates randon number after which node will be deleted
			int killafter = rand() % 10 + 1;
			int count = 1;
			CLinkedList circle;			//linked list object created
			for (int i = 1; i <= persons; i++)		//inserts number of persons
			{
				circle.insertNode(i);
			}
			Iterator it;		//iterator to iterate linked list
			for (it = circle.start(); !circle.OneLeft(); it++)		//loop goes on unltill only one person is remaining
			{
				if (count == killafter)			//time to remove a person
				{
					count = 0;					//counter reset
					cout << "Random value :" << killafter << endl;
					killafter = rand() % 10 + 1;		// new random value generated
					cout << circle.reomoveNode(it) << " is removed :( " << endl;
				}
				count++;
			}
			it = circle.start();	//iterator pointing at start
			node*winner = *it;		//winner is head
			cout << "The winner is :" << winner->data;
		}
		else
		{
			cout << "Game can't be played with less than 1 person :(.";
		}
		system("pause>NULL");
	}

};

//************************************ Driver **************************************

int main()
{
	int size, value;
	cout << "Enter the size of circular linked list : ";
	cin >> size;
	Game g(size);
	g.startGame();
	return 0;
}