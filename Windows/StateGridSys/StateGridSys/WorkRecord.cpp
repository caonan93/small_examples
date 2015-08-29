// WorkRecord.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StateGridSys.h"
#include "WorkRecord.h"
#include "afxdialogex.h"


// CWorkRecord �Ի���

IMPLEMENT_DYNAMIC(CWorkRecord, CDialogEx)

CWorkRecord::CWorkRecord(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWorkRecord::IDD, pParent)
{
	m_ClassID = _T("");
	m_iWorker1 = -1;
	m_iWorker2 = -1;
	m_iWorker3 = -1;
}

CWorkRecord::~CWorkRecord()
{
}

void CWorkRecord::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtWorkDate);
	DDX_Control(pDX, IDC_COMBO1, m_cbElecLv);
	DDX_Control(pDX, IDC_COMBO2, m_cbCar);
	DDX_Control(pDX, IDC_COMBO3, m_cbOperate);
	DDX_Control(pDX, IDC_COMBO4, m_cbOperaTime);
	DDX_Control(pDX, IDC_COMBO8, m_cbDriver);
	DDX_Control(pDX, IDC_COMBO5, m_cbWork1);
	DDX_Control(pDX, IDC_COMBO7, m_cbWork2);
	DDX_Control(pDX, IDC_COMBO6, m_cbWork3);
	DDX_Control(pDX, IDC_EDIT2, m_edWDetail);
}


BEGIN_MESSAGE_MAP(CWorkRecord, CDialogEx)
	//ON_MESSAGE(WM_POSTPASSWD, &CWorkRecord::onMSG)
	ON_BN_CLICKED(IDC_BUTTON1, &CWorkRecord::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CWorkRecord::OnCbnSelchangeCombo3)
	ON_CBN_SELCHANGE(IDC_COMBO5, &CWorkRecord::OnCbnSelchangeCombo5)
	ON_CBN_SELCHANGE(IDC_COMBO7, &CWorkRecord::OnCbnSelchangeCombo7)
END_MESSAGE_MAP()


BOOL CWorkRecord::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitDialog();
	InitDriver();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CWorkRecord::GetData(CString &data1)
{
	m_ClassID = data1;
}

