
// FloppyDeuce.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CFloppyDeuceApp:
// � ���������� ������� ������ ��. FloppyDeuce.cpp
//

class CFloppyDeuceApp : public CWinApp
{
public:
	CFloppyDeuceApp();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CFloppyDeuceApp theApp;