
// MainDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "WifiManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMainDlg �Ի���



CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CLIENT_LIST, m_ClientList);
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_VIR_WIFI, &CMainDlg::OnBnClickedVirWifi)
	ON_BN_CLICKED(IDC_WIFI_SWITCH, &CMainDlg::OnBnClickedWifiSwitch)
	ON_BN_CLICKED(IDC_WIFI_INF_MODIFY, &CMainDlg::OnBnClickedWifiInfModify)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SHOW_PASSWORD, &CMainDlg::OnBnClickedShowPassword)
END_MESSAGE_MAP()


// CMainDlg ��Ϣ�������

BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// ��ʼ��List
	m_ClientList.InsertColumn(0, _T("���"), LVCFMT_CENTER, 40);
	m_ClientList.InsertColumn(1, _T("����"), LVCFMT_CENTER, 80);
	m_ClientList.InsertColumn(2, _T("MAC ��ַ"), LVCFMT_CENTER, 130);
	m_ClientList.InsertColumn(3, _T("IP ��ַ"), LVCFMT_CENTER, 100);
	m_ClientList.InsertItem(0, _T("1")); m_ClientList.SetItemText(0, 1, _T("��֪��")); m_ClientList.SetItemText(0, 2, _T("00:00;00:00:00")); m_ClientList.SetItemText(0, 3, _T("192.168.1.1"));

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMainDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMainDlg::OnBnClickedVirWifi()
{
	CString btnText;
	GetDlgItem(IDC_VIR_WIFI)->GetWindowTextW(btnText);
	if (btnText != "������������") // ������������
	{
		CWifiManager::setVirtualWLAN(false, NULL, NULL);
		GetDlgItem(IDC_VIR_WIFI)->SetWindowTextW(_T("������������"));
		GetDlgItem(IDC_VIR_STATUS)->SetWindowTextW(_T("��������״̬��δ����"));
		GetDlgItem(IDC_WIFI_SWITCH)->EnableWindow(false);
		return;
	}
	// ��ȡ WIFI ��Ϣ
	CString SSID, password;
	returnresult returnResult;
	GetDlgItem(IDC_WIFI_SSID)->GetWindowTextW(SSID);
	GetDlgItem(IDC_WIFI_PASSWORD)->GetWindowTextW(password);
	if (SSID == "" || password == "")
	{
		MessageBox(_T("û����ȷ��д WIFI ���ƻ����룬��������ԡ�"), _T("�����ˣ�"), MB_ICONERROR);
		return;
	}
	
	if (!CWifiManager::setVirtualWLAN(true, SSID, password))
	{
		MessageBox(_T("�����˴���"), _T("�����ˣ�"), MB_ICONERROR);
		return;
	}
	GetDlgItem(IDC_VIR_WIFI)->SetWindowTextW(_T("������������"));
	GetDlgItem(IDC_VIR_STATUS)->SetWindowTextW(_T("��������״̬��������"));
	((CButton*)(GetDlgItem(IDC_WIFI_SWITCH)))->EnableWindow(true);
}


void CMainDlg::OnBnClickedWifiSwitch()
{
	CString btnText;
	GetDlgItem(IDC_WIFI_SWITCH)->GetWindowTextW(btnText);
	if (btnText != "���� WIFI �ȵ�") // �ر� WIFI �ȵ�
	{
		CWifiManager::switchWIFI(false);
		GetDlgItem(IDC_WIFI_SWITCH)->SetWindowTextW(_T("���� WIFI �ȵ�"));
		((CButton*)(GetDlgItem(IDC_VIR_WIFI)))->EnableWindow(true);
		GetDlgItem(IDC_WIFI_STATUS)->SetWindowTextW(_T("WIFI �ȵ�״̬��δ����"));
		return;
	}
	CWifiManager::switchWIFI(true);
	GetDlgItem(IDC_WIFI_SWITCH)->SetWindowTextW(_T("�ر� WIFI �ȵ�"));
	((CButton*)(GetDlgItem(IDC_VIR_WIFI)))->EnableWindow(false);
	GetDlgItem(IDC_WIFI_STATUS)->SetWindowTextW(_T("WIFI �ȵ�״̬��������"));
	return;
}


void CMainDlg::OnBnClickedWifiInfModify()
{
	// ��ȡ WIFI ��Ϣ
	CString SSID, password;
	returnresult returnResult;
	GetDlgItem(IDC_WIFI_SSID)->GetWindowTextW(SSID);
	GetDlgItem(IDC_WIFI_PASSWORD)->GetWindowTextW(password);
	if (SSID == "" || password == "")
	{
		MessageBox(_T("û����ȷ��д WIFI ���ƻ����룬��������ԡ�"), _T("�����ˣ�"), MB_ICONERROR);
		return;
	}
	if (CWifiManager::modifyWIFIInf(SSID, password))GetDlgItem(IDC_WIFI_INF_MODIFY)->SetWindowTextW(_T("�ɹ�"));
	SetTimer(1, 5000, NULL);
}


void CMainDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case 1:
		GetDlgItem(IDC_WIFI_INF_MODIFY)->SetWindowTextW(_T("�޸�"));
		KillTimer(1);
		break;
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CMainDlg::OnBnClickedShowPassword()
{
	switch (((CButton*)GetDlgItem(IDC_SHOW_PASSWORD))->GetCheck())
	{
	case BST_CHECKED: // ��ʾ����
		//((CEdit*)GetDlgItem(IDC_WIFI_PASSWORD))->ModifyStyle(NULL, NULL);
		((CEdit*)GetDlgItem(IDC_WIFI_PASSWORD))->SetPasswordChar(NULL);

		break;
	case BST_UNCHECKED: // ��������
		//((CEdit*)GetDlgItem(IDC_WIFI_PASSWORD))->ModifyStyle(NULL, ES_PASSWORD);
		((CEdit*)GetDlgItem(IDC_WIFI_PASSWORD))->SetPasswordChar(_T('*'));
		break;
	}
	((CEdit*)GetDlgItem(IDC_WIFI_PASSWORD))->RedrawWindow(NULL, NULL);
}
