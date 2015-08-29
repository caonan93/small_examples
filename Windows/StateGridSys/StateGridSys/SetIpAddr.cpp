// SetIpAddr.cpp : 实现文件
//

#include "stdafx.h"
#include "StateGridSys.h"
#include "SetIpAddr.h"
#include "afxdialogex.h"


// CSetIpAddr 对话框

IMPLEMENT_DYNAMIC(CSetIpAddr, CDialogEx)

CSetIpAddr::CSetIpAddr(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetIpAddr::IDD, pParent)
{

}

CSetIpAddr::~CSetIpAddr()
{
}

void CSetIpAddr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_SetAddress);
	DDX_Control(pDX, IDC_EDIT2, m_edUserName);
	DDX_Control(pDX, IDC_EDIT1, m_edPassWD);
	DDX_Control(pDX, IDC_EDIT9, m_edPort);
}


BEGIN_MESSAGE_MAP(CSetIpAddr, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CSetIpAddr::OnBnClickedButton2)
END_MESSAGE_MAP()


// CSetIpAddr 消息处理程序


void CSetIpAddr::OnBnClickedButton2()
{
	//保存

}
