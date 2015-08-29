// SysCar.cpp : 实现文件
//

#include "stdafx.h"
#include "StateGridSys.h"
#include "SysCar.h"
#include "afxdialogex.h"


// CSysCar 对话框

IMPLEMENT_DYNAMIC(CSysCar, CDialogEx)

CSysCar::CSysCar(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSysCar::IDD, pParent)
{

}

CSysCar::~CSysCar()
{
}

void CSysCar::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lsCarInfo);
	DDX_Control(pDX, IDC_LIST2, m_lsElecLeveInfo);
	DDX_Control(pDX, IDC_EDIT1, m_edCarNum);
	DDX_Control(pDX, IDC_EDIT2, m_edElecLeve);
}


BEGIN_MESSAGE_MAP(CSysCar, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CSysCar::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CSysCar::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CSysCar::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CSysCar::OnBnClickedButton4)
END_MESSAGE_MAP()


// CSysCar 消息处理程序


void CSysCar::OnCancel()
{
	// TODO:  在此添加专用代码和/或调用基类
	DestroyWindow();
	//CDialogEx::OnCancel();
}


void CSysCar::PostNcDestroy()
{
	// TODO:  在此添加专用代码和/或调用基类
	delete this;
	CDialogEx::PostNcDestroy();
}

BOOL CSysCar::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitCar();
	InitElec();
	SearchELEC();
	SearchCar();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CSysCar::InitElec()
{
	m_lsElecLeveInfo.SetExtendedStyle(LVS_EX_BORDERSELECT | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
	CString strCloumn;
	CRect rect;
	m_lsElecLeveInfo.GetClientRect(rect);
	int nWidth = rect.Width();
	int arrColumnInfo[][4] = {
		0, IDS_AMDUSER_LIST_CHECK, LVCFMT_LEFT, nWidth / 100.0 * 10,
		1, IDS_SYS_ELEC_LIST_ELVID, LVCFMT_LEFT, nWidth / 100.0 * 40,
		2, IDS_SYS_ELEC_LIST_ELV, LVCFMT_LEFT, nWidth / 100.0 * 50,
	};

	for (int i = 0; i < 3; i++)
	{
		strCloumn.LoadString(arrColumnInfo[i][1]);
		m_lsElecLeveInfo.InsertColumn(arrColumnInfo[i][0], strCloumn, arrColumnInfo[i][2], arrColumnInfo[i][3]);
	}
}
void CSysCar::InitCar()
{
	m_lsCarInfo.SetExtendedStyle(LVS_EX_BORDERSELECT | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
	CString strCloumn;
	CRect rect;
	m_lsCarInfo.GetClientRect(rect);
	int nWidth = rect.Width();
	int arrColumnInfo[][4] = {
		0, IDS_AMDUSER_LIST_CHECK, LVCFMT_LEFT, nWidth / 100.0 * 10,
		1, IDS_SYS_CAR_LIST_CARID, LVCFMT_LEFT, nWidth / 100.0 * 40,
		2, IDS_SYS_CAR_LIST_CARNUM, LVCFMT_LEFT, nWidth / 100.0 * 50,

	};

	for (int i = 0; i < 3; i++)
	{
		strCloumn.LoadString(arrColumnInfo[i][1]);
		m_lsCarInfo.InsertColumn(arrColumnInfo[i][0], strCloumn, arrColumnInfo[i][2], arrColumnInfo[i][3]);
	}
}

void CSysCar::SearchCar()
{
	m_lsCarInfo.DeleteAllItems();
	int nShowNum = 2;
	CStringArray arrData;
	CString column[] = { _T("CARID"), _T("PLATENUM") };
	CString sql = _T("select * from CAR");
	bool res = theApp.m_database.GetData(sql, column, nShowNum, arrData);
	int nRow = arrData.GetCount() / nShowNum;

	if (res)
	{
		CString strr;
		for (int i = 0; i < nRow; i++)
		{
			m_lsCarInfo.InsertItem(i, _T(" "));

			for (int j = 1; j < nShowNum + 1; j++)
			{
				m_lsCarInfo.SetItemText(i, j, arrData.GetAt(i*nShowNum + j - 1));
			}
		}
	}
}
void CSysCar::SearchELEC()
{
	m_lsElecLeveInfo.DeleteAllItems();
	int nShowNum = 2;
	CStringArray arrData;
	CString column[] = { _T("ELECID"), _T("ELECNAME") };
	CString sql = _T("select * from ELEC");
	bool res = theApp.m_database.GetData(sql, column, nShowNum, arrData);
	int nRow = arrData.GetCount() / nShowNum;

	if (res)
	{
		CString strr;
		for (int i = 0; i < nRow; i++)
		{
			m_lsElecLeveInfo.InsertItem(i, _T(" "));

			for (int j = 1; j < nShowNum + 1; j++)
			{
				m_lsElecLeveInfo.SetItemText(i, j, arrData.GetAt(i*nShowNum + j - 1));
			}
		}
	}
}
void CSysCar::OnBnClickedButton1()
{
	//添加车辆
	CStringArray arrData;
	arrData.Add(_T(" "));
	CString strTemp;
	//name
	m_edCarNum.GetWindowText(strTemp);
	if (strTemp == _T(""))
	{
		MessageBox(_T("添加车牌号不能为空！"));
		return;
	}
	arrData.Add(strTemp);
	
	CString temp;
	temp.Format(_T("确定添加车辆%s"), strTemp);
	if (!ISAddData(temp))
	{
		SearchCar();
		return;
	}
	
	if (theApp.m_database.AddData(_T("CAR"), arrData, 2))
	{
		SearchCar();
	}
}
bool CSysCar::ISAddData(CString &str)
{
	if (IDNO == MessageBox(str, NULL, MB_YESNO))
	{
		return false;
	}
	return true;
}

void CSysCar::OnBnClickedButton3()
{
	//删除车辆
	int nRow = m_lsCarInfo.GetItemCount();
	CString strKey = _T("");
	CString StrInfoPlus = _T("");
	CString StrInfo;
	CString strTempKey;
	for (int i = 0; i < nRow; i++)
	{
		if (m_lsCarInfo.GetCheck(i))
		{
			
			strTempKey = m_lsCarInfo.GetItemText(i, 1);
			StrInfo = m_lsCarInfo.GetItemText(i, 2);
			strKey = strKey + _T("'") + strTempKey + _T("',");
			StrInfoPlus = StrInfoPlus + _T(" ") + StrInfo + _T(" ");
			
		}
	}


	if (!strKey.IsEmpty())
	{
		strKey = strKey.Left(strKey.GetLength() - 1);
		CString strSQL = _T("select * from CAR where CARID in (") + strKey + _T(")");
		CString strTemp;
		strTemp.Format(_T("确定删除员工%s"), StrInfoPlus);
		if (IDNO == MessageBox(strTemp, NULL, MB_YESNO))
		{
			return;
		}

		theApp.m_database.DeleteData(strSQL);
		SearchCar();
	}
}


void CSysCar::OnBnClickedButton2()
{
	//添加电压等级
	CStringArray arrData;
	arrData.Add(_T(" "));
	CString strTemp;
	//name
	m_edElecLeve.GetWindowText(strTemp);
	if (strTemp == _T(""))
	{
		MessageBox(_T("添加电压等级不能为空！"));
		return;
	}
	arrData.Add(strTemp);

	CString temp;
	temp.Format(_T("确定添加电压等级%s"), strTemp);
	if (!ISAddData(temp))
	{
		SearchELEC();
		return;
	}

	if (theApp.m_database.AddData(_T("ELEC"), arrData, 2))
	{
		SearchELEC();
	}
}


void CSysCar::OnBnClickedButton4()
{
	//删除电压等级
	int nRow = m_lsElecLeveInfo.GetItemCount();
	CString strKey = _T("");
	CString StrInfoPlus = _T("");
	CString StrInfo;
	CString strTempKey;
	for (int i = 0; i < nRow; i++)
	{
		if (m_lsElecLeveInfo.GetCheck(i))
		{

			strTempKey = m_lsElecLeveInfo.GetItemText(i, 1);
			StrInfo = m_lsElecLeveInfo.GetItemText(i, 2);
			strKey = strKey + _T("'") + strTempKey + _T("',");
			StrInfoPlus = StrInfoPlus + _T(" ") + StrInfo + _T(" ");

		}
	}


	if (!strKey.IsEmpty())
	{
		strKey = strKey.Left(strKey.GetLength() - 1);
		CString strSQL = _T("select * from ELEC where ELECID in (") + strKey + _T(")");
		CString strTemp;
		strTemp.Format(_T("确定删除电压等级%s"), StrInfoPlus);
		if (IDNO == MessageBox(strTemp, NULL, MB_YESNO))
		{
			return;
		}

		theApp.m_database.DeleteData(strSQL);
		SearchELEC();
	}
}


