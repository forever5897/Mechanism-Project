
// Mechanism_HW01View.cpp : CMechanism_HW01View ���O����@
//

#include "stdafx.h"
// SHARED_HANDLERS �i�H�w�q�b��@�w���B�Y�ϩM�j�M�z�����B�z�`����
// ATL �M�פ��A�ä��\�P�ӱM�צ@�Τ��{���X�C
#ifndef SHARED_HANDLERS
#include "Mechanism_HW01.h"
#endif

#include "Mechanism_HW01Doc.h"
#include "Mechanism_HW01View.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMechanism_HW01View

IMPLEMENT_DYNCREATE(CMechanism_HW01View, CView)

BEGIN_MESSAGE_MAP(CMechanism_HW01View, CView)
	// �зǦC�L�R�O
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CMechanism_HW01View �غc/�Ѻc

CMechanism_HW01View::CMechanism_HW01View()
{
	// TODO: �b���[�J�غc�{���X
	m_xangle = m_yangle = 0;
	distance = 0.0;
	Cuboid_Data.clear();
	Cuboid_Data.resize(8);
	Cuboid1_Special_Data.clear();
	Cuboid1_Special_Data.resize(4);
	state = RotDraw1 = RotDraw2 = DisplaceDraw1 = DisplaceDraw2 = DrawArbitraryLine = ExecuteFlag = Num2LastDraw = FinalDraw = false;
	InitialDraw = Num2InitialDraw = true;
	Angle_x2 = Angle_y2 = Angle_z2 = 0;
	phi_incre = 0;
	Displace_S.resize(3);
	Displace_S_incre.resize(3,0);

	Cuboid_Data[0].x = 0; Cuboid_Data[0].y = 10; Cuboid_Data[0].z = 0;
	Cuboid_Data[1].x = 15; Cuboid_Data[1].y = 10; Cuboid_Data[1].z = 0;
	Cuboid_Data[2].x = 15; Cuboid_Data[2].y = 0; Cuboid_Data[2].z = 0;
	Cuboid_Data[3].x = 0; Cuboid_Data[3].y = 0; Cuboid_Data[3].z = 0;
	Cuboid_Data[4].x = 0; Cuboid_Data[4].y = 0; Cuboid_Data[4].z = 20;
	Cuboid_Data[5].x = 0; Cuboid_Data[5].y = 10; Cuboid_Data[5].z = 20;
	Cuboid_Data[6].x = 15; Cuboid_Data[6].y = 10; Cuboid_Data[6].z = 20;
	Cuboid_Data[7].x = 15; Cuboid_Data[7].y = 0; Cuboid_Data[7].z = 20;

	Cuboid_Data2.assign(Cuboid_Data.begin(), Cuboid_Data.end());

}

CMechanism_HW01View::~CMechanism_HW01View()
{
}

BOOL CMechanism_HW01View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �b���g�ѭק� CREATESTRUCT cs 
	// �F��ק�������O�μ˦����ت�

	return CView::PreCreateWindow(cs);
}

// CMechanism_HW01View �yø

void CMechanism_HW01View::OnDraw(CDC* /*pDC*/)
{
	CMechanism_HW01Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �b���[�J��͸�ƪ��yø�{���X
	
	RenderScene();

	::glFinish();

	::SwapBuffers(m_hdc);
}


// CMechanism_HW01View �C�L

BOOL CMechanism_HW01View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �w�]���ǳƦC�L�{���X
	return DoPreparePrinting(pInfo);
}

void CMechanism_HW01View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �[�J�C�L�e�B�~����l�]�w
}

void CMechanism_HW01View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �[�J�C�L�᪺�M���{���X
}


// CMechanism_HW01View �E�_

#ifdef _DEBUG
void CMechanism_HW01View::AssertValid() const
{
	CView::AssertValid();
}

void CMechanism_HW01View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMechanism_HW01Doc* CMechanism_HW01View::GetDocument() const // ���O�D��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMechanism_HW01Doc)));
	return (CMechanism_HW01Doc*)m_pDocument;
}
#endif //_DEBUG


