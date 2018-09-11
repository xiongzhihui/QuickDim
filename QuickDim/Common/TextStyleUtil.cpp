// TextStyleUtil.cpp: implementation of the CTextStyleUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "TextStyleUtil.h"
#include <dbsymtb.h>
#include <acutmem.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTextStyleUtil::CTextStyleUtil()
{

}

CTextStyleUtil::~CTextStyleUtil()
{

}

AcDbObjectId CTextStyleUtil::GetAt( const TCHAR* name )
{
	AcDbObjectId textStyleId;

	if (_tcslen(name) > 0)
	{
		AcDbTextStyleTable* pTextStyleTable = NULL;
		acdbHostApplicationServices()->workingDatabase()->getSymbolTable(pTextStyleTable, AcDb::kForRead);
		pTextStyleTable->getAt(name, textStyleId);	// ��������ڣ�textStyleId���ᱻ��ֵ
		pTextStyleTable->close();
	}

	return textStyleId;
}

void CTextStyleUtil::GetAll( std::vector<CString> &textStyles )
{
	textStyles.clear();
	
	AcDbTextStyleTable *pTextStyleTbl = NULL;
	acdbHostApplicationServices()->workingDatabase()->getSymbolTable(pTextStyleTbl, AcDb::kForRead);
	AcDbTextStyleTableIterator *pIt = NULL;
	pTextStyleTbl->newIterator(pIt);
	
	for (; !pIt->done(); pIt->step())
	{
		AcDbTextStyleTableRecord *pRcd = NULL;
		if (pIt->getRecord(pRcd, AcDb::kForRead) == Acad::eOk)
		{
			TCHAR *szName = NULL;
			pRcd->getName(szName);
			if (_tcslen(szName) > 0)		// ���˵�����Ϊ�յ�������ʽ
			{
				textStyles.push_back(szName);
			}
			acutDelString(szName);
			
			pRcd->close();
		}
	}
	delete pIt;
	pTextStyleTbl->close();
}

AcDbObjectId CTextStyleUtil::Add( const TCHAR* name, const TCHAR* fontFileName, const TCHAR* bigFontFileName )
{
	Acad::ErrorStatus es;
    AcDbTextStyleTable* pTextStyleTable = NULL;
    es = acdbHostApplicationServices()->workingDatabase()->getSymbolTable(pTextStyleTable, AcDb::kForWrite);    
	
    AcDbTextStyleTableRecord* pTextStyleRecord = new AcDbTextStyleTableRecord();	
	es = pTextStyleRecord->setName(name);
	es = pTextStyleRecord->setBigFontFileName(bigFontFileName);		// �������ļ�
	es = pTextStyleRecord->setFileName(fontFileName);	// �����ļ�
	es = pTextStyleRecord->setXScale(1.0);		// ���ָ߿�ȣ�һ�����ﶼ����Ϊ1�������������о����߿�ȣ�
    es = pTextStyleTable->add(pTextStyleRecord);
	AcDbObjectId styleId = pTextStyleRecord->objectId();	
    pTextStyleTable->close();
    pTextStyleRecord->close();
	
    return styleId;
}
