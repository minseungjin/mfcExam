#pragma once


#include "typesT.h"
// CProcess 명령 대상

class CProcess : public CObject
{
public:
	CProcess();
	virtual ~CProcess();

	int getStarInfo(CImage* pImage, int nTh = 100);
	int getStarInfo(CImage* pImage, int nTh, CRect rect);

	//sjmin
	bool InClickPosition(CPoint point, CPoint* pClickPosition, int nCountClick, int nRadius);
	bool IsInCircle(CPoint point, CPoint ptCenter, int nRadius);
	bool IsInCircleThickness(CPoint point, CPoint ptCenter, double dRadius, int nThickness = 4);
	bool GetCircle(CPoint pt1, CPoint pt2, CPoint pt3, CPointT<double>* pCenter, double* pRadius);
	bool GetCircle(CPointT<double> pt1, CPointT<double> pt2, CPointT<double> pt3, CPointT<double>* pCenter, double* pRadius);

	double Distance(CPointT<double> pt1, CPointT<double> pt2);
};