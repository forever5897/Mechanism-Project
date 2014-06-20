// ButtonView.cpp : 實作檔
//

#include "stdafx.h"
#include "Mechanism_HW01.h"
#include "ButtonView.h"
#include "Mechanism_HW01View.h"

// CButtonView

IMPLEMENT_DYNCREATE(CButtonView, CFormView)

CButtonView::CButtonView()
	: CFormView(CButtonView::IDD)
	, m_Angle_1(0)
	, m_Displacement_1(0)
	, m_Angle_2(0)
	, m_Displacement_2(0)
	//, T11(_T(""))
	//, T12(_T(""))
	//, T13(_T(""))
	//, T21(_T(""))
	//, T22(_T(""))
	//, T23(_T(""))
	//, T31(_T(""))
	//, T32(_T(""))
	//, T33(_T(""))
{
	OverAll_Matrix.resize(4);
	for (int i=0; i<4; i++)
	{
		OverAll_Matrix[i].resize(4);
	}
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<=4; j++)
		{
			if(i == j)
				OverAll_Matrix[i][j] = 1;
		}
	}

}

CButtonView::~CButtonView()
{
}

void CButtonView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, m_Rot_AxisSelect);
	DDX_Control(pDX, IDC_COMBO3, m_Trans_AxisSelect);
	DDX_Control(pDX, IDC_COMBO4, m_Rot_AxisSelect_2);
	DDX_Control(pDX, IDC_COMBO5, m_Trans_AxisSelect_2);
	DDX_Text(pDX, IDC_EDIT1, m_Angle_1);
	DDX_Text(pDX, IDC_EDIT2, m_Displacement_1);
	DDX_Text(pDX, IDC_EDIT3, m_Angle_2);
	DDX_Text(pDX, IDC_EDIT4, m_Displacement_2);
	DDX_Control(pDX, IDC_EDIT5, T11);
	DDX_Control(pDX, IDC_EDIT8, T12);
	DDX_Control(pDX, IDC_EDIT11, T13);
	DDX_Control(pDX, IDC_EDIT6, T21);
	DDX_Control(pDX, IDC_EDIT9, T22);
	DDX_Control(pDX, IDC_EDIT12, T23);
	DDX_Control(pDX, IDC_EDIT7, T31);
	DDX_Control(pDX, IDC_EDIT10, T32);
	DDX_Control(pDX, IDC_EDIT13, T33);
	DDX_Control(pDX, IDC_EDIT14, T14);
	DDX_Control(pDX, IDC_EDIT15, T24);
	DDX_Control(pDX, IDC_EDIT16, T34);
	DDX_Control(pDX, IDC_EDIT20, T44);
	DDX_Control(pDX, IDC_EDIT17, T41);
	DDX_Control(pDX, IDC_EDIT18, T42);
	DDX_Control(pDX, IDC_EDIT19, T43);
}

BEGIN_MESSAGE_MAP(CButtonView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CButtonView::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CButtonView::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CButtonView::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CButtonView::OnBnClickedButton4)
END_MESSAGE_MAP()


// CButtonView 診斷

#ifdef _DEBUG
void CButtonView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CButtonView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CButtonView 訊息處理常式


void CButtonView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此加入特定的程式碼和 (或) 呼叫基底類別
	
}


