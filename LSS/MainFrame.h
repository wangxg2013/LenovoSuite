#pragma once

class CMainFrame : public CFrameWindowImpl<CMainFrame>
{
public:
	// DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)
	DECLARE_FRAME_WND_CLASS_EX(L"LenovoWindow", IDS_APP_TITLE, CS_DBLCLKS | CS_DROPSHADOW | CS_HREDRAW | CS_VREDRAW, COLOR_WINDOW)

	BEGIN_MSG_MAP(CMainFrame)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		CHAIN_MSG_MAP(CFrameWindowImpl<CMainFrame>)
	END_MSG_MAP()

public:


	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		return 0;
	}
};
