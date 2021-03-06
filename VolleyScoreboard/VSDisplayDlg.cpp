
// VSDisplayDlg.cpp : implementation file
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "VolleyScoreboard.h"
#include "VSDisplayDlg.h"
#include "VSAboutDlg.h"
#include "VSUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVolleyScoreboardDisplayDlg dialog



CVSDisplayDlg::CVSDisplayDlg(CWnd* pParent /*=NULL*/, UINT nIDD)
	: CDialogEx(nIDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bKeyDown = FALSE;
	m_bKeyDownManaged = FALSE;

}

void CVSDisplayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HOME_SCORE_STATIC, m_dsHomeScore);
	DDX_Control(pDX, IDC_GUEST_SCORE_STATIC, m_dsGuestScore);
	DDX_Control(pDX, IDC_HOME_SETS_STATIC, m_dsHomeSets);
	DDX_Control(pDX, IDC_GUEST_SETS_STATIC, m_dsGuestSets);
	DDX_Control(pDX, IDC_HOME_STATIC, m_stHomeLabel);
	DDX_Control(pDX, IDC_GUEST_STATIC, m_stGuestLabel);
	DDX_Control(pDX, IDC_SETS_STATIC, m_stSetsLabel);
	DDX_Control(pDX, IDC_TIMEOUTS_STATIC, m_stTimeoutsLabel);
	DDX_Control(pDX, IDC_HOME_TIMEOUT1_BUTTON, m_stHomeTimeout1);
	DDX_Control(pDX, IDC_HOME_TIMEOUT2_BUTTON, m_stHomeTimeout2);
	DDX_Control(pDX, IDC_GUEST_TIMEOUT1_BUTTON, m_stGuestTimeout1);
	DDX_Control(pDX, IDC_GUEST_TIMEOUT2_BUTTON, m_stGuestTimeout2);
}

void CVSDisplayDlg::OnOK()
{
	return;
}

void CVSDisplayDlg::OnCancel()
{
	theApp.Exit();
}

void CVSDisplayDlg::UpdateFontSize()
{
	CHMXStatic* pStatic = &m_stGuestLabel;
	if (theApp.GetData().m_strHomeLabel.GetLength() > theApp.GetData().m_strGuestLabel.GetLength()) {
		pStatic = &m_stHomeLabel;
	}

	if (!pStatic->GetSafeHwnd()) return;
	int fontHeight = CVSUtils::GetTextFitFontHeight(pStatic);
	m_stHomeLabel.SetFontHeight(fontHeight, true);
	m_stGuestLabel.SetFontHeight(fontHeight, true);

	m_stSetsLabel.SetFontHeight(CVSUtils::GetTextFitFontHeight(&m_stSetsLabel));
	m_stTimeoutsLabel.SetFontHeight(CVSUtils::GetTextFitFontHeight(&m_stTimeoutsLabel));

}

BEGIN_MESSAGE_MAP(CVSDisplayDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR() // to make work ctl color reflect on static 
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CVolleyScoreboardDlg message handlers

BOOL CVSDisplayDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	UpdateSettings();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVSDisplayDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CVSAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVSDisplayDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}


void CVSDisplayDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	UpdateFontSize();

}


// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVSDisplayDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


HBRUSH CVSDisplayDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	
	HBRUSH hb = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (hb) return hb;

	if (m_brBkgr.GetSafeHandle() != NULL || m_hBkgrBitmap != NULL)
	{
#define AFX_MAX_CLASS_NAME 255
#define AFX_STATIC_CLASS _T("Static")
#define AFX_BUTTON_CLASS _T("Button")

		if (nCtlColor == CTLCOLOR_STATIC)
		{
			TCHAR lpszClassName[AFX_MAX_CLASS_NAME + 1];

			::GetClassName(pWnd->GetSafeHwnd(), lpszClassName, AFX_MAX_CLASS_NAME);
			CString strClass = lpszClassName;

			if (strClass == AFX_BUTTON_CLASS || strClass == AFX_STATIC_CLASS)
			{
				pDC->SetBkMode(TRANSPARENT);

				if (m_brBkgr.GetSafeHandle() != NULL && IsAppThemed())
				{
					return (HBRUSH)m_brBkgr.GetSafeHandle();
				}
				else
				{
					return (HBRUSH)::GetStockObject(HOLLOW_BRUSH);
				}
			}
		}
	}

	return hb;
}

