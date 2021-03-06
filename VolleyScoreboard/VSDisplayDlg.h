
// VSDisplayDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "Digistatic.h"
#include "HMXStatic.h"

// CVolleyScoreboardDlg dialog
class CVSDisplayDlg : public CDialogEx
{
// Construction
public:
	CVSDisplayDlg(CWnd* pParent = NULL, UINT nIDD = IDD_DISPLAY_DIALOG);	// standard constructor

// Dialog Data
	enum { IDD = IDD_DISPLAY_DIALOG };

	void UpdateSettings();
	void UpdateScore();
	void UpdateHomeScore();
	void UpdateGuestScore();

	void ToggleFullScreen();
	BOOL IsFullScreen();
	void ShowFullScreen(BOOL bFullScreen);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	virtual void OnOK();
	virtual void OnCancel();

protected:
	void UpdateFontSize();

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg); // to get keyboard shortcut

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor); 
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()

protected:
	BOOL m_bKeyDown;
	BOOL m_bKeyDownManaged;

public:
	CDigiStatic m_dsHomeScore;
	CDigiStatic m_dsGuestScore;
	CDigiStatic m_dsHomeSets;
	CDigiStatic m_dsGuestSets;
	CHMXStatic m_stHomeLabel;
	CHMXStatic m_stGuestLabel;
	CHMXStatic m_stSetsLabel;
	CHMXStatic m_stTimeoutsLabel;
	CHMXStatic m_stHomeTimeout1;
	CHMXStatic m_stHomeTimeout2;
	CHMXStatic m_stGuestTimeout1;
	CHMXStatic m_stGuestTimeout2;
};