void CButtonView::OnBnClickedButton1()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	double Angle_X, Angle_Y, Angle_Z;
	vector<vector<double>> temp_Matrix;
	temp_Matrix.resize(4);
	for (int i=0; i<4; i++)
	{
		temp_Matrix[i].resize(4);
	}
	POSITION pos = GetDocument()->GetFirstViewPosition();
	UpdateData(TRUE);
	switch(m_Rot_AxisSelect.GetCurSel())
	{
	case 0:
		Angle_X = m_Angle_1;
		temp_Matrix = Rot_x_Matrix(Angle_X);
		MultMatrix(temp_Matrix, OverAll_Matrix);
		ShowData();
		while (pos != NULL)
		{
			CView* pView = GetDocument()->GetNextView(pos);
			ASSERT_VALID(pView);
			if (pView != this)   
				((CMechanism_HW01View*)pView)->GetData1(Angle_X, 0);	
		}
		break;
	case 1:
		Angle_Y = m_Angle_1;
		temp_Matrix = Rot_y_Matrix(Angle_Y);
		MultMatrix(temp_Matrix, OverAll_Matrix);
		ShowData();
		while (pos != NULL)
		{
			CView* pView = GetDocument()->GetNextView(pos);
			ASSERT_VALID(pView);
			if (pView != this)   
				((CMechanism_HW01View*)pView)->GetData1(Angle_Y, 1);	
		}
		break;
	case 2:
		Angle_Z = m_Angle_1;
		temp_Matrix = Rot_z_Matrix(Angle_Z);
		MultMatrix(temp_Matrix, OverAll_Matrix);
		ShowData();
		while (pos != NULL)
		{
			CView* pView = GetDocument()->GetNextView(pos);
			ASSERT_VALID(pView);
			if (pView != this)   
				((CMechanism_HW01View*)pView)->GetData1(Angle_Z, 2);	
		}
		break;
	default:
		Angle_X = Angle_Y = Angle_Z = 0;
	}


	
}


void CButtonView::OnBnClickedButton3()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	double Angle_X, Angle_Y, Angle_Z;
	POSITION pos = GetDocument()->GetFirstViewPosition();
	UpdateData(TRUE);
	switch(m_Rot_AxisSelect_2.GetCurSel())
	{
	case 0:
		Angle_X = m_Angle_2;
		while (pos != NULL)
		{
			CView* pView = GetDocument()->GetNextView(pos);
			ASSERT_VALID(pView);
			if (pView != this)   
				((CMechanism_HW01View*)pView)->GetData2(Angle_X, 0);	
		}
		break;
	case 1:
		Angle_Y = m_Angle_2;
		while (pos != NULL)
		{
			CView* pView = GetDocument()->GetNextView(pos);
			ASSERT_VALID(pView);
			if (pView != this)   
				((CMechanism_HW01View*)pView)->GetData2(Angle_Y, 1);	
		}
		break;
	case 2:
		Angle_Z = m_Angle_2;
		while (pos != NULL)
		{
			CView* pView = GetDocument()->GetNextView(pos);
			ASSERT_VALID(pView);
			if (pView != this)   
				((CMechanism_HW01View*)pView)->GetData2(Angle_Z, 2);	
		}
		break;
	default:
		Angle_X = Angle_Y = Angle_Z = 0;
	}

}


void CButtonView::OnBnClickedButton2()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	double Displacement_X, Displacement_Y, Displacement_Z;
	vector<vector<double>> temp_Matrix;
	temp_Matrix.resize(4);
	for (int i=0; i<4; i++)
	{
		temp_Matrix[i].resize(4);
	}
	POSITION pos = GetDocument()->GetFirstViewPosition();
	UpdateData(TRUE);
	switch(m_Trans_AxisSelect.GetCurSel())
	{
	case 0:
		Displacement_X = m_Displacement_1;
		temp_Matrix = Dis_x_Matrix(Displacement_X);
		MultMatrix(temp_Matrix, OverAll_Matrix);
		ShowData();
		while (pos != NULL)
		{
			CView* pView = GetDocument()->GetNextView(pos);
			ASSERT_VALID(pView);
			if (pView != this)   
				((CMechanism_HW01View*)pView)->GetData3(Displacement_X, 0);	
		}
		break;
	case 1:
		Displacement_Y = m_Displacement_1;
		temp_Matrix = Dis_y_Matrix(Displacement_Y);
		MultMatrix(temp_Matrix, OverAll_Matrix);
		ShowData();
		while (pos != NULL)
		{
			CView* pView = GetDocument()->GetNextView(pos);
			ASSERT_VALID(pView);
			if (pView != this)   
				((CMechanism_HW01View*)pView)->GetData3(Displacement_Y, 1);	
		}
		break;
	case 2:
		Displacement_Z = m_Displacement_1;
		temp_Matrix = Dis_z_Matrix(Displacement_Z);
		MultMatrix(temp_Matrix, OverAll_Matrix);
		ShowData();
		while (pos != NULL)
		{
			CView* pView = GetDocument()->GetNextView(pos);
			ASSERT_VALID(pView);
			if (pView != this)   
				((CMechanism_HW01View*)pView)->GetData3(Displacement_Z, 2);	
		}
		break;
	default:
		Displacement_X = Displacement_Y = Displacement_Z = 0;
	}
}


