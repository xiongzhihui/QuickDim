#include "StdAfx.h"
#include "Tools.h"



bool GetSelection(AcDbObjectIdArray& adoia, CString sPrompt)
{
	// Check the pickfirst
	adoia.removeAll();
	ads_name anSs;
	if (acedSSGet(_T("I"), NULL, NULL, NULL, anSs) == RTNORM)
	{
		// Get objects
		GetObjectIdArray(anSs, adoia);
		if (adoia.length() > 0)
		{
			// Clear pickfirst
			int ret = acedSSSetFirst(NULL, NULL);
			return true;
		}
	}

	TCHAR*   pcaStringPointers[2];
	TCHAR    caPromptSelecting[2048],
		caPromptRemoving[2048];
	int      iReturn;

	// Intialization. Empty the selectionset. Very important
	ads_ssadd(NULL, NULL, anSs);

	if (!sPrompt.IsEmpty()) {
		// Copy prompt strings to TCHAR array
		_tcscpy(caPromptSelecting, sPrompt);
		_tcscpy(caPromptRemoving, sPrompt);

		// Set the address pointers for in the array to give as parameter
		pcaStringPointers[0] = caPromptSelecting;
		pcaStringPointers[1] = caPromptRemoving;

		// Start selection
		iReturn = acedSSGet(_T(":$"), pcaStringPointers, NULL, NULL, anSs);

		// User pressed escape
		if (iReturn == RTCAN)
			return false;
	}
	else {
		// Start selection
		iReturn = acedSSGet(NULL, NULL, NULL, NULL, anSs);
		// User pressed escape
		if (iReturn == RTCAN)
			return false;
	}

	// Convert anSs to adoia
	GetObjectIdArray(anSs, adoia);

	return true;
}

bool GetObjectIdArray(ads_name anSs, AcDbObjectIdArray& adoiaObjects)
{
	long         lLength = 0L;
	ads_name     anObject;
	AcDbObjectId adoiObject;

	// Empty the idarray
	adoiaObjects.removeAll();

	// Get length of idarray
	ads_sslength(anSs, &lLength);

	// For every objectid
	for (int i = 0; i < lLength; i++) {
		// Get objectid from idarray
		ads_ssname(anSs, i, anObject);

		// Convert objectid to AcDbObjectId
		if (acdbGetObjectId(adoiObject, anObject) != Acad::eOk) {
			return false;
		}

		// Check if AcDbObjectId is valid
		if (!adoiObject.isValid()) {
			return false;
		}

		// Append to objectid array
		adoiaObjects.append(adoiObject);
	}

	return true;
}

CString GetDwgPath()
{
	CString sPath = CAppDirectoryUtil::GetParentDirectory();
	sPath = sPath + _T("\\Support\\template.dwg");
	return sPath;
}

CString GetIniPath()
{
	CString sPath = CAppDirectoryUtil::GetParentDirectory();
	sPath = sPath + _T("\\Support\\Qd.ini");
	return sPath;
}

CString GetXmlPath()
{
	CString sPath = CAppDirectoryUtil::GetParentDirectory();
	sPath = sPath + _T("\\Support\\Xylem.xml");
	return sPath;
}

CString GetFolderPath()
{
	CString sPath = CAppDirectoryUtil::GetParentDirectory();
	sPath = sPath + _T("\\Project");
	return sPath;
}

CString GetDwgLibPath()
{
	CString sPath = CAppDirectoryUtil::GetParentDirectory();
	sPath = sPath + _T("\\Support\\DwgLib");
	return sPath;
}

CString GetBlockLibPath()
{
	CString sPath = CAppDirectoryUtil::GetParentDirectory();
	sPath = sPath + _T("\\Support\\blocklib.dwg");
	return sPath;
}

CString GetConnectionString()
{
	CString mdbFile = CAppDirectoryUtil::GetParentDirectory() + TEXT("\\Support\\Xylem.mdb");
#ifdef _WIN64
	return _T("Provider=Microsoft.ACE.OLEDB.12.0;Data Source=") + mdbFile;
#endif // _WIN64

#ifdef _WIN32
	return _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=") + mdbFile;
#endif // _WIN32

	
}

BOOL FillCombo(CAcUiComboBox &cmbTemp, CString sIniPath, const TCHAR* strFieldName, const TCHAR* strKeyName, CString sSplit/* = _T(",")*/)
{
	CIniFile ini(sIniPath);
	CString sTemp;
	ini.GetValueOfKey(strFieldName, strKeyName, sTemp);
	FillCombo(cmbTemp, sTemp, sSplit);
	return TRUE;
}

BOOL FillCombo(CAcUiComboBox &cmbTemp, CString sTemp,CString sSplit /*= _T(",")*/)
{
	cmbTemp.Clear();
	std::vector<CString> vecStr;
	CStringUtil::Split(sTemp,sSplit, vecStr, false);
	size_t iLen = vecStr.size();
	for (int i = 0; i < iLen;i++)
	{
		CString s = vecStr[i];
		cmbTemp.AddString(s);
	}
	cmbTemp.SetCurSel(0);
	return TRUE;
}

BOOL CopeDwgToFolder(CString sSourcePath, CString sExportPath)
{
	AcDbDatabase *pData = new AcDbDatabase(false);
	//pData->readDwgFile()
	return TRUE;
}

BOOL CreatFolder(CString sFolderpath)
{
	if (!PathIsDirectory(sFolderpath))
	{
		::CreateDirectory(sFolderpath, NULL);
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}

double decimalNum(double d, double i)
{
// 	int iTemp;
// 	if (d>0)
// 	{
// 		iTemp = pow(10, i + 1)*d + 5;
// 	}
// 	else if (d<0)
// 	{
// 		iTemp = pow(10, i + 1)*d - 5;
// 	}
// 	else
// 	{
// 		return 0;
// 	}
// 	int iTemp2 = iTemp / 10;
// 	double dTemp = iTemp2;
// 	double dTemp2 = dTemp / pow(10, i);
// 	return dTemp2;
	double dNum;
	if (d > 0)
	{
		dNum = pow(10, i + 1)*d /*+ 5*/;
	}
	else if (d < 0)
	{
		dNum = pow(10, i + 1)*d /*- 5*/;
	}
	else
	{
		return 0;
	}
	double dTemp3 = dNum / pow(10, i+1);
	
	return dTemp3;
}