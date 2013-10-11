#pragma once
#pragma comment(lib, "Dwmapi")
#include <dwmapi.h>
#include "resource.h"
#include "LSS.h"
#include "AppBox.h"
#include "UsbBlocker.h"
#include "OneKeyRecovery.h"
#include "PwdManager.h"
#include "APS.h"
#include "IShowInfo.h"
#include "WndIntro.h"

class CMainFrame : public CFrameWindowImpl<CMainFrame>,
	public IShowInfo
{
public:
	// DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)
	DECLARE_FRAME_WND_CLASS_EX(L"LenovoWindow", IDS_APP_TITLE, CS_HREDRAW | CS_VREDRAW, COLOR_WINDOW)

	BEGIN_MSG_MAP(CMainFrame)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkGnd)
		//MESSAGE_HANDLER(WM_NCPAINT, OnNcPaint)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		CHAIN_MSG_MAP(CFrameWindowImpl<CMainFrame>)
	END_MSG_MAP()

public:
	CMainFrame()
	{
		m_nMargin = 5;
		m_nPadding = 5;

		m_pUsbBlocker = NULL;
		m_pOneKeyRecovery = NULL;
		m_pPwdManager = NULL;
		m_pAPS = NULL;
	}

	virtual ~CMainFrame()
	{
		if (m_pUsbBlocker != NULL) delete m_pUsbBlocker;
		if (m_pOneKeyRecovery != NULL) delete m_pOneKeyRecovery;
		if (m_pPwdManager != NULL) delete m_pPwdManager;
		if (m_pAPS != NULL) delete m_pAPS;
	}

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		BOOL bEnable = FALSE;
		// ::DwmIsCompositionEnabled(&bEnable);
		if (bEnable){
			m_brushBk = ::CreateSolidBrush(COLORREF(0));
		}
		else{
			m_brushBk = ::CreateSolidBrush(RGB(220, 220, 220));
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

	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		if (m_wndIntro.m_hWnd != NULL){
			m_wndIntro.DestroyWindow();
		}
		else{
			DestroyWindow();
		}
		return 0;
	}

	void OnInitUpdate()
	{
		/*BOOL bEnable = FALSE;
		::DwmIsCompositionEnabled(&bEnable);
		if (bEnable){
		MARGINS margins;
		margins.cxLeftWidth = -1;
		margins.cxRightWidth = 0;
		margins.cyTopHeight = 0;
		margins.cyBottomHeight = 0;
		::DwmExtendFrameIntoClientArea(m_hWnd, &margins);
		}*/

		wchar_t wszBoxName[128];
		auto size = CalcAppBoxSize();
		int yLinePos = - size.cy / 5;

		// create usb blocker appbox
		CRect rcUsbBlocker = CalcWndPosForUsbBlocker();
		m_pUsbBlocker = new CUsbBlocker();
		LoadString(g_appModule.m_hInst, IDS_USB_BLOCKER, wszBoxName, 120);
		m_pUsbBlocker->SetYLinePos(yLinePos);
		m_pUsbBlocker->SetShowInfo(this);
		m_pUsbBlocker->Create(m_hWnd, rcUsbBlocker, wszBoxName);
		m_pUsbBlocker->OnInitUpdate();

		// create one key recovery appbox
		CRect rcOKR = CalcWndPosForOneKeyRecovery();
		m_pOneKeyRecovery = new COneKeyRecovery();
		LoadString(g_appModule.m_hInst, IDS_OKR, wszBoxName, 120);
		m_pOneKeyRecovery->SetYLinePos(yLinePos);
		m_pOneKeyRecovery->SetShowInfo(this);
		m_pOneKeyRecovery->Create(m_hWnd, rcOKR, wszBoxName);
		m_pOneKeyRecovery->OnInitUpdate();

		// create password manager appbox
		CRect rcPwdManager = CalcWndPosForPwdManager();
		m_pPwdManager = new CPwdManager();
		LoadString(g_appModule.m_hInst, IDS_PWD_MGR, wszBoxName, 120);
		m_pPwdManager->SetYLinePos(yLinePos);
		m_pPwdManager->SetShowInfo(this);
		m_pPwdManager->Create(m_hWnd, rcPwdManager, wszBoxName);
		m_pPwdManager->OnInitUpdate();

		// create password manager appbox
		if (g_appConfig.IsSupportAPS())
		{
			CRect rcAPS = CalcWndPosForAPS();
			m_pAPS = new CAPS();
			LoadString(g_appModule.m_hInst, IDS_APS, wszBoxName, 120);
			m_pAPS->SetYLinePos(yLinePos);
			m_pAPS->SetShowInfo(this);
			m_pAPS->Create(m_hWnd, rcAPS, wszBoxName);
			m_pAPS->OnInitUpdate();
		}
	}

	CRect CalcWindowPos(CRect &rcDisplay)
	{
		int nWidth = (int) (rcDisplay.Width() / 2.5f);
		int nHeight = (int) (nWidth * 0.9f);
		int nPosX = (rcDisplay.Width() - nWidth) / 2;
		int nPosY = (rcDisplay.Height() - nHeight) / 2;
		WTL::CRect rcMain(nPosX, nPosY, nPosX + nWidth, nPosY + nHeight);

		return rcMain;
	}

	virtual bool ShowInfo(HWND hWndSource)
	{
		ATLASSERT(m_wndIntro.m_hWnd == NULL);
		const int nLen = 512;
		wchar_t wszBuf[nLen];

		if (m_pUsbBlocker != NULL && m_pUsbBlocker->m_hWnd == hWndSource){
			m_wndIntro.SetImage(L"USB.png");
			LoadString(g_appModule.m_hInst, IDS_USB_BLOCKER, wszBuf, nLen-1);			
		}
		else if (m_pOneKeyRecovery != NULL && m_pOneKeyRecovery->m_hWnd == hWndSource){
			m_wndIntro.SetImage(L"OKR.png");
			LoadString(g_appModule.m_hInst, IDS_OKR, wszBuf, nLen - 1);
		}
		else if (m_pPwdManager != NULL && m_pPwdManager->m_hWnd == hWndSource){
			m_wndIntro.SetImage(L"PwdManager.png");
			LoadString(g_appModule.m_hInst, IDS_PWD_MGR, wszBuf, nLen - 1);
		}
		else if (m_pAPS != NULL && m_pAPS->m_hWnd == hWndSource){
			m_wndIntro.SetImage(L"APS.png");
			LoadString(g_appModule.m_hInst, IDS_APS, wszBuf, nLen - 1);
		}
		else{
			return false;
		}

		m_wndIntro.SetTitle(wszBuf);

		CRect rcClient;
		GetClientRect(&rcClient);
		m_wndIntro.Create(m_hWnd, &rcClient);
		m_wndIntro.OnInitUpdate();
		m_wndIntro.SetWindowPos(HWND_TOP, rcClient, SWP_NOMOVE | SWP_NOSIZE);
		m_wndIntro.ShowWindow(SW_SHOW);
		return true;
	}

