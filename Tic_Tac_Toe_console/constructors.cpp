#include "GameSquare.h"


game::game()
{
	// 0 2 3 5 6 8
	// [ ] [ ] [ ]
	int sch = 49;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			switch (j)
			{
				case 0: field[i][j] = '['; break;
				case 2: field[i][j] = ']'; break;
				case 3: field[i][j] = '['; break;
				case 5: field[i][j] = ']'; break;
				case 6: field[i][j] = '['; break;
				case 8: field[i][j] = ']'; break;
				default: field[i][j] = sch++;
			}
		}
	}
}