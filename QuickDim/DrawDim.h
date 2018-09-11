#pragma once
#include "Common/AllHead.h"
#include "Common/Tools.h"
#include "DrawDimJig.h"

class CDrawDim
{
public:
	CDrawDim();
	~CDrawDim();
private:
	CString m_sQz;
	CString m_sTc;
	CString m_sZbx;
	AcDbObjectId m_idInsertY;
	AcDbObjectId m_idInsertZ;
	CString m_sHH;
	CString m_sJd;
	CString	m_sX;
	CString m_sY;
	CString m_sZg;
	CString m_sFwj;
	CString m_sXzj;
	CString m_sBzbl;
	double m_dBzbl;
	CString m_sTextMark;
public:
	bool DrawLine();
};