void CButtonView::OnBnClickedButton4()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	double Displacement_X, Displacement_Y, Displacement_Z;
	POSITION pos = GetDocument()->GetFirstViewPosition();
	UpdateData(TRUE);
	switch(m_Trans_AxisSelect_2.GetCurSel())
	{
	case 0:
		Displacement_X = m_Displacement_2;
		while (pos != NULL)
		{
			CView* pView = GetDocument()->GetNextView(pos);
			ASSERT_VALID(pView);
			if (pView != this)   
				((CMechanism_HW01View*)pView)->GetData4(Displacement_X, 0);	
		}
		break;
	case 1:
		Displacement_Y = m_Displacement_2;
		while (pos != NULL)
		{
			CView* pView = GetDocument()->GetNextView(pos);
			ASSERT_VALID(pView);
			if (pView != this)   
				((CMechanism_HW01View*)pView)->GetData4(Displacement_Y, 1);	
		}
		break;
	case 2:
		Displacement_Z = m_Displacement_2;
		while (pos != NULL)
		{
			CView* pView = GetDocument()->GetNextView(pos);
			ASSERT_VALID(pView);
			if (pView != this)   
				((CMechanism_HW01View*)pView)->GetData4(Displacement_Z, 2);	
		}
		break;
	default:
		Displacement_X = Displacement_Y = Displacement_Z = 0;
	}
}
////////////////////////////定義旋轉矩陣///////////////////////////////
vector<vector<double>> CButtonView::Rot_z_Matrix(float theta)
{
	vector<vector<double>> temp_A;
	//宣告二維3x3陣列
	temp_A.resize(4);
	for(int i=0; i<4; i++)
	{
		temp_A[i].resize(4);
	}
	//矩陣所有元素設為0
	for(int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			temp_A[i][j] = 0;
		}
	}
	temp_A[0][0] = cos(theta * PI / 180);
	temp_A[0][1] = -sin(theta * PI / 180);
	temp_A[1][0] = sin(theta * PI / 180);
	temp_A[1][1] = cos(theta * PI / 180);
	temp_A[2][2] = 1;
	temp_A[3][3] = 1;

	return temp_A;
}
vector<vector<double>> CButtonView::Rot_y_Matrix(float theta)
{
	vector<vector<double>> temp_A;
	//宣告二維4x4陣列
	temp_A.resize(4);
	for(int i=0; i<4; i++)
	{
		temp_A[i].resize(4);
	}
	//矩陣所有元素設為0
	for(int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			temp_A[i][j] = 0;
		}
	}
	temp_A[0][0] = cos(theta * PI / 180);
	temp_A[0][2] = sin(theta * PI / 180);
	temp_A[2][0] = -sin(theta * PI / 180);
	temp_A[2][2] = cos(theta * PI / 180);
	temp_A[1][1] = 1;
	temp_A[3][3] = 1;
	return temp_A;
}
vector<vector<double>> CButtonView::Rot_x_Matrix(float theta)
{
	vector<vector<double>> temp_A;
	//宣告二維3x3陣列
	temp_A.resize(4);
	for(int i=0; i<4; i++)
	{
		temp_A[i].resize(4);
	}
	//矩陣所有元素設為0
	for(int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			temp_A[i][j] = 0;
		}
	}
	temp_A[0][0] = 1;
	temp_A[1][1] = cos(theta * PI / 180);
	temp_A[1][2] = -sin(theta * PI / 180);
	temp_A[2][1] = sin(theta * PI / 180);
	temp_A[2][2] = cos(theta * PI / 180);
	temp_A[3][3] = 1;

	return temp_A;
}
///////////////////////////////////////////////////////////////////////

