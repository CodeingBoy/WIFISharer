
// MainDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CMainDlg �Ի���
class CMainDlg : public CDialogEx
{
// ����
public:
	CMainDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

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
