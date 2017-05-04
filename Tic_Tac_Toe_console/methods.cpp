#include "GameSquare.h"
#include <iostream>


// перевод числа в код ASCII
void ascii(int &);

// замена на знаки X или 0
char charSign(int);


// вывод игрового поля
void game::print()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			std::cout << field[i][j];
		}
		std::cout << std::endl;
	}
}


// заполнение игрового поля символами X и 0
// prog - ход, sign - x или 0
bool game::tictac(int prog, int sign)
{
	char s[2];
	s[0] = charSign(sign);

	ascii(prog);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (field[i][j] == prog)
			{
				field[i][j] = s[0];
				return true;
			}
		}
	}

	return false;
}


// выявление победителя
// sign - X или 0, p1 - ник 1 игрока, p2 - ник 2 игрока
bool game::win(int sign, char *p1, char *p2)
{
	//1 4 7
	char s[2];
	s[0] = charSign(sign);

	if (checkWin(s))
	{
		std::cout << (sign == 0 ? p1 : p2) << " win!" << std::endl;
		return true;
	}

	return false;
}


// перебор возможных комбинаций для победы
bool game::checkWin(char *s)
{
	if (field[0][1] == s[0] && field[1][4] == s[0] && field[2][7] == s[0]) return true;
	if (field[0][7] == s[0] && field[1][4] == s[0] && field[2][1] == s[0]) return true;
	if (field[0][1] == s[0] && field[1][1] == s[0] && field[2][1] == s[0]) return true;
	if (field[0][4] == s[0] && field[1][4] == s[0] && field[2][4] == s[0]) return true;
	if (field[0][7] == s[0] && field[1][7] == s[0] && field[2][7] == s[0]) return true;
	if (field[0][1] == s[0] && field[0][4] == s[0] && field[0][7] == s[0]) return true;
	if (field[1][1] == s[0] && field[1][4] == s[0] && field[1][7] == s[0]) return true;
	if (field[2][1] == s[0] && field[2][4] == s[0] && field[2][7] == s[0]) return true;

	return false;
}


void ascii(int &prog)
{
	switch (prog)
	{
		case 1: prog = 49; break;
		case 2: prog = 50; break;
		case 3: prog = 51; break;
		case 4: prog = 52; break;
		case 5: prog = 53; break;
		case 6: prog = 54; break;
		case 7: prog = 55; break;
		case 8: prog = 56; break;
		case 9: prog = 57; break;
	}
}


char charSign(int sign)
{
	return sign == 0 ? 'X' : '0';
}
