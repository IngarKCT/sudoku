
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
	
	inline const QString & filename()
	{
		return solverwindow_filename;
	}

public slots:
	
	void doNew();
	void doOpen();
	void doSave();
	void doSaveAs();
	void doRevert();
	
	/**
	 * @brief try to solve a single cell by using the rules only
	 * */
	void doStep();	
	/**
	 * @brief try to solve a single cell by guessing where required
	 * */
	void doGuess();
	/**
	 * @brief try to find a solution by using the rules only
	 * */
	void doSolve();
	/**
	 * @brief try to find a solution by guessing where required
	 * */
	void doSearch();
	
	void doValidate();
	
private:
	void step_constraints();
	void step_coverage();	

	void saveToFile(const QString & filename);
	void openFromFile(const QString & filename);
	
	SudokuWidget	*solverwindow_sudokuwidget;
	Sudoku		solverwindow_revertstate;
	QString		solverwindow_filename;
};

#endif // __INCLUDED_SUDOKUSOLVER_SOLVERWINDOW__