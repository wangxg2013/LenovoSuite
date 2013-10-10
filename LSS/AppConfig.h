#pragma once
#pragma warning(disable:4192)
#import <msxml6.dll>
#pragma warning(default:4192)

class CAppConfig
{
public:
	CAppConfig()
	{
		m_bSupportAPS = false;
	}

	virtual ~CAppConfig(){}

	void LoadConfig()
	{
		MSXML2::IXMLDOMDocumentPtr spXmlDom;
		HRESULT hr = spXmlDom.CreateInstance(__uuidof(MSXML2::DOMDocument60), NULL, CLSCTX_INPROC_SERVER);
		spXmlDom->load(L"LSS.exe.config");

		// SupportAPS
		MSXML2::IXMLDOMNodePtr spNode = spXmlDom->selectSingleNode(L"//configuration/appSettings/add[@key='SupportAPS']");
		_bstr_t bstrBuf = spNode->attributes->getNamedItem(L"value")->text;
		if (bstrBuf == _bstr_t(L"Yes")) m_bSupportAPS = true;

		// Install_Reg_OKR
		spNode = spXmlDom->selectSingleNode(L"//configuration/appSettings/add[@key='Install_Reg_OKR']");
		bstrBuf = spNode->attributes->getNamedItem(L"value")->text;
		m_strInstallReg_OKR = (wchar_t*) bstrBuf;

		// Install_Reg_USBBlocker
		spNode = spXmlDom->selectSingleNode(L"//configuration/appSettings/add[@key='Install_Reg_USBBlocker']");
		bstrBuf = spNode->attributes->getNamedItem(L"value")->text;
		m_strInstallReg_USBBlocker = (wchar_t*) bstrBuf;

		// Install_Reg_PwdMgr
		spNode = spXmlDom->selectSingleNode(L"//configuration/appSettings/add[@key='Install_Reg_PwdMgr']");
		bstrBuf = spNode->attributes->getNamedItem(L"value")->text;
		m_strInstallReg_PwdMgr = (wchar_t*) bstrBuf;

		// Install_Reg_APS
		spNode = spXmlDom->selectSingleNode(L"//configuration/appSettings/add[@key='Install_Reg_APS']");
		bstrBuf = spNode->attributes->getNamedItem(L"value")->text;
		m_strInstallReg_APS = (wchar_t*) bstrBuf;

		// Run_OKR
		spNode = spXmlDom->selectSingleNode(L"//configuration/appSettings/add[@key='Run_OKR']");
		bstrBuf = spNode->attributes->getNamedItem(L"value")->text;
		m_strRunOKR = (wchar_t*) bstrBuf;

		// Run_USBBlocker
		spNode = spXmlDom->selectSingleNode(L"//configuration/appSettings/add[@key='Run_USBBlocker']");
		bstrBuf = spNode->attributes->getNamedItem(L"value")->text;
		m_strRunUSBBlocker = (wchar_t*) bstrBuf;

		// Run_PwdMgr
		spNode = spXmlDom->selectSingleNode(L"//configuration/appSettings/add[@key='Run_PwdMgr']");
		bstrBuf = spNode->attributes->getNamedItem(L"value")->text;
		m_strRunPwdMgr = (wchar_t*) bstrBuf;

		// Run_APS
		spNode = spXmlDom->selectSingleNode(L"//configuration/appSettings/add[@key='Run_APS']");
		bstrBuf = spNode->attributes->getNamedItem(L"value")->text;
		m_strRunAPS = (wchar_t*) bstrBuf;
	}
	
	inline bool IsSupportAPS(){ return m_bSupportAPS; };
	
	inline const CString& GetInstallRegOKR(){ return m_strInstallReg_OKR; }
	inline const CString& GetInstallRegPwdMgr(){ return m_strInstallReg_PwdMgr; }
	inline const CString& GetInstallRegUSBBlocker(){ return m_strInstallReg_USBBlocker; }
	inline const CString& GetInstallRegAPS(){ return m_strInstallReg_APS; }

	inline const CString& GetRunCmdOKR(){ return m_strRunOKR; }
	inline const CString& GetRunCmdPwdMgr(){ return m_strRunPwdMgr; }
	inline const CString& GetRunCmdUSBBlocker(){ return m_strRunUSBBlocker; }
	inline const CString& GetRunCmdAPS(){ return m_strRunAPS; }

private:
	bool m_bSupportAPS;
	CString m_strInstallReg_OKR;
	CString m_strInstallReg_PwdMgr;
	CString m_strInstallReg_USBBlocker;
	CString m_strInstallReg_APS;

	CString m_strRunOKR;
	CString m_strRunPwdMgr;
	CString m_strRunUSBBlocker;
	CString m_strRunAPS;
};