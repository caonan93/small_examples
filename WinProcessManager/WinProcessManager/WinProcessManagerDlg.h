
// WinProcessManagerDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include <Tlhelp32.h>
#include <Psapi.h>
#include "afxwin.h"
#include "list_Right.h"
#pragma comment(lib,"Psapi.Lib")
#define G 1024*1024*1024
#define K 1024
// CMyWinProcessManagerDlg 对话框
class CMyWinProcessManagerDlg : public CDialogEx
{
// 构造
public:
	CMyWinProcessManagerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY812_DIALOG };

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
	afx_msg void OnBnClickedExit();
	CListCtrl m_ListctrlLeft;
	CRect m_bigrect;
	CRect m_smallrect;
	afx_msg void OnBnClickedModify();
	CListCtrl m_listctrRight;
	void showprocesslist();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int m_nitem;
	DWORD m_dwProcess;
	afx_msg void OnBnClickedClosethread();
	afx_msg void OnBnClickedRefresh();
	CEdit m_rightmodify;
	afx_msg void OnBnClickedSerach();
	bool m_isFirst;//是否是第一次遍历内存
	void FindFirst();
	void FindNext();
	void FindOpenPage(DWORD addreass,const int value);
	CEdit m_value;//要搜索的值
public:
	list_Right m_listright;

};
