
#ifndef __INCLUDED_SUDOKUSOLVER_SUDOKUWIDGET__
#define __INCLUDED_SUDOKUSOLVER_SUDOKUWIDGET__

#include <QtGui>
#include <QWidget>

#include "sudoku.h"

class QLineEdit;

class SudokuWidget : public QWidget
{
	Q_OBJECT
	
public:
	SudokuWidget();
	
	/**
	 * @brief set widgets value from sudoku values
	 * */
	void set_values(const Sudoku & values);
	
	/**
	 * @brief set sudoku values from widget values
	 * */
	void get_values(Sudoku & values);

private:
	QLineEdit	* sudokuwidget_value[9][9];

};

#endif // __INCLUDED_SUDOKUSOLVER_SUDOKUWIDGET__