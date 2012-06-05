
#include "sudoku.h"

#include <QLineEdit>
#include <QGridLayout>

Sudoku::Sudoku()
{
	QGridLayout *gridlayout = new QGridLayout();
	
	for (size_t row = 0; row < 9; row++) {
		for (size_t column = 0; column < 9 ; column++) {
			sudoku_value[row][column] = new QLineEdit();
			gridlayout->addWidget(sudoku_value[row][column], row, column);
		}
			
	}
	
	setLayout(gridlayout);
}