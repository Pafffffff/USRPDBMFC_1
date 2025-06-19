// CDlgOperatorPREDICT.cpp: 实现文件
//

#include "pch.h"
#include "USRPDBMFC.h"
#include "USRPDBMFCDlg.h"
#include "CDlgOperatorPREDICT.h"
#include "afxdialogex.h"
#include "CDlgOperator.h"
//#include "predTa19.h"
//#include "predTi17.h"
//#include "predGH4169.h"


// CDlgOperatorPREDICT 对话框

IMPLEMENT_DYNAMIC(CDlgOperatorPREDICT, CDialogEx)

CDlgOperatorPREDICT::CDlgOperatorPREDICT(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Operator_PREDICT, pParent)
	, m_OPREStaticForce(_T("100"))
	, m_OPREAmplitude(_T("4"))
	, m_OPRESpace(_T("0.04"))
	, m_OPREVelocity(_T("4"))
	, m_OPREPasses(_T("1"))
	, m_OPREOriRS(_T("0"))
	, m_OPRERS(_T("0"))
	, m_OPREOriRa(_T("0"))
	, m_OPRERa(_T("0"))
	, m_OPREOriHardness(_T("0"))
	, m_OPREHardness(_T("0"))
	, m_OPREEffRS(_T("0%"))
	, m_OPREEffRa(_T("0%"))
	, m_OPREEffHardness(_T("0%"))
{

}

CDlgOperatorPREDICT::~CDlgOperatorPREDICT()
{
}

void CDlgOperatorPREDICT::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//材料下拉框及编辑框控件建立
	DDX_Control(pDX, IDC_OPREMaterial, m_OPREMaterial);
	DDX_Text(pDX, IDC_OPRESTATICFORCE, m_OPREStaticForce);
	DDX_Text(pDX, IDC_OPREAMPLITUDE, m_OPREAmplitude);
	DDX_Text(pDX, IDC_OPRESPACE, m_OPRESpace);
	DDX_Text(pDX, IDC_OPREVELOCITY, m_OPREVelocity);
	DDX_Text(pDX, IDC_OPREPASSES, m_OPREPasses);
	DDX_Text(pDX, IDC_OPREORIRS, m_OPREOriRS);
	DDX_Text(pDX, IDC_OPRERS, m_OPRERS);
	DDX_Text(pDX, IDC_OPREORIRA, m_OPREOriRa);
	DDX_Text(pDX, IDC_OPRERA, m_OPRERa);
	DDX_Text(pDX, IDC_OPREORIHARDNESS, m_OPREOriHardness);
	DDX_Text(pDX, IDC_OPREHARDNESS, m_OPREHardness);
	DDX_Text(pDX, IDC_OPREEffRS, m_OPREEffRS);
	DDX_Text(pDX, IDC_OPREEffRa, m_OPREEffRa);
	DDX_Text(pDX, IDC_OPREEffHardness, m_OPREEffHardness);
	//滑块控件建立
	DDX_Control(pDX, IDC_SLIDER_OPRESSTATICFORCE, m_OPRESStaticForce);
	DDX_Control(pDX, IDC_SLIDER_OPRESAmplitude, m_OPRESAmplitude);
	DDX_Control(pDX, IDC_SLIDER_OPRESSpace, m_OPRESSpace);
	DDX_Control(pDX, IDC_SLIDER_OPRESVelocity, m_OPRESVelocity);
	DDX_Control(pDX, IDC_SLIDER_OPRESPasses, m_OPRESPasses);

	//只跑一次的程序初始化
	if (num == 0)
	{
		//对下拉框添加数据
		m_OPREMaterial.AddString(TEXT("GH4169"));
		m_OPREMaterial.AddString(TEXT("Ta19"));
		m_OPREMaterial.AddString(TEXT("Ti17"));
		//设置默认下拉框选中值    SetCurrentSelect 0代表上述添加数据的第一个值
		m_OPREMaterial.SetCurSel(0);


		//静压力滑块初始化设置
		//int index_OPREStaticForce;
		m_OPRESStaticForce.SetRange(100, 500);//设置范围
		m_OPRESStaticForce.SetTicFreq(10);//设置显示刻度的间隔
		m_OPRESStaticForce.SetPos(100);//当前停留的位置
		m_OPRESStaticForce.SetLineSize(10);//一行的大小，对应键盘的方向键
		//UpdateData(TRUE);						//滑块控件当前位置代表内容赋给控件变量
		//index_OPREStaticForce = m_OPRESStaticForce.GetPos();
		//m_OPREStaticForce.Format(_T("%d"),index_OPREStaticForce);
		//UpdateData(FALSE);					//编辑框控件显示滑块控件当前位置所代表的内容

		//振幅滑块初始化设置
		m_OPRESAmplitude.SetRange(4, 10);//设置范围
		m_OPRESAmplitude.SetTicFreq(1);//设置显示刻度的间隔
		m_OPRESAmplitude.SetPos(4);//当前停留的位置
		m_OPRESAmplitude.SetLineSize(1);//一行的大小，对应键盘的方向键

		//轨迹间隔滑块初始化设置 因为滑块位置返回函数只能返回整型 所以初始化需做*100设置
		m_OPRESSpace.SetRange(4, 10);//设置范围
		m_OPRESSpace.SetTicFreq(3);//设置显示刻度的间隔
		m_OPRESSpace.SetPos(4);//当前停留的位置
		m_OPRESSpace.SetLineSize(3);//一行的大小，对应键盘的方向键

		//速度滑块初始化设置
		m_OPRESVelocity.SetRange(4, 6);//设置范围
		m_OPRESVelocity.SetTicFreq(1);//设置显示刻度的间隔
		m_OPRESVelocity.SetPos(4);//当前停留的位置
		m_OPRESVelocity.SetLineSize(1);//一行的大小，对应键盘的方向键

		//遍数滑块初始化设置
		m_OPRESPasses.SetRange(1, 20);//设置范围
		m_OPRESPasses.SetTicFreq(1);//设置显示刻度的间隔
		m_OPRESPasses.SetPos(1);//当前停留的位置
		m_OPRESPasses.SetLineSize(1);//一行的大小，对应键盘的方向键

		num++;
	}


}


