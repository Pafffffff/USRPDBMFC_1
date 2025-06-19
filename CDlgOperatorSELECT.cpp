// CDlgOperatorSELECT.cpp: 实现文件
//

#include "pch.h"
#include "USRPDBMFC.h"
#include "USRPDBMFCDlg.h"
#include "CDlgOperatorSELECT.h"
#include "afxdialogex.h"
#include "TabSheet.h"
#include "CDlgOperator.h"
#include "framework.h"

// CDlgOperatorSELECT 对话框

IMPLEMENT_DYNAMIC(CDlgOperatorSELECT, CDialogEx)

CDlgOperatorSELECT::CDlgOperatorSELECT(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Operator_SELECT, pParent)
	, m_OSELStaticForce(_T("0"))
	, m_OSELAmplitude(_T("0"))
	, m_OSELSpace(_T("0"))
	, m_OSELVelocity(_T("0"))
	, m_OSELPasses(_T("0"))
	, m_OSELOriRS(_T("0"))
	, m_OSELRS(_T("0"))
	, m_OSELOriRa(_T("0"))
	, m_OSELRa(_T("0"))
	, m_OSELOriHardness(_T("0"))
	, m_OSELHardness(_T("0"))
	, m_OSELEffRS(_T("0%"))
	, m_OSELEffRa(_T("0%"))
	, m_OSELEffHardness(_T("0%"))
	, m_OSELTime(_T(""))
	, m_OSELName(_T(""))
{

}

CDlgOperatorSELECT::~CDlgOperatorSELECT()
{
}

void CDlgOperatorSELECT::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OSELMaterial, m_OSELMaterial);
	DDX_Text(pDX, IDC_OSELSTATICFORCE, m_OSELStaticForce);
	DDX_Text(pDX, IDC_OSELAMPLITUDE, m_OSELAmplitude);
	DDX_Text(pDX, IDC_OSELSPACE, m_OSELSpace);
	DDX_Text(pDX, IDC_OSELVELOCITY, m_OSELVelocity);
	DDX_Text(pDX, IDC_OSELPASSES, m_OSELPasses);
	DDX_Text(pDX, IDC_OSELORIRS, m_OSELOriRS);
	DDX_Text(pDX, IDC_OSELRS, m_OSELRS);
	DDX_Text(pDX, IDC_OSELORIRA, m_OSELOriRa);
	DDX_Text(pDX, IDC_OSELRA, m_OSELRa);
	DDX_Text(pDX, IDC_OSELORIHARDNESS, m_OSELOriHardness);
	DDX_Text(pDX, IDC_OSELHARDNESS, m_OSELHardness);
	DDX_Text(pDX, IDC_OSELEffRS, m_OSELEffRS);
	DDX_Text(pDX, IDC_OSELEffRa, m_OSELEffRa);
	DDX_Text(pDX, IDC_OSELEffHardness, m_OSELEffHardness);
	DDX_Text(pDX, IDC_OSELTIME, m_OSELTime);


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
			m_OSELMaterial.AddString(Material_TRUE[j]);
		}

		//设置默认下拉框选中值    SetCurrentSelect 0代表上述添加数据的第一个值
		m_OSELMaterial.SetCurSel(0);

		m_pRecordset->Close();//如果有中断报错，删掉close函数 
		m_pRecordset = NULL;

		num++;

	}
	DDX_Text(pDX, IDC_OSELNAME, m_OSELName);
}


BOOL CDlgOperatorSELECT::OperatorSELECTExcuteCmd(CString bstrSqlCmd)//执行SQL语句
{
	CDlgOperatorSELECT ct;
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

BEGIN_MESSAGE_MAP(CDlgOperatorSELECT, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OSELECT, &CDlgOperatorSELECT::OnBnClickedButtonOselect)
	ON_CBN_SELCHANGE(IDC_OSELMaterial, &CDlgOperatorSELECT::OnCbnSelchangeOselmaterial)
END_MESSAGE_MAP()


// CDlgOperatorSELECT 消息处理程序


void CDlgOperatorSELECT::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CDlgOperatorSELECT::OnCbnSelchangeOselmaterial()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_OSELMaterial.GetCurSel();							//将当前材料名索引值赋值给int型index变量
	CString str;											//新建用以显示材料名的新字符串变量 C++类定义默认Private类型变量
	CString str1;											//用以显示整个提示语的字符串变量
	m_OSELMaterial.GetLBText(index, str);							//得到index代表的字符并存在str中
	str1.Format(_T("您重新选择了%s材料，请注意重新输入工艺参数及原始数据！"), str);
	//将代表材料名的字符串变量重整到整个输出字符串变量中
	MessageBox(str1, TEXT("提示！"), MB_OK | MB_ICONEXCLAMATION);			//输出更换材料时的提示语，及左上角警示语

	//更换材料后对已输入的工艺参数以及原始数据及上次得到的强化后结果及效果进行删除
	m_OSELStaticForce = TEXT("0");
	m_OSELAmplitude = TEXT("0");
	m_OSELSpace = TEXT("0");
	m_OSELVelocity = TEXT("0");
	m_OSELPasses = TEXT("0");
	m_OSELOriRS = TEXT("0");
	m_OSELRS = TEXT("0");
	m_OSELOriRa = TEXT("0");
	m_OSELRa = TEXT("0");
	m_OSELOriHardness = TEXT("0");
	m_OSELHardness = TEXT("0");
	m_OSELEffRS = TEXT("0%");
	m_OSELEffRa = TEXT("0%");
	m_OSELEffHardness = TEXT("0%");
	m_OSELTime = TEXT("");
	m_OSELName = TEXT("");
	UpdateData(FALSE);
}


