// PITestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PITest.h"
#include "PITestDlg.h"
#include "piPointConfig.h"
#include <atlconv.h>
//#include "piapix.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//#pragma   comment(lib, "piapi32.lib ")

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CPITestDlg dialog




CPITestDlg::CPITestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPITestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPITestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PT, m_listPoints);
}

BEGIN_MESSAGE_MAP(CPITestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_SEARCH, &CPITestDlg::OnBnClickedBtnSearch)
END_MESSAGE_MAP()


// CPITestDlg message handlers

BOOL CPITestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
//	char version[32];
// 	USES_CONVERSION;
// 	if (!piut_getapiversion(version,sizeof(version)))
// 	{
// 		SetDlgItemText(IDC_STATIC_VERSION,A2CT(version));
// 	}
	LPTSTR str = new TCHAR[32];
	if (PIUT_GetApiVersion(str))
	{
		SetDlgItemText(IDC_STATIC_VERSION,str);
	}
	delete str;
	//m_listPoints.SetItemCount(ITEM_COUNT);
	//m_listPoints.InsertItem(0,NULL);
	m_listPoints.InsertColumn(0,_T("Tag Name"));
	m_listPoints.InsertColumn(1,_T("Point Type"));
	m_listPoints.InsertColumn(2,_T("Value"));
	m_listPoints.InsertColumn(3,_T("Time Stamp"));
	m_listPoints.SetColumnWidth(0,LVSCW_AUTOSIZE_USEHEADER);
	m_listPoints.SetColumnWidth(1,LVSCW_AUTOSIZE_USEHEADER);
	m_listPoints.SetColumnWidth(2,LVSCW_AUTOSIZE_USEHEADER);
	m_listPoints.SetColumnWidth(3,LVSCW_AUTOSIZE_USEHEADER);
	//UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPITestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPITestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPITestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPITestDlg::OnBnClickedBtnSearch()
{
	// TODO: Add your control notification handler code here

// 	char v[32];
// 	piut_getapiversion(v,sizeof(v));
//  	HINSTANCE hs = LoadLibrary(_T("PIInterface.dll"));
// 	typedef int (*ADDPROC)(int a, int b);
// 	ADDPROC Add = (ADDPROC)GetProcAddress(hs,"add");
// 	if (!Add)
// 	{
// 		CString lpMsgBuf;
// 		FormatMessage( 
// 			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
// 			FORMAT_MESSAGE_FROM_SYSTEM | 
// 			FORMAT_MESSAGE_IGNORE_INSERTS, 
// 			NULL, 
// 			GetLastError(), 
// 			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language 
// 			(LPTSTR) &lpMsgBuf, 
// 			0, 
// 			NULL 
// 			); 
// 
// 		AfxMessageBox(lpMsgBuf);
// 		return;
// 	}
 	CString str;
 	str.Format(_T("3+5=%d"),add(3,5));
 	AfxMessageBox(str);
/*	FreeLibrary(hs);*/

}
