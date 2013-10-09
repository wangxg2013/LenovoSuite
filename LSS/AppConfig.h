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
		_bstr_t bstrSupportAPS = spNode->attributes->getNamedItem(L"value")->text;
		if (bstrSupportAPS == _bstr_t(L"Yes")) m_bSupportAPS = true;
	}
	
	inline bool IsSupportAPS(){ return m_bSupportAPS; };
private:
	bool m_bSupportAPS;
};