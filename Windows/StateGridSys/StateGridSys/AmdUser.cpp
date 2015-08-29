// AmdUser.cpp : 实现文件
//

#include "stdafx.h"
#include "StateGridSys.h"
#include "AmdUser.h"
#include "afxdialogex.h"
#include "PASSWDLOG.h"

// CAmdUser 对话框

IMPLEMENT_DYNAMIC(CAmdUser, CDialogEx)

CAmdUser::CAmdUser(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAmdUser::IDD, pParent)
{
	m_key = -1;
	m_isUsedSelect = false;
}

CAmdUser::~CAmdUser()
{
}

void CAmdUser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_strNameInput);
	DDX_Control(pDX, IDC_COMBO1, m_lsClass);
	DDX_Control(pDX, IDC_LIST1, m_lscInfo);
	DDX_Control(pDX, IDC_COMBO5, m_lsSelClass);
	DDX_Control(pDX, IDC_COMBO4, m_lsRmClass);
	DDX_Control(pDX, IDC_EDIT4, m_edShowJob);
}


BEGIN_MESSAGE_MAP(CAmdUser, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAmdUser::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CAmdUser::OnBnClickedButton3)
	ON_CBN_SELCHANGE(IDC_COMBO5, &CAmdUser::OnCbnSelchangeCombo5)
	ON_BN_CLICKED(IDC_BUTTON7, &CAmdUser::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON4, &CAmdUser::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON8, &CAmdUser::OnBnClickedButton8)
END_MESSAGE_MAP()

