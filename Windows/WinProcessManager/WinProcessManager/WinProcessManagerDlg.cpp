
// WinProcessManagerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WinProcessManager.h"
#include "WinProcessManagerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyWinProcessManagerDlg �Ի���




CMyWinProcessManagerDlg::CMyWinProcessManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyWinProcessManagerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_dwProcess = 0;
	m_isFirst = true;
}

void CMyWinProcessManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListctrlLeft);
	DDX_Control(pDX, IDC_LIST3, m_listctrRight);
	DDX_Control(pDX, IDC_EDIT2, m_rightmodify);
	DDX_Control(pDX, IDC_EDIT3, m_value);
}

BEGIN_MESSAGE_MAP(CMyWinProcessManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EXIT, &CMyWinProcessManagerDlg::OnBnClickedExit)
	ON_BN_CLICKED(IDC_MODIFY, &CMyWinProcessManagerDlg::OnBnClickedModify)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CMyWinProcessManagerDlg::OnNMClickList1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CLOSETHREAD, &CMyWinProcessManagerDlg::OnBnClickedClosethread)
	ON_BN_CLICKED(IDC_REFRESH, &CMyWinProcessManagerDlg::OnBnClickedRefresh)
	ON_BN_CLICKED(IDC_SERACH, &CMyWinProcessManagerDlg::OnBnClickedSerach)
END_MESSAGE_MAP()


// CMyWinProcessManagerDlg ��Ϣ�������

BOOL CMyWinProcessManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//���listctrl��ʼ��
	CRect rectlist;
	m_ListctrlLeft.GetClientRect(&rectlist);
	float widlist = rectlist.Width()/3;
	m_ListctrlLeft.InsertColumn(0,_T("����"),LVCFMT_LEFT,widlist);
	m_ListctrlLeft.InsertColumn(1,_T("PID"),LVCFMT_LEFT,widlist);
	m_ListctrlLeft.InsertColumn(2,_T("·��"),LVCFMT_LEFT,widlist);
	m_ListctrlLeft.SetExtendedStyle(LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES );

	m_listctrRight.GetClientRect(&rectlist);
    widlist = rectlist.Width()/3;
	m_listctrRight.InsertColumn(0,_T("���"),LVCFMT_LEFT,widlist);
	m_listctrRight.InsertColumn(1,_T("��ַ"),LVCFMT_LEFT,widlist);
	m_listctrRight.InsertColumn(2,_T("��С"),LVCFMT_LEFT,widlist);
	m_listctrRight.SetExtendedStyle(LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES );


	GetDlgItem(IDC_STATICRIGHT)->GetClientRect(&m_smallrect);
	GetWindowRect(&m_bigrect);
	SetWindowPos(NULL,0,0,m_bigrect.Width()-m_smallrect.Width(),m_bigrect.Height(),SWP_NOMOVE);

	showprocesslist();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMyWinProcessManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMyWinProcessManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMyWinProcessManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyWinProcessManagerDlg::OnBnClickedExit()
{
	//�˳�
	PostQuitMessage(0);
}


void CMyWinProcessManagerDlg::OnBnClickedModify()
{
	//�޸��ڴ�
	static bool bflag = TRUE;
	if (bflag)
	{
		//��ʾ
		GetDlgItem(IDC_MODIFY)->SetWindowText(_T("�ָ�"));
		SetTimer(10,10,NULL);
		SetWindowPos(NULL,0,0,(m_bigrect.Width()-m_smallrect.Width()),m_bigrect.Height(),SWP_NOMOVE);
	}
	else
	{
		//����
		GetDlgItem(IDC_MODIFY)->SetWindowText(_T("�޸��ڴ�"));
		SetWindowPos(NULL,0,0,m_bigrect.Width()-m_smallrect.Width(),m_bigrect.Height(),SWP_NOMOVE);
	}
	bflag = !bflag;
}

