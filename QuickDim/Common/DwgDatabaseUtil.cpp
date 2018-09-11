// DwgDatabaseUtil.cpp: implementation of the CDwgDatabaseUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "DwgDatabaseUtil.h"
#include <dbsymtb.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDwgDatabaseUtil::CDwgDatabaseUtil()
{

}

CDwgDatabaseUtil::~CDwgDatabaseUtil()
{

}

AcDbObjectId CDwgDatabaseUtil::PostToModelSpace( AcDbEntity *pEnt, AcDbDatabase *pDb )
{
	// ��������������Ч��
	assert (pEnt);		// ��Ч��assert (pEnt != NULL);
	
	// ��õ�ǰͼ�����ݿ�Ŀ��
	AcDbBlockTable *pBlkTbl = NULL;
	pDb->getBlockTable(pBlkTbl, AcDb::kForRead);
	
	// ���ģ�Ϳռ��Ӧ�Ŀ���¼
	AcDbBlockTableRecord *pBlkTblRcd = NULL;
	pBlkTbl->getAt(ACDB_MODEL_SPACE, pBlkTblRcd, AcDb::kForWrite);
	pBlkTbl->close();
	
	// ��ʵ����ӵ�ģ�Ϳռ�Ŀ���¼
	AcDbObjectId entId;
	Acad::ErrorStatus es = pBlkTblRcd->appendAcDbEntity(entId, pEnt);
	if (es != Acad::eOk)
	{
		pBlkTblRcd->close();
		delete pEnt;	// ���ʧ��ʱ��Ҫdelete
		pEnt = NULL;
		
		return AcDbObjectId::kNull;
	}
	
	// �ر�ģ�Ϳռ����¼��ʵ��
	pBlkTblRcd->close();
	pEnt->close();
	
	return entId;
}

AcDbObjectIdArray CDwgDatabaseUtil::GetAllEntityIds( const TCHAR* layerName, AcDbDatabase *pDb )
{
	AcDbObjectIdArray entIds;		// ����������ʵ�弯��
	bool bFilterLayer = false;			// �Ƿ���Ҫ����ͼ��
	AcDbObjectId layerId;
	// ���ָ��ͼ��Ķ���ID
	if (layerName != NULL)
	{
		AcDbLayerTable *pLayerTbl = NULL;
		acdbHostApplicationServices()->workingDatabase()
			->getSymbolTable(pLayerTbl, AcDb::kForRead);
		if (!pLayerTbl->has(layerName))
		{
			pLayerTbl->close();
			return entIds;
		}
		pLayerTbl->getAt(layerName, layerId);
		pLayerTbl->close();

		bFilterLayer = true;
	}
	
	// ��ÿ��
	AcDbBlockTable *pBlkTbl = NULL;
	pDb->getBlockTable(pBlkTbl, AcDb::kForRead);
	
	// ���ģ�Ϳռ�Ŀ���¼
	AcDbBlockTableRecord *pBlkTblRcd = NULL;
	pBlkTbl->getAt(ACDB_MODEL_SPACE, pBlkTblRcd, AcDb::kForRead);
	pBlkTbl->close();
	
	// ���������������η���ģ�Ϳռ��ÿһ��ʵ��
	AcDbBlockTableRecordIterator *it = NULL;
	pBlkTblRcd->newIterator(it);
	for (it->start(); !it->done(); it->step())
	{
		AcDbEntity *pEnt = NULL;
		Acad::ErrorStatus es = it->getEntity(pEnt, AcDb::kForRead);
		if (es == Acad::eOk)
		{
			if (bFilterLayer)				// ����ͼ��
			{
				if (pEnt->layerId() == layerId)
				{
					entIds.append(pEnt->objectId());
				}				
			}
			else
			{
				entIds.append(pEnt->objectId());
			}
			
			pEnt->close();
		}
		else
		{
			acutPrintf(TEXT("\nCDwgDatabaseUtil::GetAllEntityIds�д�ʵ��ʧ��(�������:%d)."), (int)es);
		}
	}
	delete it;
	pBlkTblRcd->close();
	
	return entIds;
}

AcDbExtents CDwgDatabaseUtil::GetModelSpaceExtent( AcDbDatabase *pDb )
{
	AcDbBlockTable *pBlkTbl = NULL;
	pDb->getBlockTable(pBlkTbl, AcDb::kForRead);
	
	// ���ģ�Ϳռ�Ŀ���¼
	AcDbBlockTableRecord *pBlkTblRcd = NULL;
	pBlkTbl->getAt(ACDB_MODEL_SPACE, pBlkTblRcd, AcDb::kForRead);
	pBlkTbl->close();
	
	AcDbExtents extent;
	Acad::ErrorStatus es = extent.addBlockExt(pBlkTblRcd);
	pBlkTblRcd->close();
	
	// ���ͼ�����ݿⲻ�ǵ�ǰ�Ĺ������ݿ⣬��ʱ��ֱ�ӻ�ȡģ�Ϳռ�ķ�Χ��ʧ��
	if (es != Acad::eOk)
	{
		AcDbObjectIdArray allEnts = GetAllEntityIds(NULL, pDb);
		for (int i = 0; i < allEnts.length(); i++)
		{
			AcDbEntity *pEnt = NULL;
			if (acdbOpenObject(pEnt, allEnts[i], AcDb::kForRead) == Acad::eOk)
			{
				AcDbExtents ext;
				if (pEnt->getGeomExtents(ext) == Acad::eOk)
				{
					extent.addExt(ext);
				}
				
				pEnt->close();
			}
		}
	}
	
	return extent;
}

bool CDwgDatabaseUtil::SetXdata(CString appname, CString value, AcDbEntity *pEnt)
{
	acdbRegApp(appname);
	struct resbuf*rb = acutBuildList(AcDb::kDxfRegAppName, appname, AcDb::kDxfXdAsciiString, value, RTNONE);
	pEnt->setXData(rb);
	acutRelRb(rb);
	return true;
}

bool CDwgDatabaseUtil::getXdata(CString appname, CString &value, AcDbEntity *pEnt)
{
	struct resbuf *pRb = pEnt->xData(appname);
	if (pRb)
	{
		struct resbuf *pTemp = pRb;
		pTemp = pTemp->rbnext;
		while (pTemp)
		{
			if (AcDb::kDxfXdAsciiString == pTemp->restype)
			{
				value = pTemp->resval.rstring;
				acutRelRb(pRb);
				return true;
			}
			pTemp = pTemp->rbnext;
		}
	}
	acutRelRb(pRb);
	return false;
}
