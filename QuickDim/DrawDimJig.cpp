#include "StdAfx.h"
#include "DrawDimJig.h"

CDrawDimJigEntity::CDrawDimJigEntity(AcGePoint3d ptStr, AcDbObjectId idBlockY,AcDbObjectId idBlockZ, CString sTag1, CString sTag2, bool bZytc, double dZg, double dFwj)
{
	CIniFile ini(GetIniPath());
	ini.GetValueOfKey(_T("MAIN"), _T("TEXTSTYLE"), m_sTextStyle);
	ini.GetValueOfKey(_T("MAIN"), _T("TEXTMARK"), m_sTextMark);
	m_ptStr = ptStr;
	m_RefIdY = idBlockY;
	m_RefIdZ = idBlockZ;
	m_sTag1 = sTag1;
	m_sTag2 = sTag2;
	m_bZytc = bZytc;
	m_dFwj = dFwj;
	m_dZg  = dZg;
}

CDrawDimJigEntity::~CDrawDimJigEntity()
{
}

void CDrawDimJigEntity::DrawOrAddSubEnts(AcGiWorldDraw * mode)
{
	AcDbLine *pLine = new AcDbLine(m_ptStr, m_ptEnd);

	bool bYorZ=true;//判断是左还是右 直接用end x值计算true 为右
	if (m_ptEnd.x>=m_ptStr.x)
	{
		bYorZ = true;
	}
	else
	{
		bYorZ = false;
	}

	AcGePoint3d pt1, pt2;
	int iPy = 0;//用于处理文字左偏比例
	if (!bYorZ)
	{
		if (m_sTag1 == m_sTextMark || m_sTag2 == m_sTextMark)
		{
			iPy = 17;
		}
		else
		{
			iPy = 8;
		}
	}
	pt1 = AcGePoint3d(m_ptEnd.x-m_dZg*iPy, m_ptEnd.y + m_dZg / 3, m_ptEnd.z);
	pt2 = AcGePoint3d(m_ptEnd.x-m_dZg*iPy, m_ptEnd.y - m_dZg / 3 * 4, m_ptEnd.z);
	
	pt1.rotateBy(CConvertUtil::AngleToRadian(bYorZ?m_dFwj:-m_dFwj), AcGeVector3d::kZAxis, m_ptEnd);
	pt2.rotateBy(CConvertUtil::AngleToRadian(bYorZ?m_dFwj:-m_dFwj), AcGeVector3d::kZAxis, m_ptEnd);
	
	AcDbText *pText1 = new AcDbText(pt1, m_sTag1, AcDbObjectId::kNull, m_dZg, CConvertUtil::AngleToRadian(bYorZ ? m_dFwj : -m_dFwj));
	AcDbText *pText2 = new AcDbText(pt2, m_sTag2, AcDbObjectId::kNull, m_dZg, CConvertUtil::AngleToRadian(bYorZ ? m_dFwj : -m_dFwj));
// 	if (!bYorZ)
// 	{	
// 		pText1->setHorizontalMode(AcDb::kTextRight);
// 		pText1->setVerticalMode(AcDb::kTextBase);	
//		pText1->setPosition(AcGePoint3d(pt1.x - m_dZg * iPy, pt1.y, pt1.z));	
// 		pText2->setHorizontalMode(AcDb::kTextRight);
// 		pText2->setVerticalMode(AcDb::kTextBase);		
//     	pText2->setPosition(AcGePoint3d(pt2.x - m_dZg * iPy, pt2.y, pt2.z));	
// 	}

	AcDbBlockReference *pRef = new AcDbBlockReference(m_ptEnd,bYorZ?m_RefIdY:m_RefIdZ);
	pRef->setScaleFactors(AcGeScale3d(m_dZg / 2.5, m_dZg / 2.5, m_dZg / 2.5));
	pRef->setRotation(CConvertUtil::AngleToRadian(bYorZ ? m_dFwj : -m_dFwj));

	if (mode!=NULL)
	{
		pRef->worldDraw(mode);
		delete pRef;
		pText1->worldDraw(mode);
		pText2->worldDraw(mode);
		delete pText1;
		delete pText2;
		pLine->worldDraw(mode);
		delete pLine;
	}
	else
	{
		if (m_sTag1==m_sTextMark||m_sTag2==m_sTextMark)
		{
			delete pLine;
			delete pRef;
		    AcDbObjectId idText=CTextStyleUtil::GetAt(m_sTextStyle);
			pText1->setTextStyle(idText);
			pText2->setTextStyle(idText);
			AcDbLeader *pLead = new AcDbLeader();
			pLead->appendVertex(m_ptStr);
			pLead->appendVertex(m_ptEnd);
			AcGePoint3d ptTemp;
			if (bYorZ)
			{
				ptTemp = AcGePoint3d(m_ptEnd.x + m_dZg * 17, m_ptEnd.y, m_ptEnd.z);
			}
			else
			{
				ptTemp = AcGePoint3d(m_ptEnd.x - m_dZg * 17, m_ptEnd.y, m_ptEnd.z);
			}
			ptTemp.rotateBy(CConvertUtil::AngleToRadian(bYorZ ? m_dFwj : -m_dFwj), AcGeVector3d(0, 0, 1), m_ptEnd);
			pLead->appendVertex(ptTemp);
			int iColorIndex;
			if (m_bZytc)
			{
				iColorIndex = 3;
			}
			else
			{
				iColorIndex = 7;
			}
			pText1->setColorIndex(iColorIndex);
			pText2->setColorIndex(iColorIndex);
			pLead->setColorIndex(iColorIndex);
			if (m_bZytc)
			{
				pText1->setLayer(_T("专用图层"));
				pText2->setLayer(_T("专用图层"));
				pLead->setLayer(_T("专用图层"));
			}
			CDwgDatabaseUtil::PostToModelSpace(pLead);
			CDwgDatabaseUtil::PostToModelSpace(pText1);
			CDwgDatabaseUtil::PostToModelSpace(pText2);
		}
		else
		{
			delete pText1;
			delete pText2;
			AcDbObjectId idT = CBlockUtil::InsertBlockRefWithAttribute(bYorZ ? m_RefIdY : m_RefIdZ, m_ptEnd, m_dZg / 2.5, CConvertUtil::AngleToRadian(bYorZ ? m_dFwj : -m_dFwj));
			AcDbBlockReference *pRefT;
			acdbOpenObject(pRefT, idT, AcDb::kForWrite);
			int iColorIndex;
			if (m_bZytc)
			{
				iColorIndex = 3;
			}
			else
			{
				iColorIndex = 7;
			}
			CBlockUtil::SetBlockRefAttribute(pRefT, _T("TAG1"), m_sTag1, iColorIndex, AcDb::kLnWtByBlock, m_dZg);
			CBlockUtil::SetBlockRefAttribute(pRefT, _T("TAG2"), m_sTag2, iColorIndex, AcDb::kLnWtByBlock, m_dZg);
			if (m_bZytc)
			{
				pLine->setLayer(_T("专用图层"));
				pRefT->setLayer(_T("专用图层"));
			}
			pRefT->close();
			CDwgDatabaseUtil::PostToModelSpace(pLine);
		}
		
	}
}

