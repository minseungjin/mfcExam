#pragma once
#include "afxdialogex.h"

#define MAX_POINT_CIRCLE 3
#define MAX_POINT 100000

#define DRAW_CIRCLE_GRAY		0
// CDlgImage 대화 상자

class CDlgImage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImage)

public:
	CDlgImage(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgImage();


	CImage m_Image;
	int m_nDataCount = 0;
	CPoint m_ptData[MAX_POINT];

	void ClearImage();
	void ClearClick();
	void MoveRandom();
	
private:
	CWnd* m_pParent;
	CPoint m_ptClickPosition[MAX_POINT];
	int m_nCountClick;
	bool m_bLButtonDown;

	void SetClickPosition(CPoint pt);
	void SetClickPosition(CPoint pt, int nCount);
	bool CheckInCircle(CPoint pt, int* pCount);
	void InitClickPosition();
	void DrawCircle(CPoint ptCenter, int nRadius, int nGray = 128);
	void DrawCircleThickness(CPoint ptCenter, double dRadius, int nThickness, int nGray = 128);
	void DrawCircles(int nGray = 128);
	void DrawCircle3Point(int nThickness, int nGray = 128);
	void WritePoints();


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDlgImage };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonParent();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();

private:
	void InitImage();
	void drawData(CDC* pDC);
	
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
