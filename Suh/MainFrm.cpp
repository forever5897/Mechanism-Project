
// MainFrm.cpp : CMainFrame 類別的實作
//

#include "stdafx.h"
#include "Mechanism_HW01.h"
#include "ButtonView.h"
#include "Mechanism_HW01View.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 狀態列指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 建構/解構

CMainFrame::CMainFrame()
{
	// TODO: 在此加入成員初始化程式碼
	m_splitter = new CSplitterWnd();
	bCreateSplitter = false;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("無法建立狀態列\n");
		return -1;      // 無法建立
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此經由修改 CREATESTRUCT cs 
	// 達到修改視窗類別或樣式的目的

	return TRUE;
}

// CMainFrame 診斷

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 訊息處理常式


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此加入特定的程式碼和 (或) 呼叫基底類別
	CRect rect;
	GetClientRect(&rect);
	if(!m_splitter->CreateStatic(this, 1, 2, WS_CHILD|WS_VISIBLE|WS_BORDER))
	{
		MessageBox( "Error setting up splitter frames!", "Init Error", MB_OK|MB_ICONERROR);
		return FALSE;
	}
	else
	{
		m_splitter->CreateView(0,1,RUNTIME_CLASS(CButtonView),CSize(rect.Width()/2,rect.Height()/2),pContext);       //Robot
		m_splitter->CreateView(0,0,RUNTIME_CLASS(CMechanism_HW01View),CSize(rect.Width()/2,rect.Height()/2),pContext);  //B-Spline

		bCreateSplitter = true;
	}
	return bCreateSplitter;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}
