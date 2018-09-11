// BlockUtil.cpp: implementation of the CBlockUtil class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "BlockUtil.h"
#include <dbents.h>
#include "DwgDatabaseUtil.h"
#include <acutmem.h>
#include <IO.H>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBlockUtil::CBlockUtil()
{

}

CBlockUtil::~CBlockUtil()
{

}

// ��������
AcDbObjectId CBlockUtil::InsertBlockRef( AcDbObjectId blkDefId, const AcGePoint3d &insertPoint, double scale, 
										double rotation )
{
	// ����ͼ��Ĳ���㡢��ת�Ƕȡ������ȵ�
	AcDbBlockReference *pBlkRef = new AcDbBlockReference(insertPoint, blkDefId);
	pBlkRef->setRotation(rotation);
	SetScaleFactor(pBlkRef, scale);

	// ���½���ͼ�����ʵ����뵽�½��Ŀ���¼�У���ȡ�ò���ͼ���ʵ��Id�����ڷ���ֵ
	return CDwgDatabaseUtil::PostToModelSpace(pBlkRef);
}

// �޸Ŀ���յĲ������
void CBlockUtil::SetScaleFactor( AcDbBlockReference *pBlkRef, double scale )
{
	assert (pBlkRef);
	
	AcGeScale3d geScale(scale, scale, scale);
	pBlkRef->setScaleFactors(geScale);
}

// ���ָ�����ƵĿ鶨��
AcDbObjectId CBlockUtil::GetBlkDefId( const TCHAR* blkDefName, AcDbDatabase *pDb )
{
	AcDbBlockTable* pBlockTable = NULL;
	Acad::ErrorStatus es = pDb->getBlockTable(pBlockTable, AcDb::kForRead);
	AcDbObjectId blkDefId;
	es = pBlockTable->getAt(blkDefName, blkDefId);
	pBlockTable->close();
	
	if (es == Acad::eOk)
	{
		return blkDefId;
	}
	else
	{
		return AcDbObjectId::kNull;
	}
}

AcDbObjectId CBlockUtil::InsertBlockRefWithAttribute( const AcDbObjectId &blkDefId, const AcGePoint3d &insertPoint, 
													 double scale, double rotation )
{
	// ��������ն���
	AcDbBlockReference *pBlkRef = new AcDbBlockReference(insertPoint, blkDefId);
	SetScaleFactor(pBlkRef, scale);
	pBlkRef->setRotation(rotation);

	// �ж�ָ���Ŀ���¼�Ƿ�������Զ���
	AcDbBlockTableRecord *pBlkDefRcd = NULL;
	if (acdbOpenObject(pBlkDefRcd, pBlkRef->blockTableRecord(), AcDb::kForRead) == Acad::eOk)
	{
		if (pBlkDefRcd->hasAttributeDefinitions())
		{
			// ��������¼�����������ڷ��ʿ鶨���е�����ʵ��
			AcDbBlockTableRecordIterator *pItr = NULL;
			pBlkDefRcd->newIterator(pItr);
			
			for (pItr->start(); !pItr->done(); pItr->step())
			{
				AcDbEntity *pEnt = NULL;
				if (pItr->getEntity(pEnt, AcDb::kForRead) == Acad::eOk)
				{
					// ��������Զ��壬���������������
					AcDbAttributeDefinition *pAttDef = AcDbAttributeDefinition::cast(pEnt);
					if (pAttDef != NULL)
					{
						AppendAttributeToBlkRef(pBlkRef, pAttDef);
					}
					pEnt->close();
				}
			}
			delete pItr;
		}
		
		pBlkDefRcd->close();
	}

	// ���������ӵ�ģ�Ϳռ�
	return CDwgDatabaseUtil::PostToModelSpace(pBlkRef);
}

