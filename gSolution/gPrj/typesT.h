#pragma once


/////////////////////////////////////////////////////////////////////////////
// Classes declared in this file
template <typename T>
class CPointT;

template <typename T>
class CSizeT;

template <typename T>
class CRectT;

/////////////////////////////////////////////////////////////////////////////
// Structs
template <typename T>
struct POINTT
{
	T x;
	T y;
};

template <typename T>
struct SIZET
{
	T cx;
	T cy;
};

template<typename T>
struct RECTT
{
	T left;
	T top;
	T right;
	T bottom;
};


/////////////////////////////////////////////////////////////////////////////
// Classes

template <typename T>
class CSizeT : public SIZET<T>
{
public:
	
	// Constructors
	// construct an uninitialized size
	CSizeT() throw();
	// create from two integers
	CSizeT(_In_ T initCX, _In_ T initCY) throw();
	// create from another size
	CSizeT(_In_ SIZET<T> initSize) throw();
	// create from a point
	CSizeT(_In_ POINTT<T> initPt) throw();
	// create from a DWORD: cx = LOWORD(dw) cy = HIWORD(dw)
	CSizeT(_In_ DWORD dwSize) throw();
	
	// Operations
	BOOL operator==(_In_ SIZET<T> size) const throw();
	BOOL operator!=(_In_ SIZET<T> size) const throw();
	void operator+=(_In_ SIZET<T> size) throw();
	void operator-=(_In_ SIZET<T> size) throw();
	void SetSize(_In_ T CX, _In_ T CY) throw();

	// Operators returning CSize values
	CSizeT<T> operator+(_In_ SIZET<T> size) const throw();
	CSizeT<T> operator-(_In_ SIZET<T> size) const throw();
	CSizeT<T> operator-() const throw();

	// Operators returning CPoint values
	CPointT<T> operator+(_In_ POINTT<T> point) const throw();
	CPointT<T> operator-(_In_ POINTT<T> point) const throw();

	// Operators returning CRect values
	CRectT<T> operator+(_In_ const RECTT<T>* lpRect) const throw();
	CRectT<T> operator-(_In_ const RECTT<T>* lpRect) const throw();
};


template<typename T>
inline CSizeT<T>::CSizeT() throw()
{
	CSizeT<T>::cx = 0;
	CSizeT<T>::cy = 0;
}

template<typename T>
inline CSizeT<T>::CSizeT(_In_ T initCX, _In_ T initCY) throw()
{
	CSizeT<T>::cx = initCX;
	CSizeT<T>::cy = initCY;
}

template<typename T>
inline CSizeT<T>::CSizeT(_In_ SIZET<T> initSize) throw()
{
	CSizeT<T>::cx = initSize.cx;
	CSizeT<T>::cy = initSize.cy;
}

template<typename T>
inline CSizeT<T>::CSizeT(_In_ POINTT<T> initPt) throw()
{
	CSizeT<T>::cx = initPt.x;
	CSizeT<T>::cy = initPt.y;
}

template<typename T>
inline CSizeT<T>::CSizeT(_In_ DWORD dwSize) throw()
{
	CSizeT<T>::cx = LOWORD(dwSize);
	CSizeT<T>::cy = HIWORD(dwSize);
}


template<typename T>
inline BOOL CSizeT<T>::operator==(_In_ SIZET<T> size) const throw()
{
	return (CSizeT<T>::cx == size.cx && CSizeT<T>::cy == size.cy);
}

template<typename T>
inline BOOL CSizeT<T>::operator!=(_In_ SIZET<T> size) const throw()
{
	return (CSizeT<T>::cx != size.cx || CSizeT<T>::cy != size.cy);
}

template<typename T>
inline void CSizeT<T>::operator+=(_In_ SIZET<T> size) throw()
{
	CSizeT<T>::cx += size.cx;
	CSizeT<T>::cy += size.cy;
}

template<typename T>
inline void CSizeT<T>::operator-=(_In_ SIZET<T> size) throw()
{
	CSizeT<T>::cx -= size.cx;
	CSizeT<T>::cy -= size.cy;
}

template<typename T>
inline void CSizeT<T>::SetSize(
	_In_ T CX,
	_In_ T CY) throw()
{
	CSizeT<T>::cx = CX;
	CSizeT<T>::cy = CY;
}

template<typename T>
inline CSizeT<T> CSizeT<T>::operator+(_In_ SIZET<T> size) const throw()
{
	return CSizeT(CSizeT<T>::cx + size.cx, CSizeT<T>::cy + size.cy);
}

