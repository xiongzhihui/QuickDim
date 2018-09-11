// GetInputUtil.h: interface for the CGetInputUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GETINPUTUTIL_H__EDED7CA0_9516_44E8_A440_590BBD26C2C8__INCLUDED_)
#define AFX_GETINPUTUTIL_H__EDED7CA0_9516_44E8_A440_590BBD26C2C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGetInputUtil  
{
public:
	CGetInputUtil();
	virtual ~CGetInputUtil();

	// ��ʾ�û�ѡ��һ����(���۵�ǰ�Ƿ���UCS�й�����ֱ�ӷ��ظõ��WCS����)
	// basePoint: ����WCS�ĵ�����
	// ����ֵ����acedGetPoint������ͬ
	static int GetPointReturnCode(const AcGePoint3d &basePoint, const TCHAR* prompt, AcGePoint3d &point);
	static bool GetPoint(const AcGePoint3d &basePoint, const TCHAR* prompt, AcGePoint3d &point);
	static int GetPointReturnCode(const TCHAR* prompt, AcGePoint3d &point);
	static bool GetPoint(const TCHAR* prompt, AcGePoint3d &point);

	static int GetPointReturnCode(const TCHAR* prompt, AcGePoint3d &point,bool CONVERWCS);
	static bool GetPoint(const TCHAR* prompt, AcGePoint3d &point, bool CONVERWCS);

	// ��ʾ�û�����ĳ���ؼ��ֶ�Ӧ��ѡ��
	// firstDefault: ����Ĭ��ֵ��ʾ���ݣ�����"��(Y)]"���������NULL��ʾ��ʹ��Ĭ��ֵ
	// defaultKeyIndex: Ĭ��ѡ�������
	static bool GetKeyword(const TCHAR* prompt, const TCHAR* keywords, const TCHAR* firstDefault, int defaultKeyIndex, int &nRet);

	// ��ʾ�û�����ʵ��
	// prompt:��ʾ����
	// defaultVal:Ĭ��ֵ
	// precision:Ĭ��ֵ��ʾʱС��������λ��
	// ret:ʵ�ʷ���ֵ
	// ���� CGetInputUtil::GetReal(TEXT("\n������ֵ"), 5, 0, newVal);
	static bool GetReal(const TCHAR* prompt, double defaultVal, int precision, double &ret);
};

#endif // !defined(AFX_GETINPUTUTIL_H__EDED7CA0_9516_44E8_A440_590BBD26C2C8__INCLUDED_)