// CMechanism_HW01View �T���B�z�`��


void CMechanism_HW01View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: �b���[�J�z���T���B�z�`���{���X
	wglMakeCurrent(m_hdc,m_rc);

	float rate;
	if( cy==0 ) cy = 1;                        //����h���s�A�����i���ର�s��
	glViewport( 0, 0, cx, cy);                 //��������e���ܮɡA�e���]�����
	rate = (float)cx/(float)cy;                //�e�������ܤF�A�����e���ܧ�

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-300,300,-300,300,300,-300);
	gluPerspective(45,rate,1,300);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


int CMechanism_HW01View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �b���[�J�S�O�إߪ��{���X
	//Get HDC
	m_hdc = GetDC()->GetSafeHdc();

	//Choose pixel format
	if (!SetDCPixelFormat(m_hdc))
		return -1;


	//Create RC
	m_rc = wglCreateContext(m_hdc);

	//Basic setup here
	wglMakeCurrent(m_hdc,m_rc);

	//Clear color
	glClearColor(0.95f, 0.95f, 0.95f, 1.0f);

	//Shade mode
	glShadeModel(GL_FLAT);

	//Winding
	glFrontFace(GL_CCW);

	//Culling
	//glEnable(GL_CULL_FACE);

	//Depth test
	glEnable(GL_DEPTH_TEST);

	//Polygon mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	return 0;
}


void CMechanism_HW01View::OnDestroy()
{
	CView::OnDestroy();

	// TODO: �b���[�J�z���T���B�z�`���{���X
	if (m_hdc != 0)
	{
		::wglMakeCurrent(m_hdc,NULL);
		m_hdc = 0;
	}
	if (m_rc != 0)
	{
		::wglDeleteContext(m_rc);
		m_rc = 0;
	}
}


BOOL CMechanism_HW01View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��

	return TRUE;
}


bool CMechanism_HW01View::SetDCPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pixelDesc;
	pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion = 1;
	pixelDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_STEREO_DONTCARE;
	pixelDesc.iPixelType = PFD_TYPE_RGBA;
	pixelDesc.cColorBits                  = 32;
	pixelDesc.cRedBits                    = 8;
	pixelDesc.cRedShift                   = 16;
	pixelDesc.cGreenBits				  = 8;
	pixelDesc.cGreenShift                 = 8;
	pixelDesc.cBlueBits                   = 8;
	pixelDesc.cBlueShift                  = 0;
	pixelDesc.cAlphaBits                  = 0;
	pixelDesc.cAlphaShift                 = 0;
	pixelDesc.cAccumBits                  = 64;
	pixelDesc.cAccumRedBits               = 16;
	pixelDesc.cAccumGreenBits             = 16;
	pixelDesc.cAccumBlueBits              = 16;
	pixelDesc.cAccumAlphaBits             = 0;
	pixelDesc.cDepthBits                  = 32;
	pixelDesc.cStencilBits                = 8;
	pixelDesc.cAuxBuffers                 = 0;
	pixelDesc.iLayerType                  = PFD_MAIN_PLANE;
	pixelDesc.bReserved                   = 0;
	pixelDesc.dwLayerMask                 = 0;
	pixelDesc.dwVisibleMask               = 0;
	pixelDesc.dwDamageMask                = 0;
	int m_GLPixelIndex = ChoosePixelFormat(hDC, &pixelDesc);
	if (m_GLPixelIndex==0)
	{
		m_GLPixelIndex = 1;
		if (DescribePixelFormat(hDC, m_GLPixelIndex,sizeof(PIXELFORMATDESCRIPTOR),&pixelDesc)==0)
		{
			return FALSE;
		}
	}
	if (SetPixelFormat(hDC, m_GLPixelIndex, &pixelDesc)==FALSE)
	{
		return TRUE;
	}

	return TRUE;
}


