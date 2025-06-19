// CDlgAdminINSERT.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "USRPDBMFC.h"
#include "USRPDBMFCDlg.h"
#include "afxdialogex.h"
#include "TabSheet.h"
#include "CDlgAdmin.h"
#include "CDlgAdminINSERT.h"


// CDlgAdminINSERT 对话框

IMPLEMENT_DYNAMIC(CDlgAdminINSERT, CDialogEx)

CDlgAdminINSERT::CDlgAdminINSERT(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Admin_INSERT, pParent)

	, m_AINMaterial(_T("GH4169"))
	, m_AINStaticForce(_T("0"))
	, m_AINAmplitude(_T("2"))
	, m_AINSpace(_T("2"))
	, m_AINVelocity(_T("2"))
	, m_AINPasses(_T("2"))
	, m_AINOriRS(_T("2"))
	, m_AINRS(_T("2"))
	, m_AINOriRa(_T("2"))
	, m_AINRa(_T("2"))
	, m_AINOriHardness(_T("2"))
	, m_AINHardness(_T("2"))
{

}

CDlgAdminINSERT::~CDlgAdminINSERT()
{
}



void CDlgAdminINSERT::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_AINMATERIAL, m_AINMaterial);
	DDX_Text(pDX, IDC_AINSTATICFORCE, m_AINStaticForce);
	DDX_Text(pDX, IDC_AINAMPLITUDE, m_AINAmplitude);
	DDX_Text(pDX, IDC_AINSPACE, m_AINSpace);
	DDX_Text(pDX, IDC_AINVELOCITY, m_AINVelocity);
	DDX_Text(pDX, IDC_AINPASSES, m_AINPasses);
	DDX_Text(pDX, IDC_AINORIRS, m_AINOriRS);
	DDX_Text(pDX, IDC_AINRS, m_AINRS);
	DDX_Text(pDX, IDC_AINORIRA, m_AINOriRa);
	DDX_Text(pDX, IDC_AINRA, m_AINRa);
	DDX_Text(pDX, IDC_AINORIHARDNESS, m_AINOriHardness);
	DDX_Text(pDX, IDC_AINHARDNESS, m_AINHardness);

	if (num = 0)
	{
		//数据库连接
		HRESULT hr;

		hr = m_pConnection.CreateInstance("ADODB.Connection");
		m_pConnection->ConnectionTimeout = 8;
		try
		{
			_bstr_t strConnect = "Provider = SQLOLEDB.1; Persist Security Info = False; User ID = sa; Password=123456; Initial Catalog = USRPDATABASE; Data Source =LAPTOP-02BP3EK5";//初始化连接  
			hr = m_pConnection->Open(strConnect, "", "", adModeUnknown);//打开数据库
			if (FAILED(hr))
			{
				AfxMessageBox(_T("不能连接数据库!"));
				return;
			}
			else
			{
				MessageBox(_T("连接数据库成功!"), _T("提示！"), MB_OK | MB_ICONINFORMATION);
			}
		}
		catch (_com_error& e)
		{
			AfxMessageBox(e.Description());
			return;
		}
	}
};


BOOL CDlgAdminINSERT::AdminINSERTExcuteCmd(CString bstrSqlCmd)//执行SQL语句
{
	CDlgAdminINSERT ct;
	m_sqlCmd = _bstr_t(bstrSqlCmd);
	_variant_t RecordsAffected;

	try
	{
		m_pRecordset = m_pConnection->Execute(m_sqlCmd, &RecordsAffected, adCmdText);
	}
	catch (_com_error& e)
	{
		AfxMessageBox(e.ErrorMessage());
		return FALSE;
	}
	return TRUE;
}

BEGIN_MESSAGE_MAP(CDlgAdminINSERT, CDialogEx)
//ON_BN_CLICKED(IDC_BUTTON_AINSERT, &CDlgAdminINSERT::OnBnClickedButtonAinsert)
ON_BN_CLICKED(IDC_BUTTON_AINSERT, &CDlgAdminINSERT::OnBnClickedButtonAinsert)
END_MESSAGE_MAP()


 //CDlgAdminINSERT 消息处理程序


