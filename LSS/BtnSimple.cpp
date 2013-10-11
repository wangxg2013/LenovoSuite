#include "stdafx.h"
#include "BtnSimple.h"
using namespace Gdiplus;

CBtnSimple::CBtnSimple()
{
	m_pFont = new Font(&FontFamily(L"Œ¢»Ì—≈∫⁄"), 9);
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
	
	//g.FillRectangle(m_bHighLight ? m_pBrushBk2 : m_pBrushBk, 0, 0, rcClient.Width(), rcClient.Height());
	float r=0.5f;
	PointF point1((REAL)0.0, (REAL)10.000*r);
	PointF point2((REAL)5.000f*r, (REAL)8.660*r);
	PointF point3((REAL)7.070f*r, (REAL)7.070*r);
	PointF point4((REAL)8.660f*r, (REAL)5.000*r);
	PointF point5((REAL)10.000f*r, (REAL)0*r);
	PointF point6((REAL)0.0, (REAL)0.0);	

	PointF points[6] = {point1, point2, point3, point4,point5, point6};

	PointF pointsX[6];
	//◊Û…œ‘≤ª°
	for (int i = 0; i < 6; i++)
	{
		pointsX[i].X=10*r-points[i].X;
		pointsX[i].Y=10*r-points[i].Y;
	}
	g.FillClosedCurve(m_bHighLight ? m_pBrushBk2 : m_pBrushBk ,pointsX,6);
	

	//”“…œ‘≤ª°
	for (int i = 0; i < 6; i++)
	{
		pointsX[i].X=points[i].X+rcClient.Width()-10*r;
		pointsX[i].Y=10*r-points[i].Y;
	}
	g.FillClosedCurve(m_bHighLight ? m_pBrushBk2 : m_pBrushBk ,pointsX,6);

	//◊Ûœ¬‘≤ª°
	for (int i = 0; i < 6; i++)
	{
		pointsX[i].X=10*r-points[i].X;
		pointsX[i].Y=points[i].Y+rcClient.Height()-10*r;
	}
	g.FillClosedCurve(m_bHighLight ? m_pBrushBk2 : m_pBrushBk ,pointsX,6);

	//”“œ¬‘≤ª°
	for (int i = 0; i < 6; i++)
	{
		pointsX[i].X=points[i].X+rcClient.Width()-10*r;
		pointsX[i].Y=points[i].Y+rcClient.Height()-10*r;
	}
	g.FillClosedCurve(m_bHighLight ? m_pBrushBk2 : m_pBrushBk ,pointsX,6);

	g.FillRectangle(m_bHighLight ? m_pBrushBk2 : m_pBrushBk,10*r, 0.0, rcClient.Width()-20*r, 10*r);
	g.FillRectangle(m_bHighLight ? m_pBrushBk2 : m_pBrushBk,(REAL)0, 10*r, (REAL)rcClient.Width(), rcClient.Height()-20*r);
	g.FillRectangle(m_bHighLight ? m_pBrushBk2 : m_pBrushBk,10*r, rcClient.Height()-10*r, rcClient.Width()-20*r, 10*r);



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

LRESULT CBtnSimple::OnEraseBkground(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = TRUE;
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