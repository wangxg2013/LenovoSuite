#pragma once
using namespace Gdiplus;

class CWndInfo : public CWindowImpl<CWndInfo>
{
public:
	DECLARE_WND_CLASS(L"CWndInfo")

	BEGIN_MSG_MAP(CWndInfo)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
	END_MSG_MAP()
public:
	CWndInfo();
	virtual ~CWndInfo();
protected:
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
private:
	Brush *m_pBrushBk;
};

