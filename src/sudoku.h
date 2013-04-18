
#ifndef __INCLUDED_SUDOKUSOLVER_SUDOKU__
#define __INCLUDED_SUDOKUSOLVER_SUDOKU__

#include "cell.h"

class Sudoku {
	
public:
	Sudoku();
	
	Sudoku(const Sudoku & other);
	
	void assign(const Sudoku & other);
	
	int compare_and_assign(const Sudoku & other);
	
	void reset();
	
	bool validate();

	/**
	 * @brief reset solution space of the given cell
	 * */
	void reset_cell(int pos_row, int pos_column);
	
	int solve_constraints(int pos_row, int pos_column);
	
	int solve_constraints();
	
	int solve_coverage();
	
	int solve();
	
	inline Cell & cell (int row, int column)
	{
		return sudoku_cell[row][column];
	}
	
	inline const Cell & cell(int row, int column) const 
	{
		return sudoku_cell[row][column];
	}
private:
	Cell sudoku_cell[9][9];
};

#endif // __INCLUDED_SUDOKUSOLVER_SUDOKU__
