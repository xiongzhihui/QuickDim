// StringUtil.cpp: implementation of the CStringUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "StringUtil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStringUtil::CStringUtil()
{

}

CStringUtil::~CStringUtil()
{

}

void CStringUtil::Split( const CString &text, const TCHAR* separator, std::vector<CString> &result, bool bAddEmptyItem )
{
	int prev = 0, current = 0;		// �ҵ��ĵ�ǰƥ�����һ��ƥ��
	CString strCopyText = text;
	strCopyText.TrimRight(TEXT(" "));

	// ��һ���Ȳ���Ŀ���ַ�������û�а����ָ���
	if (strCopyText.Find(separator, 0) < 0)
	{
		if (strCopyText.GetLength() > 0)
		{
			result.push_back(strCopyText);
		}
		return;
	}
	
	// ѭ����ȡ�м���ַ�
	int length = strCopyText.GetLength();
	bool bExit = false;
	while (1)
	{
		current = strCopyText.Find(separator, prev);
		if (current == -1)		// �����һ����
		{
			current = length;
			bExit = true;
		}
		
		// ��һ���ָ���֮�������ָ���֮ǰ���ַ���������Ч���ַ���
		CString item = strCopyText.Mid(prev, current - prev);
		if (bAddEmptyItem || item.GetLength() > 0)
		{
			result.push_back(item);
		}
		
		if (bExit)
		{
			break;
		}
		prev = current + _tcslen(separator);
	}
}

CString CStringUtil::Join( const std::vector<CString> &items, const TCHAR* separator )
{
	CString strResult;
	for (int i = 0; i < items.size(); i++)
	{
		strResult += items[i] + separator;
	}

	strResult.TrimRight(separator);

	return strResult;
}
