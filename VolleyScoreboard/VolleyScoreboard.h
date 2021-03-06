
// VolleyScoreboard.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include "VSControlDlg.h"
#include "VSDisplayDlg.h"
#include "VSAppData.h"

// CVolleyScoreboardApp:
// See VolleyScoreboard.cpp for the implementation of this class
//
class CShellManager;

class CVolleyScoreboardApp : public CWinApp
{
public:
	CVolleyScoreboardApp();
	virtual ~CVolleyScoreboardApp();
	CVSAppData& GetData() { return m_AppData; };
	void UpdateSettings(const CVSAppData& appData);

	void SaveSettings();
	void LoadSettings();

 	void LoadWindowPosition();
 	void SaveWindowPosition();

	// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance(); // return app exit code

	CShellManager* GetShellManager();
	BOOL InitShellManager();

// Implementation

	DECLARE_MESSAGE_MAP()

public:
	void IncrementHomeScore(int points); // negative to decrement
	void IncrementHomeSets(int sets); // negative to decrement
	void IncrementHomeTimeouts(int timeouts); // negative to decrement
	void IncrementGuestScore(int points); // negative to decrement
	void IncrementGuestSets(int sets); // negative to decrement
	void IncrementGuestTimeouts(int timeouts); // negative to decrement

	void NewSet();
	void NewMatch();

	void ToggleFullScreen();

	void ShowOptions();
	void Exit();

protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg); // to get keyboard shortcut

protected:
	BOOL m_bShellManagerAutocreated = FALSE;
	BOOL m_bKeyDown;
	BOOL m_bKeyDownManaged;
	CString m_strSettingFile;

public:
	CVSControlDlg * m_pControlDlg;
	CVSDisplayDlg *m_pDisplayDlg;
	CVSAppData	m_AppData;

};

extern CVolleyScoreboardApp theApp;
