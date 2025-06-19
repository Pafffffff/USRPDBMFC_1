#pragma once
#include "pch.h"
#include "USRPDBMFC.h"
#include "USRPDBMFCDlg.h"
#include "CDlgOperator.h"

// CDlgOperatorSELECT 对话框

class CDlgOperatorSELECT : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgOperatorSELECT)

public:
	CDlgOperatorSELECT(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgOperatorSELECT();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Operator_SELECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnOK();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_OSELMaterial;
	CString m_OSELStaticForce;
	CString m_OSELAmplitude;
	CString m_OSELSpace;
	CString m_OSELVelocity;
	CString m_OSELPasses;
	CString m_OSELOriRS;
	CString m_OSELRS;
	CString m_OSELOriRa;
	CString m_OSELRa;
	CString m_OSELOriHardness;
	CString m_OSELHardness;
	CString m_OSELEffRS;
	CString m_OSELEffRa;
	CString m_OSELEffHardness;
	CString m_OSELTime;
	afx_msg void OnBnClickedButtonOselect();

	//数据库相关设置
public:
	BOOL OperatorSELECTExcuteCmd(CString bstrSqlCmd);
	int num = 0;								//让下拉框只添加一次材料名
protected:
	_bstr_t m_sqlCmd;
	_ConnectionPtr m_pConnection;//连接SQL SERVER数据库的链接对象  
	_RecordsetPtr m_pRecordset;//结果集对象
	_CommandPtr m_pCommand;    //命令集对象
public:
	afx_msg void OnCbnSelchangeOselmaterial();
	CString m_OSELName;
};
