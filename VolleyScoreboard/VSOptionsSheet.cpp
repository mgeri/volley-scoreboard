// VBSettingsSheet.cpp : implementation file
//

#include "stdafx.h"
#include "VolleyScoreboard.h"
#include "VSOptionsSheet.h"


// CVBOptionsSheet

IMPLEMENT_DYNAMIC(CVSOptionsSheet, CMFCPropertySheet)

CVSOptionsSheet::CVSOptionsSheet(const CVSAppData& appData):CMFCPropertySheet(_T("Volley Scoreboard Settings"))
{
	m_appData.CopySettingsFrom(appData);

	AddPage(&m_OptionsPage);
	// After the last AddPage() call:
	m_psh.dwFlags &= ~PSH_HASHELP;
	for (int i = 0; i < GetPageCount(); ++i)
		GetPage(i)->m_psp.dwFlags &= ~PSP_HASHELP;
}

CVSOptionsSheet::~CVSOptionsSheet()
{
}


BEGIN_MESSAGE_MAP(CVSOptionsSheet, CMFCPropertySheet)
END_MESSAGE_MAP()



// CVSSettingsSheet message handlers


