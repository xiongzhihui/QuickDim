// GeRectangleUtil.h: interface for the CGeRectangleUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GERECTANGLEUTIL_H__D66803EA_EB61_44C1_9E2E_3E09CB282138__INCLUDED_)
#define AFX_GERECTANGLEUTIL_H__D66803EA_EB61_44C1_9E2E_3E09CB282138__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGeRectangleUtil  
{
public:
	CGeRectangleUtil();
	virtual ~CGeRectangleUtil();

	// ����: �ж����������Ƿ����ཻ�Ĳ���
	// ����: const AcGePoint2d & rect1Point1, ��һ�����εĵ�һ���ǵ�
	// ����: const AcGePoint2d & rect1Point2, ��һ�����εĵڶ����ǵ�
	// ����: const AcGePoint2d & rect2Point1, �ڶ������εĵ�һ���ǵ�
	// ����: const AcGePoint2d & rect2Point2, �ڶ������εĵڶ����ǵ�
	// ����ֵ:   bool, ��������������ཻ�Ĳ��ַ���true�����򷵻�false
	static bool IntersectWithRectangle(const AcGePoint2d &rect1Point1, const AcGePoint2d &rect1Point2, 
		const AcGePoint2d &rect2Point1, const AcGePoint2d &rect2Point2);
};

#endif // !defined(AFX_GERECTANGLEUTIL_H__D66803EA_EB61_44C1_9E2E_3E09CB282138__INCLUDED_)
