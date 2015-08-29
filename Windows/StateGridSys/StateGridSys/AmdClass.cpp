// AmdClass.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StateGridSys.h"
#include "AmdClass.h"
#include "afxdialogex.h"


// CAmdClass �Ի���

IMPLEMENT_DYNAMIC(CAmdClass, CDialogEx)

CAmdClass::CAmdClass(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAmdClass::IDD, pParent)
{

}

CAmdClass::~CAmdClass()
{
}

void CAmdClass::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT3, m_edClassName);
	DDX_Control(pDX, IDC_LIST1, m_lsInfo);
	DDX_Control(pDX, IDC_EDIT1, m_edClassEdit);
}


BEGIN_MESSAGE_MAP(CAmdClass, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &CAmdClass::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CAmdClass::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CAmdClass::OnBnClickedButton5)
END_MESSAGE_MAP()


// CAmdClass ��Ϣ�������


void CAmdClass::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���
	DestroyWindow();
	//CDialogEx::OnCancel();
}


void CAmdClass::PostNcDestroy()
{
	// TODO:  �ڴ����ר�ô����/����û���
	delete this;
	CDialogEx::PostNcDestroy();
}


BOOL CAmdClass::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitDialog();
	search();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
void CAmdClass::InitDialog()
{
	m_lsInfo.SetExtendedStyle(LVS_EX_BORDERSELECT | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
	CString strCloumn;
	CRect rect;
	m_lsInfo.GetClientRect(rect);
	int nWidth = rect.Width();
	int arrColumnInfo[][4] = {
		0, IDS_AMDUSER_LIST_CHECK, LVCFMT_LEFT, nWidth / 100.0 * 10,
		1, IDS_AMDCLASS_LIST_CLASSID, LVCFMT_LEFT, nWidth / 100.0 * 40,
		2, IDS_AMDCLASS_LIST_CLASSNAME, LVCFMT_LEFT, nWidth / 100.0 * 50,
	};

	for (int i = 0; i < 3; i++)
	{
		strCloumn.LoadString(arrColumnInfo[i][1]);
		m_lsInfo.InsertColumn(arrColumnInfo[i][0], strCloumn, arrColumnInfo[i][2], arrColumnInfo[i][3]);
	}


}

void CAmdClass::search()
{
	m_lsInfo.DeleteAllItems();
	int nShowNum = 2;
	CStringArray arrData;
	CString column[] = { _T("CLASSID"), _T("CLASSNAME") };
	CString sql = _T("select * from CLASS");
	bool res = theApp.m_database.GetData(sql, column, nShowNum, arrData);
	int nRow = arrData.GetCount() / nShowNum;

	if (res)
	{
		CString strr;
		for (int i = 0; i < nRow; i++)
		{
			m_lsInfo.InsertItem(i, _T(" "));

			for (int j = 1; j < nShowNum + 1; j++)
			{
				m_lsInfo.SetItemText(i, j, arrData.GetAt(i*nShowNum + j - 1));
			}
		}
	}
}

void CAmdClass::OnBnClickedButton3()
{
	//��Ӱ༶
	CStringArray arrData;
	arrData.Add(_T(" "));
	CString strTemp;
	//name
	m_edClassName.GetWindowText(strTemp);
	if (strTemp == _T(""))
	{
		MessageBox(_T("�����༶���Ʋ���Ϊ�գ�"));
		return;
	}
	arrData.Add(strTemp);
	//job
	CString temp;
	temp.Format(_T("ȷ��Ҫ��Ӱ༶%s"), strTemp);
	MessageBox(temp);
	if (theApp.m_database.AddData(_T("CLASS"), arrData,2))
	{
		search();
	}
}

void CAmdClass::OnBnClickedButton4()
{
	//ɾ���༶
	int nRow = m_lsInfo.GetItemCount();
	CString ClassIDStr;
	CString str_temp;
	int iRecord = 0;
	for (int i = 0; i < nRow; i++)
	{
		if (m_lsInfo.GetCheck(i))
		{

			iRecord++;
			if (iRecord > 1)
			{
				MessageBox(_T("һ��ֻ��ɾ��һ���࣡"));
				search();
				return;
			}
			ClassIDStr = m_lsInfo.GetItemText(i, 1);
			str_temp = m_lsInfo.GetItemText(i, 2);
		}
	}
	if (IDNO == MessageBox(_T("ȷ��ɾ���༶")+str_temp, NULL, MB_YESNO))
	{
		return;
	}
	CString sql = _T("select * from CLASS where CLASSID = ") + ClassIDStr;
	theApp.m_database.DeleteData(sql);
	
	//���೤����Ϊ��ͨԱ��
	int nShowNum = 3;
	CStringArray arrData;
	CString column[] = { _T("WORDERID"), _T("job"),_T("CLASSID") };
	CString sqlSet = _T("select * from WORKERINFO where CLASSID = ") + ClassIDStr;
	

	bool res = theApp.m_database.GetData(sqlSet, column, nShowNum, arrData);
	nRow = arrData.GetCount() / nShowNum;

	for (int i = 0; i < nRow; i++)
	{
		if (arrData.GetAt(i*nShowNum + 1) == _T("�೤"))
		{
			CStringArray arrEdit;
			CString WorkID = arrData.GetAt(i*nShowNum);
			arrEdit.Add(_T("-1"));
			arrEdit.Add(_T("Ա��"));
			CString strEdit = _T("select *from WORKERINFO where WORDERID = ") + WorkID;
			CString columnEdit[] = { _T("CLASSID"), _T("Job") };
			theApp.m_database.EditData(strEdit, 2, columnEdit, arrEdit);
			//ɾ�������¼��Ϣ
			CString delPassWDID = _T("select * from PASSWD where WORDERID = ") + WorkID;
			theApp.m_database.DeleteData(delPassWDID);
		}
		else
		{
			CStringArray arrEdit;
			CString WorkID = arrData.GetAt(i*nShowNum);
			arrEdit.Add(_T("-1"));
			arrEdit.Add(_T("Ա��"));
			CString strEdit = _T("select *from WORKERINFO where WORDERID = ") + WorkID;
			CString columnEdit[] = { _T("CLASSID"), _T("Job") };
			theApp.m_database.EditData(strEdit, 2, columnEdit, arrEdit);
		}
	
	}
	search();
}


void CAmdClass::OnBnClickedButton5()
{
	//�޸İ༶����
	
	int nRow = m_lsInfo.GetItemCount();
	CString strKey;
	CString str_temp;
	int iRecord = 0;
	for (int i = 0; i < nRow; i++)
	{
		if (m_lsInfo.GetCheck(i))
		{

			iRecord++;
			if (iRecord > 1)
			{
				MessageBox(_T("һ��ֻ���޸�һ���༶���ƣ�"));
				search();
				return;
			}
			strKey = m_lsInfo.GetItemText(i, 1);
			str_temp = m_lsInfo.GetItemText(i, 2);
		}
	}

	int nShowNum = 1;
	CStringArray arrData;
	CString column[] = { _T("CLASSNAME") };
	CString sql;
	sql = _T("select * from CLASS where CLASSID = ") + strKey;
	if (!strKey.IsEmpty())
	{
		CStringArray dataEdit;
		CString temp;
		m_edClassEdit.GetWindowText(temp);
		if (temp == _T(""))
		{
			MessageBox(_T("�޸İ༶���Ʋ�����Ϊ�գ�"));
			search();
			return;
		}
		str_temp = _T("ȷ�����༶") + str_temp + _T("�޸�Ϊ") + temp;
		if (!ISAddData(str_temp))
		{
			return;
		}
		
		dataEdit.Add(temp);
		theApp.m_database.EditData(sql, 1, column, dataEdit);
		search();
	}
	
}
bool CAmdClass::ISAddData(CString &str)
{
	if (IDNO == MessageBox(str, NULL, MB_YESNO))
	{
		return false;
	}
	return true;
}