bool CBlockUtil::SetBlockRefAttribute(AcDbBlockReference *pBlkRef, const TCHAR* tag, const TCHAR* val, int colorindex /*=7*/, AcDb::LineWeight linewidth /*= AcDb::kLnWtByLayer*/,double dHeight/* = 0*/)
{	
	AcDbBlockTableRecord *pBlkDefRcd = NULL;
	bool bRet = true;
	if (acdbOpenObject(pBlkDefRcd, pBlkRef->blockTableRecord(), AcDb::kForRead) == Acad::eOk)
	{
		// �鶨�����Ƿ�����˶�Ӧ������
		if (pBlkDefRcd->hasAttributeDefinitions())
		{
			AcDbBlockTableRecordIterator *pItr = NULL;
			pBlkDefRcd->newIterator(pItr);
			AcDbEntity *pEnt = NULL;
			
			for (pItr->start(); !pItr->done(); pItr->step())
			{
				if (pItr->getEntity(pEnt, AcDb::kForRead) != eOk)
				{
					return false;
				}
				
				// ����Ƿ������Զ���
				AcDbAttributeDefinition *pAttDef = AcDbAttributeDefinition::cast(pEnt);
				if (pAttDef != NULL)
				{
					TCHAR* pszTag = pAttDef->tag();
					CString strTag = pszTag;
					acutDelString(pszTag);
					if (strTag.CompareNoCase(tag) == 0)
					{
						// ��������յ��������ԣ��ж��Ƿ�����˶�Ӧ������
						bool bFound = false;
						AcDbObjectIterator *attIt = pBlkRef->attributeIterator();
						for(attIt->start(); !attIt->done(); attIt->step())
						{
							AcDbAttribute *pAtt = NULL;
							Acad::ErrorStatus es = acdbOpenObject(pAtt, attIt->objectId(), AcDb::kForWrite);
							if (es == Acad::eOk)
							{
								pszTag = pAtt->tag();
								strTag = pszTag;
								acutDelString(pszTag);
								if (strTag.CompareNoCase(tag) == 0)
								{
									pAtt->setTextString(val);
									//��ǰ���޸�����
// 									//2016.8.10�޸��������ÿ����Ե���������
 									pAtt->setColorIndex(colorindex);//������ɫ
									pAtt->setLineWeight(linewidth);//�����߿�
									if (dHeight!=0)//���ø߶� �����Ϊ0������
									{
										pAtt->setHeight(dHeight);
									}									
									bFound = true;
								}
								pAtt->close();
							}
						}
						delete attIt;
						
						// ���û���ҵ��������Ƶ����ԣ����½��������
						if (!bFound)
						{
							AppendAttributeToBlkRef(pBlkRef, pAttDef);
						}
					}										
				}
				pEnt->close();
			}
			delete pItr;
		}
		else
		{
			bRet = false;
		}
		
		pBlkDefRcd->close();
	}	
	
	return bRet;
}

void CBlockUtil::AppendAttributeToBlkRef( AcDbBlockReference * pBlkRef, AcDbAttributeDefinition * pAttDef )
{
	// ����һ���µ����Զ���
	AcDbAttribute *pAtt = new AcDbAttribute();
	// �����Զ��������Զ���Ķ�������
	pAtt->setPropertiesFrom(pBlkRef);
	pAtt->setLayer(pBlkRef->layerId());
	// �������Զ������������
	pAtt->setInvisible(pAttDef->isInvisible());
	pAtt->setPosition(pAttDef->position());
	pAtt->setHeight(pAttDef->height());
	pAtt->setWidthFactor(pAttDef->widthFactor());
	pAtt->setRotation(pAttDef->rotation());
	pAtt->setHorizontalMode(pAttDef->horizontalMode());
	pAtt->setVerticalMode(pAttDef->verticalMode());
	pAtt->setAlignmentPoint(pAttDef->alignmentPoint());
	pAtt->setTextStyle(pAttDef->textStyle());
	pAtt->setAttributeFromBlock(pBlkRef->blockTransform());
	
	// ������Զ����Tag��Prompt��TextString
	TCHAR *pStr = pAttDef->tag();
	pAtt->setTag(pStr);
	acutDelString(pStr);
	pAtt->setFieldLength(pAttDef->fieldLength());
	pAtt->setTextString(pAttDef->textString());
	
	// ������׷�����Զ���
	pBlkRef->appendAttribute(pAtt);
	pAtt->close();
}

