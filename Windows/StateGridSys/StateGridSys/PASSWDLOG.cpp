// PASSWDLOG.cpp : 实现文件
//

#include "stdafx.h"
#include "StateGridSys.h"
#include "PASSWDLOG.h"
#include "afxdialogex.h"


// CPASSWDLOG 对话框

IMPLEMENT_DYNAMIC(CPASSWDLOG, CDialogEx)

CPASSWDLOG::CPASSWDLOG(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPASSWDLOG::IDD, pParent)
{
	m_stringData = _T("");
	m_stringWorkID = _T("");
	m_ClassID = -1;
}

CPASSWDLOG::~CPASSWDLOG()
{
}

void CPASSWDLOG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT10, m_edShow);
	DDX_Control(pDX, IDC_EDIT1, m_edUserLogIn);
	DDX_Control(pDX, IDC_EDIT2, m_edPassWD);
	DDX_Control(pDX, IDC_EDIT9, m_edPassWDReapt);
}


BEGIN_MESSAGE_MAP(CPASSWDLOG, CDialogEx)
	//ON_MESSAGE(WM_MYGETMESSAGE, &CPASSWDLOG::GetPassWDMessage)
	ON_BN_CLICKED(IDC_BUTTON2, &CPASSWDLOG::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CPASSWDLOG::OnBnClickedButton4)
END_MESSAGE_MAP()


BOOL CPASSWDLOG::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	InitDialog();
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CPASSWDLOG::InitDialog()
{
	m_edShow.SetWindowText(m_stringData);
}
void CPASSWDLOG::GetStringData(CString &stringData,CString &stringWorkID, int key)
{
	m_stringData = stringData;
	m_stringWorkID = stringWorkID;
	m_ClassID = key;
}

void CPASSWDLOG::OnBnClickedButton2()
{
	//保存
	CStringArray strAddData;
	CString temp;
	CString temp1;
	//PASSWD_ID
	strAddData.Add(_T(" "));
	//USER_NAME
	m_edUserLogIn.GetWindowText(temp);
	strAddData.Add(temp);
	
	m_edPassWD.GetWindowText(temp1);
	if (temp == _T("") || temp1 == _T(""))
	{
		MessageBox(_T("用户名/密码 不能为空！"));
		return;
	}

	m_edPassWDReapt.GetWindowText(temp);
	
	if (temp != temp1)
	{
		MessageBox(_T("两次输入的密码不一致！"));
		m_edUserLogIn.SetWindowText(_T(""));
		m_edPassWD.SetWindowText(_T(""));
		m_edPassWDReapt.SetWindowText(_T(""));
		return;
	}
	//PASSWD_USER
	strAddData.Add(temp);

	//classID
	temp.Format(_T("%d"), m_ClassID);
	strAddData.Add(temp);
	//WORKID
	strAddData.Add(m_stringWorkID);
	CString column[] = { _T("PASSWD_ID"), _T("USER_NAME"), _T("PASSWD_USER"), _T("CLASSID"), _T("WORDERID") };
	int insertnum = 5;
	theApp.m_database.AddData(_T("PASSWD"), strAddData, insertnum, column);
	OnOK();
}


void CPASSWDLOG::OnBnClickedButton4()
{
	//取消
	OnCancel();
}


