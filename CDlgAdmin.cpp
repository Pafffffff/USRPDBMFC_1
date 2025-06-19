// CDlgAdmin.cpp: 实现文件
//

#include "pch.h"
#include "USRPDBMFC.h"
#include "CDlgAdmin.h"
#include "afxdialogex.h"
#include "USRPDBMFCDlg.h"
//#include "predTa19.h"
//#include "predTi17.h"
//#include "predGH4169.h"
#include "framework.h"



// CDlgAdmin 对话框

IMPLEMENT_DYNAMIC(CDlgAdmin, CDialogEx)

CDlgAdmin::CDlgAdmin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_USRPDBMFC_Admin, pParent)
{
}

CDlgAdmin::~CDlgAdmin()
{
}

void CDlgAdmin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_Admin, m_tab_Admin);
	m_tab_Admin.AddPage(_T("数据添加"), &DlgAdminINSERT, IDD_Admin_INSERT);
	m_tab_Admin.AddPage(_T("数据查询"), &DlgAdminSELECT, IDD_Admin_SELECT);
	m_tab_Admin.AddPage(_T("结果预测"), &DlgAdminPREDICT, IDD_Admin_PREDICT);
	//展示ADMIN TAB控件内容
	m_tab_Admin.Show();

}


BEGIN_MESSAGE_MAP(CDlgAdmin, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_Admin, &CDlgAdmin::OnTcnSelchangeTabAdmin)
END_MESSAGE_MAP()


// CDlgAdmin 消息处理程序


void CDlgAdmin::OnTcnSelchangeTabAdmin(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	//获取当前标签页索引值
	int index = m_tab_Admin.GetCurSel();
	TCITEM Admintab;
	TCHAR buf[200] = { 0 };
	Admintab.pszText = buf;
	Admintab.cchTextMax = 200;
	Admintab.mask = TCIF_TEXT;
	m_tab_Admin.GetItem(index, &Admintab);
	CString str;
	str.Format(_T("已切换至%s功能！"),Admintab.pszText);
	MessageBox(str, _T("超声滚压数据库（管理员模式）"), MB_OK | MB_ICONINFORMATION);



}
