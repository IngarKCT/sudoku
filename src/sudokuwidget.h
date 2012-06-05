
#ifndef __INCLUDED_SUDOKUSOLVER_SUDOKUWIDGET__
#define __INCLUDED_SUDOKUSOLVER_SUDOKUWIDGET__

#include <QtGui>
#include <QWidget>

class QLineEdit;

class SudokuWidget : public QWidget
{
	Q_OBJECT
	
public:
	SudokuWidget();

private:
	QLineEdit	* sudokuwidget_value[9][9];

};

#endif // __INCLUDED_SUDOKUSOLVER_SUDOKUWIDGET__