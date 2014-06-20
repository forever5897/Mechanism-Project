
// MainFrm.cpp : CMainFrame ���O����@
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
	ID_SEPARATOR,           // ���A�C���ܾ�
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame �غc/�Ѻc

CMainFrame::CMainFrame()
{
	// TODO: �b���[�J������l�Ƶ{���X
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
		TRACE0("�L�k�إߪ��A�C\n");
		return -1;      // �L�k�إ�
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �b���g�ѭק� CREATESTRUCT cs 
	// �F��ק�������O�μ˦����ت�

	return TRUE;
}

// CMainFrame �E�_

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


// CMainFrame �T���B�z�`��


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: �b���[�J�S�w���{���X�M (��) �I�s�����O
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