void CDlgOperatorSELECT::OnBnClickedButtonOselect()
{
	// TODO: 在此添加控件通知处理程序代码

	//查询操作
	_RecordsetPtr m_pRecordset;
	m_pRecordset.CreateInstance(__uuidof(Recordset));

	//保存编辑框中数据
	int index = m_OSELMaterial.GetCurSel();
	CString M_cbx;
	m_OSELMaterial.GetLBText(index, M_cbx);			//获取下拉框控件中的内容，内容同步到控件对应的变量
	UpdateData(TRUE);						//获取编辑框中的内容，并将内容同步到查询所新建的变量中

	CString SqlSelect;
	SqlSelect = TEXT("SELECT * FROM USRP1");					//数据库语言，从USRP1表中进行选择

	//将查询数据导入m_pRecordset数据容器

	m_pRecordset = m_pConnection->Execute(_bstr_t(SqlSelect), NULL, adCmdText);
	int Num = 0;								//查询结果指标

	//将记录集获取的数据一一与输入的数据进行比较
	//因while循环中不知为何不能使用先前定义的控件所对应的变量，故新设M*为查询专用变量名
	CString MMaterial, MStaticForce, MAmplitude, MSpace, MVelocity, MPasses, MOriRS, MOriRa, MOriHardness, MRS, MRa, MHardness, MTime,MName;


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
		if (M_cbx.Compare(MMaterial) == 0 && m_OSELStaticForce.Compare(MStaticForce) == 0 && m_OSELAmplitude.Compare(MAmplitude) == 0 && m_OSELSpace.Compare(MSpace) == 0 && m_OSELVelocity.Compare(MVelocity) == 0 && m_OSELPasses.Compare(MPasses) == 0)
		{
			Num++;

			//以下是获取数据库中目标行的目标列内容
			MOriRS = (TCHAR*)(_bstr_t)m_pRecordset->GetFields()->GetItem("Original Residual Stress(MPa)")->Value;
			MOriRa = (TCHAR*)(_bstr_t)m_pRecordset->GetFields()->GetItem("Original Roughness Of Surface(μm)")->Value;
			MOriHardness = (TCHAR*)(_bstr_t)m_pRecordset->GetFields()->GetItem("Original Hardness(HV)")->Value;
			MRS = (TCHAR*)(_bstr_t)m_pRecordset->GetFields()->GetItem("Residual Stress(MPa)")->Value;
			MRa = (TCHAR*)(_bstr_t)m_pRecordset->GetFields()->GetItem("Roughness Of Surface(μm)")->Value;
			MHardness = (TCHAR*)(_bstr_t)m_pRecordset->GetFields()->GetItem("Hardness(HV)")->Value;
			MTime = (TCHAR*)(_bstr_t)m_pRecordset->GetFields()->GetItem("Time")->Value;
			MName = (TCHAR*)(_bstr_t)m_pRecordset->GetFields()->GetItem("Name")->Value;
			break;
		}

		//记录下移
		m_pRecordset->MoveNext();


	}

	if (Num == 1)
	{
		//将查询结果赋值给控件对应变量
		m_OSELOriRS = MOriRS;
		m_OSELOriRa = MOriRa;
		m_OSELOriHardness = MOriHardness;
		m_OSELRS = MRS;
		m_OSELRa = MRa;
		m_OSELHardness = MHardness;
		m_OSELTime = MTime;
		m_OSELName = MName;

		//强化效果计算过程
		//先把三个原始值三个强化值从CString转换成float  命名规则为M_*
		float M_OriRS = _wtof(m_OSELOriRS);
		float M_OriRa = _wtof(m_OSELOriRa);
		float M_OriHardness = _wtof(m_OSELOriHardness);
		float M_RS = _wtof(m_OSELRS);
		float M_Ra = _wtof(m_OSELRa);
		float M_Hardness = _wtof(m_OSELHardness);

		//对强化效果进行计算
		float M_EffRS, M_EffRa, M_EffHardness;					//定义三个强化效果计算专用float型变量

		M_EffRS = ((M_RS - M_OriRS) * 100) / M_OriRS;
		M_EffRa = ((M_OriRa - M_Ra) * 100) / M_OriRa;
		M_EffHardness = ((M_Hardness - M_OriHardness) * 100) / M_OriHardness;


		//将强化效果计算结果从float型变量 转化到和控件对应变量一致的CString 并加上百分号 直接输出.2f就可以输出两位小数了
		m_OSELEffRS.Format(_T("%.2f%%"), M_EffRS);
		m_OSELEffRa.Format(_T("%.2f%%"), M_EffRa);
		m_OSELEffHardness.Format(_T("%.2f%%"), M_EffHardness);



		MessageBox(_T("查询成功！"), _T("提示！"), MB_OK | MB_ICONINFORMATION);
		UpdateData(FALSE);          //将变量内容同步到控件上，进行查询结果显示
	}
	else
	{	
		m_OSELRS.Format(_T("0"));
		m_OSELRa.Format(_T("0"));
		m_OSELHardness.Format(_T("0"));
		m_OSELEffRS.Format(_T("0%%"));
		m_OSELEffRa.Format(_T("0%%"));
		m_OSELEffHardness.Format(_T("0%%"));
		m_OSELName.Format(_T(""));
		m_OSELTime.Format(_T(""));
		UpdateData(FALSE);
		MessageBox(_T("查询失败，无相应记录！"), _T("警告！"), MB_OK | MB_ICONEXCLAMATION);
	}

	m_pRecordset->Close();//如果有中断报错，删掉close函数 
	m_pRecordset = NULL;
}



