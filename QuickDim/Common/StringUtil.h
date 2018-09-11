// StringUtil.h: interface for the CStringUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRINGUTIL_H__637019B0_219C_47FC_936B_866C88F308FD__INCLUDED_)
#define AFX_STRINGUTIL_H__637019B0_219C_47FC_936B_866C88F308FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>

class CStringUtil  
{
public:
	CStringUtil();
	virtual ~CStringUtil();

	// ��һ���ַ���Ϊ�ָ������ַ������зָ�
	// bAddEmptyItem: �Ƿ���ӿ��ַ���Ԫ��
	static void Split(const CString &text, const TCHAR* separator, std::vector<CString> &result, bool bAddEmptyItem = true);

	// ͨ���ָ����ϲ��ַ�������
	static CString Join(const std::vector<CString> &items, const TCHAR* separator);
};

#endif // !defined(AFX_STRINGUTIL_H__637019B0_219C_47FC_936B_866C88F308FD__INCLUDED_)
