
#include "pch.h"
#include "framework.h"
#include "StudentFilterApp.h"
#include "StudentFilterAppDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "StudentFilter.h"
#include "Logger.h"



class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();


#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);   


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






CStudentFilterAppDlg::CStudentFilterAppDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STUDENTFILTERAPP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStudentFilterAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_RESULT, m_listResult);
}

BEGIN_MESSAGE_MAP(CStudentFilterAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CStudentFilterAppDlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_FILTER, &CStudentFilterAppDlg::OnBnClickedButtonFilter)
END_MESSAGE_MAP()




BOOL CStudentFilterAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	


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

	
	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		



	return TRUE;  
}

void CStudentFilterAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
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


void CStudentFilterAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); 

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;


		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}


HCURSOR CStudentFilterAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CStudentFilterAppDlg::OnBnClickedButtonLoad() {
    try {
        
        TCHAR path[MAX_PATH];
        GetModuleFileName(NULL, path, MAX_PATH);
        CString exePath(path);
        exePath = exePath.Left(exePath.ReverseFind('\\'));

        CString filePath = exePath + _T("\\Students.txt");

      
        std::string narrowPath(CW2A(filePath.GetString()));

     
        StudentFilter filter;
        if (!filter.LoadFromFile(narrowPath)) {
            MessageBox(_T("Не удалось загрузить файл"), _T("Ошибка"), MB_ICONERROR);
            return;
        }

    
        size_t total = 0;
        for (const auto& pair : filter.GetData()) {
            total += pair.second.size();
        }

        CString msg;
        msg.Format(_T("Загружено студентов: %d"), total);
        m_listResult.ResetContent();
        m_listResult.AddString(msg);
    }
    catch (...) {
        MessageBox(_T("Ошибка при загрузке"), _T("Ошибка"), MB_ICONERROR);
    }
}



void CStudentFilterAppDlg::OnBnClickedButtonFilter() {
    try {
      
        TCHAR path[MAX_PATH];
        GetModuleFileName(NULL, path, MAX_PATH);
        CString exePath(path);
        exePath = exePath.Left(exePath.ReverseFind('\\'));

       
        CString filePath = exePath + _T("\\Students.txt");
        std::string narrowPath(CW2A(filePath.GetString()));

       
        StudentFilter filter;
        if (!filter.LoadFromFile(narrowPath)) {
            MessageBox(_T("Не удалось загрузить файл"), _T("Ошибка"), MB_ICONERROR);
            return;
        }

        std::vector<std::string> include = { "биология", "химия" };
        std::vector<std::string> exclude = { "физика" };
        auto result = filter.FilterStudents(include, exclude);

       
        m_listResult.ResetContent();
        for (const auto& student : result) {
            std::string translitStudent = StudentFilter::Transliterate(student);
            m_listResult.AddString(CString(translitStudent.c_str()));
        }

       
        std::string outputPath = narrowPath.substr(0, narrowPath.find_last_of('\\')) + "\\FilteredStudents.txt";
        std::ofstream out(outputPath);
        for (const auto& student : result) {
            std::string translitStudent = StudentFilter::Transliterate(student);
            out << translitStudent << "\n";
            OutputDebugStringA(("Saved student: " + translitStudent + "\n").c_str());
        }

       
        CString msg;
        msg.Format(_T("Найдено студентов: %d"), result.size());
        MessageBox(msg, _T("Результат"), MB_OK);
    }
    catch (const std::exception& e) {
        
        CString errorMsg;
        std::string utf8Error = e.what();
        int size = MultiByteToWideChar(CP_UTF8, 0, utf8Error.c_str(), -1, NULL, 0);
        wchar_t* wideError = new wchar_t[size];
        MultiByteToWideChar(CP_UTF8, 0, utf8Error.c_str(), -1, wideError, size);
        errorMsg.Format(_T("Ошибка: %s"), wideError);
        delete[] wideError;

        MessageBox(errorMsg, _T("Ошибка"), MB_ICONERROR);
    }
    catch (...) {
        MessageBox(_T("Неизвестная ошибка фильтрации"), _T("Ошибка"), MB_ICONERROR);
    }
}