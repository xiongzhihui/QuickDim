// TextUtil.h: interface for the CTextUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTUTIL_H__F0E02D5A_2083_4575_8BFB_F9C7716F9226__INCLUDED_)
#define AFX_TEXTUTIL_H__F0E02D5A_2083_4575_8BFB_F9C7716F9226__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTextUtil  
{
public:
	CTextUtil();
	virtual ~CTextUtil();

	// ������������
	static AcDbObjectId AddText(const AcGePoint3d& ptInsert, 
		const TCHAR* text, AcDbObjectId style = AcDbObjectId::kNull, 
		double height = 2.5, double rotation = 0);

	// ������������
	static AcDbObjectId AddMText(const AcGePoint3d& ptInsert, 
		const TCHAR* text, AcDbObjectId style = AcDbObjectId::kNull, 
		double height = 2.5, double width = 10, AcDb::LineWeight lineweight=AcDb::kLnWtByLayer,int colorindex=7);
};

#endif // !defined(AFX_TEXTUTIL_H__F0E02D5A_2083_4575_8BFB_F9C7716F9226__INCLUDED_)
