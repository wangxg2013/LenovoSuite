#include "stdafx.h"
#include "WndInfo.h"


CWndInfo::CWndInfo()
{
	m_pBrushBk = new SolidBrush(Color(220, 220, 220));
}


CWndInfo::~CWndInfo()
{
	delete m_pBrushBk;
}

LRESULT CWndInfo::OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rcClient;
	GetClientRect(&rcClient);

	PAINTSTRUCT ps;
	BeginPaint(&ps);

	Graphics g(ps.hdc);

	g.FillRectangle(m_pBrushBk, Rect(0, 0, rcClient.Width(), rcClient.Height()));

	EndPaint(&ps);

	bHandled = TRUE;
	return 0L;
}