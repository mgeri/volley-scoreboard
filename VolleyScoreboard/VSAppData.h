// VSAppData.h : header file
//

#pragma once

class CVSAppData
{

public:
	CVSAppData();
	virtual ~CVSAppData();

	enum ColorTheme {
		THEME_PURPLE = 0,
		THEME_GRAY = 1,
		THEME_GREEN = 2,
		THEME_BLUE = 3,
		THEME_DARK = 4
	};

	void CopySettingsFrom(const CVSAppData& from);

	void ResetSettings(ColorTheme theme);

	void IncrementHomeScore(int points); // negative to decrement
	void IncrementHomeSets(int sets); // negative to decrement
	void IncrementHomeTimeouts(int timeouts); // negative to decrement
	void IncrementGuestScore(int points); // negative to decrement
	void IncrementGuestSets(int sets); // negative to decrement
	void IncrementGuestTimeouts(int timeouts); // negative to decrement


	void NewMatch();
	void NewSet();

public:
	// settings
	CString m_strHomeLabel;
	CString m_strGuestLabel;
	CString m_strSetsLabel;
	CString m_strTimeoutsLabel;

	COLORREF m_clrDisplayText;
	COLORREF m_clrDisplayBack;

	COLORREF m_clrScoreText;
	COLORREF m_clrScoreBack;

	COLORREF m_clrSetsText;
	COLORREF m_clrSetsBack;
		
	COLORREF m_clrTimeoutsText;
	COLORREF m_clrTimeoutsBack;

	LONG m_bSavePosition;
	
	// score info
	int m_nHomeSets;
	int m_nGuestSets;
	int m_nHomeScore;
	int m_nGuestScore;

	int m_nHomeTimeouts;
	int m_nGuestTimeouts;

};

