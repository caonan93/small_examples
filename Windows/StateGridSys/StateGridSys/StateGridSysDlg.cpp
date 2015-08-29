
// StateGridSysDlg.cpp : ʵ���ļ�
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


// CStateGridSysDlg �Ի���



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


// CStateGridSysDlg ��Ϣ�������

BOOL CStateGridSysDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CStateGridSysDlg::OnPaint()
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
HCURSOR CStateGridSysDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CStateGridSysDlg::OnBnClickedButton1()
{
	//ȷ��
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
			MessageBox(_T("��ȡ�û����ݿ�ʧ��"));
			return;
		}

		if (arrData.IsEmpty())
		{
			MessageBox(_T("�û��������벻��ȷ��"));
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
		//theApp.m_pMainWnd = this;//##�л��û�����ʾ
		ShowWindow(SW_SHOW);	
	}
}


void CStateGridSysDlg::OnBnClickedButton2()
{
	// ȡ��
	OnCancel();
}
