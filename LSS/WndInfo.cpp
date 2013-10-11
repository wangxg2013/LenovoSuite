#include "stdafx.h"
#include "WndInfo.h"


CWndInfo::CWndInfo()
{
	m_iPosLineY = 0;
	m_pBrushBk = new SolidBrush(Color(220, 220, 220));

	m_pPenA = new Pen(Color(180, 180, 180), 1.0f);
	m_pPenB = new Pen(Color(240, 240, 240), 1.0f);

	m_pFont = new Font(&FontFamily(L"Î¢ÈíÑÅºÚ"), 9);
	m_pBrushText = new SolidBrush(Color(32, 32, 32));
}


CWndInfo::~CWndInfo()
{
	delete m_pBrushBk;
	delete m_pPenA;
	delete m_pPenB;
	delete m_pFont;
	delete m_pBrushText;
}

LRESULT CWndInfo::OnEraseBkGround(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rcClient;
	GetClientRect(&rcClient);

	HDC hdc = GetDC();
	Graphics g(hdc);
	
	g.FillRectangle(m_pBrushBk, Rect(0, 0, rcClient.Width(), rcClient.Height()));
	g.DrawLine(m_pPenA, Point(0, m_iPosLineY), Point(rcClient.right, m_iPosLineY));
	g.DrawLine(m_pPenB, Point(0, m_iPosLineY + 1), Point(rcClient.right, m_iPosLineY + 1));

	ReleaseDC(hdc);

	bHandled = TRUE;
	return 0L;
}

void CWndInfo::OnInitUpdate()
{
	const float fMainPercent = 0.85f;

	CRect rcClient;
	GetClientRect(&rcClient);

	m_iPosLineY = rcClient.top + (LONG)(rcClient.Height() * fMainPercent);
}