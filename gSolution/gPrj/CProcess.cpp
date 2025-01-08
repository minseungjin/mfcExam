// CProcess.cpp: 구현 파일
//

#include "pch.h"
#include "gPrj.h"
#include "CProcess.h"


#include <cmath>
using namespace std;


// CProcess

CProcess::CProcess()
{
}

CProcess::~CProcess()
{
}

int CProcess::getStarInfo(CImage* pImage, int nTh)
{
	unsigned char* fm = (unsigned char*)pImage->GetBits();
	int nWidth = pImage->GetWidth();
	int nHeight = pImage->GetHeight();
	int nPitch = pImage->GetPitch();

	int nSum = 0;
	for (size_t k = 0; k < nWidth*nHeight; k++)
	{
		if (fm[k] > nTh) nSum++;
	}

	return nSum;
}

int CProcess::getStarInfo(CImage* pImage, int nTh, CRect rect)
{
	unsigned char* fm = (unsigned char*)pImage->GetBits();
	int nWidth = pImage->GetWidth();
	int nHeight = pImage->GetHeight();
	int nPitch = pImage->GetPitch();

	int nSum = 0;
	for (size_t j = rect.top; j < rect.bottom; j++)
	{
		for (size_t i = rect.left; i < rect.right; i++)
		{
			if (fm[j * nPitch + i] > nTh) {
				nSum++;
			}
		}
	}

	return nSum;
}


// CProcess 멤버 함수


bool CProcess::InClickPosition(CPoint point, CPoint* pClickPosition, int nCountClick, int nRadius)
{
	bool bReturn = false;
		
	CPoint ptCircleCenter;
	CRect rect;
	CPoint ptTemp;
	for (size_t k = 0; k < nCountClick; k++)
	{
		ptCircleCenter.SetPoint(pClickPosition[k].x, pClickPosition[k].y);
		rect.SetRect(ptCircleCenter.x - nRadius, ptCircleCenter.y - nRadius, ptCircleCenter.x + nRadius, ptCircleCenter.y + nRadius);
		for (size_t y = rect.top; y < rect.bottom; y++)
		{
			for (size_t x = rect.left; x < rect.right; x++)
			{
				ptTemp.SetPoint(x, y);
				if (IsInCircle(ptTemp, ptCircleCenter, nRadius))
				{
					return true;
				}
			}
		}
	}

	return bReturn;
}

bool CProcess::IsInCircle(CPoint point, CPoint ptCenter, int nRadius)
{
	bool bReturn = false;

	int dx = ptCenter.x - point.x;
	int dy = ptCenter.y - point.y;

	if (nRadius * nRadius >= dx * dx + dy * dy)
	{
		bReturn = true;
	}

	return bReturn;
}

bool CProcess::IsInCircleThickness(CPoint point, CPoint ptCenter, double dRadius, int nThickness)
{
	bool bReturn = false;

	int dx = ptCenter.x - point.x;
	int dy = ptCenter.y - point.y;

	double dThicknessHalf = nThickness / 2;
	int nRadiusInner = dRadius - dThicknessHalf;
	int nRadiusOuter = dRadius + dThicknessHalf;

	if (nRadiusInner * nRadiusInner <= dx * dx + dy * dy
		&& nRadiusOuter * nRadiusOuter >= dx * dx + dy * dy)
	{
		bReturn = true;
	}

	return bReturn;
}

bool CProcess::GetCircle(CPoint pt1, CPoint pt2, CPoint pt3, CPointT<double>* pCenter, double* pRadius)
{
    bool bReturn = false;

    do
    {
        
		double A = pt2.x - pt1.x;
		double B = pt2.y - pt1.y;
		double C = pt3.x - pt1.x;
		double D = pt3.y - pt1.y;
		double E = A * (pt1.x + pt2.x) + B * (pt1.y + pt2.y);
		double F = C * (pt1.x + pt3.x) + D * (pt1.y + pt3.y);
		double G = 2.0 * (A * (pt3.y - pt2.y) - B * (pt3.x - pt2.x));
		if (G == 0)
		{
			pCenter->	x = pt1.x;
			pCenter->y = pt1.y;
			break;
		}

		pCenter->x = (D * E - B * F) / G;
		pCenter->y = (A * F - C * E) / G;

		*pRadius = Distance(*pCenter, CPointT<double>(pt1.x, pt1.y));

		bReturn = true;
    } while (false);

    return bReturn;
}

bool CProcess::GetCircle(CPointT<double> pt1, CPointT<double> pt2, CPointT<double> pt3, CPointT<double>* pCenter, double* pRadius)
{
	bool bReturn = false;

	do
	{

		static CPointT<double> ptCenterBefore;

		double A = pt2.x - pt1.x;
		double B = pt2.y - pt1.y;
		double C = pt3.x - pt1.x;
		double D = pt3.y - pt1.y;
		double E = A * (pt1.x + pt2.x) + B * (pt1.y + pt2.y);
		double F = C * (pt1.x + pt3.x) + D * (pt1.y + pt3.y);
		double G = 2.0 * (A * (pt3.y - pt2.y) - B * (pt3.x - pt2.x));
		if (G == 0)
		{
			pCenter->x = ptCenterBefore.x;
			pCenter->y = ptCenterBefore.y;
			break;
		}

		pCenter->x = (D * E - B * F) / G;
		pCenter->y = (A * F - C * E) / G;

		ptCenterBefore.x = pCenter->x;
		ptCenterBefore.y = pCenter->y;

		*pRadius = Distance(*pCenter, CPointT<double>(pt1.x, pt1.y));

		bReturn = true;
	} while (false);

	return bReturn;
}


double CProcess::Distance(CPointT<double> pt1, CPointT<double> pt2)
{
	return sqrt(pow(pt1.x - pt2.x, 2) + pow(pt1.y - pt2.y, 2));
}


