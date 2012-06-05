
#ifndef __INCLUDED_SUDOKUSOLVER_SOLVERWINDOW__
#define __INCLUDED_SUDOKUSOLVER_SOLVERWINDOW__

#include <QWidget>

class SudokuWidget;

class SolverWindow : public QWidget
{
	Q_OBJECT
	
public:
	SolverWindow();

public slots:
	
	void load();
	void save();
	void step();
	void clear();
	
private:
	SudokuWidget	*solverwindow_sudokuwidget;
};

#endif // __INCLUDED_SUDOKUSOLVER_SOLVERWINDOW__