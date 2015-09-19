
// MainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "WifiManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMainDlg 对话框



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


// CMainDlg 消息处理程序

BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 初始化List
	m_ClientList.InsertColumn(0, _T("编号"), LVCFMT_CENTER, 40);
	m_ClientList.InsertColumn(1, _T("类型"), LVCFMT_CENTER, 80);
	m_ClientList.InsertColumn(2, _T("MAC 地址"), LVCFMT_CENTER, 130);
	m_ClientList.InsertColumn(3, _T("IP 地址"), LVCFMT_CENTER, 100);
	m_ClientList.InsertItem(0, _T("1")); m_ClientList.SetItemText(0, 1, _T("不知道")); m_ClientList.SetItemText(0, 2, _T("00:00;00:00:00")); m_ClientList.SetItemText(0, 3, _T("192.168.1.1"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMainDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMainDlg::OnBnClickedVirWifi()
{
	CString btnText;
	GetDlgItem(IDC_VIR_WIFI)->GetWindowTextW(btnText);
	if (btnText != "启用虚拟网卡") // 禁用虚拟网卡
	{
		CWifiManager::setVirtualWLAN(false, NULL, NULL);
		GetDlgItem(IDC_VIR_WIFI)->SetWindowTextW(_T("启用虚拟网卡"));
		GetDlgItem(IDC_VIR_STATUS)->SetWindowTextW(_T("虚拟网卡状态：未启用"));
		GetDlgItem(IDC_WIFI_SWITCH)->EnableWindow(false);
		return;
	}
	// 读取 WIFI 信息
	CString SSID, password;
	returnresult returnResult;
	GetDlgItem(IDC_WIFI_SSID)->GetWindowTextW(SSID);
	GetDlgItem(IDC_WIFI_PASSWORD)->GetWindowTextW(password);
	if (SSID == "" || password == "")
	{
		MessageBox(_T("没有正确填写 WIFI 名称或密码，请检查后重试。"), _T("出错了！"), MB_ICONERROR);
		return;
	}
	
	if (!CWifiManager::setVirtualWLAN(true, SSID, password))
	{
		MessageBox(_T("出现了错误"), _T("出错了！"), MB_ICONERROR);
		return;
	}
	GetDlgItem(IDC_VIR_WIFI)->SetWindowTextW(_T("禁用虚拟网卡"));
	GetDlgItem(IDC_VIR_STATUS)->SetWindowTextW(_T("虚拟网卡状态：已启用"));
	((CButton*)(GetDlgItem(IDC_WIFI_SWITCH)))->EnableWindow(true);
}


void CMainDlg::OnBnClickedWifiSwitch()
{
	CString btnText;
	GetDlgItem(IDC_WIFI_SWITCH)->GetWindowTextW(btnText);
	if (btnText != "开启 WIFI 热点") // 关闭 WIFI 热点
	{
		CWifiManager::switchWIFI(false);
		GetDlgItem(IDC_WIFI_SWITCH)->SetWindowTextW(_T("开启 WIFI 热点"));
		((CButton*)(GetDlgItem(IDC_VIR_WIFI)))->EnableWindow(true);
		GetDlgItem(IDC_WIFI_STATUS)->SetWindowTextW(_T("WIFI 热点状态：未启用"));
		return;
	}
	CWifiManager::switchWIFI(true);
	GetDlgItem(IDC_WIFI_SWITCH)->SetWindowTextW(_T("关闭 WIFI 热点"));
	((CButton*)(GetDlgItem(IDC_VIR_WIFI)))->EnableWindow(false);
	GetDlgItem(IDC_WIFI_STATUS)->SetWindowTextW(_T("WIFI 热点状态：已启用"));
	return;
}


void CMainDlg::OnBnClickedWifiInfModify()
{
	// 读取 WIFI 信息
	CString SSID, password;
	returnresult returnResult;
	GetDlgItem(IDC_WIFI_SSID)->GetWindowTextW(SSID);
	GetDlgItem(IDC_WIFI_PASSWORD)->GetWindowTextW(password);
	if (SSID == "" || password == "")
	{
		MessageBox(_T("没有正确填写 WIFI 名称或密码，请检查后重试。"), _T("出错了！"), MB_ICONERROR);
		return;
	}
	if (CWifiManager::modifyWIFIInf(SSID, password))GetDlgItem(IDC_WIFI_INF_MODIFY)->SetWindowTextW(_T("成功"));
	SetTimer(1, 5000, NULL);
}


void CMainDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case 1:
		GetDlgItem(IDC_WIFI_INF_MODIFY)->SetWindowTextW(_T("修改"));
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
	case BST_CHECKED: // 显示密码
		//((CEdit*)GetDlgItem(IDC_WIFI_PASSWORD))->ModifyStyle(NULL, NULL);
		((CEdit*)GetDlgItem(IDC_WIFI_PASSWORD))->SetPasswordChar(NULL);

		break;
	case BST_UNCHECKED: // 隐藏密码
		//((CEdit*)GetDlgItem(IDC_WIFI_PASSWORD))->ModifyStyle(NULL, ES_PASSWORD);
		((CEdit*)GetDlgItem(IDC_WIFI_PASSWORD))->SetPasswordChar(_T('*'));
		break;
	}
	((CEdit*)GetDlgItem(IDC_WIFI_PASSWORD))->RedrawWindow(NULL, NULL);
}
