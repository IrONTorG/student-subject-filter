#pragma once

#include <afxwin.h>
#include <afxcmn.h>
#include <string>
#include "StudentFilter.h"
#include <atlconv.h> 
#include <atlstr.h>  

class CStudentFilterAppDlg : public CDialogEx
{
public:
    CStudentFilterAppDlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_STUDENTFILTERAPP_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);

    HICON m_hIcon;
    CListBox m_listResult;

    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnBnClickedButtonLoad();
    afx_msg void OnBnClickedButtonFilter();

    DECLARE_MESSAGE_MAP()
};