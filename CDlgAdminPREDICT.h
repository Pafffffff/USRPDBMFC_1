#pragma once


// CDlgAdminPREDICT 对话框
#include "pch.h"
#include "USRPDBMFC.h"
#include "USRPDBMFCDlg.h"
#include "CDlgAdmin.h"
class CDlgAdminPREDICT : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAdminPREDICT)

public:
	CDlgAdminPREDICT(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgAdminPREDICT();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Admin_PREDICT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	CComboBox m_APREMaterial;
	CString m_APREStaticForce;
	CString m_APREAmplitude;
	CString m_APRESpace;
	CString m_APREVelocity;
	CString m_APREPasses;
	CString m_APREOriRS;
	CString m_APRERS;
	CString m_APREOriRa;
	CString m_APRERa;
	CString m_APREOriHardness;
	CString m_APREHardness;
	CString m_APREEffRS;
	CString m_APREEffRa;
	CString m_APREEffHardness;
	CSliderCtrl m_APRESStaticForce;
	CSliderCtrl m_APRESAmplitude;
	CSliderCtrl m_APRESSpace;
	CSliderCtrl m_APRESVelocity;
	CSliderCtrl m_APRESPasses;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeAprestaticforce();
	afx_msg void OnEnChangeApreamplitude();
	afx_msg void OnEnChangeAprespace();
	afx_msg void OnEnChangeAprevelocity();
	afx_msg void OnEnChangeAprepasses();
	afx_msg void OnBnClickedButtonApredict();
	int num = 0;									//使下拉框只添加一次材料名
	afx_msg void OnCbnSelchangeAprematerial();
};
