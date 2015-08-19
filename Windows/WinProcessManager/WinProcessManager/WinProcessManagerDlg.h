
// WinProcessManagerDlg.h : ͷ�ļ�
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
// CMyWinProcessManagerDlg �Ի���
class CMyWinProcessManagerDlg : public CDialogEx
{
// ����
public:
	CMyWinProcessManagerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY812_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	bool m_isFirst;//�Ƿ��ǵ�һ�α����ڴ�
	void FindFirst();
	void FindNext();
	void FindOpenPage(DWORD addreass,const int value);
	CEdit m_value;//Ҫ������ֵ
public:
	list_Right m_listright;

};
