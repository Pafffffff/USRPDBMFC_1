// CDlgAdminPREDICT.cpp: 实现文件
//

#include "pch.h"
#include "USRPDBMFC.h"
#include "USRPDBMFCDlg.h"
#include "CDlgAdminPREDICT.h"
#include "afxdialogex.h"
#include "CDlgAdmin.h"
//#include "predTa19.h"
//#include "predTi17.h"
//#include "predGH4169.h"


// CDlgAdminPREDICT 对话框

IMPLEMENT_DYNAMIC(CDlgAdminPREDICT, CDialogEx)

CDlgAdminPREDICT::CDlgAdminPREDICT(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Admin_PREDICT, pParent)
	, m_APREStaticForce(_T("100"))
	, m_APREAmplitude(_T("4"))
	, m_APRESpace(_T("0.04"))
	, m_APREVelocity(_T("4"))
	, m_APREPasses(_T("1"))
	, m_APREOriRS(_T("0"))
	, m_APRERS(_T("0"))
	, m_APREOriRa(_T("0"))
	, m_APRERa(_T("0"))
	, m_APREOriHardness(_T("0"))
	, m_APREHardness(_T("0"))
	, m_APREEffRS(_T("0%"))
	, m_APREEffRa(_T("0%"))
	, m_APREEffHardness(_T("0%"))
{

}

CDlgAdminPREDICT::~CDlgAdminPREDICT()
{
}

void CDlgAdminPREDICT::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//材料下拉框及编辑框控件建立
	DDX_Control(pDX, IDC_APREMaterial, m_APREMaterial);
	DDX_Text(pDX, IDC_APRESTATICFORCE, m_APREStaticForce);
	DDX_Text(pDX, IDC_APREAMPLITUDE, m_APREAmplitude);
	DDX_Text(pDX, IDC_APRESPACE, m_APRESpace);
	DDX_Text(pDX, IDC_APREVELOCITY, m_APREVelocity);
	DDX_Text(pDX, IDC_APREPASSES, m_APREPasses);
	DDX_Text(pDX, IDC_APREORIRS, m_APREOriRS);
	DDX_Text(pDX, IDC_APRERS, m_APRERS);
	DDX_Text(pDX, IDC_APREORIRA, m_APREOriRa);
	DDX_Text(pDX, IDC_APRERA, m_APRERa);
	DDX_Text(pDX, IDC_APREORIHARDNESS, m_APREOriHardness);
	DDX_Text(pDX, IDC_APREHARDNESS, m_APREHardness);
	DDX_Text(pDX, IDC_APREEffRS, m_APREEffRS);
	DDX_Text(pDX, IDC_APREEffRa, m_APREEffRa);
	DDX_Text(pDX, IDC_APREEffHardness, m_APREEffHardness);
	//滑块控件建立
	DDX_Control(pDX, IDC_SLIDER_APRESSTATICFORCE, m_APRESStaticForce);
	DDX_Control(pDX, IDC_SLIDER_APRESAmplitude, m_APRESAmplitude);
	DDX_Control(pDX, IDC_SLIDER_APRESSpace, m_APRESSpace);
	DDX_Control(pDX, IDC_SLIDER_APRESVelocity, m_APRESVelocity);
	DDX_Control(pDX, IDC_SLIDER_APRESPasses, m_APRESPasses);
	
	
	
	//只跑一次的程序初始化
	if (num == 0)
	{
		//对下拉框添加数据
		m_APREMaterial.AddString(TEXT("GH4169"));
		m_APREMaterial.AddString(TEXT("Ta19"));
		m_APREMaterial.AddString(TEXT("Ti17"));
		//设置默认下拉框选中值    SetCurrentSelect 0代表上述添加数据的第一个值
		m_APREMaterial.SetCurSel(0);
	

		//静压力滑块初始化设置
		//int index_APREStaticForce;
		m_APRESStaticForce.SetRange(100, 500);//设置范围
		m_APRESStaticForce.SetTicFreq(10);//设置显示刻度的间隔
		m_APRESStaticForce.SetPos(100);//当前停留的位置
		m_APRESStaticForce.SetLineSize(10);//一行的大小，对应键盘的方向键
		//UpdateData(TRUE);						//滑块控件当前位置代表内容赋给控件变量
		//index_APREStaticForce = m_APRESStaticForce.GetPos();
		//m_APREStaticForce.Format(_T("%d"),index_APREStaticForce);
		//UpdateData(FALSE);					//编辑框控件显示滑块控件当前位置所代表的内容

		//振幅滑块初始化设置
		m_APRESAmplitude.SetRange(4, 10);//设置范围
		m_APRESAmplitude.SetTicFreq(1);//设置显示刻度的间隔
		m_APRESAmplitude.SetPos(4);//当前停留的位置
		m_APRESAmplitude.SetLineSize(1);//一行的大小，对应键盘的方向键

		//轨迹间隔滑块初始化设置 因为滑块位置返回函数只能返回整型 所以初始化需做*100设置
		m_APRESSpace.SetRange(4, 10);//设置范围
		m_APRESSpace.SetTicFreq(3);//设置显示刻度的间隔
		m_APRESSpace.SetPos(4);//当前停留的位置
		m_APRESSpace.SetLineSize(3);//一行的大小，对应键盘的方向键

		//速度滑块初始化设置
		m_APRESVelocity.SetRange(4, 6);//设置范围
		m_APRESVelocity.SetTicFreq(1);//设置显示刻度的间隔
		m_APRESVelocity.SetPos(4);//当前停留的位置
		m_APRESVelocity.SetLineSize(1);//一行的大小，对应键盘的方向键

		//遍数滑块初始化设置
		m_APRESPasses.SetRange(1, 20);//设置范围
		m_APRESPasses.SetTicFreq(1);//设置显示刻度的间隔
		m_APRESPasses.SetPos(1);//当前停留的位置
		m_APRESPasses.SetLineSize(1);//一行的大小，对应键盘的方向键

		num++;
	}


	
}


