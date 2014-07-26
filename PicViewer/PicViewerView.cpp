// PicViewerView.cpp : implementation of the CPicViewerView class
//

#include "stdafx.h"
#include "PicViewer.h"

#include "PicViewerDoc.h"
#include "PicViewerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPicViewerView

IMPLEMENT_DYNCREATE(CPicViewerView, CView)

BEGIN_MESSAGE_MAP(CPicViewerView, CView)
	//{{AFX_MSG_MAP(CPicViewerView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		ON_WM_MOUSEWHEEL()
		ON_WM_LBUTTONDOWN()
		ON_WM_LBUTTONUP()
		ON_WM_MOUSEMOVE()
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPicViewerView construction/destruction

CPicViewerView::CPicViewerView()
{
	m_oldInflate=m_inflate=-1.0;
	// TODO: add construction code here

}

CPicViewerView::~CPicViewerView()
{
}

BOOL CPicViewerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPicViewerView drawing

void CPicViewerView::OnDraw(CDC* pDC)
{
	CPicViewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->GetReady())
	{
		CDC memDC;      //内存绘图设备
		CBitmap memBitmap;    //内存绘图;
		CBitmap* pOldBmp = NULL;
		CRect rect;
		GetClientRect(&rect);
		memDC.CreateCompatibleDC(pDC);
		memBitmap.CreateCompatibleBitmap(pDC,rect.right,rect.bottom);
		pOldBmp = memDC.SelectObject(&memBitmap);
		CBrush bkBrush( RGB(58,110,165) );
		memDC.FillRect( &rect, &bkBrush );
		const IplImage* t_Image = pDoc->GetImage();
		int imageHeight = t_Image->height;
 		int imageWidth = t_Image->width;
 		if (m_oldInflate==-1) //如果显示rect发生变化,重新调整缩放率
  		{
// 		
			if (rect.Width()>rect.Height())	
				m_inflate = 0.9*rect.Height()/imageHeight;
			else
				m_inflate = 0.9*rect.Width()/imageWidth;
			m_oldInflate = m_inflate;
			CvSize size; //根据缩放率计算目标图像大小
			size.height=m_inflate*imageHeight;
			size.width=m_inflate*imageWidth;
			IplImage *Image=cvCreateImage(size,IPL_DEPTH_8U,3);
			cvResize(t_Image,Image,CV_INTER_CUBIC);
			CvvImage cimg;
			cimg.CopyOf(Image);
			//cimg.DrawToHDC(pHdc, rect);
			//cimg.Show(pHdc,rect.left,rect.top,rect.right,rect.bottom);
			//调整显示范围使其居中
			CRect memShowRect;
			memShowRect.left=rect.left+(rect.Width()-size.width)/2;
			memShowRect.top=rect.top+(rect.Height()-size.height)/2;
			memShowRect.right=rect.right;
			memShowRect.bottom=rect.bottom;
			m_memShowRect=memShowRect;
			//memShowRect=rect;
			//
			cimg.Show(memDC.GetSafeHdc(),memShowRect.left,memShowRect.top,memShowRect.right,memShowRect.bottom);
			cvReleaseImage(&Image);
		}else{
				m_oldInflate=m_inflate;
				CvSize size; //根据缩放率计算目标图像大小
				size.height=m_inflate*imageHeight;
				size.width=m_inflate*imageWidth;
				IplImage *Image=cvCreateImage(size,IPL_DEPTH_8U,3);
				cvResize(t_Image,Image,CV_INTER_CUBIC);
				CvvImage cimg;
				cimg.CopyOf(Image);
				cimg.Show(memDC.GetSafeHdc(),m_memShowRect.left,m_memShowRect.top,size.width,size.height);
				//cimg.Show(memDC.GetSafeHdc(),rect.left,rect.top,rect.right,rect.bottom);
				cvReleaseImage(&Image);
		}
			char str[25];
			sprintf(str, "当前的缩放率为%f" ,m_inflate);
			memDC.TextOut(rect.right-200,rect.bottom-20,str);
			pDC->BitBlt(rect.left,rect.top,rect.right,rect.bottom,&memDC,0,0,SRCCOPY);//将内存中画好的图显示在屏幕上
			memDC.SelectObject(pOldBmp);
			memDC.DeleteDC();						
			memBitmap.DeleteObject();	
	}

	// TODO: add draw code for native data here
}
void CPicViewerView::OnLButtonDown(UINT nFlags, CPoint point)
{
    if(m_memShowRect.PtInRect(point))
    {
		//::SetCursor(LoadCursor());
        m_bIsPick    = TRUE;
        m_ptPre        = point;
        SetCapture();
    }
	
    CView::OnLButtonDown(nFlags, point);
}

void CPicViewerView::OnLButtonUp(UINT nFlags, CPoint point)
{
    m_bIsPick = FALSE;
    ReleaseCapture();
	
    CView::OnLButtonUp(nFlags, point);
}

void CPicViewerView::OnMouseMove(UINT nflags,CPoint point)
{
    if(m_bIsPick)
    {
        m_memShowRect.top+= point.y-m_ptPre.y;
        m_memShowRect.bottom+= point.y-m_ptPre.y;
        m_memShowRect.right+= point.x-m_ptPre.x;
        m_memShowRect.left+= point.x-m_ptPre.x;
		
        m_ptPre=point;
        Invalidate(FALSE);
    }
}
CPicViewerView::OnMouseWheel(UINT nFlags, 
						   short zDelta, CPoint pt)
{
	CPicViewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->GetReady())
	{
		//m_viewRect.inflateRatio(-zDelta/120.f/2);
		if(zDelta>0)
			m_inflate+=0.1f;
		else
			m_inflate<=0?m_inflate=0.1:m_inflate-=0.1f;
		
		Invalidate(FALSE);
	}
	
	return CView::OnMouseWheel(nFlags, zDelta, pt);
	
        }

/////////////////////////////////////////////////////////////////////////////
// CPicViewerView printing

BOOL CPicViewerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPicViewerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPicViewerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPicViewerView diagnostics

#ifdef _DEBUG
void CPicViewerView::AssertValid() const
{
	CView::AssertValid();
}

void CPicViewerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPicViewerDoc* CPicViewerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPicViewerDoc)));
	return (CPicViewerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPicViewerView message handlers
