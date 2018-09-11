// HelloWorld.cpp : 
//

#include "stdafx.h"
#include "tchar.h"
#include <aced.h>
#include <rxregsvc.h>
#include "zadscodes.h"
#include "arxHeaders.h"

void initApp();
void unloadApp();

void helloWorld();

void initApp()
{ 
	// register a command with the AutoCAD command mechanism
	acedRegCmds->addCommand(_T("HELLOWORLD_COMMANDS"),
							_T("Hello"),
							_T("Hello"),
							ACRX_CMD_TRANSPARENT,
							helloWorld);
}


void unloadApp()
{ 
	acedRegCmds->removeGroup(_T("HELLOWORLD_COMMANDS"));
}


void helloWorld()
{ 
	ads_name ent; 
	ads_point pt; 
	if (acedEntSel(_T("\n选择一个射线："), ent, pt) != RTNORM) 
		return; 
	AcDbObjectId entId; 
	acdbGetObjectId(entId, ent); 
	AcDbEntity *pEnt = NULL; 
	if (Acad::eOk == acdbOpenObject(pEnt,entId,AcDb::kForRead)) 
	{
		AcDbCurve *pCurve=NULL;
		double startpar,endpar;
		double dist;
		if (pEnt->isKindOf(AcDbCurve::desc()))
		{
			pCurve=AcDbCurve::cast(pEnt);
			pCurve->getStartParam(startpar);
			pCurve->getEndParam(endpar);
			double param=(endpar+startpar)/2;
			pCurve->getDistAtParam(param,dist);
			acutPrintf(_T("\n%f"),dist);
		}
		pEnt->close();
	}
}

extern "C" AcRx::AppRetCode
zcrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
	switch (msg)
	{
	case AcRx::kInitAppMsg:
		acrxDynamicLinker->unlockApplication(pkt);
		acrxRegisterAppMDIAware(pkt);
		initApp();
		break;
	case AcRx::kUnloadAppMsg:
		unloadApp();
		break;
	default:
		break;
	}

	return AcRx::kRetOK;
}


