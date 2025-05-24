
// mapDlg.h : header file
//

#pragma once


// CmapDlg dialog
class CSetMapSize;
class CmapDlg : public CDialogEx
{
// Construction
public:
	CmapDlg(CWnd* pParent = nullptr);	// standard constructor
	~CmapDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAP_DIALOG };
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
	afx_msg void OnClickNewMap(); // This function is called when I click "New Map" item. that is need for set map size when start working

public:
	void EnableToolBox();  // This function is called when I set map size. this will enable tool box items.


private:
	CSetMapSize * m_pSetMapSize; // Set Map Size Dialog

	// Tool Box Items
	// Tool style
	CButton m_radioRiver;
	CButton m_radioLand;
	CButton m_radioErase;

	// Tool property
	CStatic m_staticToolSizeTitle;
	CSliderCtrl m_sliderToolSize;
	CStatic m_intToolSize;
	CStatic m_staticToolHeight;
	CSliderCtrl m_sliderToolHeight;
	CStatic m_intToolHeight;
	CButton m_btnMapSave;

public:
	int* m_pIntMapSizeArray;

public:
	int m_intWindowWidth;
	int m_intWindowHeight;
};
