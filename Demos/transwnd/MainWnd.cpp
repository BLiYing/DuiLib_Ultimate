#include "StdAfx.h"
#include "MainWnd.h"

#include <ShellAPI.h>
//////////////////////////////////////////////////////////////////////////
///

DUI_BEGIN_MESSAGE_MAP(CMainWnd, WindowImplBase)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK,OnClick)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_ITEMSELECT,OnItemSelect)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_SELECTCHANGED,OnSelectChanged)
DUI_END_MESSAGE_MAP()

CMainWnd::CMainWnd(void)
{
}

CMainWnd::~CMainWnd(void)
{
}

void CMainWnd::OnFinalMessage( HWND hWnd)
{
	__super::OnFinalMessage(hWnd);
	delete this;
}

DuiLib::CDuiString CMainWnd::GetSkinFolder()
{
#ifdef _DEBUG
	return _T("skin\\transwnd\\");
#else
	return _T("skin\\");
#endif
	
}

DuiLib::CDuiString CMainWnd::GetSkinFile()
{
	return _T("skin.xml");
}

UILIB_RESOURCETYPE CMainWnd::GetResourceType() const
{
#ifdef _DEBUG
	return UILIB_FILE;
#else
	return UILIB_ZIPRESOURCE;
#endif
}

LPCTSTR CMainWnd::GetResourceID() const
{
	return _T("IDR_RES_SKIN");
}

DuiLib::CDuiString CMainWnd::GetZIPFileName() const
{
	return _T("skin.zip");
}

LPCTSTR CMainWnd::GetWindowClassName( void ) const
{
	return _T("MainWnd");
}

void CMainWnd::OnClick( TNotifyUI &msg )
{
	CDuiString sName = msg.pSender->GetName();
	sName.MakeLower();

	if( msg.pSender == m_pCloseBtn ) {
		PostQuitMessage(0);
		return; 
	}
	else if( msg.pSender == m_pMinBtn ) { 
		SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0); return; }
	else if( msg.pSender == m_pMaxBtn ) { 
		SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0); return; }
	else if( msg.pSender == m_pRestoreBtn ) { 
		SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0); return; }
	else if( msg.pSender == m_pMenuBtn ) {
	}
	else if(sName.CompareNoCase(_T("homepage_btn")) == 0)
	{
		ShellExecute(NULL, _T("open"), _T("https://github.com/duisharp"), NULL, NULL, SW_SHOW);
	}
}

void CMainWnd::OnSelectChanged( TNotifyUI &msg )
{
	CDuiString sName = msg.pSender->GetName();
	sName.MakeLower();

}

void CMainWnd::OnItemSelect( TNotifyUI &msg )
{
	CDuiString sName = msg.pSender->GetName();
	sName.MakeLower();
}

LRESULT CMainWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
 {
	 // �رմ��ڣ��˳�����
	 if(uMsg == WM_DESTROY)
	 {
		 ::PostQuitMessage(0L);
		bHandled = TRUE;
		return 0;
	 }
	 bHandled = FALSE;
	 return 0;
 }

void CMainWnd::Notify( TNotifyUI &msg )
{
	return WindowImplBase::Notify(msg);
}

LRESULT CMainWnd::OnSysCommand( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	// ��ʱ�����յ�WM_NCDESTROY���յ�wParamΪSC_CLOSE��WM_SYSCOMMAND
	if( wParam == SC_CLOSE ) {
		::PostQuitMessage(0L);
		bHandled = TRUE;
		return 0;
	}
	BOOL bZoomed = ::IsZoomed(*this);
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	if( ::IsZoomed(*this) != bZoomed ) {
		if( !bZoomed ) {
			CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("maxbtn")));
			if( pControl ) pControl->SetVisible(false);
			pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("restorebtn")));
			if( pControl ) pControl->SetVisible(true);
		}
		else {
			CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("maxbtn")));
			if( pControl ) pControl->SetVisible(true);
			pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("restorebtn")));
			if( pControl ) pControl->SetVisible(false);
		}
	}
	return lRes;
}

void CMainWnd::InitWindow()
{
	m_pCloseBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("closebtn")));
	m_pMaxBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("maxbtn")));
	m_pRestoreBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("restorebtn")));
	m_pMinBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("minbtn")));
	m_pMenuBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("menubtn")));
}