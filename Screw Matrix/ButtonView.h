#pragma once
#include "afxwin.h"
#include <vector>
#include <math.h>
using namespace std;

// CButtonView 表單檢視

class CButtonView : public CFormView
{
	DECLARE_DYNCREATE(CButtonView)

public:
	CButtonView();           // 動態建立所使用的保護建構函式
	virtual ~CButtonView();

public:
	enum { IDD = IDD_BUTTONVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_Rot_AxisSelect;
	CComboBox m_Trans_AxisSelect;
	CComboBox m_Rot_AxisSelect_2;
	CComboBox m_Trans_AxisSelect_2;
	virtual void OnInitialUpdate();
	float m_Angle_1;
	float m_Displacement_1;
	float m_Angle_2;
	float m_Displacement_2;
	double phi;
	bool ScrewCheck, bodyCheck;
	vector<double> Translation;
	vector<vector<double>> OverAll_Matrix;

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();

	vector<vector<double>> Rot_z_Matrix(float theta);
	vector<vector<double>> Rot_y_Matrix(float theta);
	vector<vector<double>> Rot_x_Matrix(float theta);
	vector<vector<double>> Dis_x_Matrix(float length);
	vector<vector<double>> Dis_y_Matrix(float length);
	vector<vector<double>> Dis_z_Matrix(float length);

	void MultMatrix(vector<vector<double>> Matrix_A, vector<vector<double>> Matrix_B);
	void ShowData(void);

	CEdit T11;
	CEdit T12;
	CEdit T13;
	CEdit T21;
	CEdit T22;
	CEdit T23;
	CEdit T31;
	CEdit T32;
	CEdit T33;
	CEdit T14;
	CEdit T24;
	CEdit T34;
	CEdit T44;
	CEdit T41;
	CEdit T42;
	CEdit T43;
	afx_msg void OnBnClickedButton6();

	vector<double> Cal_Screw_Parameter(vector<vector<double>> temp_matrix);
	vector<double> NaiveGauss(vector<vector<double>> matrix, vector<double> b, int n);

	vector<vector<double>> Setting_MatrixA(vector<double> temp_var, vector<vector<double>> temp_Data);
	vector<double> Setting_Matrixb(vector<vector<double>> temp_Data, vector<double> temp_Coeff);

	CEdit ux;
	CEdit uy;
	CEdit uz;
	CEdit P1x;
	CEdit P1y;
	CEdit P1z;
	CEdit S;
	afx_msg void OnBnClickedButton5();
};


