
// #include <QtGui>

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
/*
void Sudoku::set_value(int row, int column, int cell_value)
{
	sudoku_cell[row][column].set_value(cell_value);
}
*/

// reset the solution space and calculate possible values for all cells
void Sudoku::reset()
{
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 9; column++) {
			reset_cell(row, column);
		}
	}
}

bool Sudoku::validate()
{
	bool v = true;
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 9; column++) {
			reset_cell(row, column);
			v = v && sudoku_cell[row][column].valid();
		}
	}
	return v;
}

// reset the solution space for this cell and calculate possible values
void Sudoku::reset_cell(int pos_row, int pos_column)
{
	// mark cell as valid
	sudoku_cell[pos_row][pos_column].set_valid(true);
	
	// reset all possibilities for this cell
	for (int possible_value = 0; possible_value < 9; possible_value++) {
		sudoku_cell[pos_row][pos_column].set_possibility(possible_value, true);
	}
	
	// eliminate row
	for (int column = 0; column < 9; column++) {
		if (column != pos_column) {
			const int v = cell(pos_row,column).value();
			if ((v > 0) && (v <= 9)) {
				sudoku_cell[pos_row][pos_column].set_possibility(v -1, false);
			}
		}
	}
	
	// eliminate column
	for (int row = 0; row < 9; row++) {
		if (row != pos_row) {
			const int v = cell(row,pos_column).value();
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
				const int v = cell(row, column).value();
				if ((v > 0) && (v <= 9)) {
					sudoku_cell[pos_row][pos_column].set_possibility(v -1, false);
				}	
			}
			
		}
		
	}
	
	// set validity
	if ((cell(pos_row,pos_column).value() > 0) && (cell(pos_row,pos_column).value() <= 9)) {
	  
		if (!sudoku_cell[pos_row][pos_column].possibility(sudoku_cell[pos_row][pos_column].value() - 1)) {
			// cell is invalid if the current value is not possible
			sudoku_cell[pos_row][pos_column].set_valid(false);
		} else {
			// cell is not valid if there are no possibilities
			int n = 0;
			for (int possible_value = 0; possible_value < 9; possible_value++) {
				if (sudoku_cell[pos_row][pos_column].possibility(possible_value))
					n++;
			}
			if (n == 0) {
				sudoku_cell[pos_row][pos_column].set_valid(false);
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
				if (!cell(row, column).value() && cell(row,column).possibility(v - 1)) {
					// value is still possible for this cell
					available_column = column;
				} else {
					covered++;
				}
			}
			if (covered == 8) {
				// value is only possible for a single cell
				solution.cell(row, available_column).set_value(v);
				// qDebug() << "(" << row << "," <<  available_column << ") row covered, value " << v;
			}
		}
		
		// verify coverage for each column
		for (int column = 0; column < 9; column++) {
			int available_row = 0;
			int covered = 0;
			
			// verify if there's exactly one possibility for v in this column
			for (int row = 0; row < 9; row++) {
				if (!cell(row, column).value() && sudoku_cell[row][column].possibility(v - 1)) {
					// value is still possible a single cell
					available_row = row;
				} else {
					covered++;
				}
			}
			if (covered == 8) {
				// value is only possible for a single cell
				solution.cell(available_row, column).set_value(v);
				// qDebug() << "(" << available_row << "," <<  column << ") column covered, value " << v;
			}
		}
		
		// verify coverage for each subgrid
		for (int subgrid = 0; subgrid < 9; subgrid++) {
			// global coordinates of the (0,0) element of the subgrid
			const int sg_row = (subgrid / 3) * 3;
			const int sg_column = (subgrid % 3) * 3;
			
			// translate linear subgrid positions to row, col coordinate
			for  (int subgrid_pos = 0; subgrid_pos < 9; subgrid_pos++) {
				int sg_rowidx = sg_row + subgrid_pos / 3;
				int sg_colidx = sg_column + subgrid_pos % 3;
				int available_pos = 0;
				int covered = 0;
				
				if (!cell(sg_rowidx, sg_colidx).value() && cell(sg_rowidx,sg_colidx).possibility(v - 1)) {
					// value is still possible a single cell
					available_pos = subgrid_pos;
				} else {
					covered++;
				}
				
				if (covered == 8) {
					// value is only possible for a single cell
					int av_rowidx = sg_row + available_pos / 3;
					int av_colidx = sg_column + available_pos % 3;
					solution.cell(av_rowidx, av_colidx).set_value(v);
					// qDebug() << "(" << av_rowidx << "," <<  av_colidx << ") subgrid covered, value " << v;
				}
			}
		}
	}
	
	reset();
	
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
			solution.cell(row, column).set_value(solve_constraints(row, column));
		}
	}
	
	reset();
	
	return compare_and_assign(solution);
}

int Sudoku::solve_constraints(int pos_row, int pos_column)
{
	// verify if the cell has already been solved
	if ((cell(pos_row,pos_column).value() > 0 ) && (cell(pos_row,pos_column).value() <= 9)) {
		return cell(pos_row,pos_column).value();
	}
	
	bool possible_solution[9];
	
	for (int idx = 0; idx < 9; idx++) {
		possible_solution[idx] = true; 
	}
	
	// eliminate row
	for (int column = 0; column < 9; column++) {
		if (column != pos_column) {
			const int v = cell(pos_row,column).value();
			if ((v > 0) && (v <= 9)) {
				possible_solution[v - 1] = false;
			}
		}
	}
	// eliminate column
	for (int row = 0; row < 9; row++) {
		if (row != pos_row) {
			const int v = cell(row,pos_column).value();
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
				const int v = cell(row, column).value();
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