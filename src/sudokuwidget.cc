
#include "sudokuwidget.h"

#include <QLineEdit>
#include <QGridLayout>
#include <QString>

SudokuWidget::SudokuWidget()
{
	QGridLayout *gridlayout = new QGridLayout();
	
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 9 ; column++) {
			
			sudokuwidget_value[row][column] = new QLineEdit();
			sudokuwidget_value[row][column]->setFrame(false);
			sudokuwidget_value[row][column]->setAlignment(Qt::AlignCenter);
			
			gridlayout->addWidget(sudokuwidget_value[row][column], row, column);
		}
	}
	
	setLayout(gridlayout);
}

void SudokuWidget::set_values(const Sudoku & values)
{
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 9 ; column++) {
			int i = values.value(row, column);
			if (i > 0) {
				QString str = QString::number(i);		
				sudokuwidget_value[row][column]->setText(str);
			} else {
				sudokuwidget_value[row][column]->clear();
			}
		}
	}
}

void SudokuWidget::get_values(Sudoku & values)
{
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 9 ; column++) {
			bool ok;
			QString str(sudokuwidget_value[row][column]->text());
			int i = str.toInt(&ok);
			if (ok && (i > 0) && (i <= 9)) {
				values.value(row, column) = i;
			} else {
				values.value(row, column) = 0;
			}
		}
	}	
}