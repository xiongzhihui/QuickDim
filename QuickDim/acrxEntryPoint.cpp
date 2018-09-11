//////////////////////////////////////////////////////////////////////////
// 本文件由向导生成
// 

//-----------------------------------------------------------------------------
//----- acrxEntryPoint.cpp
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
#include "QdDlg.h"
#include "Common/AllHead.h"
#include "Common/Tools.h"
#include "DrawDimJig.h"
#include "DrawDim.h"

//-----------------------------------------------------------------------------
#define szRDS _RXST("")

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CQuickDimApp : public AcRxArxApp{

public:
	CQuickDimApp() : AcRxArxApp() {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		// TODO: 如果有其他依赖项，请在这里加载
		
		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
		
		// TODO: 初始化

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		// TODO: 退出

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;

		// TODO: 卸载依赖

		return (retCode) ;
	}

	static void qdCmds_Qd_Dim()
	{
		bool b = true;
		while (b)
		{
			CDrawDim dd;
			b = dd.DrawLine();
		}

	}
	static void qdCmds_Qd_Set()
	{
		CAcModuleResourceOverride rs;
		CQdDlg dlg;
		dlg.DoModal();
	}

	static void qdCmds_Test()
	{
		AcDbLeader *pLead = new AcDbLeader();
		pLead->appendVertex(AcGePoint3d(0, 0, 0));
		pLead->appendVertex(AcGePoint3d(10, 10, 0));
		pLead->appendVertex(AcGePoint3d(20, 10, 0));
		AcDbText *pText = new AcDbText(AcGePoint3d(15, 10, 0), _T("test"));
		AcDbObjectId idText=CDwgDatabaseUtil::PostToModelSpace(pText);
		pLead->attachAnnotation(idText);
		pLead->evaluateLeader();
		CDwgDatabaseUtil::PostToModelSpace(pLead);
	}
	virtual void RegisterServerComponents () {
	}
	
} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CQuickDimApp)
ACED_ARXCOMMAND_ENTRY_AUTO(CQuickDimApp, qdCmds, _Qd_Set, Qd_Set, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CQuickDimApp, qdCmds, _Qd_Dim, Qd_Dim, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CQuickDimApp, qdCmds, _Test, Test, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)