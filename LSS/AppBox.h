#pragma once
#include "LSS.h"
using namespace Gdiplus;

class CAppBox : public CWindowImpl<CAppBox>
{
public:
	DECLARE_WND_CLASS(L"AppBox")

	BEGIN_MSG_MAP(CAppBox)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkGnd)
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	END_MSG_MAP()
public:
	CAppBox(){
		m_colorText = RGB(0xf7, 0x7a, 0x00);
		m_colorText2 = RGB(255, 255, 255);
		m_brBk.CreateSolidBrush(RGB(200, 200, 200));
		m_brBk2.CreateSolidBrush(m_colorText);
		m_bHighLight = false;

		m_colorTitle = RGB(80, 80, 80);

		m_penLineA.CreatePen(PS_SOLID, 1, RGB(180, 180, 180));
		m_penLineB.CreatePen(PS_SOLID, 1, RGB(212, 212, 212));
		m_fontMsBlack.CreateFont(20, 0, 0, 0, FW_NORMAL, 0, 0, 0,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
			L"Î¢ÈíÑÅºÚ");
	}

	virtual ~CAppBox()
	{
		delete m_pImageLogo;
	}

	void SetYLinePos(int y){ m_nYLinePos = y; }

	virtual void OnInitUpdate()
	{
		UpdateStatus(true);
	}
protected:
	CString m_strStatus;
	Image *m_pImageLogo = NULL;

	LRESULT OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CRect rcClient;
		GetClientRect(&rcClient);

		int x = 8;
		int y = rcClient.bottom + m_nYLinePos;

		wchar_t wszBuf[128];
		::GetWindowText(m_hWnd, wszBuf, 128);

		PAINTSTRUCT ps;
		BeginPaint(&ps);
		Graphics graphics(ps.hdc);

		::SetBkMode(ps.hdc, TRANSPARENT);
		HGDIOBJ hFontOld = SelectObject(ps.hdc, m_fontMsBlack);

		COLORREF colorOld = GetTextColor(ps.hdc);
		::SetTextColor(ps.hdc, m_bHighLight ? m_colorText2 : m_colorTitle);
		::DrawText(ps.hdc, wszBuf, (int) wcslen(wszBuf), CRect(x, y, rcClient.right, rcClient.bottom), DT_VCENTER | DT_SINGLELINE);

		SetTextColor(ps.hdc, m_bHighLight ? m_colorText2 : m_colorText);
		::DrawText(ps.hdc, m_strStatus, m_strStatus.GetLength(), CRect(0, 4, rcClient.right - 8, rcClient.bottom), DT_RIGHT | DT_SINGLELINE);
		SelectObject(ps.hdc, hFontOld);
		SetTextColor(ps.hdc, colorOld);

		TEXTMETRIC tm;
		::GetTextMetrics(ps.hdc, &tm);

		CRect rcBound;
		rcBound.left = 0;
		rcBound.top = tm.tmHeight;
		rcBound.right = rcClient.right;
		rcBound.bottom = y;

		OnDrawImage(graphics, rcBound);

		EndPaint(&ps);

		bHandled = true;
		return 0L;
	}

	LRESULT OnEraseBkGnd(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CRect rcClient;
		GetClientRect(&rcClient);
		int y = rcClient.bottom + m_nYLinePos;


		HDC hdc = GetDC();
		HGDIOBJ hOldPen = SelectObject(hdc, GetStockObject(NULL_PEN));
		HGDIOBJ hOldBrush = SelectObject(hdc, m_bHighLight ? m_brBk2 : m_brBk);
		RoundRect(hdc, rcClient.left, rcClient.top, rcClient.right, rcClient.bottom, 8, 8);
		SelectObject(hdc, hOldBrush);
		SelectObject(hdc, hOldPen);

		hOldPen = SelectObject(hdc, m_penLineA);
		MoveToEx(hdc, 0, y, NULL);
		LineTo(hdc, rcClient.right - 1, y);
		SelectObject(hdc, m_penLineB);
		MoveToEx(hdc, 0, y + 1, NULL);
		LineTo(hdc, rcClient.right - 1, y + 1);
		SelectObject(hdc, hOldPen);

		ReleaseDC(hdc);

		bHandled = true;
		return 0L;
	}

	LRESULT OnMouseLeave(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_bHighLight = false;

		this->Invalidate();

		bHandled = true;
		return 0L;
	}

	LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if (m_bHighLight != true){
			m_bHighLight = true;
			Invalidate();

			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.dwFlags = TME_LEAVE;
			tme.hwndTrack = m_hWnd;
			tme.dwHoverTime = HOVER_DEFAULT;
			TrackMouseEvent(&tme);
		}

		bHandled = true;
		return 0L;
	}

	LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		WinExec("Notepad.exe", SW_SHOW);
		bHandled = true;
		return 0L;
	}

	virtual bool IsInstalled() = 0;
	virtual void LoadStatusText() = 0;
	virtual void LoadLogo(bool bDisabledImage) = 0;
private:
	bool m_bInstalled = false;
	COLORREF m_colorText;
	COLORREF m_colorText2;
	COLORREF m_colorTitle;

	CBrush m_brBk;
	CBrush m_brBk2;
	bool m_bHighLight;

	CPen m_penLineA;
	CPen m_penLineB;
	CFont m_fontMsBlack;

	int m_nYLinePos;

	void UpdateStatus(bool bForce = false)
	{
		bool bInstalled = IsInstalled();
		if (bForce || m_bInstalled != bInstalled){
			m_bInstalled = bInstalled;
			
			LoadLogo(!bInstalled);

			if (bInstalled){
				LoadStatusText();
			}
			else{
				wchar_t wszBuf[250];
				LoadString(g_appModule.m_hInst, IDS_NOT_INSTALLED, wszBuf, 250);
				m_strStatus = wszBuf;
			}

			Invalidate();
		}
	}

	void OnDrawImage(Graphics &g, const CRect &rc)
	{
		int nWidth = (int) (rc.Width() / 2.5f);
		int nHeight = m_pImageLogo->GetHeight() * nWidth / m_pImageLogo->GetWidth();

		g.DrawImage(m_pImageLogo, rc.left + (rc.Width() - nWidth) / 2, rc.top + (rc.Height() - nHeight) / 2, nWidth, nHeight);
	}
};

