// StatisticPer.cpp : 实现文件
//

#include "stdafx.h"
#include "StateGridSys.h"
#include "StatisticPer.h"
#include "afxdialogex.h"
#include "IllusionExcelFile.h"

// CStatisticPer 对话框

IMPLEMENT_DYNAMIC(CStatisticPer, CDialogEx)

CStatisticPer::CStatisticPer(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStatisticPer::IDD, pParent)
{
	m_ColumnNum = -1;
}

CStatisticPer::~CStatisticPer()
{
}

void CStatisticPer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listInfoSortPerMonth);
	DDX_Control(pDX, IDC_COMBO5, m_cbPersonDetial);
	DDX_Control(pDX, IDC_COMBO6, m_cbDriver);
	DDX_Control(pDX, IDC_DATETIMEPICKER_START, m_cbStart);
	DDX_Control(pDX, IDC_DATETIMEPICKER_END, m_cbEnd);
}


BEGIN_MESSAGE_MAP(CStatisticPer, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CStatisticPer::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CStatisticPer::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CStatisticPer::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CStatisticPer::OnBnClickedButton5)
	ON_CBN_SELCHANGE(IDC_COMBO5, &CStatisticPer::OnCbnSelchangeCombo5)
	ON_BN_CLICKED(IDC_BUTTON2, &CStatisticPer::OnBnClickedButton2)
	ON_CBN_SELCHANGE(IDC_COMBO6, &CStatisticPer::OnCbnSelchangeCombo6)
	ON_BN_CLICKED(IDC_BUTTON9, &CStatisticPer::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON8, &CStatisticPer::OnBnClickedButton8)
END_MESSAGE_MAP()


// CStatisticPer 消息处理程序


void CStatisticPer::OnCancel()
{
	// TODO:  在此添加专用代码和/或调用基类
	DestroyWindow();
	//CDialogEx::OnCancel();
}


void CStatisticPer::PostNcDestroy()
{
	// TODO:  在此添加专用代码和/或调用基类
	delete this;
	CDialogEx::PostNcDestroy();
}


