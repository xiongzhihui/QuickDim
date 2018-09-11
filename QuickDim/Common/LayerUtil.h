// LayerUtil.h: interface for the CLayerUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LAYERUTIL_H__001B5B7F_7ECE_40B0_8303_6E63AEA26C92__INCLUDED_)
#define AFX_LAYERUTIL_H__001B5B7F_7ECE_40B0_8303_6E63AEA26C92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLayerUtil  
{
public:
	CLayerUtil();
	virtual ~CLayerUtil();

	// ������ͼ�㣬���ָ�����Ƶ�ͼ���Ѿ����ڣ��Ͳ��ٴ����µ�ͼ��
	static void Add(const TCHAR* layerName, int colorIndex = 7,AcDb::LineWeight lineweight=AcDb::kLnWtByLwDefault,CString linetype=_T("CONTINUOUS"));

	// ���ͼ��ID
	static AcDbObjectId GetLayerId(const TCHAR* layerName);

	// ����ͼ�����ɫ
	static bool SetColor(const TCHAR* layerName, int colorIndex);

	// �������ͼ����б�
	static void GetLayerList(AcDbObjectIdArray &layers);
};

#endif // !defined(AFX_LAYERUTIL_H__001B5B7F_7ECE_40B0_8303_6E63AEA26C92__INCLUDED_)
