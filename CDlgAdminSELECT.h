#pragma once
#include "pch.h"
#include "USRPDBMFC.h"
#include "USRPDBMFCDlg.h"
#include "CDlgAdmin.h"

// CDlgAdminSELECT 对话框

class CDlgAdminSELECT : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAdminSELECT)

public:
	CDlgAdminSELECT(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgAdminSELECT();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Admin_SELECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnOK();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ASELMaterial;
	CString m_ASELStaticForce;
	CString m_ASELAmplitude;
	CString m_ASELSpace;
	CString m_ASELVelocity;
	CString m_ASELPasses;
	CString m_ASELOriRS;
	CString m_ASELRS;
	CString m_ASELOriRa;
	CString m_ASELRa;
	CString m_ASELOriHardness;
	CString m_ASELHardness;
	CString m_ASELEffRS;
	CString m_ASELEffRa;
	CString m_ASELEffHardness;
	CString m_ASELTime;
	afx_msg void OnBnClickedButtonAselect();

	//数据库相关设置
public:
	BOOL AdminSELECTExcuteCmd(CString bstrSqlCmd);
	int num = 0;								//让下拉框只添加一次材料名
protected:
	_bstr_t m_sqlCmd;
	_ConnectionPtr m_pConnection;//连接SQL SERVER数据库的链接对象  
	_RecordsetPtr m_pRecordset;//结果集对象
	_CommandPtr m_pCommand;    //命令集对象
	
public:
	afx_msg void OnCbnSelchangeAselmaterial();
	CString m_ASELName;
};
