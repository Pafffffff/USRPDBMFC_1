// CDlgAdminSELECT.cpp: 实现文件
//

#include "pch.h"
#include "USRPDBMFC.h"
#include "USRPDBMFCDlg.h"
#include "CDlgAdminSELECT.h"
#include "afxdialogex.h"
#include "TabSheet.h"
#include "CDlgAdmin.h"
#include "framework.h"



// CDlgAdminSELECT 对话框

IMPLEMENT_DYNAMIC(CDlgAdminSELECT, CDialogEx)

CDlgAdminSELECT::CDlgAdminSELECT(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Admin_SELECT, pParent)
	, m_ASELStaticForce(_T("0"))
	, m_ASELAmplitude(_T("0"))
	, m_ASELSpace(_T("0"))
	, m_ASELVelocity(_T("0"))
	, m_ASELPasses(_T("0"))
	, m_ASELOriRS(_T("0"))
	, m_ASELRS(_T("0"))
	, m_ASELOriRa(_T("0"))
	, m_ASELRa(_T("0"))
	, m_ASELOriHardness(_T("0"))
	, m_ASELHardness(_T("0"))
	, m_ASELEffRS(_T("0%"))
	, m_ASELEffRa(_T("0%"))
	, m_ASELEffHardness(_T("0%"))
	, m_ASELTime(_T(""))
	, m_ASELName(_T(""))
{
	
}

CDlgAdminSELECT::~CDlgAdminSELECT()
{
}

void CDlgAdminSELECT::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ASELMaterial, m_ASELMaterial);
	DDX_Text(pDX, IDC_ASELSTATICFORCE, m_ASELStaticForce);
	DDX_Text(pDX, IDC_ASELAMPLITUDE, m_ASELAmplitude);
	DDX_Text(pDX, IDC_ASELSPACE, m_ASELSpace);
	DDX_Text(pDX, IDC_ASELVELOCITY, m_ASELVelocity);
	DDX_Text(pDX, IDC_ASELPASSES, m_ASELPasses);
	DDX_Text(pDX, IDC_ASELORIRS, m_ASELOriRS);
	DDX_Text(pDX, IDC_ASELRS, m_ASELRS);
	DDX_Text(pDX, IDC_ASELORIRA, m_ASELOriRa);
	DDX_Text(pDX, IDC_ASELRA, m_ASELRa);
	DDX_Text(pDX, IDC_ASELORIHARDNESS, m_ASELOriHardness);
	DDX_Text(pDX, IDC_ASELHARDNESS, m_ASELHardness);
	DDX_Text(pDX, IDC_ASELEffRS, m_ASELEffRS);
	DDX_Text(pDX, IDC_ASELEffRa, m_ASELEffRa);
	DDX_Text(pDX, IDC_ASELEffHardness, m_ASELEffHardness);
	DDX_Text(pDX, IDC_ASELTIME, m_ASELTime);


	//使下拉框只添加一次材料名 并且材料名来自数据库内容
	if (num == 0)
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

		//材料名查询操作
		_RecordsetPtr m_pRecordset;
		m_pRecordset.CreateInstance(__uuidof(Recordset));

		CString SqlSelect;
		SqlSelect = TEXT("SELECT * FROM USRP1");					//数据库语言，从USRP1表中进行选择

																	//将查询数据导入m_pRecordset数据容器

		m_pRecordset = m_pConnection->Execute(_bstr_t(SqlSelect), NULL, adCmdText);

		//因while循环中不知为何不能使用先前定义的控件所对应的变量，故新设M*为查询专用变量名
		CString MMaterial_former;
		CString MMaterial_latter;
		CStringArray Material;
		CStringArray Material_TRUE;

		/***********************************************************************************************************************/
		Material_TRUE.SetSize(3);					//确定只有三种材料 需"人为!!!!"控制数组大小
	    /***********************************************************************************************************************/
													//将连续重复出现的值筛除
		while (!m_pRecordset->adoEOF)//EOF判断是否到末尾

		{
			//查询条件遍历 把所有结果丢进储值数组Material
			MMaterial_latter = (TCHAR*)(_bstr_t)m_pRecordset->GetFields()->GetItem("Material")->Value;
			if (MMaterial_latter.Compare(MMaterial_former) != 0)
			{
				Material.Add(MMaterial_latter);
				MMaterial_former = MMaterial_latter;
			}
			//记录下移
			m_pRecordset->MoveNext();
		}

		//对储值数组中的元素进行查重存储			//查重算法如下
		int m = 0;

		Material_TRUE[m] = Material[m];
		for (int i = 0; i < Material.GetCount(); i++)
		{
			int k = 0;
			for (int j = 0; j < Material_TRUE.GetCount(); j++)
			{
				if (Material[i] != Material_TRUE[j])
				{
					k++;
				}
			}
			if (k == Material_TRUE.GetCount())
			{
				m++;
				Material_TRUE[m] = Material[i];
			}
		}

		//对下拉框添加数据
		for (int j = 0; j < Material_TRUE.GetCount(); j++)
		{
			m_ASELMaterial.AddString(Material_TRUE[j]);
		}

		//设置默认下拉框选中值    SetCurrentSelect 0代表上述添加数据的第一个值
		m_ASELMaterial.SetCurSel(0);

		m_pRecordset->Close();//如果有中断报错，删掉close函数 
		m_pRecordset = NULL;

		num++;

	}


	DDX_Text(pDX, IDC_ASELNAME, m_ASELName);
}



