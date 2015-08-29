// StatisticClass.cpp : 实现文件
//

#include "stdafx.h"
#include "StateGridSys.h"
#include "StatisticClass.h"
#include "afxdialogex.h"
#include "IllusionExcelFile.h"

// CStatisticClass 对话框

IMPLEMENT_DYNAMIC(CStatisticClass, CDialogEx)

CStatisticClass::CStatisticClass(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStatisticClass::IDD, pParent)
{
	m_ColumnNum = -1;
}

CStatisticClass::~CStatisticClass()
{
}

void CStatisticClass::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cbClassSel);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtStart);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtEnd);
	DDX_Control(pDX, IDC_LIST1, m_listInfo);
}


BEGIN_MESSAGE_MAP(CStatisticClass, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CStatisticClass::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON3, &CStatisticClass::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &CStatisticClass::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CStatisticClass::OnBnClickedButton4)
END_MESSAGE_MAP()


// CStatisticClass 消息处理程序


void CStatisticClass::OnCancel()
{
	// TODO:  在此添加专用代码和/或调用基类
	DestroyWindow();
	//CDialogEx::OnCancel();
}


void CStatisticClass::PostNcDestroy()
{
	// TODO:  在此添加专用代码和/或调用基类
	delete this;
	CDialogEx::PostNcDestroy();
}
BOOL CStatisticClass::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitDialogClass();
	InitSelClass();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
void CStatisticClass::InitDialogClass()
{

	m_dtStart.SetFormat(_T("yy-MM-dd"));
	m_dtEnd.SetFormat(_T("yy-MM-dd"));

	m_listInfo.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	CString strCloumn;
	CRect rect;
	m_listInfo.GetClientRect(rect);
	int nWidth = rect.Width();
	int arrColumnInfo[][4] = {
		0, IDS_STATIC_PER_DATTE, LVCFMT_LEFT, nWidth / 100.0 * 12,
		1, IDS_STATIC_PER_CLASSNAME, LVCFMT_LEFT, nWidth / 100.0 * 11,
		2, IDS_STATIC_PER_WRKID, LVCFMT_LEFT, nWidth / 100.0 * 11,
		3, IDS_STATIC_PER_OPERATE, LVCFMT_LEFT, nWidth / 100.0 * 11,
		4, IDS_STATIC_PER_OPERATETIME, LVCFMT_LEFT, nWidth / 100.0 * 11,
		5, IDS_STATIC_PER_SCORE, LVCFMT_LEFT, nWidth / 100.0 * 11,
		6, IDS_STATIC_PER_DETIAL, LVCFMT_LEFT, nWidth / 100.0 * 11,
		7, IDS_STATIC_PER_CAR, LVCFMT_LEFT, nWidth / 100.0 * 11,
		8, IDS_STATIC_PER_ELEC, LVCFMT_LEFT, nWidth / 100.0 * 11,

	};

	for (int i = 0; i < 9; i++)
	{
		strCloumn.LoadString(arrColumnInfo[i][1]);
		m_listInfo.InsertColumn(arrColumnInfo[i][0], strCloumn, arrColumnInfo[i][2], arrColumnInfo[i][3]);
	}
}
void CStatisticClass::InitSelClass()
{
	
	m_cbClassSel.SelectString(0, _T("选择班组"));

	CString strselectsql = _T("select * from CLASS");
	CString column[] = { _T("CLASSID"), _T("CLASSNAME") };
	int nShowNum = 2;
	CStringArray arrdata;
	theApp.m_database.GetData(strselectsql, column, nShowNum, arrdata);
	int nRow = arrdata.GetCount() / nShowNum;
	for (int i = 0; i < nRow; i++)
	{
		m_cbClassSel.AddString(arrdata.GetAt(i*nShowNum + 1));
		m_cbClassSel.SetItemData(i + 1, _ttoi(arrdata.GetAt(i*nShowNum)));
	}


}

