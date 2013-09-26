#pragma once
#pragma comment(lib, "Dwmapi")
#include <dwmapi.h>
#include "AppBox.h"

class CMainFrame : public CFrameWindowImpl<CMainFrame>
{
public:
	// DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)
	DECLARE_FRAME_WND_CLASS_EX(L"LenovoWindow", IDS_APP_TITLE, CS_DBLCLKS | CS_DROPSHADOW | CS_HREDRAW | CS_VREDRAW, COLOR_WINDOW)

	BEGIN_MSG_MAP(CMainFrame)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkGnd)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		CHAIN_MSG_MAP(CFrameWindowImpl<CMainFrame>)
	END_MSG_MAP()

public:
	CMainFrame()
	{
		m_nMargin = 5;
		m_nPadding = 5;
	}

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		BOOL bEnable = FALSE;
		::DwmIsCompositionEnabled(&bEnable);
		if (bEnable){
			m_brushBk = ::CreateSolidBrush(COLORREF(0));
		}
		else{
			m_brushBk = ::CreateSolidBrush(COLOR_WINDOW);
		}

		bHandled = TRUE;
		return 0;
	}

	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		::DeleteObject(m_brushBk);
		::PostQuitMessage(0);
		return 0;
	}

	void OnInitUpdate()
	{
		BOOL bEnable = FALSE;
		::DwmIsCompositionEnabled(&bEnable);
		if (bEnable){
			MARGINS margins;
			margins.cxLeftWidth = -1;
			margins.cxRightWidth = 0;
			margins.cyTopHeight = 0;
			margins.cyBottomHeight = 0;
			::DwmExtendFrameIntoClientArea(m_hWnd, &margins);
		}

		// create usb blocker appbox
		CRect rcUsbBlocker = CalcWndPosForUsbBlocker();
		m_appboxUsbBlocker.Create(m_hWnd, rcUsbBlocker, L"USB Blocker");

		// create one key recovery appbox
		CRect rcOKR = CalcWndPosForOneKeyRecovery();
		m_appboxOneKeyRecovery.Create(m_hWnd, rcOKR, L"OneKey Recovery");

		// create password manager appbox
		CRect rcPwdManager = CalcWndPosForPwdManager();
		m_appboxPwdManager.Create(m_hWnd, rcPwdManager, L"Password Manager");

		// create password manager appbox
		CRect rcAPS = CalcWndPosForAPS();
		m_appboxAPS.Create(m_hWnd, rcAPS, L"APS");
	}

	LRESULT OnEraseBkGnd(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		HDC hdc = GetDC();
		RECT rcClient;
		GetClientRect(&rcClient);
		FillRect(hdc, &rcClient, m_brushBk);

		ReleaseDC(hdc);

		bHandled = TRUE;
		return 0;
	}
private:
	HBRUSH m_brushBk;
	int m_nMargin;
	int m_nPadding;
	CAppBox m_appboxUsbBlocker;
	CAppBox m_appboxOneKeyRecovery;
	CAppBox m_appboxPwdManager;
	CAppBox m_appboxAPS;


	CRect CalcWndPosForUsbBlocker()
	{
		CRect rcWnd;
		rcWnd.left = m_nMargin + m_nPadding;
		rcWnd.top = m_nMargin + m_nPadding;

		CSize size = CalcAppBoxSize();
		rcWnd.right = rcWnd.left + size.cx;
		rcWnd.bottom = rcWnd.top + size.cy;

		return rcWnd;
	}

	CRect CalcWndPosForOneKeyRecovery()
	{
		RECT rcClient;
		GetClientRect(&rcClient);

		CRect rcWnd;
		rcWnd.right = rcClient.right - (m_nMargin + m_nPadding);
		rcWnd.top = m_nMargin + m_nPadding;

		CSize size = CalcAppBoxSize();
		rcWnd.left = rcWnd.right - size.cx;
		rcWnd.bottom = rcWnd.top + size.cy;

		return rcWnd;
	}

	CRect CalcWndPosForPwdManager()
	{
		RECT rcClient;
		GetClientRect(&rcClient);

		CRect rcWnd;
		rcWnd.left = m_nMargin + m_nPadding;
		rcWnd.bottom = rcClient.bottom - (m_nMargin + m_nPadding);

		CSize size = CalcAppBoxSize();
		rcWnd.right = rcWnd.left + size.cx;
		rcWnd.top = rcWnd.bottom - size.cy;

		return rcWnd;
	}

	CRect CalcWndPosForAPS()
	{
		RECT rcClient;
		GetClientRect(&rcClient);

		CRect rcWnd;
		rcWnd.right = rcClient.right - (m_nMargin + m_nPadding);
		rcWnd.bottom = rcClient.bottom - (m_nMargin + m_nPadding);

		CSize size = CalcAppBoxSize();
		rcWnd.left = rcWnd.right - size.cx;
		rcWnd.top = rcWnd.bottom - size.cy;

		return rcWnd;
	}

	CSize CalcAppBoxSize()
	{
		RECT rcClient;
		GetClientRect(&rcClient);

		CSize size;
		size.cx = ((rcClient.right - rcClient.left) - (m_nMargin * 2 + m_nPadding * 4)) / 2;
		size.cy = ((rcClient.bottom - rcClient.top) - (m_nMargin * 2 + m_nPadding * 4)) / 2;
		return size;
	}
};
