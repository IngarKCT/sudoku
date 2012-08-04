
#include "sudoku.h"

Sudoku::Sudoku()
{
}


Sudoku::Sudoku(const Sudoku & other)
{
	assign(other);
}
	
void Sudoku::assign(const Sudoku & other)
{
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 9; column++) {
			sudoku_cell[row][column].assign(other.sudoku_cell[row][column]);
		}
	}
}

int Sudoku::compare_and_assign(const Sudoku & other)
{
	int d = 0;
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 9; column++) {
			if (sudoku_cell[row][column].value() != other.sudoku_cell[row][column].value()) {
				d++;
			}
			sudoku_cell[row][column].assign(other.sudoku_cell[row][column]);
		}
	}
	return d;
}

void Sudoku::set_value(int row, int column, int cell_value)
{
	sudoku_cell[row][column].set_value(cell_value);
}

// reset the solution space and calculate possible values for all cells
void Sudoku::reset()
{
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 9; column++) {
			reset_cell(row, column);
		}
	}
}

// reset the solution space for this cell and calculate possible values
void Sudoku::reset_cell(int pos_row, int pos_column)
{
	// reset all possibilities for this cell
	for (int possible_value = 0; possible_value < 9; possible_value++) {
		sudoku_cell[pos_row][pos_column].set_possibility(possible_value, true);
	}
	
	// eliminate row
	for (int column = 0; column < 9; column++) {
		if (column != pos_column) {
			const int v = value(pos_row,column);
			if ((v > 0) && (v <= 9)) {
				sudoku_cell[pos_row][pos_column].set_possibility(v -1, false);
			}
		}
	}
	
	// eliminate column
	for (int row = 0; row < 9; row++) {
		if (row != pos_row) {
			const int v = value(row,pos_column);
			if ((v > 0) && (v <= 9)) {
				sudoku_cell[pos_row][pos_column].set_possibility(v -1, false);
			}
		}
		
	}
	
	// eliminate subgrid
	int grid_row = pos_row - (pos_row % 3);
	int grid_column = pos_column - (pos_column % 3);
	for (int row = grid_row; row < grid_row + 3; row++) {
		for (int column = grid_column; column < grid_column + 3; column ++) {
			if ((column != pos_column) && (row != pos_row)) {
				const int v = value(row, column);
				if ((v > 0) && (v <= 9)) {
					sudoku_cell[pos_row][pos_column].set_possibility(v -1, false);
				}	
			}
			
		}
		
	}
}

/*
 * 	The coverage solver verifies the constraint which imposes that each
 * 	value from 1-9 has to appear exactly once in each row, column and subgrid
 * 	Cells with a unique solution are solved
 */
int Sudoku::solve_coverage()
{
	// calculate cell.possibilities
	reset();
	
	Sudoku solution(*this);
	
	// for each possible value
	for (int v = 1; v <= 9; v++) {
		
		// verify coverage for each row
		for (int row = 0; row < 9; row++) {
			int available_column = 0;
			int covered = 0;
			
			// verify if there's exactly one possibility for v in this row
			for (int column = 0; column < 9 ; column++) {
				if (!value(row, column) && sudoku_cell[row][column].possibility(v - 1)) {
					// value is still possible for this cell
					available_column = column;
				} else {
					covered++;
				}
			}
			if (covered == 8) {
				// value is only possible for a single cell
				solution.set_value(row, available_column, v);
			}
		}
		
		// verify coverage for each column
		for (int column = 0; column < 9; column++) {
			int available_row = 0;
			int covered = 0;
			
			// verify if there's exactly one possibility for v in this column
			for (int row = 0; row < 9; row++) {
				if (!value(row, column) && sudoku_cell[row][column].possibility(v - 1)) {
					// value is still possible a single cell
					available_row = row;
				} else {
					covered++;
				}
			}
			if (covered == 8) {
				// value is only possible for a single cell
				solution.set_value(available_row, column, v);
			}
		}
		
		// verify coverage for each subgrid
		for (int subgrid = 0; subgrid < 9; subgrid++) {
			// global coordinates of the (0,0) element of the subgrid
			const int sg_row = (subgrid / 3) * 3;
			const int sg_column = (subgrid % 3) * 3;
			
			// transle linear subgrid positions to row, col coordinate
			for  (int subgrid_pos = 0; subgrid_pos < 9; subgrid_pos++) {
				int sg_rowidx = sg_row + subgrid_pos / 3;
				int sg_colidx = sg_column + subgrid_pos % 3;
				int available_pos = 0;
				int covered = 0;
				
				if (!value(sg_rowidx, sg_colidx) && sudoku_cell[sg_rowidx][sg_colidx].possibility(v - 1)) {
					// value is still possible a single cell
					available_pos = subgrid_pos;
				} else {
					covered++;
				}
				
				if (covered == 8) {
					// value is only possible for a single cell
					int sg_rowidx = sg_row + available_pos / 3;
					int sg_colidx = sg_column + available_pos % 3;
					solution.set_value(sg_rowidx, sg_colidx, v);
				}
			}
		}
	}
	
	return compare_and_assign(solution);
}

/*
 * 	The constraint solver verifies the constraint that each value from 1-9
 * 	can appear only once in each column, row and subgrid
 * 	Cells with a unique solution are solved
 */
int Sudoku::solve_constraints()
{
	Sudoku solution;
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 9; column++) {
			solution.set_value(row, column, solve_constraints(row, column));
		}
	}
	
	return compare_and_assign(solution);
}

int Sudoku::solve_constraints(int pos_row, int pos_column)
{
	// verify if the cell has already been solved
	if ((value(pos_row,pos_column) > 0 ) && (value(pos_row,pos_column) <= 9)) {
		return value(pos_row,pos_column);
	}
	
	bool possible_solution[9];
	
	for (int idx = 0; idx < 9; idx++) {
		possible_solution[idx] = true; 
	}
	
	// eliminate row
	for (int column = 0; column < 9; column++) {
		if (column != pos_column) {
			const int v = value(pos_row,column);
			if ((v > 0) && (v <= 9)) {
				possible_solution[v - 1] = false;
			}
		}
	}
	// eliminate column
	for (int row = 0; row < 9; row++) {
		if (row != pos_row) {
			const int v = value(row,pos_column);
			if ((v > 0) && (v <= 9)) {
				possible_solution[v - 1] = false;
			}
		}
		
	}
	
	// eliminate subgrid
	int grid_row = pos_row - (pos_row % 3);
	int grid_column = pos_column - (pos_column % 3);
	for (int row = grid_row; row < grid_row + 3; row++) {
		for (int column = grid_column; column < grid_column + 3; column ++) {
			if ((column != pos_column) && (row != pos_row)) {
				const int v = value(row, column);
				if ((v > 0) && (v <= 9)) {
					possible_solution[v - 1] = false;
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