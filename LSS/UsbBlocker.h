#pragma once
#include "AppBox.h"
using namespace Gdiplus;

class CUsbBlocker :	public CAppBox
{
public:
	BEGIN_MSG_MAP(CUsbBlocker)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp);
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
	LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		WinExec("calc.exe", SW_SHOW);
		bHandled = true;
		return 0L;
	}

	virtual void OnDrawImage(Graphics &g, const CRect &rc)
	{
		int nWidth = (int)(rc.Width() / 2.5f);
		int nHeight = m_pImageUSB->GetHeight() * nWidth/ m_pImageUSB->GetWidth();


		g.DrawImage(m_pImageUSB, rc.left + (rc.Width() - nWidth)/2, rc.top + (rc.Height() - nHeight)/2, nWidth, nHeight);
	}
	
	virtual bool IsInstalled()
	{
		HKEY hKeyOKR = NULL;
		LSTATUS status = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, g_appConfig.GetInstallRegUSBBlocker(), 0, KEY_READ, &hKeyOKR);
		if (status == ERROR_SUCCESS){
			::RegCloseKey(hKeyOKR);
			return true;
		}
		else{
			return false;
		}
	}
private:
	Image *m_pImageUSB;
};

