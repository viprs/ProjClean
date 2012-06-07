
// PrjCleanDlg.h : header file
//

#pragma once


// CPrjCleanDlg dialog
class CPrjCleanDlg : public CDialog
{
// Construction
public:
	CPrjCleanDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PRJCLEAN_DIALOG };

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
	afx_msg void OnBnClickedBntBrowse();
	afx_msg void OnBnClickedBntClean();
	void GetFileList(CString sFloderPath,CStringArray& aryFileList);
	BOOL isNeedDelete(CString sExName);
	CString GetParentDirName(CString sFilePath);
	void AddMessageLine(CString sLine);
};
