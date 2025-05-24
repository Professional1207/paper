
// mapDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "map.h"
#include "mapDlg.h"
#include "afxdialogex.h"
#include "CSetMapSize.h"

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


// CmapDlg dialog



CmapDlg::CmapDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pSetMapSize = NULL;
	m_pIntMapSizeArray = NULL;
}

CmapDlg::~CmapDlg()
{
	if (m_pSetMapSize != NULL)
	{
		delete m_pSetMapSize;
		m_pSetMapSize = NULL;
	}

	if (m_pIntMapSizeArray != NULL)
	{
		delete[] m_pIntMapSizeArray;
		m_pIntMapSizeArray = NULL;
	}
}

void CmapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO_RIVER, m_radioRiver);
	DDX_Control(pDX, IDC_RADIO_LAND, m_radioLand);
	DDX_Control(pDX, IDC_RADIO_ERASE, m_radioErase);
	DDX_Control(pDX, IDC_STATIC_SIZE_TITLE, m_staticToolSizeTitle);
	DDX_Control(pDX, IDC_SLIDER_BRUSH_SIZE, m_sliderToolSize);
	DDX_Control(pDX, IDC_STATIC_BRUSH_SIZE_VALUE, m_intToolSize);
	DDX_Control(pDX, IDC_STATIC_HEIGHT_TITLE, m_staticToolHeight);
	DDX_Control(pDX, IDC_SLIDER_BRUSH_DEEP, m_sliderToolHeight);
	DDX_Control(pDX, IDC_STATIC_BRUSH_DEEP_VALUE, m_intToolHeight);
	DDX_Control(pDX, IDC_BUTTON_MAP_SAVE, m_btnMapSave);
}

BEGIN_MESSAGE_MAP(CmapDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_NEWMAP, &CmapDlg::OnClickNewMap)
END_MESSAGE_MAP()


// CmapDlg message handlers

BOOL CmapDlg::OnInitDialog()
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

	// TODO: Add extra initialization here
	
	//Initalize map size array
	m_pIntMapSizeArray = new int[2];
	m_pIntMapSizeArray[0] = 0; //Width
	m_pIntMapSizeArray[1] = 0; //Height

	m_intWindowWidth = GetSystemMetrics(SM_CXSCREEN);
	m_intWindowHeight = GetSystemMetrics(SM_CYSCREEN);
	SetWindowPos(NULL, 0, 0, m_intWindowWidth, m_intWindowHeight - 50, SWP_NOZORDER | SWP_SHOWWINDOW);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CmapDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CmapDlg::OnPaint()
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
HCURSOR CmapDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CmapDlg::OnClickNewMap()
{
	// TODO: Add your command handler code here
	if (m_pSetMapSize != NULL)
	{
		m_pSetMapSize->ShowWindow(SW_SHOW);
	}
	else
	{
		m_pSetMapSize = new CSetMapSize(this);
		m_pSetMapSize->Create(CSetMapSize::IDD);
	}
}

void CmapDlg::EnableToolBox()
{
	// Tool Box Items
	// Tool style
	m_radioRiver.EnableWindow(true);
	m_radioLand.EnableWindow(true);
	m_radioErase.EnableWindow(true);

	// Tool property
	m_staticToolSizeTitle.EnableWindow(true);
	m_sliderToolSize.EnableWindow(true);
	m_intToolSize.EnableWindow(true);
	m_staticToolHeight.EnableWindow(true);
	m_sliderToolHeight.EnableWindow(true);
	m_intToolHeight.EnableWindow(true);
	m_btnMapSave.EnableWindow(true);
}