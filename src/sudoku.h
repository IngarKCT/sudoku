
#ifndef __INCLUDED_SUDOSOLVE_SUDOKU__
#define __INCLUDED_SUDOSOLVE_SUDOKU__

#include <QtGui>
#include <QWidget>

class QLineEdit;

class Sudoku : public QWidget
{
	Q_OBJECT
	
public:
	Sudoku();

private:
	QLineEdit	* sudoku_value[9][9];

};

#endif // __INCLUDED_SUDOSOLVE_SUDOKU__