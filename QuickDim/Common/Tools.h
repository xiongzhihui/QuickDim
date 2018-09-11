#pragma once
#include <vector>
#include <math.h>
#include "AllHead.h"
#include "MathUtil.h"

#include "shlwapi.h"
#pragma comment(lib,"shlwapi.lib")

bool GetSelection(AcDbObjectIdArray& adoia, CString sPrompt = _T(""));

bool GetObjectIdArray(ads_name anSs, AcDbObjectIdArray& adoiaObjects);

CString GetDwgPath();//��ȡͼ���ļ�λ�� ����ͼ�� ˵��ͼ��

CString GetBlockLibPath();//��ȡͼ�������� ���ù̶����ͼֽ��ַ

CString GetIniPath();//��ȡini�ļ�λ��

CString GetXmlPath();//��ȡXml�ļ�λ��

CString GetFolderPath();//��ñ������ļ���λ��

CString GetDwgLibPath();//��ȡͼֽ���ļ��е�ַ ���4 5 6ͼֽ

CString GetConnectionString();

BOOL FillCombo(CAcUiComboBox &cmbTemp, CString sIniPath, const TCHAR* strFieldName, const TCHAR* strKeyName, CString sSplit = _T(","));

BOOL FillCombo(CAcUiComboBox &cmbTemp, CString sTemp,CString sSplit=_T(","));

BOOL CopeDwgToFolder(CString sSourcePath, CString sExportPath);

BOOL CreatFolder(CString sFolderpath);

double decimalNum(double d, double i);

static AcGeVector3d GetNormalByInVector(const AcGeVector3d &inVector)
{
	double tol = 1.0E-7;
	if (fabs(inVector.x)<tol&&fabs(inVector.y)<tol)
	{
		if (inVector.z>0)
		{
			return AcGeVector3d(-1, 0, 0);
		}
		else
		{
			return AcGeVector3d::kXAxis;
		}
	}
	else
	{
		AcGeVector2d yAxis2d(inVector.x, inVector.y);
		yAxis2d = yAxis2d.rotateBy(CMathUtil::PI()*0.5);
		AcGeVector3d yAxis(yAxis2d.x, yAxis2d.y, 0);
		AcGeVector3d normal = yAxis;
		normal = normal.rotateBy(CMathUtil::PI()*0.5, inVector);
		return normal;
	}
}

static AcGeMatrix3d GetTranslateMatrix(const AcGePoint3d &inPoint, const AcGeVector3d &inVector, const AcGeVector3d &normal)
{
	AcGeVector3d xAxis = inVector;
	xAxis.normalize();
	AcGeVector3d zAxis = normal;
	zAxis.normalize();
	AcGeVector3d yAxis(xAxis.x, xAxis.y, xAxis.z);
	yAxis = yAxis.rotateBy(CMathUtil::PI()*0.5, zAxis);

	AcGeMatrix3d mat = AcGeMatrix3d::alignCoordSys(AcGePoint3d::kOrigin, AcGeVector3d::kXAxis, AcGeVector3d::kYAxis, AcGeVector3d::kZAxis, inPoint, xAxis, yAxis, zAxis);
	return mat;
}