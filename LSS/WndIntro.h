#pragma once
#include "WndInfo.h"
#include "SimpleCheck.h"
using namespace Gdiplus;

class CWndIntro : public CWndInfo
{
public:
	BEGIN_MSG_MAP(CWndIntro)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		CHAIN_MSG_MAP(CWndInfo)
	END_MSG_MAP()
public:
	CWndIntro();
	virtual ~CWndIntro();

	inline void SetTitle(const CString& strTitle){ m_strTitle = strTitle; }
	inline void SetText(const CString& strText){ m_strText = strText; }
	inline void SetImage(const CString& strImageFile){ m_pImage = new Image(strImageFile); }

	virtual void OnInitUpdate();
protected:
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
private:
	Image *m_pImage;
	Gdiplus::Font *m_pFontTitle;
	CString m_strTitle;
	CString m_strText;
	CRect m_rcImage;

	CSimpleCheck m_check;
};

