
#include "mainwindow.h"
#include "solverwindow.h"

MainWindow::MainWindow()
{
	setWindowTitle(tr("Sudoku"));
	
	mainwindow_solverwindow = new SolverWindow();	
	setCentralWidget(mainwindow_solverwindow);
	
	initActions();
	
	initMenus();
}


void MainWindow::initActions()
{
	// Game -> New
	action_new = new QAction(tr("&New"), this);
	action_new->setShortcuts(QKeySequence::New);
	action_new->setStatusTip(tr("Start a new game"));
	connect(action_new, SIGNAL(triggered()), mainwindow_solverwindow, SLOT(clear()));
	
	// Game -> Load
	action_load = new QAction(tr("&Load..."), this);
	action_load->setShortcuts(QKeySequence::Open);
	action_load->setStatusTip(tr("Load a previously saved game"));
	connect(action_load, SIGNAL(triggered()), mainwindow_solverwindow, SLOT(load()));
	
	// Game -> Save
	action_save = new QAction(tr("&Save"), this);
	action_load->setStatusTip(tr("Save the current game"));
	//TODO

	// Game -> Save As
	action_saveas = new QAction(tr("Save &As..."), this);
	action_load->setStatusTip(tr("Save the current game to a new file"));
	connect(action_saveas, SIGNAL(triggered()), mainwindow_solverwindow, SLOT(saveas()));
	
	// Game -> Revert
	action_revert = new QAction(tr("&Revert"), this);
	action_revert->setStatusTip(tr("Reload the current game from file"));
	connect(action_revert, SIGNAL(triggered()), mainwindow_solverwindow, SLOT(revert()));
	
	// Game -> Quit
	action_quit = new QAction(tr("&Quit"), this);
	action_quit->setShortcuts(QKeySequence::Quit);
	action_quit->setStatusTip(tr("Exit the application"));
	connect(action_quit, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
	
	// Move -> Hint
	action_hint = new QAction(tr("Hint"), this);
	action_hint->setStatusTip(tr("Give a hint"));
	// TODO
	
	// Move -> Step
	action_step = new QAction(tr("Step"), this);
	action_step->setStatusTip(tr("Solve a single cell"));
	connect(action_step, SIGNAL(triggered()), mainwindow_solverwindow, SLOT(step()));
	
	// Move -> Solve
	action_solve = new QAction(tr("Solve rules"), this);
	action_solve->setStatusTip(tr("Solve sudoku rules"));
	connect(action_solve, SIGNAL(triggered()), mainwindow_solverwindow, SLOT(solve()));

	// Move -> Search
	action_search = new QAction(tr("Find solution"), this);
	action_search->setStatusTip(tr("Find a solution"));
	connect(action_search, SIGNAL(triggered()), mainwindow_solverwindow, SLOT(search()));
}

void MainWindow::initMenus()
{
	mainwindow_gamemenu = menuBar()->addMenu(tr("&Game"));
	mainwindow_gamemenu->addAction(action_new);
	mainwindow_gamemenu->addAction(action_load);
	mainwindow_gamemenu->addSeparator();
	//mainwindow_gamemenu->addAction(action_save);
	mainwindow_gamemenu->addAction(action_saveas);
	mainwindow_gamemenu->addAction(action_revert);
	mainwindow_gamemenu->addSeparator();
	mainwindow_gamemenu->addAction(action_quit);
	
	mainwindow_movemenu = menuBar()->addMenu(tr("&Move"));
	//mainwindow_movemenu->addAction(action_hint);
	mainwindow_movemenu->addAction(action_step);
	mainwindow_movemenu->addAction(action_solve);
	mainwindow_movemenu->addAction(action_search);
}

