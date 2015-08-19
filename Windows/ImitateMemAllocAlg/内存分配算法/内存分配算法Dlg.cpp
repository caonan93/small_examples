
// �ڴ�����㷨Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "�ڴ�����㷨.h"
#include "�ڴ�����㷨Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// C�ڴ�����㷨Dlg �Ի���



C�ڴ�����㷨Dlg::C�ڴ�����㷨Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C�ڴ�����㷨Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nLeftNum = 0;
	m_nMark = 0;
	m_nMarkSort = 0;
}

void C�ڴ�����㷨Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listInfo);
	DDX_Control(pDX, IDC_COMBO1, m_sortSelect);
	DDX_Control(pDX, IDC_EDIT3, m_InPut);
}

BEGIN_MESSAGE_MAP(C�ڴ�����㷨Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &C�ڴ�����㷨Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON5, &C�ڴ�����㷨Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &C�ڴ�����㷨Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &C�ڴ�����㷨Dlg::OnBnClickedButton2)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &C�ڴ�����㷨Dlg::OnNMDblclkList1)
END_MESSAGE_MAP()


// C�ڴ�����㷨Dlg ��Ϣ�������

BOOL C�ڴ�����㷨Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//��ʼ��
	
	m_listInfo.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	CRect rect;	
	m_listInfo.GetClientRect(rect);
	int nWidth = rect.Width();
	int column[][4] = { 0, IDC_RESOURCEID, LVCFMT_LEFT, nWidth / 100.0 * 10,
				1, IDC_STARTADRESS, LVCFMT_LEFT, nWidth / 100.0 * 30,
				2, IDC_SQUAREVALUE, LVCFMT_LEFT, nWidth / 100.0 * 30,
				3, IDC_STATE, LVCFMT_LEFT, nWidth / 100.0 * 30
	};
	CString str;
	for (int i = 0; i < 4;i++)
	{		
		str.LoadString(column[i][1]);
		m_listInfo.InsertColumn(column[i][0], str, column[i][2], column[i][3]);
	}
	InitSourceTable();

	/*HBITMAP hBitmap;
	CImage img;	
	CString strPath = _T("res\\0.bmp");
	
	img.Load(strPath);
	
	HDC hdc = ::GetDC(GetDlgItem(IDC_IMAG)->m_hWnd);//��ȡ�ؼ��Ļ���
	CRect irect;
	GetDlgItem(IDC_IMAG)->GetClientRect(irect);
	img.StretchBlt(hdc, irect);//���쿽��*/
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void C�ڴ�����㷨Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void C�ڴ�����㷨Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR C�ڴ�����㷨Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void C�ڴ�����㷨Dlg::InitSourceTable()
{
/*
	m_listInfo.InsertItem(0, _T("1"));
	m_listInfo.SetItemText(0, 1, _T("60"));
	m_listInfo.SetItemText(0, 2, _T("100"));

	m_listInfo.InsertItem(1, _T("20"));
	m_listInfo.SetItemText(1, 1, _T("200"));
	m_listInfo.InsertItem(2, _T("200"));
	m_listInfo.SetItemText(2, 1, _T("300"));
	m_listInfo.InsertItem(3, _T("100"));
	m_listInfo.SetItemText(3, 1, _T("700"));
	m_listInfo.InsertItem(4, _T("60"));
	m_listInfo.SetItemText(4, 1, _T("820"));
	m_listInfo.InsertItem(5, _T("120"));
	m_listInfo.SetItemText(5, 1, _T("900"));*/
	m_sortSelect.AddString(_T("�״���Ӧ�㷨"));
	m_sortSelect.AddString(_T("ѭ���״���Ӧ�㷨"));
	m_sortSelect.AddString(_T("�����Ӧ�㷨"));
	m_sortSelect.AddString(_T("�����Ӧ�㷨"));
	
}

