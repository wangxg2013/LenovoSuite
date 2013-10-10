#pragma once
#include "resource.h"
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
	CUsbBlocker()
	{
	}

	virtual ~CUsbBlocker()
	{
	}
protected:
	LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		WinExec("calc.exe", SW_SHOW);
		bHandled = true;
		return 0L;
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

	virtual void LoadStatusText()
	{
		// TODO: How to detect the USB Blocker's status?
		wchar_t wszBuf[256];
		LoadString(g_appModule.m_hInst, IDS_UNCONFIG, wszBuf, 256);
		m_strStatus = wszBuf;
	}

	virtual void LoadLogo(bool bDisabledImage)
	{
		delete m_pImageLogo;
		m_pImageLogo = bDisabledImage ? new Image(L"USB_disabled.png") : new Image(L"USB.png");
	}
};

