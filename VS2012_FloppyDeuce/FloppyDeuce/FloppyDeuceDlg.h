
// FloppyDeuceDlg.h : файл заголовка
//

#pragma once
#include "afxwin.h"


// диалоговое окно CFloppyDeuceDlg
class CFloppyDeuceDlg : public CDialogEx
{
// Создание
public:
	CFloppyDeuceDlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
	enum { IDD = IDD_FLOPPYDEUCE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonRate();
	CComboBox m_pComboBox_COM;
	CStatic m_pCStatic_Status;
	CStatic m_pCStatic_Rate;
};
