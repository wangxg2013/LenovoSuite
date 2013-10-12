#pragma once
using namespace Gdiplus;

class CSimpleCheck : public CWindowImpl<CSimpleCheck>
{
public:
	CSimpleCheck();
	virtual ~CSimpleCheck();

public:
	DECLARE_WND_CLASS(L"CSimpleCheck")

	BEGIN_MSG_MAP(CSimpleCheck)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	END_MSG_MAP()
protected:
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
private:
	bool m_bChecked;
	Pen *m_pPenBorder;
};