void C�ڴ�����㷨Dlg::OnBnClickedButton1()//��ʼ����
{
	GetDlgItem(IDC_TABLE)->SetWindowText(_T("�ѷ��������"));
	CString str ;
	m_InPut.GetWindowText(str);
	if (!str)
	{
		//Ĭ������Ϊ0
		m_nInput = 0;
	}
	else
	{
		m_nInput = _ttoi(str);
	}
	
	m_sortSelect.GetWindowText(str);
	DWORD n = m_sortSelect.SelectString(0,str);
	
	switch (n)
	{
	case 0:
		FistAdaptSort();
		break;
	case 1:
		BestFirstSort();
		break;
	case 2:
		BadSort();
		break;
	case 3:
		BestSort();
		break;
	default:
		MessageBox(_T("��ѡ���㷨"));
		break;
	}

	///////////////////////////
	m_listInfo.DeleteAllItems();//����б�
	n = m_addSort.GetCount();
	CStringArray *pData = m_addSort.GetData();
	CString st_iTot;
	m_addSort.CreateReceive();//��ʼ��ˢ��
	for (int i = 0; i < n; i++)
	{
		st_iTot.Format(_T("%d"), i);
		m_listInfo.InsertItem(i, st_iTot);
		m_listInfo.SetItemText(i, 1, pData[1].GetAt(i));
		m_listInfo.SetItemText(i, 2, pData[2].GetAt(i));
		m_listInfo.SetItemText(i, 3, pData[3].GetAt(i));
	}
	//�ͷ�pdata
	delete[] pData;
	/////////////////////
}
void C�ڴ�����㷨Dlg::BadSort()
{
	if (!m_addSort.BadSort(m_nInput))
	{
		MessageBox(_T("û���㹻��С�Ŀ��з���"));
	}

	m_listInfo.DeleteAllItems();//����б�
	int n = m_addSort.GetCount();
	CStringArray *pData = m_addSort.GetData();
	CString st_iTot;
	m_addSort.CreateReceive();//��ʼ��ˢ��
	for (int i = 0; i < n; i++)
	{
		st_iTot.Format(_T("%d"), i);
		m_listInfo.InsertItem(i, st_iTot);
		m_listInfo.SetItemText(i, 1, pData[1].GetAt(i));
		m_listInfo.SetItemText(i, 2, pData[2].GetAt(i));
		m_listInfo.SetItemText(i, 3, pData[3].GetAt(i));
	}
	//�ͷ�pdata
	delete[] pData;
}
void C�ڴ�����㷨Dlg::BestSort()
{

	if (!m_addSort.BestSort(m_nInput))
	{
		MessageBox(_T("û���㹻��С�Ŀ��з���"));
	}

	m_listInfo.DeleteAllItems();//����б�
	int n = m_addSort.GetCount();
	CStringArray *pData = m_addSort.GetData();
	CString st_iTot;
	m_addSort.CreateReceive();//��ʼ��ˢ��
	for (int i = 0; i < n; i++)
	{
		st_iTot.Format(_T("%d"), i);
		m_listInfo.InsertItem(i, st_iTot);
		m_listInfo.SetItemText(i, 1, pData[1].GetAt(i));
		m_listInfo.SetItemText(i, 2, pData[2].GetAt(i));
		m_listInfo.SetItemText(i, 3, pData[3].GetAt(i));
	}
	//�ͷ�pdata
	delete[] pData;

}
void C�ڴ�����㷨Dlg::BestFirstSort()
{
	if (m_nMarkSort == 0)
	{
		FistAdaptSort();
		m_nMarkSort++;
		return;
	}
	
	if (!m_addSort.LoopSort(m_nInput))
	{
		MessageBox(_T("û���㹻��С�Ŀ��з���"));
	}

	m_listInfo.DeleteAllItems();//����б�
	int n = m_addSort.GetCount();
	CStringArray *pData = m_addSort.GetData();
	CString st_iTot;
	m_addSort.CreateReceive();//��ʼ��ˢ��
	for (int i = 0; i < n; i++)
	{
		st_iTot.Format(_T("%d"), i);
		m_listInfo.InsertItem(i, st_iTot);
		m_listInfo.SetItemText(i, 1, pData[1].GetAt(i));
		m_listInfo.SetItemText(i, 2, pData[2].GetAt(i));
		m_listInfo.SetItemText(i, 3, pData[3].GetAt(i));
	}
	//�ͷ�pdata
	delete[] pData;
}
void C�ڴ�����㷨Dlg::FistAdaptSort()//�״���Ӧ�㷨
{
	if (!m_addSort.FirstSort(m_nInput))
	{
		MessageBox(_T("û���㹻��С�Ŀ��з���"));
	}
	
	m_listInfo.DeleteAllItems();//����б�
	int n = m_addSort.GetCount();
	CStringArray *pData = m_addSort.GetData();
	CString st_iTot;
	m_addSort.CreateReceive();//��ʼ��ˢ��
	for (int i = 0; i < n; i++)
	{	
		st_iTot.Format(_T("%d"), i);
		m_listInfo.InsertItem(i, st_iTot);
		m_listInfo.SetItemText(i, 1, pData[1].GetAt(i));
		m_listInfo.SetItemText(i, 2, pData[2].GetAt(i));
		m_listInfo.SetItemText(i, 3, pData[3].GetAt(i));
	}
	//�ͷ�pdata
	delete[] pData;

}

