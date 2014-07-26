// PicViewerView.h : interface of the CPicViewerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PICVIEWERVIEW_H__2600ACEF_36FB_459D_B833_9D752A90E3A4__INCLUDED_)
#define AFX_PICVIEWERVIEW_H__2600ACEF_36FB_459D_B833_9D752A90E3A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPicViewerView : public CView
{
protected: // create from serialization only
	CPicViewerView();
	DECLARE_DYNCREATE(CPicViewerView)

// Attributes
public:
	CPicViewerDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPicViewerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPicViewerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	double m_inflate;
	double m_oldInflate;
	CRect m_memShowRect;
	BOOL  m_bIsPick;
    CPoint m_ptPre;
// Generated message map functions
protected:
	//{{AFX_MSG(CPicViewerView)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nflags,CPoint point);// Û±Í“∆∂Ø
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PicViewerView.cpp
inline CPicViewerDoc* CPicViewerView::GetDocument()
   { return (CPicViewerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICVIEWERVIEW_H__2600ACEF_36FB_459D_B833_9D752A90E3A4__INCLUDED_)
