
// StateGridSysDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CStateGridSysDlg �Ի���
class CStateGridSysDlg : public CDialogEx
{
// ����
public:
	CStateGridSysDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_STATEGRIDSYS_DIALOG };

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
	afx_msg void OnBnClickedButton2();
	CEdit m_sUserInput;
	CEdit m_sPassWd;
	
};
