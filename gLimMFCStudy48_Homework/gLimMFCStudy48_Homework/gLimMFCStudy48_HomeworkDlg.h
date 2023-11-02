
// gLimMFCStudy48_HomeworkDlg.h : header file
//

#pragma once


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
};
