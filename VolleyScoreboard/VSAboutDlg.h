
// VSAboutDlg.h : header file
//

#pragma once


// CVSAboutDlg dialog used for App About

class CVSAboutDlg : public CDialogEx
{
public:
	CVSAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

														// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};
