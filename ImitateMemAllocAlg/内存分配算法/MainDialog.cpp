// MainDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "内存分配算法.h"
#include "MainDialog.h"
#include "afxdialogex.h"


// CMainDialog 对话框

IMPLEMENT_DYNAMIC(CMainDialog, CDialogEx)

CMainDialog::CMainDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainDialog::IDD, pParent)
{

}

CMainDialog::~CMainDialog()
{
}

void CMainDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMainDialog, CDialogEx)
END_MESSAGE_MAP()


// CMainDialog 消息处理程序
