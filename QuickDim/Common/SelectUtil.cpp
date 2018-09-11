// SelectUtil.cpp: implementation of the CSelectUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SelectUtil.h"
#include <math.h>
#include "DwgDatabaseUtil.h"
#include "GeRectangleUtil.h"
#include "ConvertUtil.h"
#include <geassign.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSelectUtil::CSelectUtil()
{

}

CSelectUtil::~CSelectUtil()
{

}

void CSelectUtil::GetEntityInRectangle( const AcGePoint2d &firstPoint, const AcGePoint2d &secondPoint, AcDbObjectIdArray &entIds )
{
	// 1.������Ч�Լ��
	// 1.1 �㲻�ܹ���һ��ֱ�߻��غ�
	assert (fabs(firstPoint.x - secondPoint.x) > 1.0E-7 || fabs(firstPoint.y - secondPoint.y) > 1.0E-7);
	
	// 2.����ģ�Ϳռ�������������ʵ��
	AcDbObjectIdArray allEntIds = CDwgDatabaseUtil::GetAllEntityIds();
	for (int i = 0; i < allEntIds.length(); i++)
	{
		// ���ñ��������ÿһ��ʵ��
		AcDbEntity *pEnt = NULL;
		if (acdbOpenObject(pEnt, allEntIds[i], AcDb::kForRead) == Acad::eOk)
		{
			AcDbExtents extent;
			pEnt->getGeomExtents(extent);
			
			// ���ʵ������Χ��͸��������ཻ���ͽ����ʵ����ӵ�������
			AcGePoint2d extMinPoint = CConvertUtil::ToPoint2d(extent.minPoint());
			AcGePoint2d extMaxPoint = CConvertUtil::ToPoint2d(extent.maxPoint());
			if (CGeRectangleUtil::IntersectWithRectangle(extMinPoint, extMaxPoint, firstPoint, secondPoint))
			{
				entIds.append(pEnt->objectId());
			}			
			
			pEnt->close();
		}
	}
}

bool CSelectUtil::PromptSelectEnts( const TCHAR* prompt, struct resbuf *rb, AcDbObjectIdArray &entIds )
{
	entIds.setLogicalLength(0);

	bool bRet = false;
	ads_name sset;
	acutPrintf(prompt);
	int rc = acedSSGet(NULL, NULL, NULL, rb, sset);
	
	if (rc == RTNORM)
	{		
		long length = 0;
		acedSSLength(sset, &length);
		
		for (int i = 0; i < length; i++)
		{
			ads_name ename;
			acedSSName(sset, i, ename);
			
			AcDbObjectId entId;
			acdbGetObjectId(entId, ename);
			entIds.append(entId);
		}
		
		bRet = true;
	}
	
	acedSSFree(sset);
	
	return bRet;
}

bool CSelectUtil::PromptSelectEnts( const TCHAR* prompt, AcRxClass* classDesc, AcDbObjectIdArray &entIds )
{
	std::vector<AcRxClass*> vecClassDesc;
	vecClassDesc.push_back(classDesc);
	
	return PromptSelectEnts(prompt, vecClassDesc, entIds);
}

bool CSelectUtil::PromptSelectEnts( const TCHAR* prompt, const std::vector<AcRxClass*> &classDescs, AcDbObjectIdArray &entIds )
{
	// ��ʼ��
	entIds.setLogicalLength(0);
	
	// ��ʾ�û�ѡ��ʵ��
	ads_name sset;
	int result = 0;
	acutPrintf(prompt);
	result = acedSSGet(NULL, NULL, NULL, NULL, sset);
	
	if (result != RTNORM)
	{
		return false;
	}
	
	// ȡ��ѡ�񼯵ĳ���
	long length = 0;
	acedSSLength(sset, &length);
	
	// ����ѡ��
	Acad::ErrorStatus es;
	AcDbEntity* pEnt = NULL;
	for (long i = 0; i < length; i++)
	{
		ads_name ename;
		acedSSName(sset, i, ename);
		
		AcDbObjectId curEntId;
		es = acdbGetObjectId(curEntId, ename);
		if (es != Acad::eOk)
		{
			continue;
		}
		
		// ��ʵ��
		es = acdbOpenObject(pEnt, curEntId, AcDb::kForRead);
		if (es != Acad::eOk)
		{
			continue;
		}
		
		// �жϵ�ǰʵ���Ƿ���ָ����ʵ������
		for (int j = 0; j < (int)classDescs.size(); j++)
		{
			if (pEnt->isKindOf(classDescs[j]))
			{
				entIds.append(pEnt->objectId());				
				break;
			}
		}
		
		pEnt->close();	// �ر�ʵ��
	}
	acedSSFree(sset);	// �ͷ�ѡ��

	return (entIds.length() > 0);
}

bool CSelectUtil::PromptSelectEntity( const TCHAR* prompt, AcRxClass* classDesc, AcDbEntity *&pEnt, 
									 AcGePoint3d &pickPoint, bool bOpenForWrite /*= true*/ )
{
	std::vector<AcRxClass*> descs;
	descs.push_back(classDesc);

	return PromptSelectEntity(prompt, descs, pEnt, pickPoint, bOpenForWrite);
}

bool CSelectUtil::PromptSelectEntity( const TCHAR* prompt, const std::vector<AcRxClass*> &classDescs, AcDbEntity *&pEnt, 
									 AcGePoint3d &pickPoint, bool bOpenForWrite /*= true*/ )
{
	ads_name ename;
RETRY:
	if (acedEntSel(prompt, ename, asDblArray(pickPoint)) != RTNORM)
	{
		pEnt = NULL;
		return false;
	}
	
	AcDbObjectId entId;
	acdbGetObjectId(entId, ename);
	
	// �ж�ѡ���ʵ���Ƿ���ָ�����͵�ʵ��
	Acad::ErrorStatus es;
	if (bOpenForWrite)
	{
		es = acdbOpenObject(pEnt, entId, AcDb::kForWrite);
	}
	else
	{
		es = acdbOpenObject(pEnt, entId, AcDb::kForRead);
	}
	assert (es == Acad::eOk);
	bool bRet = false;
	for (int i = 0; i < (int)classDescs.size(); i++)
	{
		if (pEnt->isKindOf(classDescs[i]))
		{			
			bRet = true;
			break;
		}
	}
	
	if (bRet)
	{
		return true;
	}
	else
	{
		pEnt->close();
		acutPrintf(TEXT("\nѡ���ʵ�����Ͳ���Ҫ��, ���ٴ�ѡ��..."));
		goto RETRY;
	}
}
