
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
 * This should move to mainwindow
 * */

const QString HOMEDIR(QDir::homePath() + "/.sudoku");

SolverWindow::SolverWindow()
{
	QHBoxLayout *windowlayout = new QHBoxLayout();

	// sudoku widget
	solverwindow_sudokuwidget = new SudokuWidget();
	windowlayout->addWidget(solverwindow_sudokuwidget, 1);
	
	// set window layout
	setLayout(windowlayout);

	// create home directory
	// FIXME this should move to mainwindow
	QDir directory;
	if (!directory.exists(HOMEDIR)) {
		directory.mkdir(HOMEDIR);
	}
}

void SolverWindow::loadFromFile(const QString & filename)
{
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
	
	solverwindow_filename = filename;
	
	QApplication::restoreOverrideCursor();
}


void SolverWindow::saveToFile(const QString & filename)
{
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
	
	solverwindow_filename = filename;
	
	QApplication::restoreOverrideCursor();
}


void SolverWindow::load()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Open..."), HOMEDIR, "Sudoku (*.sudoku)");
     	
	if (!filename.isEmpty()) {
		loadFromFile(filename);
	}
	
	return;
}

void SolverWindow::revert()
{
	if (!solverwindow_filename.isEmpty()) {
		loadFromFile(solverwindow_filename);
	}
}

void SolverWindow::save()
{
	if (solverwindow_filename.isEmpty()) {
		saveas();
	} else {
		saveToFile(solverwindow_filename);
	}
	return;
}

void SolverWindow::saveas()
{
	QString filename = QFileDialog::getSaveFileName(this, tr("Save as..."), HOMEDIR, "Sudoku (*.sudoku)");
	if (!filename.isEmpty()) {
		solverwindow_filename = filename;
		saveToFile(solverwindow_filename);
	}
	
	return;
}

void SolverWindow::clear()
{
	Sudoku sudoku;
	solverwindow_sudokuwidget->set_values(sudoku);
	
	solverwindow_filename.clear();
}

void SolverWindow::step()
{
	Sudoku sudoku;
	solverwindow_sudokuwidget->get_values(sudoku);
	
	Sudoku solution(sudoku);
	int solved = solution.solve_rules();
	if (solved == 0) {
		QMessageBox::warning(this, tr("Step"), tr("No cells to solve found"));
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

void SolverWindow::guess()
{
	Sudoku sudoku;
	solverwindow_sudokuwidget->get_values(sudoku);
	
	Sudoku solution(sudoku);
	int solved = solution.solve_search();
	if (solved == 0) {
		QMessageBox::warning(this, tr("Guess"), tr("No cells to solve found"));
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
	// TODO messagebox, detect invalid and solved states
	Sudoku sudoku;
	solverwindow_sudokuwidget->get_values(sudoku);
	int solved = sudoku.solve_rules();
	sudoku.validate();
	solverwindow_sudokuwidget->set_values(sudoku);
	qDebug() << solved << " cells solved";
}

void SolverWindow::search()
{
	// TODO messagebox, detect invalid and solved states
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
	// qDebug() << solved << " cells solved";
}

void SolverWindow::step_coverage()
{
	Sudoku sudoku;
	solverwindow_sudokuwidget->get_values(sudoku);
	int solved = sudoku.solve_coverage();
	solverwindow_sudokuwidget->set_values(sudoku);
	// qDebug() << solved << " cells solved";
}

void SolverWindow::validate()
{
	Sudoku sudoku;
	solverwindow_sudokuwidget->get_values(sudoku);
	if (sudoku.validate()) {
		QMessageBox::information(this, tr("Validate"), tr("Sudoku is valid."));
	} else {
		QMessageBox::warning(this, tr("Validate"), tr("Sudoku is not valid!"));
	}
	solverwindow_sudokuwidget->set_values(sudoku);
}

