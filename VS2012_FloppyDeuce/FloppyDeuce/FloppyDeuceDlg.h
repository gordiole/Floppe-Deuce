
// FloppyDeuceDlg.h : ���� ���������
//

#pragma once
#include "afxwin.h"


// ���������� ���� CFloppyDeuceDlg
class CFloppyDeuceDlg : public CDialogEx
{
// ��������
public:
	CFloppyDeuceDlg(CWnd* pParent = NULL);	// ����������� �����������

// ������ ����������� ����
	enum { IDD = IDD_FLOPPYDEUCE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV


// ����������
protected:
	HICON m_hIcon;

	// ��������� ������� ����� ���������
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