void CStatisticClass::OnCbnSelchangeCombo1()
{
	//按班级查询
	CHeaderCtrl* pHeaderCtrl = m_listInfo.GetHeaderCtrl();

	if (pHeaderCtrl != NULL)
	{
		int  nColumnCount = pHeaderCtrl->GetItemCount();
		for (int i = 0; i < nColumnCount; i++)
		{
			m_listInfo.DeleteColumn(0);
		}
	}
	InitDialogClass();
	m_ColumnNum = 9;
	//m_cbClassSel.ResetContent();
	int index = m_cbClassSel.GetCurSel();
	CString ClassID;
	ClassID.Format(_T("%d"), m_cbClassSel.GetItemData(index));

	m_listInfo.DeleteAllItems();
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
	where   LEFT(DATE,7) =  LEFT(CONVERT (date, GETDATE()),7) and  wk.CLASSID = \
		") + ClassID;
	CString column[] = {_T("DATE"),_T("CLASSNAME"),_T("NAME"),_T("OPERATECLASS"),_T("OPERATETIME"),_T("SCORE"),_T("DETIALe"),_T("PLATENUM"),_T("ELECNAME")};
	bool res = theApp.m_database.GetData(sql, column, nNum, arrData);
	int nRow = arrData.GetCount() / nNum;
	if (res)
	{
		for (int i = 0; i < nRow;i++)
		{
			m_listInfo.InsertItem(i,arrData.GetAt(i*nNum));
			for (int j = 1; j < nNum;j++)
			{
				m_listInfo.SetItemText(i, j, arrData.GetAt(i*nNum + j));
			}
		}
	}
}


void CStatisticClass::OnBnClickedButton3()
{
	//按时间查询
	CHeaderCtrl* pHeaderCtrl = m_listInfo.GetHeaderCtrl();

	if (pHeaderCtrl != NULL)
	{
		int  nColumnCount = pHeaderCtrl->GetItemCount();
		for (int i = 0; i < nColumnCount; i++)
		{
			m_listInfo.DeleteColumn(0);
		}
	}
	InitDialogClass();
	m_ColumnNum = 9;
	CString cstrStart;
	CString cstrEnd;
	GetDlgItem(IDC_DATETIMEPICKER1)->GetWindowText(cstrStart);
	GetDlgItem(IDC_DATETIMEPICKER2)->GetWindowText(cstrEnd);

	int index = m_cbClassSel.GetCurSel();
	CString ClassID;
	ClassID.Format(_T("%d"), m_cbClassSel.GetItemData(index));

	m_listInfo.DeleteAllItems();
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
		where DATE between '") + cstrStart + _T("' and '") + cstrEnd + _T( "' and wk.CLASSID =") + ClassID;
	CString column[] = {_T("DATE"),_T("CLASSNAME"),_T("NAME"),_T("OPERATECLASS"),_T("OPERATETIME"),_T("SCORE"),_T("DETIALe"),_T("PLATENUM"),_T("ELECNAME")};
	bool res = theApp.m_database.GetData(sql, column, nNum, arrData);
	int nRow = arrData.GetCount() / nNum;
	if (res)
	{
		for (int i = 0; i < nRow;i++)
		{
			m_listInfo.InsertItem(i,arrData.GetAt(i*nNum));
			for (int j = 1; j < nNum;j++)
			{
				m_listInfo.SetItemText(i, j, arrData.GetAt(i*nNum + j));
			}
		}
	}
}

