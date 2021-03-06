
// VolleyScoreboard.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "VolleyScoreboard.h"
#include "VSOptionsSheet.h"
#include "VSUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define PROFILE_SECTION_SETTINGS _T("Settings")
#define PROFILE_SECTION_DISPLAYPOS _T("DisplayPosition")
#define PROFILE_SECTION_CONTROLPOS _T("ControlPosition")

#define PROFILE_ENTRY_HOME_LABEL _T("HomeLabel")
#define PROFILE_ENTRY_GUEST_LABEL _T("GuestLabel")
#define PROFILE_ENTRY_SETS_LABEL _T("SetsLabel")
#define PROFILE_ENTRY_TIMEOUTS_LABEL _T("TimeoutsLabel")
#define PROFILE_ENTRY_DISPLAYBACK_COLOR _T("DisplayBackColor")
#define PROFILE_ENTRY_DISPLAYTEXT_COLOR _T("DisplayTextColor")
#define PROFILE_ENTRY_SCOREBACK_COLOR _T("ScoreBackColor")
#define PROFILE_ENTRY_SCORETEXT_COLOR _T("ScoreTextColor")
#define PROFILE_ENTRY_SETSBACK_COLOR _T("SetsBackColor")
#define PROFILE_ENTRY_SETSTEXT_COLOR _T("SetsTextColor")
#define PROFILE_ENTRY_TIMEOUTSBACK_COLOR _T("TimeoutsBackColor")
#define PROFILE_ENTRY_TIMEOUTSTEXT_COLOR _T("TimeoutsTextColor")

#define PROFILE_ENTRY_SAVEPOSITION _T("SavePosition")

#define PROFILE_ENTRY_WINDOWPLACEMENT _T("WindowPlacement") // STRUCT
#define PROFILE_ENTRY_FULLSCREEN _T("FullScreen") // LONG

// CVolleyScoreboardApp

BEGIN_MESSAGE_MAP(CVolleyScoreboardApp, CWinApp)
//	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CVolleyScoreboardApp construction

