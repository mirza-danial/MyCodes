#include<iostream>
using namespace std;
class Players
{
public:
	char activePlayer;
	char nonActivePlayer;

	
	Players(char a, char b)
	{
		activePlayer = a;
		nonActivePlayer = b;
	}

	void interchangePlayers()
	{
		swap(activePlayer, nonActivePlayer);
	}
};

void Game(Players p, int no_of_coins)
{
	if (no_of_coins != 0)
	{
		p.interchangePlayers();
		if (no_of_coins == 4 || no_of_coins == 1 || no_of_coins == 2)
		{
			cout << p.activePlayer << " is winner ."<<endl<<endl;
		}
		else if (no_of_coins == 3)
		{
			cout << p.nonActivePlayer << " is winner ."<<endl<<endl;
		}
		else
		{
			
			cout << "Player " << p.activePlayer << " took turn and picked ";
		
			if ((no_of_coins - 4) % 3 == 0)
			{
				cout << "4 coin " << no_of_coins - 4 << " coins are left " << endl;
				Game(p, no_of_coins - 4);
			}
			else if ((no_of_coins - 2) % 3 == 0)
			{
				cout << "2 coin " << no_of_coins - 2 << " coins are left " << endl;
				Game(p, no_of_coins - 2);
			}

			else 
			{
				cout << "1 coin " << no_of_coins - 1 << " coins are left " << endl;
				Game(p, no_of_coins - 1);
			}


		}
	}
}

int main()
{
	int coins;
	cout << "Enter the number of coins at the start of the game :";
	cin >> coins;
	while (coins < 1)
	{
		system("cls");
		cout << "Game cannot be played without coins !" << endl;
		cout << "Enter the number of coins at the start of the game :";
		cin >> coins;
	}

	Players p('B', 'A');
	Game(p, coins);
}