// SysOperate.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StateGridSys.h"
#include "SysOperate.h"
#include "afxdialogex.h"


// CSysOperate �Ի���

IMPLEMENT_DYNAMIC(CSysOperate, CDialogEx)

CSysOperate::CSysOperate(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSysOperate::IDD, pParent)
{
	m_iKey = -1;
}

CSysOperate::~CSysOperate()
{
}

void CSysOperate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lsInfo);
	DDX_Control(pDX, IDC_EDIT1, m_edAddName);
	DDX_Control(pDX, IDC_EDIT2, m_edAddScore);
	DDX_Control(pDX, IDC_COMBO1, m_cbAddMaxTime);
	DDX_Control(pDX, IDC_COMBO2, m_cbNormalAddTime);
	DDX_Control(pDX, IDC_EDIT7, m_edEditName);
	DDX_Control(pDX, IDC_EDIT8, m_edEditScore);
	DDX_Control(pDX, IDC_COMBO9, m_cbEditMaxTime);
	DDX_Control(pDX, IDC_COMBO10, m_cbNormalEditTime);
	DDX_Control(pDX, IDC_EDIT3, m_cbDelName);
	DDX_Control(pDX, IDC_EDIT4, m_edDelScore);
	DDX_Control(pDX, IDC_EDIT5, m_edDelMax);
	DDX_Control(pDX, IDC_EDIT6, m_edDelNormal);
}


BEGIN_MESSAGE_MAP(CSysOperate, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CSysOperate::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON6, &CSysOperate::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON5, &CSysOperate::OnBnClickedButton5)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CSysOperate::OnNMClickList1)
END_MESSAGE_MAP()


// CSysOperate ��Ϣ�������


void CSysOperate::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���
	DestroyWindow();
	//CDialogEx::OnCancel();
}


void CSysOperate::PostNcDestroy()
{
	// TODO:  �ڴ����ר�ô����/����û���
	delete this;
	CDialogEx::PostNcDestroy();
}


