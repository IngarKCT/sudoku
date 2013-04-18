
#ifndef __INCLUDED_SUDOKUSOLVER_SOLVERWINDOW__
#define __INCLUDED_SUDOKUSOLVER_SOLVERWINDOW__

#include <QWidget>

#include "sudoku.h"

class SudokuWidget;

class SolverWindow : public QWidget
{
	Q_OBJECT
	
public:
	SolverWindow();

public slots:
	
	void load();
	void saveas();
	void revert();
	void solve();
	void step();
	void step_constraints();
	void step_coverage();
	void clear();
	void validate();
	
private:
	SudokuWidget	*solverwindow_sudokuwidget;
	Sudoku		solverwindow_revertstate;
};

#endif // __INCLUDED_SUDOKUSOLVER_SOLVERWINDOW__