CVolleyScoreboardApp::CVolleyScoreboardApp()
{
	m_bShellManagerAutocreated = FALSE;
	m_bKeyDown = FALSE;
	m_bKeyDownManaged = FALSE;

	m_pControlDlg = NULL;
	m_pDisplayDlg = NULL;

	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	InitShellManager();
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


CVolleyScoreboardApp::~CVolleyScoreboardApp()
{
	if (m_bShellManagerAutocreated && afxShellManager != NULL)
	{
		delete afxShellManager;
		afxShellManager = NULL;
	}
}

// The one and only CVolleyScoreboardApp object

CVolleyScoreboardApp theApp;


void CVolleyScoreboardApp::UpdateSettings(const CVSAppData& appData)
{
	GetData().CopySettingsFrom(appData);
	m_pDisplayDlg->UpdateSettings();
	m_pControlDlg->UpdateSettings();
}

void CVolleyScoreboardApp::SaveSettings()
{
	ASSERT(!m_strSettingFile.IsEmpty());
	if (m_strSettingFile.IsEmpty()) return;

	CString strTmp;

	WritePrivateProfileString(PROFILE_SECTION_SETTINGS, PROFILE_ENTRY_HOME_LABEL, GetData().m_strHomeLabel, m_strSettingFile);
	WritePrivateProfileString(PROFILE_SECTION_SETTINGS, PROFILE_ENTRY_GUEST_LABEL, GetData().m_strGuestLabel, m_strSettingFile);
	WritePrivateProfileString(PROFILE_SECTION_SETTINGS, PROFILE_ENTRY_SETS_LABEL, GetData().m_strSetsLabel, m_strSettingFile);
	WritePrivateProfileString(PROFILE_SECTION_SETTINGS, PROFILE_ENTRY_TIMEOUTS_LABEL, GetData().m_strTimeoutsLabel, m_strSettingFile);

	CVSUtils::ColorToString(GetData().m_clrDisplayBack, strTmp);
	WritePrivateProfileString(PROFILE_SECTION_SETTINGS, PROFILE_ENTRY_DISPLAYBACK_COLOR, strTmp, m_strSettingFile);
	CVSUtils::ColorToString(GetData().m_clrDisplayText, strTmp);
	WritePrivateProfileString(PROFILE_SECTION_SETTINGS, PROFILE_ENTRY_DISPLAYTEXT_COLOR, strTmp, m_strSettingFile);

	CVSUtils::ColorToString(GetData().m_clrScoreBack, strTmp);
	WritePrivateProfileString(PROFILE_SECTION_SETTINGS, PROFILE_ENTRY_SCOREBACK_COLOR, strTmp, m_strSettingFile);
	CVSUtils::ColorToString(GetData().m_clrScoreText, strTmp);
	WritePrivateProfileString(PROFILE_SECTION_SETTINGS, PROFILE_ENTRY_SCORETEXT_COLOR, strTmp, m_strSettingFile);

	CVSUtils::ColorToString(GetData().m_clrSetsBack, strTmp);
	WritePrivateProfileString(PROFILE_SECTION_SETTINGS, PROFILE_ENTRY_SETSBACK_COLOR, strTmp, m_strSettingFile);
	CVSUtils::ColorToString(GetData().m_clrSetsText, strTmp);
	WritePrivateProfileString(PROFILE_SECTION_SETTINGS, PROFILE_ENTRY_SETSTEXT_COLOR, strTmp, m_strSettingFile);

	CVSUtils::ColorToString(GetData().m_clrTimeoutsBack, strTmp);
	WritePrivateProfileString(PROFILE_SECTION_SETTINGS, PROFILE_ENTRY_TIMEOUTSBACK_COLOR, strTmp, m_strSettingFile);
	CVSUtils::ColorToString(GetData().m_clrTimeoutsText, strTmp);
	WritePrivateProfileString(PROFILE_SECTION_SETTINGS, PROFILE_ENTRY_TIMEOUTSTEXT_COLOR, strTmp, m_strSettingFile);

	CVSUtils::LongToString(GetData().m_bSavePosition, strTmp);
	WritePrivateProfileString(PROFILE_SECTION_SETTINGS, PROFILE_ENTRY_SAVEPOSITION, strTmp, m_strSettingFile);

}

void CVolleyScoreboardApp::LoadSettings()
{
	ASSERT(!m_strSettingFile.IsEmpty());
	if (m_strSettingFile.IsEmpty()) return;

	TCHAR strTmp[1024];
	CString strDefault;

	if (GetPrivateProfileString(PROFILE_SECTION_SETTINGS, PROFILE_ENTRY_HOME_LABEL, GetData().m_strHomeLabel, strTmp, (sizeof(strTmp) / sizeof(TCHAR)), m_strSettingFile) >= 0) {
		GetData().m_strHomeLabel = strTmp;
	}
	if (GetPrivateProfileString(PROFILE_SECTION_SETTINGS, PROFILE_ENTRY_GUEST_LABEL, GetData().m_strGuestLabel, strTmp, (sizeof(strTmp) / sizeof(TCHAR)), m_strSettingFile) >= 0) {
		GetData().m_strGuestLabel = strTmp;
	}
	if (GetPrivateProfileString(PROFILE_SECTION_SETTINGS, PROFILE_ENTRY_SETS_LABEL, GetData().m_strSetsLabel, strTmp, (sizeof(strTmp) / sizeof(TCHAR)), m_strSettingFile) >= 0) {
		GetData().m_strSetsLabel = strTmp;
	}
	if (GetPrivateProfileString(PROFILE_SECTION_SETTINGS, PROFILE_ENTRY_TIMEOUTS_LABEL, GetData().m_strTimeoutsLabel, strTmp, (sizeof(strTmp) / sizeof(TCHAR)), m_strSettingFile) > 0) {
		GetData().m_strTimeoutsLabel = strTmp;
	}

	CVSUtils::ColorToString(GetData().m_clrDisplayText, strDefault);
	if (GetPrivateProfileString(PROFILE_SECTION_SETTINGS, PROFILE_ENTRY_DISPLAYTEXT_COLOR, strDefault, strTmp, (sizeof(strTmp) / sizeof(TCHAR)), m_strSettingFile) > 0) {
		CVSUtils::StringToColor(strTmp, GetData().m_clrDisplayText);
	}
	CVSUtils::ColorToString(GetData().m_clrDisplayBack, strDefault);
	if (GetPrivateProfileString(PROFILE_SECTION_SETTINGS, PROFILE_ENTRY_DISPLAYBACK_COLOR, strDefault, strTmp, (sizeof(strTmp) / sizeof(TCHAR)), m_strSettingFile) > 0) {
		CVSUtils::StringToColor(strTmp, GetData().m_clrDisplayBack);
	}

	CVSUtils::ColorToString(GetData().m_clrScoreBack, strDefault);
	if (GetPrivateProfileString(PROFILE_SECTION_SETTINGS, PROFILE_ENTRY_SCOREBACK_COLOR, strDefault, strTmp, (sizeof(strTmp) / sizeof(TCHAR)), m_strSettingFile) > 0) {
		CVSUtils::StringToColor(strTmp, GetData().m_clrScoreBack);
	}
	CVSUtils::ColorToString(GetData().m_clrScoreText, strDefault);
	if (GetPrivateProfileString(PROFILE_SECTION_SETTINGS, PROFILE_ENTRY_SCORETEXT_COLOR, strDefault, strTmp, (sizeof(strTmp) / sizeof(TCHAR)), m_strSettingFile) > 0) {
		CVSUtils::StringToColor(strTmp, GetData().m_clrScoreText);
	}

	CVSUtils::ColorToString(GetData().m_clrSetsBack, strDefault);
	if (GetPrivateProfileString(PROFILE_SECTION_SETTINGS, PROFILE_ENTRY_SETSBACK_COLOR, strDefault, strTmp, (sizeof(strTmp) / sizeof(TCHAR)), m_strSettingFile) > 0) {
		CVSUtils::StringToColor(strTmp, GetData().m_clrSetsBack);
	}
	CVSUtils::ColorToString(GetData().m_clrSetsText, strDefault);
	if (GetPrivateProfileString(PROFILE_SECTION_SETTINGS, PROFILE_ENTRY_SETSTEXT_COLOR, strDefault, strTmp, (sizeof(strTmp) / sizeof(TCHAR)), m_strSettingFile) > 0) {
		CVSUtils::StringToColor(strTmp, GetData().m_clrSetsText);
	}

	CVSUtils::ColorToString(GetData().m_clrScoreBack, strDefault);
	if (GetPrivateProfileString(PROFILE_SECTION_SETTINGS, PROFILE_ENTRY_TIMEOUTSBACK_COLOR, strDefault, strTmp, (sizeof(strTmp) / sizeof(TCHAR)), m_strSettingFile) > 0) {
		CVSUtils::StringToColor(strTmp, GetData().m_clrTimeoutsBack);
	}
	CVSUtils::ColorToString(GetData().m_clrScoreText, strDefault);
	if (GetPrivateProfileString(PROFILE_SECTION_SETTINGS, PROFILE_ENTRY_TIMEOUTSTEXT_COLOR, strDefault, strTmp, (sizeof(strTmp) / sizeof(TCHAR)), m_strSettingFile) > 0) {
		CVSUtils::StringToColor(strTmp, GetData().m_clrTimeoutsText);
	}

	CVSUtils::LongToString(GetData().m_bSavePosition, strDefault);
	if (GetPrivateProfileString(PROFILE_SECTION_SETTINGS, PROFILE_ENTRY_SAVEPOSITION, strDefault, strTmp, (sizeof(strTmp) / sizeof(TCHAR)), m_strSettingFile) > 0) {
		CVSUtils::StringToLong(strTmp, GetData().m_bSavePosition);
	}

}

void CVolleyScoreboardApp::LoadWindowPosition()
{
	CString strDefault;
	TCHAR strTmp[32];

	if (m_pControlDlg) {
		WINDOWPLACEMENT wp{ 0 };
		if (GetPrivateProfileStruct(PROFILE_SECTION_CONTROLPOS, PROFILE_ENTRY_WINDOWPLACEMENT, &wp, sizeof(WINDOWPLACEMENT), m_strSettingFile)) {
			WINDOWPLACEMENT wpOrig;
			// save only XY position 
			m_pControlDlg->GetWindowPlacement(&wpOrig);
			CRect rcOrig(wpOrig.rcNormalPosition);
			rcOrig.MoveToXY(wp.rcNormalPosition.left, wp.rcNormalPosition.top);
			wpOrig.rcNormalPosition = rcOrig;
			CVSUtils::EnsureRectangleOnDisplay(&wpOrig.rcNormalPosition);
			m_pControlDlg->SetWindowPlacement(&wpOrig);
		}
	}

	if (m_pDisplayDlg) {
		WINDOWPLACEMENT wp{ 0 };
		if (GetPrivateProfileStruct(PROFILE_SECTION_DISPLAYPOS, PROFILE_ENTRY_WINDOWPLACEMENT, &wp, sizeof(WINDOWPLACEMENT), m_strSettingFile)) {
			CVSUtils::EnsureRectangleOnDisplay(&wp.rcNormalPosition);
			m_pDisplayDlg->SetWindowPlacement(&wp);
		}
		LONG isFullScreen = 0;
		CVSUtils::LongToString(isFullScreen, strDefault);
		if (GetPrivateProfileString(PROFILE_SECTION_DISPLAYPOS, PROFILE_ENTRY_FULLSCREEN, strDefault, strTmp, (sizeof(strTmp) / sizeof(TCHAR)), m_strSettingFile) > 0) {
			CVSUtils::StringToLong(strTmp, isFullScreen);
		}
		if (isFullScreen)
			m_pDisplayDlg->ShowFullScreen(isFullScreen);
	}
}

void CVolleyScoreboardApp::SaveWindowPosition()
{
	if (GetData().m_bSavePosition) {
		CString strTmp;
		if (m_pControlDlg) {
			WINDOWPLACEMENT wp{ 0 };
			m_pControlDlg->GetWindowPlacement(&wp);
			WritePrivateProfileStruct(PROFILE_SECTION_CONTROLPOS, PROFILE_ENTRY_WINDOWPLACEMENT, &wp, sizeof(WINDOWPLACEMENT), m_strSettingFile);
		}
		if (m_pDisplayDlg) {
			WINDOWPLACEMENT wp{ 0 };
			m_pDisplayDlg->GetWindowPlacement(&wp);
			WritePrivateProfileStruct(PROFILE_SECTION_DISPLAYPOS, PROFILE_ENTRY_WINDOWPLACEMENT, &wp, sizeof(WINDOWPLACEMENT), m_strSettingFile);

			LONG isFullScreen = (LONG)m_pDisplayDlg->IsFullScreen();
			CVSUtils::LongToString(isFullScreen, strTmp);
			WritePrivateProfileString(PROFILE_SECTION_DISPLAYPOS, PROFILE_ENTRY_FULLSCREEN, strTmp, m_strSettingFile);
		}
	}
	else {
		// clear sections
		WritePrivateProfileString(PROFILE_SECTION_CONTROLPOS, NULL, NULL, m_strSettingFile);
		WritePrivateProfileString(PROFILE_SECTION_DISPLAYPOS, NULL, NULL, m_strSettingFile);
	}
}

// CVolleyScoreboardApp initialization

BOOL CVolleyScoreboardApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();


	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	// SetRegistryKey(_T("VollyScoreboard-Free"));

	TCHAR buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	m_strSettingFile = buffer;
	m_strSettingFile.Replace(_T(".exe"), _T(".ini"));

	LoadSettings();

	m_pDisplayDlg = new CVSDisplayDlg();;
	m_pControlDlg = new CVSControlDlg();;
	m_pMainWnd = m_pControlDlg;

	m_pDisplayDlg->Create(CVSDisplayDlg::IDD);
	m_pControlDlg->Create(CVSControlDlg::IDD);

	LoadWindowPosition();
	//m_pDisplayDlg->ShowWindow(SW_SHOW);
	//m_pControlDlg->ShowWindow(SW_SHOW);


	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return TRUE;
}

