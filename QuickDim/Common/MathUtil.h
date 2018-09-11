// MathUtil.h: interface for the CMathUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATHUTIL_H__6942F157_F85E_4F55_B188_CB413C7BED7E__INCLUDED_)
#define AFX_MATHUTIL_H__6942F157_F85E_4F55_B188_CB413C7BED7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMathUtil  
{
public:
	CMathUtil();
	virtual ~CMathUtil();

	// ���PI��ֵ
	static double PI();

	// �ж��������Ƿ����
	static bool IsEqual(double a, double b, double tol = 1.0E-7);

	// ��ȡ��������֮��������
	// ע�����֮ǰ��Ӧ��ִ��һ�� srand((unsigned)time(NULL));
	static int GetRand(int minValue, int maxValue);

	// ��һ��������ָ����С��λ��������������
	static double Round(double a, int precision);
	static int Round(double a);
};

#endif // !defined(AFX_MATHUTIL_H__6942F157_F85E_4F55_B188_CB413C7BED7E__INCLUDED_)
