
#include "stdafx.h"
#include "resource.h"
#include "VSOptionsPage.h"
#include "VSOptionsSheet.h"
#include "VolleyScoreboard.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define RESET_DEFAULT_PURPLE	10001
#define RESET_DEFAULT_GRAY		10002
#define RESET_DEFAULT_GREEN		10003
#define RESET_DEFAULT_BLUE		10004
#define RESET_DEFAULT_DARK		10005


IMPLEMENT_DYNCREATE(CVSOptionsPage, CMFCPropertyPage)

/////////////////////////////////////////////////////////////////////////////
// CVBOptionsPage property page

CVSOptionsPage::CVSOptionsPage() : CMFCPropertyPage(CVSOptionsPage::IDD)
{
	//{{AFX_DATA_INIT(CVBOptionsPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CVSOptionsPage::~CVSOptionsPage()
{
}

BOOL CVSOptionsPage::OnInitDialog()
{
	BOOL bRet = CMFCPropertyPage::OnInitDialog();

	m_mnReset.CreatePopupMenu();
	m_mnReset.AppendMenu(MF_ENABLED, RESET_DEFAULT_PURPLE, _T("Tema Viola"));
	m_mnReset.AppendMenu(MF_ENABLED, RESET_DEFAULT_GRAY, _T("Tema Grigio"));
	m_mnReset.AppendMenu(MF_ENABLED, RESET_DEFAULT_GREEN, _T("Tema Verde"));
	m_mnReset.AppendMenu(MF_ENABLED, RESET_DEFAULT_BLUE, _T("Tema Blu"));
	m_mnReset.AppendMenu(MF_ENABLED, RESET_DEFAULT_DARK, _T("Tema Scuro"));

	m_btResetToDefaults.m_hMenu = m_mnReset.GetSafeHmenu();

	m_pSheet = DYNAMIC_DOWNCAST(CVSOptionsSheet, GetParentSheet());
	
	UpdateSettings(FALSE, FALSE);

	return bRet;
}

void CVSOptionsPage::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVBOptionsPage)
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_HOME_TEXT_EDIT, m_edHomeLabel);
	DDX_Control(pDX, IDC_GUEST_TEXT_EDIT, m_edGuestLabel);
	DDX_Control(pDX, IDC_SETS_TEXT_EDIT, m_edSetsLabel);
	DDX_Control(pDX, IDC_TIMEOUTS_TEXT_EDIT, m_edTimeoutsLabel);
	DDX_Control(pDX, IDC_DISPLAY_BG_COLOR, m_clDisplayBack);
	DDX_Control(pDX, IDC_DISPLAY_FG_COlOR, m_clDisplayText);
	DDX_Control(pDX, IDC_SCORE_BG_COLOR, m_clScoreBack);
	DDX_Control(pDX, IDC_SCORE_FG_COLOR, m_clScoreText);
	DDX_Control(pDX, IDC_SETS_BG_COLOR, m_clSetsBack);
	DDX_Control(pDX, IDC_SETS_FG_COLOR, m_clSetsText);
	DDX_Control(pDX, IDC_TIMEOUTS_BG_COLOR, m_clTimeoutsBack);
	DDX_Control(pDX, IDC_TIMEOUTS_FG_COLOR, m_clTimeoutsText);
	DDX_Control(pDX, IDC_SAVEPOS_CHECK, m_ckSavePosition);
	DDX_Control(pDX, IDC_RESET_BUTTON, m_btResetToDefaults);
}


BEGIN_MESSAGE_MAP(CVSOptionsPage, CMFCPropertyPage)
	//{{AFX_MSG_MAP(CVBOptionsPage)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_RESET_BUTTON, &CVSOptionsPage::OnBnClickedResetButton)
END_MESSAGE_MAP()

