
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

	bool solved();
	
	/**
	 * @brief reset solution space of the given cell
	 * */
	void reset_cell(int pos_row, int pos_column);
	
	/**
	 * @brief resolve sudoku constraint rules for a single cell
	 * */
	int solve_constraints(int pos_row, int pos_column);
	
	/**
	 * @brief resolve sudoku constraint rules
	 * */
	int solve_constraints();
	
	/**
	 * @brief resolve sudoku coverage rules
	 * */
	int solve_coverage();
	
	/**
	 * @brief solve the sudoku, using constraint and converage rules only
	 * */
	int solve_rules();
	
	/**
	 * @brief solve the sudoku, using full search
	 * */
	int solve_search();
	
	inline Cell & cell (int row, int column)
	{
		return sudoku_cell[row][column];
	}
	
	inline const Cell & cell(int row, int column) const 
	{
		return sudoku_cell[row][column];
	}
private:
	bool solve_search_step(int &iterations, Sudoku & solution);
	
	Cell sudoku_cell[9][9];
};

#endif // __INCLUDED_SUDOKUSOLVER_SUDOKU__
