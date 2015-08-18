
// 内存分配算法Dlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "SortNode.h"

// C内存分配算法Dlg 对话框
class C内存分配算法Dlg : public CDialogEx
{
// 构造
public:
	C内存分配算法Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	void InitSourceTable();
	void FistAdaptSort();
	void BestFirstSort();
	void BestSort();
	void BadSort();
	CListCtrl m_listInfo;
	// //选择算法
	CComboBox m_sortSelect;
	CEdit m_InPut;
	int m_nInput;
	afx_msg void OnBnClickedButton5();
	int m_nLeftNum;	
	afx_msg void OnBnClickedButton4();
	CString m_AddressStart;//起始地址
	int m_nMark;
	int m_i;
	afx_msg void OnBnClickedButton2();
	CSortNode m_addSort;
	int m_nMarkSort;
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
};
