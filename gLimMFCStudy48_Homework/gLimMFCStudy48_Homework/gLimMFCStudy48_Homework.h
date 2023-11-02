
// gLimMFCStudy48_Homework.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CgLimMFCStudy48HomeworkApp:
// See gLimMFCStudy48_Homework.cpp for the implementation of this class
//

class CgLimMFCStudy48HomeworkApp : public CWinApp
{
public:
	CgLimMFCStudy48HomeworkApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CgLimMFCStudy48HomeworkApp theApp;
