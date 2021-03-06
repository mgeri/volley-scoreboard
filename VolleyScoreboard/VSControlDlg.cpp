
// VSControlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VolleyScoreboard.h"
#include "VSControlDlg.h"
#include "VSAboutDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CVSControlDlg dialog
CVSControlDlg::CVSControlDlg(CWnd* pParent /*=NULL*/, UINT nIDD)
	: CVSDisplayDlg(pParent, nIDD)
{

}

void CVSControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CVSDisplayDlg::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVSControlDlg, CVSDisplayDlg)
	ON_BN_CLICKED(IDC_HOME_SCORE_PLUS_BTN, &CVSControlDlg::OnBnClickedHomeScorePlusBtn)
	ON_BN_CLICKED(IDC_HOME_SCORE_MINUS_BTN, &CVSControlDlg::OnBnClickedHomeScoreMinusBtn)
	ON_BN_CLICKED(IDC_NEWSET_BTN, &CVSControlDlg::OnBnClickedNewsetBtn)
	ON_BN_CLICKED(IDC_NEWMATCH_BTN, &CVSControlDlg::OnBnClickedNewmatchBtn)
	ON_BN_CLICKED(IDC_HOME_SETS_PLUS_BTN, &CVSControlDlg::OnBnClickedHomeSetsPlusBtn)
	ON_BN_CLICKED(IDC_HOME_SETS_MINUS_BTN, &CVSControlDlg::OnBnClickedHomeSetsMinusBtn)
	ON_BN_CLICKED(IDC_GUEST_SETS_PLUS_BTN, &CVSControlDlg::OnBnClickedGuestSetsPlusBtn)
	ON_BN_CLICKED(IDC_GUEST_SETS_MINUS_BTN, &CVSControlDlg::OnBnClickedGuestSetsMinusBtn)
	ON_BN_CLICKED(IDC_GUEST_SCORE_PLUS_BTN, &CVSControlDlg::OnBnClickedGuestScorePlusBtn)
	ON_BN_CLICKED(IDC_GUEST_SCORE_MINUS_BTN, &CVSControlDlg::OnBnClickedGuestScoreMinusBtn)
	ON_BN_CLICKED(IDC_OPTIONS_BTN, &CVSControlDlg::OnBnClickedOptionsBtn)
	ON_BN_CLICKED(IDC_FULLSCREEN_BTN, &CVSControlDlg::OnBnClickedFullscreenBtn)
	ON_BN_CLICKED(IDC_INFO_BTN, &CVSControlDlg::OnBnClickedInfoBtn)
	ON_BN_CLICKED(IDC_HOME_TIMEOUTS_BUTTON, &CVSControlDlg::OnBnClickedHomeTimeoutsButton)
	ON_BN_CLICKED(IDC_GUEST_TIMEOUTS_BUTTON, &CVSControlDlg::OnBnClickedGuestTimeoutsButton)
END_MESSAGE_MAP()


// CVolleyScoreboardDlg message handlers

BOOL CVSControlDlg::OnInitDialog()
{
	BOOL bRet = CVSDisplayDlg::OnInitDialog();


	return bRet;
}



void CVSControlDlg::OnBnClickedHomeScorePlusBtn()
{
	theApp.IncrementHomeScore(+1);
}


void CVSControlDlg::OnBnClickedHomeScoreMinusBtn()
{
	theApp.IncrementHomeScore(-1);
}


void CVSControlDlg::OnBnClickedHomeSetsPlusBtn()
{
	theApp.IncrementHomeSets(1);
}


void CVSControlDlg::OnBnClickedHomeSetsMinusBtn()
{
	theApp.IncrementHomeSets(-1);
}


void CVSControlDlg::OnBnClickedGuestSetsPlusBtn()
{
	theApp.IncrementGuestSets(1);
}

void CVSControlDlg::OnBnClickedGuestSetsMinusBtn()
{
	theApp.IncrementGuestSets(-1);
}


void CVSControlDlg::OnBnClickedGuestScorePlusBtn()
{
	theApp.IncrementGuestScore(1);
}


void CVSControlDlg::OnBnClickedGuestScoreMinusBtn()
{
	theApp.IncrementGuestScore(-1);
}


void CVSControlDlg::OnBnClickedNewsetBtn()
{
	theApp.NewSet();
}


void CVSControlDlg::OnBnClickedNewmatchBtn()
{
	theApp.NewMatch();
}



void CVSControlDlg::OnBnClickedOptionsBtn()
{
	theApp.ShowOptions();
}


void CVSControlDlg::OnBnClickedFullscreenBtn()
{
	theApp.ToggleFullScreen();
}


void CVSControlDlg::OnBnClickedInfoBtn()
{
	CVSAboutDlg dlgAbout;
	dlgAbout.DoModal();
}


void CVSControlDlg::OnBnClickedHomeTimeoutsButton()
{
	theApp.IncrementHomeTimeouts(1);
}


void CVSControlDlg::OnBnClickedGuestTimeoutsButton()
{
	theApp.IncrementGuestTimeouts(1);
}