void CMechanism_HW01View::RenderScene(void)
{
	//Combine m_hdc and m_rc
	wglMakeCurrent(m_hdc, m_rc);

	//Clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 0, 120.0, 0, 0, 0, 0, 1, 0);

	glTranslatef(0, 0, distance);
	glRotatef( m_yangle, 1.0, 0.0, 0.0);   //�Hx�b�����b
	glRotatef( m_xangle, 0.0, 1.0, 0.0);   //�Hy�b�����b

	//Draw cuboid_1
	glNewList(1, GL_COMPILE);
	glColor3f(0.f, 0.25f, 0.8f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(2);
		glBegin(GL_QUADS);
			glVertex3f(Cuboid_Data[3].x, Cuboid_Data[3].y, Cuboid_Data[3].z);
			glVertex3f(Cuboid_Data[0].x, Cuboid_Data[0].y, Cuboid_Data[0].z);
			glVertex3f(Cuboid_Data[5].x, Cuboid_Data[5].y, Cuboid_Data[5].z);
			glVertex3f(Cuboid_Data[4].x, Cuboid_Data[4].y, Cuboid_Data[4].z);
		
			glVertex3f(Cuboid_Data[5].x, Cuboid_Data[5].y, Cuboid_Data[5].z);
			glVertex3f(Cuboid_Data[6].x, Cuboid_Data[6].y, Cuboid_Data[6].z);
			glVertex3f(Cuboid_Data[7].x, Cuboid_Data[7].y, Cuboid_Data[7].z);
			glVertex3f(Cuboid_Data[4].x, Cuboid_Data[4].y, Cuboid_Data[4].z);

			glVertex3f(Cuboid_Data[0].x, Cuboid_Data[0].y, Cuboid_Data[0].z);
			glVertex3f(Cuboid_Data[5].x, Cuboid_Data[5].y, Cuboid_Data[5].z);
			glVertex3f(Cuboid_Data[6].x, Cuboid_Data[6].y, Cuboid_Data[6].z);
			glVertex3f(Cuboid_Data[1].x, Cuboid_Data[1].y, Cuboid_Data[1].z);

			glVertex3f(Cuboid_Data[1].x, Cuboid_Data[1].y, Cuboid_Data[1].z);
			glVertex3f(Cuboid_Data[2].x, Cuboid_Data[2].y, Cuboid_Data[2].z);
			glVertex3f(Cuboid_Data[7].x, Cuboid_Data[7].y, Cuboid_Data[7].z);
			glVertex3f(Cuboid_Data[6].x, Cuboid_Data[6].y, Cuboid_Data[6].z);

			glVertex3f(Cuboid_Data[3].x, Cuboid_Data[3].y, Cuboid_Data[3].z);
			glVertex3f(Cuboid_Data[0].x, Cuboid_Data[0].y, Cuboid_Data[0].z);
			glVertex3f(Cuboid_Data[1].x, Cuboid_Data[1].y, Cuboid_Data[1].z);
			glVertex3f(Cuboid_Data[2].x, Cuboid_Data[2].y, Cuboid_Data[2].z);

			glVertex3f(Cuboid_Data[3].x, Cuboid_Data[3].y, Cuboid_Data[3].z);
			glVertex3f(Cuboid_Data[2].x, Cuboid_Data[2].y, Cuboid_Data[2].z);
			glVertex3f(Cuboid_Data[7].x, Cuboid_Data[7].y, Cuboid_Data[7].z);
			glVertex3f(Cuboid_Data[4].x, Cuboid_Data[4].y, Cuboid_Data[4].z);
		glEnd();
	glEndList();

	//Draw cuboid_2
	glNewList(2, GL_COMPILE);
		glColor3f(1.f, 0.25f, 0.f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_QUADS);
		glVertex3f(Cuboid_Data2[3].x, Cuboid_Data2[3].y, Cuboid_Data2[3].z);
		glVertex3f(Cuboid_Data2[0].x, Cuboid_Data2[0].y, Cuboid_Data2[0].z);
		glVertex3f(Cuboid_Data2[5].x, Cuboid_Data2[5].y, Cuboid_Data2[5].z);
		glVertex3f(Cuboid_Data2[4].x, Cuboid_Data2[4].y, Cuboid_Data2[4].z);

		glVertex3f(Cuboid_Data2[5].x, Cuboid_Data2[5].y, Cuboid_Data2[5].z);
		glVertex3f(Cuboid_Data2[6].x, Cuboid_Data2[6].y, Cuboid_Data2[6].z);
		glVertex3f(Cuboid_Data2[7].x, Cuboid_Data2[7].y, Cuboid_Data2[7].z);
		glVertex3f(Cuboid_Data2[4].x, Cuboid_Data2[4].y, Cuboid_Data2[4].z);

		glVertex3f(Cuboid_Data2[0].x, Cuboid_Data2[0].y, Cuboid_Data2[0].z);
		glVertex3f(Cuboid_Data2[5].x, Cuboid_Data2[5].y, Cuboid_Data2[5].z);
		glVertex3f(Cuboid_Data2[6].x, Cuboid_Data2[6].y, Cuboid_Data2[6].z);
		glVertex3f(Cuboid_Data2[1].x, Cuboid_Data2[1].y, Cuboid_Data2[1].z);

		glVertex3f(Cuboid_Data2[1].x, Cuboid_Data2[1].y, Cuboid_Data2[1].z);
		glVertex3f(Cuboid_Data2[2].x, Cuboid_Data2[2].y, Cuboid_Data2[2].z);
		glVertex3f(Cuboid_Data2[7].x, Cuboid_Data2[7].y, Cuboid_Data2[7].z);
		glVertex3f(Cuboid_Data2[6].x, Cuboid_Data2[6].y, Cuboid_Data2[6].z);

		glVertex3f(Cuboid_Data2[3].x, Cuboid_Data2[3].y, Cuboid_Data2[3].z);
		glVertex3f(Cuboid_Data2[0].x, Cuboid_Data2[0].y, Cuboid_Data2[0].z);
		glVertex3f(Cuboid_Data2[1].x, Cuboid_Data2[1].y, Cuboid_Data2[1].z);
		glVertex3f(Cuboid_Data2[2].x, Cuboid_Data2[2].y, Cuboid_Data2[2].z);

		glVertex3f(Cuboid_Data2[3].x, Cuboid_Data2[3].y, Cuboid_Data2[3].z);
		glVertex3f(Cuboid_Data2[2].x, Cuboid_Data2[2].y, Cuboid_Data2[2].z);
		glVertex3f(Cuboid_Data2[7].x, Cuboid_Data2[7].y, Cuboid_Data2[7].z);
		glVertex3f(Cuboid_Data2[4].x, Cuboid_Data2[4].y, Cuboid_Data2[4].z);
		glEnd();
	glEndList();

	if (InitialDraw == true)
	{
		glPushMatrix();
		glCallList(1);
		glPopMatrix();
	}
	if(Num2InitialDraw == true)
	{
		glPushMatrix();
		glCallList(2);
		glPopMatrix();
	}

	if(RotDraw1 == true)
	{
		switch(N)
		{
		case 0:
			glPushMatrix();
			glCallList(1);
			glPopMatrix();
			InitialDraw = false;
			break;
		case 1:
			glPushMatrix();
			glCallList(1);
			glPopMatrix();
			InitialDraw = false;
			break;
		case 2:
			glPushMatrix();
			glCallList(1);
			glPopMatrix();
			InitialDraw = false;
			break;
		}

	}

	if(RotDraw2 == true)
	{
		switch(N)
		{
		case 0:
			glPushMatrix();
			glCallList(2);
			glPopMatrix();
			Num2InitialDraw = false;
			break;
		case 1:
			glPushMatrix();
			glCallList(2);
			glPopMatrix();
			Num2InitialDraw = false;
			break;
		case 2:
			glPushMatrix();
			glCallList(2);
			glPopMatrix();
			Num2InitialDraw = false;
			break;
		}
	}

	if (DisplaceDraw1 == true)
	{
		switch(N)
		{
		case 0:
			glPushMatrix();
			glCallList(1);
			glPopMatrix();
			InitialDraw = false;
			break;
		case 1:
			glPushMatrix();
			glCallList(1);
			glPopMatrix();
			InitialDraw = false;
			break;
		case 2:
			glPushMatrix();
			glCallList(1);
			glPopMatrix();
			InitialDraw = false;
			break;
		}
	}
	if (DisplaceDraw2 == true)
	{
		switch(N)
		{
		case 0:
			glPushMatrix();
			glCallList(2);
			glPopMatrix();
			Num2InitialDraw = false;
			break;
		case 1:
			glPushMatrix();
			glCallList(2);
			glPopMatrix();
			Num2InitialDraw = false;
			break;
		case 2:
			glPushMatrix();
			glCallList(2);
			glPopMatrix();
			Num2InitialDraw = false;
			break;
		}
	}

	if (DrawArbitraryLine == true)
	{
		glColor3f(0.f, 0.5f, 0.8f);
		glBegin(GL_LINES);
			glVertex3f(Screw_Parameter[3], Screw_Parameter[4], Screw_Parameter[5]);
			glVertex3f(Screw_Parameter[3] + Screw_Parameter[0] * 50
					 , Screw_Parameter[4] + Screw_Parameter[1] * 50
					 , Screw_Parameter[5] + Screw_Parameter[2] * 50);
		glEnd();
	}

	if (ExecuteFlag == true)
	{
		glCallList(2);
		if (phi_incre > phi)
		{
			KillTimer(1);
			phi_incre = 0;
			ExecuteFlag = false;
			FinalDraw = true;
		}
		if (Displace_S_incre[0] > Displace_S[0])
		{
			Displace_S_incre.assign(3, 0);
		}
		glPushMatrix();
		glTranslatef(Displace_S_incre[0], Displace_S_incre[1], Displace_S_incre[2]);
		glRotatef(phi_incre, Screw_Parameter[0], Screw_Parameter[1], Screw_Parameter[2]);
		glCallList(1);
		glPopMatrix();
	}

	if (Num2LastDraw == true)
	{
		glCallList(1);
		glCallList(2);
	}

	if (FinalDraw == true)
	{
		glPushMatrix();
		glTranslatef(Displace_S[0], Displace_S[1], Displace_S[2]);
		glRotatef(phi, Screw_Parameter[0], Screw_Parameter[1], Screw_Parameter[2]);
		glCallList(1);
		glPopMatrix();
	}

	//Draw coordinate
	glColor3f(1.0f,0.f,0.f);
	glBegin(GL_LINES);
	glVertex3f(0.0f,0.f,0.f);
	glVertex3f(50.f,0.f,0.f);
	glEnd();

	glColor3f(0.0f,1.f,0.f);
	glBegin(GL_LINES);
	glVertex3f(0.0f,0.f,0.f);
	glVertex3f(0.f,50.f,0.f);
	glEnd();

	glColor3f(0.0f,0.f,1.f);
	glBegin(GL_LINES);
	glVertex3f(0.0f,0.f,0.f);
	glVertex3f(0.f,0.f,50.f);
	glEnd();

}


void CMechanism_HW01View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	m_MouseDownPoint = point;
	SetCapture();
	RotDraw1 = RotDraw2 = DisplaceDraw1 = DisplaceDraw2 = true;
	state = true;
	CView::OnLButtonDown(nFlags, point);
}


