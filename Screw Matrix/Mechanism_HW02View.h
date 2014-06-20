
// Mechanism_HW01View.h : CMechanism_HW01View 類別的介面
//

#pragma once
#include "gl\gl.h"
#include "gl\glu.h"
#include <gl\glut.h>
#include "Mechanism_HW01Doc.h"
#include <vector>
#include <math.h>
#include "ButtonView.h"

using namespace std;

#define PI 3.1415926535
class CPtInfo
{
public:
	CPtInfo(){x = y = z = 0.0;}
	~CPtInfo(){};
public:
	float x, y, z;
};
class CMechanism_HW01View : public CView
{
protected: // 僅從序列化建立
	CMechanism_HW01View();
	DECLARE_DYNCREATE(CMechanism_HW01View)

// 屬性
public:
	CMechanism_HW01Doc* GetDocument() const;

// 作業
public:
	HDC m_hdc;
	HGLRC m_rc;

//變數
public:
	double Angle_x2, Angle_y2, Angle_z2;
	bool InitialDraw, RotDraw1, RotDraw2, DisplaceDraw1, DisplaceDraw2, Num2InitialDraw, Num2LastDraw;
	int N;
	vector<CPtInfo> Cuboid_Data, Cuboid_Data2, Cuboid1_Special_Data, Cuboid2_Special_Data;
	vector<double> Screw_Parameter, Displace_S, Displace_S_incre;
	bool DrawArbitraryLine, ExecuteFlag, FinalDraw;
	double phi, phi_incre;

//旋轉平移
public:
	bool state;
	GLfloat m_xangle;
	GLfloat m_yangle;
	GLfloat distance;
	CPoint m_MouseDownPoint;

// 覆寫
public:
	virtual void OnDraw(CDC* pDC);  // 覆寫以描繪此檢視
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 程式碼實作
public:
	virtual ~CMechanism_HW01View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 產生的訊息對應函式
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	bool SetDCPixelFormat(HDC hDC);
	void RenderScene(void);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	void GetData1(float temp_Angle, int Num);
	void GetData2(float temp_Angle, int Num);
	void GetData3(float temp_Displacement, int Num);
	void GetData4(float temp_Displacement, int Num);

	vector<vector<double>> Rot_z_Matrix(float theta);
	vector<vector<double>> Rot_y_Matrix(float theta);
	vector<vector<double>> Rot_x_Matrix(float theta);
	vector<vector<double>> Dis_x_Matrix(float length);
	vector<vector<double>> Dis_y_Matrix(float length);
	vector<vector<double>> Dis_z_Matrix(float length);
	void MultMatrix1(vector<vector<double>> KineMatrix, vector<CPtInfo> ObjMatrix);
	void MultMatrix2(vector<vector<double>> KineMatrix, vector<CPtInfo> ObjMatrix);

	void GetScrew_Data(vector<double> temp_Coeff, double temp_phi, int DrawFlag, vector<double> temp_matrix);

	afx_msg void OnTimer(UINT_PTR nIDEvent);

	void AnimateCheck(void);
};

#ifndef _DEBUG  // Mechanism_HW01View.cpp 中的偵錯版本
inline CMechanism_HW01Doc* CMechanism_HW01View::GetDocument() const
   { return reinterpret_cast<CMechanism_HW01Doc*>(m_pDocument); }
#endif

