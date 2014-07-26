// PicViewerDoc.cpp : implementation of the CPicViewerDoc class
//

#include "stdafx.h"
#include "PicViewer.h"

#include "PicViewerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPicViewerDoc

IMPLEMENT_DYNCREATE(CPicViewerDoc, CDocument)

BEGIN_MESSAGE_MAP(CPicViewerDoc, CDocument)
	//{{AFX_MSG_MAP(CPicViewerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPicViewerDoc construction/destruction

CPicViewerDoc::CPicViewerDoc()
{
	m_image=NULL;
	m_bImageOk=FALSE;
	//m_cvvImage=NULL;
	// TODO: add one-time construction code here

}

CPicViewerDoc::~CPicViewerDoc()
{
	if (m_image)
	{
		cvReleaseImage(&m_image);
	}
}

BOOL CPicViewerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPicViewerDoc serialization

void CPicViewerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{

		// TODO: add loading code here
		loadimage(ar.GetFile()->GetFilePath());
	}
}
void CPicViewerDoc::loadimage(const char* fn)
{
	m_image = cvLoadImage(fn);
	m_bImageOk=TRUE;

}
/////////////////////////////////////////////////////////////////////////////
// CPicViewerDoc diagnostics

#ifdef _DEBUG
void CPicViewerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPicViewerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPicViewerDoc commands
