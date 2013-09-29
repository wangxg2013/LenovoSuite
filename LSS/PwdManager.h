#pragma once
#include "AppBox.h"
class CPwdManager :
	public CAppBox
{
public:
	BEGIN_MSG_MAP(CUsbBlocker)
		CHAIN_MSG_MAP(CAppBox)
	END_MSG_MAP()
public:
	CPwdManager()
	{
		m_pImagePwdManager = new Image(L"PwdManager.png");
	}
	virtual ~CPwdManager()
	{
		delete m_pImagePwdManager;
	}
protected:
	virtual void OnDrawImage(Graphics &g, const CRect &rc)
	{
		int nWidth = (int) (rc.Width() / 2.5f);
		int nHeight = m_pImagePwdManager->GetHeight() * nWidth / m_pImagePwdManager->GetWidth();


		g.DrawImage(m_pImagePwdManager, rc.left + (rc.Width() - nWidth) / 2, rc.top + (rc.Height() - nHeight) / 2, nWidth, nHeight);
	}
private:
	Image *m_pImagePwdManager;
};

