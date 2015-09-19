
// MainDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CMainDlg 对话框
class CMainDlg : public CDialogEx
{
// 构造
public:
	CMainDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

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
	afx_msg void OnBnClickedVirWifi();
	afx_msg void OnBnClickedWifiSwitch();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedWifiInfModify();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedShowPassword();
//	CListBox m_ClientList;
//	CListCtrl m_ClientList;
	CListCtrl m_ClientList;
};
