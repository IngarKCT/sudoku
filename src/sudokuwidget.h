
#ifndef __INCLUDED_SUDOKUSOLVER_SUDOKUWIDGET__
#define __INCLUDED_SUDOKUSOLVER_SUDOKUWIDGET__

#include <QtWidgets>
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
	
	inline const bool showHintUnique() const
	{
		return m_showHintUnique;
	}
	
	void setShowHintUnique(const bool hintunique = true);
	
	
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
	bool		m_showHintUnique;

private slots:
	void verify();
	
	void verify(const QString & text);
};

#endif // __INCLUDED_SUDOKUSOLVER_SUDOKUWIDGET__
