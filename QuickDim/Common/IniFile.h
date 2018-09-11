// IniFile.h: interface for the CIniFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIFILE_H__D508DA87_D947_4FB1_9267_D79016C0BB55__INCLUDED_)
#define AFX_INIFILE_H__D508DA87_D947_4FB1_9267_D79016C0BB55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIniFile  
{
public:
	CIniFile(const TCHAR* fileName);
	virtual ~CIniFile();	
	
	// ָ���ֶ����ͼ������ƣ���ö�Ӧ�ļ�ֵ
	bool GetValueOfKey(const TCHAR* strFieldName, const TCHAR* strKeyName, CString &strValue, int bufferLength = 1000) const;
	bool GetValueOfKey(const TCHAR* strFieldName, const TCHAR* strKeyName, int &nValue) const;	
	bool GetValueOfKey(const TCHAR* strFieldName, const TCHAR* strKeyName, byte &byteValue) const;	
	bool GetValueOfKey( const TCHAR* strFieldName, const TCHAR* strKeyName, bool &bValue ) const;	
	bool GetValueOfKey( const TCHAR* strFieldName, const TCHAR* strKeyName, double &dValue ) const;
	
	// ָ���ֶ����ͼ������ƣ�д���Ӧ�ļ�ֵ
	bool SetValueOfKey(const TCHAR* strFieldName, const TCHAR* strKeyName, const TCHAR* strValue);	
	bool SetValueOfKey(const TCHAR* strFieldName, const TCHAR* strKeyName, int nValue);	
	bool SetValueOfKey(const TCHAR* strFieldName, const TCHAR* strKeyName, byte byteValue);	
	bool SetValueOfKey( const TCHAR* strFieldName, const TCHAR* strKeyName, bool bValue );	
	// decimalPlaces��С����λ��
	bool SetValueOfKey( const TCHAR* strFieldName, const TCHAR* strKeyName, double dValue, int decimalPlaces = 2 );
	
private:
	CString m_strFile;		// INI�ļ��ı���λ��
};

#endif // !defined(AFX_INIFILE_H__D508DA87_D947_4FB1_9267_D79016C0BB55__INCLUDED_)