Adesk::Boolean CDrawDimJigEntity::worldDraw(AcGiWorldDraw * mode)
{
	DrawOrAddSubEnts(mode);
	return Adesk::kTrue;
}

void CDrawDimJigEntity::PostToModeSpace()
{
	DrawOrAddSubEnts(NULL);
}

void CDrawDimJigEntity::SetPtEnd(AcGePoint3d ptEnd)
{
	assertWriteEnabled();
	m_ptEnd = ptEnd;
}

CDrawDimJig::CDrawDimJig()
{
}

CDrawDimJig::~CDrawDimJig()
{
}

bool CDrawDimJig::doIt(const AcGePoint3d &ptStart, AcDbObjectId idBlockY,AcDbObjectId idBlockZ, CString sTag1, CString sTag2, bool bZytc, double dZg, double dFwj)
{
	m_pJigEnt = new CDrawDimJigEntity(ptStart, idBlockY,idBlockZ,sTag1,sTag2,bZytc,dZg,dFwj);
	CString sPrompt=TEXT("\n指定下一点:");
	setDispPrompt(sPrompt);
	AcEdJig::DragStatus stat = drag();
	if (stat==kNormal)
	{
		m_pJigEnt->PostToModeSpace();
	}
	else
	{
		delete m_pJigEnt;
		m_pJigEnt = NULL;
		return false;
	}
	delete m_pJigEnt;
	m_pJigEnt = NULL;
	return true;
}

AcEdJig::DragStatus CDrawDimJig::sampler()
{
	setUserInputControls((UserInputControls)(AcEdJig::kAccept3dCoordinates | AcEdJig::kNoNegativeResponseAccepted |AcEdJig::kNullResponseAccepted));
	static AcGePoint3d pointTemp;
	DragStatus stat = acquirePoint(m_curPt);
	if (pointTemp!=m_curPt)
	{
		pointTemp = m_curPt;
	}
	else if (stat ==AcEdJig::kNormal)
	{
		return AcEdJig::kNoChange;
	}
	return stat;
}

Adesk::Boolean CDrawDimJig::update()
{
	m_pJigEnt->SetPtEnd(m_curPt);
	return Adesk::kTrue;
} 

AcDbEntity * CDrawDimJig::entity() const
{
	return m_pJigEnt;
}