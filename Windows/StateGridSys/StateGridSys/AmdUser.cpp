// AmdUser.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StateGridSys.h"
#include "AmdUser.h"
#include "afxdialogex.h"
#include "PASSWDLOG.h"

// CAmdUser �Ի���

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

	// ��ʼ��
	InitDialog();
	Search();
	InitClassList();
	InitClassSelList();
	InitRMClassList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
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
	CString sql = _T("select WORDERID , w.NAME as wName,isnull(cl.CLASSNAME,'��') as clClassName,job from WORKERINFO w \
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
	// TODO:  �ڴ����ר�ô����/����û���
	DestroyWindow();
	//CDialogEx::OnCancel();
}


void CAmdUser::PostNcDestroy()
{
	// TODO:  �ڴ����ר�ô����/����û���
	delete this;
	CDialogEx::PostNcDestroy();
}


void CAmdUser::OnBnClickedButton1()
{
	m_isUsedSelect = false;
	//���Ա��
	CStringArray arrData;
	arrData.Add(_T(" "));
	
	CString strTemp;
	//classid
	int nIndex = m_lsClass.GetCurSel();
	int nKey = m_lsClass.GetItemData(nIndex);//Ϊʲô����0
	strTemp.Format(_T("%d"), nKey);
	if (strTemp == _T("-1"))
	{
		MessageBox(_T("����Ա���༶����Ϊ��"));
		return;
	}
	arrData.Add(strTemp);

	//name
	m_strNameInput.GetWindowText(strTemp);
	if (strTemp == _T(""))
	{
		MessageBox(_T("����Ա����������Ϊ��"));
		return;
	}

	arrData.Add(strTemp);
	//job
	arrData.Add(_T("Ա��"));
	CString temp;
	temp.Format(_T("ȷ��Ҫ�����Ա��%s"),strTemp);
	MessageBox(temp);
	if (theApp.m_database.AddData(_T("WORKERINFO"), arrData,4))
	{
		Search();
	}
}


void CAmdUser::OnBnClickedButton3()
{
	m_isUsedSelect = false;
	//ɾ��Ա��
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
			if (StrJob == _T("�೤"))
			{
				MessageBox(_T("���ܽ��೤ɾ���볢�����������೤������"));
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
		strTemp.Format(_T("ȷ��ɾ��Ա��%s"), StrInfoPlus);
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
	//ѡ��༶
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
				if (arrData.GetAt(i*nShowNum + 3) == _T("�೤"))
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
	//���ð೤
	if (m_isUsedSelect == false)
	{
		MessageBox(_T("����ѡ��<�鿴�༶>"));
		return;
	}
	//���ѡ����ǲ���Ϊһ
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
				MessageBox(_T("ֻ������һ���೤��"));
				Search();
				return;
			}
			strKey = m_lscInfo.GetItemText(i, 1);
			addData = m_lscInfo.GetItemText(i, 2);
			
		}
	}
	if (iRecord != 1)
	{
		MessageBox(_T("��ѡ��һ��Ա����"));
		return;
	}

	CPASSWDLOG dlg;
	addData = _T("����ҪΪ ") + addData + _T("������¼�û������룬���û����������ڰ༶�û���ǩ������");
	
	
	//��ԭ���İ೤��Ϊ��ͨԱ��
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
		if (arrData.GetAt(i*nShowNum + 1) == _T("�೤"))
		{
			if (strKey == arrData.GetAt(i*nShowNum))
			{
				MessageBox(_T("��ǰ��ѡ�Ѿ��ǰ೤��"));
				return;
			}
		}
	}
	//��������Ի���
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
		CString strID;//��¼ɾ���û��������Ա��ID
		for (int i = 0; i < nRow; i++)
		{
			if (arrData.GetAt(i*nShowNum+1) == _T("�೤"))
			{
	
				//*******
				iReCount++;
				CString num = arrData.GetAt(i*nShowNum);
				strTempKey = strTempKey + _T("'") + num + _T("',");
				
				strdata_del.Add(_T("Ա��"));
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

	//��ѡ�е�Ա����Ϊ�೤
	CString column1[] = { _T("Job") };
	CStringArray strEdit;

	if (!strKey.IsEmpty())
	{
		
		CString strSQL = _T("select * from WORKERINFO where WORDERID in (") + strKey + _T(")");
		
		strEdit.Add(_T("�೤"));
		
		theApp.m_database.EditData(strSQL, 1, column1, strEdit);
		//Search();
		OnCbnSelchangeCombo5();
	}


	
}



void CAmdUser::OnBnClickedButton4()
{
	//��ʾ����
	m_isUsedSelect = false;
	Search();
}


void CAmdUser::OnBnClickedButton8()
{
	//��ѡ��Ա����ӵ��༶
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
			if (StrJob == _T("�೤"))
			{
				MessageBox(_T("�೤�����ƶ��������༶�����������೤�ڽ��иò�����"));
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
		strTemp.Format(_T("ȷ���޸�Ա��%s���༶%s"), StrInfoPlus, strname);
		if (IDNO == MessageBox(strTemp, NULL, MB_YESNO))
		{
			return;
		}

		//�޸Ĵ���
		for (int i = 0; i < iRecord;i++)
		{
			strEdit.Add(temp);
		}
		theApp.m_database.EditData(strSQL, 1, column, strEdit);
		Search();
	}
}
