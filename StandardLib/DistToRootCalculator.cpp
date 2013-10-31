#include "BaseLib/Logger.h"
#include "BaseLib/LogString.h"
#include "BaseObject.h"
#include "DistToRootCalculator.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CDistToRootCalculator::Init(void)
{
	mpcFromChanged = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CDistToRootCalculator::Kill(void)
{
	mpcFromChanged = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CDistToRootCalculator::Calculate(void)
{
	CDistCalculatorParameters	cDistParameters;

	cDistParameters.Init();

	Calculate(&cDistParameters);

	cDistParameters.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CDistToRootCalculator::Calculate(CDistCalculatorParameters* pcParameters)
{
	CollectStartingObjectsAndSetClearedToRoot(pcParameters);

	UpdateAttachedAndDetachedDistToRoot(pcParameters);

	ClearTouchedFlagsAndDetach(pcParameters);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CDistToRootCalculator::ClearTouchedFlagsAndDetach(CDistCalculatorParameters* pcParameters)
{
	int				i;
	int				iNumTouched;
	CBaseObject*	pcBaseObject;

	iNumTouched = pcParameters->NumTouched();

	for (i = 0; i < iNumTouched; i++)
	{
		pcBaseObject = pcParameters->GetTouched(i);
		pcBaseObject->ClearDistTouchedFlags();
		if (pcBaseObject->GetDistToRoot() == CLEARED_DIST_TO_ROOT)
		{
			pcBaseObject->SetDistToRoot(UNATTACHED_DIST_TO_ROOT);
		}
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CDistToRootCalculator::CollectStartingObjectsAndSetClearedToRoot(CDistCalculatorParameters* pcParameters)
{
	//Check if the "FromChanged" object has any froms pointing to it that can still find the Root object.
	//If they can add those froms pointing to it objects to an array of objects to start from (macExpectedDists).
	//
	//Also check if the "FromChanged" object has any froms pointing to it that can still find the stack.
	//If they can add those froms pointing to it objects to an array of objects to start from (mapcUnattched).
	//
	//This method also has side effect of setting the objects dist to root to CLEARED_DIST_TO_ROOT.
	mpcFromChanged->CollectStartingObjectsAndSetClearedToRoot(NULL, pcParameters);

	ValidateStartingObject(mpcFromChanged, pcParameters);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CDistToRootCalculator::ValidateStartingObject(CBaseObject* pcObject, CDistCalculatorParameters* pcParameters)
{
	if (!pcParameters->HasStartingObjects())
	{
		if (!(mpcFromChanged->HasStackPointers() || mpcFromChanged->CanFindRoot()))
		{
			CChars	sz;

			sz.Init();
			mpcFromChanged->PrintObject(&sz);
			gcLogger.Error2(__METHOD__, " Could not find any starting objects for ", sz.Text(), NULL);
			sz.Kill();
		}
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CDistToRootCalculator::AddFromChanged(CBaseObject* pcObject)
{
	mpcFromChanged = pcObject;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CDistToRootCalculator::UpdateAttachedTosDistToRoot(CDistCalculatorParameters* pcParameters)
{
	SDistToRoot*	psLowestDistToRoot;
	CBaseObject*	pcObject;

	psLowestDistToRoot = pcParameters->GetLowestExpectedDist();
	while (psLowestDistToRoot)
	{
		pcObject = psLowestDistToRoot->pcObject;
		pcParameters->RemoveExpectedDist(psLowestDistToRoot);
		pcObject->UpdateAttachedTosDistToRoot(pcParameters);

		psLowestDistToRoot = pcParameters->GetLowestExpectedDist();
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CDistToRootCalculator::UpdateAttachedAndDetachedDistToRoot(CDistCalculatorParameters* pcParameters)
{
	CBaseObject**	ppcObject;
	CBaseObject*	pcObject;

	for (;;)
	{
		UpdateAttachedTosDistToRoot(pcParameters);

		ppcObject = pcParameters->GetNextDetachedFromRoot();
		if (ppcObject)
		{
			pcObject = (*ppcObject);
			pcParameters->RemoveDetachedFromRoot(ppcObject);
			pcObject->UpdateTosDetached(pcParameters);
		}
		else
		{
			break;
		}
	} 
}

