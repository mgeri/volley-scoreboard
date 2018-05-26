#include "stdafx.h"
#include "VSAppData.h"
#include "RgbColors.h"
#include "VSUtils.h"


static COLORREF THEMES[][8] = {
{ WHITE,	PURPLE,			RED,			BLACK,		ORANGE,			BLACK,		RED,	BLACK}, // PURPLE
{ WHITE,	RGB(66,66,66),	YELLOW,			BLACK,		RED,			BLACK,		RED,	BLACK}, // GRAY
{ WHITE,	RGB(0,132,0),	RGB(255,165,0),	BLACK,		YELLOW,			BLACK,		RGB(255,165,0),	BLACK, }, // GREEN
{ WHITE,	RGB(0,0,181),	RGB(255,165,0),	BLACK,		RGB(0,188,0),	BLACK,		RGB(255,165,0),	BLACK }, // BLUE
{ WHITE,	RGB(27,27,27),	RED,			BLACK,		YELLOW,			BLACK,		RED,			BLACK }, // DARK
};

CVSAppData::CVSAppData()
{
	ResetSettings(THEME_PURPLE);
	NewMatch();
}


CVSAppData::~CVSAppData()
{
}

//////////////////////////////////////////////////////////////////////////
// Settings
void CVSAppData::ResetSettings(ColorTheme theme)
{
	m_strHomeLabel = _T("LOCALI");
	m_strGuestLabel = _T("OSPITI");
	m_strSetsLabel = _T("SETS");
	m_strTimeoutsLabel = _T("TIMEOUT");

	m_clrDisplayText = THEMES[theme][0];
	m_clrDisplayBack = THEMES[theme][1];
	m_clrScoreText = THEMES[theme][2];
	m_clrScoreBack = THEMES[theme][3];
	m_clrSetsText = THEMES[theme][4];
	m_clrSetsBack = THEMES[theme][5];
	m_clrTimeoutsText = THEMES[theme][6];
	m_clrTimeoutsBack = THEMES[theme][7];

	m_bSavePosition = TRUE;
}

void CVSAppData::CopySettingsFrom(const CVSAppData& from)
{
	m_strHomeLabel = from.m_strHomeLabel;
	m_strGuestLabel = from.m_strGuestLabel;
	m_strSetsLabel = from.m_strSetsLabel;
	m_strTimeoutsLabel = from.m_strTimeoutsLabel;

	m_clrDisplayText = from.m_clrDisplayText;
	m_clrDisplayBack = from.m_clrDisplayBack;

	m_clrScoreText = from.m_clrScoreText;
	m_clrScoreBack = from.m_clrScoreBack;

	m_clrSetsText = from.m_clrSetsText;
	m_clrSetsBack = from.m_clrSetsBack;

	m_clrTimeoutsText = from.m_clrTimeoutsText;
	m_clrTimeoutsBack = from.m_clrTimeoutsBack;

	m_bSavePosition = from.m_bSavePosition;

}

//////////////////////////////////////////////////////////////////////////
// Score
void CVSAppData::NewMatch()
{
	m_nHomeSets = 0;
	m_nGuestSets = 0;
	m_nHomeScore = 0;
	m_nGuestScore = 0;
	m_nHomeTimeouts = 0;
	m_nGuestTimeouts = 0;
}

void CVSAppData::NewSet()
{
	if (m_nHomeScore > m_nGuestScore)
		m_nHomeSets++;

	if (m_nGuestScore > m_nHomeScore)
		m_nGuestSets++;

	m_nHomeScore = m_nGuestScore = 0;
	m_nHomeTimeouts = m_nGuestTimeouts = 0;
}


void CVSAppData::IncrementHomeScore(int points)
{
	m_nHomeScore += points;

	if (m_nHomeScore < 0) {
		m_nHomeScore = 0;
	} 
	if (m_nHomeScore > 99) {
		m_nHomeScore = 99;
	}
}

void CVSAppData::IncrementHomeSets(int sets)
{
	m_nHomeSets += sets;

	if (m_nHomeSets < 0) {
		m_nHomeSets = 0;
	}
	if (m_nHomeSets > 9) {
		m_nHomeSets = 9;
	}

}

void CVSAppData::IncrementHomeTimeouts(int timeouts)
{
	m_nHomeTimeouts = (m_nHomeTimeouts + timeouts) % 3;
}

void CVSAppData::IncrementGuestScore(int points)
{
	m_nGuestScore += points;

	if (m_nGuestScore < 0) {
		m_nGuestScore = 0;
	}
	if (m_nGuestScore > 99) {
		m_nGuestScore = 99;
	}

}

void CVSAppData::IncrementGuestSets(int sets)
{
	m_nGuestSets += sets;

	if (m_nGuestSets < 0) {
		m_nGuestSets = 0;
	}
	if (m_nGuestSets > 9) {
		m_nGuestSets = 9;
	}

}

void CVSAppData::IncrementGuestTimeouts(int timeouts)
{
	m_nGuestTimeouts = (m_nGuestTimeouts + timeouts) % 3;
}
