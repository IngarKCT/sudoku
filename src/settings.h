#ifndef __INCLUDED_SUDOKUSOLVER_SETTINGS__
#define __INCLUDED_SUDOKUSOLVER_SETTINGS__

#include <QtWidgets>

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
	
	inline const QColor & colorSolved() const
	{
		return m_colorSolved;
	}
	
	inline const QColor & colorHintUnique() const
	{
		return m_colorHintUnique;
	}
	
private:	
	QString 	m_homePath;
	QColor 		m_colorInvalidValue;
	QColor 		m_colorInputError;
	QColor		m_colorSolved;
	QColor		m_colorHintUnique;
};

const Settings & globalSettings();

#endif // __INCLUDED_SUDOKUSOLVER_SETTINGS__
