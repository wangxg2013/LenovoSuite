#include "stdafx.h"
#include "AppBox.h"


CAppBox::CAppBox()
{
}


CAppBox::~CAppBox()
{
}

LRESULT CAppBox::OnEraseBkGnd(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	wchar_t wszBuf[128];
	::GetWindowText(m_hWnd, wszBuf, 128);

	RECT rcClient;
	GetClientRect(&rcClient);
	HDC hdc = GetDC();
	
	FillRect(hdc, &rcClient, (HBRUSH) GetStockObject(GRAY_BRUSH));

	// ::SelectObject(hdc, GetStockObject(BLACK_PEN));
	::TextOut(hdc, 0, 0, wszBuf, wcslen(wszBuf));

	// ReleaseDC(hdc);
	
	bHandled = TRUE;
	return 0;
}
