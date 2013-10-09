// LSS.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "LSS.h"
#include "MainFrame.h"

CAppModule g_appModule;
CAppConfig g_appConfig;

int Run(LPTSTR lpstrCmdLine = NULL, int nCmdShow = SW_SHOWDEFAULT);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);

	// Force Language to en-US or zh-CN
	SetProcessPreferredUILanguages(MUI_LANGUAGE_NAME, L"en-US\0\0", NULL);
	//SetProcessPreferredUILanguages(MUI_LANGUAGE_NAME, L"zh-CN\0\0", NULL);

	wchar_t wcsBuf[250];
	LoadString(hInstance, IDS_APP_TITLE, wcsBuf, 250);
	
	HRESULT hr = ::CoInitialize(NULL);
	ATLASSERT(SUCCEEDED(hr));

	g_appConfig.LoadConfig();

	GdiplusStartupInput gdiInput;
	ULONG_PTR gdiToken;
	Gdiplus::GdiplusStartup(&gdiToken, &gdiInput, NULL);

	::DefWindowProc(NULL, 0, 0, 0L);

	AtlInitCommonControls(ICC_COOL_CLASSES | ICC_BAR_CLASSES);

	hr = g_appModule.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hr));

	int nRet = Run(lpCmdLine, nCmdShow);

	Gdiplus::GdiplusShutdown(gdiToken);

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