BOOL CDlgAdminSELECT::AdminSELECTExcuteCmd(CString bstrSqlCmd)//执行SQL语句
{
	CDlgAdminSELECT ct;
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

BEGIN_MESSAGE_MAP(CDlgAdminSELECT, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ASELECT, &CDlgAdminSELECT::OnBnClickedButtonAselect)
	ON_CBN_SELCHANGE(IDC_ASELMaterial, &CDlgAdminSELECT::OnCbnSelchangeAselmaterial)
END_MESSAGE_MAP()


// CDlgAdminSELECT 消息处理程序


void CDlgAdminSELECT::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}

void CDlgAdminSELECT::OnCbnSelchangeAselmaterial()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_ASELMaterial.GetCurSel();							//将当前材料名索引值赋值给int型index变量
	CString str;											//新建用以显示材料名的新字符串变量 C++类定义默认Private类型变量
	CString str1;											//用以显示整个提示语的字符串变量
	m_ASELMaterial.GetLBText(index, str);							//得到index代表的字符并存在str中
	str1.Format(_T("您重新选择了%s材料，请注意重新输入工艺参数及原始数据！"), str);
	//将代表材料名的字符串变量重整到整个输出字符串变量中
	MessageBox(str1, TEXT("提示！"), MB_OK | MB_ICONEXCLAMATION);			//输出更换材料时的提示语，及左上角警示语

	//更换材料后对已输入的工艺参数以及原始数据及上次得到的强化后结果及效果进行删除
	m_ASELStaticForce = TEXT("0");
	m_ASELAmplitude = TEXT("0");
	m_ASELSpace = TEXT("0");
	m_ASELVelocity = TEXT("0");
	m_ASELPasses = TEXT("0");
	m_ASELOriRS = TEXT("0");
	m_ASELRS = TEXT("0");
	m_ASELOriRa = TEXT("0");
	m_ASELRa = TEXT("0");
	m_ASELOriHardness = TEXT("0");
	m_ASELHardness = TEXT("0");
	m_ASELEffRS = TEXT("0%");
	m_ASELEffRa = TEXT("0%");
	m_ASELEffHardness = TEXT("0%");
	m_ASELTime = TEXT("");
	m_ASELName = TEXT("");
	UpdateData(FALSE);
}


