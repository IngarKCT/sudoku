
#include "solverwindow.h"
#include "sudokuwidget.h"
#include "sudoku.h"

#include <QtGui>
#include <QDir>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

const QString HOMEDIR(QDir::homePath() + "/.sudoku");

SolverWindow::SolverWindow()
{
	QHBoxLayout *windowlayout = new QHBoxLayout();
	
	
	// sidebar
	QVBoxLayout *sidebarlayout = new QVBoxLayout();	
	
	// add load button
	QPushButton *loadbutton = new QPushButton(tr("Load"));
	sidebarlayout->addWidget(loadbutton);
	connect(loadbutton, SIGNAL(clicked()), this, SLOT(load()));
	
	// add save button
	QPushButton *savebutton = new QPushButton(tr("Save"));
	sidebarlayout->addWidget(savebutton);
	connect(savebutton, SIGNAL(clicked()), this, SLOT(save()));
	
	// add revert button
	QPushButton *revertbutton = new QPushButton(tr("Revert"));
	sidebarlayout->addWidget(revertbutton);
	connect(revertbutton, SIGNAL(clicked()), this, SLOT(revert()));
	
	// add step constraints button
	QPushButton *stepconstraintsbutton = new QPushButton(tr("Constraints"));
	sidebarlayout->addWidget(stepconstraintsbutton);
	connect(stepconstraintsbutton, SIGNAL(clicked()), this, SLOT(step_constraints()));

	// add step coverage button
	QPushButton *stepcoveragebutton = new QPushButton(tr("Coverage"));
	sidebarlayout->addWidget(stepcoveragebutton);
	connect(stepcoveragebutton, SIGNAL(clicked()), this, SLOT(step_coverage()));
	
	// add stretch
	sidebarlayout->addStretch(1);
	
	// add clear button
	QPushButton *clearbutton = new QPushButton(tr("Clear"));
	sidebarlayout->addWidget(clearbutton);
	connect(clearbutton, SIGNAL(clicked()), this, SLOT(clear()));
	
	// add sidebar layout
	windowlayout->addLayout(sidebarlayout);
	
	
	// sudoku widget
	solverwindow_sudokuwidget = new SudokuWidget();
	windowlayout->addWidget(solverwindow_sudokuwidget, 1);
	
	// set window layout
	setLayout(windowlayout);

	// create home directory
	QDir directory;
	if (!directory.exists(HOMEDIR)) {
		directory.mkdir(HOMEDIR);
	}
}

void SolverWindow::load()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Open..."), HOMEDIR, "Sudoku (*.sudoku)");
     	if (filename.isEmpty()) {
		return;
	}
	
	QFile file(filename);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Open file"),
				tr("Could not open file %1:\n%2.")
				.arg(filename)
				.arg(file.errorString()));
		return;
	}

	QApplication::setOverrideCursor(Qt::WaitCursor);
	
	QTextStream textstream(&file);
	
	Sudoku sudoku;	
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 9 ; column++) {
			int i;
			textstream >> i;
			sudoku.set_value(row, column, i);
		}
	}
	solverwindow_sudokuwidget->set_values(sudoku);
	solverwindow_revertstate.assign(sudoku);
	
	file.close();
	
	QApplication::restoreOverrideCursor();
}

void SolverWindow::revert()
{
	solverwindow_sudokuwidget->set_values(solverwindow_revertstate);
}

void SolverWindow::save()
{
	QString filename = QFileDialog::getSaveFileName(this, tr("Save as..."), HOMEDIR, "Sudoku (*.sudoku)");
	if (filename.isEmpty()) {
		return;
	}
	
	QFile file(filename);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Save file"),
				tr("Cannot write file %1:\n%2.")
				.arg(filename)
				.arg(file.errorString()));
		return;
	}

	QApplication::setOverrideCursor(Qt::WaitCursor);
	
	QTextStream textstream(&file);
	
	Sudoku sudoku;
	solverwindow_sudokuwidget->get_values(sudoku);
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 9 ; column++) {
			textstream << sudoku.value(row, column);
			if (column < 8) {
				textstream  << ' ';
				if ((column % 3) == 2) {
					textstream  << ' ';
				}
					
			} else {
				textstream  << '\n';
			}
		}
		if ((row < 8) && ((row % 3) == 2)) {
			textstream  << '\n';
		}
	}
	
	file.close();
	
	QApplication::restoreOverrideCursor();

	return;
}

void SolverWindow::clear()
{
	Sudoku sudoku;
	solverwindow_sudokuwidget->set_values(sudoku);
}

void SolverWindow::step_constraints()
{
	Sudoku sudoku;
	solverwindow_sudokuwidget->get_values(sudoku);
	int solved = sudoku.solve_constraints();
	solverwindow_sudokuwidget->set_values(sudoku);
	qDebug() << solved << " cells solved";
}

void SolverWindow::step_coverage()
{
	Sudoku sudoku;
	solverwindow_sudokuwidget->get_values(sudoku);
	int solved = sudoku.solve_coverage();
	solverwindow_sudokuwidget->set_values(sudoku);
	qDebug() << solved << " cells solved";
}