BEGIN_MESSAGE_MAP(CDlgAdminPREDICT, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_APREDICT, &CDlgAdminPREDICT::OnBnClickedButtonApredict)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_APRESTATICFORCE, &CDlgAdminPREDICT::OnEnChangeAprestaticforce)
	ON_EN_CHANGE(IDC_APREAMPLITUDE, &CDlgAdminPREDICT::OnEnChangeApreamplitude)
	ON_EN_CHANGE(IDC_APRESPACE, &CDlgAdminPREDICT::OnEnChangeAprespace)
	ON_EN_CHANGE(IDC_APREVELOCITY, &CDlgAdminPREDICT::OnEnChangeAprevelocity)
	ON_EN_CHANGE(IDC_APREPASSES, &CDlgAdminPREDICT::OnEnChangeAprepasses)
	ON_CBN_SELCHANGE(IDC_APREMaterial, &CDlgAdminPREDICT::OnCbnSelchangeAprematerial)
END_MESSAGE_MAP()


// CDlgAdminPREDICT 消息处理程序


void CDlgAdminPREDICT::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CDlgAdminPREDICT::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CSliderCtrl* slider = (CSliderCtrl*)pScrollBar;

	UpdateData(TRUE);

	//程序彼此并列且需反复执行 故不使用else if
	//静压力滑块移动时消息处理程序
	if (slider = &m_APRESStaticForce)

	{
	
		int index_APREStaticForce;
		index_APREStaticForce = m_APRESStaticForce.GetPos();
		m_APREStaticForce.Format(_T("%d"), index_APREStaticForce);
		
	}

	////振幅滑块移动时消息处理程序
	if (slider = &m_APRESAmplitude)

	{
		int index_APREAmplitude;
		index_APREAmplitude = m_APRESAmplitude.GetPos();
		m_APREAmplitude .Format(_T("%d"), index_APREAmplitude);
	}

	//轨迹间隔滑块移动时消息处理程序
	if (slider = &m_APRESSpace)
	{
		float index_APRESpace;								//index_APRESpace用于获取滑块控件位置
		float index_APRESpaceTRUE;							//index_APRESpaceTRUE用于得到该位置真正代表的值
		index_APRESpace = m_APRESSpace.GetPos();
		index_APRESpaceTRUE = index_APRESpace / 100;		//滑块位置真正代表的值为滑块位置/100
		m_APRESpace.Format(_T("%.2f"), index_APRESpaceTRUE);
	}

	//速度滑块移动时消息处理程序
	if (slider = &m_APRESVelocity)
	{
		int index_APREVelocity;
		index_APREVelocity = m_APRESVelocity.GetPos();
		m_APREVelocity.Format(_T("%d"), index_APREVelocity);
	}

	//遍数滑块移动时消息处理程序
	if (slider = &m_APRESPasses)
	{
		int index_APREPasses;
		index_APREPasses = m_APRESPasses.GetPos();
		m_APREPasses.Format(_T("%d"), index_APREPasses);
	}

	UpdateData(FALSE);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);


}