bool CWorkRecord::InitWorkCtrl(CComboBox *work,int workID,double radio)
{
	CStringArray saveDataArr;
	int ID_ELe = work->GetItemData(workID);
	if (ID_ELe == -1)
	{
		
		return false;
	}
	saveDataArr.Add(_T(""));
	//��ȡ����
	CString date;
	GetDlgItem(IDC_DATETIMEPICKER1)->GetWindowText(date);
	saveDataArr.Add(date);
	if (false == CheckMessageBox(_T("����"), date))
	{
		return false;
	}
	
	//������Ա
	//int ID_ELe = work->GetItemData(workID);
	CString strWork;
	strWork.Format(_T("%d"), ID_ELe);
	saveDataArr.Add(strWork);
	if (false == CheckMessageBox(_T("������Ա����ѡ��һ��"), strWork))
	{
		return false;
	}
	//��������
	int index = m_cbOperate.GetCurSel();
	if (index == -1)
	{
		MessageBox(_T("�������಻��Ϊ�գ�"));
		return false;
	}
	ID_ELe = m_cbOperate.GetItemData(index);
	CString strOperate;
	strOperate.Format(_T("%d"), ID_ELe);
	saveDataArr.Add(strOperate);

	if (false == CheckMessageBox(_T("��������"), strOperate))
	{
		return false;
	}
	//����վ��
	index = m_cbOperaTime.GetCurSel();
	if (index == -1)
	{
		MessageBox(_T("����վ�β���Ϊ�գ�"));
		return false;
	}
	//ID_ELe = m_cbOperaTime.GetItemData(index);
	CString strOperateTime;
	strOperateTime.Format(_T("%d"), index + 1);
	saveDataArr.Add(strOperateTime);
	int iOperate = index + 1;

	if (false == CheckMessageBox(_T("��������"), strOperateTime))
	{
		return false;
	}
	//Score
	//ϵ��*��������*����վ��
	float iscore = CalculateScore(radio, strOperate, iOperate);
	CString scoreStr;
	scoreStr.Format(_T("%f"), iscore);
	saveDataArr.Add(scoreStr);

	//��������
	CString detailStr;
	m_edWDetail.GetWindowText(detailStr);
	saveDataArr.Add(detailStr);
	//��������
	index = m_cbCar.GetCurSel();
	if (index == -1)
	{
		MessageBox(_T("������������Ϊ�գ�"));
		return false;
	}
	ID_ELe = m_cbCar.GetItemData(index);
	CString strCar;
	strCar.Format(_T("%d"), ID_ELe);
	saveDataArr.Add(strCar);

	if (false == CheckMessageBox(_T("��������"), strCar))
	{
		return false;
	}
	//������ѹ
	index = m_cbElecLv.GetCurSel();
	if (index == -1)
	{
		MessageBox(_T("������ѹ����Ϊ�գ�"));
		return false;
	}
	ID_ELe = m_cbElecLv.GetItemData(index);
	CString strEle;
	strEle.Format(_T("%d"), ID_ELe);
	saveDataArr.Add(strEle);

	if (false == CheckMessageBox(_T("��ѹ�ȼ�"), strEle))
	{
		return false;
	}
	//˾��

	/*//������Ա2?
	ID_ELe = m_cbWork2.GetItemData(m_iWorker2);
	CString strWork2;
	strWork2.Format(_T("%d"), ID_ELe);
	saveDataArr.Add(strWork2);
	//������Ա3
	index = m_cbWork3.GetCurSel();
	ID_ELe = m_cbWork3.GetItemData(index);
	CString strWork3;
	strWork3.Format(_T("%d"), ID_ELe);
	saveDataArr.Add(strWork3);*/

	//
	CString strAdd = _T("select *from SCORE");
	CString column[] = { _T("SCOREID")_T("DATE"), _T("WORDERID"), _T("OPERATEID"), _T("OPERATEIDTIME"), _T("SCORE"), _T("DETAIL"), _T("CARID"), _T("ELECID") };
	int shownum = 9;
	//�������
	theApp.m_database.AddData(_T("SCORE"), saveDataArr, shownum, column);
	return true;
}
void CWorkRecord::OnBnClickedButton1()
{
	//�ύ
		//�������������Ա
	if (IDNO == MessageBox(_T("ȷ�������𣬱���󽫲��ɸ��ģ�"), NULL, MB_YESNO))
	{
		return;
	}
	int index = m_cbWork3.GetCurSel();
	//m_iWorker3 = m_cbWork3.GetItemData(index+1);
	
	bool istrue1 = InitWorkCtrl(&m_cbWork1,m_iWorker1,1);
	bool istrue2 = InitWorkCtrl(&m_cbWork2, m_iWorker2, /*0.9*/1);
	bool istrue3 = InitWorkCtrl(&m_cbWork3, index, /*0.6*/1);
	//����˾������
	
	bool isTrue = SaveDriveInfo();
	if (isTrue)
	{
		OnCancel();
	}
	
}
bool CWorkRecord::SaveDriveInfo()
{
	CStringArray saveDataArr;
	
	
	saveDataArr.Add(_T(""));
	//��ȡ����
	CString date;
	GetDlgItem(IDC_DATETIMEPICKER1)->GetWindowText(date);
	saveDataArr.Add(date);
	if (false == CheckMessageBox(_T("����"), date))
	{
		return false;
	}
	//��������
	int index = m_cbOperate.GetCurSel();
	if (index == -1)
	{
		MessageBox(_T("�������಻��Ϊ�գ�"));
		return false;
	}
	int OperateClass = m_cbOperate.GetItemData(index);
	CString strOperate;
	strOperate.Format(_T("%d"), OperateClass);
			//saveDataArr.Add(strOperate);
	//DRIVERID
	int indexd = m_cbDriver.GetCurSel();
	if (-1 == indexd)
	{
		MessageBox(_T("��ѡ��˾��"));
		return false;
	}
	int DRIVERID = m_cbDriver.GetItemData(indexd);
	CString driverstrID;
	driverstrID.Format(_T("%d"), DRIVERID);
	saveDataArr.Add(driverstrID);
	
	//Score
	//ϵ��*��������
	CString strTime;
	int nTime = m_cbOperaTime.GetCurSel();
	m_cbOperaTime.GetLBText(nTime, strTime);
	saveDataArr.Add(strTime);

	//��������
	CString detailStr;
	m_edWDetail.GetWindowText(detailStr);
	saveDataArr.Add(detailStr);
	//��������
	index = m_cbCar.GetCurSel();
	if (index == -1)
	{
		MessageBox(_T("������������Ϊ�գ�"));
		return false;
	}
	int carID = m_cbCar.GetItemData(index);
	CString strCar;
	strCar.Format(_T("%d"), carID);
	saveDataArr.Add(strCar);

	if (false == CheckMessageBox(_T("��������"), strCar))
	{
		return false;
	}


	CString strAdd = _T("select *from DRAVER_SCORE");
	CString column[] = { _T("DATEID"),_T("DATE")_T("DRIVERID"), _T("SCORE"), _T("DETAIL"), _T("CARID")};
	int shownum = 6;
	//�������
	theApp.m_database.AddData(_T("DRAVER_SCORE"), saveDataArr, shownum, column);

	return true;
}
double CWorkRecord::CalculateScore(double ratio, CString OperateID, int Time)
{
	CStringArray strOperateData;
	CString strOperate = _T("select *from OPERATECLASS where OPERATEID = ") + OperateID;
	CString columnOper[] = { _T("OPERATEID") ,_T("OPERATESCORE")};
	int nshowNum = 2;
	theApp.m_database.GetData(strOperate, columnOper, nshowNum, strOperateData);
	CString score = strOperateData.GetAt(1);
	int iScore = _ttoi(score);

	return ratio*iScore*Time;
}
void CWorkRecord::InitDialog()
{
	//��ȡʱ��
	m_dtWorkDate.SetFormat(_T("yy-MM-dd"));
	

	//��ѹ�ȼ�
	CStringArray strDataElec;
	int nNum = 2;
	CString stringEleSql = _T("select *from ELEC");
	CString column[] = { _T("ELECID"), _T("ELECNAME") };
	theApp.m_database.GetData(stringEleSql, column, nNum, strDataElec);
	int nRow = strDataElec.GetCount() / nNum;
	for (int i = 0; i < nRow;i++)
	{
		CString tempElec = strDataElec.GetAt(i*nNum);
		int itempElec = _ttoi(tempElec);
		m_cbElecLv.AddString(strDataElec.GetAt(i*nNum + 1));
		m_cbElecLv.SetItemData(i, itempElec);
	}
	
	//��������
	CStringArray strDataCar;
	nNum = 2;
	CString stringCarSql = _T("select *from CAR");
	CString columncar[] = { _T("CARID"), _T("PLATENUM") };
	theApp.m_database.GetData(stringCarSql, columncar, nNum, strDataCar);
	nRow = strDataCar.GetCount() / nNum;
	for (int i = 0; i < nRow; i++)
	{
		CString tempElec = strDataCar.GetAt(i*nNum);
		int itempElec = _ttoi(tempElec);
		m_cbCar.AddString(strDataCar.GetAt(i*nNum + 1));
		m_cbCar.SetItemData(i, itempElec);
	}

	//��������
	CStringArray strDataOperate;
	nNum = 2;
	CString stringOper = _T("select *from OPERATECLASS");
	CString columnOper[] = { _T("OPERATEID"), _T("OPERATENAME") };
	theApp.m_database.GetData(stringOper, columnOper, nNum, strDataOperate);

	nRow = strDataOperate.GetCount() / nNum;

	for (int i = 0; i < nRow; i++)
	{
		CString tempElec = strDataOperate.GetAt((i)*nNum);
		int itempElec = _ttoi(tempElec);
		m_cbOperate.AddString(strDataOperate.GetAt((i)*nNum + 1));
		m_cbOperate.SetItemData(i, itempElec);
	}
	
	
	//˾��
	//������Ա1
	CStringArray strWorker1;
	nNum = 2;
	CString stringWorker1 = _T("select * from WORKERINFO where CLASSID = ")+m_ClassID;
	CString columnWorker1[] = { _T("WORDERID"), _T("NAME") };
	theApp.m_database.GetData(stringWorker1, columnWorker1, nNum, strWorker1);

	nRow = strWorker1.GetCount() / nNum;

	m_cbWork1.AddString(_T("��ѡ��"));
	m_cbWork1.SetItemData(0, -1);
	for (int i = 0; i < nRow; i++)
	{
		CString tempElec = strWorker1.GetAt((i)*nNum);
		int itempElec = _ttoi(tempElec);
		m_cbWork1.AddString(strWorker1.GetAt((i)*nNum + 1));
		m_cbWork1.SetItemData(i+1, itempElec);
	}
	
}