template<typename T>
inline CSizeT<T> CSizeT<T>::operator-(_In_ SIZET<T> size) const throw()
{
	return CSizeT(CSizeT<T>::cx - size.cx, CSizeT<T>::cy - size.cy);
}

template<typename T>
inline CSizeT<T> CSizeT<T>::operator-() const throw()
{
	return CSizeT(-CSizeT<T>::cx, -CSizeT<T>::cy);
}

template<typename T>
inline CPointT<T> CSizeT<T>::operator+(_In_ POINTT<T> point) const throw()
{
	return CPointT(CSizeT<T>::cx + point.x, CSizeT<T>::cy + point.y);
}

template<typename T>
inline CPointT<T> CSizeT<T>::operator-(_In_ POINTT<T> point) const throw()
{
	return CPointT(CSizeT<T>::cx - point.x, CSizeT<T>::cy - point.y);
}

template<typename T>
inline CRectT<T> CSizeT<T>::operator+(_In_ const RECTT<T>* lpRect) const throw()
{
	return CRectT(lpRect) + *this;
}

template<typename T>
inline CRectT<T> CSizeT<T>::operator-(_In_ const RECTT<T>* lpRect) const throw()
{
	return CRectT(lpRect) - *this;
}






template <typename T>
class CPointT : public POINTT<T>
{

public:
	// Constructors

	// create an uninitialized point
	CPointT() throw();
	// create from two integers
	CPointT(_In_ T initX, _In_ T initY) throw();
	// create from another point	
	CPointT(_In_ POINTT<T> initPt) throw();

	// create from a size
	CPointT(_In_ SIZET<T> initSize) throw();
	// create from an LPARAM: x = LOWORD(dw) y = HIWORD(dw)
	CPointT(_In_ LPARAM dwPoint) throw();


	// Operations

	// translate the point
	void Offset(_In_ T xOffset, _In_ T yOffset) throw();
	void Offset(_In_ POINTT<T> point) throw();
	void Offset(_In_ SIZET<T> size) throw();
	void SetPoint(_In_ T X, _In_ T Y) throw();


	BOOL operator==(_In_ POINTT<T> point) const throw();
	BOOL operator!=(_In_ POINTT<T> point) const throw();
	void operator+=(_In_ SIZET<T> size) throw();
	void operator-=(_In_ SIZET<T> size) throw();
	void operator+=(_In_ POINTT<T> point) throw();
	void operator-=(_In_ POINTT<T> point) throw();

	// Operators returning CPointT values
	CPointT<T> operator+(_In_ SIZET<T> size) const throw();
	CPointT<T> operator-(_In_ SIZET<T> size) const throw();
	CPointT<T> operator-() const throw();
	CPointT<T> operator+(_In_ POINTT<T> point) const throw();
	
	// Operators returning CSize values
	CSizeT<T> operator-(_In_ POINTT<T> point) const throw();	

	
	// Operators returning CRect values
	CRectT<T> operator+(_In_ const RECTT<T>* lpRect) const throw();
	CRectT<T> operator-(_In_ const RECTT<T>* lpRect) const throw();
};


template<typename T>
inline CPointT<T>::CPointT() throw()
{
	CPointT<T>::x = 0;
	CPointT<T>::y = 0;
}

template<typename T>
inline CPointT<T>::CPointT(
	_In_ T initX,
	_In_ T initY) throw()
{
	CPointT::x = initX;
	CPointT::y = initY;
}

template<typename T>
inline CPointT<T>::CPointT(_In_ POINTT<T> initPt) throw()
{
	*(POINTT<T>*)this = initPt;
}

template<typename T>
inline CPointT<T>::CPointT(_In_ SIZET<T> initSize) throw()
{
	*(SIZET<T>*)this = initSize;
}

template<typename T>
inline CPointT<T>::CPointT(_In_ LPARAM dwPoint) throw()
{
	CPointT::x = (short)LOWORD(dwPoint);
	CPointT::y = (short)HIWORD(dwPoint);
}

template<typename T>
inline void CPointT<T>::Offset(
	_In_ T xOffset,
	_In_ T yOffset) throw()
{
	CPointT::x += xOffset;
	CPointT::y += yOffset;
}

template<typename T>
inline void CPointT<T>::Offset(_In_ POINTT<T> point) throw()
{
	CPointT::x += point.x;
	CPointT::y += point.y;
}

template<typename T>
inline void CPointT<T>::Offset(_In_ SIZET<T> size) throw()
{
	CPointT::x += size.cx;
	CPointT::y += size.cy;
}

