
// FloppyDeuce.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CFloppyDeuceApp:
// О реализации данного класса см. FloppyDeuce.cpp
//

class CFloppyDeuceApp : public CWinApp
{
public:
	CFloppyDeuceApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CFloppyDeuceApp theApp;