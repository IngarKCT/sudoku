
#include "mainwindow.h"
#include "solverwindow.h"

#include "config.h"

/* XPM */
const char *icon_xpm[] = {
"16 16 2 1",
" 	c #000000",
".	c #FFFFFF",
"                ",
" .... .... .... ",
" .... .... .... ",
" .... .... .... ",
" .... .... .... ",
"                ",
" .... .... .... ",
" .... .... .... ",
" .... .... .... ",
" .... .... .... ",
"                ",
" .... .... .... ",
" .... .... .... ",
" .... .... .... ",
" .... .... .... ",
"                "};


MainWindow::MainWindow()
{
	
	setWindowTitle(tr("Sudoku"));
	setWindowIcon(QIcon(QPixmap(icon_xpm)));

	mainwindow_solverwindow = new SolverWindow();	
	setCentralWidget(mainwindow_solverwindow);
	
	initActions();
	
	initMenus();
	
	initStatus();
	
	updateTitle();
	
	connect(mainwindow_solverwindow, SIGNAL(statusChanged(const QString &)), this, SLOT(updateStatus(const QString &)));
}


void MainWindow::initActions()
{
	// Game -> New
	action_new = new QAction(tr("&New"), this);
	action_new->setShortcuts(QKeySequence::New);
	action_new->setStatusTip(tr("Start a new game"));
	connect(action_new, SIGNAL(triggered()), this, SLOT(doNew()));
	
	// Game -> Load
	action_open = new QAction(tr("&Open..."), this);
	action_open->setShortcuts(QKeySequence::Open);
	action_open->setStatusTip(tr("Open a previously saved game"));
	connect(action_open, SIGNAL(triggered()), this, SLOT(doOpen()));
	
	// Game -> Save
	action_save = new QAction(tr("&Save"), this);
	action_save->setShortcuts(QKeySequence::Save);
	action_save->setStatusTip(tr("Save the current game"));
	connect(action_save, SIGNAL(triggered()), this, SLOT(doSave()));

	// Game -> Save As
	action_saveas = new QAction(tr("Save &As..."), this);
	action_saveas->setStatusTip(tr("Save the current game to a new file"));
	connect(action_saveas, SIGNAL(triggered()), this, SLOT(doSaveAs()));
	
	// Game -> Revert
	action_revert = new QAction(tr("&Revert"), this);
	action_revert->setStatusTip(tr("Reload the current game from file"));
	connect(action_revert, SIGNAL(triggered()), this, SLOT(doRevert()));
	
	// Game -> Quit
	action_quit = new QAction(tr("&Quit"), this);
	action_quit->setShortcuts(QKeySequence::Quit);
	action_quit->setStatusTip(tr("Exit the application"));
	connect(action_quit, SIGNAL(triggered()), this, SLOT(doQuit()));
	
	// Move -> Hint
	action_hint = new QAction(tr("Hint"), this);
	action_hint->setStatusTip(tr("Give a hint"));
	// TODO connect()
	
	// Move -> Step
	action_step = new QAction(tr("Step"), this);
	action_step->setStatusTip(tr("Solve a single cell"));
	connect(action_step, SIGNAL(triggered()), mainwindow_solverwindow, SLOT(doStep()));
	
	// Move -> Step
	action_guess = new QAction(tr("Guess"), this);
	action_guess->setStatusTip(tr("Solve a single cell with guessing"));
	connect(action_guess, SIGNAL(triggered()), mainwindow_solverwindow, SLOT(doGuess()));
	
	// Move -> Solve
	action_solve = new QAction(tr("Solve rules"), this);
	action_solve->setStatusTip(tr("Solve sudoku rules"));
	connect(action_solve, SIGNAL(triggered()), mainwindow_solverwindow, SLOT(doSolve()));

	// Move -> Search
	action_search = new QAction(tr("Find solution"), this);
	action_search->setStatusTip(tr("Find a solution"));
	connect(action_search, SIGNAL(triggered()), mainwindow_solverwindow, SLOT(doSearch()));
	
	// Move -> Validate
	action_validate = new QAction(tr("Validate"), this);
	action_validate ->setStatusTip(tr("Validate the sudoku"));
	connect(action_validate, SIGNAL(triggered()), this, SLOT(doValidate()));
	
	// Settings -> Show Unique
	action_hintunique = new QAction(tr("Mark solveable"), this);
	action_hintunique->setStatusTip(tr("Mark cells with a unique solution"));
	action_hintunique->setCheckable(true);
	connect(action_hintunique, SIGNAL(triggered()), this, SLOT(doShowHintUnique()));
	
	// Help -> About
	action_about = new QAction(tr("About..."), this);
	action_about ->setStatusTip(tr("About %1").arg(PACKAGE_NAME));
	connect(action_about, SIGNAL(triggered()), this, SLOT(doAbout()));
}