template<typename T>
inline void CPointT<T>::SetPoint(
	_In_ T X,
	_In_ T Y) throw()
{
	CPointT::x = X;
	CPointT::y = Y;
}

template<typename T>
inline BOOL CPointT<T>::operator==(_In_ POINTT<T> point) const throw()
{
	return (CPointT::x == point.x && CPointT::y == point.y);
}

template<typename T>
inline BOOL CPointT<T>::operator!=(_In_ POINTT<T> point) const throw()
{
	return (CPointT::x != point.x || CPointT::y != point.y);
}

template<typename T>
inline void CPointT<T>::operator+=(_In_ SIZET<T> size) throw()
{
	CPointT::x += size.cx;
	CPointT::y += size.cy;
}

template<typename T>
inline void CPointT<T>::operator-=(_In_ SIZET<T> size) throw()
{
	CPointT::x -= size.cx;
	CPointT::y -= size.cy;
}

template<typename T>
inline void CPointT<T>::operator+=(_In_ POINTT<T> point) throw()
{
	CPointT::x += point.x;
	CPointT::y += point.y;
}

template<typename T>
inline void CPointT<T>::operator-=(_In_ POINTT<T> point) throw()
{
	CPointT::x -= point.x;
	CPointT::y -= point.y;
}

template<typename T>
inline CPointT<T> CPointT<T>::operator+(_In_ SIZET<T> size) const throw()
{
	return CPointT(CPointT::x + size.cx, CPointT::y + size.cy);
}

template<typename T>
inline CPointT<T> CPointT<T>::operator-(_In_ SIZET<T> size) const throw()
{
	return CPointT(CPointT::x - size.cx, CPointT::y - size.cy);
}

template<typename T>
inline CPointT<T> CPointT<T>::operator-() const throw()
{
	return CPointT(-CPointT::x, -CPointT::y);
}

template<typename T>
inline CPointT<T> CPointT<T>::operator+(_In_ POINTT<T> point) const throw()
{
	return CPointT(CPointT::x + point.x, CPointT::y + point.y);
}

template<typename T>
inline CSizeT<T> CPointT<T>::operator-(_In_ POINTT<T> point) const throw()
{
	return CSizeT(CPointT::x - point.x, CPointT::y - point.y);
}


template<typename T>
inline CRectT<T> CPointT<T>::operator+(_In_ const RECTT<T>* lpRect) const throw()
{
	return CRectT(lpRect) + *this;
}

template<typename T>
inline CRectT<T> CPointT<T>::operator-(_In_ const RECTT<T>* lpRect) const throw()
{
	return CRectT(lpRect) - *this;
}






template<typename T>
class CRectT :public RECTT<T>
{
	// Constructors
public:
	// uninitialized rectangle
	CRectT() throw();
	// from left, top, right, and bottom
	CRectT(
		_In_ T l,
		_In_ T t,
		_In_ T r,
		_In_ T b) throw();
	// copy constructor
	CRectT(_In_ const RECTT<T>& srcRect) throw();

	// from a pointer to another rect
	CRectT(_In_ RECTT<T>* lpSrcRect) throw();

	void CopyRectT(_Out_ RECTT<T>* pDstRect, _In_ RECTT<T>* pSrcRect) throw();


	// from a point and size
	CRectT(
		_In_ POINTT<T> point,
		_In_ SIZET<T> size) throw();
	// from two points
	CRectT(
		_In_ POINTT<T> topLeft,
		_In_ POINTT<T> bottomRight) throw();

	// Attributes (in addition to RECT members)
	
	// retrieves the width
	int Width() const throw();
	// returns the height
	int Height() const throw();
	// returns the size
	CSizeT<T> SizeT() const throw();
	// reference to the top-left point
	CPointT<T>& TopLeft() throw();
	// reference to the bottom-right point
	CPointT<T>& BottomRight() throw();
	// const reference to the top-left point
	const CPointT<T>& TopLeft() const throw();
	// const reference to the bottom-right point
	const CPointT<T>& BottomRight() const throw();
	// the geometric center point of the rectangle
	CPointT<T> CenterPoint() const throw();
	// swap the left and right
	void SwapLeftRight() throw();
	static void WINAPI SwapLeftRight(_Inout_ RECTT<T>* pRect) throw();

	// convert between CRect and LPRECT/LPCRECT (no need for &)
	/*operator LPRECT() throw();
	operator LPCRECT() const throw();*/

