#pragma once
#include "AppBox.h"
class COneKeyRecovery :
	public CAppBox
{
public:
	BEGIN_MSG_MAP(CUsbBlocker)
		CHAIN_MSG_MAP(CAppBox)
	END_MSG_MAP()
public:
	COneKeyRecovery()
	{
		m_pImageOKR = new Image(L"OKR.png");
	}
	virtual ~COneKeyRecovery()
	{
		delete m_pImageOKR;
	}
protected:
	virtual void OnDrawImage(Graphics &g, const CRect &rc)
	{
		int nWidth = (int) (rc.Width() / 2.5f);
		int nHeight = m_pImageOKR->GetHeight() * nWidth / m_pImageOKR->GetWidth();


		g.DrawImage(m_pImageOKR, rc.left + (rc.Width() - nWidth) / 2, rc.top + (rc.Height() - nHeight) / 2, nWidth, nHeight);
	}
private:
		Image *m_pImageOKR;
};

