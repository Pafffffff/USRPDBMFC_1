
// USRPDBMFCDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "USRPDBMFC.h"
#include "USRPDBMFCDlg.h"
#include "afxdialogex.h"
#include "TabSheet.h"
#include "CDlgAdmin.h"
#include "CDlgOperator.h"
//#include "predTa19.h"
//#include "predTi17.h"
//#include "predGH4169.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CUSRPDBMFCDlg 对话框



CUSRPDBMFCDlg::CUSRPDBMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_USRPDBMFC_DIALOG, pParent)
	, m_Name(_T(""))
	, m_Pwd(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_BADGE);
}

void CUSRPDBMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LOGINNAME, m_Name);
	DDX_Text(pDX, IDC_EDIT_LOGINPWD, m_Pwd);
}

BEGIN_MESSAGE_MAP(CUSRPDBMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOGOUT, &CUSRPDBMFCDlg::OnBnClickedButtonLogout)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CUSRPDBMFCDlg::OnBnClickedButtonLogin)
//	ON_STN_CLICKED(IDC_STATIC_LOGINNAME, &CUSRPDBMFCDlg::OnStnClickedStaticLoginname)

ON_BN_CLICKED(IDC_BUTTON_Sign, &CUSRPDBMFCDlg::OnBnClickedButtonSign)
END_MESSAGE_MAP()


// CUSRPDBMFCDlg 消息处理程序

BOOL CUSRPDBMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	//数据库初始化
	//AfxOleInit();
	//数据库连接
	
	if (!AfxOleInit())
	{
		AfxMessageBox(_T("OLE初始化失败!"));
		return FALSE;
	}


	HRESULT hr;

	hr = m_pConnection.CreateInstance("ADODB.Connection");
	m_pConnection->ConnectionTimeout = 8;
	try
	{
		_bstr_t strConnect = "Provider=SQLOLEDB.1;Password=123456;User ID=sa;"
			"Initial Catalog=USRPDATABASE;Data Source=LAPTOP-02BP3EK5;"
			"Connect Timeout=8;";//初始化连接  
		hr = m_pConnection->Open(strConnect, "", "", adModeUnknown);//打开数据库
		if (FAILED(hr))
		{
			AfxMessageBox(_T("不能连接数据库!"));
			return FALSE;
		}
		/*else
		{
			MessageBox(_T("连接数据库成功!"), _T("提示！"), MB_OK | MB_ICONINFORMATION);
		}*/
	}
	catch (const _com_error& e)
	{
		CString errMsg;
		errMsg.Format(_T("数据库连接失败：%s\n详细信息：%s"), e.ErrorMessage(), (LPCTSTR)e.Description());
		AfxMessageBox(errMsg);
		return FALSE;
	}

			
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

BOOL CUSRPDBMFCDlg::ExcuteCmd(CString bstrSqlCmd)//执行SQL语句
{
	CUSRPDBMFCDlg ct;
	
	m_sqlCmd = _bstr_t(bstrSqlCmd);
	_variant_t RecordsAffected;

	try
	{
		m_pRecordset = m_pConnection->Execute(m_sqlCmd, &RecordsAffected, adCmdText);
	}
	catch (_com_error& e)
	{
		AfxMessageBox(e.ErrorMessage());
		return FALSE;
	}
	return TRUE;
}

void CUSRPDBMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CUSRPDBMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CUSRPDBMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//解决单行编辑框中按下回车界面关闭的问题
void CUSRPDBMFCDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}

//点击退出按钮关闭程序
void CUSRPDBMFCDlg::OnBnClickedButtonLogout()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}

//点击登录按钮验证用户名和密码，登录进入不同的操作模式
void CUSRPDBMFCDlg::OnBnClickedButtonLogin()
{
	// TODO: 在此添加控件通知处理程序代码
	//登录查询操作
	
	m_pRecordset.CreateInstance(__uuidof(Recordset));

	UpdateData(TRUE);

	CString SqlUser;
	SqlUser = TEXT("SELECT * FROM USER1");					//数据库语言，从USER表中进行选择

	//将查询数据导入m_pRecordset数据容器

	m_pRecordset = m_pConnection->Execute(_bstr_t(SqlUser), NULL, adCmdText);

	
	int index=0;
	
	if (m_pRecordset == nullptr)
	{
		AfxMessageBox(_T("记录集为空，查询未成功！"));
	}
	if (m_pRecordset->State != adStateOpen)
	{
		AfxMessageBox(_T("记录集未打开！"));
	}


	while (!m_pRecordset->adoEOF)//EOF判断是否到末尾

	{
		//查询条件遍历 把所有结果丢进储值数组Material
		MLoginID = (TCHAR*)(_bstr_t)m_pRecordset->GetFields()->GetItem("ID")->Value;
		MLoginPwd = (TCHAR*)(_bstr_t)m_pRecordset->GetFields()->GetItem("Password")->Value;
		
		if (m_Name.Compare(MLoginID) == 0)
		{
			if (m_Pwd.Compare(MLoginPwd) == 0)
			{
				MLoginClass = (TCHAR*)(_bstr_t)m_pRecordset->GetFields()->GetItem("Class")->Value;
				MLoginName = (TCHAR*)(_bstr_t)m_pRecordset->GetFields()->GetItem("Name")->Value;
				index = 1;
				break;
			}
			else
			{
				index = 2;
				break;
			}
		}
		
		//记录下移
		m_pRecordset->MoveNext();
	}

	switch (index)
	{
		case 1:
		{
			if (MLoginClass == '0')
			{
				CString str;
				str.Format(_T("管理员%s你好！"), MLoginName);
				MessageBox(str, _T("超声滚压数据库（管理员模式）"), MB_OK | MB_ICONINFORMATION);
				CDlgAdmin DlgAdmin;
				DlgAdmin.DoModal();
				m_Pwd = TEXT("");
				UpdateData(FALSE);
				break;
			}
			else
			{
				MessageBox(_T("操作员你好！"), _T("超声滚压数据库"), MB_OK | MB_ICONINFORMATION);
				CDlgOperator DlgOperator;
				DlgOperator.DoModal();
				m_Pwd = TEXT("");
				UpdateData(FALSE);
				break;
			}
		}
		case 2:
			MessageBox(_T("密码错误！"), _T("超声滚压数据库登录窗口"), MB_OK | MB_ICONEXCLAMATION);
			break;
		case 0:
			MessageBox(_T("警告！无此用户！"), _T("超声滚压数据库登录窗口"), MB_OK | MB_ICONEXCLAMATION);
	}
	m_pRecordset->Close();//如果有中断报错，删掉close函数 
	m_pRecordset = NULL;
}








void CUSRPDBMFCDlg::OnBnClickedButtonSign()
{
	// TODO: 在此添加控件通知处理程序代码
}