void CVSOptionsPage::UpdateSettings(BOOL bSave, BOOL bApply)
{
	if (!m_pSheet) return;

	if (bSave) {
		m_edHomeLabel.GetWindowTextW(m_pSheet->m_appData.m_strHomeLabel);
		m_edGuestLabel.GetWindowTextW(m_pSheet->m_appData.m_strGuestLabel);
		m_edSetsLabel.GetWindowTextW(m_pSheet->m_appData.m_strSetsLabel);
		m_edTimeoutsLabel.GetWindowTextW(m_pSheet->m_appData.m_strTimeoutsLabel);

		m_pSheet->m_appData.m_clrDisplayBack =m_clDisplayBack.GetColor();
		m_pSheet->m_appData.m_clrDisplayText = m_clDisplayText.GetColor();

		m_pSheet->m_appData.m_clrScoreBack = m_clScoreBack.GetColor();
		m_pSheet->m_appData.m_clrScoreText= m_clScoreText.GetColor();

		m_pSheet->m_appData.m_clrSetsBack = m_clSetsBack.GetColor();
		m_pSheet->m_appData.m_clrSetsText = m_clSetsText.GetColor();

		m_pSheet->m_appData.m_clrTimeoutsBack = m_clTimeoutsBack.GetColor();
		m_pSheet->m_appData.m_clrTimeoutsText = m_clTimeoutsText.GetColor();

		m_pSheet->m_appData.m_bSavePosition = (m_ckSavePosition.GetCheck()!=0);

		if (bApply) 
			theApp.UpdateSettings(m_pSheet->m_appData);
		
	}
	else {
		m_edHomeLabel.SetWindowTextW(m_pSheet->m_appData.m_strHomeLabel);
		m_edGuestLabel.SetWindowTextW(m_pSheet->m_appData.m_strGuestLabel);
		m_edSetsLabel.SetWindowTextW(m_pSheet->m_appData.m_strSetsLabel);
		m_edTimeoutsLabel.SetWindowTextW(m_pSheet->m_appData.m_strTimeoutsLabel);

		m_clDisplayBack.SetColor(m_pSheet->m_appData.m_clrDisplayBack);
		m_clDisplayText.SetColor(m_pSheet->m_appData.m_clrDisplayText);

		m_clScoreBack.SetColor(m_pSheet->m_appData.m_clrScoreBack);
		m_clScoreText.SetColor(m_pSheet->m_appData.m_clrScoreText);

		m_clSetsBack.SetColor(m_pSheet->m_appData.m_clrSetsBack);
		m_clSetsText.SetColor(m_pSheet->m_appData.m_clrSetsText);

		m_clTimeoutsBack.SetColor(m_pSheet->m_appData.m_clrTimeoutsBack);
		m_clTimeoutsText.SetColor(m_pSheet->m_appData.m_clrTimeoutsText);

		m_ckSavePosition.SetCheck(m_pSheet->m_appData.m_bSavePosition ? 1 : 0);

	}

	if (m_pSheet->GetSafeHwnd() != NULL)
		m_pSheet->PostMessage(PSM_CHANGED, (WPARAM)m_hWnd);

}


BOOL CVSOptionsPage::OnApply()
{
	UpdateSettings(TRUE, TRUE);
	return TRUE;
}

void CVSOptionsPage::OnOK()
{
	UpdateSettings(TRUE, TRUE);
	CMFCPropertyPage::OnOK();	
}

void CVSOptionsPage::OnCancel()
{
	CMFCPropertyPage::OnCancel();
}

void CVSOptionsPage::OnBnClickedResetButton()
{
	if (!m_pSheet) return;

	CString str;
	switch (m_btResetToDefaults.m_nMenuResult)
	{
	case RESET_DEFAULT_PURPLE:
		m_pSheet->m_appData.ResetSettings(CVSAppData::THEME_PURPLE);
		break;
	case RESET_DEFAULT_GRAY:
		m_pSheet->m_appData.ResetSettings(CVSAppData::THEME_GRAY);
		break;
	case RESET_DEFAULT_GREEN:
		m_pSheet->m_appData.ResetSettings(CVSAppData::THEME_GREEN);
		break;
	case RESET_DEFAULT_BLUE:
		m_pSheet->m_appData.ResetSettings(CVSAppData::THEME_BLUE);
		break;
	case RESET_DEFAULT_DARK:
		m_pSheet->m_appData.ResetSettings(CVSAppData::THEME_DARK);
		break;
	}
	UpdateSettings(FALSE, FALSE);
}
