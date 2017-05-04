#include "GameSquare.h"
#include <iostream>


using namespace std;


// ввод ников игроков
void gamers(char *g1, char *g2)
{
	cout << "First player: ";
	cin >> g1;
	cout << "Second player: ";
	cin >> g2;
	system("cls");
}


// выбор игрока для следующего хода
int GameProgress(char *p1, char *p2)
{
	static int who = 0;

	cout << (who % 2 == 0 ? p1 : p2) << " ";

	return who++ % 2 == 0 ? 0 : 1; // первый игрок возврат 0, второй возврат 1
}


int main()
{
	char player1[19], player2[19];
	int sch;

	gamers(player1, player2);

	for (;;)
	{
		game a;
		sch = 0;

		for (;;)
		{
			a.print();

			// проверка на ничью
			if (sch++ == 9) 
			{
				cout << "Draw!" << endl;
				break;
			}

			int sign = GameProgress(player1, player2);
			int prog;

			// избежание заполнения уже заполненной клетки
			do
			{
				cin >> prog;
			} while (!a.tictac(prog, sign));

			if (a.win(sign, player1, player2))
			{
				break;
			}

			system("cls");
		}

		cout << "play again? (y/n) ";

		char answ[2];

		do
		{
			cin >> answ[0];
		} while (answ[0] != 'y' && answ[0] != 'n');

		if (answ[0] == 'n')
			break;
		else
			system("cls");
	}
	
	return 0;
}

/*
x x 0
0 x x
x 0 0
*/