BEGIN_MESSAGE_MAP(CDlgOperatorPREDICT, CDialogEx)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_OPRESTATICFORCE, &CDlgOperatorPREDICT::OnEnChangeOprestaticforce)
	ON_EN_CHANGE(IDC_OPREAMPLITUDE, &CDlgOperatorPREDICT::OnEnChangeOpreamplitude)
	ON_EN_CHANGE(IDC_OPRESPACE, &CDlgOperatorPREDICT::OnEnChangeOprespace)
	ON_EN_CHANGE(IDC_OPREVELOCITY, &CDlgOperatorPREDICT::OnEnChangeOprevelocity)
	ON_EN_CHANGE(IDC_OPREPASSES, &CDlgOperatorPREDICT::OnEnChangeOprepasses)
	//ON_BN_CLICKED(IDC_BUTTON_OPREDICT, &CDlgOperatorPREDICT::OnBnClickedButtonOpredict)
	ON_CBN_SELCHANGE(IDC_OPREMaterial, &CDlgOperatorPREDICT::OnCbnSelchangeOprematerial)
END_MESSAGE_MAP()


// CDlgOperatorPREDICT 消息处理程序


void CDlgOperatorPREDICT::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CDlgOperatorPREDICT::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	CSliderCtrl* slider = (CSliderCtrl*)pScrollBar;

	UpdateData(TRUE);

	//程序彼此并列且需反复执行 故不使用else if
	//静压力滑块移动时消息处理程序
	if (slider = &m_OPRESStaticForce)

	{

		int index_OPREStaticForce;
		index_OPREStaticForce = m_OPRESStaticForce.GetPos();
		m_OPREStaticForce.Format(_T("%d"), index_OPREStaticForce);

	}

	////振幅滑块移动时消息处理程序
	if (slider = &m_OPRESAmplitude)

	{
		int index_OPREAmplitude;
		index_OPREAmplitude = m_OPRESAmplitude.GetPos();
		m_OPREAmplitude.Format(_T("%d"), index_OPREAmplitude);
	}

	//轨迹间隔滑块移动时消息处理程序
	if (slider = &m_OPRESSpace)
	{
		float index_OPRESpace;								//index_OPRESpace用于获取滑块控件位置
		float index_OPRESpaceTRUE;							//index_OPRESpaceTRUE用于得到该位置真正代表的值
		index_OPRESpace = m_OPRESSpace.GetPos();
		index_OPRESpaceTRUE = index_OPRESpace / 100;		//滑块位置真正代表的值为滑块位置/100
		m_OPRESpace.Format(_T("%.2f"), index_OPRESpaceTRUE);
	}

	//速度滑块移动时消息处理程序
	if (slider = &m_OPRESVelocity)
	{
		int index_OPREVelocity;
		index_OPREVelocity = m_OPRESVelocity.GetPos();
		m_OPREVelocity.Format(_T("%d"), index_OPREVelocity);
	}

	//遍数滑块移动时消息处理程序
	if (slider = &m_OPRESPasses)
	{
		int index_OPREPasses;
		index_OPREPasses = m_OPRESPasses.GetPos();
		m_OPREPasses.Format(_T("%d"), index_OPREPasses);
	}

	UpdateData(FALSE);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);

}

