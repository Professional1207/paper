// CSetMapSize.cpp : implementation file
//

#include "pch.h"
#include "map.h"
#include "afxdialogex.h"
#include "CSetMapSize.h"
#include "mapDlg.h"


// CSetMapSize dialog

IMPLEMENT_DYNAMIC(CSetMapSize, CDialogEx)

CSetMapSize::CSetMapSize(CmapDlg* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIG_SETTING_SIZE_MAP, pParent)
{
	m_pWndParent = pParent;
}

CSetMapSize::~CSetMapSize()
{
}

void CSetMapSize::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_WIDTH_MAP_SIZE, m_comboWidthSize);
	DDX_Control(pDX, IDC_COMBO_HEIGHT_MAP_SIZE, m_comboHeightSize);
}


BEGIN_MESSAGE_MAP(CSetMapSize, CDialogEx)
	ON_BN_CLICKED(IDC_SET_BUTTON, &CSetMapSize::OnClickSetButton)
END_MESSAGE_MAP()



BOOL CSetMapSize::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString strConvertedString = _T("");
	for (int i = 100; i <= 500; i += 100)
	{
		strConvertedString.Format(_T("%d"), i);
		m_comboWidthSize.AddString(strConvertedString);
		m_comboHeightSize.AddString(strConvertedString);
	}

	return TRUE;
}

// CSetMapSize message handlers

void CSetMapSize::OnClickSetButton()
{
	// TODO: Add your control notification handler code here
	CString strMapWidthSizeString = _T("");
	CString strMapHeightSizeString = _T("");
	m_comboWidthSize.GetWindowTextW(strMapWidthSizeString);
	m_comboHeightSize.GetWindowTextW(strMapHeightSizeString);
	if (strMapWidthSizeString != _T(""))
	{
		if (strMapHeightSizeString != _T(""))
		{
			m_pWndParent->m_pIntMapSizeArray[0] = _ttoi(strMapWidthSizeString);
			m_pWndParent->m_pIntMapSizeArray[1] = _ttoi(strMapHeightSizeString);			
			m_pWndParent->EnableToolBox();
			this->ShowWindow(SW_HIDE);
		}
		else
		{
			MessageBox(_T("Select Map Height size."));
		}
	}
	else
	{
		MessageBox(_T("Select Map Width Size."));
	}
}
