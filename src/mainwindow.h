
#ifndef __INCLUDED_SUDOSOLVE_MAINWINDOW__
#define __INCLUDED_SUDOSOLVE_MAINWINDOW__

#include <QtGui> 
#include <QMainWindow>

class Sudoku;

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	MainWindow();

private:
	Sudoku	*mainwindow_sudoku;

};

#endif // __INCLUDED_SUDOSOLVE_MAINWINDOW__