BOOL CVolleyScoreboardApp::InitShellManager()
{
	if (afxShellManager != NULL)
	{
		return TRUE;
	}

	afxShellManager = new CShellManager;
	m_bShellManagerAutocreated = TRUE;

	return TRUE;
}

CShellManager* CVolleyScoreboardApp::GetShellManager()
{
	if (afxShellManager == NULL)
	{
		InitShellManager();
	}

	ASSERT_VALID(afxShellManager);
	return afxShellManager;
}


int CVolleyScoreboardApp::ExitInstance()
{
	SaveSettings();
	SaveWindowPosition();
	m_pControlDlg->DestroyWindow();
	delete m_pControlDlg;
	m_pControlDlg = NULL;
	m_pDisplayDlg->DestroyWindow();
	delete m_pDisplayDlg;
	m_pDisplayDlg = NULL;

// 	// Delete the shell manager created above.
// 	if (pShellManager != NULL)
// 	{
// 		delete pShellManager;
// 	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif


	return CWinApp::ExitInstance();
}

void CVolleyScoreboardApp::IncrementHomeScore(int points)
{
	GetData().IncrementHomeScore(points);
	m_pControlDlg->UpdateHomeScore();
	m_pDisplayDlg->UpdateHomeScore();
}

void CVolleyScoreboardApp::IncrementHomeSets(int sets)
{
	GetData().IncrementHomeSets(sets);
	m_pControlDlg->UpdateHomeScore();
	m_pDisplayDlg->UpdateHomeScore();
}