void MainWindow::initMenus()
{
	mainwindow_gamemenu = menuBar()->addMenu(tr("&Game"));
	mainwindow_gamemenu->addAction(action_new);
	mainwindow_gamemenu->addAction(action_open);
	mainwindow_gamemenu->addSeparator();
	mainwindow_gamemenu->addAction(action_save);
	mainwindow_gamemenu->addAction(action_saveas);
	mainwindow_gamemenu->addAction(action_revert);
	mainwindow_gamemenu->addSeparator();
	mainwindow_gamemenu->addAction(action_quit);
	
	mainwindow_movemenu = menuBar()->addMenu(tr("&Move"));
	//mainwindow_movemenu->addAction(action_hint);
	mainwindow_movemenu->addAction(action_step);
	mainwindow_movemenu->addAction(action_guess);
	mainwindow_movemenu->addSeparator();
	mainwindow_movemenu->addAction(action_solve);
	mainwindow_movemenu->addAction(action_search);
	mainwindow_movemenu->addSeparator();
	mainwindow_movemenu->addAction(action_validate);
	
	mainwindow_settingsmenu = menuBar()->addMenu(tr("&Settings"));
	mainwindow_settingsmenu->addAction(action_hintunique);
	
	mainwindow_helpmenu = menuBar()->addMenu(tr("&Help"));
	mainwindow_helpmenu->addAction(action_about);
}


void MainWindow::initStatus()
{
	setStatusBar(new QStatusBar(this));	
	statusBar()->showMessage(PACKAGE_STRING);
}

void MainWindow::updateTitle()
{
	if (mainwindow_solverwindow->filename().isEmpty()) {
		setWindowTitle(PACKAGE_NAME);
		
		action_revert->setEnabled(false);
		
	} else {
		QFileInfo fileinfo(mainwindow_solverwindow->filename());
		setWindowTitle(fileinfo.baseName() + " - " + PACKAGE_NAME);
		
		action_revert->setEnabled(true);
	}
	
	action_hintunique->setChecked(mainwindow_solverwindow->showHintUnique());
}

void MainWindow::updateStatus(const QString & text)
{
	statusBar()->showMessage(text);
}

void MainWindow::doNew()
{
	mainwindow_solverwindow->doNew();
	updateTitle();
}

void MainWindow::doSave()
{
	mainwindow_solverwindow->doSave();
	updateTitle();
}

void MainWindow::doSaveAs()
{
	mainwindow_solverwindow->doSaveAs();
	updateTitle();
}

void MainWindow::doOpen()
{
	mainwindow_solverwindow->doOpen();
	updateTitle();
}

void MainWindow::doRevert()
{
	mainwindow_solverwindow->doRevert();
	updateTitle();
}

void MainWindow::doValidate()
{
	mainwindow_solverwindow->doValidate();
}


void MainWindow::doShowHintUnique()
{
	mainwindow_solverwindow->doShowHintUnique();
	updateTitle();
}

void MainWindow::doQuit()
{
	if (QMessageBox::question(this, tr("Quit"), tr("Exit the application?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
		qApp->closeAllWindows();
	}
}

void MainWindow::doAbout()
{
	QMessageBox::information(this, tr("About %1").arg(PACKAGE_NAME),
		tr("%1 version %2\n\n"
		   "This application was written by Stijn 'Ingar' Buys and "
		   "is available under the terms and conditions of the GNU Public License, version 3 or higher.")
		.arg(PACKAGE_NAME)
		.arg(PACKAGE_VERSION));
}
