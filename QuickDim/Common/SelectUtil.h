// SelectUtil.h: interface for the CSelectUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SELECTUTIL_H__73F892C8_D07B_4446_97D2_BB31119A85DD__INCLUDED_)
#define AFX_SELECTUTIL_H__73F892C8_D07B_4446_97D2_BB31119A85DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <vector>

class CSelectUtil  
{
public:
	CSelectUtil();
	virtual ~CSelectUtil();

	// ����: ��õ�ǰͼ����λ�ڸ������η�Χ�ڵ�����ʵ�壨��ʵ��İ�Χ������жϣ�
	// ����: const AcGePoint2d & firstPoint, ���εĵ�һ���ǵ�
	// ����: const AcGePoint2d & secondPoint, ���εĵڶ����ǵ�
	// ����: AcDbObjectIdArray & entIds, ����������ʵ������
	// ����ֵ:   void, ��
	//************************************
	static void GetEntityInRectangle(const AcGePoint2d &firstPoint, const AcGePoint2d &secondPoint, AcDbObjectIdArray &entIds);

	// ��ʾ�û�ѡ����ʵ��
	static bool PromptSelectEnts(const TCHAR* prompt, struct resbuf *rb, AcDbObjectIdArray &entIds);
	static bool PromptSelectEnts(const TCHAR* prompt, AcRxClass* classDesc, AcDbObjectIdArray &entIds);
	static bool PromptSelectEnts(const TCHAR* prompt, const std::vector<AcRxClass*> &classDescs, AcDbObjectIdArray &entIds);

	// ��ʾ�û�ѡ��ĳ�����͵�ʵ��
	// ע�⣺�����߱���ر�ʵ��	
	static bool PromptSelectEntity(const TCHAR* prompt, AcRxClass* classDesc, AcDbEntity *&pEnt, AcGePoint3d &pickPoint, 
		bool bOpenForWrite = true);
	static bool PromptSelectEntity(const TCHAR* prompt, const std::vector<AcRxClass*> &classDescs, AcDbEntity *&pEnt, 
		AcGePoint3d &pickPoint, bool bOpenForWrite = true);
};

#endif // !defined(AFX_SELECTUTIL_H__73F892C8_D07B_4446_97D2_BB31119A85DD__INCLUDED_)
