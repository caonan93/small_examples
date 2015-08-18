
// 内存分配算法Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "内存分配算法.h"
#include "内存分配算法Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// C内存分配算法Dlg 对话框



C内存分配算法Dlg::C内存分配算法Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C内存分配算法Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nLeftNum = 0;
	m_nMark = 0;
	m_nMarkSort = 0;
}

void C内存分配算法Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listInfo);
	DDX_Control(pDX, IDC_COMBO1, m_sortSelect);
	DDX_Control(pDX, IDC_EDIT3, m_InPut);
}

BEGIN_MESSAGE_MAP(C内存分配算法Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &C内存分配算法Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON5, &C内存分配算法Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &C内存分配算法Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &C内存分配算法Dlg::OnBnClickedButton2)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &C内存分配算法Dlg::OnNMDblclkList1)
END_MESSAGE_MAP()


// C内存分配算法Dlg 消息处理程序

BOOL C内存分配算法Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//初始化
	
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
	
	HDC hdc = ::GetDC(GetDlgItem(IDC_IMAG)->m_hWnd);//获取控件的画布
	CRect irect;
	GetDlgItem(IDC_IMAG)->GetClientRect(irect);
	img.StretchBlt(hdc, irect);//拉伸拷贝*/
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C内存分配算法Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C内存分配算法Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C内存分配算法Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void C内存分配算法Dlg::InitSourceTable()
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
	m_sortSelect.AddString(_T("首次适应算法"));
	m_sortSelect.AddString(_T("循环首次适应算法"));
	m_sortSelect.AddString(_T("最佳适应算法"));
	m_sortSelect.AddString(_T("最差适应算法"));
	
}

void C内存分配算法Dlg::OnBnClickedButton1()//开始分配
{
	GetDlgItem(IDC_TABLE)->SetWindowText(_T("已分配分区表"));
	CString str ;
	m_InPut.GetWindowText(str);
	if (!str)
	{
		//默认数据为0
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
		MessageBox(_T("请选择算法"));
		break;
	}

	///////////////////////////
	m_listInfo.DeleteAllItems();//清空列表
	n = m_addSort.GetCount();
	CStringArray *pData = m_addSort.GetData();
	CString st_iTot;
	m_addSort.CreateReceive();//初始化刷新
	for (int i = 0; i < n; i++)
	{
		st_iTot.Format(_T("%d"), i);
		m_listInfo.InsertItem(i, st_iTot);
		m_listInfo.SetItemText(i, 1, pData[1].GetAt(i));
		m_listInfo.SetItemText(i, 2, pData[2].GetAt(i));
		m_listInfo.SetItemText(i, 3, pData[3].GetAt(i));
	}
	//释放pdata
	delete[] pData;
	/////////////////////
}
void C内存分配算法Dlg::BadSort()
{
	if (!m_addSort.BadSort(m_nInput))
	{
		MessageBox(_T("没有足够大小的空闲分区"));
	}

	m_listInfo.DeleteAllItems();//清空列表
	int n = m_addSort.GetCount();
	CStringArray *pData = m_addSort.GetData();
	CString st_iTot;
	m_addSort.CreateReceive();//初始化刷新
	for (int i = 0; i < n; i++)
	{
		st_iTot.Format(_T("%d"), i);
		m_listInfo.InsertItem(i, st_iTot);
		m_listInfo.SetItemText(i, 1, pData[1].GetAt(i));
		m_listInfo.SetItemText(i, 2, pData[2].GetAt(i));
		m_listInfo.SetItemText(i, 3, pData[3].GetAt(i));
	}
	//释放pdata
	delete[] pData;
}
void C内存分配算法Dlg::BestSort()
{

	if (!m_addSort.BestSort(m_nInput))
	{
		MessageBox(_T("没有足够大小的空闲分区"));
	}

	m_listInfo.DeleteAllItems();//清空列表
	int n = m_addSort.GetCount();
	CStringArray *pData = m_addSort.GetData();
	CString st_iTot;
	m_addSort.CreateReceive();//初始化刷新
	for (int i = 0; i < n; i++)
	{
		st_iTot.Format(_T("%d"), i);
		m_listInfo.InsertItem(i, st_iTot);
		m_listInfo.SetItemText(i, 1, pData[1].GetAt(i));
		m_listInfo.SetItemText(i, 2, pData[2].GetAt(i));
		m_listInfo.SetItemText(i, 3, pData[3].GetAt(i));
	}
	//释放pdata
	delete[] pData;

}
void C内存分配算法Dlg::BestFirstSort()
{
	if (m_nMarkSort == 0)
	{
		FistAdaptSort();
		m_nMarkSort++;
		return;
	}
	
	if (!m_addSort.LoopSort(m_nInput))
	{
		MessageBox(_T("没有足够大小的空闲分区"));
	}

	m_listInfo.DeleteAllItems();//清空列表
	int n = m_addSort.GetCount();
	CStringArray *pData = m_addSort.GetData();
	CString st_iTot;
	m_addSort.CreateReceive();//初始化刷新
	for (int i = 0; i < n; i++)
	{
		st_iTot.Format(_T("%d"), i);
		m_listInfo.InsertItem(i, st_iTot);
		m_listInfo.SetItemText(i, 1, pData[1].GetAt(i));
		m_listInfo.SetItemText(i, 2, pData[2].GetAt(i));
		m_listInfo.SetItemText(i, 3, pData[3].GetAt(i));
	}
	//释放pdata
	delete[] pData;
}
void C内存分配算法Dlg::FistAdaptSort()//首次适应算法
{
	if (!m_addSort.FirstSort(m_nInput))
	{
		MessageBox(_T("没有足够大小的空闲分区"));
	}
	
	m_listInfo.DeleteAllItems();//清空列表
	int n = m_addSort.GetCount();
	CStringArray *pData = m_addSort.GetData();
	CString st_iTot;
	m_addSort.CreateReceive();//初始化刷新
	for (int i = 0; i < n; i++)
	{	
		st_iTot.Format(_T("%d"), i);
		m_listInfo.InsertItem(i, st_iTot);
		m_listInfo.SetItemText(i, 1, pData[1].GetAt(i));
		m_listInfo.SetItemText(i, 2, pData[2].GetAt(i));
		m_listInfo.SetItemText(i, 3, pData[3].GetAt(i));
	}
	//释放pdata
	delete[] pData;

}