void CMechanism_HW01View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	m_MouseDownPoint = CPoint(0,0);
	ReleaseCapture();
	RotDraw1 = RotDraw2 = DisplaceDraw1 = DisplaceDraw2 = false;
	state = false;
	CView::OnLButtonUp(nFlags, point);
}


void CMechanism_HW01View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��

	if (GetCapture() == this && state == TRUE)
	{
		m_xangle += (point.x - m_MouseDownPoint.x)/3.6;
		m_yangle += (point.y - m_MouseDownPoint.y)/3.6;
		Invalidate();
		UpdateWindow();
		m_MouseDownPoint = point;
	}

	CView::OnMouseMove(nFlags, point);
}


BOOL CMechanism_HW01View::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	if (zDelta > 1)
	{
		distance+=1;
	}
	else
	{
		distance-=1;
	}
	RotDraw1 = RotDraw2 = DisplaceDraw1 = DisplaceDraw2 = true;
	Invalidate();
	UpdateWindow();
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}



void CMechanism_HW01View::GetData1(float temp_Angle, int Num)   //Get No.1 Cuboid rotation angle
{
	N = Num;
	vector<vector<double>> temp_Matrix;
	temp_Matrix.resize(4);
	for (int i=0; i<4; i++)
	{
		temp_Matrix[i].resize(4);
	}

	switch(Num)
	{
	case 0:
		RotDraw1 = true;
		RotDraw2 = true;
		temp_Matrix = Rot_x_Matrix(temp_Angle);
		MultMatrix1(temp_Matrix, Cuboid_Data);
		MultMatrix2(temp_Matrix, Cuboid_Data2);
		Invalidate();
		UpdateWindow();
		RotDraw1 = false;
		RotDraw2 = false;
		break;
	case 1:
		RotDraw1 = true;
		RotDraw2 = true;
		temp_Matrix = Rot_y_Matrix(temp_Angle);
		MultMatrix1(temp_Matrix, Cuboid_Data);
		MultMatrix2(temp_Matrix, Cuboid_Data2);
		Invalidate();
		UpdateWindow();
		RotDraw1 = false;
		RotDraw2 = false;
		break;
	case 2:
		RotDraw1 = true;
		RotDraw2 = true;
		temp_Matrix = Rot_z_Matrix(temp_Angle);
		MultMatrix1(temp_Matrix, Cuboid_Data);
		MultMatrix2(temp_Matrix, Cuboid_Data2);
		Invalidate();
		UpdateWindow();
		RotDraw1 = false;
		RotDraw2 = false;
		break;
	}
	
}


