#pragma once


// CDlgOperatorPREDICT 对话框
#include "pch.h"
#include "USRPDBMFC.h"
#include "USRPDBMFCDlg.h"
#include "CDlgOperator.h"
class CDlgOperatorPREDICT : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgOperatorPREDICT)

public:
	CDlgOperatorPREDICT(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgOperatorPREDICT();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Operator_PREDICT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	CComboBox m_OPREMaterial;
	CString m_OPREStaticForce;
	CString m_OPREAmplitude;
	CString m_OPRESpace;
	CString m_OPREVelocity;
	CString m_OPREPasses;
	CString m_OPREOriRS;
	CString m_OPRERS;
	CString m_OPREOriRa;
	CString m_OPRERa;
	CString m_OPREOriHardness;
	CString m_OPREHardness;
	CString m_OPREEffRS;
	CString m_OPREEffRa;
	CString m_OPREEffHardness;
	CSliderCtrl m_OPRESStaticForce;
	CSliderCtrl m_OPRESAmplitude;
	CSliderCtrl m_OPRESSpace;
	CSliderCtrl m_OPRESVelocity;
	CSliderCtrl m_OPRESPasses;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeOprestaticforce();
	afx_msg void OnEnChangeOpreamplitude();
	afx_msg void OnEnChangeOprespace();
	afx_msg void OnEnChangeOprevelocity();
	afx_msg void OnEnChangeOprepasses();
	//afx_msg void OnBnClickedButtonOpredict();
	int num = 0;									//使下拉框只添加一次材料名
	afx_msg void OnCbnSelchangeOprematerial();
};
