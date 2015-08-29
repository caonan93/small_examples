#pragma once


// CMain 对话框

class CMain : public CDialogEx
{
	DECLARE_DYNAMIC(CMain)

public:
	CMain(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMain();

// 对话框数据
	enum { IDD = IDD_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CDialog *m_pDlgNew;
	afx_msg void onBasicMenu(UINT uid);
	afx_msg void onBasicMenu2(UINT uid);
	afx_msg void onBasicMenu3(UINT uid);
	void DestroyChildWindow();
	CWnd* m_CwndParent;

	afx_msg void OnAmidDriver();
};