	// returns TRUE if rectangle has no area
	BOOL IsRectEmpty() const throw();
	// returns TRUE if rectangle is at (0,0) and has no area
	BOOL IsRectNull() const throw();
	// returns TRUE if point is within rectangle
	BOOL PtInRect(_In_ POINTT<T> point) const throw();

	// Operations

	// set rectangle from left, top, right, and bottom
	void SetRect(
		_In_ T x1,
		_In_ T y1,
		_In_ T x2,
		_In_ T y2) throw();
	void SetRect(
		_In_ POINTT<T> topLeft,
		_In_ POINTT<T> bottomRight) throw();
	// empty the rectangle
	void SetRectEmpty() throw();
	// copy from another rectangle
	void CopyRectT(_In_ RECTT<T>* lpSrcRect) throw();


	// TRUE if exactly the same as another rectangle
	BOOL EqualRect(_In_ RECTT<T>* lpRect) const throw();

	// Inflate rectangle's width and height by
	// x units to the left and right ends of the rectangle
	// and y units to the top and bottom.
	void InflateRect(
		_In_ T x,
		_In_ T y) throw();
	// Inflate rectangle's width and height by
	// size.cx units to the left and right ends of the rectangle
	// and size.cy units to the top and bottom.
	void InflateRect(_In_ SIZET<T> size) throw();
	// Inflate rectangle's width and height by moving individual sides.
	// Left side is moved to the left, right side is moved to the right,
	// top is moved up and bottom is moved down.
	void InflateRect(_In_ RECTT<T>* lpRect) throw();
	void InflateRect(
		_In_ T l,
		_In_ T t,
		_In_ T r,
		_In_ T b) throw();

	// deflate the rectangle's width and height without
	// moving its top or left
	void DeflateRect(
		_In_ T x,
		_In_ T y) throw();
	void DeflateRect(_In_ SIZET<T> size) throw();
	void DeflateRect(_In_ RECTT<T>* lpRect) throw();
	void DeflateRect(
		_In_ T l,
		_In_ T t,
		_In_ T r,
		_In_ T b) throw();

	// translate the rectangle by moving its top and left
	void OffsetRect(
		_In_ T x,
		_In_ T y) throw();
	void OffsetRect(_In_ SIZET<T> size) throw();
	void OffsetRect(_In_ POINTT<T> point) throw();
	void NormalizeRect() throw();

	// absolute position of rectangle
	void MoveToY(_In_ T y) throw();
	void MoveToX(_In_ T x) throw();
	void MoveToXY(
		_In_ T x,
		_In_ T y) throw();
	void MoveToXY(_In_ POINTT<T> point) throw();

	// set this rectangle to intersection of two others
	BOOL IntersectRect(
		_In_ RECTT<T>* lpRect1,
		_In_ RECTT<T>* lpRect2) throw();

	// set this rectangle to bounding union of two others
	BOOL UnionRect(
		_In_ RECTT<T>* lpRect1,
		_In_ RECTT<T>* lpRect2) throw();

	// set this rectangle to minimum of two others
	BOOL SubtractRect(
		_In_ RECTT<T>* lpRectSrc1,
		_In_ RECTT<T>* lpRectSrc2) throw();

	// Additional Operations
	void operator=(_In_ const RECTT<T>& srcRect) throw();
	BOOL operator==(_In_ const RECTT<T>& rect) const throw();
	BOOL operator!=(_In_ const RECTT<T>& rect) const throw();
	void operator+=(_In_ POINTT<T> point) throw();
	void operator+=(_In_ SIZET<T> size) throw();
	void operator+=(_In_ RECTT<T>* lpRect) throw();
	void operator-=(_In_ POINTT<T> point) throw();
	void operator-=(_In_ SIZET<T> size) throw();
	void operator-=(_In_ RECTT<T>* lpRect) throw();
	void operator&=(_In_ const RECTT<T>& rect) throw();
	void operator|=(_In_ const RECTT<T>& rect) throw();

	// Operators returning CRect values
	CRectT<T> operator+(_In_ POINTT<T> point) const throw();
	CRectT<T> operator-(_In_ POINTT<T> point) const throw();
	CRectT<T> operator+(_In_ RECTT<T>* lpRect) const throw();
	CRectT<T> operator+(_In_ SIZET<T> size) const throw();
	CRectT<T> operator-(_In_ SIZET<T> size) const throw();
	CRectT<T> operator-(_In_ RECTT<T>* lpRect) const throw();
	CRectT<T> operator&(_In_ const RECTT<T>& rect2) const throw();
	 
