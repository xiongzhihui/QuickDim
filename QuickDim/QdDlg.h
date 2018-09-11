#pragma once
#include "resource.h"
#include "Common/AllHead.h"
#include "Common/Tools.h"

// CQdDlg �Ի���

class CQdDlg : public CAcUiDialog
{
	DECLARE_DYNAMIC(CQdDlg)

public:
	CQdDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CQdDlg();

// �Ի�������
	enum { IDD = IDD_DLG_QD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//ǰ׺
	BOOL m_radioXy;
	BOOL m_radioAb;
	BOOL m_radioNe;
	BOOL m_radioNone;
	BOOL m_radioMask;//Maskͼ��
	//ͼ��
	BOOL m_radioZytc;
	BOOL m_radioDqtc;
	//����ϵ
	BOOL m_radioDq;
	BOOL m_radioSj;
	BOOL m_radioZdy;
	
	CString m_sZg;
	CAcUiComboBox m_cmbJd;
	CString m_sBzbl;
	CString m_sFwj;

	BOOL m_bHH;
	CString m_sX;
	CString m_sY;
	CString m_sXzj;

public:
	void SaveIni();
	void GetIni();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnPickpoint();
	afx_msg void OnBnClickedRadioDq();
	afx_msg void OnBnClickedRadioZdy();
};
