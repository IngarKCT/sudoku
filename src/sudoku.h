
#ifndef __INCLUDED_SUDOKUSOLVER_SUDOKU__
#define __INCLUDED_SUDOKUSOLVER_SUDOKU__

#include "cell.h"

class Sudoku {
	
public:
	Sudoku();
	
	// inspector
	inline int value(int row, int column) const {
		return sudoku_cell[row][column].value();
	}
	
	// mutator
	void set_value(int row, int column, int value);
	
	int solve_step(int pos_row, int pos_column);
	
private:
	Cell sudoku_cell[9][9];
};

#endif // __INCLUDED_SUDOKUSOLVER_SUDOKU__
