#pragma once

#include "VSOptionsPage.h"
#include "VSAppData.h"

// CVBSettingsSheet

class CVSOptionsSheet : public CMFCPropertySheet
{
	DECLARE_DYNAMIC(CVSOptionsSheet)

public:
	CVSOptionsSheet(const CVSAppData& appData);
	virtual ~CVSOptionsSheet();

protected:
	DECLARE_MESSAGE_MAP()

public:
	CVSOptionsPage	m_OptionsPage;
	CVSAppData m_appData;
};


