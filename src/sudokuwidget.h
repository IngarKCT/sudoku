
#ifndef __INCLUDED_SUDOKUSOLVER_SUDOKUWIDGET__
#define __INCLUDED_SUDOKUSOLVER_SUDOKUWIDGET__

#include <QtGui>
#include <QWidget>

#include "sudoku.h"

class QLineEdit;

class SudokuWidget : public QWidget
{
	Q_OBJECT
	
public:
	SudokuWidget();
	
	/**
	 * @brief set widgets value from sudoku values
	 * */
	void set_values(const Sudoku & values);
	
	/**
	 * @brief set sudoku values from widget values
	 * */
	void get_values(Sudoku & values);
	
	/**
         * @brief return the default size hint for this widget
         * */
	virtual QSize sizeHint() const;
	
protected:	
        /**
         * @brief handle paint events
         * */
        virtual void paintEvent(QPaintEvent *event);
	
	/**
	 * @brief handle resize events
	 * */
	virtual void resizeEvent(QResizeEvent *event);
	
private:
	QLineEdit	* sudokuwidget_value[9][9];

private slots:
	void verify(const QString & text);
};

#endif // __INCLUDED_SUDOKUSOLVER_SUDOKUWIDGET__