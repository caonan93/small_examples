// Main.cpp : 实现文件
//

#include "stdafx.h"
#include "StateGridSys.h"
#include "Main.h"
#include "afxdialogex.h"
#include "AmdUser.h"
#include "AmdClass.h"
#include "SysCar.h"
#include "SysOperate.h"
#include "StatisticPer.h"
#include "StatisticClass.h"
#include "AmdDriver.h"
// CMain 对话框

IMPLEMENT_DYNAMIC(CMain, CDialogEx)

CMain::CMain(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMain::IDD, pParent)
{
	m_pDlgNew = NULL;
	m_CwndParent = pParent;
}

CMain::~CMain()
{
}

void CMain::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMain, CDialogEx)
	ON_COMMAND_RANGE(IDM_AMID_LOG, IDM_AMID_TAB, &CMain::onBasicMenu)
	ON_COMMAND_RANGE(IDM_SYS_CAR, IDM_SYS_CLASS, &CMain::onBasicMenu2)
	ON_COMMAND_RANGE(IDM_STATISC_CLASS, IDM_STATISC_PERSON, &CMain::onBasicMenu3)

	ON_COMMAND(IDM_AMID_DRIVER, &CMain::OnAmidDriver)
END_MESSAGE_MAP()


// CMain 消息处理程序
void CMain::onBasicMenu(UINT uid)
{
	DestroyChildWindow();
	switch (uid)
	{
		case IDM_AMID_LOG:
		{
			m_pDlgNew = new CAmdUser;
			m_pDlgNew->Create(ID_AMID_USER, this);
			m_pDlgNew->ShowWindow(SW_SHOW);
		}
			break;
		case IDM_AMID_CLASS:
		{
			m_pDlgNew = new CAmdClass;
			m_pDlgNew->Create(ID_AMID_CLASS, this);
			m_pDlgNew->ShowWindow(SW_SHOW);
		}
			break;
		case IDM_AMID_TAB:
		{
			DestroyChildWindow();
			theApp.m_pMainWnd = m_CwndParent;
			OnOK();
		}
			break;
	}
}
void CMain::onBasicMenu2(UINT uid)
{
	DestroyChildWindow();
	switch (uid)
	{
		case IDM_SYS_CAR:
		{
			m_pDlgNew = new CSysCar;
			m_pDlgNew->Create(ID_SYS_CAR, this);
			m_pDlgNew->ShowWindow(SW_SHOW);
		}
			break;
		case IDM_SYS_CLASS:
		{
			m_pDlgNew = new CSysOperate;
			m_pDlgNew->Create(ID_SYS_OPERTECLASS, this);
			m_pDlgNew->ShowWindow(SW_SHOW);
		}
			break;
	}
}
void CMain::onBasicMenu3(UINT uid)
{
	DestroyChildWindow();
	switch (uid)
	{
	case IDM_STATISC_CLASS:
	{
		m_pDlgNew = new CStatisticClass;
		m_pDlgNew->Create(ID_STATISTIC_CLASS, this);
		m_pDlgNew->ShowWindow(SW_SHOW);
	}
		break;
	case IDM_STATISC_PERSON:
	{
		m_pDlgNew = new CStatisticPer;
		m_pDlgNew->Create(ID_STATISTIC_PERSON, this);
		m_pDlgNew->ShowWindow(SW_SHOW);
	}
		break;
	}
}
void CMain::DestroyChildWindow()
{
	if (m_pDlgNew)
	{
		if (::IsWindow(m_pDlgNew->m_hWnd))
		{
			m_pDlgNew->PostMessage(WM_CLOSE);
		}

	}
}

void CMain::OnAmidDriver()
{
	//driver
	CAmdDriver dlg;
	dlg.DoModal();
}