void CVSDisplayDlg::UpdateSettings()
{
	SetBackgroundColor(theApp.GetData().m_clrDisplayBack, FALSE);

	m_stHomeLabel.SetWindowText(theApp.GetData().m_strHomeLabel);
	m_stHomeLabel.SetTextClr(theApp.GetData().m_clrDisplayText);

	m_stGuestLabel.SetWindowText(theApp.GetData().m_strGuestLabel);
	m_stGuestLabel.SetTextClr(theApp.GetData().m_clrDisplayText);

	m_stSetsLabel.SetWindowText(theApp.GetData().m_strSetsLabel);
	m_stSetsLabel.SetTextClr(theApp.GetData().m_clrDisplayText);

	m_stTimeoutsLabel.SetWindowText(theApp.GetData().m_strTimeoutsLabel);
	m_stTimeoutsLabel.SetTextClr(theApp.GetData().m_clrDisplayText);

	m_dsHomeScore.SetBkColor(theApp.GetData().m_clrScoreBack);
	m_dsHomeScore.SetColor(theApp.GetData().m_clrScoreBack, theApp.GetData().m_clrScoreText);

	m_dsHomeSets.SetBkColor(theApp.GetData().m_clrSetsBack);
	m_dsHomeSets.SetColor(theApp.GetData().m_clrSetsBack, theApp.GetData().m_clrSetsText);

	m_dsGuestScore.SetBkColor(theApp.GetData().m_clrScoreBack);
	m_dsGuestScore.SetColor(theApp.GetData().m_clrScoreBack, theApp.GetData().m_clrScoreText);

	m_dsGuestSets.SetBkColor(theApp.GetData().m_clrSetsBack);
	m_dsGuestSets.SetColor(theApp.GetData().m_clrSetsBack, theApp.GetData().m_clrSetsText);

	m_stGuestTimeout1.SetTransparent(false);
	m_stGuestTimeout2.SetTransparent(false);
	m_stHomeTimeout1.SetTransparent(false);
	m_stHomeTimeout2.SetTransparent(false);

	UpdateFontSize();

	UpdateScore();

	Invalidate();
}

void CVSDisplayDlg::UpdateScore()
{
	UpdateHomeScore();
	UpdateGuestScore();
}

void CVSDisplayDlg::UpdateHomeScore()
{
	m_dsHomeScore.Format(_T("%02d"), theApp.GetData().m_nHomeScore);
	m_dsHomeSets.Format(_T("%d"), theApp.GetData().m_nHomeSets);

	m_stHomeTimeout1.SetBkClr(
		theApp.GetData().m_nHomeTimeouts > 0 ? theApp.GetData().m_clrTimeoutsText: theApp.GetData().m_clrTimeoutsBack
	);
	m_stHomeTimeout2.SetBkClr(
		theApp.GetData().m_nHomeTimeouts > 1 ? theApp.GetData().m_clrTimeoutsText : theApp.GetData().m_clrTimeoutsBack
	);

}

void CVSDisplayDlg::UpdateGuestScore()
{
	m_dsGuestScore.Format(_T("%02d"), theApp.GetData().m_nGuestScore);
	m_dsGuestSets.Format(_T("%d"), theApp.GetData().m_nGuestSets);

	m_stGuestTimeout1.SetBkClr(
		theApp.GetData().m_nGuestTimeouts > 0 ? theApp.GetData().m_clrTimeoutsText : theApp.GetData().m_clrTimeoutsBack
	);
	m_stGuestTimeout2.SetBkClr(
		theApp.GetData().m_nGuestTimeouts > 1 ? theApp.GetData().m_clrTimeoutsText : theApp.GetData().m_clrTimeoutsBack
	);

}

void CVSDisplayDlg::ToggleFullScreen()
{
	ShowFullScreen(!IsFullScreen());
}

BOOL CVSDisplayDlg::IsFullScreen()
{
	DWORD style = GetStyle();
	return (style & WS_CAPTION) == 0;
}

