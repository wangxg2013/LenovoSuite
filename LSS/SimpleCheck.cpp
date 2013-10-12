#include "stdafx.h"
#include "SimpleCheck.h"


CSimpleCheck::CSimpleCheck()
{
	m_bChecked = false;
	m_pPenBorder = new Pen(Color(165, 165, 165));
}


CSimpleCheck::~CSimpleCheck()
{
	delete m_pPenBorder;
}

LRESULT CSimpleCheck::OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rcClient;
	GetClientRect(&rcClient);

	PAINTSTRUCT ps;
	BeginPaint(&ps);
	Graphics g(ps.hdc);

	g.DrawRectangle(m_pPenBorder, Rect(rcClient.left, rcClient.top, rcClient.Width()-1, rcClient.Height()-1));

	EndPaint(&ps);
	bHandled = true;
	return 0L;
}

LRESULT CSimpleCheck::OnLButtonUp(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = true;
	return 0L;
}