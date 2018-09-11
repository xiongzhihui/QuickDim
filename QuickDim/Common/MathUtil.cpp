// MathUtil.cpp: implementation of the CMathUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "MathUtil.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMathUtil::CMathUtil()
{

}

CMathUtil::~CMathUtil()
{

}

double CMathUtil::PI()
{
	return atan(1.0) * 4;
}

// �ж��������Ƿ����
bool CMathUtil::IsEqual( double a, double b, double tol /*= 1.0E-7*/ )
{
	return (fabs(a - b) < tol);
}

// ��ȡ��������֮��������
// ע�����֮ǰ��Ӧ��ִ��һ�� srand((unsigned)time(NULL));
int CMathUtil::GetRand( int minValue, int maxValue )
{
	assert (maxValue - minValue);
	
	int value = rand();			// ���ɵ������
	int rc = minValue + (int)CMathUtil::Round(((double)value) / RAND_MAX * (maxValue - minValue));
	
	return rc;
}

// ��һ��������ָ����С��λ��������������
double CMathUtil::Round( double a, int precision )
{
	return (floor(a * pow(10.0, precision) + 0.5)) / pow(10.0, precision);
}

// ��һ����������������
int CMathUtil::Round( double a )
{
	return (int)(a + 0.5);
}