void CVSDisplayDlg::ShowFullScreen(BOOL bFullScreen)
{
	if (bFullScreen) {
		ShowWindow(SW_NORMAL);

		ModifyStyle(WS_MAXIMIZEBOX, 0);
		ModifyStyle(WS_MINIMIZEBOX, 0);
		ModifyStyle(WS_CAPTION, 0);

		ShowWindow(SW_SHOWMAXIMIZED);
	}
	else {
		ModifyStyle(0, WS_MAXIMIZEBOX);
		ModifyStyle(0, WS_MINIMIZEBOX);
		ModifyStyle(0, WS_CAPTION);

		ShowWindow(SW_NORMAL);
	}
}

BOOL CVSDisplayDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN) {
		const int wParam = pMsg->wParam;
		const int lParam = pMsg->lParam;
		const int keyboardScanCode = (lParam >> 16) & 0x00ff;
		const int virtualKey = wParam;
		const int repeatCount = (lParam & 0xffff);
		if (!m_bKeyDown) {
			m_bKeyDown = TRUE;
			m_bKeyDownManaged = FALSE;
		}

		switch (virtualKey) {
		case VK_F11:
			theApp.ToggleFullScreen();
			return TRUE;
			break;
		case VK_F2:
			theApp.ShowOptions();
			return TRUE;
			break;
		}
	}
	else if (pMsg->message == WM_KEYUP) {
		m_bKeyDown = FALSE;
		m_bKeyDownManaged = FALSE;
	}
	else if (pMsg->message == WM_CHAR) {
		const int wParam = pMsg->wParam;
		const int repeatCount = (pMsg->lParam & 0xffff);

		switch (wParam) {
		case _T('1'):
			if (!m_bKeyDownManaged)
				theApp.IncrementHomeScore(+1);
			m_bKeyDownManaged = TRUE;
			return TRUE;
			break;
		case _T('2'):
			if (!m_bKeyDownManaged)
				theApp.IncrementHomeScore(-1);
			m_bKeyDownManaged = TRUE;
			return TRUE;
			break;
		case _T('3'):
			if (!m_bKeyDownManaged)
				theApp.IncrementHomeSets(+1);
			m_bKeyDownManaged = TRUE;
			return TRUE;
			break;
		case _T('4'):
			if (!m_bKeyDownManaged)
				theApp.IncrementHomeSets(-1);
			m_bKeyDownManaged = TRUE;
			return TRUE;
			break;
		case _T('5'):
			if (!m_bKeyDownManaged)
				theApp.IncrementHomeTimeouts(1);
			m_bKeyDownManaged = TRUE;
			return TRUE;
			break;
		case _T('6'):
			if (!m_bKeyDownManaged)
				theApp.IncrementGuestTimeouts(1);
			m_bKeyDownManaged = TRUE;
			return TRUE;
			break;
		case _T('7'):
			if (!m_bKeyDownManaged)
				theApp.IncrementGuestSets(+1);
			m_bKeyDownManaged = TRUE;
			return TRUE;
			break;
		case _T('8'):
			if (!m_bKeyDownManaged)
				theApp.IncrementGuestSets(-1);
			m_bKeyDownManaged = TRUE;
			return TRUE;
			break;
		case _T('9'):
			if (!m_bKeyDownManaged)
				theApp.IncrementGuestScore(+1);
			m_bKeyDownManaged = TRUE;
			return TRUE;
			break;
		case _T('0'):
			if (!m_bKeyDownManaged)
				theApp.IncrementGuestScore(-1);
			m_bKeyDownManaged = TRUE;
			return TRUE;
			break;
		case _T('S'):
		case _T('s'):
			if (!m_bKeyDownManaged)
				theApp.NewSet();
			m_bKeyDownManaged = TRUE;
			return TRUE;
			break;
		case _T('M'):
		case _T('m'):
			if (!m_bKeyDownManaged)
				theApp.NewMatch();
			m_bKeyDownManaged = TRUE;
			return TRUE;
			break;
		}
	}

	
	return CDialogEx::PreTranslateMessage(pMsg);

}
