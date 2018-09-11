// TextUtil.cpp: implementation of the CTextUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "TextUtil.h"
#include <dbents.h>
#include "DwgDatabaseUtil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTextUtil::CTextUtil()
{

}

CTextUtil::~CTextUtil()
{

}

AcDbObjectId CTextUtil::AddText( const AcGePoint3d& ptInsert, const TCHAR* text, 
								AcDbObjectId style, double height, double rotation )
{
	AcDbText *pText = new AcDbText(ptInsert, text, style, height, rotation);
	//设置颜色等属性
	pText->setColorIndex(3);
	pText->setWidthFactor(0.7);
	
	return CDwgDatabaseUtil::PostToModelSpace(pText);
}

AcDbObjectId CTextUtil::AddMText( const AcGePoint3d& ptInsert, const TCHAR* text, 
	AcDbObjectId style, double height, double width, AcDb::LineWeight lineweight, int colorindex)
{
	AcDbMText *pMText = new AcDbMText();
	
	// 设置多行文字的特性
	pMText->setTextStyle(style);
	pMText->setContents(text);
	pMText->setLocation(ptInsert);
	pMText->setTextHeight(height);
	pMText->setWidth(width);
	pMText->setColorIndex(colorindex);
	//线宽格式 行间距设置
	pMText->setLineWeight(lineweight);
	pMText->setAttachment(AcDbMText::kMiddleLeft);
	pMText->setLineSpacingFactor(0.9);

	
	return CDwgDatabaseUtil::PostToModelSpace(pMText);
}
