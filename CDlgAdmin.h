#pragma once
#include "TabSheet.h"
#include "CDlgAdminINSERT.h"
#include "CDlgAdminSELECT.h"
#include "CDlgAdminPREDICT.h"
// CDlgAdmin 对话框

class CDlgAdmin : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAdmin)

public:
	CDlgAdmin(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgAdmin();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USRPDBMFC_Admin };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
private:
	CTabSheet m_tab_Admin;
	CDlgAdminINSERT DlgAdminINSERT;
	CDlgAdminSELECT DlgAdminSELECT;
	CDlgAdminPREDICT DlgAdminPREDICT;


public:
	afx_msg void OnTcnSelchangeTabAdmin(NMHDR* pNMHDR, LRESULT* pResult);
};
