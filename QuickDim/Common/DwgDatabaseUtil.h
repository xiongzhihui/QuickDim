// DwgDatabaseUtil.h: interface for the CDwgDatabaseUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DWGDATABASEUTIL_H__129CFB33_5499_4344_BA7B_815CB0DE76EF__INCLUDED_)
#define AFX_DWGDATABASEUTIL_H__129CFB33_5499_4344_BA7B_815CB0DE76EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDwgDatabaseUtil  
{
public:
	CDwgDatabaseUtil();
	virtual ~CDwgDatabaseUtil();

	// ��ʵ����ӵ�ģ�Ϳռ�
	static AcDbObjectId PostToModelSpace(AcDbEntity *pEnt, AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase());

	// ���ģ�Ϳռ�����ʵ��ID���飨���Խ�ͼ����Ϊ����������
	static AcDbObjectIdArray GetAllEntityIds(const TCHAR* layerName = NULL, 
		AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase());

	// �������ͼ��ģ�Ϳռ�����ʵ��İ�Χ��
	static AcDbExtents GetModelSpaceExtent(AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase());

	static bool SetXdata(CString appname, CString value, AcDbEntity *pEnt);
	static bool getXdata(CString appname, CString &value, AcDbEntity *pEnt);
};

#endif // !defined(AFX_DWGDATABASEUTIL_H__129CFB33_5499_4344_BA7B_815CB0DE76EF__INCLUDED_)