void CMechanism_HW01View::GetData2(float temp_Angle, int Num)    //Get No.2 Cuboid rotation angle
{
	N = Num;
	vector<vector<double>> temp_Matrix;
	temp_Matrix.resize(4);
	for (int i=0; i<4; i++)
	{
		temp_Matrix[i].resize(4);
	}

	switch(Num)
	{
	case 0:
		RotDraw1 = true;
		RotDraw2 = true;
		temp_Matrix = Rot_x_Matrix(temp_Angle);
		MultMatrix2(temp_Matrix, Cuboid_Data2);
		Invalidate();
		UpdateWindow();
		RotDraw1 = false;
		RotDraw2 = false;
		break;
	case 1:
		RotDraw1 = true;
		RotDraw2 = true;
		temp_Matrix = Rot_y_Matrix(temp_Angle);
		MultMatrix2(temp_Matrix, Cuboid_Data2);
		Invalidate();
		UpdateWindow();
		RotDraw1 = false;
		RotDraw2 = false;
		break;
	case 2:
		RotDraw1 = true;
		RotDraw2 = true;
		temp_Matrix = Rot_z_Matrix(temp_Angle);
		MultMatrix2(temp_Matrix, Cuboid_Data2);
		Invalidate();
		UpdateWindow();
		RotDraw1 = false;
		RotDraw2 = false;
		break;
	}
}

