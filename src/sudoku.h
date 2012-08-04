
#ifndef __INCLUDED_SUDOKUSOLVER_SUDOKU__
#define __INCLUDED_SUDOKUSOLVER_SUDOKU__

#include "cell.h"

class Sudoku {
	
public:
	Sudoku();
	
	Sudoku(const Sudoku & other);
	
	void assign(const Sudoku & other);
	
	int compare_and_assign(const Sudoku & other);
	
	inline int value(int row, int column) const {
		return sudoku_cell[row][column].value();
	}
	
	void set_value(int row, int column, int cell_value);
	
	void reset();
	
	void reset_cell(int pos_row, int pos_column);
	
	int solve_constraints(int pos_row, int pos_column);
	
	int solve_constraints();
	
	int solve_coverage();
	
private:
	Cell sudoku_cell[9][9];
};

#endif // __INCLUDED_SUDOKUSOLVER_SUDOKU__
