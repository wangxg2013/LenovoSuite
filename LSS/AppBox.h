#pragma once

class CAppBox : public CWindowImpl<CAppBox>
{
public:
	DECLARE_WND_CLASS(L"AppBox")

	BEGIN_MSG_MAP(CAppBox)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkGnd)
	END_MSG_MAP()
public:
	CAppBox();
	virtual ~CAppBox();
protected:
	LRESULT OnEraseBkGnd(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};

