
#include "sudokuwidget.h"
#include "settings.h"

#include <QLineEdit>
#include <QGridLayout>
#include <QString>

SudokuWidget::SudokuWidget()
{
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 9 ; column++) {
			
			sudokuwidget_value[row][column] = new QLineEdit(this);
			sudokuwidget_value[row][column]->setFrame(false);
			sudokuwidget_value[row][column]->setAlignment(Qt::AlignCenter);
			
			connect(sudokuwidget_value[row][column], SIGNAL(textEdited(const QString &)), this, SLOT(verify(const QString &)));
		}
	}
}

void SudokuWidget::verify()
{
	Sudoku values;
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 9 ; column++) {
			bool ok;
			QString str(sudokuwidget_value[row][column]->text());
			int i = str.toInt(&ok);
			if (ok && (i > 0) && (i <= 9)) {
				values.cell(row, column).set_value(i);
			} else {
				values.cell(row, column).set_value(0);
				QPalette child_palette(palette());
				if (!sudokuwidget_value[row][column]->text().isEmpty()) {
					child_palette.setColor(QPalette::Base, globalSettings().colorInputError());
				}
				sudokuwidget_value[row][column]->setPalette(child_palette);
			}
		}
	}
		
	bool solved = values.solved();
	
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 9 ; column++) {
			QPalette child_palette(palette());
			int i = values.cell(row, column).value();
			if ( (i > 0) && (i <= 9) ) {
				// set background color depending on the validity of the cell value
				if (solved) {
					child_palette.setColor(QPalette::Base, globalSettings().colorSolved());
				} else if (!values.cell(row, column).valid()) {
					child_palette.setColor(QPalette::Base, globalSettings().colorInvalidValue());
				}
				sudokuwidget_value[row][column]->setPalette(child_palette);
			}
		}
	}
}

void SudokuWidget::verify(const QString & text) {
	verify();
}

QSize SudokuWidget::sizeHint () const
{
        return QSize(512, 512);
}

void SudokuWidget::set_values(const Sudoku & values)
{	
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 9 ; column++) {
			QPalette child_palette(palette());
			int i = values.cell(row, column).value();
			if (i > 0) {
				QString str = QString::number(i);		
				sudokuwidget_value[row][column]->setText(str);
				
				// set background color depending on the validity of the cell value
				if (!values.cell(row, column).valid()) {
					child_palette.setColor(QPalette::Base, globalSettings().colorInvalidValue());
				}
			} else {
				sudokuwidget_value[row][column]->clear();
			}
			sudokuwidget_value[row][column]->setPalette(child_palette);
		}
	}
	
	verify();
}

void SudokuWidget::get_values(Sudoku & values)
{
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 9 ; column++) {
			bool ok;
			QString str(sudokuwidget_value[row][column]->text());
			int i = str.toInt(&ok);
			if (ok && (i > 0) && (i <= 9)) {
				values.cell(row, column).set_value(i);
			} else {
				values.cell(row, column).set_value(0);
			}
		}
	}	
}

void SudokuWidget::resizeEvent(QResizeEvent *event)
{
	// cell size
	int sgx = width() / 9;
	int sgy = height() / 9;	
	if (sgx > sgy) {
		sgx = sgy;
	} else {
		sgy = sgx;
	}
	
	// offset, used to center the grid inside the widget
	int offset_x = (width() - 9 * sgx) / 2;
	int offset_y = (height() - 9 * sgy) / 2;
	
	QFont font("default", 16);
	font.setPixelSize(sgx / 2);
		
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 9 ; column++) {
			sudokuwidget_value[row][column]->setFont(font);
			sudokuwidget_value[row][column]->setGeometry(offset_x + column * sgx + 2, offset_y + row * sgy + 2 , sgx - 4, sgy - 4);
			
		}
	}
}

void SudokuWidget::paintEvent(QPaintEvent *event)
{
	if ((width() < 16) || (height() < 16))
		return;

	// main line color
	const QColor mainlinecolor(0, 0, 0);
	// subgrid line color
	const QColor sublinecolor(64, 64, 64);

	// subgrid size
	int sgx = width() / 9;
	int sgy = height() / 9;
	
	// offset
	if (sgx > sgy) {
		sgx = sgy;
	} else {
		sgy = sgx;
	}	
	int offset_x = (width() - 9 * sgx) / 2;
	int offset_y = (height() - 9 * sgy) / 2;
	
	// draw background
	QPainter painter(this);	
	QPen pen(palette().color(QPalette::Base), 1, Qt::SolidLine);
	painter.setPen(pen);
	
	painter.fillRect(offset_x, offset_y, sgx * 9 , sgy * 9, palette().color(QPalette::Base));
			 
	// draw subgrid
	pen.setWidth(1);
	pen.setColor(palette().color(QPalette::Text));
	painter.setPen(pen);
	
	for (int i = 0; i < 9; i++) {
		if ( (i % 3) > 0 ) {
			painter.drawLine(offset_x, offset_y + i * sgy, offset_x + sgx * 9, offset_y + i * sgy);
			painter.drawLine(offset_x + i * sgx, offset_y, offset_x +i * sgx, offset_y + sgy * 9);
		}
	}
	
	// draw main grid lines
	int sx = sgx * 3;
	int sy = sgy * 3;
		
	for (int i = 0; i <= 3; i++) {
		if ( (i % 3) == 0) {
			pen.setColor(palette().color(QPalette::WindowText));
			pen.setWidth(1);
			painter.setPen(pen);	
		} else {
			pen.setColor(palette().color(QPalette::WindowText));
			pen.setWidth(2);
			painter.setPen(pen);
		}
		painter.drawLine(offset_x, offset_y + i * sy, offset_x + sx * 3, offset_y + i * sy);
		painter.drawLine(offset_x + i * sx, offset_y, offset_x + i * sx, offset_y + sy * 3);
	}
}