	CRectT<T> operator|(_In_ const RECTT<T>& rect2) const throw();
	CRectT<T> MulDiv(
		_In_ int nMultiplier,
		_In_ int nDivisor) const throw();
};


// CRect
template<typename T>
inline CRectT<T>::CRectT() throw()
{
	CRectT<T>::left = 0;
	CRectT<T>::top = 0;
	CRectT<T>::right = 0;
	CRectT<T>::bottom = 0;
}

template<typename T>
inline CRectT<T>::CRectT(
	_In_ T l,
	_In_ T t,
	_In_ T r,
	_In_ T b) throw()
{
	CRectT<T>::left = l;
	CRectT<T>::top = t;
	CRectT<T>::right = r;
	CRectT<T>::bottom = b;
}

template<typename T>
inline CRectT<T>::CRectT(_In_ const RECTT<T>& srcRect) throw()
{
	::CopyRectT(this, &srcRect);
}

template<typename T>
inline CRectT<T>::CRectT(_In_ RECTT<T>* pSrcRect) throw()
{
	::CopyRectT(this, pSrcRect);
}

template<typename T>
inline void CRectT<T>::CopyRectT(_Out_ RECTT<T>* pDstRect, _In_ RECTT<T>* pSrcRect)
{
	memcpy(pDstRect, pSrcRect, sizeof(RECTT));
}

template<typename T>
inline CRectT<T>::CRectT(
	_In_ POINTT<T> point,
	_In_ SIZET<T> size) throw()
{
	CRectT<T>::right = (CRectT<T>::left = point.x) + size.cx;
	CRectT<T>::bottom = (CRectT<T>::top = point.y) + size.cy;
}

template<typename T>
inline CRectT<T>::CRectT(
	_In_ POINTT<T> topLeft,
	_In_ POINTT<T> bottomRight) throw()
{
	CRectT<T>::left = topLeft.x;
	CRectT<T>::top = topLeft.y;
	CRectT<T>::right = bottomRight.x;
	CRectT<T>::bottom = bottomRight.y;
}

template<typename T>
inline int CRectT<T>::Width() const throw()
{
	return CRectT<T>::right - CRectT<T>::left;
}

template<typename T>
inline int CRectT<T>::Height() const throw()
{
	return CRectT<T>::bottom - CRectT<T>::top;
}

template<typename T>
inline CSizeT<T> CRectT<T>::SizeT() const throw()
{
	return CSizeT(CRectT<T>::right - CRectT<T>::left, CRectT<T>::bottom - CRectT<T>::top);
}


template<typename T>
inline CPointT<T>& CRectT<T>::TopLeft() throw()
{
	return *((CPointT<T>*)this);
}

template<typename T>
inline CPointT<T>& CRectT<T>::BottomRight() throw()
{
	return *((CPointT<T>*)this + 1);
}

template<typename T>
inline const CPointT<T>& CRectT<T>::TopLeft() const throw()
{
	return *((CPointT<T>*)this);
}

template<typename T>
inline const CPointT<T>& CRectT<T>::BottomRight() const throw()
{
	return *((CPointT<T>*)this + 1);
}

template<typename T>
inline CPointT<T> CRectT<T>::CenterPoint() const throw()
{
	return CPointT((CRectT<T>::left + CRectT<T>::right) / 2, (CRectT<T>::top + CRectT<T>::bottom) / 2);
}

template<typename T>
inline void CRectT<T>::SwapLeftRight() throw()
{
	SwapLeftRight(&this);
}

template<typename T>
inline void WINAPI CRectT<T>::SwapLeftRight(_Inout_ RECTT<T>* pRect) throw()
{
	T temp = pRect->left;
	pRect->left = pRect->right;
	pRect->right = temp;
}

//template<typename T>
//inline CRectT<T>::operator LPRECT() throw()
//{
//	return this;
//}
//
//template<typename T>
//inline CRectT<T>::operator LPCRECT() const throw()
//{
//	return this;
//}

template<typename T>
inline BOOL CRectT<T>::IsRectEmpty() const throw()
{
	return (CRectT<T>::left == CRectT<T>::right) || (CRectT<T>::top == CRectT<T>::bottom);
}

template<typename T>
inline BOOL CRectT<T>::IsRectNull() const throw()
{
	return (CRectT<T>::left == 0 && CRectT<T>::right == 0 && CRectT<T>::top == 0 && CRectT<T>::bottom == 0);
}

