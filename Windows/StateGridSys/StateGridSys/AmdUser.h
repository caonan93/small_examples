#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CAmdUser �Ի���

class CAmdUser : public CDialogEx
{
	DECLARE_DYNAMIC(CAmdUser)

public:
	CAmdUser(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAmdUser();

// �Ի�������
	enum { IDD = ID_AMID_USER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void PostNcDestroy();
public:
	CEdit m_strNameInput;
	CComboBox m_lsClass;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	void InitDialog();
	CListCtrl m_lscInfo;
	virtual BOOL OnInitDialog();
	void Search();
	void GetContrlData(CStringArray &arrData);
	void InitClassList();
	void InitClassSelList();
	void InitRMClassList();
	afx_msg void OnCbnSelchangeCombo5();
	CComboBox m_lsSelClass;
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton8();
	// ��ѡ��Ա����ӵ��༶
	CComboBox m_lsRmClass;
	// ��ʾ�೤
	CEdit m_edShowJob;
	int m_key;
	bool m_isUsedSelect;//�Ƿ����ѡ��༶
};