BOOL CSysOperate::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	InitDialog();
	Search();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CSysOperate::InitDialog()
{
	m_lsInfo.SetExtendedStyle(LVS_EX_BORDERSELECT | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	CString strCloumn;
	CRect rect;
	m_lsInfo.GetClientRect(rect);
	int nWidth = rect.Width();
	int arrColumnInfo[][4] = {
		0, IDS_SYS_OPERATE_ID, LVCFMT_LEFT, nWidth / 100.0 * 20,
		1, IDS_SYS_OPERATE_NAME, LVCFMT_LEFT, nWidth / 100.0 * 20,
		2, IDS_SYS_OPERATE_SCORE, LVCFMT_LEFT, nWidth / 100.0 * 20,
		3, IDS_SYS_OPERATE_MAXPEOPLE, LVCFMT_LEFT, nWidth / 100.0 * 20,
		4, IDS_SYS_OPERATE_NORMALTIME, LVCFMT_LEFT, nWidth / 100.0 * 20,

	};

	for (int i = 0; i < 5; i++)
	{
		strCloumn.LoadString(arrColumnInfo[i][1]);
		m_lsInfo.InsertColumn(arrColumnInfo[i][0], strCloumn, arrColumnInfo[i][2], arrColumnInfo[i][3]);
	}
}

void CSysOperate::OnBnClickedButton1()
{
	//���
	//OPERATEID
	CStringArray arrData;
	arrData.Add(_T(" "));

	CString strTemp;
	//OPERATENAME
	m_edAddName.GetWindowText(strTemp);
	if (strTemp == _T(""))
	{
		MessageBox(_T("�������಻��Ϊ�գ�"));
		return;
	}
	arrData.Add(strTemp);

	//OPERATESCORE
	m_edAddScore.GetWindowText(strTemp);
	if (0 == _ttoi(strTemp))
	{
		MessageBox(_T("��������վ�η�ֵ����Ϊ��ֵ��"));
		return;
	}
	
	if (strTemp == _T(""))
	{
		MessageBox(_T("��������վ�η�ֵ����Ϊ�գ�"));
		return;
	}
	arrData.Add(strTemp);

	//MAXPEOPLE
	int index = m_cbAddMaxTime.GetCurSel();
	if (index == -1)
	{
		MessageBox(_T("�����������Ϊ�գ�"));
		return;
	}
	m_cbAddMaxTime.GetLBText(index, strTemp);
	int max = _ttoi(strTemp);
	
	arrData.Add(strTemp);

	//NORMALTIME
	
	index = m_cbNormalAddTime.GetCurSel();
	if (-1 == index)
	{
		MessageBox(_T("��׼����������Ϊ�գ�"));
		return;
	}
	m_cbAddMaxTime.GetLBText(index, strTemp);
	int normal = _ttoi(strTemp);
	if (normal > max)
	{
		MessageBox(_T("��׼���������ܴ������������"));
		return;
	}
	
	arrData.Add(strTemp);
	if (IDNO == MessageBox(_T("ȷ�������"), NULL, MB_YESNO))
	{
		return;
	}

	if (theApp.m_database.AddData(_T("OPERATECLASS"), arrData, 5))
	{
		Search();
	}
}

void CSysOperate::Search()
{
	m_lsInfo.DeleteAllItems();
	int nShowNum = 5;
	CStringArray arrData;
	CString column[] = { _T("OPERATEID"), _T("OPERATENAME"), _T("OPERATESCORE"), _T("MAXPEOPLE") , _T("NORMALTIME")};
	CString sql = _T("select * from OPERATECLASS");
	bool res = theApp.m_database.GetData(sql, column, nShowNum, arrData);
	int nRow = arrData.GetCount() / nShowNum;

	if (res)
	{
		CString strr;
		for (int i = 0; i < nRow; i++)
		{
			m_lsInfo.InsertItem(i, arrData.GetAt(i*nShowNum));

			for (int j = 1; j < nShowNum; j++)
			{
				m_lsInfo.SetItemText(i, j, arrData.GetAt(i*nShowNum + j));
			}
		}
	}
}
void CSysOperate::OnBnClickedButton6()
{
	//�޸�
	CString strKey = _T("");
	CString column[] = {  _T("OPERATENAME"), _T("OPERATESCORE"), _T("MAXPEOPLE"), _T("NORMALTIME") };

	//OPERATEID
	CStringArray arrData;

	CString strTemp;
	//OPERATENAME
	m_edEditName.GetWindowText(strTemp);
	if (strTemp == _T(""))
	{
		MessageBox(_T("�������಻��Ϊ�գ�"));
		return;
	}
	arrData.Add(strTemp);

	//OPERATESCORE
	m_edEditScore.GetWindowText(strTemp);
	if (strTemp == _T(""))
	{
		MessageBox(_T("��������վ�η�ֵ����Ϊ�գ�"));
		return;
	}
	arrData.Add(strTemp);

	//MAXPEOPLE
	int index = m_cbEditMaxTime.GetCurSel();
	if (index == -1)
	{
		MessageBox(_T("�����������Ϊ�գ�"));
		return;
	}
	m_cbEditMaxTime.GetLBText(index, strTemp);
	int max = _ttoi(strTemp);

	arrData.Add(strTemp);

	//NORMALTIME

	index = m_cbNormalEditTime.GetCurSel();
	if (-1 == index)
	{
		MessageBox(_T("��׼����������Ϊ�գ�"));
		return;
	}
	m_cbNormalEditTime.GetLBText(index, strTemp);
	int normal = _ttoi(strTemp);
	if (normal > max)
	{
		MessageBox(_T("��׼���������ܴ������������"));
		return;
	}
	arrData.Add(strTemp);
	if (IDNO == MessageBox(_T("ȷ���޸���"), NULL, MB_YESNO))
	{
		return;
	}
	strKey = m_lsInfo.GetItemText(m_iKey, 0);
	CString strSQL = _T("select * from OPERATECLASS where OPERATEID = ")+ strKey;
	
	theApp.m_database.EditData(strSQL, 4, column, arrData);
	Search();
	
	
}


void CSysOperate::OnBnClickedButton5()
{
	//ɾ��
	CString strKey;
	strKey = m_lsInfo.GetItemText(m_iKey, 0);
	CString strSQL = _T("select * from OPERATECLASS where OPERATEID = ") + strKey;
	if (IDNO == MessageBox(_T("ȷ��ɾ����"), NULL, MB_YESNO))
	{
		return;
	}
	theApp.m_database.DeleteData(strSQL);
	Search();
}


void CSysOperate::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	//��굥��
	CPoint pt;
	::GetCursorPos(&pt);
	m_lsInfo.ScreenToClient(&pt);
	LVHITTESTINFO pHitTestInfo;
	pHitTestInfo.pt = pt;
	int n = m_lsInfo.HitTest(&pHitTestInfo);
	if (n == -1)
	{
		return;
	}
	m_iKey = n;

	CString strtemp = m_lsInfo.GetItemText(n, 1);//��ȡѡ���������
	m_edEditName.SetWindowText(strtemp);
	m_cbDelName.SetWindowText(strtemp);
	strtemp = m_lsInfo.GetItemText(n, 2);//��ȡ����
	m_edEditScore.SetWindowText(strtemp);
	m_edDelScore.SetWindowText(strtemp);
	strtemp = m_lsInfo.GetItemText(n, 3);//��ȡ������
	m_cbEditMaxTime.SetWindowText(strtemp);
	m_edDelMax.SetWindowText(strtemp);
	strtemp = m_lsInfo.GetItemText(n, 4);//��ȡ������
	m_cbNormalEditTime.SetWindowText(strtemp);
	m_edDelNormal.SetWindowText(strtemp);
		
	

	*pResult = 0;
}