void CMyWinProcessManagerDlg::showprocesslist()
{
	m_ListctrlLeft.DeleteAllItems();
	PROCESSENTRY32 pe = {sizeof(PROCESSENTRY32)};
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if (hSnapShot == INVALID_HANDLE_VALUE)
	{
		MessageBox(_T("����ʧ��"));
	}
	BOOL bHasprocess = Process32First(hSnapShot,&pe);
	TCHAR buffer[MAX_PATH] = {0};
	CString strpath;
	while (bHasprocess)
	{
		
		//·��
			//ͨ��id��õ�ǰ���
		HANDLE hCurrent = OpenProcess(PROCESS_VM_READ|PROCESS_QUERY_INFORMATION,FALSE,pe.th32ParentProcessID);
			//ͨ��GetModuleFileNameEx()���·��
		if (hCurrent)
		{
			GetModuleFileNameEx(hCurrent,NULL,buffer,MAX_PATH);
			m_ListctrlLeft.SetItemText(0,2,buffer);

			//����
			m_ListctrlLeft.InsertItem(0,pe.szExeFile);
			//id
			CString str;
			str.Format(_T("%d"),pe.th32ParentProcessID);
			m_ListctrlLeft.SetItemText(0,1,str);
		}
		
		bHasprocess = Process32Next(hSnapShot,&pe);
	}
}

void CMyWinProcessManagerDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// ��������������Ľ��̽���
	LPNMITEMACTIVATE pnmclick = (LPNMITEMACTIVATE )pNMHDR;
	m_nitem = pnmclick->iItem;
	CString str = m_ListctrlLeft.GetItemText(m_nitem,1);
	m_rightmodify.SetWindowText(str);
	m_dwProcess = _ttoi(str);

	*pResult = 0;
}


void CMyWinProcessManagerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect rect;
	GetWindowRect(&rect);
	if (rect.Width() < m_bigrect.Width())
	{
		SetWindowPos(NULL,0,0,rect.Width()+50,m_bigrect.Height(),SWP_NOMOVE);

	}
	else
	{
		KillTimer(10);
		SetWindowPos(NULL,0,0,m_bigrect.Width(),m_bigrect.Height(),SWP_NOMOVE);
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CMyWinProcessManagerDlg::OnBnClickedClosethread()
{
	// �رս���
	if (m_dwProcess)
	{
		HANDLE hClose = OpenProcess(PROCESS_TERMINATE,FALSE,m_dwProcess);
		if (TerminateProcess(hClose,-1))
		{
			CloseHandle(hClose);
			hClose = NULL;
			Sleep(100);
			showprocesslist();
		}		
		
	}
}


void CMyWinProcessManagerDlg::OnBnClickedRefresh()
{
	//ˢ��
	showprocesslist();
}


void CMyWinProcessManagerDlg::OnBnClickedSerach()
{
	//����
	if (m_isFirst)
	{
		m_isFirst = !m_isFirst;
		FindFirst();

	}
	else
	{
		FindNext();
	}
	int i = 0;
	
	while (m_listright.GetHead())
	{
		CString str;
		//���
		str.Format(_T("%d"),i++);
		m_listctrRight.InsertItem(0,str);
		//�����ַ
		
		str.Format(_T("%p"),m_listright.GetHead()->address);
		
		m_listctrRight.SetItemText(0,1,str);
		//�����С
		str.Format(_T("%d"),m_listright.GetHead()->size);
		m_listctrRight.SetItemText(0,2,str);

		m_listright.GetNext();
	}
}

void CMyWinProcessManagerDlg::FindFirst()
{
	CString str = NULL;
	GetDlgItem(IDC_EDIT3)->GetWindowTextW(str);
	if (str)
	{
		int value = _ttoi(str);
		if (value)
		{
			for (DWORD i = 64*K;i < 2*G;i += 4*K)
			{
				FindOpenPage(i,value);
			}
		}		
	}	
}

void CMyWinProcessManagerDlg::FindOpenPage(DWORD addreass,const int value)
{
	byte szbuf[4*K] = {0};
	HANDLE hModify = OpenProcess(PROCESS_VM_READ|PROCESS_QUERY_INFORMATION,FALSE,m_dwProcess);
	
	if (ReadProcessMemory(hModify,(LPVOID)addreass,szbuf,4*K,NULL))
	{
		//����������
		//һ���ֽ�ֵ��С����
		byte *p = NULL;
		for (DWORD i = 0;i<4*K;i++)
		{
			p = (byte *)(szbuf+i);
			if (*p == value)
			{
				m_listright.AddNode(addreass,1);
			}
		}

		//2���ֽ�ֵ����
		short *ps = NULL;
		for (DWORD i = 0;i<4*K-1;i++)
		{
			ps = (short *)(szbuf+i);
			if (*ps == value)
			{
				m_listright.AddNode(addreass,2);
			}
		}
		//4��
		int *pint = NULL;
		for (DWORD i = 0;i<4*K-3;i++)
		{
			pint = (int *)(szbuf+i);
			if (*pint == value)
			{
				m_listright.AddNode(addreass,4);
			}
		}
	}	
	
}

void CMyWinProcessManagerDlg::FindNext()
{

}