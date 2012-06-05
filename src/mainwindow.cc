
#include "mainwindow.h"
#include "solverwindow.h"

MainWindow::MainWindow()
{
	SolverWindow *solverwindow = new SolverWindow();	
	setCentralWidget(solverwindow);
}
