#pragma once


// CMain �Ի���

class CMain : public CDialogEx
{
	DECLARE_DYNAMIC(CMain)

public:
	CMain(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMain();

// �Ի�������
	enum { IDD = IDD_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
