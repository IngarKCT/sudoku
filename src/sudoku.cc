
#include "sudoku.h"

Sudoku::Sudoku()
{
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 9; column++) {
			sudoku_value[row][column] = 0;
		}
	}
}

int Sudoku::solve_step(int pos_row, int pos_column)
{
	// verify if the cell has already been solved
	if ((sudoku_value[pos_row][pos_column] > 0 ) && (sudoku_value[pos_row][pos_column] <= 9)) {
		return sudoku_value[pos_row][pos_column];
	}
	
	bool possible_solution[9];
	
	for (int idx = 0; idx < 9; idx++) {
		possible_solution[idx] = true; 
	}
	
	// eliminate row
	for (int column = 0; column < 9; column++) {
		if (column != pos_column) {
			int value = sudoku_value[pos_row][column];
			if ((value > 0) && (value <= 9)) {
				possible_solution[value - 1] = false;
			}
		}
	}
	// eliminate column
	for (int row = 0; row < 9; row++) {
		if (row != pos_row) {
			int value = sudoku_value[row][pos_column];
			if ((value > 0) && (value <= 9)) {
				possible_solution[value - 1] = false;
			}
		}
		
	}
	
	// eliminate subgrid
	int grid_row = pos_row - (pos_row % 3);
	int grid_column = pos_column - (pos_column % 3);
	for (int row = grid_row; row < grid_row + 3; row++) {
		for (int column = grid_column; column < grid_column + 3; column ++) {
			if ((column != pos_column) && (row != pos_row)) {
				int value = sudoku_value[row][column];
				if ((value > 0) && (value <= 9)) {
					possible_solution[value - 1] = false;
				}	
			}
			
		}
		
	}
	
	int nbeliminated = 0;
	int solution = 0;
	for (int idx = 0; idx < 9; idx++) {
		if (!possible_solution[idx]) {
			nbeliminated++;
		} else {
			solution = idx + 1;
		}
	}
	
	if (nbeliminated == 8) {
		return solution;
	} else {
		return 0;
	}
}