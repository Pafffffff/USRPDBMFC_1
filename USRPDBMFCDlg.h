
// USRPDBMFCDlg.h: 头文件
//

#pragma once
#include "pch.h"
#include "framework.h"
#include "USRPDBMFC.h"
#include "USRPDBMFCDlg.h"
#include "afxdialogex.h"
#include "TabSheet.h"
#include "CDlgAdmin.h"
#include "CDlgOperator.h"


// CUSRPDBMFCDlg 对话框
class CUSRPDBMFCDlg : public CDialogEx
{
// 构造
public:
	CUSRPDBMFCDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USRPDBMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	afx_msg void OnBnClickedButtonLogout();
	afx_msg void OnBnClickedButtonLogin();


//数据库相关设置
public:
	BOOL ExcuteCmd(CString bstrSqlCmd);
protected:
	_bstr_t m_sqlCmd;
	_CommandPtr m_pCommand;    //命令集对象
	_ConnectionPtr m_pConnection;//连接SQL SERVER数据库的链接对象  
	_RecordsetPtr m_pRecordset;//结果集对象

public:
	CString m_Name;
	CString m_Pwd;
	
//	afx_msg void OnStnClickedStaticLoginname();
	
	afx_msg void OnBnClickedButtonSign();
};
