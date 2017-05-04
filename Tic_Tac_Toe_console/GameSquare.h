const int n = 3;
const int m = 9;

struct game
{
    // игровое поле
	char field[n][m];

	// вывод игрового поля
    void print();

    // заполнение игрового поля символами X и 0
	bool tictac(int prog, int sign);

	// выявление победителя
    bool win(int sign, char *p1, char *p2);

    // перебор возможных комбинаций для победы
	bool checkWin(char *s);

    // формирование игрового поля
	game();
};

/*
[1][2][3]
[4][5][6]
[7][8][9]
*/