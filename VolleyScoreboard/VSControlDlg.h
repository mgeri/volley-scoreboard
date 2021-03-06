
// VSControlDlg.h : header file
//

#pragma once

#include "VSDisplayDlg.h"

// CVSControlDlg dialog
class CVSControlDlg : public CVSDisplayDlg
{
// Construction
public:
	CVSControlDlg(CWnd* pParent = NULL, UINT nIDD = IDD_CONTROL_DIALOG);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CONTROL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedHomeScorePlusBtn();
	afx_msg void OnBnClickedHomeScoreMinusBtn();
	afx_msg void OnBnClickedNewsetBtn();
	afx_msg void OnBnClickedNewmatchBtn();
	afx_msg void OnBnClickedHomeSetsPlusBtn();
	afx_msg void OnBnClickedHomeSetsMinusBtn();
	afx_msg void OnBnClickedGuestSetsPlusBtn();
	afx_msg void OnBnClickedGuestSetsMinusBtn();
	afx_msg void OnBnClickedGuestScorePlusBtn();
	afx_msg void OnBnClickedGuestScoreMinusBtn();
	afx_msg void OnBnClickedOptionsBtn();
	afx_msg void OnBnClickedFullscreenBtn();
	afx_msg void OnBnClickedInfoBtn();
	afx_msg void OnBnClickedHomeTimeoutsButton();
	afx_msg void OnBnClickedGuestTimeoutsButton();
};