void CStatisticClass::InitClassSort()
{
	m_listInfo.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	CString strCloumn;
	CRect rect;
	m_listInfo.GetClientRect(rect);
	int nWidth = rect.Width();
	int arrColumnInfo[][4] = { 
		0, IDS_STATIC_PER_SORT, LVCFMT_LEFT, nWidth / 100.0 * 33,
		1, IDS_AMDCLASS_LIST_CLASSNAME, LVCFMT_LEFT, nWidth / 100.0 * 33,
		2, IDS_STATIC_CLASS_SCORE, LVCFMT_LEFT, nWidth / 100.0 * 34,

	};
	m_ColumnNum = 3;
	for (int i = 0; i < 5; i++)
	{
		strCloumn.LoadString(arrColumnInfo[i][1]);
		m_listInfo.InsertColumn(arrColumnInfo[i][0], strCloumn, arrColumnInfo[i][2], arrColumnInfo[i][3]);
	}
}
void CStatisticClass::OnBnClickedButton1()
{
	//本月排名
	CHeaderCtrl* pHeaderCtrl = m_listInfo.GetHeaderCtrl();

	if (pHeaderCtrl != NULL)
	{
		int  nColumnCount = pHeaderCtrl->GetItemCount();
		for (int i = 0; i < nColumnCount; i++)
		{
			m_listInfo.DeleteColumn(0);
		}
	}
	m_ColumnNum = 3;
	InitClassSort();
	m_listInfo.DeleteAllItems();
	CStringArray arrData;
	int nNum = 2;
	CString sql = _T("select REPLACE(MAX(DATE),'-','') 'DATE',CLASSNAME 'CLASSNAME',MAX(t.NAME) 'WORKNAME', MAX(OPERATECLASS) 'OPERATECLASS' \
		, MAX(OPERATETIME) 'OPERATETIME', SUM(t.SCORE) 'SUMSCORE', MAX(DETIAL) 'DETIAL', MAX(PLATENUM) 'PLATENUM', MAX(ELECNAME) 'ELECNAME' from \
		( \
		select sc.DATE 'DATE', cc.CLASSNAME 'CLASSNAME', wk.NAME 'NAME', \
		OPERATEIDTIME 'OPERATETIME', op.OPERATENAME 'OPERATECLASS' \
		, sc.SCORE 'SCORE', DETAIL 'DETIAL', car.PLATENUM 'PLATENUM', el.ELECNAME 'ELECNAME' \
		from SCORE sc \
		inner join WORKERINFO wk on wk.WORDERID = sc.WORDERID \
		inner join OPERATECLASS op on op.OPERATEID = sc.OPERATEID \
		inner join CLASS cc on cc.CLASSID = wk.CLASSID \
		inner join CAR car on car.CARID = sc.CARID \
		inner join ELEC el on el.ELECID = sc.ELECID  where LEFT(DATE,7) =  LEFT(CONVERT (date, GETDATE()),7) \
		) t group by CLASSNAME  order by SUMSCORE desc \
	");
	CString column[] = {_T("CLASSNAME"),_T("SUMSCORE")};
	bool res = theApp.m_database.GetData(sql, column, nNum, arrData);
	int nRow = arrData.GetCount() / nNum;
	if (res)
	{
		for (int i = 0; i < nRow;i++)
		{
			//m_listInfoSortPerMonth.InsertItem(i,arrData.GetAt(i*nNum));
			CString sort;
			sort.Format(_T("%d"), i+1);
			m_listInfo.InsertItem(i, sort);
			for (int j = 1; j <= nNum;j++)
			{
				m_listInfo.SetItemText(i, j, arrData.GetAt(i*nNum + j - 1));
			}
		}
	}

}




void CStatisticClass::OnBnClickedButton4()
{
	//导出电子表格
	static TCHAR BASED_CODE szFilter[] =
		_T("EXCL Files (*.xlsx)|||");
	CFileDialog fd(FALSE, NULL, NULL, NULL, szFilter);

	int nRes = fd.DoModal();
	if (nRes == IDCANCEL)
	{
		return;
	}
	CString StrPathName = fd.GetPathName();
	//获取列明
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
				int nRow = m_listInfo.GetItemCount();

				for (int i = 0; i < nRow; i++)
				{
					for (int j = 0; j < m_ColumnNum; j++)
					{
						m_listInfo.GetHeaderCtrl()->GetItem(j, &hdi);
						CString textColumn = hdi.pszText;

						ef.SetCellString(1, j + 1, textColumn);
					}
					for (int j = 0; j < m_ColumnNum; j++)
					{
						CString temp = m_listInfo.GetItemText(i, j);
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
