#pragma once
#include "afxcolorbutton.h"
#include "afxwin.h"

class CVSOptionsSheet;
/////////////////////////////////////////////////////////////////////////////
// CVBOptionsPage dialog

class CVSOptionsPage : public CMFCPropertyPage
{
	DECLARE_DYNCREATE(CVSOptionsPage)

// Construction
public:
	CVSOptionsPage();
	~CVSOptionsPage();

// Dialog Data
	//{{AFX_DATA(CMyPropertyPage1)
	enum { IDD = IDD_OPTIONS_PAGE };
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CVBOptionsPage)
public:
	virtual BOOL OnApply();
	virtual void OnOK();
	virtual void OnCancel();

//	virtual BOOL OnSetActive();
protected:
	virtual BOOL OnInitDialog();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void UpdateSettings(BOOL bSave, BOOL bApply);

	// Generated message map functions
	//{{AFX_MSG(CVBOptionsPage)
	afx_msg void OnBnClickedResetButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CVSOptionsSheet* m_pSheet;
	CEdit m_edHomeLabel;
	CEdit m_edGuestLabel;
	CEdit m_edSetsLabel;
	CEdit m_edTimeoutsLabel;
	CMFCColorButton m_clDisplayBack;
	CMFCColorButton m_clDisplayText;
	CMFCColorButton m_clScoreBack;
	CMFCColorButton m_clScoreText;
	CMFCColorButton m_clSetsBack;
	CMFCColorButton m_clSetsText;
	CMFCColorButton m_clTimeoutsBack;
	CMFCColorButton m_clTimeoutsText;
	CButton m_ckSavePosition;
	CMFCMenuButton m_btResetToDefaults;
	CMenu m_mnReset;
};