void C内存分配算法Dlg::OnBnClickedButton5()
{
	//添加按钮
	CString str;
	CString StartAddress;//起始地址
	CString SquareData;//分区大小
	m_nLeftNum = m_addSort.GetCount();
	if (m_nMark != 1)
	{
		GetDlgItem(IDC_INIT_ADDRESS)->GetWindowText(StartAddress);
		if (StartAddress == _T(""))
		{
			MessageBox(_T("请输入起始地址"));
			return;
		}
		m_i = _ttoi(StartAddress);
	}
	GetDlgItem(IDC_INIT_SQUAREDATA)->GetWindowText(SquareData);
	if (SquareData == _T(""))
	{
		MessageBox(_T("请输入分区大小"));
		return;
	}

	str.Format(_T("%d"), m_nLeftNum);
	m_listInfo.InsertItem(m_nLeftNum, str);//PID

	StartAddress.Format(_T("%d"), m_i);
	m_listInfo.SetItemText(m_nLeftNum, 1, StartAddress);

	
	m_listInfo.SetItemText(m_nLeftNum, 2, SquareData);
	m_i = _ttoi(StartAddress);

	m_addSort.CreateNodeList(m_nLeftNum, _ttoi(SquareData), m_i, HAVESPARATED);//添加到链表
	/////////////////////////////////////
	/*m_addSort.CreateReceive();
	int n = m_addSort.GetCount();
	CStringArray *pData = m_addSort.GetData();//获取控件内容
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
	//释放pdata
	delete[] pData;*/
	//////////////////////////////////////
	m_i = m_i + _ttoi(SquareData);

	m_listInfo.SetItemText(m_nLeftNum, 3, _T("已分配"));

	//m_nLeftNum++;
	GetDlgItem(IDC_INIT_SQUAREDATA)->SetWindowText(_T(""));
	GetDlgItem(IDC_INIT_ADDRESS)->SetWindowText(_T(""));

	m_nMark = 1;

}


void C内存分配算法Dlg::OnBnClickedButton4()
{
	// 清空
	m_listInfo.DeleteAllItems();
	m_nMark = 0;
	m_nLeftNum = 0;
	m_addSort.delteAllList();

}


void C内存分配算法Dlg::OnBnClickedButton2()
{
	//回收内存
	CString PID;
	CString strGet;
	GetDlgItem(IDC_PID)->GetWindowText(PID);
	if (PID == _T(""))
	{
		MessageBox(_T("请输入要回收的进程号"));
		return;
	}
	int i = _ttoi(PID);
	strGet = m_listInfo.GetItemText(i,3);
	if (strGet == _T("已分配"))
	{
		
		m_addSort.AlterListData(i, NOTSPAEATED);
		
	}
	else if (strGet == _T("空闲分区"))
	{
		MessageBox(_T("该分区已经是空闲分区"));
	}
	else
	{		
		MessageBox(_T("没有该进程"));
		return;
	}
	

	m_addSort.CreateReceive();// 回收 将相邻空闲分区合并 返回合并后的行数
	int n = m_addSort.GetCount();
	CStringArray *pData = m_addSort.GetData();//获取控件内容
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
	//释放pdata
	delete[] pData;
}


void C内存分配算法Dlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	//双击
	CPoint pt;
	::GetCursorPos(&pt);
	m_listInfo.ScreenToClient(&pt);
	int i = m_listInfo.HitTest(pt);
	CString strGet = m_listInfo.GetItemText(i, 3);
	if (strGet == _T("已分配"))
	{

		m_addSort.AlterListData(i, NOTSPAEATED);

	}
	
	m_addSort.CreateReceive();// 回收 将相邻空闲分区合并 返回合并后的行数
	int n = m_addSort.GetCount();
	CStringArray *pData = m_addSort.GetData();//获取控件内容
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
	//释放pdata
	delete[] pData;
	*pResult = 0;
}