template<typename T>
inline BOOL CRectT<T>::PtInRect(_In_ POINTT<T> point) const throw()
{
	return (point.x >= CRectT<T>::left && point.x <= CRectT<T>::right && point.y >= CRectT<T>::top && point.y <= CRectT<T>::bottom);
}

template<typename T>
inline void CRectT<T>::SetRect(
	_In_ T x1,
	_In_ T y1,
	_In_ T x2,
	_In_ T y2) throw()
{
	CRectT<T>::left = x1;
	CRectT<T>::right = x2;
	CRectT<T>::top = y1;
	CRectT<T>::bottom = y2;
}

template<typename T>
inline void CRectT<T>::SetRect(
	_In_ POINTT<T> topLeft,
	_In_ POINTT<T> bottomRight) throw()
{
	::SetRect(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
}

template<typename T>
inline void CRectT<T>::SetRectEmpty() throw()
{
	memset(this, 0, sizeof(RECTT<T>));
}

template<typename T>
inline void CRectT<T>::CopyRectT(_In_ RECTT<T>* lpSrcRect) throw()
{
	CopyRectT(this, lpSrcRect);
}

template<typename T>
inline BOOL CRectT<T>::EqualRect(_In_ RECTT<T>* lpRect) const throw()
{
	return (memcmp(this, lpRect, sizeof(RECTT)) == 0);
}

template<typename T>
inline void CRectT<T>::InflateRect(
	_In_ T x,
	_In_ T y) throw()
{
	CRectT<T>::left -= x;
	CRectT<T>::top -= y;
	CRectT<T>::right += x;
	CRectT<T>::bottom += y;	
}

template<typename T>
inline void CRectT<T>::InflateRect(_In_ SIZET<T> size) throw()
{
	::InflateRect(this, size.cx, size.cy);
}

template<typename T>
inline void InflateRect(_In_ RECTT<T>* lpRect) throw()
{
	CRectT<T>::left -= lpRect->left;
	CRectT<T>::top -= lpRect->top;
	CRectT<T>::right += lpRect->right;
	CRectT<T>::bottom += lpRect->bottom;
}

template<typename T>
inline void InflateRect(
	_In_ T l,
	_In_ T t,
	_In_ T r,
	_In_ T b) throw()
{
	CRectT<T>::left -= l;
	CRectT<T>::top -= t;
	CRectT<T>::right += r;
	CRectT<T>::bottom += b;
}

template<typename T>
inline void CRectT<T>::DeflateRect(
	_In_ T x,
	_In_ T y) throw()
{
	::InflateRect(this, -x, -y);
}

template<typename T>
inline void CRectT<T>::DeflateRect(_In_ SIZET<T> size) throw()
{
	::InflateRect(this, -size.cx, -size.cy);
}

template<typename T>
inline void CRectT<T>::DeflateRect(_In_ RECTT<T>* lpRect) throw()
{
	CRectT<T>::left += lpRect->left;
	CRectT<T>::top += lpRect->top;
	CRectT<T>::right -= lpRect->right;
	CRectT<T>::bottom -= lpRect->bottom;
}

template<typename T>
inline void CRectT<T>::DeflateRect(
	_In_ T l,
	_In_ T t,
	_In_ T r,
	_In_ T b) throw()
{
	CRectT<T>::left += l;
	CRectT<T>::top += t;
	CRectT<T>::right -= r;
	CRectT<T>::bottom -= b;
}

template<typename T>
inline void CRectT<T>::OffsetRect(
	_In_ T x,
	_In_ T y) throw()
{
	CRectT<T>::left += x;
	CRectT<T>::top += y;
	CRectT<T>::right += x;
	CRectT<T>::bottom += y;
}

template<typename T>
inline void CRectT<T>::OffsetRect(_In_ POINTT<T> point) throw()
{
	::OffsetRect(point.x, point.y);
}

template<typename T>
inline void CRectT<T>::OffsetRect(_In_ SIZET<T> size) throw()
{
	::OffsetRect(size.cx, size.cy);
}

template<typename T>
inline void CRectT<T>::NormalizeRect() throw()
{
	T nTemp;
	if (CRectT<T>::left > CRectT<T>::right)
	{
		nTemp = CRectT<T>::left;
		CRectT<T>::left = CRectT<T>::right;
		CRectT<T>::right = nTemp;
	}
	if (CRectT<T>::top > CRectT<T>::bottom)
	{
		nTemp = CRectT<T>::top;
		CRectT<T>::top = CRectT<T>::bottom;
		CRectT<T>::bottom = nTemp;
	}
}

template<typename T>
inline void CRectT<T>::MoveToY(_In_ T y) throw()
{
	CRectT<T>::bottom = Height() + y;
	CRectT<T>::top = y;
}

template<typename T>
inline void CRectT<T>::MoveToX(_In_ T x) throw()
{
	CRectT<T>::right = Width() + x;
	CRectT<T>::left = x;
}

template<typename T>
inline void CRectT<T>::MoveToXY(
	_In_ T x,
	_In_ T y) throw()
{
	MoveToX(x);
	MoveToY(y);
}

template<typename T>
inline void CRectT<T>::MoveToXY(_In_ POINTT<T> pt) throw()
{
	MoveToX(pt.x);
	MoveToY(pt.y);
}

template<typename T>
inline BOOL CRectT<T>::IntersectRect(
	_In_ RECTT<T>* lpRect1,
	_In_ RECTT<T>* lpRect2) throw()
{
	if (!lpRect1 || !lpRect2) return false;

	bool bIntersect = !(lpRect1->left > lpRect2->right || lpRect1->right < lpRect2->left ||
		lpRect1->top > lpRect2->bottom || lpRect1->bottom < lpRect2->top);

	if (bIntersect)
	{
		CRectT<T>::left = max(lpRect1->left, lpRect2->left);
		CRectT<T>::top = max(lpRect1->top, lpRect2->top);
		CRectT<T>::right = min(lpRect1->right, lpRect2->right);
		CRectT<T>::bottom = min(lpRect1->bottom, lpRect2->bottom);
		return true;
	}

	return false;
}

template<typename T>
inline BOOL CRectT<T>::UnionRect(
	_In_ RECTT<T>* lpRect1,
	_In_ RECTT<T>* lpRect2) throw()
{
	if (!lpRect1 || !lpRect2) return false;

	if (lpRect1->left != lpRect1->right &&
		lpRect1->top != lpRect1->bottom &&
		lpRect2->left != lpRect2->right &&
		lpRect2->top != lpRect2->bottom)
	{
		CRectT<T>::left = min(lpRect1->left, lpRect2->left);
		CRectT<T>::right = max(lpRect1->right, lpRect2->right);
		CRectT<T>::top = min(lpRect1->top, lpRect2->top);
		CRectT<T>::bottom = max(lpRect1->bottom, lpRect2->bottom);
		return true;
	}

	if (lpRect1->left != lpRect1->right &&
		lpRect1->top != lpRect1->bottom)
	{
		CopyRectT(lpRect1);
		return true;
	}

	if (lpRect2->left != lpRect2->right &&
		lpRect2->top != lpRect2->bottom)
	{
		CopyRectT(lpRect2);
		return true;
	}

	return false;
}

template<typename T>
inline BOOL CRectT<T>::SubtractRect(
	_In_ RECTT<T>* lpRectSrc1,
	_In_ RECTT<T>* lpRectSrc2) throw()
{
	if (!lpRectSrc1 || !lpRectSrc2) return false;

	CRectT dr1(lpRectSrc1), dr2(lpRectSrc2);

	if (lpRectSrc1->left >= lpRectSrc2->left &&
		lpRectSrc1->top >= lpRectSrc2->top &&
		lpRectSrc1->right <= lpRectSrc2->right &&
		lpRectSrc1->bottom <= lpRectSrc2->bottom)
	{
		CRectT<T>::left = 0;
		CRectT<T>::top = 0;
		CRectT<T>::right = 0;
		CRectT<T>::bottom = 0;
		return true;
	}

	if (!dr1.IntersectRect(dr1, dr2))
	{
		CopyRectT(lpRectSrc1);
		return true;
	}

	dr1 = *lpRectSrc1;

	if (lpRectSrc1->top >= lpRectSrc2->top &&
		lpRectSrc1->bottom <= lpRectSrc2->bottom)
	{
		if (lpRectSrc1->left < lpRectSrc2->left &&
			lpRectSrc1->right < lpRectSrc2->right)
		{
			dr1.right = lpRectSrc2->left;
		}
		else if (lpRectSrc1->left > lpRectSrc2->left &&
			lpRectSrc1->right > lpRectSrc2->right)
		{
			dr1.left = lpRectSrc2->right;
		}
	}

	if (lpRectSrc1->left >= lpRectSrc2->left &&
		lpRectSrc1->right <= lpRectSrc2->right)
	{
		if (lpRectSrc1->top < lpRectSrc2->top &&
			lpRectSrc1->bottom < lpRectSrc2->bottom)
		{
			dr1.bottom = lpRectSrc2->top;
		}
		else if (lpRectSrc1->top > lpRectSrc2->top &&
			lpRectSrc1->bottom > lpRectSrc2->bottom)
		{
			dr1.top = lpRectSrc2->bottom;
		}
	}

	*this = dr1;

	return true;
}

template<typename T>
inline void CRectT<T>::operator=(_In_ const RECTT<T>& srcRect) throw()
{
	::CopyRectT(this, &srcRect);
}

template<typename T>
inline BOOL CRectT<T>::operator==(_In_ const RECTT<T>& rect) const throw()
{
	return ::EqualRect(&rect);
}

template<typename T>
inline BOOL CRectT<T>::operator!=(_In_ const RECTT<T>& rect) const throw()
{
	return !::EqualRect(&rect);
}

template<typename T>
inline void CRectT<T>::operator+=(_In_ POINTT<T> point) throw()
{
	::OffsetRect(point.x, point.y);
}

template<typename T>
inline void CRectT<T>::operator+=(_In_ SIZET<T> size) throw()
{
	::OffsetRect(size.cx, size.cy);
}

template<typename T>
inline void CRectT<T>::operator+=(_In_ RECTT<T>* lpRect) throw()
{
	InflateRect(lpRect);
}

template<typename T>
inline void CRectT<T>::operator-=(_In_ POINTT<T> point) throw()
{
	::OffsetRect(-point.x, -point.y);
}

template<typename T>
inline void CRectT<T>::operator-=(_In_ SIZET<T> size) throw()
{
	::OffsetRect(-size.cx, -size.cy);
}

template<typename T>
inline void CRectT<T>::operator-=(_In_ RECTT<T>* lpRect) throw()
{
	DeflateRect(lpRect);
}

template<typename T>
inline void CRectT<T>::operator&=(_In_ const RECTT<T>& rect) throw()
{
	::IntersectRect(this, &rect);
}

template<typename T>
inline void CRectT<T>::operator|=(_In_ const RECTT<T>& rect) throw()
{
	::UnionRect(this, &rect);
}


template<typename T>
inline CRectT<T> CRectT<T>::operator+(_In_ POINTT<T> pt) const throw()
{
	CRectT<T> rect(*this);
	rect.OffsetRect(pt.x, pt.y);
	return rect;
}

template<typename T>
inline CRectT<T> CRectT<T>::operator-(_In_ POINTT<T> pt) const throw()
{
	CRectT rect(*this);
	rect.OffsetRect(-pt.x, -pt.y);
	return rect;
}

template<typename T>
inline CRectT<T> CRectT<T>::operator+(_In_ SIZET<T> size) const throw()
{
	CRectT rect(*this);
	rect.OffsetRect(size.cx, size.cy);
	return rect;
}

template<typename T>
inline CRectT<T> CRectT<T>::operator-(_In_ SIZET<T> size) const throw()
{
	CRectT rect(*this);
	rect.OffsetRect(-size.cx, -size.cy);
	return rect;
}

template<typename T>
inline CRectT<T> CRectT<T>::operator+(_In_ RECTT<T>* lpRect) const throw()
{
	CRectT rect(this);
	rect.InflateRect(lpRect);
	return rect;
}

template<typename T>
inline CRectT<T> CRectT<T>::operator-(_In_ RECTT<T>* lpRect) const throw()
{
	CRectT rect(this);
	rect.DeflateRect(lpRect);
	return rect;
}

template<typename T>
inline CRectT<T> CRectT<T>::operator&(_In_ const RECTT<T>& rect2) const throw()
{
	CRectT rect;
	::IntersectRect(&rect, this, &rect2);
	return rect;
}

template<typename T>
inline CRectT<T> CRectT<T>::operator|(_In_ const RECTT<T>& rect2) const throw()
{
	CRectT rect;
	::UnionRect(&rect, this, &rect2);
	return rect;
}

template<typename T>
inline CRectT<T> CRectT<T>::MulDiv(
	_In_ int nMultiplier,
	_In_ int nDivisor) const throw()
{
	return CRectT(
		::MulDiv(CRectT<T>::left, nMultiplier, nDivisor),
		::MulDiv(CRectT<T>::top, nMultiplier, nDivisor),
		::MulDiv(CRectT<T>::right, nMultiplier, nDivisor),
		::MulDiv(CRectT<T>::bottom, nMultiplier, nDivisor));
}