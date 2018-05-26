#include "stdafx.h"
#include "VSUtils.h"

int CVSUtils::GetTextFitFontHeight(CWnd* pWnd, LPCTSTR strText /*= NULL*/)
{
	CRect rc;
	pWnd->GetClientRect(rc);

	CString strTmp;
	if (strText) {
		strTmp = strText;
	}
	else {
		pWnd->GetWindowText(strTmp);
	}

	CClientDC dc(pWnd);

	int fontHeight = rc.Height();

	CFont font;
	LOGFONT logfont{ 0 };

	pWnd->GetFont()->GetObject(sizeof(LOGFONT), (void*)&logfont);

	logfont.lfHeight = -MulDiv(fontHeight, GetDeviceCaps(dc.m_hDC, LOGPIXELSY), 72);
	font.CreateFontIndirect(&logfont);
	CFont * pOldFont = dc.SelectObject(&font);
	CSize sz = dc.GetTextExtent(strTmp);
	dc.SelectObject(pOldFont);

	int xHeight = fontHeight;
	int yHeight = fontHeight;

	if (sz.cx > rc.Width()) {
		double scale = (double)rc.Width() / (double)sz.cx;
		xHeight = (int)((scale)*(double)fontHeight);
	}

	if (sz.cy > rc.Height()) {
		double scale = (double)rc.Height() / (double)sz.cy;
		yHeight = (int)((scale)*(double)fontHeight);
	}

	return min(xHeight, yHeight);

}

void CVSUtils::ColorToString(COLORREF clr, CString& strColor)
{
	DWORD dwR = GetRValue(clr);
	DWORD dwG = GetGValue(clr);
	DWORD dwB = GetBValue(clr);
	strColor.Format(_T("#%02X%02X%02X"), dwR, dwG, dwB);
}

void CVSUtils::StringToColor(LPCTSTR strColor, COLORREF &clr)
{
	LPCTSTR pszTmp = strColor;
	pszTmp++; // cut the #

	LPTSTR pStop;
	LONG nTmp = _tcstol(pszTmp, &pStop, 16);
	LONG nR = (nTmp & 0xFF0000) >> 16;
	LONG nG = (nTmp & 0xFF00) >> 8;
	LONG nB = (nTmp & 0xFF);

	clr = RGB(nR, nG, nB);
}

void CVSUtils::LongToString(LONG v, CString& str)
{
	str.Format(_T("%ld"), v);
}

void CVSUtils::StringToLong(LPCTSTR str, LONG &v)
{
	LPTSTR pStop;
	v = _tcstol(str, &pStop, 10);
}


// Take coords, and shift them so all corners
// (if possible) appear on the nearest screen.
BOOL CVSUtils::EnsureRectangleOnDisplay(RECT *prc)
{
	HMONITOR hMonitor;
	MONITORINFO mi;
	memset(&mi, 0, sizeof(mi));
	mi.cbSize = sizeof(mi);

	if (!prc)
		return FALSE;

	hMonitor = MonitorFromRect(prc,	MONITOR_DEFAULTTONEAREST);
	if (hMonitor)
		GetMonitorInfo(hMonitor, &mi);

	// Now we have a clipping rectangle,
	// bring our input rectangle into sight.
	if (prc->right > mi.rcWork.right)
	{
		prc->left -= prc->right - mi.rcWork.right;
		prc->right = mi.rcWork.right;
	}
	if (prc->bottom > mi.rcWork.bottom)
	{
		prc->top -= prc->bottom - mi.rcWork.bottom;
		prc->bottom = mi.rcWork.bottom;
	}
	if (prc->left < mi.rcWork.left)
	{
		prc->right += mi.rcWork.left - prc->left;
		prc->left = mi.rcWork.left;
	}
	if (prc->top < mi.rcWork.top)
	{
		prc->bottom += mi.rcWork.top - prc->top;
		prc->top = mi.rcWork.top;
	}

	return TRUE;
}