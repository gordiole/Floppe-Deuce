
// FloppyDeuceDlg.cpp : ���� ����������
//

#include "stdafx.h"
#include "FloppyDeuce.h"
#include "FloppyDeuceDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���������� ���� CFloppyDeuceDlg



CFloppyDeuceDlg::CFloppyDeuceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFloppyDeuceDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFloppyDeuceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_COM, m_pComboBox_COM);
	DDX_Control(pDX, IDC_STATIC_STATUS, m_pCStatic_Status);
	DDX_Control(pDX, IDC_STATIC_RATE, m_pCStatic_Rate);
}

BEGIN_MESSAGE_MAP(CFloppyDeuceDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_RATE, &CFloppyDeuceDlg::OnBnClickedButtonRate)
END_MESSAGE_MAP()


// ����������� ��������� CFloppyDeuceDlg

BOOL CFloppyDeuceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ������ ������ ��� ����� ����������� ����. ����� ������ ��� �������������,
	//  ���� ������� ���� ���������� �� �������� ����������
	SetIcon(m_hIcon, TRUE);			// ������� ������
	SetIcon(m_hIcon, FALSE);		// ������ ������

	ShowWindow(SW_SHOWNORMAL);

	// �������������� Static
	m_pCStatic_Rate.SetWindowTextW(_T(""));
	m_pCStatic_Status.SetWindowTextW(_T(""));

	// ������� ������ COM ������ � ComboBox
	m_pComboBox_COM.ResetContent();

	// ��������� ��� COM �����
	for (UINT i = 1; i < 256; i++)
	{
		// ��������� ��� COM �����
		CString sPort;
		sPort.Format(_T("\\\\.\\COM%d"), i);

		// ������� ������� COM ����
		BOOL bSuccess = FALSE;
		HANDLE hCOM = CreateFile(sPort, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
		// COM ���� ������ ?
		if (hCOM == INVALID_HANDLE_VALUE)
		{
			// �������� ��������� ��� ������
			DWORD dwError = GetLastError();

			if (dwError == ERROR_ACCESS_DENIED || dwError == ERROR_GEN_FAILURE || dwError == ERROR_SHARING_VIOLATION || dwError == ERROR_SEM_TIMEOUT)
			{
				// ���� ��������
				bSuccess = TRUE;
			}
		}
		else
		{
			// ���� ��������
			bSuccess = TRUE;
		}
		if (bSuccess)
		{
			// ��������� � ComboBox ��������� COM ����
			sPort.Format(_T("COM%d"), i);
			m_pComboBox_COM.AddString(sPort);

			// ��������� �������� COM ����
			CloseHandle(hCOM);		

		}
	}

	// TODO: �������� �������������� �������������

	return TRUE;  // ������� �������� TRUE, ���� ����� �� ������� �������� ����������
}

// ��� ���������� ������ ����������� � ���������� ���� ����� ��������������� ����������� ���� �����,
//  ����� ���������� ������. ��� ���������� MFC, ������������ ������ ���������� ��� �������������,
//  ��� ������������� ����������� ������� ��������.

void CFloppyDeuceDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �������� ���������� ��� ���������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ������������ ������ �� ������ ����������� ��������������
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ��������� ������
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ������� �������� ��� ������� ��� ��������� ����������� ������� ��� �����������
//  ���������� ����.
HCURSOR CFloppyDeuceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFloppyDeuceDlg::OnBnClickedButtonRate()
{
	CString sRate;
	CString sStatus;
	CString sPort;
	LARGE_INTEGER timerFrequency, timerStart, timerStop;

	sStatus = "";
	sRate = "";

	m_pCStatic_Rate.SetWindowTextW(sRate);
	m_pCStatic_Status.SetWindowTextW(sStatus);

	// �������� ����� ���������� COM ����� �� ComboBox
	int NumCOM = m_pComboBox_COM.GetCurSel();
	// COM ���� ������ ?
	if (NumCOM == CB_ERR)
	{
		return;
	}

	// ��������� ��� COM �����
	m_pComboBox_COM.GetLBText(NumCOM, sStatus);
	sPort.Format(_T("\\\\.\\" + sStatus));

	// ����� COM �����
	HANDLE hFile = CreateFile(
		sPort,
		GENERIC_READ|GENERIC_WRITE,
		0,
		0,
		OPEN_EXISTING,
		FILE_FLAG_OVERLAPPED,
		0);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		COMMTIMEOUTS CTO;
		BOOL bRet;

		bRet = GetCommTimeouts(hFile, &CTO);
		if (!bRet)
		{
			sStatus = "Get COM Timeouts error";
			m_pCStatic_Status.SetWindowTextW(sStatus);
		}

		CTO.ReadIntervalTimeout = 5000; 
		CTO.ReadTotalTimeoutMultiplier = 2; 
		CTO.ReadTotalTimeoutConstant = 10; 
		CTO.WriteTotalTimeoutMultiplier = 50; 
		CTO.WriteTotalTimeoutConstant = 500; 

		bRet=SetCommTimeouts(hFile, &CTO);
		if (!bRet)
		{
			sStatus = "Set COM Timeouts error";
			m_pCStatic_Status.SetWindowTextW(sStatus);
		}

		unsigned char WBuf[512];
		unsigned char RBuf[512];
		unsigned long Offs=0;
		DWORD dwBytesWritten;
		unsigned char BlockNum;
		unsigned char BlockItem;

		OVERLAPPED ovRx;
		OVERLAPPED ovTx;
		DWORD LastError;

		QueryPerformanceFrequency(&timerFrequency);
		QueryPerformanceCounter(&timerStart);

		for (int i = 0; i < 256; i++)
		{
			BlockNum = (unsigned char)i;
			WBuf[0] = 0;
			WBuf[1] = 0;
			WBuf[2] = 0;
			WBuf[3] = BlockNum;

			ZeroMemory(&ovTx, sizeof(ovTx));
			ovTx.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

			bRet = WriteFile(hFile, WBuf, 4, &dwBytesWritten, &ovTx);
			if (!bRet)
			{
				LastError = GetLastError();

				if (LastError == ERROR_IO_PENDING)
				{
					DWORD wRet = WaitForSingleObject(ovTx.hEvent, 10000);
					if (wRet != WAIT_OBJECT_0)
					{
						sStatus = "Write timeouts error";
						m_pCStatic_Status.SetWindowTextW(sStatus);
						return;
					}

					bRet = GetOverlappedResult(hFile, &ovTx, &dwBytesWritten, FALSE);
					if (!bRet)
					{
						sStatus = "Write error";
						m_pCStatic_Status.SetWindowTextW(sStatus);
						return;
					}
				}
				else
				{
					sStatus.Format(_T("Write error code %x4"), LastError);
					m_pCStatic_Status.SetWindowTextW(sStatus);
					return;
				}
			}

			ZeroMemory(&ovRx, sizeof(ovRx));
			ovRx.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

			bRet = ReadFile(hFile, RBuf, 512, &Offs,  &ovRx);
			if (!bRet)
			{
				LastError = GetLastError();

				if (LastError == ERROR_IO_PENDING)
				{
					DWORD wRet = WaitForSingleObject(ovRx.hEvent, 10000);
					if (wRet != WAIT_OBJECT_0)
					{
						if (wRet == WAIT_TIMEOUT)
						{
							sStatus = "Read error: WAIT_TIMEOUT";
							m_pCStatic_Status.SetWindowTextW(sStatus);
							return;
						}
						else if (wRet == WAIT_ABANDONED)
						{
							sStatus = "Read error: WAIT_ABANDONED";
							m_pCStatic_Status.SetWindowTextW(sStatus);
							return;
						}
						else
						{
							sStatus = "Read error: WAIT_FAILED";
							m_pCStatic_Status.SetWindowTextW(sStatus);
							return;
						}
					}

					bRet = GetOverlappedResult(hFile, &ovRx, &Offs, FALSE);
					if (!bRet)
					{
						sStatus = "Read error: ERROR_IO_INCOMPLETE";
						m_pCStatic_Status.SetWindowTextW(sStatus);
						return;
					}
				}
				else
				{
					sStatus.Format(_T("Read error: Code %x4"), LastError);
					m_pCStatic_Status.SetWindowTextW(sStatus);
					return;
				}
			}

			// ��������� �������� ����
			for (int x = 0; x < 512; x++)
			{
				BlockItem = *(RBuf+x);

				if (BlockItem != BlockNum)
				{
					sStatus = "Read block error";
					m_pCStatic_Status.SetWindowTextW(sStatus);
					CloseHandle(hFile);
					return;
				}
			}
		}

	    QueryPerformanceCounter(&timerStop);

		double t( static_cast<double>( timerStop.QuadPart - timerStart.QuadPart ) / timerFrequency.QuadPart);

		double Rate = (256 * 512 / 1024) / t;

		sRate.Format(_T("%g kB/s"), Rate);
		m_pCStatic_Rate.SetWindowTextW(sRate);
	}
	else
	{
		sStatus = "Not open COM port";
		m_pCStatic_Status.SetWindowTextW(sStatus);
	}

	// ��������� COM ����
	CloseHandle(hFile);		
}
