#pragma once
#include "afxdialogex.h"


// CSetMapSize dialog
class CmapDlg;
class CSetMapSize : public CDialogEx
{
	DECLARE_DYNAMIC(CSetMapSize)

public:
	CSetMapSize(CmapDlg* pParent);   // standard constructor
	virtual ~CSetMapSize();

// Dialog Data
	enum { IDD = IDD_DIG_SETTING_SIZE_MAP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickSetButton();

public:
	CmapDlg* m_pWndParent;
	CComboBox m_comboWidthSize;
	CComboBox m_comboHeightSize;
};