void CVolleyScoreboardApp::IncrementHomeTimeouts(int timeouts)
{
	GetData().IncrementHomeTimeouts(timeouts);
	m_pControlDlg->UpdateHomeScore();
	m_pDisplayDlg->UpdateHomeScore();
}

void CVolleyScoreboardApp::IncrementGuestScore(int points)
{
	GetData().IncrementGuestScore(points);
	m_pControlDlg->UpdateGuestScore();
	m_pDisplayDlg->UpdateGuestScore();

}

void CVolleyScoreboardApp::IncrementGuestSets(int sets)
{
	GetData().IncrementGuestSets(sets);
	m_pControlDlg->UpdateGuestScore();
	m_pDisplayDlg->UpdateGuestScore();

}

void CVolleyScoreboardApp::IncrementGuestTimeouts(int timeouts)
{
	GetData().IncrementGuestTimeouts(timeouts);
	m_pControlDlg->UpdateGuestScore();
	m_pDisplayDlg->UpdateGuestScore();
}

void CVolleyScoreboardApp::NewSet()
{
	GetData().NewSet();
	m_pControlDlg->UpdateScore();
	m_pDisplayDlg->UpdateScore();

}

void CVolleyScoreboardApp::NewMatch()
{
	GetData().NewMatch();
	m_pControlDlg->UpdateScore();
	m_pDisplayDlg->UpdateScore();

}