//////////////////////////////定義位移矩陣/////////////////////////////
vector<vector<double>> CButtonView::Dis_x_Matrix(float length)
{
	vector<vector<double>> temp_A;
	//宣告二維3x3陣列
	temp_A.resize(4);
	for(int i=0; i<4; i++)
	{
		temp_A[i].resize(4);
	}
	//矩陣所有元素設為0,單位矩陣
	for(int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			temp_A[i][j] = 0;
			if (i == j)
			{
				temp_A[i][j] = 1;
			}
		}
	}
	temp_A[0][3] = length;


	return temp_A;

}
vector<vector<double>> CButtonView::Dis_y_Matrix(float length)
{
	vector<vector<double>> temp_A;
	//宣告二維3x3陣列
	temp_A.resize(4);
	for(int i=0; i<4; i++)
	{
		temp_A[i].resize(4);
	}
	//矩陣所有元素設為0,單位矩陣
	for(int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			temp_A[i][j] = 0;
			if (i == j)
			{
				temp_A[i][j] = 1;
			}
		}
	}
	temp_A[1][3] = length;


	return temp_A;

}
vector<vector<double>> CButtonView::Dis_z_Matrix(float length)
{
	vector<vector<double>> temp_A;
	//宣告二維3x3陣列
	temp_A.resize(4);
	for(int i=0; i<4; i++)
	{
		temp_A[i].resize(4);
	}
	//矩陣所有元素設為0,單位矩陣
	for(int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			temp_A[i][j] = 0;
			if (i == j)
			{
				temp_A[i][j] = 1;
			}
		}
	}
	temp_A[2][3] = length;


	return temp_A;

}
///////////////////////////////////////////////////////////////////////

void CButtonView::MultMatrix(vector<vector<double>> Matrix_A, vector<vector<double>> Matrix_B)
{
	vector<vector<double>> temp_A, temp_B, temp_C;
	//宣告二維1x4陣列
	//temp_A.resize(4);
	//temp_B.resize(4);
	temp_C.resize(4);
	for(int i=0; i<4; i++)
	{
		//temp_A[i].resize(4);
		//temp_B[i].resize(4);
		temp_C[i].resize(4);
	}

	//temp_A.assign(Matrix_A.begin(), Matrix_B.end());
	//temp_B.assign(Matrix_B.begin(), Matrix_B.end());

	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			temp_C[i][j] = 0;
			for (int k=0; k<4; k++)
			{
				temp_C[i][j] =  temp_C[i][j] + Matrix_A[i][k] * Matrix_B[k][j];
			}
		}
	}
	
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			OverAll_Matrix[i][j] = temp_C[i][j];
		}
	}
}


void CButtonView::ShowData()
{
	CString strBuffer[16];
	int j = 0;
	for (int i=0; i<16; i++)
	{
		strBuffer[i].Format("%f", OverAll_Matrix[j][i%4]);
		if (i%4 == 3)
		{
			j++;
		}
	}

	T11.SetWindowText(strBuffer[0]);
	T12.SetWindowText(strBuffer[1]);
	T13.SetWindowText(strBuffer[2]);
	T14.SetWindowText(strBuffer[3]);
	T21.SetWindowText(strBuffer[4]);
	T22.SetWindowText(strBuffer[5]);
	T23.SetWindowText(strBuffer[6]);
	T24.SetWindowText(strBuffer[7]);
	T31.SetWindowText(strBuffer[8]);
	T32.SetWindowText(strBuffer[9]);
	T33.SetWindowText(strBuffer[10]);
	T34.SetWindowText(strBuffer[11]);
	T41.SetWindowText(strBuffer[12]);
	T42.SetWindowText(strBuffer[13]);
	T43.SetWindowText(strBuffer[14]);
	T44.SetWindowText(strBuffer[15]);


}