void CWorkRecord::OnCbnSelchangeCombo5()
{
	//������Ա2
	m_cbWork2.ResetContent();
	int index = m_cbWork1.GetCurSel();
	m_iWorker1 = index;
	int iWorkID = m_cbWork1.GetItemData(index);
	CString strWorkID;
	strWorkID.Format(_T("%d"), iWorkID);
	CStringArray strWorker2;
	int nNum = 2;
	CString stringWorker2 = _T("select * from WORKERINFO where CLASSID = ") 
		+ m_ClassID + _T(" and WORDERID != ") + strWorkID;
	CString columnWorker2[] = { _T("WORDERID"), _T("NAME") };
	theApp.m_database.GetData(stringWorker2, columnWorker2, nNum, strWorker2);

	int nRow = strWorker2.GetCount() / nNum;
	m_cbWork2.AddString(_T("��ѡ��"));
	m_cbWork2.SetItemData(0, -1);
	for (int i = 0; i < nRow; i++)
	{
		CString tempElec = strWorker2.GetAt((i)*nNum);
		int itempElec = _ttoi(tempElec);
		m_cbWork2.AddString(strWorker2.GetAt((i)*nNum + 1));
		m_cbWork2.SetItemData(i+1, itempElec);
	}
	
}


void CWorkRecord::OnCbnSelchangeCombo7()
{
	//������Ա3
	m_cbWork3.ResetContent();
	int index = m_cbWork1.GetCurSel();
	int iWorkID = m_cbWork1.GetItemData(index);

	int index2 = m_cbWork2.GetCurSel();
	m_iWorker2 = index2;
	int iWorkID2 = m_cbWork2.GetItemData(index2);
	CString strWorkID;
	strWorkID.Format(_T("%d"), iWorkID);

	CString strWorkID2;
	strWorkID2.Format(_T("%d"), iWorkID2);

	CStringArray strWorker3;
	int nNum = 2;
	CString stringWorker3 = _T("select * from WORKERINFO where CLASSID = ")
		+ m_ClassID + _T(" and WORDERID not in ( ") + strWorkID + _T(",") + strWorkID2 +_T(")");
	CString columnWorker3[] = { _T("WORDERID"), _T("NAME") };
	theApp.m_database.GetData(stringWorker3, columnWorker3, nNum, strWorker3);

	int nRow = strWorker3.GetCount() / nNum;

	m_cbWork3.AddString(_T("��ѡ��"));
	m_cbWork3.SetItemData(0, -1);
	for (int i = 0; i < nRow; i++)
	{
		CString tempElec = strWorker3.GetAt((i)*nNum);
		int itempElec = _ttoi(tempElec);
		m_cbWork3.AddString(strWorker3.GetAt((i)*nNum + 1));
		m_cbWork3.SetItemData(i+1, itempElec);
	}
}

