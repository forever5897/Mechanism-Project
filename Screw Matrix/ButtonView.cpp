// ButtonView.cpp : ��@��
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

	ScrewCheck = bodyCheck = false;
	Translation.resize(3);
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

	DDX_Control(pDX, IDC_EDIT21, ux);
	DDX_Control(pDX, IDC_EDIT22, uy);
	DDX_Control(pDX, IDC_EDIT27, uz);
	DDX_Control(pDX, IDC_EDIT23, P1x);
	DDX_Control(pDX, IDC_EDIT24, P1y);
	DDX_Control(pDX, IDC_EDIT25, P1z);
	DDX_Control(pDX, IDC_EDIT26, S);
}

BEGIN_MESSAGE_MAP(CButtonView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CButtonView::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CButtonView::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CButtonView::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CButtonView::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &CButtonView::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON5, &CButtonView::OnBnClickedButton5)
END_MESSAGE_MAP()


// CButtonView �E�_

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


// CButtonView �T���B�z�`��


void CButtonView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �b���[�J�S�w���{���X�M (��) �I�s�����O
	
}


void CButtonView::OnBnClickedButton1()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	double Angle_X, Angle_Y, Angle_Z;
	POSITION pos = GetDocument()->GetFirstViewPosition();
	UpdateData(TRUE);
	switch(m_Rot_AxisSelect.GetCurSel())
	{
	case 0:
		Angle_X = m_Angle_1;
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
	// TODO: �b���[�J����i���B�z�`���{���X
	double Angle_X, Angle_Y, Angle_Z;
	vector<vector<double>> temp_Matrix;
	temp_Matrix.resize(4);
	for (int i=0; i<4; i++)
	{
		temp_Matrix[i].resize(4);
	}
	POSITION pos = GetDocument()->GetFirstViewPosition();
	UpdateData(TRUE);
	switch(m_Rot_AxisSelect_2.GetCurSel())
	{
	case 0:
		Angle_X = m_Angle_2;
		temp_Matrix = Rot_x_Matrix(Angle_X);
		MultMatrix(temp_Matrix, OverAll_Matrix);
		ShowData();
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
		temp_Matrix = Rot_y_Matrix(Angle_Y);
		MultMatrix(temp_Matrix, OverAll_Matrix);
		ShowData();
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
		temp_Matrix = Rot_z_Matrix(Angle_Z);
		MultMatrix(temp_Matrix, OverAll_Matrix);
		ShowData();
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
	// TODO: �b���[�J����i���B�z�`���{���X
	double Displacement_X, Displacement_Y, Displacement_Z;
	POSITION pos = GetDocument()->GetFirstViewPosition();
	UpdateData(TRUE);
	switch(m_Trans_AxisSelect.GetCurSel())
	{
	case 0:
		Displacement_X = m_Displacement_1;
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
	// TODO: �b���[�J����i���B�z�`���{���X
	double Displacement_X, Displacement_Y, Displacement_Z;
	vector<vector<double>> temp_Matrix;
	temp_Matrix.resize(4);
	for (int i=0; i<4; i++)
	{
		temp_Matrix[i].resize(4);
	}
	POSITION pos = GetDocument()->GetFirstViewPosition();
	UpdateData(TRUE);
	switch(m_Trans_AxisSelect_2.GetCurSel())
	{
	case 0:
		Displacement_X = m_Displacement_2;
		temp_Matrix = Dis_x_Matrix(Displacement_X);
		MultMatrix(temp_Matrix, OverAll_Matrix);
		ShowData();
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
		temp_Matrix = Dis_y_Matrix(Displacement_Y);
		MultMatrix(temp_Matrix, OverAll_Matrix);
		ShowData();
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
		temp_Matrix = Dis_z_Matrix(Displacement_Z);
		MultMatrix(temp_Matrix, OverAll_Matrix);
		ShowData();
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
////////////////////////////�w�q����x�}///////////////////////////////
vector<vector<double>> CButtonView::Rot_z_Matrix(float theta)
{
	vector<vector<double>> temp_A;
	//�ŧi�G��3x3�}�C
	temp_A.resize(4);
	for(int i=0; i<4; i++)
	{
		temp_A[i].resize(4);
	}
	//�x�}�Ҧ������]��0
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
	//�ŧi�G��4x4�}�C
	temp_A.resize(4);
	for(int i=0; i<4; i++)
	{
		temp_A[i].resize(4);
	}
	//�x�}�Ҧ������]��0
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
	//�ŧi�G��3x3�}�C
	temp_A.resize(4);
	for(int i=0; i<4; i++)
	{
		temp_A[i].resize(4);
	}
	//�x�}�Ҧ������]��0
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

//////////////////////////////�w�q�첾�x�}/////////////////////////////
vector<vector<double>> CButtonView::Dis_x_Matrix(float length)
{
	vector<vector<double>> temp_A;
	//�ŧi�G��3x3�}�C
	temp_A.resize(4);
	for(int i=0; i<4; i++)
	{
		temp_A[i].resize(4);
	}
	//�x�}�Ҧ������]��0,���x�}
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
	//�ŧi�G��3x3�}�C
	temp_A.resize(4);
	for(int i=0; i<4; i++)
	{
		temp_A[i].resize(4);
	}
	//�x�}�Ҧ������]��0,���x�}
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
	//�ŧi�G��3x3�}�C
	temp_A.resize(4);
	for(int i=0; i<4; i++)
	{
		temp_A[i].resize(4);
	}
	//�x�}�Ҧ������]��0,���x�}
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
	//�ŧi�G��1x4�}�C
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

	bodyCheck = true;
}


void CButtonView::OnBnClickedButton6()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	if (bodyCheck == true)
	{
		vector<double> temp_parameter;
		POSITION pos = GetDocument()->GetFirstViewPosition();
		temp_parameter = Cal_Screw_Parameter(OverAll_Matrix);

		CString strBuffer[7];
		for (int i=0; i<7; i++)
		{
			strBuffer[i].Format("%f", temp_parameter[i]);
		}

		ux.SetWindowText(strBuffer[0]);
		uy.SetWindowText(strBuffer[1]);
		uz.SetWindowText(strBuffer[2]);
		P1x.SetWindowText(strBuffer[3]);
		P1y.SetWindowText(strBuffer[4]);
		P1z.SetWindowText(strBuffer[5]);
		S.SetWindowText(strBuffer[6]);

		while (pos != NULL)
		{
			CView* pView = GetDocument()->GetNextView(pos);
			ASSERT_VALID(pView);
			if (pView != this)   
				((CMechanism_HW01View*)pView)->GetScrew_Data(temp_parameter, phi, 0, Translation);	
		}

		ScrewCheck = true;
	}
	else
	{
		MessageBox("������G�|���]�w����!!");
	}



}



vector<double> CButtonView::Cal_Screw_Parameter(vector<vector<double>> temp_matrix)
{
	vector<double> temp_Coefficient, temp_Matrixb(3, 0);
	temp_Coefficient.resize(7);
	double temp_phi;
	vector<vector<double>> temp_A, temp_MatrixA;
	temp_A.resize(3);
	temp_MatrixA.resize(3);
	for (int i=0; i<3; i++)
	{
		temp_A[i].resize(3);
		temp_MatrixA[i].resize(3);
	}

	for (int i=0; i<3; i++)
	{
		for (int j=0; j<3; j++)
		{
			temp_A[i][j] = temp_matrix[i][j];
		}
	}
	//�p��u�b�Y��

	temp_phi = acos((temp_A[0][0] + temp_A[1][1] + temp_A[2][2] - 1) / 2);

	temp_Coefficient[0] = (temp_A[2][1] - temp_A[1][2]) / (2*sin(temp_phi));
	temp_Coefficient[1] = (temp_A[0][2] - temp_A[2][0]) / (2*sin(temp_phi));
	temp_Coefficient[2] = (temp_A[1][0] - temp_A[0][1]) / (2*sin(temp_phi));
	temp_Coefficient[3] = 1;         //�] P1x = 0

	temp_MatrixA = Setting_MatrixA(temp_Coefficient, temp_A);
	temp_Matrixb = Setting_Matrixb(OverAll_Matrix, temp_Coefficient);
	vector<double> temp_c(3,0);
	temp_c = NaiveGauss(temp_MatrixA, temp_Matrixb, 3);

	temp_Coefficient[4] = temp_c[1];
	temp_Coefficient[5] = temp_c[2];
	temp_Coefficient[6] = temp_c[0];

	phi = temp_phi;

	for (int i=0; i<3; i++)
	{
		Translation[i] = OverAll_Matrix[i][3];
	}

	return temp_Coefficient;
}

///////////////////////////////////////�p��P1x,P1y,P1z,S���ѼơA�ҨϥΤ��ƭȤ�k/////////////////////////////////////

vector<double> CButtonView::NaiveGauss(vector<vector<double>> matrix, vector<double> b, int n)
{
	/*
		�G��vector�t�m
	*/
	matrix.resize(n);
	for (int i=0; i<n; i++)
	{
		matrix[i].resize(n);
	}
	/*
		Forward elimination
	*/
	for (int i =0; i<n-1;i++)
	{
		for(int j = i+1; j< n; j++)
		{
			double multiplier = matrix[j][i]/matrix[i][i];
			for (int k=i+1; k<n; k++)
			{
				matrix[j][k] = matrix[j][k] - (multiplier * matrix[i][k]);
			}
			b[j] = b[j] - (multiplier * b[i]);
		}
	}

	/*
		Backward Substitution
	*/
	vector<double> temp_c(n,0);
	
	for (int i = n-1; i>=0; i--)
	{
		double factor=0;
		for (int k =i; k<n; k++)
		{
			factor += matrix[i][k] * temp_c[k];
		}
		temp_c[i] = (b[i]-factor)/matrix[i][i];
	}

	return temp_c;
}

vector<vector<double>> CButtonView::Setting_MatrixA(vector<double> temp_var, vector<vector<double>> temp_Data)
{
	/*
		�G��vector�t�m
	*/
	vector<vector<double>> matrix;
	matrix.resize(3);
	for (int i =0; i<3; i++)
	{
		matrix[i].resize(3);
	}

	/*
		��x�}�S�w��m�]��
	*/
	matrix[0][0] = temp_var[0];
	matrix[1][0] = temp_var[1];
	matrix[2][0] = temp_var[2];
	matrix[0][1] = -temp_Data[0][1];
	matrix[1][1] = 1 - temp_Data[1][1];
	matrix[2][1] = -temp_Data[2][1];
	matrix[0][2] = -temp_Data[0][2];
	matrix[1][2] = -temp_Data[1][2];
	matrix[2][2] = 1 - temp_Data[2][2];


	return matrix;
}

vector<double> CButtonView::Setting_Matrixb(vector<vector<double>> temp_Data, vector<double> temp_Coeff)
{
	vector<double> temp_b(3,0);

	temp_b[0] = temp_Data[0][3] + (temp_Data[0][0] - 1) * temp_Coeff[0];
	temp_b[1] = temp_Data[1][3] + temp_Data[0][1] * temp_Coeff[0];
	temp_b[2] = temp_Data[2][3] + temp_Data[2][0] * temp_Coeff[0];

	return temp_b;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CButtonView::OnBnClickedButton5()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	if (ScrewCheck == true)
	{
		POSITION pos = GetDocument()->GetFirstViewPosition();
		while (pos != NULL)
		{
			CView* pView = GetDocument()->GetNextView(pos);
			ASSERT_VALID(pView);
			if (pView != this)   
				((CMechanism_HW01View*)pView)->AnimateCheck();	
		}
	}
	else
	{
		MessageBox("Screw�ѼƩ|��D�X!!");
	}

}
