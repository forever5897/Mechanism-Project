
// Mechanism_HW01.h : Mechanism_HW01 ���ε{�����D���Y��
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"       // �D�n�Ÿ�


// CMechanism_HW01App:
// �аѾ\��@�����O�� Mechanism_HW01.cpp
//

class CMechanism_HW01App : public CWinApp
{
public:
	CMechanism_HW01App();


// �мg
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �{���X��@
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMechanism_HW01App theApp;
