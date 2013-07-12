
#include "solverwindow.h"
#include "sudokuwidget.h"
#include "sudoku.h"

#include <QtGui>
#include <QDir>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

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

void SolverWindow::openFromFile(const QString & filename)
{
	QFile file(filename);
	
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Open"),
				tr("Could not open file \"%1\":\n%2.")
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
	file.close();
	
	solverwindow_sudokuwidget->set_values(sudoku);
	solverwindow_filename = filename;
	
	QApplication::restoreOverrideCursor();
}


void SolverWindow::saveToFile(const QString & filename)
{
	QFile file(filename);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Save"),
				tr("Could not write to file \"%1\":\n%2.")
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


void SolverWindow::doOpen()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Open"), HOMEDIR, "Sudoku (*.sudoku)");
     	
	if (!filename.isEmpty()) {
		openFromFile(filename);
	}	
}

void SolverWindow::doRevert()
{
	if (!solverwindow_filename.isEmpty()) {
		QFileInfo fileinfo(solverwindow_filename);
		if (QMessageBox::warning(this, tr("Revert?"), tr("Revert the state of the game to the previously saved file \"%1\"?").arg(fileinfo.fileName()), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
			openFromFile(solverwindow_filename);
		}
	}
}

void SolverWindow::doSave()
{
	if (solverwindow_filename.isEmpty()) {
		// no file name is set, use the Save As dialog
		doSaveAs();
	} else {
		// confirm overwriting an existing file
		QFile file (solverwindow_filename);
		if (file.exists()) {
			QFileInfo fileinfo(file);
			if (QMessageBox::warning(this, tr("Overwrite file?"), tr("The file \"%1\" already exists. Do you wish to overwrite it?").arg(fileinfo.fileName()), QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) {
				return;
			}
		} 
		saveToFile(solverwindow_filename);
		
	}
}

void SolverWindow::doSaveAs()
{
	// QFileDialog::getSaveFileName() warns about existing files
	QString filename = QFileDialog::getSaveFileName(this, tr("Save as..."), HOMEDIR, "Sudoku (*.sudoku)");
	
	if (!filename.isEmpty()) {
		saveToFile(filename);
	}
}

void SolverWindow::doNew()
{
	if (QMessageBox::question(this, tr("New"), tr("Start a new game?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
		Sudoku sudoku;
		solverwindow_sudokuwidget->set_values(sudoku);
		solverwindow_filename.clear();
	}
}

void SolverWindow::doStep()
{
	Sudoku sudoku;
	solverwindow_sudokuwidget->get_values(sudoku);
	
	Sudoku solution(sudoku);
	int solved = solution.solve_rules();
	if (solved == 0) {
		QMessageBox::warning(this, tr("Step"), tr("No more cells to solve!"));
		return;
	}
	
	// compare sudoku and solution values
	int index_start = qrand() % 81;
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

void SolverWindow::doGuess()
{
	Sudoku sudoku;
	solverwindow_sudokuwidget->get_values(sudoku);
	
	Sudoku solution(sudoku);
	int solved = solution.solve_search();
	if (solved == 0) {
		QMessageBox::warning(this, tr("Guess"), tr("No more cells to solve!"));
		return;
	}
	
	// compare sudoku and solution values
	int index_start = qrand() % 81;
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

void SolverWindow::doSolve()
{
	// TODO detect invalid and solved states
	Sudoku sudoku;
	solverwindow_sudokuwidget->get_values(sudoku);
	int solved = sudoku.solve_rules();
	sudoku.validate();
	solverwindow_sudokuwidget->set_values(sudoku);
	
	if (solved == 0) {
		QMessageBox::warning(this, tr("Solve rules"), tr("No more cells to solve!"));
		return;
	}
}

void SolverWindow::doSearch()
{
	// TODO detect invalid and solved states
	Sudoku sudoku;
	solverwindow_sudokuwidget->get_values(sudoku);
	int iterations = sudoku.solve_search();
	sudoku.validate();
	solverwindow_sudokuwidget->set_values(sudoku);
	
	if (iterations == 0) {
		QMessageBox::warning(this, tr("Find solution"), tr("No more cells to solve!"));
		return;
	}
}

void SolverWindow::doValidate()
{
	Sudoku sudoku;
	solverwindow_sudokuwidget->get_values(sudoku);
	
	bool is_valid = sudoku.validate();
	solverwindow_sudokuwidget->set_values(sudoku);
	
	if (is_valid) {
		QMessageBox::information(this, tr("Validate"), tr("Sudoku is valid."));
	} else {
		QMessageBox::warning(this, tr("Validate"), tr("Sudoku is not valid!"));
	}	
}

void SolverWindow::step_constraints()
{
	Sudoku sudoku;
	solverwindow_sudokuwidget->get_values(sudoku);
	int solved = sudoku.solve_constraints();
	solverwindow_sudokuwidget->set_values(sudoku);
}

void SolverWindow::step_coverage()
{
	Sudoku sudoku;
	solverwindow_sudokuwidget->get_values(sudoku);
	int solved = sudoku.solve_coverage();
	solverwindow_sudokuwidget->set_values(sudoku);
}

