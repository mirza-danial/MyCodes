
#include<iostream>
#include<string>
using namespace std;



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
class SLinkedList
{
	node<T>*head;					//list head
public:
	SLinkedList()					//default constructor
	{
		head = nullptr;
	}
	~SLinkedList()				//Destructor
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

//************************** BLock Class ***************************
class Block{
public:
	int startSector;		//sector number storing starting sector of contigous memory
	int endSector;			//sector number storing ending sector of contigous memory
	Block()
	{
		startSector = 0;
		endSector = 0;
	}
	Block(Block &obj)
	{
		startSector = obj.startSector;
		endSector = obj.endSector;
	}
};


//************************* File Class ******************************

class File{
public:
	string name;			// name of file
	int size;				//size of file
	SLinkedList<Block> blockList;			//block contained by file

	File()
	{

	}
	File(File& obj)
	{
		name = obj.name;
		size = obj.size;

		Iterator<Block> bit;
		bit = obj.blockList.begin();
		while (bit != obj.blockList.end())
		{
			Block *b = new Block;
			b->startSector = (*bit).startSector;
			b->endSector = (*bit).endSector;
			blockList.insertAtEnd(*b);
			bit++;
		}
	}

	File& operator=(File& obj)
	{
		name = obj.name;
		size = obj.size;

		Iterator<Block> bit;
		bit = obj.blockList.begin();
		while (bit != obj.blockList.end())
		{
			Block *b = new Block;
			b->startSector = (*bit).startSector;
			b->endSector = (*bit).endSector;
			blockList.insertAtEnd(*b);
			bit++;
		}
		return *this;
	}



};


//************************** File System Class ***********************
class FileSystem{
private:
	SLinkedList<Block> pool;		//list of available blocks of memory
	SLinkedList<File> files;		//list of files stored 
	char * disk;					//memory location where content of file will be stored
	int numOfSectors;				//total number of sectors in the disk
	int sizeOfSectors;				//size of a single sector
public:
	FileSystem(int size, int sectors)		// Parametric Constructor
	{

		numOfSectors = sectors;
		sizeOfSectors = size;
		disk = new char[numOfSectors*sizeOfSectors];			//assigning memory to the disk
		Block one;
		one.startSector = 1;
		one.endSector = numOfSectors;
		pool.insertAtStart(one);
	}


	bool SaveFile(int fsize, char*fcontent, string& fname)		//Save File Function
	{
		//*************************** Part to check if file with same name exist before ***********************************
		Iterator<File> lit;
		lit = files.begin();
		while (lit != files.end())
		{
			if ((*lit).name == fname)
				return false;
			lit++;
		}

		//****************************Part to check if number of sectors available can contain the file ************************
		int poolbytes = 0;
		Iterator<Block> it;
		it = pool.begin();
		while (it != pool.end())
		{
			int i = (*it).startSector;
			while (i != (*it).endSector)
			{
				i++;
				poolbytes++;
			}
			poolbytes++;

			it++;
		}

		if (poolbytes*sizeOfSectors < fsize)
			return false;


		//*************************** Part to Save the file *******************************************
		File*f = new File;

		f->name = fname;
		f->size = fsize;
		int sectors_required = fsize / sizeOfSectors;
		if (fsize%sizeOfSectors != 0)
		{
			sectors_required++;
		}
		int sector_count = 0;

		it = pool.begin();
		while (it != pool.end())
		{
			sector_count = ((*it).endSector - (*it).startSector) + 1;
			if (sector_count < sectors_required)
			{
				Block a;
				it++;
				a = pool.removeFromStart();
				f->blockList.insertAtStart(a);
				sectors_required -= sector_count;
			}
			else if (sector_count == sectors_required)
			{
				Block a;
				it++;
				a = pool.removeFromStart();
				f->blockList.insertAtStart(a);
				break;
			}
			else
			{
				int newstart = (*it).startSector + sectors_required;
				Block a;
				a.startSector = (*it).startSector;
				a.endSector = newstart - 1;
				f->blockList.insertAtStart(a);
				(*it).startSector = newstart;
				break;
			}
		}

		Iterator<Block> blit;
		blit = f->blockList.begin();
		int i = 0;
		while (blit != f->blockList.end())
		{
			int start_sector = (*blit).startSector;
			int end_sector = (*blit).endSector;
			for (int j = sizeOfSectors*(start_sector - 1); j < sizeOfSectors*end_sector && i<fsize; j++)
			{
				disk[j] = fcontent[i];
				i++;
			}
			blit++;
		}

		files.insertAtStart(*f);
		return true;

	}