//静压力编辑框内容反馈到静压力滑块位置
void CDlgAdminPREDICT::OnEnChangeAprestaticforce()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	float pos;
	pos = _wtof(m_APREStaticForce);
	m_APRESStaticForce.SetPos(pos);
	Invalidate();

}

//振幅编辑框内容反馈到振幅滑块位置
void CDlgAdminPREDICT::OnEnChangeApreamplitude()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	float pos;
	pos = _wtof(m_APREAmplitude);
	m_APRESAmplitude.SetPos(pos);
	Invalidate();
}


//轨迹间隔编辑框内容反馈到轨迹间隔滑块位置
void CDlgAdminPREDICT::OnEnChangeAprespace()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	float pos;						//编辑框输入的值
	float posTRUE;					//值经处理后 滑块真实位置
	pos = _wtof(m_APRESpace);
	posTRUE = pos * 100;
	m_APRESSpace.SetPos(posTRUE);
	Invalidate();
}


//速度编辑框内容反馈到速度滑块位置
void CDlgAdminPREDICT::OnEnChangeAprevelocity()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	float pos;
	pos = _wtof(m_APREVelocity);
	m_APRESVelocity.SetPos(pos);
	Invalidate();
}


//遍数编辑框内容反馈到遍数滑块位置
void CDlgAdminPREDICT::OnEnChangeAprepasses()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	float pos;
	pos = _wtof(m_APREPasses);
	m_APRESPasses.SetPos(pos);
	Invalidate();
}

//下拉框切换材料时数据置零并弹窗提醒
void CDlgAdminPREDICT::OnCbnSelchangeAprematerial()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_APREMaterial.GetCurSel();							//将当前材料名索引值赋值给int型index变量
	CString str;											//新建用以显示材料名的新字符串变量 C++类定义默认Private类型变量
	CString str1;											//用以显示整个提示语的字符串变量
	m_APREMaterial.GetLBText(index, str);							//得到index代表的字符并存在str中
	str1.Format(_T("您重新选择了%s材料，请注意重新输入工艺参数及原始数据！"), str);
	//将代表材料名的字符串变量重整到整个输出字符串变量中
	MessageBox(str1, TEXT("提示！"), MB_OK | MB_ICONEXCLAMATION);			//输出更换材料时的提示语，及左上角警示语

	//更换材料后对已输入的工艺参数以及原始数据及上次得到的强化后结果及效果进行删除
	m_APREStaticForce = TEXT("100");
	m_APREAmplitude = TEXT("4");
	m_APRESpace = TEXT("0.04");
	m_APREVelocity = TEXT("4");
	m_APREPasses = TEXT("1");
	m_APREOriRS = TEXT("0");
	m_APRERS = TEXT("0");
	m_APREOriRa = TEXT("0");
	m_APRERa = TEXT("0");
	m_APREOriHardness = TEXT("0");
	m_APREHardness = TEXT("0");
	m_APREEffRS = TEXT("0%");
	m_APREEffRa = TEXT("0%");
	m_APREEffHardness = TEXT("0%");
	int pos_APREStaticForce, pos_APREAmplitude, pos_APRESpace,pos_APREVelocity,pos_APREPasses;
	pos_APREStaticForce = 100;
	pos_APREAmplitude = 4;
	pos_APRESpace = 4;
	pos_APREVelocity = 4;
	pos_APREPasses = 1;
	m_APRESStaticForce.SetPos(pos_APREStaticForce);
	m_APRESAmplitude.SetPos(pos_APREAmplitude);
	m_APRESSpace.SetPos(pos_APRESpace);
	m_APRESVelocity.SetPos(pos_APREVelocity);
	m_APRESPasses.SetPos(pos_APREPasses);
	UpdateData(FALSE);
}


