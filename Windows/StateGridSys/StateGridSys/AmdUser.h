#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CAmdUser 对话框

class CAmdUser : public CDialogEx
{
	DECLARE_DYNAMIC(CAmdUser)

public:
	CAmdUser(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAmdUser();

// 对话框数据
	enum { IDD = ID_AMID_USER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
	// 将选中员工添加到班级
	CComboBox m_lsRmClass;
	// 显示班长
	CEdit m_edShowJob;
	int m_key;
	bool m_isUsedSelect;//是否调用选择班级
};