bool CBlockUtil::GetAttributeValue( AcDbBlockReference *pBlkRef, const TCHAR* tag, CString &value )
{
	// ��������¼�����Ա�����
	bool bFound = false;
	AcDbObjectIterator *pItr = pBlkRef->attributeIterator();
	if (pItr)
	{
		while (!pItr->done())
		{
			AcDbObjectId attId = pItr->objectId();
			AcDbAttribute *pAtt = NULL;
			if (pBlkRef->openAttribute(pAtt, attId, AcDb::kForRead) == Acad::eOk)
			{
				// ������е�����Tag��Զ�����Ǵ�д��ĸ����˴���Ĳ�����Ҫ���л�ת
				TCHAR *szTag = pAtt->tag();
				CString strTag = tag;
				strTag.MakeUpper();
				if (_tcscmp(strTag, szTag) == 0)
				{
					TCHAR *szValue = pAtt->textString();	
					value = szValue;
					acutDelString(szValue);
					bFound = true;
				}
				acutDelString(szTag);
				
				pAtt->close();
			}			
			
			pItr->step();
		}
		delete pItr;
		
		return bFound;
	}
	else
	{
		return false;
	}
}

void CBlockUtil::IntersectWith( AcDbBlockReference *pBlkRef, AcDbEntity *pEnt, AcGePoint3dArray &intPoints, 
							   bool bIntersectWithText, bool bProjectToXOY, bool bExtendEntArg )
{
	assert(pBlkRef);
	assert(pEnt);
	
	// ��ȡ����ն�Ӧ�ı任����
	AcGeMatrix3d xform = pBlkRef->blockTransform();
	
	AcDbObjectId blkTblId = pBlkRef->blockTableRecord();
	AcDbBlockTableRecord *pBlkTblRcd = NULL;
	if (acdbOpenObject(pBlkTblRcd, blkTblId, AcDb::kForRead) == Acad::eOk)
	{
		// ����¼���������ʿ鶨���е�ÿһ��ʵ��
		AcDbBlockTableRecordIterator *pIt = NULL;
		pBlkTblRcd->newIterator(pIt);
		for (pIt->start(); !pIt->done(); pIt->step())
		{
			AcDbEntity *pSubEnt = NULL;
			if (pIt->getEntity(pSubEnt, AcDb::kForRead) == Acad::eOk)
			{
				// ������������󽻵㣬�жϵ�ǰʵ������ͣ����������־�����ȥ
				if ((!bIntersectWithText) && (pSubEnt->isKindOf(AcDbMText::desc()) || pSubEnt->isKindOf(AcDbMText::desc())))
				{
					pSubEnt->close();
					continue;
				}
				
				// ����һ��ʵ����б任�������޸Ŀ鶨���е���ʵ��
				AcDbEntity *pEntCopy = NULL;
				if (pSubEnt->getTransformedCopy(xform, pEntCopy) == Acad::eOk)
				{
					// �Ƿ��ӳ��󽻵�
					AcDb::Intersect intMode = bExtendEntArg ? AcDb::kExtendArg : AcDb::kOnBothOperands;
					
					if (bProjectToXOY)
					{
						pEntCopy->intersectWith(pEnt, intMode, AcGePlane::kXYPlane, intPoints);
					}
					else
					{
						pEntCopy->intersectWith(pEnt, intMode, intPoints);
					}
					delete pEntCopy;
				}
				
				pSubEnt->close();
			}			
		}
		delete pIt;
		
		pBlkTblRcd->close();
	}
}

