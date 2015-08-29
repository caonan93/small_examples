
// StateGridSysDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StateGridSys.h"
#include "StateGridSysDlg.h"
#include "afxdialogex.h"
#include "Main.h"
#include "WorkRecord.h"
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


// CStateGridSysDlg 对话框



CStateGridSysDlg::CStateGridSysDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStateGridSysDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStateGridSysDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_sUserInput);
	DDX_Control(pDX, IDC_EDIT2, m_sPassWd);
}

BEGIN_MESSAGE_MAP(CStateGridSysDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CStateGridSysDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CStateGridSysDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CStateGridSysDlg 消息处理程序

BOOL CStateGridSysDlg::OnInitDialog()
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CStateGridSysDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CStateGridSysDlg::OnPaint()
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
HCURSOR CStateGridSysDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CStateGridSysDlg::OnBnClickedButton1()
{
	//确定
	CStringArray arrData;
	int nShowNum = 5;
	CString column[] = {_T("PASSWD_ID"),_T("USER_NAME"),_T("PASSWD_USER"),_T("CLASSID"),_T("WORDERID")};
	
	
	
	CString userInput,userpasswd;
	m_sUserInput.GetWindowText(userInput);
	m_sPassWd.GetWindowText(userpasswd);

	CString sql = _T("select * from PASSWD where USER_NAME = '")  \
		+ userInput + _T("' and PASSWD_USER = '") + userpasswd + _T("'");

	
	
	UINT nRes;
	if (userInput == _T("user") && userpasswd == _T("user0102") || userInput == _T("pdgq") && userpasswd == _T("pdgq012345"))
	{
		CMain amd/*(this)*/;
		ShowWindow(SW_HIDE);
		theApp.m_pMainWnd = &amd;
		
		nRes = amd.DoModal();
		
	}
	else 
	{
		if (!theApp.m_database.GetData(sql, column, nShowNum, arrData))
		{
			MessageBox(_T("获取用户数据库失败"));
			return;
		}

		if (arrData.IsEmpty())
		{
			MessageBox(_T("用户名或密码不正确！"));
			m_sUserInput.SetWindowText(_T(""));
			m_sPassWd.SetWindowText(_T(""));
			return;
		}

		CString classID = arrData.GetAt(3);
		
		CWorkRecord userLog;
		userLog.GetData(classID);			
		ShowWindow(SW_HIDE);
		theApp.m_pMainWnd = &userLog;
		nRes = userLog.DoModal();
	}

	if (IDCANCEL == nRes)
	{
		OnCancel();
		//DestroyWindow();
	}
	if (nRes == IDOK)
	{
		//CStateGridSysDlg dlg;
		//theApp.m_pMainWnd = this;//##切换用户不显示
		ShowWindow(SW_SHOW);	
	}
}


void CStateGridSysDlg::OnBnClickedButton2()
{
	// 取消
	OnCancel();
}
