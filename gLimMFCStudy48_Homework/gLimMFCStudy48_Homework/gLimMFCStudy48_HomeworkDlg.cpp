
// gLimMFCStudy48_HomeworkDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "gLimMFCStudy48_Homework.h"
#include "gLimMFCStudy48_HomeworkDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CgLimMFCStudy48HomeworkDlg dialog



CgLimMFCStudy48HomeworkDlg::CgLimMFCStudy48HomeworkDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GLIMMFCSTUDY48_HOMEWORK_DIALOG, pParent)
	, m_nRadius(100)
	, m_strImgSize(_T(""))
	, m_strCenterGravityX(_T(""))
	, m_strCenterGravityY(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgLimMFCStudy48HomeworkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCREEN, m_ctlScreen);
	DDX_Text(pDX, IDC_RADIUS, m_nRadius);
	DDX_Text(pDX, IDC_STATIC_SIZE, m_strImgSize);
	DDX_Text(pDX, IDC_EDIT_X, m_strCenterGravityX);
	DDX_Text(pDX, IDC_EDIT_Y, m_strCenterGravityY);
}

BEGIN_MESSAGE_MAP(CgLimMFCStudy48HomeworkDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CgLimMFCStudy48HomeworkDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CgLimMFCStudy48HomeworkDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_MakeCircel, &CgLimMFCStudy48HomeworkDlg::OnBnClickedMakecircel)
	ON_BN_CLICKED(IDC_GRAVITY, &CgLimMFCStudy48HomeworkDlg::OnBnClickedGravity)
END_MESSAGE_MAP()


// CgLimMFCStudy48HomeworkDlg message handlers

BOOL CgLimMFCStudy48HomeworkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	//이미지 사이즈 표시 
	m_strImgSize.Format(_T("%d x %d"), m_ctlScreen.GetImageWidth(), m_ctlScreen.GetImageHeight());
	UpdateData(false);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CgLimMFCStudy48HomeworkDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CgLimMFCStudy48HomeworkDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CgLimMFCStudy48HomeworkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CgLimMFCStudy48HomeworkDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void CgLimMFCStudy48HomeworkDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CgLimMFCStudy48HomeworkDlg::OnBnClickedMakecircel()
{
	//clear
	m_ctlScreen.onClearImage();

	//update m_nRadius
	UpdateData();
	
	int xPos = rand() % m_ctlScreen.GetImageWidth();
	int yPos = rand() % m_ctlScreen.GetImageHeight();

	m_ctlScreen.onDrawCircel(xPos, yPos, m_nRadius);
}


void CgLimMFCStudy48HomeworkDlg::OnBnClickedGravity()
{
	
	DPOINT dCenterGravity;
	dCenterGravity = m_ctlScreen.GetImageCenterGravity();

	//update 
	m_strCenterGravityX.Format(_T("%3.2f"), dCenterGravity.x);
	m_strCenterGravityY.Format(_T("%3.2f"), dCenterGravity.y);
	UpdateData(false);

	m_ctlScreen.onDrawTargetMark(dCenterGravity, m_nRadius/10);
}
