
#include "solverwindow.h"
#include "sudokuwidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QPushButton>

SolverWindow::SolverWindow()
{
	QHBoxLayout *windowlayout = new QHBoxLayout();
	
	
	// sidebar
	QVBoxLayout *sidebarlayout = new QVBoxLayout();	
	
	// add load button
	QPushButton *loadbutton = new QPushButton(tr("Load"));
	sidebarlayout->addWidget(loadbutton);
	
	// add save button
	QPushButton *savebutton = new QPushButton(tr("Save"));
	sidebarlayout->addWidget(savebutton);
	
	// add step button
	QPushButton *stepbutton = new QPushButton(tr("Step"));
	sidebarlayout->addWidget(stepbutton);
	
	// add stretch
	sidebarlayout->addStretch(1);
	
	// add clear button
	QPushButton *clearbutton = new QPushButton(tr("Clear"));
	sidebarlayout->addWidget(clearbutton);
	
	// add sidebar layout
	windowlayout->addLayout(sidebarlayout);
	
	
	// sudoku widget
	SudokuWidget *sudokuwidget = new SudokuWidget();
	windowlayout->addWidget(sudokuwidget);
	
	// set window layout
	setLayout(windowlayout);
}
