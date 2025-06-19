#pragma once
#include "pch.h"
#include "USRPDBMFC.h"
#include "USRPDBMFCDlg.h"
#include "CDlgAdmin.h"

// CDlgAdminINSERT 对话框

class CDlgAdminINSERT : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAdminINSERT)

public:
	CDlgAdminINSERT(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgAdminINSERT();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Admin_INSERT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnOK();
	DECLARE_MESSAGE_MAP()

public:
	CString m_AINMaterial;
	CString m_AINStaticForce;
	CString m_AINAmplitude;
	CString m_AINSpace;
	CString m_AINVelocity;
	CString m_AINPasses;
	CString m_AINOriRS;
	CString m_AINRS;
	CString m_AINOriRa;
	CString m_AINRa;
	CString m_AINOriHardness;
	CString m_AINHardness;
	


//数据库相关设置
public:
	int num = 0;											//使数据库只初始化一次
	BOOL AdminINSERTExcuteCmd(CString bstrSqlCmd);
protected:
	_bstr_t m_sqlCmd;
	_ConnectionPtr m_pConnection;//连接SQL SERVER数据库的链接对象  
	_RecordsetPtr m_pRecordset;//结果集对象
	_CommandPtr m_pCommand;    //命令集对象

public:
	afx_msg void OnBnClickedButtonAinsert();

};
