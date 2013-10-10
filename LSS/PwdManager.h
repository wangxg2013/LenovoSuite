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
	}

	virtual ~CPwdManager()
	{
	}
protected:
	virtual bool IsInstalled()
	{
		HKEY hKeyOKR = NULL;
		LSTATUS status = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, g_appConfig.GetInstallRegPwdMgr(), 0, KEY_READ, &hKeyOKR);
		if (status == ERROR_SUCCESS){
			::RegCloseKey(hKeyOKR);
			return true;
		}
		else{
			return false;
		}
	}
	
	virtual const CString& GetRunCmd()
	{
		return g_appConfig.GetRunCmdPwdMgr();
	}

	virtual void LoadStatusText()
	{
		// TODO: How to detect the status?
		wchar_t wszBuf[256];
		LoadString(g_appModule.m_hInst, IDS_ENABLED, wszBuf, 256);
		m_strStatus = wszBuf;
	}

	virtual void LoadLogo(bool bDisabledImage)
	{
		delete m_pImageLogo;
		m_pImageLogo = bDisabledImage ? new Image(L"PwdManager_disabled.png") : new Image(L"PwdManager.png");
	}
};

