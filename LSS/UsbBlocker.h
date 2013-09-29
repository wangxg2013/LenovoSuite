#pragma once
#include "AppBox.h"
using namespace Gdiplus;

class CUsbBlocker :	public CAppBox
{
public:
	BEGIN_MSG_MAP(CUsbBlocker)
		CHAIN_MSG_MAP(CAppBox)
	END_MSG_MAP()
public:
	CUsbBlocker(){
		m_pImageUSB = new Image(L"USB.png");
	};
	virtual ~CUsbBlocker(){
		delete m_pImageUSB;
	};
protected:
	virtual void OnDrawImage(Graphics &g, const CRect &rc)
	{
		int nWidth = (int)(rc.Width() / 2.5f);
		int nHeight = m_pImageUSB->GetHeight() * nWidth/ m_pImageUSB->GetWidth();


		g.DrawImage(m_pImageUSB, rc.left + (rc.Width() - nWidth)/2, rc.top + (rc.Height() - nHeight)/2, nWidth, nHeight);
	}
private:
	Image *m_pImageUSB;
};