void CAmdUser::InitDialog()
{
	m_lscInfo.SetExtendedStyle(LVS_EX_BORDERSELECT | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
	CString strCloumn;
	CRect rect;
	m_lscInfo.GetClientRect(rect);
	int nWidth = rect.Width();
	int arrColumnInfo[][4] = {
		0, IDS_AMDUSER_LIST_CHECK, LVCFMT_LEFT, nWidth / 100.0 * 10,
		1, IDS_AMDUSER_LIST_WORKERID, LVCFMT_LEFT, nWidth / 100.0 * 20,
		2, IDS_AMDUSER_LIST_USERNAME, LVCFMT_LEFT, nWidth / 100.0 * 25,
		3, IDS_AMDUSER_LIST_CLASSNAME, LVCFMT_LEFT, nWidth / 100.0 * 25,
		4, IDS_AMDUSER_LIST_JOB, LVCFMT_LEFT, nWidth / 100.0 * 20,
		
	};

	for (int i = 0; i < 5; i++)
	{
		strCloumn.LoadString(arrColumnInfo[i][1]);
		m_lscInfo.InsertColumn(arrColumnInfo[i][0], strCloumn, arrColumnInfo[i][2], arrColumnInfo[i][3]);
	}
}

BOOL CAmdUser::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 初始化
	InitDialog();
	Search();
	InitClassList();
	InitClassSelList();
	InitRMClassList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
void CAmdUser::InitRMClassList()
{
	int nShowNum = 2;
	CStringArray arrData;
	CString column[] = { _T("CLASSID"), _T("CLASSNAME") };
	CString sql = _T("select * from CLASS");
	theApp.m_database.GetData(sql, column, nShowNum, arrData);
	int nRow = arrData.GetCount() / nShowNum;
	for (int i = 0; i < nRow; i++)
	{
		m_lsRmClass.AddString(arrData.GetAt(i * nShowNum + 1));
		//DWORD k = _ttoi(arrData.GetAt(i * nShowNum + 1));
		m_lsRmClass.SetItemData(i, _ttoi(arrData.GetAt(i * nShowNum)));

	}
}
void CAmdUser::InitClassList()
{
	int nShowNum = 2;
	CStringArray arrData;
	CString column[] = { _T("CLASSID"), _T("CLASSNAME") };
	CString sql = _T("select * from CLASS");
	theApp.m_database.GetData(sql, column, nShowNum, arrData);
	int nRow = arrData.GetCount() / nShowNum;
	for (int i = 0; i < nRow; i++)
	{
		m_lsClass.AddString(arrData.GetAt(i * nShowNum + 1));
		int k = _ttoi(arrData.GetAt(i * nShowNum));
		m_lsClass.SetItemData(i, _ttoi(arrData.GetAt(i * nShowNum )));

	}
}

void CAmdUser::InitClassSelList()
{
	int nShowNum = 2;
	CStringArray arrData;
	CString column[] = { _T("CLASSID"), _T("CLASSNAME") };
	CString sql = _T("select * from CLASS");
	theApp.m_database.GetData(sql, column, nShowNum, arrData);
	int nRow = arrData.GetCount() / nShowNum;
	for (int i = 0; i < nRow; i++)
	{
		m_lsSelClass.AddString(arrData.GetAt(i * nShowNum + 1));
		m_lsSelClass.SetItemData(i, _ttoi(arrData.GetAt(i * nShowNum)));
	}
}
void CAmdUser::GetContrlData(CStringArray &arrData)
{
	//////////////////////////////////////////////////////////////////////////
}


void CAmdUser::Search()
{
	m_lscInfo.DeleteAllItems();
	int nShowNum = 4;
	CStringArray arrData;
	CString column[] = { _T("WORDERID"),_T("wName"), _T("clClassName"),_T("job") };
	CString sql = _T("select WORDERID , w.NAME as wName,isnull(cl.CLASSNAME,'空') as clClassName,job from WORKERINFO w \
		left join CLASS cl on cl.CLASSID = w.CLASSID  ");
	bool res = theApp.m_database.GetData(sql, column, nShowNum, arrData);
	int nRow = arrData.GetCount() / nShowNum;

	if (res)
	{
		CString strr;
		for (int i = 0; i < nRow; i++)
		{
			m_lscInfo.InsertItem(i, _T(" "));
			
			for (int j = 1; j < nShowNum+1; j++)
			{
				m_lscInfo.SetItemText(i, j, arrData.GetAt(i*nShowNum + j - 1));
			}
		}
	}
}
void CAmdUser::OnCancel()
{
	// TODO:  在此添加专用代码和/或调用基类
	DestroyWindow();
	//CDialogEx::OnCancel();
}


void CAmdUser::PostNcDestroy()
{
	// TODO:  在此添加专用代码和/或调用基类
	delete this;
	CDialogEx::PostNcDestroy();
}


void CAmdUser::OnBnClickedButton1()
{
	m_isUsedSelect = false;
	//添加员工
	CStringArray arrData;
	arrData.Add(_T(" "));
	
	CString strTemp;
	//classid
	int nIndex = m_lsClass.GetCurSel();
	int nKey = m_lsClass.GetItemData(nIndex);//为什么总是0
	strTemp.Format(_T("%d"), nKey);
	if (strTemp == _T("-1"))
	{
		MessageBox(_T("新增员工班级不能为空"));
		return;
	}
	arrData.Add(strTemp);

	//name
	m_strNameInput.GetWindowText(strTemp);
	if (strTemp == _T(""))
	{
		MessageBox(_T("新增员工姓名不能为空"));
		return;
	}

	arrData.Add(strTemp);
	//job
	arrData.Add(_T("员工"));
	CString temp;
	temp.Format(_T("确定要添加新员工%s"),strTemp);
	MessageBox(temp);
	if (theApp.m_database.AddData(_T("WORKERINFO"), arrData,4))
	{
		Search();
	}
}


void CAmdUser::OnBnClickedButton3()
{
	m_isUsedSelect = false;
	//删除员工
	int nRow = m_lscInfo.GetItemCount();
	CString strKey = _T("");
	CString strTempKey;
	CString StrInfo;
	CString StrInfoPlus = _T("");
	CString StrJob;
	for (int i = 0; i < nRow; i++)
	{
		if (m_lscInfo.GetCheck(i))
		{
			StrJob = m_lscInfo.GetItemText(i, 4);
			if (StrJob == _T("班长"))
			{
				MessageBox(_T("不能讲班长删除请尝试设置其他班长操作！"));
				Search();
				return;
			}
			StrInfo = m_lscInfo.GetItemText(i, 2);
			strTempKey = m_lscInfo.GetItemText(i,1);
			strKey = strKey + _T("'") + strTempKey + _T("',");
			StrInfoPlus = StrInfoPlus + _T(" ") + StrInfo + _T(" ");
		}
	}


	if (!strKey.IsEmpty())
	{
		strKey = strKey.Left(strKey.GetLength() - 1);
		CString strSQL = _T("select * from WORKERINFO where WORDERID in (") + strKey + _T(")");
		CString strTemp;
		strTemp.Format(_T("确定删除员工%s"), StrInfoPlus);
		if (IDNO == MessageBox(strTemp, NULL, MB_YESNO))
		{
			return;
		}
		
		theApp.m_database.DeleteData(strSQL);
		Search();
	}
}





void CAmdUser::OnCbnSelchangeCombo5()
{
	//选择班级
	m_isUsedSelect = true;
	m_lscInfo.DeleteAllItems();
	int nShowNum = 4;
	CStringArray arrData;
	CString column[] = { _T("WORDERID"), _T("wName"), _T("clClassName"), _T("job") };
	CString sql;

	int index = m_lsSelClass.GetCurSel();
	m_key = m_lsSelClass.GetItemData(index);
	sql.Format(_T("select WORDERID , w.NAME as wName,cl.CLASSNAME as clClassName,job from WORKERINFO w \
		inner join CLASS cl on cl.CLASSID = w.CLASSID where cl.CLASSID = %d "),m_key);
	bool res = theApp.m_database.GetData(sql, column, nShowNum, arrData);
	int nRow = arrData.GetCount() / nShowNum;

	CString showJob;
	if (res)
	{
		CString strr;
		for (int i = 0; i < nRow; i++)
		{
			m_lscInfo.InsertItem(i, _T(" "));

			for (int j = 1; j < nShowNum + 1; j++)
			{
				if (arrData.GetAt(i*nShowNum + 3) == _T("班长"))
				{
					showJob = arrData.GetAt(i*nShowNum + 1);
					m_edShowJob.SetWindowText(showJob);
				}
				
				m_lscInfo.SetItemText(i, j, arrData.GetAt(i*nShowNum + j - 1));
			}

		}
		
	}
}


void CAmdUser::OnBnClickedButton7()
{
	//设置班长
	if (m_isUsedSelect == false)
	{
		MessageBox(_T("请先选择<查看班级>"));
		return;
	}
	//检测选择的是不是为一
	int nRow = m_lscInfo.GetItemCount();
	CString strKey;
	int iRecord = 0;
	CString addData = _T("");

	for (int i = 0; i < nRow; i++)
	{
		if (m_lscInfo.GetCheck(i))
		{

			iRecord++;
			if (iRecord > 1)
			{
				MessageBox(_T("只能设置一个班长！"));
				Search();
				return;
			}
			strKey = m_lscInfo.GetItemText(i, 1);
			addData = m_lscInfo.GetItemText(i, 2);
			
		}
	}
	if (iRecord != 1)
	{
		MessageBox(_T("请选择一个员工！"));
		return;
	}

	CPASSWDLOG dlg;
	addData = _T("您将要为 ") + addData + _T("创建登录用户名密码，该用户将负责所在班级用户的签到工作");
	
	
	//将原来的班长变为普通员工
	int nShowNum = 2;
	CStringArray arrData;
	CString column[] = { _T("WORDERID"), _T("job") };
	CString sql;
	sql.Format(_T("select * from WORKERINFO where CLASSID = %d "), m_key);

	bool res = theApp.m_database.GetData(sql, column, nShowNum, arrData);
	nRow = arrData.GetCount() / nShowNum;

	CString sqlstr;
	CString column_del[] = { _T("job") };
	CStringArray strdata_del;
	int iReCount = 0;
	
	for (int i = 0; i < nRow; i++)
	{
		if (arrData.GetAt(i*nShowNum + 1) == _T("班长"))
		{
			if (strKey == arrData.GetAt(i*nShowNum))
			{
				MessageBox(_T("当前所选已经是班长！"));
				return;
			}
		}
	}
	//弹出密码对话框
	dlg.GetStringData(addData, strKey, m_key);
	int nRes = dlg.DoModal();

	if (nRes == IDCANCEL)
	{
		return;
	}

	if (res)
	{
		CString strr;
		CString strTempKey = _T(" ");
		CString strID;//记录删除用户名密码的员工ID
		for (int i = 0; i < nRow; i++)
		{
			if (arrData.GetAt(i*nShowNum+1) == _T("班长"))
			{
	
				//*******
				iReCount++;
				CString num = arrData.GetAt(i*nShowNum);
				strTempKey = strTempKey + _T("'") + num + _T("',");
				
				strdata_del.Add(_T("员工"));
				strID = arrData.GetAt(i*nShowNum);
				CString delPassWDID = _T("select * from PASSWD where WORDERID = ") + strID;
				theApp.m_database.DeleteData(delPassWDID);
			}
		}
		if (iReCount > 0)
		{
			strTempKey = strTempKey.Left(strTempKey.GetLength() - 1);
			sqlstr = _T("select * from WORKERINFO where WORDERID in (") + strTempKey + _T(")");
			theApp.m_database.EditData(sqlstr, 1, column_del, strdata_del);
		}
		
	}

	//将选中的员工变为班长
	CString column1[] = { _T("Job") };
	CStringArray strEdit;

	if (!strKey.IsEmpty())
	{
		
		CString strSQL = _T("select * from WORKERINFO where WORDERID in (") + strKey + _T(")");
		
		strEdit.Add(_T("班长"));
		
		theApp.m_database.EditData(strSQL, 1, column1, strEdit);
		//Search();
		OnCbnSelchangeCombo5();
	}


	
}



void CAmdUser::OnBnClickedButton4()
{
	//显示所有
	m_isUsedSelect = false;
	Search();
}


void CAmdUser::OnBnClickedButton8()
{
	//将选中员工添加到班级
	m_isUsedSelect = false;
	int nRow = m_lscInfo.GetItemCount();
	CString strKey = _T("");
	CString strTempKey;
	CString StrInfo;
	CString StrInfoPlus = _T("");
	CString StrJob;
	int iRecord = 0;
	for (int i = 0; i < nRow; i++)
	{
		if (m_lscInfo.GetCheck(i))
		{
			iRecord++;
			StrInfo = m_lscInfo.GetItemText(i, 2);
			StrJob = m_lscInfo.GetItemText(i, 4);
			if (StrJob == _T("班长"))
			{
				MessageBox(_T("班长不能移动到其他班级请设置其他班长在进行该操作！"));
				Search();
				return;
			}
			strTempKey = m_lscInfo.GetItemText(i, 1);
			strKey = strKey + _T("'") + strTempKey + _T("',");
			StrInfoPlus = StrInfoPlus + _T(" ") + StrInfo + _T(" ");
		}
	}

	int index = m_lsRmClass.GetCurSel();
	int ikey = m_lsRmClass.GetItemData(index);
	CString strname;
	m_lsRmClass.GetLBText(index, strname);

	CString column[] = { _T("CLASSID") };
	CStringArray strEdit;
	CString temp;
	temp.Format(_T("%d"),ikey);
	
	if (!strKey.IsEmpty())
	{
		strKey = strKey.Left(strKey.GetLength() - 1);
		CString strSQL = _T("select * from WORKERINFO where WORDERID in (") + strKey + _T(")");
		CString strTemp;
		strTemp.Format(_T("确定修改员工%s到班级%s"), StrInfoPlus, strname);
		if (IDNO == MessageBox(strTemp, NULL, MB_YESNO))
		{
			return;
		}

		//修改次数
		for (int i = 0; i < iRecord;i++)
		{
			strEdit.Add(temp);
		}
		theApp.m_database.EditData(strSQL, 1, column, strEdit);
		Search();
	}
}