////////////////////////////�w�q����x�}///////////////////////////////
vector<vector<double>> CMechanism_HW01View::Rot_z_Matrix(float theta)
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
vector<vector<double>> CMechanism_HW01View::Rot_y_Matrix(float theta)
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
vector<vector<double>> CMechanism_HW01View::Rot_x_Matrix(float theta)
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
vector<vector<double>> CMechanism_HW01View::Dis_x_Matrix(float length)
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
vector<vector<double>> CMechanism_HW01View::Dis_y_Matrix(float length)
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
vector<vector<double>> CMechanism_HW01View::Dis_z_Matrix(float length)
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
//////////////////////////////////////////////////////////////////////

 void CMechanism_HW01View::MultMatrix1(vector<vector<double>> KineMatrix, vector<CPtInfo> ObjMatrix)
{
	vector<vector<double>> temp_A, temp_C;
	//�ŧi�G��1x4�}�C
	temp_A.resize(4);
	temp_C.resize(4);
	for(int i=0; i<4; i++)
	{
		temp_A[i].resize(8);
		temp_C[i].resize(8);
	}

	for (int i=0; i<4; i++)
	{
		for (int j=0; j<8; j++)
		{
			switch(i)
			{
			case 0:
				temp_A[i][j] = ObjMatrix[j].x;
				break;
			case 1:
				temp_A[i][j] = ObjMatrix[j].y;
				break;
			case 2:
				temp_A[i][j] = ObjMatrix[j].z;
				break;
			case 3:
				temp_A[i][j] = 1;
				break;
			}
		}
	}


	for (int i=0; i<4; i++)
	{
		for (int j=0; j<8; j++)
		{
			temp_C[i][j] = 0;
			for (int k=0; k<4; k++)
			{
				temp_C[i][j] =  temp_C[i][j] + KineMatrix[i][k] * temp_A[k][j];
			}
		}
	}
	
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<8; j++)
		{
			switch(i)
			{
			case 0:
				ObjMatrix[j].x = temp_C[i][j];
				break;
			case 1:
				ObjMatrix[j].y = temp_C[i][j];
				break;
			case 2:
				ObjMatrix[j].z = temp_C[i][j];
				break;
			case 3:
				temp_C[i][j] = 1;
				break;
			}
		}
	}
	Cuboid_Data.assign(ObjMatrix.begin(), ObjMatrix.end());

}
 void CMechanism_HW01View::MultMatrix2(vector<vector<double>> KineMatrix, vector<CPtInfo> ObjMatrix)
 {
	 vector<vector<double>> temp_A, temp_C;
	 //�ŧi�G��1x4�}�C
	 temp_A.resize(4);
	 temp_C.resize(4);
	 for(int i=0; i<4; i++)
	 {
		 temp_A[i].resize(8);
		 temp_C[i].resize(8);
	 }

	 for (int i=0; i<4; i++)
	 {
		 for (int j=0; j<8; j++)
		 {
			 switch(i)
			 {
			 case 0:
				 temp_A[i][j] = ObjMatrix[j].x;
				 break;
			 case 1:
				 temp_A[i][j] = ObjMatrix[j].y;
				 break;
			 case 2:
				 temp_A[i][j] = ObjMatrix[j].z;
				 break;
			 case 3:
				 temp_A[i][j] = 1;
				 break;
			 }
		 }
	 }


	 for (int i=0; i<4; i++)
	 {
		 for (int j=0; j<8; j++)
		 {
			 temp_C[i][j] = 0;
			 for (int k=0; k<4; k++)
			 {
				 temp_C[i][j] =  temp_C[i][j] + KineMatrix[i][k] * temp_A[k][j];
			 }
		 }
	 }

	 for (int i=0; i<4; i++)
	 {
		 for (int j=0; j<8; j++)
		 {
			 switch(i)
			 {
			 case 0:
				 ObjMatrix[j].x = temp_C[i][j];
				 break;
			 case 1:
				 ObjMatrix[j].y = temp_C[i][j];
				 break;
			 case 2:
				 ObjMatrix[j].z = temp_C[i][j];
				 break;
			 case 3:
				 temp_C[i][j] = 1;
				 break;
			 }
		 }
	 }
	 Cuboid_Data2.assign(ObjMatrix.begin(), ObjMatrix.end());

 }

 void CMechanism_HW01View::GetData3(float temp_Displacement, int Num)    //Get No.1 Cuboid Displacement
 {
	 N = Num;
	 vector<vector<double>> temp_Matrix;
	 temp_Matrix.resize(4);
	 for (int i=0; i<4; i++)
	 {
		 temp_Matrix[i].resize(4);
	 }

	 switch(Num)
	 {
	 case 0:
		 DisplaceDraw1 = true;
		 DisplaceDraw2 = true;
		 temp_Matrix = Dis_x_Matrix(temp_Displacement);
		 MultMatrix1(temp_Matrix, Cuboid_Data);
		 MultMatrix2(temp_Matrix, Cuboid_Data2);
		 Invalidate();
		 UpdateWindow();
		 DisplaceDraw1 = false;
		 DisplaceDraw2 = false;
		 break;
	 case 1:
		 DisplaceDraw1 = true;
		 DisplaceDraw2 = true;
		 temp_Matrix = Dis_y_Matrix(temp_Displacement);
		 MultMatrix1(temp_Matrix, Cuboid_Data);
		 MultMatrix2(temp_Matrix, Cuboid_Data2);
		 Invalidate();
		 UpdateWindow();
		 DisplaceDraw1 = false;
		 DisplaceDraw2 = false;
		 break;
	 case 2:
		 DisplaceDraw1 = true;
		 DisplaceDraw2 = true;
		 temp_Matrix = Dis_z_Matrix(temp_Displacement);
		 MultMatrix1(temp_Matrix, Cuboid_Data);
		 MultMatrix2(temp_Matrix, Cuboid_Data2);
		 Invalidate();
		 UpdateWindow();
		 DisplaceDraw1 = false;
		 DisplaceDraw2 = false;
		 break;
	 }
 }

 void CMechanism_HW01View::GetData4(float temp_Displacement, int Num)     //Get No.2 Cuboid Displacement
 {
	 N = Num;
	 vector<vector<double>> temp_Matrix;
	 temp_Matrix.resize(4);
	 for (int i=0; i<4; i++)
	 {
		 temp_Matrix[i].resize(4);
	 }

	 switch(Num)
	 {
	 case 0:
		 DisplaceDraw1 = true;
		 DisplaceDraw2 = true;
		 temp_Matrix = Dis_x_Matrix(temp_Displacement);
		 MultMatrix2(temp_Matrix, Cuboid_Data2);
		 Invalidate();
		 UpdateWindow();
		 DisplaceDraw1 = false;
		 DisplaceDraw2 = false;
		 break;
	 case 1:
		 DisplaceDraw1 = true;
		 DisplaceDraw2 = true;
		 temp_Matrix = Dis_y_Matrix(temp_Displacement);
		 MultMatrix2(temp_Matrix, Cuboid_Data2);
		 Invalidate();
		 UpdateWindow();
		 DisplaceDraw1 = false;
		 DisplaceDraw2 = false;
		 break;
	 case 2:
		 DisplaceDraw1 = true;
		 DisplaceDraw2 = true;
		 temp_Matrix = Dis_z_Matrix(temp_Displacement);
		 MultMatrix2(temp_Matrix, Cuboid_Data2);
		 Invalidate();
		 UpdateWindow();
		 DisplaceDraw1 = false;
		 DisplaceDraw2 = false;
		 break;
	 }
 }

void CMechanism_HW01View::GetScrew_Data(vector<double> temp_Coeff, double temp_phi, int DrawFlag, vector<double> temp_matrix)
 {
	 Screw_Parameter.assign(temp_Coeff.begin(), temp_Coeff.end());
	 phi = temp_phi * 180 / PI;
	 DrawArbitraryLine = true;
	 if (DrawFlag == 0)
	 {
		 Num2LastDraw = true;
	 }
	 Displace_S.assign(temp_matrix.begin(), temp_matrix.end());

	 Invalidate();
	 UpdateWindow();

 }


void CMechanism_HW01View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	switch(nIDEvent)
	{
	case 1:
		phi_incre += 1;
		Displace_S_incre[0] += Displace_S[0] / phi;
		Displace_S_incre[1] += Displace_S[1] / phi;
		Displace_S_incre[2] += Displace_S[2] / phi;
		Invalidate(TRUE);
		break;
	default:
		break;
	}

	CView::OnTimer(nIDEvent);
}




void CMechanism_HW01View::AnimateCheck(void)
{
	SetTimer(1, 10, NULL);

	ExecuteFlag = true;
	FinalDraw = false;
}
