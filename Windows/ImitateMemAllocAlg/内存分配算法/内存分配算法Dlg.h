
// �ڴ�����㷨Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "SortNode.h"

// C�ڴ�����㷨Dlg �Ի���
class C�ڴ�����㷨Dlg : public CDialogEx
{
// ����
public:
	C�ڴ�����㷨Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY_DIALOG };

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
	afx_msg void OnBnClickedButton1();
	void InitSourceTable();
	void FistAdaptSort();
	void BestFirstSort();
	void BestSort();
	void BadSort();
	CListCtrl m_listInfo;
	// //ѡ���㷨
	CComboBox m_sortSelect;
	CEdit m_InPut;
	int m_nInput;
	afx_msg void OnBnClickedButton5();
	int m_nLeftNum;	
	afx_msg void OnBnClickedButton4();
	CString m_AddressStart;//��ʼ��ַ
	int m_nMark;
	int m_i;
	afx_msg void OnBnClickedButton2();
	CSortNode m_addSort;
	int m_nMarkSort;
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
};