	~FileSystem()
	{
		delete[] disk;
	}
	void readFile(string& fname)
	{
		Iterator<File> it;
		char*array;
		int index = 0;
		for (it = files.begin(); it != files.end(); it++)
		{
			if ((*it).name == fname)
			{
				Iterator<Block> blit;
				blit = (*it).blockList.begin();
				int i = 0;
				while (blit != (*it).blockList.end())
				{
					int start_sector = (*blit).startSector;
					int end_sector = (*blit).endSector;
					for (int j = sizeOfSectors*(start_sector - 1); j < sizeOfSectors*end_sector && i<(*it).size; j++)
					{
						cout << disk[j];
						i++;
					}
					blit++;
				}
				cout << endl;
				return;
			}
		}
		cout << endl << "File not found!" << endl;

	}

	bool DeleteFile(string fname)
	{
		Iterator<File> fit;
		fit = files.begin();
		int c = 0;
		bool found = false;
		while (fit != files.end())
		{
			if ((*fit).name == fname)
			{
				Iterator<Block> bit;
				int count = 1;
				bit = (*fit).blockList.begin();
				while (bit != (*fit).blockList.end())
				{
					count++;
					bit++;
				}


				bit = (*fit).blockList.begin();
				while (bit != (*fit).blockList.end())
				{
					int start_sector = (*bit).startSector;
					int end_sector = (*bit).endSector;
					for (int j = sizeOfSectors*(start_sector - 1); j < sizeOfSectors*end_sector; j++)
					{
						disk[j] = '\0';
					}
					bit++;
				}


				for (int i = 1; i < count; i++)
					pool.insertAtStart((*fit).blockList.removeFromStart());
				found = true;
				break;
			}
			c++;
			fit++;
		}
		if (found)
		{
			if (c == 0)
			{
				files.removeFromStart();
			}

			else
			{
				fit = files.begin();
				c--;
				while (c != 0)
				{
					fit++;
					c--;
				}
				files.remove(fit);
			}
			return true;
		}
		else
		{
			return false;
		}
	}

};

//************************** MAIN ************************************

int main()
{
	string name;
	char array[500];
	int size;
	int operation = 0;
	int numSectors, sizeSector;
	bool loop = true;
	system("COLOR F0");
	cout << "Enter number of sectors you want to create on disk : " ;
	cin >> numSectors;
	cout << "What should be the size of each sector : ";
	cin >> sizeSector;
	if (numSectors > 0 && sizeSector > 0)
	{
		FileSystem FAT(sizeSector, numSectors);
		system("cls");
		while (loop)

		{
			system("COLOR F0");
			cout << "************************************************* FILE SYSTEM ********************************************************" << endl
				<< "1. Create a new file." << endl
				<< "2. Delete an exsiting file." << endl
				<< "3. Read an existing file." << endl
				<< "Press 4 to exit " << endl
				<< "Enter a corresponding number to perform the operation  : ";
			cin >> operation;
			if (operation == 1)
			{
				system("COLOR F0");
				system("cls");
				cout << "************************************************* Create a new File ********************************************************" << endl;
				cout << "Enter a file name : "  ;
				cin >> name;
				cout << "Enter the content of the file : "  ;
				cin.getline(array,500);
				cin.getline(array, 500);
				bool operation_success = FAT.SaveFile(strlen(array), array, name);
				if (!operation_success)
				{
					cout << "Operation failed either because of insufficient storage or some file with that name already exists :(" << endl;
				}
				else
				{
					cout << "File has successfully been created :) " << endl;
				}
				system("pause>NULL");
			
			}
			else if (operation == 2)
			{
				system("cls");
				system("COLOR C0");
				cout << "************************************************* Delete a file ********************************************************" << endl;
				cout << "Enter a file name : " ;
				cin >> name;
				bool op_success = FAT.DeleteFile(name);
				if (!op_success)
				{
					cout << "Operation failed  because no file with such name exists :(" << endl;
				}
				else
				{
					cout << "File was successfully removed";
				}
				system("pause>NULL");
			}
			else if (operation == 3)
			{
				system("COLOR F0");
				system("cls");
				cout << "************************************************* Read File ********************************************************" << endl;

				cout << "Enter a file name : " ;
				cin >> name;
				cout << endl << endl;
				FAT.readFile(name);
				system("pause>NULL");
			}
			else if (operation==4)
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
	else
	{
		cout << "Size of sector or Number of sector can't be 0 ";
		system("cls");
	}

	return 0;
}
