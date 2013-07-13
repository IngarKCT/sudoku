#ifndef __INCLUDED_SUDOKUSOLVER_SETTINGS__
#define __INCLUDED_SUDOKUSOLVER_SETTINGS__

#include <QtGui>

class Settings {
public:
	Settings();

	inline const QString & homePath() const
	{
		return m_homePath;
	}
	
	inline const QColor & colorInvalidValue() const
	{
		return m_colorInvalidValue;
	}
	
	inline const QColor & colorInputError() const
	{
		return m_colorInputError;
	}
	
private:	
	QString 	m_homePath;
	QColor 		m_colorInvalidValue;
	QColor 		m_colorInputError;
};

const Settings & globalSettings();

#endif // __INCLUDED_SUDOKUSOLVER_SETTINGS__