void C�ڴ�����㷨Dlg::OnBnClickedButton5()
{
	//��Ӱ�ť
	CString str;
	CString StartAddress;//��ʼ��ַ
	CString SquareData;//������С
	m_nLeftNum = m_addSort.GetCount();
	if (m_nMark != 1)
	{
		GetDlgItem(IDC_INIT_ADDRESS)->GetWindowText(StartAddress);
		if (StartAddress == _T(""))
		{
			MessageBox(_T("��������ʼ��ַ"));
			return;
		}
		m_i = _ttoi(StartAddress);
	}
	GetDlgItem(IDC_INIT_SQUAREDATA)->GetWindowText(SquareData);
	if (SquareData == _T(""))
	{
		MessageBox(_T("�����������С"));
		return;
	}

	str.Format(_T("%d"), m_nLeftNum);
	m_listInfo.InsertItem(m_nLeftNum, str);//PID

	StartAddress.Format(_T("%d"), m_i);
	m_listInfo.SetItemText(m_nLeftNum, 1, StartAddress);

	
	m_listInfo.SetItemText(m_nLeftNum, 2, SquareData);
	m_i = _ttoi(StartAddress);

	m_addSort.CreateNodeList(m_nLeftNum, _ttoi(SquareData), m_i, HAVESPARATED);//��ӵ�����
	/////////////////////////////////////
	/*m_addSort.CreateReceive();
	int n = m_addSort.GetCount();
	CStringArray *pData = m_addSort.GetData();//��ȡ�ؼ�����
	m_listInfo.DeleteAllItems();
	CString st_iTot;
	for (int i = 0; i < n; i++)
	{
		st_iTot.Format(_T("%d"), i);
		m_listInfo.InsertItem(i, st_iTot);
		m_listInfo.SetItemText(i, 1, pData[1].GetAt(i));
		m_listInfo.SetItemText(i, 2, pData[2].GetAt(i));
		m_listInfo.SetItemText(i, 3, pData[3].GetAt(i));
	} 
	//�ͷ�pdata
	delete[] pData;*/
	//////////////////////////////////////
	m_i = m_i + _ttoi(SquareData);

	m_listInfo.SetItemText(m_nLeftNum, 3, _T("�ѷ���"));

	//m_nLeftNum++;
	GetDlgItem(IDC_INIT_SQUAREDATA)->SetWindowText(_T(""));
	GetDlgItem(IDC_INIT_ADDRESS)->SetWindowText(_T(""));

	m_nMark = 1;

}


void C�ڴ�����㷨Dlg::OnBnClickedButton4()
{
	// ���
	m_listInfo.DeleteAllItems();
	m_nMark = 0;
	m_nLeftNum = 0;
	m_addSort.delteAllList();

}


void C�ڴ�����㷨Dlg::OnBnClickedButton2()
{
	//�����ڴ�
	CString PID;
	CString strGet;
	GetDlgItem(IDC_PID)->GetWindowText(PID);
	if (PID == _T(""))
	{
		MessageBox(_T("������Ҫ���յĽ��̺�"));
		return;
	}
	int i = _ttoi(PID);
	strGet = m_listInfo.GetItemText(i,3);
	if (strGet == _T("�ѷ���"))
	{
		
		m_addSort.AlterListData(i, NOTSPAEATED);
		
	}
	else if (strGet == _T("���з���"))
	{
		MessageBox(_T("�÷����Ѿ��ǿ��з���"));
	}
	else
	{		
		MessageBox(_T("û�иý���"));
		return;
	}
	

	m_addSort.CreateReceive();// ���� �����ڿ��з����ϲ� ���غϲ��������
	int n = m_addSort.GetCount();
	CStringArray *pData = m_addSort.GetData();//��ȡ�ؼ�����
	m_listInfo.DeleteAllItems();
	CString st_iTot;
	for (int i = 0; i < n; i++)
	{
		st_iTot.Format(_T("%d"), i);
		m_listInfo.InsertItem(i, st_iTot);
		m_listInfo.SetItemText(i, 1, pData[1].GetAt(i));
		m_listInfo.SetItemText(i, 2, pData[2].GetAt(i));
		m_listInfo.SetItemText(i, 3, pData[3].GetAt(i));
	}
	//�ͷ�pdata
	delete[] pData;
}


void C�ڴ�����㷨Dlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	//˫��
	CPoint pt;
	::GetCursorPos(&pt);
	m_listInfo.ScreenToClient(&pt);
	int i = m_listInfo.HitTest(pt);
	CString strGet = m_listInfo.GetItemText(i, 3);
	if (strGet == _T("�ѷ���"))
	{

		m_addSort.AlterListData(i, NOTSPAEATED);

	}
	
	m_addSort.CreateReceive();// ���� �����ڿ��з����ϲ� ���غϲ��������
	int n = m_addSort.GetCount();
	CStringArray *pData = m_addSort.GetData();//��ȡ�ؼ�����
	m_listInfo.DeleteAllItems();
	CString st_iTot;
	for (int i = 0; i < n; i++)
	{
		st_iTot.Format(_T("%d"), i);
		m_listInfo.InsertItem(i, st_iTot);
		m_listInfo.SetItemText(i, 1, pData[1].GetAt(i));
		m_listInfo.SetItemText(i, 2, pData[2].GetAt(i));
		m_listInfo.SetItemText(i, 3, pData[3].GetAt(i));
	}
	//�ͷ�pdata
	delete[] pData;
	*pResult = 0;
}
