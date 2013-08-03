
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

private slots:
	void updateTitle();
	void updateStatus(const QString & text);
	
	void doNew();
	void doOpen();
	void doSave();
	void doSaveAs();
	void doRevert();
	void doQuit();
	
	void doValidate();
	
	void doShowHintUnique();
	
	void doAbout();

private:
	void initActions();
	void initMenus();
	void initStatus();
		
	SolverWindow	*mainwindow_solverwindow;
	QMenu		*mainwindow_gamemenu;
	QMenu		*mainwindow_movemenu;
	QMenu		*mainwindow_settingsmenu;
	QMenu		*mainwindow_helpmenu;
	
	// Game menu actions
	QAction		*action_new;
	QAction		*action_open;
	QAction		*action_save;
	QAction		*action_saveas;
	QAction		*action_revert;
	QAction		*action_quit;
	
	// Move menu actions
	QAction		*action_hint;
	QAction		*action_step;
	QAction		*action_guess;
	QAction		*action_solve;
	QAction		*action_search;
	QAction		*action_validate;
	
	// Settings menu actions
	QAction		*action_hintunique;
	
	// Help menu actions
	QAction		*action_about;
};

#endif // __INCLUDED_SUDOKUSOLVER_MAINWINDOW__

