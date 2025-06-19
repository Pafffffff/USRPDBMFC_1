#pragma once
#include "TabSheet.h"
#include "CDlgOperatorSELECT.h"
#include "CDlgOperatorPREDICT.h"

// CDlgOperator 对话框

class CDlgOperator : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgOperator)

public:
	CDlgOperator(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgOperator();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USRPDBMFC_Operator };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CTabSheet m_tab_Operator;
	CDlgOperatorSELECT DlgOperatorSELECT;
	CDlgOperatorPREDICT DlgOperatorPREDICT;

public:	
	afx_msg void OnTcnSelchangeTabOperator(NMHDR* pNMHDR, LRESULT* pResult);
};
