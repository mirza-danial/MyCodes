#include<iostream>
#include<Windows.h>
#include<conio.h>
using namespace std;
struct fraction{
	int num;
	int denum;
	fraction*next;
};
void PrintList(fraction*first)						//Prints List
{
	if (first != nullptr)					
	{
		fraction*temp = first;
		cout << "\nCURRENT FAREY FRACTION IS:\n";
		while (temp != nullptr)
		{
			cout << temp->num << "/" << temp->denum<<"		";
			temp = temp->next;
		}
	}

}
void levelup(fraction *&first, int &level)
{
	fraction*current = first;							//travel through list 
	while (current->next != nullptr)
	{
		if (current->denum + (current->next)->denum <= level + 1)
		{
			fraction *newfrac = new fraction;
			newfrac->num = current->num + (current->next)->num;
			newfrac->denum = current->denum + (current->next)->denum;
			newfrac->next = current->next;
			fraction*temp=current;
			current = current->next;
			temp->next = newfrac;
		}
		else
		{
			current = current->next;
		}
		
	}
	level++;
}
void leveldown(fraction *&first, int &level)
{
	if (level > 1)
	{
		fraction*current = first;
		while (current->next != nullptr)
		{
			if (current->denum + ((current->next)->next)->denum == (current->next)->denum)
			{
				fraction*temp=current->next;
				current->next = temp->next;
				delete temp;
			}
			current = current->next;
		}
		level--;
	}
	else
		cout << "FAREY'S FRACTION CANNOT BE SMALLER THEN LEVEL 1";
}
void ListCreater(fraction *&first, fraction *&last,int &level)
{
	if (level != 0)
	{
		int l = 1;				//starting level
		first = new fraction;
		last = new fraction;
		first->num = 0;
		first->denum = 1;
		last->num = 1;
		last->denum = 1;
		first->next = last;
		last->next = nullptr;
		for (int i = 1; i < level; i++)
		{
			levelup(first, l);
		}
		level = l;
	}

}
void ChangeLevel(fraction*first, int &current_level, int new_level)
{
	if (new_level != 0)
	{
		if (current_level < new_level)
		{
			while (current_level != new_level)
			{
				levelup(first, current_level);
			}
		}
		else if (current_level > new_level)
		{
			while (current_level != new_level)
			{
				leveldown(first, current_level);
			}
		}
	}
}
int main()
{
	fraction *first,*last;
	first = nullptr, last = nullptr;
	int level,value,new_level,count=0;
	cout << "****************************************FAREY'S FRACTION***********************************\n";
	cout << "ENTER THE LEVEL OF FAREY FRACTION:";
	cin >> level;
	ListCreater(first, last, level);
	PrintList(first);
	_getch();
	/*system("cls");*/

	while (true)
	{
		cout << "****************************************FAREY'S FRACTION***********************************";
		cout << "\nPress 1 to increase the level of fraction.";
		cout << "\nPress 2 to decrease the level of fraction.";
		cout << "\nPress 3 to change the level of fraction to any level.";
		cout << "\nPress 4 to leave.";
		cout << "\nYour Choice:";
		cin >> value;
		while (value <= 0 || value > 4)
		{
			if (count < 3){
				cout << "\nPLEASE ENTER A VALUE WHICH HAS BEEN ASSIGNED A TASK.YOU DON'T HAVE ANY OTHER CHOICE.\nYour Choice: ";
				cin >> value;
			}
			else{
				cout << "\nKEEP WASTING YOUR TIME I AM NOT GOING TO MAKE A CHOICE OF YOUR DESIRE";
				cout << "\nYour Choice:";
				cin >> value;
			}
			count++;
		}
		/*system("cls");*/
		if (value == 1)
		{
			cout << "YOU HAVE CHOSED TO INCREASE THE LEVEL OF FRACTION BY 1\n";
			levelup(first, level);
			PrintList(first);
			_getch();
		}
		else if (value == 2)
		{
			cout << "YOU HAVE CHOSED TO TO DECREASE THE LEVEL OF FRACTION BY 1\n";
			leveldown(first, level);
			PrintList(first);
			_getch();
		}
		else if (value == 3)
		{
			cout << "YOU HAVE CHOSED TO CHANGE THE LEVEL OF FRACTION\nEnter new level :";
			cin >> new_level;
			while (new_level <= 0)
			{
				cout << "\nLEVEL CANNOT BE SMALLER THAN 1";
				cout << "PLEASE ENTER NEW LEVEL AGAIN:";
				cin >> new_level;
			}
			ChangeLevel(first, level, new_level);
			PrintList(first);
			_getch();
		}
		else if (value == 4)
		{
			cout << "GOOD BYE :-)\n\n";
			return 0;
		}
		/*system("cls");*/
	}
}