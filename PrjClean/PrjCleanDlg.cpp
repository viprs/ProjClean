
// PrjCleanDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PrjClean.h"
#include "PrjCleanDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBntRegist();
	afx_msg void OnBnClickedBntUnregist();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_BN_CLICKED(IDC_BNT_REGIST, &CAboutDlg::OnBnClickedBntRegist)
	ON_BN_CLICKED(IDC_BNT_UNREGIST, &CAboutDlg::OnBnClickedBntUnregist)
END_MESSAGE_MAP()


// CPrjCleanDlg dialog




CPrjCleanDlg::CPrjCleanDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPrjCleanDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPrjCleanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPrjCleanDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BNT_BROWSE, &CPrjCleanDlg::OnBnClickedBntBrowse)
	ON_BN_CLICKED(IDC_BNT_CLEAN, &CPrjCleanDlg::OnBnClickedBntClean)
END_MESSAGE_MAP()


// CPrjCleanDlg message handlers

BOOL CPrjCleanDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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
	((CButton*)GetDlgItem(IDC_CHECK_SOURCE_FILE_INCLUDE))->SetCheck(TRUE);

	int   argc=0; 
	CString   msg;
	CString sTemp;
	LPWSTR   *argv=::CommandLineToArgvW(::GetCommandLineW(),&argc);   

	for(int   i=1;i<argc;i++)   
	{
		msg+=argv[i];
		if(i!=argc-1)
			msg += _T(" ");
	}
	SetDlgItemText(IDC_EDIT_FILE_PATH,msg);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPrjCleanDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPrjCleanDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPrjCleanDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPrjCleanDlg::OnBnClickedBntBrowse()
{
	// TODO: Add your control notification handler code here
	BROWSEINFO   bi; 
	TCHAR   szBuffer[512]=_T("");   
	TCHAR   szFullPath[MAX_PATH]=_T("");   
	bi.hwndOwner   =   m_hWnd; 
	bi.pidlRoot   =   NULL;   
	bi.pszDisplayName   =   szBuffer;    
	bi.lpszTitle   =  _T("请选择文件夹");   
	bi.ulFlags   =   BIF_RETURNONLYFSDIRS|BIF_EDITBOX|BIF_BROWSEFORCOMPUTER; 
	bi.lpfn   =   NULL;
	bi.lParam   =   0;   
	bi.iImage   =   0;   
	ITEMIDLIST*   pidl   =   ::SHBrowseForFolder(&bi);  
	if(::SHGetPathFromIDList(pidl,szFullPath))    
	{   
		SetDlgItemText(IDC_EDIT_FILE_PATH,szFullPath);
	}
}
void CPrjCleanDlg::GetFileList(CString sFloderPath,CStringArray& aryFileList)
{
	if (sFloderPath.GetLength() == 0)
	{
		return;
	}
	CString sTemp;
	CString sDirPath;
	sDirPath = sFloderPath + _T("\\*");
	CFileFind ff;
	BOOL res = ff.FindFile(sDirPath);   
	while(res)
	{
		res = ff.FindNextFile();
		if(ff.IsDirectory() && !ff.IsDots())
		{
			GetFileList(ff.GetFilePath(),aryFileList);
			continue;
		}
		else if(!ff.IsDirectory() && !ff.IsDots())  
		{
			aryFileList.Add(ff.GetFilePath());			
		}

	}
	ff.Close();
}
void CPrjCleanDlg::OnBnClickedBntClean()
{
	// TODO: Add your control notification handler code here
	CStringArray aryFileList;
	CString sFilePath;
	CString sTemp;
	UpdateData();
	GetDlgItemText(IDC_EDIT_FILE_PATH,sFilePath);
	GetFileList(sFilePath,aryFileList);
	for (int i=0;i<aryFileList.GetCount();i++)
	{
		sTemp = aryFileList[i];
		if (isNeedDelete(sTemp))
		{
			if(!DeleteFile(sTemp))
			{
				SetFileAttributes(sTemp,FILE_ATTRIBUTE_NORMAL);
				if(DeleteFile(sTemp))
					AddMessageLine(sTemp);
			}
			else
				AddMessageLine(sTemp);
		}
	}
// 	sTemp = sFilePath + L"\\.svn";
// 	SetFileAttributes(sTemp,FILE_ATTRIBUTE_NORMAL);
// 	SHFILEOPSTRUCT   fileop; 
// 	fileop.hwnd      =   NULL; 
// 	fileop.wFunc     =   FO_DELETE; 
// 	fileop.pFrom     =   sTemp;   //注意，后面需要有一个\0字符 
// 	fileop.pTo       =   NULL; 
// 	fileop.fFlags    =   FOF_SILENT   |   FOF_NOCONFIRMATION; 
// 	SHFileOperation(&fileop);
// 	CString sCmd;
// 	CStringA sacmd;
// 	sCmd = L"del/s/q " + sTemp + L"\\*.*";
// 	sacmd = sCmd;
// 	WinExec(sacmd,SW_HIDE);
// 	sCmd = L"rmdir " + sTemp;
// 	sacmd = sCmd;
// 	WinExec(sacmd,SW_HIDE);
}


