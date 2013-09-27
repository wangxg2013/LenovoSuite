// LSS.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "LSS.h"
#include "MainFrame.h"

CAppModule g_appModule;

int Run(LPTSTR lpstrCmdLine = NULL, int nCmdShow = SW_SHOWDEFAULT);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);

	HRESULT hr = ::CoInitialize(NULL);
	ATLASSERT(SUCCEEDED(hr));

	::DefWindowProc(NULL, 0, 0, 0L);

	AtlInitCommonControls(ICC_COOL_CLASSES | ICC_BAR_CLASSES);

	hr = g_appModule.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hr));

	int nRet = Run(lpCmdLine, nCmdShow);

	g_appModule.Term();
	::CoUninitialize();

	return nRet;
}

int Run(LPTSTR lpstrCmdLine, int nCmdShow)
{
	CMessageLoop theLoop;
	g_appModule.AddMessageLoop(&theLoop);

	CMainFrame wndMain;
	// central the window
	CRect rcDisplay(0, 0, 0, 0);
	rcDisplay.right = ::GetSystemMetrics(SM_CXFULLSCREEN);
	rcDisplay.bottom = ::GetSystemMetrics(SM_CYFULLSCREEN);
	CRect rcMain = wndMain.CalcWindowPos(rcDisplay);

	if (wndMain.CreateEx(NULL, rcMain, WS_CLIPCHILDREN | WS_MINIMIZEBOX | WS_VISIBLE | WS_SYSMENU, 0) == NULL)
	{
		ATLTRACE(_T("Main window creation failed!\n"));
		return 0;
	}

	wndMain.ShowWindow(nCmdShow);
	wndMain.OnInitUpdate();

	int nRet = theLoop.Run();

	g_appModule.RemoveMessageLoop();
	return nRet;
}