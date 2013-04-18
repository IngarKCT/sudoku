
#ifndef __INCLUDED_SUDOKUSOLVER_MAINWINDOW__
#define __INCLUDED_SUDOKUSOLVER_MAINWINDOW__

#include <QtGui> 
#include <QMainWindow>

class SudokuWidget;
class QAction;
class QMenu;
class SolverWindow;

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	MainWindow();

private:
	void initActions();
	
	void initMenus();
	
	SolverWindow	*mainwindow_solverwindow;
	QMenu		*mainwindow_gamemenu;
	QMenu		*mainwindow_movemenu;
	
	// Game menu actions
	QAction		*action_new;
	QAction		*action_load;
	QAction		*action_save;
	QAction		*action_saveas;
	QAction		*action_quit;
	
	// Move menu actions
	QAction		*action_hint;
	QAction		*action_step;
	QAction		*action_solve;

};

#endif // __INCLUDED_SUDOKUSOLVER_MAINWINDOW__

