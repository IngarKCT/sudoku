
#include "settings.h"
#include "solverwindow.h"
#include "sudokuwidget.h"
#include "sudoku.h"

#include "config.h"

#include <QtWidgets>
#include <QDir>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

SolverWindow::SolverWindow()
{
	QHBoxLayout *windowlayout = new QHBoxLayout();

	// sudoku widget
	solverwindow_sudokuwidget = new SudokuWidget();
	windowlayout->addWidget(solverwindow_sudokuwidget, 1);
	
	// set window layout
	setLayout(windowlayout);
}

const bool SolverWindow::showHintUnique() const
{
	return solverwindow_sudokuwidget->showHintUnique();
}

void SolverWindow::openFromFile(const QString & filename)
{
	QFile file(filename);
	
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Error opening file"),
				tr("Could not open file \"%1\":\n%2.")
				.arg(filename)
				.arg(file.errorString()));
		
		QFileInfo fileinfo(filename);
		emit statusChanged(tr("Could not open file \"%1\"").arg(fileinfo.fileName()));

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
	
	QFileInfo fileinfo(filename);
	emit statusChanged(tr("Opened file \"%1\"").arg(fileinfo.fileName()));
	
	QApplication::restoreOverrideCursor();
}


void SolverWindow::saveToFile(const QString & filename)
{
	QFile file(filename);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Error saving file"),
				tr("Could not save file \"%1\":\n%2.")
				.arg(filename)
				.arg(file.errorString()));
		
		QFileInfo fileinfo(filename);
		emit statusChanged(tr("Could not save file \"%1\"").arg(fileinfo.fileName()));
		
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
	
	QFileInfo fileinfo(filename);
	emit statusChanged(tr("Saved file \"%1\"").arg(fileinfo.fileName()));
	
	QApplication::restoreOverrideCursor();
}


void SolverWindow::doOpen()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Open"), globalSettings().homePath(), "Sudoku (*.sudoku)");
     	
	if (!filename.isEmpty()) {
		openFromFile(filename);
	}	
}

void SolverWindow::doRevert()
{
	if (!solverwindow_filename.isEmpty()) {
		QFileInfo fileinfo(solverwindow_filename);
		if (QMessageBox::warning(this, tr("Revert?"), tr("Revert the game to the previously saved file \"%1\"?").arg(fileinfo.fileName()), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
			openFromFile(solverwindow_filename);
		}
	}
}

bool SolverWindow::confirmOverwrite(const QString & filename)
{
	QFile file (filename);
	if (file.exists()) {
		QFileInfo fileinfo(file);
		return (QMessageBox::warning(this, tr("Overwrite file?"), tr("The file \"%1\" already exists.\nDo you wish to overwrite it?").arg(fileinfo.fileName()), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes);
	} else {
		return true;
	}
}

void SolverWindow::doSave()
{
	if (solverwindow_filename.isEmpty()) {
		// no file name is set, use the Save As dialog
		doSaveAs();
	} else if (confirmOverwrite(solverwindow_filename)) {
		saveToFile(solverwindow_filename);
	}
}

void SolverWindow::doSaveAs()
{
	QString filename;
	do {
		filename = QFileDialog::getSaveFileName(this, tr("Save as..."), globalSettings().homePath(), "Sudoku (*.sudoku)", 0, QFileDialog::DontConfirmOverwrite);
		if (filename.isEmpty()) {
			return;
		}
	} while (!confirmOverwrite(filename));
		
	saveToFile(filename);
}

void SolverWindow::doNew()
{
	if (QMessageBox::question(this, tr("New"), tr("Start a new game?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
		Sudoku sudoku;
		solverwindow_sudokuwidget->set_values(sudoku);
		solverwindow_filename.clear();
		
		emit statusChanged(PACKAGE_STRING);
	}
}

void SolverWindow::doStep()
{
	Sudoku sudoku;
	solverwindow_sudokuwidget->get_values(sudoku);
	
	if (!sudoku.validate()) {
		QMessageBox::warning(this, tr("Step"), tr("This sudoku is not valid!"));
		return;
	}
	
	Sudoku solution(sudoku);
	int solved = solution.solve_coverage() + solution.solve_constraints();
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
	
	if (!sudoku.validate()) {
		QMessageBox::warning(this, tr("Guess"), tr("This sudoku is not valid!"));
		return;
	}
	
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
	Sudoku sudoku;
	solverwindow_sudokuwidget->get_values(sudoku);
	bool is_valid = sudoku.validate();
	sudoku.solve_rules();
	bool is_solved = sudoku.solved();
	solverwindow_sudokuwidget->set_values(sudoku);
	
	if (!is_valid) {
		QMessageBox::warning(this, tr("Find solution"), tr("This sudoku is not valid!"));
	} else if (is_solved) {
		QMessageBox::information(this, tr("Find solution"), tr("This sudoku has been solved."));
	} else {
		QMessageBox::warning(this, tr("Find solution"), tr("This sudoku can not be solved by applying the rules!"));
	}
}

void SolverWindow::doSearch()
{
	Sudoku sudoku;
	solverwindow_sudokuwidget->get_values(sudoku);
	bool is_valid = sudoku.validate();
	sudoku.solve_search();
	bool is_solved = sudoku.solved();
	solverwindow_sudokuwidget->set_values(sudoku);	
	
	if (!is_valid) {
		QMessageBox::warning(this, tr("Find solution"), tr("This sudoku is not valid!"));
	} else if (is_solved) {
		QMessageBox::information(this, tr("Find solution"), tr("This sudoku has been solved."));
	} else {
		QMessageBox::warning(this, tr("Find solution"), tr("This sudoku can not be solved!"));
	}
}

void SolverWindow::doValidate()
{
	Sudoku sudoku;
	solverwindow_sudokuwidget->get_values(sudoku);
	
	bool is_valid = sudoku.validate();
	
	solverwindow_sudokuwidget->set_values(sudoku);
	
	if (!is_valid) {
		QMessageBox::warning(this, tr("Validate"), tr("This sudoku is not valid!"));
		return;
	}
	
	bool is_solved = sudoku.solved();
	if (is_solved) {
		QMessageBox::information(this, tr("Validate"), tr("This sudoku has been solved."));
		return;
	}
	
	sudoku.solve_rules();
	is_solved = sudoku.solved();
	if (is_solved) {
		QMessageBox::information(this, tr("Validate"), tr("This sudoku can be solved by applying the rules."));
		return;
	}
	
	sudoku.solve_search();
	is_solved = sudoku.solved();
	if (is_solved) {
		QMessageBox::information(this, tr("Validate"), tr("This sudoku can be solved but needs guessing."));
		return;
	}
	
	QMessageBox::warning(this, tr("Validate"), tr("This sudoku is valid but can not be solved!"));
}

void SolverWindow::doShowHintUnique()
{
	solverwindow_sudokuwidget->setShowHintUnique(!solverwindow_sudokuwidget->showHintUnique());
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

