
#include "mainwindow.h"
#include "sudoku.h"

MainWindow::MainWindow()
{
	mainwindow_sudoku = new Sudoku();
	
	setCentralWidget(mainwindow_sudoku);
}