AcDbObjectId CBlockUtil::CopyBlockDefFromOtherDwg( const TCHAR* fileName, const TCHAR* blkDefName )
{
	AcDbObjectId blockRefId = AcDbObjectId::kNull;
	//���ڱ���ͼֽ��
	blockRefId=CBlockUtil::GetBlkDefId(blkDefName);
	if (blockRefId!=AcDbObjectId::kNull)
	{
		return blockRefId;
	}

	// ʹ��_SH_DENYNO������ͼ��(ֻ����)�����������û���д���ļ�
	AcDbDatabase* pSourceDwg = new AcDbDatabase(false);	
	Acad::ErrorStatus es = pSourceDwg->readDwgFile(fileName, _SH_DENYNO);
	if (es != Acad::eOk)
	{
		delete pSourceDwg;
		pSourceDwg = NULL;
		
		acutPrintf(TEXT("\n����dwgͼ�δ���, ͼ������: %s"), fileName);
		return blockRefId;
	}
	
	// ���ⲿͼ�����ݿ�Ŀ��Ѱ�Ҹ������ƵĿ���¼
	AcDbBlockTable* pBlkTable = NULL;
	es = pSourceDwg->getBlockTable(pBlkTable, AcDb::kForRead);
	assert (es == Acad::eOk);
	bool bRet = false;
	if (pBlkTable->has(blkDefName))	// ������ָ����ͼ��
	{	
		AcDbObjectId destBlkDefId;		// ָ��ͼ��Ŀ���¼Id
		es = pBlkTable->getAt(blkDefName, destBlkDefId);
		
		// ��ָ����ͼ�������һ����ʱͼ�����ݿ�
		AcDbDatabase* pTempDb = NULL;	// ע�⣺����ǧ����new
		es = pSourceDwg->wblock(pTempDb, destBlkDefId);
		assert (es == Acad::eOk);		
		
		// �Ѹ���ʱͼ�����ݿ���Ϊ����뵽��ǰdwg
		AcDbDatabase* pCurDb = acdbHostApplicationServices()->workingDatabase();
		es = pCurDb->insert(blockRefId, blkDefName, pTempDb);
		assert (es == Acad::eOk);
		delete pTempDb;
		pTempDb = NULL;
	}
	else
	{
		acutPrintf(TEXT("\n������DWG�ļ���, ������ָ�����ƵĿ���¼."));
	}
	pBlkTable->close();
	
	delete pSourceDwg;
	pSourceDwg = NULL;
	
	return blockRefId;
}

AcDbObjectId CBlockUtil::InsertDwgBlockDef( const TCHAR* dwgFileName, const TCHAR* blkName, bool bOverwriteIfExist, 
										   AcDbDatabase *pDb )
{
	// �Ƿ����ָ�����ƵĿ鶨��
	AcDbObjectId blkDefId = GetBlkDefId(blkName, pDb);
	if (blkDefId.isNull() || bOverwriteIfExist)
	{
		if (_taccess(dwgFileName, 0) != -1)
		{
			AcDbDatabase *pBlkDb = new AcDbDatabase(false);
			Acad::ErrorStatus es = pBlkDb->readDwgFile(dwgFileName, _SH_DENYNO);
			if (es == Acad::eOk)
			{
				es = pDb->insert(blkDefId, blkName, pBlkDb);
				if (es != Acad::eOk)
				{
					CString strMsg;
					strMsg.Format(TEXT("CBlockUtil::InsertDwgBlockDef����, insertʧ��:%d."), (int)es);
					AfxMessageBox(strMsg);
				}
			}
			else
			{
				CString strMsg;
				strMsg.Format(TEXT("CBlockUtil::InsertDwgBlockDef����, readDwgFileʧ��:%d."), (int)es);
				AfxMessageBox(strMsg);
			}
			delete pBlkDb;
		}
		else
		{
			AfxMessageBox(TEXT("CBlockUtil::InsertDwgBlockDef����, δ�ҵ�ָ����ͼ���ļ�."));
		}
	}
	
	return blkDefId;
}

void CBlockUtil::InsertAttributeforBlkRef(AcDbBlockReference *pBlkRef)
{
	AcDbBlockTableRecord *pBlkDefRcd = NULL;
	if (acdbOpenObject(pBlkDefRcd, pBlkRef->blockTableRecord(), AcDb::kForRead) == Acad::eOk)
	{
		// �鶨�����Ƿ�����˶�Ӧ������
		if (pBlkDefRcd->hasAttributeDefinitions())
		{
			AcDbBlockTableRecordIterator *pItr = NULL;
			pBlkDefRcd->newIterator(pItr);
			AcDbEntity *pEnt = NULL;

			for (pItr->start(); !pItr->done(); pItr->step())
			{
				pItr->getEntity(pEnt, AcDb::kForRead);

				// ����Ƿ������Զ���
				AcDbAttributeDefinition *pAttDef = AcDbAttributeDefinition::cast(pEnt);
				if (pAttDef != NULL)
				{
					CBlockUtil::AppendAttributeToBlkRef(pBlkRef, pAttDef);
				}
				pEnt->close();
				pEnt = NULL;
			}
			delete pItr;
		}
		pBlkDefRcd->close();
	}
}