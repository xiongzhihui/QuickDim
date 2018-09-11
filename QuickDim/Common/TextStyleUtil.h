// TextStyleUtil.h: interface for the CTextStyleUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTSTYLEUTIL_H__F392A987_01EA_4AD0_BCE3_C39921CAC013__INCLUDED_)
#define AFX_TEXTSTYLEUTIL_H__F392A987_01EA_4AD0_BCE3_C39921CAC013__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>

class CTextStyleUtil  
{
public:
	CTextStyleUtil();
	virtual ~CTextStyleUtil();

	// ���ĳ��������ʽ��ID
	static AcDbObjectId GetAt(const TCHAR* name);

	// ���������ʽ�����б�
	static void GetAll(std::vector<CString> &textStyles);

	// ����һ��������ʽ
	static AcDbObjectId Add(const TCHAR* name, const TCHAR* fontFileName = TEXT("txt.shx"), 
		const TCHAR* bigFontFileName = TEXT("gbcbig.shx"));
};

#endif // !defined(AFX_TEXTSTYLEUTIL_H__F392A987_01EA_4AD0_BCE3_C39921CAC013__INCLUDED_)