//静压力编辑框内容反馈到静压力滑块位置
void CDlgOperatorPREDICT::OnEnChangeOprestaticforce()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	float pos;
	pos = _wtof(m_OPREStaticForce);
	m_OPRESStaticForce.SetPos(pos);
	Invalidate();

}

//振幅编辑框内容反馈到振幅滑块位置
void CDlgOperatorPREDICT::OnEnChangeOpreamplitude()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	float pos;
	pos = _wtof(m_OPREAmplitude);
	m_OPRESAmplitude.SetPos(pos);
	Invalidate();
}

//轨迹间隔编辑框内容反馈到轨迹间隔滑块位置
void CDlgOperatorPREDICT::OnEnChangeOprespace()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	float pos;						//编辑框输入的值
	float posTRUE;					//值经处理后 滑块真实位置
	pos = _wtof(m_OPRESpace);
	posTRUE = pos * 100;
	m_OPRESSpace.SetPos(posTRUE);
	Invalidate();
}

//速度编辑框内容反馈到速度滑块位置
void CDlgOperatorPREDICT::OnEnChangeOprevelocity()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	float pos;
	pos = _wtof(m_OPREVelocity);
	m_OPRESVelocity.SetPos(pos);
	Invalidate();
}

//遍数编辑框内容反馈到遍数滑块位置
void CDlgOperatorPREDICT::OnEnChangeOprepasses()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	float pos;
	pos = _wtof(m_OPREPasses);
	m_OPRESPasses.SetPos(pos);
	Invalidate();
}


void CDlgOperatorPREDICT::OnCbnSelchangeOprematerial()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_OPREMaterial.GetCurSel();							//将当前材料名索引值赋值给int型index变量
	CString str;											//新建用以显示材料名的新字符串变量 C++类定义默认Private类型变量
	CString str1;											//用以显示整个提示语的字符串变量
	m_OPREMaterial.GetLBText(index, str);							//得到index代表的字符并存在str中
	str1.Format(_T("您重新选择了%s材料，请注意重新输入工艺参数及原始数据！"), str);
	//将代表材料名的字符串变量重整到整个输出字符串变量中
	MessageBox(str1, TEXT("提示！"), MB_OK | MB_ICONEXCLAMATION);			//输出更换材料时的提示语，及左上角警示语

	//更换材料后对已输入的工艺参数以及原始数据及上次得到的强化后结果及效果进行删除
	m_OPREStaticForce = TEXT("100");
	m_OPREAmplitude = TEXT("4");
	m_OPRESpace = TEXT("0.04");
	m_OPREVelocity = TEXT("4");
	m_OPREPasses = TEXT("1");
	m_OPREOriRS = TEXT("0");
	m_OPRERS = TEXT("0");
	m_OPREOriRa = TEXT("0");
	m_OPRERa = TEXT("0");
	m_OPREOriHardness = TEXT("0");
	m_OPREHardness = TEXT("0");
	m_OPREEffRS = TEXT("0%");
	m_OPREEffRa = TEXT("0%");
	m_OPREEffHardness = TEXT("0%");
	int pos_OPREStaticForce, pos_OPREAmplitude, pos_OPRESpace, pos_OPREVelocity, pos_OPREPasses;
	pos_OPREStaticForce = 100;
	pos_OPREAmplitude = 4;
	pos_OPRESpace = 4;
	pos_OPREVelocity = 4;
	pos_OPREPasses = 1;
	m_OPRESStaticForce.SetPos(pos_OPREStaticForce);
	m_OPRESAmplitude.SetPos(pos_OPREAmplitude);
	m_OPRESSpace.SetPos(pos_OPRESpace);
	m_OPRESVelocity.SetPos(pos_OPREVelocity);
	m_OPRESPasses.SetPos(pos_OPREPasses);
	UpdateData(FALSE);
}

