
#ifndef __INCLUDED_SUDOKUSOLVER_SUDOKU__
#define __INCLUDED_SUDOKUSOLVER_SUDOKU__

class Sudoku {
	
public:
	Sudoku();
	
	// inspector
	inline int value(int row, int column) const {
		return sudoku_value[row][column];
	}
	
	// mutator
	inline int & value(int row, int column) {
		return sudoku_value[row][column];
	}
	
private:
	int sudoku_value[9][9];
};

#endif // __INCLUDED_SUDOKUSOLVER_SUDOKU__
