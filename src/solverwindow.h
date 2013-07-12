
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
	
	void load();
	void save();
	void saveas();
	void revert();
	
	/**
	 * @brief try to find a solution by using the rules only
	 * */
	void solve();
	
	/**
	 * @brief try to find a solution by guessing where required
	 * */
	void search();
	
	/**
	 * @brief try to solve a single cell by using the rules only
	 * */
	void step();
	
	void step_constraints();
	void step_coverage();	
	
	/**
	 * @brief try to solve a single cell by guessing where required
	 * */
	void guess();
	
	void clear();
	
	void validate();
	
private:
	void saveToFile(const QString & filename);
	void loadFromFile(const QString & filename);
	
	SudokuWidget	*solverwindow_sudokuwidget;
	Sudoku		solverwindow_revertstate;
	QString		solverwindow_filename;
};

#endif // __INCLUDED_SUDOKUSOLVER_SOLVERWINDOW__