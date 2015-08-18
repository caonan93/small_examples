
// WinProcessManagerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WinProcessManager.h"
#include "WinProcessManagerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMyWinProcessManagerDlg 对话框




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


// CMyWinProcessManagerDlg 消息处理程序

BOOL CMyWinProcessManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//左边listctrl初始化
	CRect rectlist;
	m_ListctrlLeft.GetClientRect(&rectlist);
	float widlist = rectlist.Width()/3;
	m_ListctrlLeft.InsertColumn(0,_T("名称"),LVCFMT_LEFT,widlist);
	m_ListctrlLeft.InsertColumn(1,_T("PID"),LVCFMT_LEFT,widlist);
	m_ListctrlLeft.InsertColumn(2,_T("路径"),LVCFMT_LEFT,widlist);
	m_ListctrlLeft.SetExtendedStyle(LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES );

	m_listctrRight.GetClientRect(&rectlist);
    widlist = rectlist.Width()/3;
	m_listctrRight.InsertColumn(0,_T("序号"),LVCFMT_LEFT,widlist);
	m_listctrRight.InsertColumn(1,_T("地址"),LVCFMT_LEFT,widlist);
	m_listctrRight.InsertColumn(2,_T("大小"),LVCFMT_LEFT,widlist);
	m_listctrRight.SetExtendedStyle(LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES );


	GetDlgItem(IDC_STATICRIGHT)->GetClientRect(&m_smallrect);
	GetWindowRect(&m_bigrect);
	SetWindowPos(NULL,0,0,m_bigrect.Width()-m_smallrect.Width(),m_bigrect.Height(),SWP_NOMOVE);

	showprocesslist();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyWinProcessManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMyWinProcessManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyWinProcessManagerDlg::OnBnClickedExit()
{
	//退出
	PostQuitMessage(0);
}


void CMyWinProcessManagerDlg::OnBnClickedModify()
{
	//修改内存
	static bool bflag = TRUE;
	if (bflag)
	{
		//显示
		GetDlgItem(IDC_MODIFY)->SetWindowText(_T("恢复"));
		SetTimer(10,10,NULL);
		SetWindowPos(NULL,0,0,(m_bigrect.Width()-m_smallrect.Width()),m_bigrect.Height(),SWP_NOMOVE);
	}
	else
	{
		//隐藏
		GetDlgItem(IDC_MODIFY)->SetWindowText(_T("修改内存"));
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
		MessageBox(_T("创建失败"));
	}
	BOOL bHasprocess = Process32First(hSnapShot,&pe);
	TCHAR buffer[MAX_PATH] = {0};
	CString strpath;
	while (bHasprocess)
	{
		
		//路径
			//通过id获得当前句柄
		HANDLE hCurrent = OpenProcess(PROCESS_VM_READ|PROCESS_QUERY_INFORMATION,FALSE,pe.th32ParentProcessID);
			//通过GetModuleFileNameEx()获得路径
		if (hCurrent)
		{
			GetModuleFileNameEx(hCurrent,NULL,buffer,MAX_PATH);
			m_ListctrlLeft.SetItemText(0,2,buffer);

			//名称
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
	// 获得鼠标左键单击的进程焦点
	LPNMITEMACTIVATE pnmclick = (LPNMITEMACTIVATE )pNMHDR;
	m_nitem = pnmclick->iItem;
	CString str = m_ListctrlLeft.GetItemText(m_nitem,1);
	m_rightmodify.SetWindowText(str);
	m_dwProcess = _ttoi(str);

	*pResult = 0;
}


void CMyWinProcessManagerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	// 关闭进程
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
	//刷新
	showprocesslist();
}


void CMyWinProcessManagerDlg::OnBnClickedSerach()
{
	//搜索
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
		//序号
		str.Format(_T("%d"),i++);
		m_listctrRight.InsertItem(0,str);
		//放入地址
		
		str.Format(_T("%p"),m_listright.GetHead()->address);
		
		m_listctrRight.SetItemText(0,1,str);
		//放入大小
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
		//遍历缓冲区
		//一个字节值大小遍历
		byte *p = NULL;
		for (DWORD i = 0;i<4*K;i++)
		{
			p = (byte *)(szbuf+i);
			if (*p == value)
			{
				m_listright.AddNode(addreass,1);
			}
		}

		//2个字节值遍历
		short *ps = NULL;
		for (DWORD i = 0;i<4*K-1;i++)
		{
			ps = (short *)(szbuf+i);
			if (*ps == value)
			{
				m_listright.AddNode(addreass,2);
			}
		}
		//4个
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