#pragma once
using namespace Gdiplus;

class CWndInfo : public CWindowImpl<CWndInfo>
{
public:
	DECLARE_WND_CLASS(L"CWndInfo")

	BEGIN_MSG_MAP(CWndInfo)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkGround)
	END_MSG_MAP()
public:
	CWndInfo();
	virtual ~CWndInfo();

	virtual void OnInitUpdate();
protected:
	int m_iPosLineY;
	Gdiplus::Font *m_pFont;
	Brush *m_pBrushText;

	LRESULT OnEraseBkGround(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

private:
	Brush *m_pBrushBk;
	Pen *m_pPenA;
	Pen *m_pPenB;
};

