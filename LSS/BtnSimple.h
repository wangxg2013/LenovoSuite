#pragma once
using namespace Gdiplus;

class CBtnSimple : public CWindowImpl<CBtnSimple>
{
public:
	DECLARE_WND_CLASS(L"BtnSimple")

	BEGIN_MSG_MAP(CBtnSimple)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkground)
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	END_MSG_MAP()

public:
	CBtnSimple();
	virtual ~CBtnSimple();

	inline void SetText(const CString &strText){ m_strText = strText; }
protected:
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseLeave(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnEraseBkground(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	
private:
	Brush *m_pBrushBk;
	Brush *m_pBrushBk2;
	Brush *m_pBrushText;
	Gdiplus::Font *m_pFont;

	CString m_strText;
	bool m_bHighLight;
};

