// CDlgOperator.cpp: 实现文件
//

#include "pch.h"
#include "USRPDBMFC.h"
#include "CDlgOperator.h"
#include "afxdialogex.h"


// CDlgOperator 对话框

IMPLEMENT_DYNAMIC(CDlgOperator, CDialogEx)

CDlgOperator::CDlgOperator(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_USRPDBMFC_Operator, pParent)
{

}

CDlgOperator::~CDlgOperator()
{
}

void CDlgOperator::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_TAB_Operator, m_Tab_Operator);
	DDX_Control(pDX, IDC_TAB_Operator, m_tab_Operator);
	m_tab_Operator.AddPage(_T("数据查询"), &DlgOperatorSELECT, IDD_Operator_SELECT);
	m_tab_Operator.AddPage(_T("结果预测"), &DlgOperatorPREDICT, IDD_Operator_PREDICT);
	//展示Operator TAB控件内容
	m_tab_Operator.Show();
}


BEGIN_MESSAGE_MAP(CDlgOperator, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_Operator, &CDlgOperator::OnTcnSelchangeTabOperator)
END_MESSAGE_MAP()


// CDlgOperator 消息处理程序


void CDlgOperator::OnTcnSelchangeTabOperator(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	//获取当前标签页索引值
	int index = m_tab_Operator.GetCurSel();
	TCITEM Operatortab;
	TCHAR buf[200] = { 0 };
	Operatortab.pszText = buf;
	Operatortab.cchTextMax = 200;
	Operatortab.mask = TCIF_TEXT;
	m_tab_Operator.GetItem(index, &Operatortab);
	CString str;
	str.Format(_T("已切换至%s功能！"), Operatortab.pszText);
	MessageBox(str, _T("超声滚压数据库"), MB_OK | MB_ICONINFORMATION);

}
