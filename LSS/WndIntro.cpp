#include "stdafx.h"
#include "WndIntro.h"

CWndIntro::CWndIntro()
{
	m_pImage = NULL;
	m_pFontTitle = new Font(&FontFamily(L"Î¢ÈíÑÅºÚ"), 18);
}


CWndIntro::~CWndIntro()
{
	delete m_pImage;
	delete m_pFontTitle;
}

LRESULT CWndIntro::OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rcClient;
	GetClientRect(&rcClient);

	PAINTSTRUCT ps;
	BeginPaint(&ps);

	Graphics g(ps.hdc);

	if (m_pImage != NULL){
		float fWidRatio = 0.25f;
		float fWidthImage = rcClient.Width() * fWidRatio;
		float fHeightImage = m_pImage->GetHeight() * fWidthImage / m_pImage->GetWidth();

		RectF rcImage;
		rcImage.X = (rcClient.Width() - fWidthImage) / 2.0f;
		rcImage.Y = rcClient.Height() / 2.0f - fHeightImage;
		rcImage.Width = fWidthImage;
		rcImage.Height = fHeightImage;

		g.DrawImage(m_pImage, rcImage);
	}

	RectF rcTitle;
	rcTitle.X = 0;
	rcTitle.Y = rcClient.Height() / 2.0f + 10.0f;
	rcTitle.Width = (REAL)rcClient.Width();
	rcTitle.Height = 32.0f;

	StringFormat format;
	format.SetAlignment(StringAlignment::StringAlignmentCenter);
	format.SetLineAlignment(StringAlignment::StringAlignmentCenter);
	g.DrawString(m_strTitle, m_strTitle.GetLength(), m_pFontTitle, rcTitle, &format, m_pBrushText);

	EndPaint(&ps);

	bHandled = TRUE;
	return 0L;
}