void CDlgAdminSELECT::OnBnClickedButtonAselect()
{
	// TODO: 在此添加控件通知处理程序代码
	
	//查询操作
	_RecordsetPtr m_pRecordset;
	m_pRecordset.CreateInstance(__uuidof(Recordset));

	//保存编辑框中数据
	int index = m_ASELMaterial.GetCurSel();
	CString M_cbx;
	m_ASELMaterial.GetLBText(index, M_cbx);			//获取下拉框控件中的内容，内容同步到控件对应的变量
	UpdateData(TRUE);						//获取编辑框中的内容，并将内容同步到查询所新建的变量中

	CString SqlSelect;
	SqlSelect = TEXT("SELECT * FROM USRP1");					//数据库语言，从USRP1表中进行选择

	//将查询数据导入m_pRecordset数据容器

	m_pRecordset = m_pConnection->Execute(_bstr_t(SqlSelect), NULL, adCmdText);
	int Num = 0;				//查询结果指标

	//将记录集获取的数据一一与输入的数据进行比较
	//因while循环中不知为何不能使用先前定义的控件所对应的变量，故新设M*为查询专用变量名
	CString MMaterial, MStaticForce, MAmplitude, MSpace, MVelocity, MPasses, MOriRS, MOriRa, MOriHardness, MRS, MRa, MHardness,MTime,MName;


	while (!m_pRecordset->adoEOF)//EOF判断是否到末尾

	{
		//查询条件遍历
		MMaterial = (TCHAR*)(_bstr_t)m_pRecordset->GetFields()->GetItem("Material")->Value;
		MStaticForce = (TCHAR*)(_bstr_t)m_pRecordset->GetFields()->GetItem("Static Force(N)")->Value;
		MAmplitude = (TCHAR*)(_bstr_t)m_pRecordset->GetFields()->GetItem("Amplitude(μm)")->Value;
		MSpace = (TCHAR*)(_bstr_t)m_pRecordset->GetFields()->GetItem("Space(mm)")->Value;
		MVelocity = (TCHAR*)(_bstr_t)m_pRecordset->GetFields()->GetItem("Velocity(mm/s)")->Value;
		MPasses = (TCHAR*)(_bstr_t)m_pRecordset->GetFields()->GetItem("Passes")->Value;

		//如果相等即查找到
		if (M_cbx.Compare(MMaterial) == 0 && m_ASELStaticForce.Compare(MStaticForce) == 0 && m_ASELAmplitude.Compare(MAmplitude) == 0 && m_ASELSpace.Compare(MSpace) == 0 && m_ASELVelocity.Compare(MVelocity) == 0 && m_ASELPasses.Compare(MPasses) == 0)
		{
			Num++;

			//以下是获取数据库中目标行的目标列内容
			MOriRS = (TCHAR*)(_bstr_t)m_pRecordset->GetFields()->GetItem("Original Residual Stress(MPa)")->Value;
			MOriRa = (TCHAR*)(_bstr_t)m_pRecordset->GetFields()->GetItem("Original Roughness Of Surface(μm)")->Value;
			MOriHardness = (TCHAR*)(_bstr_t)m_pRecordset->GetFields()->GetItem("Original Hardness(HV)")->Value;
			MRS = (TCHAR*)(_bstr_t)m_pRecordset->GetFields()->GetItem("Residual Stress(MPa)")->Value;
			MRa = (TCHAR*)(_bstr_t)m_pRecordset->GetFields()->GetItem("Roughness Of Surface(μm)")->Value;
			MHardness = (TCHAR*)(_bstr_t)m_pRecordset->GetFields()->GetItem("Hardness(HV)")->Value;
			MTime= (TCHAR*)(_bstr_t)m_pRecordset->GetFields()->GetItem("Time")->Value;
			MName = (TCHAR*)(_bstr_t)m_pRecordset->GetFields()->GetItem("Name")->Value;
			break;
		}

		//记录下移
		m_pRecordset->MoveNext();


	}

	if (Num == 1)
	{
		//将查询结果赋值给控件对应变量
		m_ASELOriRS = MOriRS;
		m_ASELOriRa = MOriRa;
		m_ASELOriHardness = MOriHardness;
		m_ASELRS = MRS;
		m_ASELRa = MRa;
		m_ASELHardness = MHardness;
		m_ASELTime = MTime;
		m_ASELName = MName;


		//强化效果计算过程
		//先把三个原始值三个强化值从CString转换成float  命名规则为M_*
		float M_OriRS = _wtof(m_ASELOriRS);
		float M_OriRa = _wtof(m_ASELOriRa);
		float M_OriHardness = _wtof(m_ASELOriHardness);
		float M_RS = _wtof(m_ASELRS);
		float M_Ra = _wtof(m_ASELRa);
		float M_Hardness = _wtof(m_ASELHardness);

		//对强化效果进行计算
		float M_EffRS, M_EffRa, M_EffHardness;					//定义三个强化效果计算专用float型变量

		M_EffRS = ((M_RS - M_OriRS) * 100) / M_OriRS;
		M_EffRa = ((M_OriRa - M_Ra) * 100) / M_OriRa;
		M_EffHardness = ((M_Hardness - M_OriHardness) * 100) / M_OriHardness;


		//将强化效果计算结果从float型变量 转化到和控件对应变量一致的CString 并加上百分号 直接输出.2f就可以输出两位小数了
		m_ASELEffRS.Format(_T("%.2f%%"), M_EffRS);
		m_ASELEffRa.Format(_T("%.2f%%"), M_EffRa);
		m_ASELEffHardness.Format(_T("%.2f%%"), M_EffHardness);



		MessageBox(_T("查询成功！"), _T("提示！"), MB_OK | MB_ICONINFORMATION);
		UpdateData(FALSE);          //将变量内容同步到控件上，进行查询结果显示
	}
	else
	{
		m_ASELRS.Format(_T("0"));
		m_ASELRa.Format(_T("0"));
		m_ASELHardness.Format(_T("0"));
		m_ASELEffRS.Format(_T("0%%"));
		m_ASELEffRa.Format(_T("0%%"));
		m_ASELEffHardness.Format(_T("0%%"));
		UpdateData(FALSE);
		MessageBox(_T("查询失败，无相应记录！"), _T("警告！"), MB_OK | MB_ICONEXCLAMATION);
	}

	m_pRecordset->Close();//如果有中断报错，删掉close函数 
	m_pRecordset = NULL;

}



