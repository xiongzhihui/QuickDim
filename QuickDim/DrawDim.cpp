#include "StdAfx.h"
#include "DrawDim.h"


CDrawDim::CDrawDim()
{
	CIniFile ini(GetIniPath());
	ini.GetValueOfKey(_T("MAIN"), _T("QZ"), m_sQz);
	ini.GetValueOfKey(_T("MAIN"), _T("TC"), m_sTc);
	ini.GetValueOfKey(_T("MAIN"), _T("ZBX"), m_sZbx);
	ini.GetValueOfKey(_T("MAIN"), _T("HH"), m_sHH);
	ini.GetValueOfKey(_T("MAIN"), _T("JD"), m_sJd);
	ini.GetValueOfKey(_T("MAIN"), _T("X"), m_sX);
	ini.GetValueOfKey(_T("MAIN"), _T("Y"), m_sY);
	ini.GetValueOfKey(_T("MAIN"), _T("ZG"), m_sZg);
	ini.GetValueOfKey(_T("MAIN"), _T("FWJ"), m_sFwj);
	ini.GetValueOfKey(_T("MAIN"), _T("XZJ"), m_sXzj);
	ini.GetValueOfKey(_T("MAIN"), _T("BZBL"), m_sBzbl);
	ini.GetValueOfKey(_T("MAIN"), _T("TEXTMARK"), m_sTextMark);

	m_dBzbl = _wtof(m_sBzbl);
	CLayerUtil::Add(_T("专用图层"), 3);
	m_idInsertY = CBlockUtil::CopyBlockDefFromOtherDwg(GetDwgPath(), _T("TAG-Y"));
	m_idInsertZ = CBlockUtil::CopyBlockDefFromOtherDwg(GetDwgPath(), _T("TAG-Z"));
}


CDrawDim::~CDrawDim()
{
}

bool CDrawDim::DrawLine()
{
	AcGePoint3d ptInsert,ptInsertOriginal;
	bool bConverWcs = true;
	if (m_sZbx==_T("当前坐标系"))
	{
		bConverWcs = false;
	}
	bool b = CGetInputUtil::GetPoint(_T("\n选择标注点:"), ptInsert,bConverWcs);
	if (!bConverWcs)
	{
		ptInsertOriginal = CConvertUtil::UcsToWcsPoint(ptInsert);
	}
	else
	{
		ptInsertOriginal = ptInsert;
	}
	
	if (!b)
	{
		return false;
	}
	int iJd; CString sFormat;
	if (m_sJd == _T("0.1"))
	{
		sFormat = _T("%.1f");
		iJd = 1;
	}
	if (m_sJd == _T("0.01"))
	{
		sFormat = _T("%.2f");
		iJd = 2;
	}
	if (m_sJd == _T("0.001"))
	{
		sFormat = _T("%.3f");
		iJd = 3;
	}
	if (m_sJd == _T("0.0001"))
	{
		sFormat = _T("%.4f");
		iJd = 4;
	}
	if (m_sJd == _T("0.00001"))
	{
		sFormat = _T("%.5f");
		iJd = 5;
	}
	if (m_sJd == _T("0.000001"))
	{
		sFormat = _T("%.6f");
		iJd = 6;
	}

	CString sTag1,sTag2,sX,sY;
	double x = decimalNum(ptInsert.x,iJd);
	double y = decimalNum(ptInsert.y,iJd);
	if (m_sZbx==_T("自定义坐标系"))
	{
		double xTemp, yTemp;
		xTemp = _wtof(m_sX);
		yTemp = _wtof(m_sY);
		if (m_sXzj!=_T("0")&&m_sXzj!=_T(""))
		{
			AcGePoint3d ptTemp(xTemp, yTemp, 0);
			AcGeVector3d vecTemp = AcGePoint3d::kOrigin-ptTemp;
			AcGeMatrix3d mat;
 			double dXzj = _wtof(m_sXzj);
 			mat.setToRotation(-CConvertUtil::AngleToRadian(dXzj), AcGeVector3d::kZAxis/*ptTemp*/,AcGePoint3d(0, 0, 0));
			mat.setTranslation(vecTemp.transformBy(mat));
			AcGePoint3d ptRotation = ptInsert.transformBy(mat);
			x = decimalNum(ptRotation.x, iJd);
			y = decimalNum(ptRotation.y, iJd);
		}
		else
		{
			x -= xTemp;
			y -= yTemp;
		}

	}
	if (m_dBzbl<0.000001||m_dBzbl>100000)
	{
		m_dBzbl = 1;
	}
	x = x * m_dBzbl;
	y = y * m_dBzbl;
	sX.Format(sFormat, x);
	sY.Format(sFormat, y);
	if (m_sHH==_T("是"))
	{
		CString sTemp;
		sTemp = sX;
		sX = sY;
		sY = sTemp;
	}
	if (m_sQz==_T("XY"))
	{
		sTag1 = _T("X=") + sX;
		sTag2 = _T("Y=") + sY;
	}
	if (m_sQz == _T("AB"))
	{
		sTag1 = _T("A=") + sX;
		sTag2 = _T("B=") + sY;
	}
	if (m_sQz == _T("NE"))
	{
		sTag1 = _T("N=") + sX;
		sTag2 = _T("E=") + sY;
	}
	if (m_sQz==_T("MASK"))
	{
		sTag1 = m_sTextMark;
		sTag2 = _T("(") + sX + _T(",") + sY + _T(")");
	}
	if (m_sQz == _T("NONE")||m_sQz==_T(""))
	{
		sTag1 =  sX;
		sTag2 =  sY;
	}
// 	if (m_sHH==_T("是"))
// 	{
// 		CString sTemp;
// 		sTemp = sTag1;
// 		sTag1 = sTag2;
// 		sTag2 = sTemp;
// 	}
	bool bZytc;
	if (m_sTc == _T("专用图层"))
	{
		bZytc = true;
	}
	else
	{
		bZytc = false;
	}
	double dZg = _wtof(m_sZg);
	double dFwj = _wtof(m_sFwj);
	CDrawDimJig jig;
	bool bRet = jig.doIt(ptInsertOriginal, m_idInsertY,m_idInsertZ,sTag1,sTag2,bZytc,dZg,dFwj);
	return bRet;
}