BOOL CStatisticPer::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	InitPerMonthDialog();
	InitPersonScoreDeatil();
	// TODO:  在此添加额外的初始化
	InitCBDriver();
	m_cbStart.SetFormat(_T("yy-MM-dd"));
	m_cbEnd.SetFormat(_T("yy-MM-dd"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
void CStatisticPer::InitPerMonthDialog()
{
	m_listInfoSortPerMonth.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	CString strCloumn;
	CRect rect;
	m_listInfoSortPerMonth.GetClientRect(rect);
	int nWidth = rect.Width();
	int arrColumnInfo[][4] = {

		0, IDS_STATIC_PER_DATTE, LVCFMT_LEFT, nWidth / 100.0 * 11,
		1, IDS_STATIC_PER_CLASSNAME, LVCFMT_LEFT, nWidth / 100.0 * 12,
		2, IDS_STATIC_PER_WRKID, LVCFMT_LEFT, nWidth / 100.0 * 11,
		3, IDS_STATIC_PER_OPERATE, LVCFMT_LEFT, nWidth / 100.0 * 11,
		4, IDS_STATIC_PER_OPERATETIME, LVCFMT_LEFT, nWidth / 100.0 * 11,
		5, IDS_STATIC_PER_SCORE, LVCFMT_LEFT, nWidth / 100.0 * 11,
		6, IDS_STATIC_PER_DETIAL, LVCFMT_LEFT, nWidth / 100.0 * 11,
		7, IDS_STATIC_PER_CAR, LVCFMT_LEFT, nWidth / 100.0 * 11,
		8, IDS_STATIC_PER_ELEC, LVCFMT_LEFT, nWidth / 100.0 * 11,
	};
	m_ColumnNum = 9;
	for (int i = 0; i < 9; i++)
	{
		strCloumn.LoadString(arrColumnInfo[i][1]);
		m_listInfoSortPerMonth.InsertColumn(arrColumnInfo[i][0], strCloumn, arrColumnInfo[i][2], arrColumnInfo[i][3]);
	}
}
void CStatisticPer::InitPerMonthDialog_Deatil()
{
	m_listInfoSortPerMonth.SetExtendedStyle( LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );
	CString strCloumn;
	CRect rect;
	m_listInfoSortPerMonth.GetClientRect(rect);
	int nWidth = rect.Width();
	int arrColumnInfo[][4] = {
		0, IDS_STATIC_PER_NUM, LVCFMT_LEFT, nWidth / 100.0 * 10,
		1, IDS_STATIC_PER_DATTE, LVCFMT_LEFT, nWidth / 100.0 * 10,
		2, IDS_STATIC_PER_CLASSNAME, LVCFMT_LEFT, nWidth / 100.0 * 10,
		3, IDS_STATIC_PER_WRKID, LVCFMT_LEFT, nWidth / 100.0 * 10,
		4, IDS_STATIC_PER_OPERATE, LVCFMT_LEFT, nWidth / 100.0 * 10,
		5, IDS_STATIC_PER_OPERATETIME, LVCFMT_LEFT, nWidth / 100.0 * 10,
		6, IDS_STATIC_PER_SCORE, LVCFMT_LEFT, nWidth / 100.0 * 10,
		7, IDS_STATIC_PER_DETIAL, LVCFMT_LEFT, nWidth / 100.0 * 10,
		8, IDS_STATIC_PER_CAR, LVCFMT_LEFT, nWidth / 100.0 * 10,
		9, IDS_STATIC_PER_ELEC, LVCFMT_LEFT, nWidth / 100.0 * 10,

	};
	m_ColumnNum = 10;
	for (int i = 0; i < 10; i++)
	{
		strCloumn.LoadString(arrColumnInfo[i][1]);
		m_listInfoSortPerMonth.InsertColumn(arrColumnInfo[i][0], strCloumn, arrColumnInfo[i][2], arrColumnInfo[i][3]);
	}
}

void CStatisticPer::Search()
{

}

void CStatisticPer::InitPeopleScoreSort()
{
	m_listInfoSortPerMonth.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	CString strCloumn;
	CRect rect;
	m_listInfoSortPerMonth.GetClientRect(rect);
	int nWidth = rect.Width();
	int arrColumnInfo[][4] = {	
		0, IDS_STATIC_PER_SORT, LVCFMT_LEFT, nWidth / 100.0 * 20,
		1, IDS_AMDUSER_LIST_WORKERID, LVCFMT_LEFT, nWidth / 100.0 * 20,
		2, IDS_STATIC_PER_WRKID, LVCFMT_LEFT, nWidth / 100.0 * 20,
		3, IDS_STATIC_PER_CLASSNAME, LVCFMT_LEFT, nWidth / 100.0 * 20,
		4, IDS_STATIC_PER_SCORE, LVCFMT_LEFT, nWidth / 100.0 * 20,
	};
	m_ColumnNum = 5;
	for (int i = 0; i < 5; i++)
	{
		strCloumn.LoadString(arrColumnInfo[i][1]);
		m_listInfoSortPerMonth.InsertColumn(arrColumnInfo[i][0], strCloumn, arrColumnInfo[i][2], arrColumnInfo[i][3]);
	}
}
void CStatisticPer::OnBnClickedButton1()
{
	
	//本月所有员工查询
	CHeaderCtrl* pHeaderCtrl = m_listInfoSortPerMonth.GetHeaderCtrl();

	if (pHeaderCtrl != NULL)
	{
		int  nColumnCount = pHeaderCtrl->GetItemCount();
		for (int i = 0; i < nColumnCount; i++)
		{
			m_listInfoSortPerMonth.DeleteColumn(0);
		}
	}
	
	InitPeopleScoreSort();
	m_listInfoSortPerMonth.DeleteAllItems();
	CStringArray arrData;
	int nNum = 4;
	CString sql = _T("select  MAX(WORDERID) 'WORDERID',MAX(DATE) 'DATE',MAX(CLASSNAME) 'CLASSNAME',t.NAME 'WORKNAME', MAX(OPERATECLASS) 'OPERATECLASS' \
		, MAX(OPERATETIME) 'OPERATETIME', SUM(t.SCORE) 'SUMSCORE', MAX(DETIAL) 'DETIAL', MAX(PLATENUM) 'PLATENUM', MAX(ELECNAME) 'ELECNAME' from \
		( \
		select sc.WORDERID 'WORDERID', sc.DATE 'DATE', cc.CLASSNAME 'CLASSNAME', wk.NAME 'NAME', \
		OPERATEIDTIME 'OPERATETIME', op.OPERATENAME 'OPERATECLASS' \
		, sc.SCORE 'SCORE', DETAIL 'DETIAL', car.PLATENUM 'PLATENUM', el.ELECNAME 'ELECNAME' \
		from SCORE sc \
		inner join WORKERINFO wk on wk.WORDERID = sc.WORDERID \
		inner join OPERATECLASS op on op.OPERATEID = sc.OPERATEID \
		inner join CLASS cc on cc.CLASSID = wk.CLASSID \
		inner join CAR car on car.CARID = sc.CARID \
		inner join ELEC el on el.ELECID = sc.ELECID where LEFT(DATE,7) =  LEFT(CONVERT (date, GETDATE()),7)\
		) t group by t.NAME  order by SUMSCORE desc \
	");
	CString column[] = {_T("WORDERID"),_T("WORKNAME"),_T("CLASSNAME"),_T("SUMSCORE")};
	bool res = theApp.m_database.GetData(sql, column, nNum, arrData);
	int nRow = arrData.GetCount() / nNum;
	if (res)
	{
		for (int i = 0; i < nRow;i++)
		{
			//m_listInfoSortPerMonth.InsertItem(i,arrData.GetAt(i*nNum));
			CString sort;
			sort.Format(_T("%d"), i+1);
			m_listInfoSortPerMonth.InsertItem(i, sort);
			for (int j = 1; j <= nNum;j++)
			{
				m_listInfoSortPerMonth.SetItemText(i, j, arrData.GetAt(i*nNum + j-1));
			}
		}
	}
}
void CStatisticPer::InitPersonScoreDeatil()
{
	//初始化combox
	CString strCopare = _T("本月个人分数详情");
	m_cbPersonDetial.SelectString(0, strCopare);

	CString strselectsql = _T("select * from WORKERINFO");
	CString column[] = { _T("WORDERID"), _T("NAME") };
	int nShowNum = 2;
	CStringArray arrdata;
	theApp.m_database.GetData(strselectsql, column, nShowNum, arrdata);
	int nRow = arrdata.GetCount() / nShowNum;
	for (int i = 0; i < nRow; i++)
	{
		m_cbPersonDetial.AddString(arrdata.GetAt(i*nShowNum + 1));
		m_cbPersonDetial.SetItemData(i + 1, _ttoi(arrdata.GetAt(i*nShowNum)));
	}
	

}

void CStatisticPer::OnBnClickedButton4()
{
	//个人分值详情
	CHeaderCtrl* pHeaderCtrl = m_listInfoSortPerMonth.GetHeaderCtrl();

	if (pHeaderCtrl != NULL)
	{
		int  nColumnCount = pHeaderCtrl->GetItemCount();
		for (int i = 0; i < nColumnCount; i++)
		{
			m_listInfoSortPerMonth.DeleteColumn(0);
		}
	}
	CString cstrStart;
	CString cstrEnd;
	GetDlgItem(IDC_DATETIMEPICKER_START)->GetWindowText(cstrStart);
	GetDlgItem(IDC_DATETIMEPICKER_END)->GetWindowText(cstrEnd);
	InitPeopleScoreSort();
	m_listInfoSortPerMonth.DeleteAllItems();
	CStringArray arrData;
	int nNum = 4;
	CString sql = _T("select  MAX(WORDERID) 'WORDERID',MAX(DATE) 'DATE',MAX(CLASSNAME) 'CLASSNAME',t.NAME 'WORKNAME', MAX(OPERATECLASS) 'OPERATECLASS' \
		, MAX(OPERATETIME) 'OPERATETIME', SUM(t.SCORE) 'SUMSCORE', MAX(DETIAL) 'DETIAL', MAX(PLATENUM) 'PLATENUM', MAX(ELECNAME) 'ELECNAME' from \
		( \
		select sc.WORDERID 'WORDERID', sc.DATE 'DATE', cc.CLASSNAME 'CLASSNAME', wk.NAME 'NAME', \
		OPERATEIDTIME 'OPERATETIME', op.OPERATENAME 'OPERATECLASS' \
		, sc.SCORE 'SCORE', DETAIL 'DETIAL', car.PLATENUM 'PLATENUM', el.ELECNAME 'ELECNAME' \
		from SCORE sc \
		inner join WORKERINFO wk on wk.WORDERID = sc.WORDERID \
		inner join OPERATECLASS op on op.OPERATEID = sc.OPERATEID \
		inner join CLASS cc on cc.CLASSID = wk.CLASSID \
		inner join CAR car on car.CARID = sc.CARID \
		inner join ELEC el on el.ELECID = sc.ELECID  \
		where DATE between '") + cstrStart + _T("' and '") + cstrEnd +
		_T("') t group by t.NAME  order by SUMSCORE desc");
	CString column[] = {_T("WORDERID"),_T("WORKNAME"),_T("CLASSNAME"),_T("SUMSCORE")};
	bool res = theApp.m_database.GetData(sql, column, nNum, arrData);
	int nRow = arrData.GetCount() / nNum;
	if (res)
	{
		for (int i = 0; i < nRow;i++)
		{
			//m_listInfoSortPerMonth.InsertItem(i,arrData.GetAt(i*nNum));
			CString sort;
			sort.Format(_T("%d"), i+1);
			m_listInfoSortPerMonth.InsertItem(i, sort);
			for (int j = 1; j <= nNum;j++)
			{
				m_listInfoSortPerMonth.SetItemText(i, j, arrData.GetAt(i*nNum + j-1));
			}
		}
	}
}


void CStatisticPer::OnBnClickedButton3()
{
	//TODO导出到Excl
	static TCHAR BASED_CODE szFilter[] =
		_T("EXCL Files (*.xlsx)|||");
	CFileDialog fd(FALSE,NULL,NULL,NULL,szFilter);

	int nRes = fd.DoModal();
	if (nRes == IDCANCEL)
	{
		return;
	}
	CString StrPathName = fd.GetPathName();
	//获取列名
	HDITEM hdi;
	TCHAR  lpBuffer[256];
	bool   fFound = false;
	hdi.mask = HDI_TEXT;
	hdi.pszText = lpBuffer;
	hdi.cchTextMax = 256;

	
	IllusionExcelFile ef;
	bool bInit = IllusionExcelFile::InitExcel();
	if (bInit)
	{
		
		bool bOPen = ef.OpenExcelFile(NULL/*_T("C:\\Users\\caonan\\Desktop\\bb.xlsx")*/);
		if (bOPen)
		{
			bool bLoad = ef.LoadSheet(1);
			if (bLoad)
			{
				int nRow = m_listInfoSortPerMonth.GetItemCount();
				
				for (int i = 0; i < nRow;i++)
				{	
					for (int j = 0; j < m_ColumnNum;j++)
					{
						m_listInfoSortPerMonth.GetHeaderCtrl()->GetItem(j, &hdi);
						CString textColumn = hdi.pszText;
						
						ef.SetCellString(1, j + 1, textColumn);
					}
					for (int j = 0; j < m_ColumnNum; j++)
					{
						CString temp = m_listInfoSortPerMonth.GetItemText(i, j);
						ef.SetCellString(i + 2, j + 1, temp);
					}
					
				}
				
				ef.SaveasXSLFile(StrPathName);
				ef.CloseExcelFile();
			}
			
		}
		
	}
	IllusionExcelFile::ReleaseExcel();
	MessageBox(_T("您已成功导出当前表中数据！"));
}


void CStatisticPer::OnBnClickedButton5()
{
	//按时间查询员工详情
	CHeaderCtrl* pHeaderCtrl = m_listInfoSortPerMonth.GetHeaderCtrl();

	if (pHeaderCtrl != NULL)
	{
		int  nColumnCount = pHeaderCtrl->GetItemCount();
		for (int i = 0; i < nColumnCount; i++)
		{
			m_listInfoSortPerMonth.DeleteColumn(0);
		}
	}
	CString cstrStart;
	CString cstrEnd;
	GetDlgItem(IDC_DATETIMEPICKER_START)->GetWindowText(cstrStart);
	GetDlgItem(IDC_DATETIMEPICKER_END)->GetWindowText(cstrEnd);
	InitPerMonthDialog_Deatil();
	m_listInfoSortPerMonth.DeleteAllItems();
	CStringArray arrData;
	int nNum = 9;
	CString sql = _T(" \
		select sc.WORDERID 'WORDERID', sc.DATE 'DATE', cc.CLASSNAME 'CLASSNAME', wk.NAME 'NAME', \
		OPERATEIDTIME 'OPERATETIME', op.OPERATENAME 'OPERATECLASS' \
		, sc.SCORE 'SCORE', DETAIL 'DETIAL', car.PLATENUM 'PLATENUM', el.ELECNAME 'ELECNAME' \
		from SCORE sc \
		inner join WORKERINFO wk on wk.WORDERID = sc.WORDERID \
		inner join OPERATECLASS op on op.OPERATEID = sc.OPERATEID \
		inner join CLASS cc on cc.CLASSID = wk.CLASSID \
		inner join CAR car on car.CARID = sc.CARID \
		inner join ELEC el on el.ELECID = sc.ELECID  \
		where DATE between '") + cstrStart + _T("' and '") + cstrEnd+_T("'");
	CString column[] = { _T("DATE"), _T("CLASSNAME"), _T("NAME"), _T("OPERATECLASS"), _T("OPERATETIME"), _T("SCORE"), _T("DETIAL"), _T("PLATENUM"), _T("ELECNAME") };
	bool res = theApp.m_database.GetData(sql, column, nNum, arrData);
	int nRow = arrData.GetCount() / nNum;
	if (res)
	{
		for (int i = 0; i < nRow;i++)
		{
			//m_listInfoSortPerMonth.InsertItem(i,arrData.GetAt(i*nNum));
			CString sort;
			sort.Format(_T("%d"), i+1);
			m_listInfoSortPerMonth.InsertItem(i, sort);
			for (int j = 1; j <= nNum;j++)
			{
				m_listInfoSortPerMonth.SetItemText(i, j, arrData.GetAt(i*nNum + j-1));
			}
		}
	}
}



void CStatisticPer::OnCbnSelchangeCombo5()
{

	CHeaderCtrl* pHeaderCtrl = m_listInfoSortPerMonth.GetHeaderCtrl();

	if (pHeaderCtrl != NULL)
	{
		int  nColumnCount = pHeaderCtrl->GetItemCount();
		for (int i = 0; i < nColumnCount; i++)
		{
			m_listInfoSortPerMonth.DeleteColumn(0);
		}
	}


	InitPerMonthDialog();

	//个人分值详情
	int index = m_cbPersonDetial.GetCurSel();
	CString workID;
	workID.Format(_T("%d"), m_cbPersonDetial.GetItemData(index));

	m_listInfoSortPerMonth.DeleteAllItems();
	CStringArray arrData;
	int nNum = 9;
	CString sql = _T("select sc.DATE 'DATE',cc.CLASSNAME 'CLASSNAME',wk.NAME 'NAME', \
		OPERATEIDTIME 'OPERATETIME', op.OPERATENAME 'OPERATECLASS' \
		, sc.SCORE 'SCORE', DETAIL 'DETIALe', car.PLATENUM 'PLATENUM', el.ELECNAME 'ELECNAME' \
		from SCORE sc \
		inner join WORKERINFO wk on wk.WORDERID = sc.WORDERID \
		inner join OPERATECLASS op on op.OPERATEID = sc.OPERATEID \
		inner join CLASS cc on cc.CLASSID = wk.CLASSID \
		inner join CAR car on car.CARID = sc.CARID \
		inner join ELEC el on el.ELECID = sc.ELECID \
	where LEFT(DATE,7) =  LEFT(CONVERT (date, GETDATE()),7) and sc.WORDERID = \
		") + workID;
	CString column[] = {_T("DATE"),_T("CLASSNAME"),_T("NAME"),_T("OPERATECLASS"),_T("OPERATETIME"),_T("SCORE"),_T("DETIALe"),_T("PLATENUM"),_T("ELECNAME")};
	bool res = theApp.m_database.GetData(sql, column, nNum, arrData);
	int nRow = arrData.GetCount() / nNum;
	if (res)
	{
		for (int i = 0; i < nRow;i++)
		{
			m_listInfoSortPerMonth.InsertItem(i,arrData.GetAt(i*nNum));
			for (int j = 1; j < nNum;j++)
			{
				m_listInfoSortPerMonth.SetItemText(i, j, arrData.GetAt(i*nNum + j));
			}
		}
	}
}
//初始化司机界面
void CStatisticPer::InitDriverDialog()
{
	m_listInfoSortPerMonth.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	CString strCloumn;
	CRect rect;
	m_listInfoSortPerMonth.GetClientRect(rect);
	int nWidth = rect.Width();
	int arrColumnInfo[][4] = {
		0, IDS_STATIC_PER_DATTE, LVCFMT_LEFT, nWidth / 100.0 * 20,
		1, IDS_AMID_DRIVER_NAME, LVCFMT_LEFT, nWidth / 100.0 * 20,
		2, IDS_STATIC_PER_CAR, LVCFMT_LEFT, nWidth / 100.0 * 20,
		3, IDS_STATIC_DRIVER_TIME, LVCFMT_LEFT, nWidth / 100.0 * 20,
		4, IDS_STATIC_PER_DETIAL, LVCFMT_LEFT, nWidth / 100.0 * 20,
	};
	m_ColumnNum = 5;
	for (int i = 0; i < 5; i++)
	{
		strCloumn.LoadString(arrColumnInfo[i][1]);
		m_listInfoSortPerMonth.InsertColumn(arrColumnInfo[i][0], strCloumn, arrColumnInfo[i][2], arrColumnInfo[i][3]);
	}
}

void CStatisticPer::InitDriverSort()
{
	m_listInfoSortPerMonth.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	CString strCloumn;
	CRect rect;
	m_listInfoSortPerMonth.GetClientRect(rect);
	int nWidth = rect.Width();
	int arrColumnInfo[][4] = {		
		0, IDS_AMID_DRIVER_NAME, LVCFMT_LEFT, nWidth / 100.0 * 50,		
		1, IDS_STATIC_DRIVER_TIME, LVCFMT_LEFT, nWidth / 100.0 * 50,	
	};
	m_ColumnNum = 2;
	for (int i = 0; i < 2; i++)
	{
		strCloumn.LoadString(arrColumnInfo[i][1]);
		m_listInfoSortPerMonth.InsertColumn(arrColumnInfo[i][0], strCloumn, arrColumnInfo[i][2], arrColumnInfo[i][3]);
	}
}
void CStatisticPer::OnBnClickedButton2()
{
	//本月所有司机排名
	CHeaderCtrl* pHeaderCtrl = m_listInfoSortPerMonth.GetHeaderCtrl();

	if (pHeaderCtrl != NULL)
	{
		int  nColumnCount = pHeaderCtrl->GetItemCount();
		for (int i = 0; i < nColumnCount; i++)
		{
			m_listInfoSortPerMonth.DeleteColumn(0);
		}
	}
	InitDriverSort();

	m_listInfoSortPerMonth.DeleteAllItems();
	CStringArray arrData;
	int nNum = 2;
	CString sql = _T("	select t.NAME 'NAME',sum(SCORE) 'SCORE' from(	\
		select DATE, dr.NAME 'NAME', PLATENUM, SCORE, DETAIL from DRAVER_SCORE ds \
		inner join DRIVER dr on dr.DRIVERID = ds.DRIVERID \
		inner join CAR ca on ca.CARID = ds.CARID)t group by t.NAME order by SCORE desc \
		");
	CString column[] = {_T("NAME"),_T("SCORE")};
	bool res = theApp.m_database.GetData(sql, column, nNum, arrData);
	int nRow = arrData.GetCount() / nNum;
	if (res)
	{
		for (int i = 0; i < nRow;i++)
		{
			m_listInfoSortPerMonth.InsertItem(i,arrData.GetAt(i*nNum));
			for (int j = 1; j < nNum;j++)
			{
				m_listInfoSortPerMonth.SetItemText(i, j, arrData.GetAt(i*nNum + j));
			}
		}
	}
}

void CStatisticPer::InitCBDriver()
{
	CString strCopare = _T("本月司机个人详情");
	m_cbDriver.SelectString(0, strCopare);

	CString strselectsql = _T("select * from DRIVER");
	CString column[] = { _T("DRIVERID"), _T("NAME") };
	int nShowNum = 2;
	CStringArray arrdata;
	theApp.m_database.GetData(strselectsql, column, nShowNum, arrdata);
	int nRow = arrdata.GetCount() / nShowNum;
	for (int i = 0; i < nRow; i++)
	{
		m_cbDriver.AddString(arrdata.GetAt(i*nShowNum + 1));
		m_cbDriver.SetItemData(i + 1, _ttoi(arrdata.GetAt(i*nShowNum)));
	}
}
void CStatisticPer::OnCbnSelchangeCombo6()
{
	//司机个人详情
	CHeaderCtrl* pHeaderCtrl = m_listInfoSortPerMonth.GetHeaderCtrl();

	if (pHeaderCtrl != NULL)
	{
		int  nColumnCount = pHeaderCtrl->GetItemCount();
		for (int i = 0; i < nColumnCount; i++)
		{
			m_listInfoSortPerMonth.DeleteColumn(0);
		}
	}

	InitDriverDialog();

	int index = m_cbDriver.GetCurSel();
	CString workID;
	workID.Format(_T("%d"), m_cbDriver.GetItemData(index));

	m_listInfoSortPerMonth.DeleteAllItems();
	CStringArray arrData;
	int nNum = 5;
	CString sql = _T("select DATE ,dr.NAME 'NAME',PLATENUM ,SCORE,DETAIL from DRAVER_SCORE ds \
					 		inner join DRIVER dr on dr.DRIVERID = ds.DRIVERID \
									inner join CAR ca on ca.CARID = ds.CARID \
	where LEFT(DATE,7) =  LEFT(CONVERT (date, GETDATE()),7) and dr.DRIVERID = \
		") + workID;
	CString column[] = { _T("DATE"), _T("NAME"), _T("PLATENUM"), _T("SCORE"), _T("DETAIL") };
	bool res = theApp.m_database.GetData(sql, column, nNum, arrData);
	int nRow = arrData.GetCount() / nNum;
	if (res)
	{
		for (int i = 0; i < nRow;i++)
		{
			m_listInfoSortPerMonth.InsertItem(i,arrData.GetAt(i*nNum));
			for (int j = 1; j < nNum;j++)
			{
				m_listInfoSortPerMonth.SetItemText(i, j, arrData.GetAt(i*nNum + j));
			}
		}
	}
}


void CStatisticPer::OnBnClickedButton9()
{
	//按时间查询司机排名
	CHeaderCtrl* pHeaderCtrl = m_listInfoSortPerMonth.GetHeaderCtrl();

	if (pHeaderCtrl != NULL)
	{
		int  nColumnCount = pHeaderCtrl->GetItemCount();
		for (int i = 0; i < nColumnCount; i++)
		{
			m_listInfoSortPerMonth.DeleteColumn(0);
		}
	}
	CString cstrStart;
	CString cstrEnd;
	GetDlgItem(IDC_DATETIMEPICKER_START)->GetWindowText(cstrStart);
	GetDlgItem(IDC_DATETIMEPICKER_END)->GetWindowText(cstrEnd);
	InitDriverSort();

	m_listInfoSortPerMonth.DeleteAllItems();
	CStringArray arrData;
	int nNum = 2;
	CString sql = _T("	select t.NAME 'NAME',sum(SCORE) 'SCORE' from(	\
		select DATE, dr.NAME 'NAME', PLATENUM, SCORE, DETAIL from DRAVER_SCORE ds \
		inner join DRIVER dr on dr.DRIVERID = ds.DRIVERID \
		inner join CAR ca on ca.CARID = ds.CARID  where DATE between '") + cstrStart + _T("' and '") + cstrEnd + _T("') t group by t.NAME order by SCORE desc ");
		
	CString column[] = {_T("NAME"),_T("SCORE")};
	bool res = theApp.m_database.GetData(sql, column, nNum, arrData);
	int nRow = arrData.GetCount() / nNum;
	if (res)
	{
		for (int i = 0; i < nRow;i++)
		{
			m_listInfoSortPerMonth.InsertItem(i,arrData.GetAt(i*nNum));
			for (int j = 1; j < nNum;j++)
			{
				m_listInfoSortPerMonth.SetItemText(i, j, arrData.GetAt(i*nNum + j));
			}
		}
	}
}


void CStatisticPer::OnBnClickedButton8()
{
	//按时间查询司机详情
	CHeaderCtrl* pHeaderCtrl = m_listInfoSortPerMonth.GetHeaderCtrl();

	if (pHeaderCtrl != NULL)
	{
		int  nColumnCount = pHeaderCtrl->GetItemCount();
		for (int i = 0; i < nColumnCount; i++)
		{
			m_listInfoSortPerMonth.DeleteColumn(0);
		}
	}
	CString cstrStart;
	CString cstrEnd;
	GetDlgItem(IDC_DATETIMEPICKER_START)->GetWindowText(cstrStart);
	GetDlgItem(IDC_DATETIMEPICKER_END)->GetWindowText(cstrEnd);
	InitDriverDialog();

	m_listInfoSortPerMonth.DeleteAllItems();
	CStringArray arrData;
	int nNum = 5;
	CString sql = _T("select DATE ,dr.NAME 'NAME',PLATENUM ,SCORE,DETAIL from DRAVER_SCORE ds \
					 inner join DRIVER dr on dr.DRIVERID = ds.DRIVERID \
					inner join CAR ca on ca.CARID = ds.CARID \
		where DATE between '") + cstrStart + _T("' and '") + cstrEnd+_T("'"); 
	CString column[] = { _T("DATE"), _T("NAME"), _T("PLATENUM"), _T("SCORE"), _T("DETAIL") };
	bool res = theApp.m_database.GetData(sql, column, nNum, arrData);
	int nRow = arrData.GetCount() / nNum;
	if (res)
	{
		for (int i = 0; i < nRow;i++)
		{
			m_listInfoSortPerMonth.InsertItem(i,arrData.GetAt(i*nNum));
			for (int j = 1; j < nNum;j++)
			{
				m_listInfoSortPerMonth.SetItemText(i, j, arrData.GetAt(i*nNum + j));
			}
		}
	}
}
