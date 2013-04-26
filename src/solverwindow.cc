
#include "solverwindow.h"
#include "sudokuwidget.h"
#include "sudoku.h"

#include <QtGui>
#include <QDir>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

#include <cstdlib>
/*
 * FIXME
 * On windows, this results in a rather awkward directory.
 * The homepath should probably be a setting.
 * */

const QString HOMEDIR(QDir::homePath() + "/.sudoku");

SolverWindow::SolverWindow()
{
	QHBoxLayout *windowlayout = new QHBoxLayout();
	
	
	// sidebar
	QVBoxLayout *sidebarlayout = new QVBoxLayout();
	
	// add stretch
	sidebarlayout->addStretch(1);
	
	// add load button
	QPushButton *loadbutton = new QPushButton(tr("Load"));
	sidebarlayout->addWidget(loadbutton);
	connect(loadbutton, SIGNAL(clicked()), this, SLOT(load()));
	
	// add save button
	QPushButton *savebutton = new QPushButton(tr("Save"));
	sidebarlayout->addWidget(savebutton);
	connect(savebutton, SIGNAL(clicked()), this, SLOT(saveas()));
	
	// add revert button
	QPushButton *revertbutton = new QPushButton(tr("Revert"));
	sidebarlayout->addWidget(revertbutton);
	connect(revertbutton, SIGNAL(clicked()), this, SLOT(revert()));

	// add validate button
	QPushButton *validatebutton = new QPushButton(tr("Validate"));
	sidebarlayout->addWidget(validatebutton);
	connect(validatebutton, SIGNAL(clicked()), this, SLOT(validate()));
	
	// add a step button
	QPushButton *stepbutton = new QPushButton(tr("Step"));
	sidebarlayout->addWidget(stepbutton);
	connect(stepbutton, SIGNAL(clicked()), this, SLOT(step()));

	// add stretch
	sidebarlayout->addStretch(2);
	
	// add a solve button
	QPushButton *solvebutton = new QPushButton(tr("Solve"));
	sidebarlayout->addWidget(solvebutton);
	connect(solvebutton, SIGNAL(clicked()), this, SLOT(solve()));
	
	// add a search button
	QPushButton *searchbutton = new QPushButton(tr("Search"));
	sidebarlayout->addWidget(searchbutton);
	connect(searchbutton, SIGNAL(clicked()), this, SLOT(search()));
	
	// add clear button
	QPushButton *clearbutton = new QPushButton(tr("Clear"));
	sidebarlayout->addWidget(clearbutton);
	connect(clearbutton, SIGNAL(clicked()), this, SLOT(clear()));
	
	// add stretch
	sidebarlayout->addStretch(1);
	
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
			sudoku.cell(row, column).set_value(i);
		}
	}
	solverwindow_sudokuwidget->set_values(sudoku);
	solverwindow_revertstate.assign(sudoku);
	
	file.close();
	
	QApplication::restoreOverrideCursor();
}

void SolverWindow::revert()
{
	// FIXME this should actually re-load the savegame
	solverwindow_sudokuwidget->set_values(solverwindow_revertstate);
}

void SolverWindow::saveas()
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
			textstream << sudoku.cell(row, column).value();
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

void SolverWindow::step()
{
	Sudoku sudoku;
	solverwindow_sudokuwidget->get_values(sudoku);
	
	Sudoku solution(sudoku);
	int solved = solution.solve_rules();
	if (solved == 0) {
		qDebug() << "no solveable cells left!";
		return;
	}
	
	// compare sudoku and solution values
	int index_start = (int) random() % 81;
	int index_current = index_start;
	do {
		int column = index_current % 9;
		int row = (index_current - column) / 9;
		if ((sudoku.cell(row,column).value() == 0) && (solution.cell(row,column).value() != 0)) {
			sudoku.cell(row,column).set_value(solution.cell(row, column).value());
			solverwindow_sudokuwidget->set_values(sudoku);
			return;
		}
		
		index_current = (index_current + 1) % 81;
		
	} while (index_current != index_start);
	
}

void SolverWindow::solve()
{
	Sudoku sudoku;
	solverwindow_sudokuwidget->get_values(sudoku);
	int solved = sudoku.solve_rules();
	sudoku.validate();
	solverwindow_sudokuwidget->set_values(sudoku);
	qDebug() << solved << " cells solved";
}

void SolverWindow::search()
{
	Sudoku sudoku;
	solverwindow_sudokuwidget->get_values(sudoku);
	int iterations = sudoku.solve_search();
	solverwindow_sudokuwidget->set_values(sudoku);
	if (iterations > 0) {
		qDebug() << "solved in " << iterations << " iterations";
	}
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

void SolverWindow::validate()
{
	Sudoku sudoku;
	solverwindow_sudokuwidget->get_values(sudoku);
	if (sudoku.validate()) {
		qDebug() << "sudoku is valid";
	} else {
		qDebug() << "sudoku is not valid";
	}
	solverwindow_sudokuwidget->set_values(sudoku);
	qDebug() << "sudoku validated";
}

