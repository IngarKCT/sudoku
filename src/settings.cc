
#ifdef _WIN32
#include <windows.h>
#include <shlobj.h>
#endif

#include "settings.h"

Settings m_globalSettings;

const Settings & globalSettings()
{
	return m_globalSettings;
}
Settings::Settings() :
	m_homePath(),
	m_colorInvalidValue(255, 0, 0),
	m_colorInputError(195, 195, 195)
{
#ifdef _WIN32
	// get the full path for "Applicaton Data"
	TCHAR appdatapath[512];
	memset(appdatapath, 0, sizeof(appdatapath));
	SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, appdatapath);
	
	// FIXME detect Unicode support
	// m_homePath = QString::fromAscii(appdatapath);
	m_homePath = QString::fromUtf16((const ushort *)appdatapath);
	m_homePath += "\\Sudoku Solver";
#else
	m_homePath = QDir::homePath() + "/.sudokusolver";
#endif
	QDir directory;
	if (!directory.exists(m_homePath)) {
		// create home directory
		directory.mkdir(m_homePath);
	}
}