/*void CDlgOperatorPREDICT::OnBnClickedButtonOpredict()
{
	// TODO: 在此添加控件通知处理程序代码
	//设置布尔变量以判断模型是否初始化成功
	//bool isOk = 0;

	//神经网络预测模型初始化
	predTa19Initialize();
	predTi17Initialize();
	predGH4169Initialize();


	//isOk = predTa19Initialize();

	//设置用于matlab预测模型使用的数值矩阵型变量   而编辑框中输入的是字符串，需要字符串转数值 再预测 再数值转字符串
	//设置matlab返回来的数值矩阵型变量 一行三列的数值矩阵 需要分别提取 并转换成字符串类型  先行再列看官方定义
	//即如果赋值矩阵为[1,2,3,4] 而mwArray设为2x2的矩阵，则mwArray转换后，matlab中的结果会是[{1,3},{2,4}]
	//设置用于预测模型输入的数值矩阵 一行八列 1,8,mxDOUBLE_CLASS
	mwArray Input(1, 8, mxDOUBLE_CLASS);


	//ComboBox下拉框材料名的获取   0是Ta19 1是Ti17 2是GH4169  得到其索引值

	int index = m_OPREMaterial.GetCurSel();

	//获取编辑框中内容，并将其赋值给相对应的变量m_*
	UpdateData(TRUE);

	//从编辑框中获取所输入的字符串并将其转换成数值 
	float M_StaticForce = _wtof(m_OPREStaticForce);
	float M_Amplitude = _wtof(m_OPREAmplitude);
	float M_Space = _wtof(m_OPRESpace);
	float M_Velocity = _wtof(m_OPREVelocity);
	float M_Passes = _wtof(m_OPREPasses);
	float M_OriRS = _wtof(m_OPREOriRS);
	float M_OriRa = _wtof(m_OPREOriRa);
	float M_OriHardness = _wtof(m_OPREOriHardness);





	//设置用于给输入矩阵赋值的数值矩阵，并将输入的变量导入
	float FInput[8] = { M_StaticForce,M_Amplitude,M_Space,M_Velocity,M_Passes,M_OriRS,M_OriRa,M_OriHardness };
	Input.SetData(FInput, 8);

	//设置用于返回预测结果的mwArray矩阵
	mwArray Output(1, 3, mxDOUBLE_CLASS);

	//设置用于获取返回矩阵中内容的float型变量
	float M_RS, M_Ra, M_Hardness;

	//调用matlab动态库进行模型预测	第一个数字是输出的量的数目 即便输出的是多维矩阵 但矩阵只有一个 所以只输出了一个量
	if (index == 0)
	{
		predictionGH4169(1, Output, Input);

	}
	else if (index == 1)
	{
		predictionTa19(1, Output, Input);
	}
	else if (index == 2)
	{
		predictionTi17(1, Output, Input);

	}
	else
		MessageBox(_T("尚未建立相应预测模型！"), _T("警告！"), MB_OK | MB_ICONEXCLAMATION);


	//获取返回矩阵中的数值       在获取一般矩阵时，SetData会自动把数值填充成自己的格式，所以只要读取和设定mwArray格式一样即可 Get函数中也是先列后行
	//get函数中 得到的是一行三列的矩阵，按照先行后列的顺序，直接按顺序取数据不用关心矩阵行列，转换的事情即便有mwArray也会做掉 
	//也可以直接get(1,1),get(1,2),get(1,3) 即获取矩阵里第一个第二个第三个数据 
	//第一个数字是后面用于获取数据的坐标的长度 
	M_RS = Output.Get(2, 1, 1);
	M_Ra = Output.Get(2, 1, 2);
	M_Hardness = Output.Get(2, 1, 3);


	//将得到的数值转换成字符串数据，并赋值给相应控件变量
	m_OPRERS.Format(_T("%.2f"), M_RS);
	m_OPRERa.Format(_T("%.3f"), M_Ra);
	m_OPREHardness.Format(_T("%.1f"), M_Hardness);

	CString M_cbx, str;
	m_OPREMaterial.GetLBText(index, M_cbx);			//获取下拉框控件中的内容，内容同步到控件对应的变量
	str.Format(_T("%s材料预测成功！"), M_cbx);
	MessageBox(str, _T("提示！"), MB_OK | MB_ICONINFORMATION);

	//将变量的内容同步到控件

	//对强化效果进行计算
	float M_EffRS, M_EffRa, M_EffHardness;					//定义三个强化效果计算专用float型变量

	M_EffRS = ((M_RS - M_OriRS) * 100) / M_OriRS;
	M_EffRa = ((M_OriRa - M_Ra) * 100) / M_OriRa;
	M_EffHardness = ((M_Hardness - M_OriHardness) * 100) / M_OriHardness;


	//将强化效果计算结果从float型变量 转化到和控件对应变量一致的CString 并加上百分号 直接输出.2f就可以输出两位小数了
	m_OPREEffRS.Format(_T("%.2f%%"), M_EffRS);
	m_OPREEffRa.Format(_T("%.2f%%"), M_EffRa);
	m_OPREEffHardness.Format(_T("%.2f%%"), M_EffHardness);


	UpdateData(FALSE);

	//关闭库和程序
	//predTa19Terminate();
	//mclTerminateApplication();      //没必要关 一直开着吧

	return;

}*/


