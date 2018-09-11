#pragma once
#include "Common/AllHead.h"
#include "Common/Tools.h"

class CDrawDimJigEntity:public AcDbEntity
{
public:
	CDrawDimJigEntity(AcGePoint3d ptStr,AcDbObjectId idBlockY,AcDbObjectId idBlockZ,CString sTag1,CString sTag2,bool bZytc,double dZg,double dFwj);
	virtual~CDrawDimJigEntity();
	virtual Adesk::Boolean worldDraw(AcGiWorldDraw * mode);
	void PostToModeSpace();
	void SetPtEnd(AcGePoint3d ptEnd);
private:
	void DrawOrAddSubEnts(AcGiWorldDraw * mode);
	AcGePoint3d m_ptStr;
	AcGePoint3d m_ptEnd;
	CString m_sTag1;
	CString m_sTag2;
	double m_dZg;
	double m_dFwj;
	AcDbObjectId m_RefIdY;
	AcDbObjectId m_RefIdZ;
	AcDbLine *m_Line;
	bool m_bZytc;
	CString m_sTextStyle;
	CString m_sTextMark;
};



class CDrawDimJig :public AcEdJig
{
public:
	CDrawDimJig();
	virtual~CDrawDimJig();

	bool doIt(const AcGePoint3d &ptStart,AcDbObjectId idBlockY,AcDbObjectId  idBlockZ,CString sTag1,CString sTag2,bool bZytc,double dZg,double dFwj);
	virtual AcEdJig::DragStatus sampler();
	virtual Adesk::Boolean update();
	virtual AcDbEntity *entity() const;

private: 
	AcGePoint3d m_curPt;
	CDrawDimJigEntity *m_pJigEnt;
};

