
#include "sudokuwidget.h"

#include <QLineEdit>
#include <QGridLayout>

SudokuWidget::SudokuWidget()
{
	QGridLayout *gridlayout = new QGridLayout();
	
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 9 ; column++) {
			sudokuwidget_value[row][column] = new QLineEdit();
			gridlayout->addWidget(sudokuwidget_value[row][column], row, column);
		}
			
	}
	
	setLayout(gridlayout);
}