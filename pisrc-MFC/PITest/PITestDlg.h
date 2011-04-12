// PITestDlg.h : header file
//

#pragma once
#include "afxcmn.h"


// CPITestDlg dialog
class CPITestDlg : public CDialog
{
// Construction
public:
	CPITestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PITEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnSearch();
	// 搜索到的点的列表
	CListCtrl m_listPoints;
};
