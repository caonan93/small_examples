// PASSWDLOG.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StateGridSys.h"
#include "PASSWDLOG.h"
#include "afxdialogex.h"


// CPASSWDLOG �Ի���

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
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
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
	//����
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
		MessageBox(_T("�û���/���� ����Ϊ�գ�"));
		return;
	}

	m_edPassWDReapt.GetWindowText(temp);
	
	if (temp != temp1)
	{
		MessageBox(_T("������������벻һ�£�"));
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
	//ȡ��
	OnCancel();
}