protected:
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

	LRESULT OnNcPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = TRUE;
		return 1L;
	}

private:
	HBRUSH m_brushBk;
	int m_nMargin;
	int m_nPadding;
	CUsbBlocker *m_pUsbBlocker;
	COneKeyRecovery *m_pOneKeyRecovery;
	CPwdManager *m_pPwdManager;
	CAPS *m_pAPS;
	CWndIntro m_wndIntro;

	CRect CalcWndPosForUsbBlocker()
	{
		CRect rcWnd;
		rcWnd.left = m_nMargin + m_nPadding;
		rcWnd.top = m_nMargin + m_nPadding;

		CSize size = CalcAppBoxSize();
		rcWnd.right = rcWnd.left + size.cx;
		if (g_appConfig.IsSupportAPS()){
			rcWnd.bottom = rcWnd.top + size.cy;
		}
		else{
			RECT rcClient;
			GetClientRect(&rcClient);
			rcWnd.bottom = rcClient.bottom - (m_nMargin + m_nPadding);
		}

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
		CSize size = CalcAppBoxSize();
		if (g_appConfig.IsSupportAPS()){
			rcWnd.left = m_nMargin + m_nPadding;
			rcWnd.bottom = rcClient.bottom - (m_nMargin + m_nPadding);
			
			rcWnd.right = rcWnd.left + size.cx;
			rcWnd.top = rcWnd.bottom - size.cy;
		}
		else{
			rcWnd.right = rcClient.right - (m_nMargin + m_nPadding);
			rcWnd.bottom = rcClient.bottom - (m_nMargin + m_nPadding);

			rcWnd.left = rcWnd.right - size.cx;
			rcWnd.top = rcWnd.bottom - size.cy;
		}

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
