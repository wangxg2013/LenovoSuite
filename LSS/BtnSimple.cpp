#include "stdafx.h"
#include "BtnSimple.h"
using namespace Gdiplus;

CBtnSimple::CBtnSimple()
{
	m_pFont = new Font(&FontFamily(L"Î¢ÈíÑÅºÚ"), 9);
	m_pBrushText = new SolidBrush(Color(250, 250, 250));
	m_pBrushBk = new SolidBrush(Color(91, 155, 213));
	m_pBrushBk2 = new SolidBrush(Color(110, 175, 233));
}


CBtnSimple::~CBtnSimple()
{
	delete m_pBrushText;
	delete m_pBrushBk;
	delete m_pBrushBk2;
	delete m_pFont;
}

LRESULT CBtnSimple::OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rcClient;
	GetClientRect(&rcClient);

	RectF rcBound((REAL) rcClient.left, (REAL) rcClient.top, (REAL) rcClient.right, (REAL) rcClient.bottom);

	PAINTSTRUCT ps;
	BeginPaint(&ps);
	Graphics g(ps.hdc);
	
	g.FillRectangle(m_bHighLight ? m_pBrushBk2 : m_pBrushBk, 0, 0, rcClient.Width(), rcClient.Height());
	StringFormat format;
	format.SetAlignment(StringAlignment::StringAlignmentCenter);
	format.SetLineAlignment(StringAlignment::StringAlignmentCenter);
	g.DrawString(m_strText, m_strText.GetLength(), m_pFont, rcBound, &format, m_pBrushText);

	EndPaint(&ps);
	bHandled = TRUE;
	return 0L;
}

LRESULT CBtnSimple::OnMouseMove(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_bHighLight != true){
		m_bHighLight = true;
		Invalidate();

		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = m_hWnd;
		tme.dwHoverTime = HOVER_DEFAULT;
		TrackMouseEvent(&tme);
	}

	bHandled = true;
	return 0L;
}

LRESULT CBtnSimple::OnMouseLeave(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_bHighLight = false;

	this->Invalidate();

	bHandled = true;
	return 0L;
}

LRESULT CBtnSimple::OnLButtonUp(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = true;
	return 0L;
}