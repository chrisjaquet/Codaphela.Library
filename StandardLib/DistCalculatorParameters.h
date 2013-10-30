#ifndef __DIST_TO_ROOT_EFFECTED_FROMS_H__
#define __DIST_TO_ROOT_EFFECTED_FROMS_H__
#include "ObjectPointerArrays.h"


class CBaseObject;


struct SDistToRoot
{
	CBaseObject*	pcObject;
	int				iExpectedDist;
};


typedef CArrayTemplate<SDistToRoot>		CArrayDistToRoot;


class CDistCalculatorParameters
{
private:
	CArrayDistToRoot		macExpectedDists;
	CArrayBaseObjectPtr		mapcUnattched;
	CArrayBaseObjectPtr		mapcLowestFroms;
	CArrayBaseObjectPtr		mapcDetachedFromRoot;
	CArrayBaseObjectPtr		mapcCompletelyDetached;

	CArrayBaseObjectPtr		mapcObjectTouched;

public:
	void					Init(void);
	void					Kill(void);

	void					AddExpectedDist(CBaseObject* pcObject, int iExpectedDist);
	SDistToRoot*			GetLowest(void);
	int						NumExpectedDists(void);
	SDistToRoot*			GetExpectedDist(int iIndex);
	SDistToRoot*			GetExpectedDist(CBaseObject* pcObject);
	void					RemoveExpectedDist(int iIndex);
	void					RemoveExpectedDist(SDistToRoot* psDistToRoot);

	void					AddUnattached(CBaseObject* pcObject);
	CBaseObject*			GetUnattached(void);
	CBaseObject*			GetUnattached(int iIndex);
	BOOL					ContainsUnattached(CBaseObject* pcObject);
	int						NumUnattached(void);
	void					RemoveUnattached(CBaseObject* pcBaseObject);

	void					MarkExpectedDistLowestFroms(void);
	void					MarkUnattachedLowestFroms(void);
	CArrayBaseObjectPtr*	GetLowestFroms(void);
	void					AddChangedFromAsLowest(CBaseObject* pcFromChanged);

	void					AddDetachedFromRoot(CBaseObject* pcObject);
	int						NumDetachedFromRoot(void);
	CBaseObject*			GetDetachedFromRoot(int iIndex);

	void					AddCompletelyDetached(CBaseObject* pcObject);
	int						NumCompletelyDetached(void);
	CBaseObject*			GetCompletelyDetached(int iIndex);
	void					RemoveCompletelyDetached(int iIndex);
	void					CopyRootDetachedToCompletelyDetached(void);
	CArrayBaseObjectPtr*	GetCompletelyDetachedArray(void);

	void					AddTouchedObject(CBaseObject* pcObject);
};


#endif // __DIST_TO_ROOT_CALCULATOR_H__

