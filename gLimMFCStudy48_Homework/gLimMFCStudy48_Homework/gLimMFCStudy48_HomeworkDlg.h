
// gLimMFCStudy48_HomeworkDlg.h : header file
//

#pragma once

#include "StaticImage.h"

// CgLimMFCStudy48HomeworkDlg dialog
class CgLimMFCStudy48HomeworkDlg : public CDialogEx
{
// Construction
public:
	CgLimMFCStudy48HomeworkDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLIMMFCSTUDY48_HOMEWORK_DIALOG };
#endif

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
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedMakecircel();
	afx_msg void OnBnClickedGravity();

public:	
	CStaticImage m_ctlScreen;
	int m_nRadius; // ¹ÝÁö¸§
	CString m_strImgSize;
	CString m_strCenterGravityX;
	CString m_strCenterGravityY;
};
