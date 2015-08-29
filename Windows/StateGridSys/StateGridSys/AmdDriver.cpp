// AmdDriver.cpp : 实现文件
//

#include "stdafx.h"
#include "StateGridSys.h"
#include "AmdDriver.h"
#include "afxdialogex.h"


// CAmdDriver 对话框

IMPLEMENT_DYNAMIC(CAmdDriver, CDialogEx)

CAmdDriver::CAmdDriver(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAmdDriver::IDD, pParent)
{

}

CAmdDriver::~CAmdDriver()
{
}

void CAmdDriver::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listInfo);
	DDX_Control(pDX, IDC_EDIT1, m_edName);
}


BEGIN_MESSAGE_MAP(CAmdDriver, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAmdDriver::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAmdDriver::OnBnClickedButton2)
END_MESSAGE_MAP()

BOOL CAmdDriver::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitDialog();
	Search();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
// CAmdDriver 消息处理程序
void CAmdDriver::InitDialog()
{
	m_listInfo.SetExtendedStyle(LVS_EX_BORDERSELECT | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
	CString strCloumn;
	CRect rect;
	m_listInfo.GetClientRect(rect);
	int nWidth = rect.Width();
	int arrColumnInfo[][4] = { 
		0, IDS_AMID_DRIVER_ID, LVCFMT_LEFT, nWidth / 100.0 * 50,
		1, IDS_AMID_DRIVER_NAME, LVCFMT_LEFT, nWidth / 100.0 * 50,

	};

	for (int i = 0; i < 2; i++)
	{
		strCloumn.LoadString(arrColumnInfo[i][1]);
		m_listInfo.InsertColumn(arrColumnInfo[i][0], strCloumn, arrColumnInfo[i][2], arrColumnInfo[i][3]);
	}
}
void CAmdDriver::Search()
{
	int shownum = 2;
	CString sql = _T("select * from DRIVER");
	CString column[] = { _T("DRIVERID"), _T("NAME") };
	CStringArray arrData;
	theApp.m_database.GetData(sql, column, shownum, arrData);
	int nRow = arrData.GetCount() / shownum;
	for (int i = 0;i < nRow; i++)
	{
		m_listInfo.InsertItem(i,arrData.GetAt(i*shownum));
		CString a = arrData.GetAt(i*shownum + 1);
		m_listInfo.SetItemText(i,1, arrData.GetAt(i*shownum + 1) );
	}
}
void CAmdDriver::OnBnClickedButton1()
{
	//添加司机
	m_listInfo.DeleteAllItems();
	CString name;
	m_edName.GetWindowText(name);
	CStringArray arrData;
	arrData.Add(_T(""));
	arrData.Add(name);
	CString column[] = { _T("DRIVERID"), _T("NAME") };

	if (IDNO == MessageBox(_T("确定添加？"), NULL, MB_YESNO))
	{
		return ;
	}
	theApp.m_database.AddData(_T("DRIVER"),arrData,2,column);
	Search();
}


void CAmdDriver::OnBnClickedButton2()
{
	//删除选中司机
	int nRow = m_listInfo.GetItemCount();
	CString strKey = _T("");
	CString strTempKey;
	CString StrInfo;
	CString StrInfoPlus = _T("");
	
	for (int i = 0; i < nRow; i++)
	{
		if (m_listInfo.GetCheck(i))
		{
			
			
			StrInfo = m_listInfo.GetItemText(i, 0);
			strTempKey = m_listInfo.GetItemText(i, 0);
			strKey = strKey + _T("'") + strTempKey + _T("',");
			StrInfoPlus = StrInfoPlus + _T(" ") + StrInfo + _T(" ");
		}
	}


	if (!strKey.IsEmpty())
	{
		strKey = strKey.Left(strKey.GetLength() - 1);
		CString strSQL = _T("select * from DRIVER where DRIVERID in (") + strKey + _T(")");
		CString strTemp;
		strTemp.Format(_T("确定删除司机%s"), StrInfoPlus);
		if (IDNO == MessageBox(strTemp, NULL, MB_YESNO))
		{
			return;
		}

		theApp.m_database.DeleteData(strSQL);
		m_listInfo.DeleteAllItems();
		Search();
	}
	
}



