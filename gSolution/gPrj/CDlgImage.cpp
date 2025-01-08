// CDlgImage.cpp: 구현 파일
//

#include "pch.h"
#include "gPrj.h"
#include "afxdialogex.h"
#include "CDlgImage.h"

#include "gPrjDlg.h"
#include "CProcess.h"
#include <thread>
using namespace std;

// CDlgImage 대화 상자

IMPLEMENT_DYNAMIC(CDlgImage, CDialogEx)

CDlgImage::CDlgImage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CDlgImage, pParent)
{
	m_pParent = pParent;
	m_bLButtonDown = false;
}

CDlgImage::~CDlgImage()
{
}

void CDlgImage::ClearImage()
{
	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();
	int nPitch = m_Image.GetPitch();
	unsigned char* fm = (unsigned char*)m_Image.GetBits();

	//1. image
	memset(fm, 0xff, nPitch * nHeight);
}

void CDlgImage::ClearClick()
{
	//2. circle
	m_nCountClick = 0;
}

void CDlgImage::MoveRandom()
{
	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();

	//1. Set Points 
	m_nCountClick = MAX_POINT_CIRCLE;
	for (size_t i = 0; i < m_nCountClick; i++)
	{
		m_ptClickPosition[i].x = rand() % nWidth;
		m_ptClickPosition[i].y = rand() % nHeight;
	}

	//2. Write Point
	WritePoints();
}

void CDlgImage::SetClickPosition(CPoint pt)
{
	do
	{
		if (m_nCountClick >= MAX_POINT_CIRCLE) break;

		//1. Set Point
		m_ptClickPosition[m_nCountClick].x = pt.x;
		m_ptClickPosition[m_nCountClick].y = pt.y;
		m_nCountClick++;
		//2. Write Point
		WritePoints();

		//2. Draw Point
		Invalidate(false);

	} while (false);
}

void CDlgImage::SetClickPosition(CPoint pt, int nCount)
{
	do
	{
		if (nCount >= MAX_POINT_CIRCLE) break;

		//1. Set Point
		m_ptClickPosition[nCount].x = pt.x;
		m_ptClickPosition[nCount].y = pt.y;
		
		//2. Write Point
		WritePoints();

		//2. Draw Point
		ClearImage();
		Invalidate(false);

	} while (false);
}

bool CDlgImage::CheckInCircle(CPoint pt, int* pCount)
{
	bool bReturn = false;

	static int nCountBefore = 0;

	int nFindCount = 0;

	CProcess process;
	int nRadius = ((CgPrjDlg*)m_pParent)->m_nRadiusClickCircle;
	for (size_t i = 0; i < m_nCountClick; i++)
	{
		if (process.IsInCircle(pt, m_ptClickPosition[i], nRadius))
		{
			bReturn = true;
			*pCount = i;
			
			nFindCount++;
		}
	}

	if (nFindCount >= 2) *pCount = nCountBefore;
	else nCountBefore = *pCount;

	return bReturn;
}


void CDlgImage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImage, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_PARENT, &CDlgImage::OnBnClickedButtonParent)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CDlgImage 메시지 처리기
void CDlgImage::OnBnClickedButtonParent()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	static int n = 100;
	CgPrjDlg* pDlg = (CgPrjDlg*)m_pParent;
	pDlg->CallFunc(n++);
}


BOOL CDlgImage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	MoveWindow(0, 0, 640, 480);

	InitImage();

	InitClickPosition();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlgImage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	DrawCircles(DRAW_CIRCLE_GRAY);

	int nThicknessCircle = ((CgPrjDlg*)m_pParent)->m_nCircleThickness;
	DrawCircle3Point(nThicknessCircle, DRAW_CIRCLE_GRAY);

	if (m_Image) {
		m_Image.Draw(dc, 0, 0);
	}

	drawData(&dc);
}

void CDlgImage::InitImage()
{
	int nWidth = 640;
	int nHeight = 480;
	int nBpp = 8;
	m_Image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (size_t i = 0; i < 256; i++) {
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		}
		m_Image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_Image.GetPitch();
	unsigned char* fm = (unsigned char*)m_Image.GetBits();

	memset(fm, 0xff, nPitch * nHeight);
}



void CDlgImage::drawData(CDC* pDC)
{
	CRect rect;
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, COLOR_RED);
	CPen* pOldPen = pDC->SelectObject(&pen);

	for (size_t i = 0; i < m_nDataCount; i++)
	{
		rect.SetRect(m_ptData[i], m_ptData[i]);
		rect.InflateRect(1, 1);
		pDC->Ellipse(rect);		
	}

	pDC->SelectObject(pOldPen);
}

void CDlgImage::InitClickPosition()
{
	for (size_t i = 0; i < MAX_POINT_CIRCLE; i++)
	{
		m_ptClickPosition[i].SetPoint(0, 0);
	}	
	m_nCountClick = 0;
}