void CVolleyScoreboardApp::ToggleFullScreen()
{
	m_pDisplayDlg->ToggleFullScreen();
}

void CVolleyScoreboardApp::ShowOptions()
{
	CVSOptionsSheet options(theApp.GetData());

	if (options.DoModal() == IDOK) {

	}
}

void CVolleyScoreboardApp::Exit()
{
	if (AfxMessageBox(_T("Sei sicuro di voler chiudere Volley Scoreboard?"), MB_YESNO) == IDYES) {
		PostQuitMessage(0);
	}
}

BOOL CVolleyScoreboardApp::PreTranslateMessage(MSG* pMsg)
{
// 	if (pMsg->message == WM_KEYDOWN) {
// 		const int wParam = pMsg->wParam;
// 		const int lParam = pMsg->lParam;
// 		const int keyboardScanCode = (lParam >> 16) & 0x00ff;
// 		const int virtualKey = wParam;
// 		const int repeatCount = (lParam & 0xffff);
// 		if (!m_bKeyDown) {
// 			m_bKeyDown = TRUE;
// 			m_bKeyDownManaged = FALSE;
// 		}
// 		
// 		switch (virtualKey) {
// 		case VK_F11:
// 			ToggleFullScreen();
// 			return TRUE;
// 			break;
// 		case VK_F2:
// 			ShowOptions();
// 			return TRUE;
// 			break;
// 		}
// 	}
// 	else if (pMsg->message == WM_KEYUP) {
// 		m_bKeyDown = FALSE;
// 		m_bKeyDownManaged = FALSE;
// 	}
// 	else if (pMsg->message == WM_CHAR) {
// 		const int wParam = pMsg->wParam;
// 		const int repeatCount = (pMsg->lParam & 0xffff);
// 
// 		switch (wParam) {
// 		case _T('1'):
// 			if (!m_bKeyDownManaged)
// 				IncrementHomeScore(+1);
// 			m_bKeyDownManaged = TRUE;
// 			return TRUE;
// 			break;
// 		case _T('2'):
// 			if (!m_bKeyDownManaged)
// 				IncrementHomeScore(-1);
// 			m_bKeyDownManaged = TRUE;
// 			return TRUE;
// 			break;
// 		case _T('3'):
// 			if (!m_bKeyDownManaged)
// 				IncrementHomeSets(+1);
// 			m_bKeyDownManaged = TRUE;
// 			return TRUE;
// 			break;
// 		case _T('4'):
// 			if (!m_bKeyDownManaged)
// 				IncrementHomeSets(-1);
// 			m_bKeyDownManaged = TRUE;
// 			return TRUE;
// 			break;
// 		case _T('7'):
// 			if (!m_bKeyDownManaged)
// 				IncrementGuestSets(+1);
// 			m_bKeyDownManaged = TRUE;
// 			return TRUE;
// 			break;
// 		case _T('8'):
// 			if (!m_bKeyDownManaged)
// 				IncrementGuestSets(-1);
// 			m_bKeyDownManaged = TRUE;
// 			return TRUE;
// 			break;
// 		case _T('9'):
// 			if (!m_bKeyDownManaged)
// 				IncrementGuestScore(+1);
// 			m_bKeyDownManaged = TRUE;
// 			return TRUE;
// 			break;
// 		case _T('0'):
// 			if (!m_bKeyDownManaged)
// 				IncrementGuestScore(-1);
// 			m_bKeyDownManaged = TRUE;
// 			return TRUE;
// 			break;
// 		case _T('S'):
// 		case _T('s'):
// 			if (!m_bKeyDownManaged)
// 				NewSet();
// 			m_bKeyDownManaged = TRUE;
// 			return TRUE;
// 			break;
// 		case _T('M'):
// 		case _T('m'):
// 			if (!m_bKeyDownManaged)
// 				NewMatch();
// 			m_bKeyDownManaged = TRUE;
// 			return TRUE;
// 			break;
// 		}
// 	}

	return CWinApp::PreTranslateMessage(pMsg);
	
}
