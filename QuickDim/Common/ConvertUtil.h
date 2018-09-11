// ConvertUtil.h: interface for the CConvertUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONVERTUTIL_H__E2F2B2F9_52B8_4A46_A8BE_148DD9645A15__INCLUDED_)
#define AFX_CONVERTUTIL_H__E2F2B2F9_52B8_4A46_A8BE_148DD9645A15__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CConvertUtil  
{
public:
	CConvertUtil();
	virtual ~CConvertUtil();

	// ��ά�����ά��֮���ת��
	static AcGePoint3d ToPoint3d(const AcGePoint2d &point2d, double z = 0);
	static AcGePoint2d ToPoint2d(const AcGePoint3d &point3d);

	// �Ƕ�ת��Ϊ����
	static double AngleToRadian(double angle);
	
	// ����ת�Ƕ�
	static double RadianToAngle(double radian);

	// ת��Ϊ�ַ���
	static CString ToString(int val);
	static CString ToString(double value, int precision = 2);

	// �ַ���ת��Ϊ�ض�������
	static double ToDouble(const TCHAR* str);

	// ��һ�������������ϵ����ת������ʾ����ϵ
	static AcGePoint3d WcsToDcsPoint(const AcGePoint3d &point);

	// ��һ������û�����ϵ����ת������������ϵ
	static AcGePoint3d UcsToWcsPoint(const AcGePoint3d &point);

	// ��һ�������������ϵ����ת�����û�����ϵ
	static AcGePoint3d WcsToUcsPoint(const AcGePoint3d &point);
};

#endif // !defined(AFX_CONVERTUTIL_H__E2F2B2F9_52B8_4A46_A8BE_148DD9645A15__INCLUDED_)
