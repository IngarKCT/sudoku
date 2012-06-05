
#include "sudoku.h"

Sudoku::Sudoku()
{
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 9; column++) {
			sudoku_value[row][column] = 0;
		}
	}
}