// MainDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "�ڴ�����㷨.h"
#include "MainDialog.h"
#include "afxdialogex.h"


// CMainDialog �Ի���

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


// CMainDialog ��Ϣ�������
