// QdDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "QdDlg.h"
#include "afxdialogex.h"


// CQdDlg 对话框

IMPLEMENT_DYNAMIC(CQdDlg, CAcUiDialog)

CQdDlg::CQdDlg(CWnd* pParent /*=NULL*/)
: CAcUiDialog(CQdDlg::IDD, pParent)
{

}

CQdDlg::~CQdDlg()
{
}

void CQdDlg::DoDataExchange(CDataExchange* pDX)
{
	CAcUiDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_RADIO_XY, m_radioXy);
	DDX_Check(pDX, IDC_RADIO_AB, m_radioAb);
	DDX_Check(pDX, IDC_RADIO_NE, m_radioNe);
	DDX_Check(pDX, IDC_RADIO_NONE, m_radioNone);
	DDX_Check(pDX, IDC_RADIO_MASK, m_radioMask);

	DDX_Check(pDX, IDC_RADIO_ZYTC, m_radioZytc);
	DDX_Check(pDX, IDC_RADIO_DQTC, m_radioDqtc);

	DDX_Check(pDX, IDC_RADIO_DQ, m_radioDq);
	DDX_Check(pDX, IDC_RADIO_SJ, m_radioSj);
	DDX_Check(pDX, IDC_RADIO_ZDY, m_radioZdy);

	DDX_Text(pDX, IDC_EDIT_ZG, m_sZg);
	DDX_Text(pDX, IDC_EDIT_BZBL, m_sBzbl);
	DDX_Text(pDX, IDC_EDIT_FWJ, m_sFwj);
	DDX_Control(pDX, IDC_CMB_JD, m_cmbJd);

	DDX_Check(pDX, IDC_CHECK_HH, m_bHH);

	DDX_Text(pDX, IDC_EDIT_X, m_sX);
	DDX_Text(pDX, IDC_EDIT_Y, m_sY);
	DDX_Text(pDX, IDC_EDIT_XZJ, m_sXzj);
}


BEGIN_MESSAGE_MAP(CQdDlg, CAcUiDialog)
	ON_BN_CLICKED(IDOK, &CQdDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_PICKPOINT, &CQdDlg::OnBnClickedBtnPickpoint)
	ON_BN_CLICKED(IDC_RADIO_DQ, &CQdDlg::OnBnClickedRadioDq)
	ON_BN_CLICKED(IDC_RADIO_ZDY, &CQdDlg::OnBnClickedRadioZdy)
END_MESSAGE_MAP()


// CQdDlg 消息处理程序
void CQdDlg::SaveIni()
{
	CIniFile ini(GetIniPath());
	if (m_radioXy)
	{
		ini.SetValueOfKey(_T("MAIN"), _T("QZ"), _T("XY"));
	}
	else if (m_radioAb)
	{
		ini.SetValueOfKey(_T("MAIN"), _T("QZ"), _T("AB"));
	}
	else if(m_radioNe)
	{
		ini.SetValueOfKey(_T("MAIN"), _T("QZ"), _T("NE"));
	}
	else if (m_radioNone)
	{
		ini.SetValueOfKey(_T("MAIN"), _T("QZ"), _T("NONE"));
	}
	else if(m_radioMask)
	{
		ini.SetValueOfKey(_T("MAIN"), _T("QZ"), _T("MASK"));
	}
	else
	{
		ini.SetValueOfKey(_T("MAIN"), _T("QZ"), _T(""));
	}
	if (m_radioZytc)
	{
		ini.SetValueOfKey(_T("MAIN"), _T("TC"), _T("专用图层"));
	}
	else if (m_radioDqtc)
	{
		ini.SetValueOfKey(_T("MAIN"), _T("TC"), _T("当前图层"));
	}
	else
	{
		ini.SetValueOfKey(_T("MAIN"), _T("TC"), _T(""));
	}
	if (m_radioDq)
	{
		ini.SetValueOfKey(_T("MAIN"), _T("ZBX"), _T("当前坐标系"));
	}
	else if (m_radioZdy)
	{
		ini.SetValueOfKey(_T("MAIN"), _T("ZBX"), _T("自定义坐标系"));
	}
	else if (m_radioSj)
	{
		ini.SetValueOfKey(_T("MAIN"), _T("ZBX"), _T("世界坐标系"));
	}
	else
	{
		ini.SetValueOfKey(_T("MAIN"), _T("ZBX"), _T(""));
	}
	if (m_bHH)
	{
		ini.SetValueOfKey(_T("MAIN"), _T("HH"), _T("是"));
	}
	else
	{
		ini.SetValueOfKey(_T("MAIN"), _T("HH"), _T("否"));
	}
	ini.SetValueOfKey(_T("MAIN"), _T("ZG"), m_sZg);
	CString sJd;
	GetDlgItemText(IDC_CMB_JD, sJd);
	ini.SetValueOfKey(_T("MAIN"), _T("JD"), sJd);
	ini.SetValueOfKey(_T("MAIN"), _T("BZBL"), m_sBzbl);
	ini.SetValueOfKey(_T("MAIN"), _T("FWJ"), m_sFwj);

	ini.SetValueOfKey(_T("MAIN"), _T("X"), m_sX);
	ini.SetValueOfKey(_T("MAIN"), _T("Y"), m_sY);
	ini.SetValueOfKey(_T("MAIN"), _T("XZJ"), m_sXzj);
}