void CWorkRecord::OnCbnSelchangeCombo3()
{

	m_cbOperaTime.ResetContent();
	int index = m_cbOperate.GetCurSel();
	int operateID = m_cbOperate.GetItemData(index);
	//����վ��
	CStringArray strDataOperateTime;
	int nNum = 3;
	CString stringOperTimeSql;
	stringOperTimeSql.Format(_T("select *from OPERATECLASS where OPERATEID = %d"), operateID);
	CString columnOperTime[] = { _T("OPERATEID"), _T("MAXPEOPLE"), _T("NORMALTIME") };
	bool a = theApp.m_database.GetData(stringOperTimeSql, columnOperTime, nNum, strDataOperateTime);

	int nRow = strDataOperateTime.GetCount() / nNum;
	CString maxpeople = strDataOperateTime.GetAt(1);
	CString normalpeople = strDataOperateTime.GetAt(2);
	CString time;
	int iMaxPeople = _ttoi(maxpeople);
	for (int i = 1; i <= iMaxPeople; i++)
	{
		time.Format(_T("%d"), i);
		m_cbOperaTime.AddString(time);

		m_cbOperaTime.SelectString(0, normalpeople);
	}

}
void CWorkRecord::InitDriver()
{
	
	int nshow = 2;
	CString sql = _T("select * from DRIVER");
	CStringArray arrData;
	CString column[] = { _T("DRIVERID"), _T("NAME") };
	theApp.m_database.GetData(sql, column, nshow, arrData);
	int nRow = arrData.GetCount() / nshow;
	for (int i = 0; i < nRow;i++)
	{
		m_cbDriver.AddString(arrData.GetAt(i*nshow + 1));
		int a = _ttoi(arrData.GetAt(i*nshow));
		m_cbDriver.SetItemData(i,_ttoi(arrData.GetAt(i*nshow)));
	}
}
bool CWorkRecord::CheckMessageBox(CString strInfoName,CString strCheck)
{
	if (strCheck == _T(""))
	{
		MessageBox(strInfoName + _T("����Ϊ�գ�"));
		return false;
	}
	
	return true;
}