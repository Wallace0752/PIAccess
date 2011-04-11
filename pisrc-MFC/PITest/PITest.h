// PITest.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPITestApp:
// See PITest.cpp for the implementation of this class
//

class CPITestApp : public CWinApp
{
public:
	CPITestApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
	afx_msg void OnFunctionConnect();
	afx_msg void OnFunctionDisconnect();
};

extern CPITestApp theApp;