void CDlgImage::DrawCircle(CPoint ptCenter, int nRadius, int nGray)
{
	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();
	int nPitch = m_Image.GetPitch();
	unsigned char* fm = (unsigned char*)m_Image.GetBits();

	
	CPoint ptTemp;
	CRect rect(ptCenter.x - nRadius, ptCenter.y - nRadius, ptCenter.x + nRadius, ptCenter.y + nRadius);
	CRect rectImage(0, 0, nWidth, nHeight);
	CProcess process;
	for (size_t y = rect.top; y < rect.bottom; y++)
	{
		for (size_t x = rect.left; x < rect.right; x++)
		{
			ptTemp.SetPoint(x, y);
			if (process.IsInCircle(ptTemp, ptCenter, nRadius))
			{
				POINT pt;
				pt.x = x;
				pt.y = y;
				if (!rectImage.PtInRect(pt)) continue;
				fm[y * nPitch + x] = nGray;
			}
		}
	}
}

void CDlgImage::DrawCircleThickness(CPoint ptCenter, double dRadius, int nThickness, int nGray)
{
	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();
	int nPitch = m_Image.GetPitch();
	unsigned char* fm = (unsigned char*)m_Image.GetBits();

	double dThicknessHalf = nThickness * 0.5;
	double dOffset = dRadius + dThicknessHalf;
	CRect rect(ptCenter.x - dOffset, ptCenter.y - dOffset, ptCenter.x + dOffset, ptCenter.y + dOffset);
	CRect rectImage(0, 0, nWidth, nHeight);
	CProcess process;
	for (int y = rect.top; y < rect.bottom; y++)
	{
		for (int x = rect.left; x < rect.right; x++)
		{
			if (process.IsInCircleThickness(CPoint(x, y), ptCenter, dRadius, nThickness))
			{
				POINT pt;
				pt.x = x;
				pt.y = y;
				if (!rectImage.PtInRect(pt)) continue;

				fm[y * nPitch + x] = nGray;
			}
		}
	}
}

void CDlgImage::DrawCircles(int nGray)
{
	int nRadius = ((CgPrjDlg*)m_pParent)->m_nRadiusClickCircle;
	for (size_t i = 0; i < m_nCountClick; i++)
	{
		DrawCircle(m_ptClickPosition[i], nRadius, nGray);
	}
	
}

void CDlgImage::DrawCircle3Point(int nThickness, int nGray)
{
	if (m_nCountClick < MAX_POINT_CIRCLE) return;

	CProcess process;
	CPointT<double> ptCenter(0, 0);
	double dRadius = 0;
	//bool bReturn = process.GetCircle(m_ptClickPosition[0], m_ptClickPosition[1], m_ptClickPosition[2], &ptCenter, &dRadius);	
	CPointT<double> pt1(m_ptClickPosition[0].x, m_ptClickPosition[0].y);
	CPointT<double> pt2(m_ptClickPosition[1].x, m_ptClickPosition[1].y);
	CPointT<double> pt3(m_ptClickPosition[2].x, m_ptClickPosition[2].y);
	bool bReturn = process.GetCircle(pt1, pt2, pt3, &ptCenter, &dRadius);
	if (!bReturn)
	{
		return;
	}

	DrawCircleThickness(CPoint(ptCenter.x, ptCenter.y), dRadius, nThickness, nGray);
}

void CDlgImage::WritePoints()
{
	for (size_t i = 0; i < m_nCountClick; i++)
	{
		CString strText;
		strText.Format(_T("x:%d,  y:%d"), m_ptClickPosition[i].x, m_ptClickPosition[i].y);
		switch (i)
		{
		case 0:			
			m_pParent->GetDlgItem(IDC_STATIC_CLICK_POS1)->SetWindowTextW(strText);
			break;
		case 1:
			m_pParent->GetDlgItem(IDC_STATIC_CLICK_POS2)->SetWindowTextW(strText);
			break;
		case 2:
			m_pParent->GetDlgItem(IDC_STATIC_CLICK_POS3)->SetWindowTextW(strText);
			break;
		default:
			break;
		}
	}
}


void CDlgImage::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_bLButtonDown = true;
	SetClickPosition(point);

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CDlgImage::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	do
	{
		//1. Check LButtonDown
		if (!m_bLButtonDown) break;

		//2. Check In Circle	
		int nCount;
		if (CheckInCircle(point, &nCount))
		{
			//3. Set Click Position
			SetClickPosition(point, nCount);
		}

	} while (false);
	

	CDialogEx::OnMouseMove(nFlags, point);
}


void CDlgImage::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_bLButtonDown = false;

	CDialogEx::OnLButtonUp(nFlags, point);
}
