#pragma once

class CAppBox : public CWindowImpl<CAppBox>
{
public:
	DECLARE_WND_CLASS(L"AppBox")

	BEGIN_MSG_MAP(CAppBox)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkGnd)
	END_MSG_MAP()
public:
	CAppBox(){
		m_brBk.CreateSolidBrush(RGB(200, 200, 200));
		m_penLineA.CreatePen(PS_SOLID, 1, RGB(180, 180, 180));
		m_penLineB.CreatePen(PS_SOLID, 1, RGB(212, 212, 212));
	}
	virtual ~CAppBox(){}

protected:
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		wchar_t wszBuf[128];
		::GetWindowText(m_hWnd, wszBuf, 128);

		PAINTSTRUCT ps;
		BeginPaint(&ps);
		::TextOut(ps.hdc, 0, 0, wszBuf, (int) wcslen(wszBuf));
		EndPaint(&ps);

		bHandled = true;
		return 0L;
	}

	LRESULT OnEraseBkGnd(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CRect rcClient;
		GetClientRect(&rcClient);
		int y = rcClient.bottom - rcClient.Height() / 5;

	
		HDC hdc = GetDC();
		HGDIOBJ hOldPen = SelectObject(hdc, GetStockObject(NULL_PEN));
		HGDIOBJ hOldBrush = SelectObject(hdc, m_brBk);
		RoundRect(hdc, rcClient.left, rcClient.top, rcClient.right, rcClient.bottom, 8, 8);
		SelectObject(hdc, hOldBrush);
		SelectObject(hdc, hOldPen);

		hOldPen = SelectObject(hdc, m_penLineA);
		MoveToEx(hdc, 0, y, NULL);
		LineTo(hdc, rcClient.right - 1, y);
		SelectObject(hdc, m_penLineB);
		MoveToEx(hdc, 0, y+1, NULL);
		LineTo(hdc, rcClient.right - 1, y+1);
		SelectObject(hdc, hOldPen);

		ReleaseDC(hdc);

		bHandled = true;
		return 0;
	}
private:
	CBrush m_brBk;
	CPen m_penLineA;
	CPen m_penLineB;
};