void CDlgAdminINSERT::OnBnClickedButtonAinsert()
{
	// TODO: 在此添加控件通知处理程序代码
		
	HRESULT hr;

	hr = m_pConnection.CreateInstance("ADODB.Connection");
	m_pConnection->ConnectionTimeout = 8;
	try
	{
		_bstr_t strConnect = "Provider = SQLOLEDB.1; Persist Security Info = False; User ID = sa; Password=123456; Initial Catalog = USRPDATABASE; Data Source =LAPTOP-02BP3EK5";//初始化连接  
		hr = m_pConnection->Open(strConnect, "", "", adModeUnknown);//打开数据库
		if (FAILED(hr))
		{
			AfxMessageBox(_T("不能连接数据库!"));
			return;
		}
		/*else
		{
			MessageBox(_T("连接数据库成功!"), _T("提示！"), MB_OK | MB_ICONINFORMATION);
		}*/
	}
	catch (_com_error& e)
	{
		AfxMessageBox(e.Description());
		return;
	}



	//执行SQL语句之前 先遍历一遍表内数据 若有重复 则弹窗提示 下为遍历查询语句
	_RecordsetPtr m_pRecordset;

	m_pRecordset.CreateInstance(__uuidof(Recordset));


	UpdateData(TRUE);						//获取编辑框中的内容，并将内容同步到查询所新建的变量中

	//对界面输入参数进行非零限定
	if (m_AINStaticForce == '0' || m_AINAmplitude == '0' || m_AINSpace == '0' || m_AINVelocity == '0' || m_AINPasses == '0' || m_AINOriRS == '0' || m_AINOriRa == '0' || m_AINOriHardness == '0' || m_AINRS == '0' || m_AINRa == '0' || m_AINHardness == '0')
	{
		MessageBox(_T("请完整输入工艺参数及相关检测量！"), _T("提示！"), MB_OK | MB_ICONINFORMATION);
		return;
	}

	//在点击按钮时 插入数据之前首先进行数据检索遍历，若有重复数据，则插入失败且弹窗
	CString SqlSelect;											//建立查询专用SQL语句 SqlSelect
	SqlSelect = TEXT("SELECT * FROM USRP1");					//数据库语言，从USRP1表中进行选择

	//将查询数据导入m_pRecordset数据容器

	m_pRecordset = m_pConnection->Execute(_bstr_t(SqlSelect), NULL, adCmdText);
	int Num = 0;

	//将记录集获取的数据一一与输入的数据进行比较
	//因while循环中不知为何不能使用先前定义的控件所对应的变量，故新设M*为查询专用变量名
	CString MMaterial, MStaticForce, MAmplitude, MSpace, MVelocity, MPasses, MOriRS, MOriRa, MOriHardness, MRS, MRa, MHardness;

	//循环遍历while体
	while (!m_pRecordset->adoEOF)//EOF判断是否到末尾

	{
		//获取第一行内容 接下来进行对比
		MMaterial = (TCHAR*)(_bstr_t)m_pRecordset->GetFields()->GetItem("Material")->Value;
		MAmplitude = (TCHAR*)(_bstr_t)m_pRecordset->GetFields()->GetItem("Amplitude(μm)")->Value;
		MSpace = (TCHAR*)(_bstr_t)m_pRecordset->GetFields()->GetItem("Space(mm)")->Value;
		MVelocity = (TCHAR*)(_bstr_t)m_pRecordset->GetFields()->GetItem("Velocity(mm/s)")->Value;
		MPasses = (TCHAR*)(_bstr_t)m_pRecordset->GetFields()->GetItem("Passes")->Value;

		//如果相等即查找到
		if (m_AINMaterial.Compare(MMaterial) == 0 && m_AINStaticForce.Compare(MStaticForce) == 0 && m_AINAmplitude.Compare(MAmplitude) == 0 && m_AINSpace.Compare(MSpace) == 0 && m_AINVelocity.Compare(MVelocity) == 0 && m_AINPasses.Compare(MPasses) == 0)
		{
			Num++;
			//查找到即说明已有相同数据输入，应及时弹窗并避免插入语句生成
			MessageBox(_T("数据库中已存在相同数据，请勿重复添加！"), _T("警告！"), MB_OK | MB_ICONEXCLAMATION);
			break;
		}

		//记录下移
		m_pRecordset->MoveNext();

	}

	//获取系统当前时间
	CString m_Time;
	CTime tm;
	tm = CTime::GetCurrentTime();
	m_Time = tm.Format("%Y年%m月%d日 %X");

	
	if (Num == 0)
	{
		CString SqlInsert;
		//该插入语句在SQL SERVER 中自动按列从前往后排序
		SqlInsert.Format(_T("INSERT INTO [USRPDATABASE].[dbo].[USRP1]([Material],[Residual Stress relieving],[Static Force(N)],[Amplitude(μm)],[Space(mm)],[Velocity(mm/s)],[Passes],[Original Residual Stress(MPa)],[Original Roughness Of Surface(μm)],[Original Hardness(HV)],[Residual Stress(MPa)],[Roughness Of Surface(μm)],[Hardness(HV)],Time,Name) VALUES('%s','0','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')"), m_AINMaterial, m_AINStaticForce, m_AINAmplitude, m_AINSpace, m_AINVelocity, m_AINPasses, m_AINOriRS, m_AINOriRa, m_AINOriHardness, m_AINRS, m_AINRa, m_AINHardness, m_Time, MLoginName);

		
		if (!AdminINSERTExcuteCmd(SqlInsert))
			AfxMessageBox(_T("添加失败！"));
		else
		{
			CString str;
			str = tm.Format("数据于%Y年%m月%d日 %X添加成功");
			MessageBox(str, _T("超声滚压数据库（管理员）"), MB_OK | MB_ICONINFORMATION);
		}
		
	}

	m_pRecordset->Close();//如果有中断报错，删掉close函数 
	m_pRecordset = NULL;
	return;
}


void CDlgAdminINSERT::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}
