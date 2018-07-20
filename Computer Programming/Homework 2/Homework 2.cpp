#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#include<conio.h>
using namespace std;
bool ispresent(int**array, int size, int user)
{												
	for (int i = 0; i < size; i++)		//search the whole array to find that a certain user IS PRESENT or not
	{
		if (array[i][0] == user)
		{
			return true;
		}
	}
	return false;
}
int searchindex(int**array, int size,int value)
{								/*As in first index or every row the user itself is stored so in order to find the index of array for a certain
	user this function is used*/
	for (int i = 0; i < size; i++)
	{
		if (array[i][0] == value)
		{
			return i;
		}
	}
}
int getsize(int*array)
{
	//returns the size of 1D array(row) which is helpful while shrinking array 
	int size=0;
	for (int i = 0; array[i] != -1; i++)
	{
		size++;
	}
	return size;
}
int *shrinkarray(int arr1[], int &size, int index)
{
	//shrinks 1D array(row)
	int*arr2 = new int[size];
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
	arr2[size - 1] = -1;
	delete[]arr1;
	size = size - 1;
	return arr2;
}
int getindex(int*user, int member)
{
	//gives the index on which a certain member(friend) is stored in a row(1D array)
	for (int i = 1; user[i] != -1; i++)
	{
		if (user[i] == member)
		{
			return i;
		}
	}
}
void RemoveUser(int **&array, int &size, int user,int val)
{
	//removes a user from network
	int **arr = new int*[size - 1];
	for (int i = 0; i < size; i++)
	{
		for (int k = 1; array[i][k] != -1; k++)
		{
			if (array[i][k] == val)
			{
				int n = getsize(array[i]);
				array[i] = shrinkarray(array[i], n, k);
				break;
			}
		}
	}
	int j = 0;
	for (int i = 0; i < user; i++)
	{
		arr[j] = array[i];
		j++;
	}
	for (int i = user + 1; i < size; i++)
	{
		arr[j] = array[i];
		j++;
	}


	delete[]array[user];
	delete[]array;
	array = arr;
	size--;
	
}
bool isFriend(int**array,int size, int u1, int u2)
{
	//return true if two users are friends
	int val1 = searchindex(array, size, u1);
	int val2 = searchindex(array, size, u2);
	for (int i = 0; array[val1][i] != -1; i++)
	{
		if (array[val1][i] == u2)
		{
			return true;
		}
	}
	return false;
}
void Unfriend(int**array,int size,int*&user1, int*&user2, int u1, int u2)
{
	//unfriends two users by shrinking array
	if (isFriend(array, size, array[searchindex(array, size, u1)][0], array[searchindex(array, size, u2)][1]) != false)
	{
		int size1 = getsize(user1);
		int size2 = getsize(user2);
		int index1 = getindex(user1, u2);
		int index2 = getindex(user2, u1);
		user1 = shrinkarray(user1, size1, index1);
		user2 = shrinkarray(user2, size2, index2);

	}
}
void AddFriend(int **array,int size,int *&user1, int*&user2, int u1, int u2)
{
	//add a new friend
	if (isFriend(array, size, array[searchindex(array, size, u1)][0], array[searchindex(array, size, u2)][0]) == false)
	{
		int size1 = getsize(user1);
		int size2 = getsize(user2);
		int*arr1 = new int[size1 + 2];
		int *arr2 = new int[size2 + 2];
		int var1 = 0, var2 = 0;
		for (int i = 0; i < size1; i++)
		{
			arr1[var1] = user1[i];
			var1++;
		}
		arr1[var1] = u2;
		arr1[size1 + 1] = -1;
		delete[]user1;
		user1 = arr1;
		for (int i = 0; i < size2; i++)
		{
			arr2[var2] = user2[i];
			var2++;
		}
		arr2[var2] = u1;
		arr2[size2 + 1] = -1;
		delete[]user2;
		user2 = arr2;
	}
}
void AddUser(int**&array, int &size)
{
	//add a new user to network and update size
	int**arr = new int*[size + 1];
	for (int i = 0; i < size; i++)
	{
		arr[i] = array[i];
	}
	arr[size] = new int[2];
	int largst=array[0][0];
	for (int i = 0; i < size; i++)
	{
		if (array[i][0]>largst)
		{
			largst = array[i][0];
		}
	}
	arr[size][0] = largst+1;
	arr[size][1] = -1;
	delete[]array;
	array=arr;
	size = size + 1;
}
void PrintFriends(int*array)
{
	//print all friends of a user
	cout << "List Of Friends is:"<<endl;
	for (int i = 1; array[i] != -1; i++)
	{
		cout << array[i]<<endl;
	}
}
void save(int**array, int size)
{
	//save changes to the file
	ofstream link;
	link.open("file.txt");
	link << size << endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; array[i][j] != -1; j++)
		{
			link << array[i][j];
			if (array[i][j + 1] != -1)
			{
				link << ",";
			}
		}
		link << endl;
	}
	link.close();
}
void printLikelyFriends(int**array, int size, int index,int user)
{
	//print likely friends by storing non-friends in an 2D array with number of mutual friends and than printing non-friend users with highest number of mutual friends
	cout << "USER'S LIKELY FRIENDS ARE:\n";
	int ind=0;
	int arr[20][2];
	for (int i = 0; i < size; i++)
	{
		if (isFriend(array, size, user, array[i][0]) == false && array[i][0]!=user)
		{
			arr[ind][0] = array[i][0];
			ind++;
		}
		
	}
	arr[ind][0] = -1;
	for (int i = 0; arr[i][0] != -1; i++)
	{
		int count = 0;
		for (int j = 1; array[index][j] != -1; j++)
		{
			for (int k = 1; array[searchindex(array,size,arr[i][0])][k] != -1; k++)
			{
				if (array[index][j] == array[searchindex(array, size, arr[i][0])][k])
				{
					count++;
				}
			}
		}
		arr[i][1] = count; 
	}
	for (int a = 0; a < 3; a++)
	{
		int large = arr[0][1],alpha = 0;
		for (int i = 0; arr[i][0] != -1; i++)
		{
			if (arr[i][1]>large)
			{
				alpha = i;
			}
		}
		if (arr[alpha][1] != 0)
		{
			cout << arr[alpha][0] << "	";

		}
		arr[alpha][1] = 0;
	}

}
void PrintMutualFriends(int**array, int user1, int user2)
{
	//find mutual friensd and print
	int count = 0;
	cout << "Mutual Friends of " << array[user1][0] << " and " << array[user2][0] << " are :";
	for (int i = 1; array[user1][i] != -1; i++)
	{
		for (int j = 1; array[user2][j] != -1; j++)
		{
			if (array[user1][i] == array[user2][j])
			{
				cout << array[user2][j]<<"	";
				count++;
			}
		}
	}
	if (count == 0)
	{
		cout << " no mutual friends";
	}
}
void PrintFOF(int **array,int size, int user)
{
	//get a friend and print its friends 
	for (int i = 1; array[user][i] != -1; i++)
	{
		int n = array[user][i];
		cout << "Friends of " << n << " are:";
		for (int j = 1; array[searchindex(array,size,n)][j] != -1; j++)
		{
			cout << array[searchindex(array, size, n)][j] << "	";
		}
		cout << endl;
	}
}
void Prompt(int**&array, int &size)
{
	//prints menu and creates an interface
	cout << "**********************************************************FAKEBOOK******************************************************\n";
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; array[i][j] != -1; j++)
		{
			if (j == 0)
			{
				cout << array[i][j] << " is friend with ";
			}
			else
				cout << array[i][j] << "	";
			if (array[i][1] == -1)
			{
				cout << " no one !";
			}
		}
		cout << endl;
	}
	_getch();
	system("cls");
	int number;
	while (true)
	{
		cout << "**********************************************************FAKEBOOK******************************************************\n";
		cout << endl << "COMMANDS:\n";
		cout << "1) Add new user: adds new user, number n, to the network\n2) Make friends : makes two specified users friends with each other\n3) Remove friends : unfriends two specified users\n4) Remove User : removes a specified user, k; unfriends k from all other users,removes k from the array, decrements all numbers above k to keep dataconsistent.\n5) Print Friends : prints all friends of a user\n6) Print Friends of Friends : prints all friends of friends of a user\n7) Print Mutual Friends : prints all mutual friends of two specified users.\n8) Print Likely Friends : for a specified user, x, print 3 users y who are currentlynot x’s friends but have the maximum number of mutual friends with x\n9) Save: save the data onto file(overwrite the previous data)\n";
		cout << "10)EXIT";

		cout << endl << endl << endl;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; array[i][j] != -1; j++)
			{
				if (j == 0)
				{
					cout << array[i][j] << " is friend with ";
				}
				else
					cout << array[i][j] << "	";
				if (array[i][1] == -1)
				{
					cout << " no one !";
				}
			}
			cout << endl;
		}
		cout << endl << "\nENTER CORRESPONDING NUMBER TO PROCEED:";
		cin >>number;
		
		system("cls");
		int user1=NULL, user2=NULL, val1=NULL, val2=NULL;
		if (number == 1)
		{
			cout << "YOU HAVE CHOSED TO ADD A NEW USER TO NETWORK\nA NEW USER HAS BEEN ADDED TO NETWORK";
			AddUser(array, size);
			
		}
		else if (number == 2)
		{
			
			cout << "YOU HAVE CHOSED TO MAKE TWO USER FRIENDS\n";
			cout << "ENTER FIRST USER:";
			cin >> user1;
			cout << "ENTER SECOND USER:";
			cin >> user2;
			while (ispresent(array, size, user1) == false || ispresent(array, size, user2) == false)
			{
				cout << "YOU HAVE ENTERED AN INVALID USERS PLEASE ENTER AGAIN:";
				cout << "/nENTER FIRST USER:";
				cin >> user1;
				cout << "ENTER SECOND USER:";
				cin >> user2;
			}
			val1 = searchindex(array, size, user1);
			val2 = searchindex(array, size, user2);
			AddFriend(array,size,array[val1], array[val2], user1, user2);
			cout << user1 << " & " << user2 << " ARE NOW FRIENDS!";
		
		}
		else if (number == 3)
		{
			cout << "YOU HAVE CHOSED TO UNFRIEND TWO USERS\n";
			cout << "ENTER FIRST USER:";
			cin >> user1;
			cout << "ENTER SECOND USER:";
			cin >> user2;
			while (ispresent(array, size, user1) == false || ispresent(array, size, user2) == false)
			{
				cout << "YOU HAVE ENTERED AN INVALID USERS PLEASE ENTER AGAIN:";
				cout << "YOU HAVE CHOSED TO UNFRIEND TWO USERS\n";
				cout << "ENTER FIRST USER:";
				cin >> user1;
				cout << "ENTER SECOND USER:";
				cin >> user2;
			}
			val1 = searchindex(array, size, user1);
			val2 = searchindex(array, size, user2);
			Unfriend(array,size,array[val1], array[val2], user1, user2);
			cout << user1 << " & " << user2 << " ARE NOT FRIENDS ANYMORE!";
		
		}
		else if (number == 4)
		{
			cout << "YOU HAVE CHOSED TO REMOVE A USER FROM NETWORK\nENTER THE USER YOU WANT TO REMOVE:";
			cin >> user1;
			while (ispresent(array, size, user1) == false)
			{
				cout << "\nYOU HAVE ENTERED AN INVALID USERS PLEASE ENTER AGAIN:";
				cin >> user1;
			}
			val1 = searchindex(array, size, user1);
			RemoveUser(array,size,val1,user1);
			
		}
		else if (number == 5)
		{
			cout << "YOU HAVE CHOSED TO PRINT ALL FRIENDS OF A USER\nENTER THE USER:";
			cin >> user1;
			while (ispresent(array, size, user1) == false)
			{
				cout << "\nYOU HAVE ENTERED AN INVALID USERS PLEASE ENTER AGAIN:";
				cin >> user1;
			}
			val1 = searchindex(array, size, user1);
			PrintFriends(array[val1]);
			

		}
		else if (number == 6)
		{
			cout << "YOU HAVE CHOSED TO PRINT ALL FRIENDS OF FRIENDS OF A USER\nENTER THE USER:";
			cin >> user1;
			while (ispresent(array, size, user1) == false)
			{
				cout << "\nYOU HAVE ENTERED AN INVALID USERS PLEASE ENTER AGAIN:";
				cin >> user1;
			}
			val1 = searchindex(array, size, user1);
			PrintFOF(array,size,val1);
		

		}
		else if (number == 7)
		{
			cout << "YOU HAVE CHOSED TO PRINT ALL MUTUAL FRIENDS OF TWO USERS\nENTER THE FIRST USER:";
			cin >> user1;
			cout << "ENTER THE SECOND USER:";
			cin >> user2;
			while (ispresent(array, size, user1) == false || ispresent(array, size, user2) == false)
			{
				cout << "YOU HAVE ENTERED AN INVALID USERS PLEASE ENTER AGAIN:";
				cout << "\nENTER FIRST USER:";
				cin >> user1;
				cout << "ENTER SECOND USER:";
				cin >> user2;
			}
			val1 = searchindex(array, size, user1);
			val2 = searchindex(array, size, user2);
			PrintMutualFriends(array,val1,val2);
			

		}
		else if (number == 8)
		{
			cout << "YOU HAVE CHOSED TO PRINT LIKELY FRIENDS\nENTER A USER:";
			cin >> user1;
			while (ispresent(array, size, user1) == false)
			{
				cout << "\nYOU HAVE ENTERED AN INVALID USERS PLEASE ENTER AGAIN:";
				cin >> user1;
			}
			val1 = searchindex(array, size, user1);
			printLikelyFriends(array, size, val1, user1);
		
			

		}
		else if (number == 9)
		{
			cout << "YOU HAVE CHOSED TO SAVE CHANGES TO FILE\nCHANGES HAVE BEEN SAVED!";
			save(array, size);
		
		}
		else if (number == 10)
		{
			return;
		}
		else
		{
			cout << "PLEASE ENTER A VALID NUMBER\n";
		}
		_getch();
		system("cls");
	}
}
int main()
{
	int n, first = 0;
	char *alpha = NULL;
	char *line = new char[100];
	ifstream path("file.txt");
	path >> n;
	int **array = new int*[n];
	if (path.fail())
	{
		cout << "FILE CRASHED!";
	}
	else
	{
		path.getline(line, 100);
		while (path.getline(line, 100))
		{
			int count = 0;
			for (int j = 0; line[j] != '\0'; j++)
			{
				if (line[j + 1] >= '0'&&line[j + 1] <= '9')
				{
					j++;
				}
				if (line[j] != ',')
				{
					count++;
				}
				
			}
			array[first] = new int[count + 1];
			char*tok = nullptr;
			tok = strtok_s(line,",",&alpha);
			int i = atoi(tok);
			array[first][0] = i;
			int index = 1;
			while (tok != NULL)
			{
				tok = strtok_s(NULL, ",",&alpha);
				if (tok == NULL)
				{
					break;
				}
				i = atoi(tok);
				array[first][index] = i;
				index++;
			}
			array[first][index]=-1;
			first++;
		}
	}
	Prompt(array, n);
}