void CQdDlg::GetIni()
{
	CIniFile ini(GetIniPath());
	CString QZ, TC,ZBX;
	ini.GetValueOfKey(_T("MAIN"), _T("QZ"), QZ);
	ini.GetValueOfKey(_T("MAIN"), _T("TC"), TC);
	ini.GetValueOfKey(_T("MAIN"), _T("ZBX"), ZBX);
	if (QZ==_T("XY"))
	{
		m_radioXy = true;
		m_radioAb = false;
		m_radioNe = false;
		m_radioNone = false;
		m_radioMask = false;
	}
	else if (QZ == _T("AB"))
	{
		m_radioXy = false;
		m_radioAb = true;
		m_radioNe = false;
		m_radioNone = false;
		m_radioMask = false;
	}
	else if (QZ == _T("NE"))
	{
		m_radioXy = false;
		m_radioAb = false;
		m_radioNe = true;
		m_radioNone = false;
		m_radioMask = false;
	}
	else if (QZ == _T("NONE"))
	{
		m_radioXy = false;
		m_radioAb = false;
		m_radioNe = false;
		m_radioNone = true;
		m_radioMask = false;
	}
	else if (QZ == _T("MASK"))
	{
		m_radioXy = false;
		m_radioAb = false;
		m_radioNe = false;
		m_radioNone = false;
		m_radioMask = true;
	}
	else
	{
		m_radioXy = false;
		m_radioAb = false;
		m_radioNe = false;
		m_radioNone = false;
		m_radioMask = false;
	}

	if (TC==_T("专用图层"))
	{
		m_radioZytc = true;
		m_radioDqtc = false;
	}
	else
	{
		m_radioZytc = false;
		m_radioDqtc = true;
	}
	if (ZBX==_T("当前坐标系"))
	{
		m_radioDq = true;
		m_radioSj = false;
		m_radioZdy = false;
		GetDlgItem(IDC_EDIT_X)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_Y)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_XZJ)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_PICKPOINT)->EnableWindow(FALSE);
	}
	else if (ZBX == _T("世界坐标系"))
	{
		m_radioDq = false;
		m_radioSj = true;
		m_radioZdy = false;
		GetDlgItem(IDC_EDIT_X)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_Y)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_XZJ)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_PICKPOINT)->EnableWindow(FALSE);
	}
	else
	{
		m_radioDq = false;
		m_radioSj = false;
		m_radioZdy = true;
		GetDlgItem(IDC_EDIT_X)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_Y)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_XZJ)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_PICKPOINT)->EnableWindow(TRUE);
	}
	CString HH, JD;
	ini.GetValueOfKey(_T("MAIN"), _T("HH"), HH);
	ini.GetValueOfKey(_T("MAIN"), _T("JD"), JD);
	if (HH==_T("是"))
	{
		m_bHH = TRUE;
	}
	else
	{
		m_bHH = FALSE;
	}
//	SetDlgItemText(IDC_CMB_JD, JD);
	m_cmbJd.SetCurSel(m_cmbJd.FindString(0, JD));
	ini.GetValueOfKey(_T("MAIN"), _T("ZG"), m_sZg);
	ini.GetValueOfKey(_T("MAIN"), _T("BZBL"), m_sBzbl);
	ini.GetValueOfKey(_T("MAIN"), _T("FWJ"), m_sFwj);

	ini.GetValueOfKey(_T("MAIN"), _T("X"), m_sX);
	ini.GetValueOfKey(_T("MAIN"), _T("Y"), m_sY);
	ini.GetValueOfKey(_T("MAIN"), _T("XZJ"), m_sXzj);
}

BOOL CQdDlg::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();
	CString sJdbx;
	CIniFile ini(GetIniPath());
	ini.GetValueOfKey(_T("MAIN"), _T("JDBX"), sJdbx);
	FillCombo(m_cmbJd, sJdbx);
	GetIni();
	UpdateData(FALSE);
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CQdDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	SaveIni();
	CAcUiDialog::OnOK();
}

void CQdDlg::OnBnClickedBtnPickpoint()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	BeginEditorCommand();
	CString sJd;
	GetDlgItemText(IDC_CMB_JD, sJd);
	int iJd; CString sFormat;
	if (sJd == _T("0.1"))
	{
		sFormat = _T("%.1f");
		iJd = 1;
	}
	if (sJd == _T("0.01"))
	{
		sFormat = _T("%.2f");
		iJd = 2;
	}
	if (sJd == _T("0.001"))
	{
		sFormat = _T("%.3f");
		iJd = 3;
	}
	if (sJd == _T("0.0001"))
	{
		sFormat = _T("%.4f");
		iJd = 4;
	}
	if (sJd == _T("0.00001"))
	{
		sFormat = _T("%.5f");
		iJd = 5;
	}
	if (sJd == _T("0.000001"))
	{
		sFormat = _T("%.6f");
		iJd = 6;
	}

	AcGePoint3d pt;
	if (CGetInputUtil::GetPoint(_T("\n选择自定义中心点:"), pt))
	{
		CString sX, sY;
		double x, y;
		x = pt.x;
		x = decimalNum(x, iJd);
		y = pt.y;
		y = decimalNum(y, iJd);
		sX.Format(sFormat, x);
		sY.Format(sFormat, y);
		SetDlgItemText(IDC_EDIT_X, sX);
		SetDlgItemText(IDC_EDIT_Y, sY);
	}
	CompleteEditorCommand(TRUE);
	UpdateData(TRUE);
}

void CQdDlg::OnBnClickedRadioDq()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_radioDq)
	{
		GetDlgItem(IDC_EDIT_X)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_Y)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_XZJ)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_PICKPOINT)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_X)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_Y)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_XZJ)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_PICKPOINT)->EnableWindow(TRUE);
	}
	UpdateData(FALSE);
}

void CQdDlg::OnBnClickedRadioZdy()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_radioDq)
	{
		GetDlgItem(IDC_EDIT_X)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_Y)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_XZJ)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_PICKPOINT)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_X)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_Y)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_XZJ)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_PICKPOINT)->EnableWindow(TRUE);
	}
	UpdateData(FALSE);
}
