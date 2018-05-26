#pragma once

class CVSUtils
{
public:
	static int GetTextFitFontHeight(CWnd* pWnd, LPCTSTR strText = NULL);
	static void ColorToString(COLORREF clr, CString& strColor);
	static void StringToColor(LPCTSTR strColor, COLORREF &clr);
	static void LongToString(LONG v, CString& str);
	static void StringToLong(LPCTSTR str, LONG &v);
	static BOOL EnsureRectangleOnDisplay(RECT *prc);
};

class CImcLoadLib
{
public:
	HMODULE m_hModule;

	CImcLoadLib(LPCTSTR pModuleName)
	{
		m_hModule = LoadLibrary(pModuleName);
	}

	~CImcLoadLib()
	{
		if (m_hModule)
		{
			FreeLibrary(m_hModule);
			m_hModule = NULL;
		}
	}

	FARPROC GetProcAddress(LPCSTR lpProcName)
	{
		return ::GetProcAddress(m_hModule, lpProcName);
	}
};