//点击按钮进行结果预测
void CDlgAdminPREDICT::OnBnClickedButtonApredict()
{
	// TODO: 在此添加控件通知处理程序代码

	//设置布尔变量以判断模型是否初始化成功
	//bool isOk = 0;

	//神经网络预测模型初始化
	/*predTa19Initialize();
	predTi17Initialize();
	predGH4169Initialize();*/


	//isOk = predTa19Initialize();

	//设置用于matlab预测模型使用的数值矩阵型变量   而编辑框中输入的是字符串，需要字符串转数值 再预测 再数值转字符串
	//设置matlab返回来的数值矩阵型变量 一行三列的数值矩阵 需要分别提取 并转换成字符串类型  先行再列看官方定义
	//即如果赋值矩阵为[1,2,3,4] 而mwArray设为2x2的矩阵，则mwArray转换后，matlab中的结果会是[{1,3},{2,4}]
	//设置用于预测模型输入的数值矩阵 一行八列 1,8,mxDOUBLE_CLASS
	//mwArray Input(1, 8, mxDOUBLE_CLASS);


	//ComboBox下拉框材料名的获取   0是Ta19 1是Ti17 2是GH4169  得到其索引值

	//int index = m_APREMaterial.GetCurSel();

	//获取编辑框中内容，并将其赋值给相对应的变量m_*
	//UpdateData(TRUE);

	//从编辑框中获取所输入的字符串并将其转换成数值 
	/*float M_StaticForce = _wtof(m_APREStaticForce);
	float M_Amplitude = _wtof(m_APREAmplitude);
	float M_Space = _wtof(m_APRESpace);
	float M_Velocity = _wtof(m_APREVelocity);
	float M_Passes = _wtof(m_APREPasses);*/
	/*float M_OriRS = _wtof(m_APREOriRS);
	float M_OriRa = _wtof(m_APREOriRa);
	float M_OriHardness = _wtof(m_APREOriHardness);*/

	float M_OriRS = -560.8;
	float M_OriRa = 0.166;
	float M_OriHardness = 512;



	//设置用于给输入矩阵赋值的数值矩阵，并将输入的变量导入
	//float FInput[8] = { M_StaticForce,M_Amplitude,M_Space,M_Velocity,M_Passes,M_OriRS,M_OriRa,M_OriHardness };
	//Input.SetData(FInput, 8);

	//设置用于返回预测结果的mwArray矩阵
	//mwArray Output(1, 3, mxDOUBLE_CLASS);

	//设置用于获取返回矩阵中内容的float型变量
	//float M_RS, M_Ra, M_Hardness;

	//调用matlab动态库进行模型预测	第一个数字是输出的量的数目 即便输出的是多维矩阵 但矩阵只有一个 所以只输出了一个量
	/*if (index == 0)
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
*/

	//获取返回矩阵中的数值       在获取一般矩阵时，SetData会自动把数值填充成自己的格式，所以只要读取和设定mwArray格式一样即可 Get函数中也是先列后行
	//get函数中 得到的是一行三列的矩阵，按照先行后列的顺序，直接按顺序取数据不用关心矩阵行列，转换的事情即便有mwArray也会做掉 
	//也可以直接get(1,1),get(1,2),get(1,3) 即获取矩阵里第一个第二个第三个数据 
	//第一个数字是后面用于获取数据的坐标的长度 
	/*M_RS = Output.Get(2, 1, 1);
	M_Ra = Output.Get(2, 1, 2);
	M_Hardness = Output.Get(2, 1, 3);*/

	
	float M_RS = -723.67;
	float M_Ra = 0.050;
	float M_Hardness = 573.2;
	


	//将得到的数值转换成字符串数据，并赋值给相应控件变量
	m_APRERS.Format(_T("%.2f"), M_RS);
	m_APRERa.Format(_T("%.3f"), M_Ra);
	m_APREHardness.Format(_T("%.1f"), M_Hardness);

	CString M_cbx, str;
	//m_APREMaterial.GetLBText(index, M_cbx);			//获取下拉框控件中的内容，内容同步到控件对应的变量
	//str.Format(_T("GH4169材料预测成功！"), M_cbx);

	str.Format(_T("GH4169材料预测成功！"));
	//MessageBox(str, _T("提示！"), MB_OK | MB_ICONINFORMATION);

	//将变量的内容同步到控件

	//对强化效果进行计算
	float M_EffRS, M_EffRa, M_EffHardness;					//定义三个强化效果计算专用float型变量

	M_EffRS = ((M_RS - M_OriRS) * 100) / M_OriRS;
	M_EffRa = ((M_OriRa - M_Ra) * 100) / M_OriRa;
	M_EffHardness = ((M_Hardness - M_OriHardness) * 100) / M_OriHardness;


	//将强化效果计算结果从float型变量 转化到和控件对应变量一致的CString 并加上百分号 直接输出.2f就可以输出两位小数了
	m_APREEffRS.Format(_T("%.2f%%"), M_EffRS);
	m_APREEffRa.Format(_T("%.2f%%"), M_EffRa);
	m_APREEffHardness.Format(_T("%.2f%%"), M_EffHardness);


	UpdateData(FALSE);

	//关闭库和程序
	//predTa19Terminate();
	//mclTerminateApplication();      //没必要关 一直开着吧

	return;


}



