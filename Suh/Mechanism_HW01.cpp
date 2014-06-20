
// Mechanism_HW01.cpp : �w�q���ε{�������O�欰�C
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Mechanism_HW01.h"
#include "MainFrm.h"

#include "Mechanism_HW01Doc.h"
#include "Mechanism_HW01View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMechanism_HW01App

BEGIN_MESSAGE_MAP(CMechanism_HW01App, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CMechanism_HW01App::OnAppAbout)
	// �̾ڤ��R�O���з��ɮ�
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// �зǦC�L�]�w�R�O
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CMechanism_HW01App �غc

CMechanism_HW01App::CMechanism_HW01App()
{
	// �䴩���s�Ұʺ޲z��
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// �p�G���ε{���O�ϥ� Common Language Runtime �䴩 (/clr) �ظm��:
	//     1) �n�ϭ��s�Ұʺ޲z���䴩���`�B�@�ݭn�o���B�~�]�w�C
	//     2) �b�M�פ������N�Ѧҥ[�J�� System.Windows.Forms �~��i��ظm�C
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: �H�ߤ@�� ID �r����N�U�������ε{�� ID �r��; ��ĳ��
	// �r��榡�� CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("Mechanism_HW01.AppID.NoVersion"));

	// TODO: �b���[�J�غc�{���X�A
	// �N�Ҧ����n����l�]�w�[�J InitInstance ��
}

// �Ȧ����@�� CMechanism_HW01App ����

CMechanism_HW01App theApp;


// CMechanism_HW01App ��l�]�w

BOOL CMechanism_HW01App::InitInstance()
{
	// ���p���ε{����T�M����w�ϥ� ComCtl32.dll 6 (�t) �H�᪩���A
	// �ӱҰʵ�ı�Ƽ˦��A�b Windows XP �W�A�h�ݭn InitCommonControls()�C
	// �_�h����������إ߳��N���ѡC
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// �]�w�n�]�t�Ҧ��z�Q�n�Ω����ε{������
	// �q�α�����O�C
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// ��l�� OLE �{���w
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// �ݭn�� AfxInitRichEdit2() �~��ϥ� RichEdit ���	
	// AfxInitRichEdit2();

	// �зǪ�l�]�w
	// �p�G�z���ϥγo�ǥ\��åB�Q���
	// �̫᧹�����i�����ɤj�p�A�z�i�H
	// �q�U�C�{���X�������ݭn����l�Ʊ`���A
	// �ܧ��x�s�]�w�Ȫ��n�����X
	// TODO: �z���ӾA�׭ק惡�r��
	// (�Ҧp�A���q�W�٩β�´�W��)
	SetRegistryKey(_T("���� AppWizard �Ҳ��ͪ����ε{��"));
	LoadStdProfileSettings(4);  // ���J�з� INI �ɿﶵ (�]�t MRU)


	// �n�����ε{�������d���C���d���t�d�b���B
	// �ج[�����P�˵����i��s��
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMechanism_HW01Doc),
		RUNTIME_CLASS(CMainFrame),       // �D SDI �ج[����
		RUNTIME_CLASS(CMechanism_HW01View));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// ��R�з� Shell �R�O�BDDE�B�ɮ׶}�����ɪ��R�O�C
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// �b�R�O�C�����w�������R�O�C�p�G�w�ϥ� 
	// /RegServer�B/Register�B/Unregserver �� /Unregister �Ұ����ε{���A�N�Ǧ^ FALSE�C
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// �Ȫ�l�Ƥ@�ӵ����A�ҥH��ܨç�s�ӵ���
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->SetWindowText("�������c - �@�~�@");
	m_pMainWnd->UpdateWindow();
	// �u���b SDI ���ε{��������m�r���ɡA�~�I�s DragAcceptFiles
	// �o�|�o�ͩ� ProcessShellCommand ����
	return TRUE;
}

int CMechanism_HW01App::ExitInstance()
{
	// TODO: �B�z��L�z�w�g�[�J���귽
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CMechanism_HW01App �T���B�z�`��


// �� App About �ϥ� CAboutDlg ��ܤ��

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ܤ�����
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

// �{���X��@
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// �����ܤ�������ε{���R�O
void CMechanism_HW01App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CMechanism_HW01App �T���B�z�`��


