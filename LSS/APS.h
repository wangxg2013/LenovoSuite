#pragma once
#include "AppBox.h"
class CAPS :
	public CAppBox
{
public:
	BEGIN_MSG_MAP(CUsbBlocker)
		CHAIN_MSG_MAP(CAppBox)
	END_MSG_MAP()
public:
	CAPS()
	{
		m_pImageAPS = new Image(L"APS.png");
	}
	virtual ~CAPS()
	{
		delete m_pImageAPS;
	}
protected:
	virtual void OnDrawImage(Graphics &g, const CRect &rc)
	{
		int nWidth = (int) (rc.Width() / 2.5f);
		int nHeight = m_pImageAPS->GetHeight() * nWidth / m_pImageAPS->GetWidth();


		g.DrawImage(m_pImageAPS, rc.left + (rc.Width() - nWidth) / 2, rc.top + (rc.Height() - nHeight) / 2, nWidth, nHeight);
	}
private:
	Image *m_pImageAPS;
};