BOOL CPrjCleanDlg::isNeedDelete(CString sFilePath)
{
	BOOL NeedDelete = FALSE;
	BOOL isDeleteSourceFile = FALSE;
	CString sTemp;
	CString sExName;
	int nIndex = -1;
	nIndex = sFilePath.ReverseFind(_T('.'));
	if (nIndex != -1)
	{
		sTemp = sFilePath.Mid(nIndex+1);
	}
	sExName = sTemp;
	if(((CButton*)GetDlgItem(IDC_CHECK_SOURCE_FILE_INCLUDE))->GetCheck()==BST_CHECKED)
		isDeleteSourceFile = TRUE;
	do 
	{
		if(sExName.CompareNoCase(_T("ncb"))==0)
		{
			NeedDelete = TRUE;
			break;
		}
		if(sExName.CompareNoCase(_T("ilk"))==0)
		{
			NeedDelete = TRUE;
			break;
		}
		if(sExName.CompareNoCase(_T("obj"))==0)
		{
			NeedDelete = TRUE;
			break;
		}
		if(sExName.CompareNoCase(_T("idb"))==0)
		{
			NeedDelete = TRUE;
			break;
		}
		if(sExName.CompareNoCase(_T("pch"))==0)
		{
			NeedDelete = TRUE;
			break;
		}
		if(sExName.CompareNoCase(_T("aps"))==0)
		{
			NeedDelete = TRUE;
			break;
		}
		if(sExName.CompareNoCase(_T("htm"))==0)
		{
			NeedDelete = TRUE;
			break;
		}
		// [2011/2/22]
		// 生成的文件
		sTemp = GetParentDirName(sFilePath);
		if (sTemp.CompareNoCase(_T("Debug"))==0||
			sTemp.CompareNoCase(_T("i386"))==0||
			sTemp.CompareNoCase(_T("Release"))==0)
		{
			if(!isDeleteSourceFile)
			{
				NeedDelete = FALSE;
				break;
			}
			if(sExName.CompareNoCase(_T("exe"))==0)
			{
				NeedDelete = TRUE;
				break;
			}
			if(sExName.CompareNoCase(_T("dll"))==0)
			{
				NeedDelete = TRUE;
				break;
			}
			if(sExName.CompareNoCase(_T("pdb"))==0)
			{
				NeedDelete = TRUE;
				break;
			}
			if(sExName.CompareNoCase(_T("res"))==0)
			{
				NeedDelete = TRUE;
				break;
			}

			if(sExName.CompareNoCase(_T("dep"))==0)
			{
				NeedDelete = TRUE;
				break;
			}
			if(sExName.CompareNoCase(_T("manifest"))==0)
			{
				NeedDelete = TRUE;
				break;
			}
			if(sExName.CompareNoCase(_T("lib"))==0)
			{
				NeedDelete = TRUE;
				break;
			}

		}

	} while (0);
	return NeedDelete;
}

CString CPrjCleanDlg::GetParentDirName(CString sFilePath)
{
	int nIndex = -1;
	CString sTemp;
	nIndex = sFilePath.ReverseFind(_T('\\'));
	if (nIndex != -1)
	{
		sTemp = sFilePath.Left(nIndex);
		nIndex = sTemp.ReverseFind(_T('\\'));
		if (nIndex != -1)
		{
			sTemp = sTemp.Mid(nIndex+1);
		}
	}
	return sTemp;
}

void CPrjCleanDlg::AddMessageLine(CString sLine)
{
	CString sMesssage;
	GetDlgItemText(IDC_EDIT_MESSAGE,sMesssage);
	sMesssage += sLine + _T("\r\n");
	SetDlgItemText(IDC_EDIT_MESSAGE,sMesssage);
}

void CAboutDlg::OnBnClickedBntRegist()
{
	// TODO: Add your control notification handler code here
	HKEY hKeyPath = NULL;
	LRESULT lret = ERROR_SUCCESS;
	CString sLine;
	TCHAR szBuffer[MAX_PATH] = {0};
	GetModuleFileName(NULL,szBuffer,sizeof(szBuffer)/sizeof(szBuffer[0]));
	CString sFilePath = szBuffer;
	sFilePath += _T(" %1");
	do 
	{
		lret = RegCreateKey(HKEY_CLASSES_ROOT,_T("Folder\\shell\\CleanProject\\command"),&hKeyPath);
		if(lret != ERROR_SUCCESS)
		{
			sLine.Format(_T("RegCreateKey()->Fail:%d\r\n"),lret);
			break;
		}

		lret = RegSetValueEx(hKeyPath,NULL,0,REG_SZ,(const BYTE*)(LPCTSTR)sFilePath,wcslen(sFilePath)*2+2);
		if(lret != ERROR_SUCCESS)
		{
			sLine.Format(_T("RegCreateKey()->Fail:%d\r\n"),lret);
			break;
		}

		sLine.Format(_T("RegCreateKey()->Success\r\n"));

	} while (0);
	if(hKeyPath)
	{
		RegCloseKey(hKeyPath);
		hKeyPath = NULL;
	}	
	AfxMessageBox(sLine);
}

void CAboutDlg::OnBnClickedBntUnregist()
{
	// TODO: Add your control notification handler code here
	HKEY hKeyPath = NULL;
	LRESULT lret = ERROR_SUCCESS;
	CString sLine;
	do 
	{

		lret = RegOpenKey(HKEY_CLASSES_ROOT,_T("Folder\\shell"),&hKeyPath);
		if(lret != ERROR_SUCCESS)
		{
			sLine.Format(_T("RegOpenKey()->Fail:%d\r\n"),lret);
			break;
		}
		SHDeleteKey(hKeyPath,_T("CleanProject"));
		sLine.Format(_T("RegDeleteKey()->Success\r\n"));

	} while (0);
	if(hKeyPath)
	{
		RegCloseKey(hKeyPath);
		hKeyPath = NULL;
	}
	AfxMessageBox(sLine);

}
