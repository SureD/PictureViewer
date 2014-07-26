// PicViewerDoc.h : interface of the CPicViewerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PICVIEWERDOC_H__DB1025B5_D71A_4658_B0EC_87AFAE8F5B4F__INCLUDED_)
#define AFX_PICVIEWERDOC_H__DB1025B5_D71A_4658_B0EC_87AFAE8F5B4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPicViewerDoc : public CDocument
{
protected: // create from serialization only
	CPicViewerDoc();
	DECLARE_DYNCREATE(CPicViewerDoc)

// Attributes
public:
	void loadimage(const char* fn);
	const IplImage* GetImage() {return m_image;};
	BOOL GetReady() {return m_bImageOk;};
	INT GetHeight() {return m_image->height;};
	INT GetWidth() {return m_image->width;};
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPicViewerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPicViewerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	IplImage *m_image;
	BOOL m_bImageOk;
	//CvvImage *m_cvvImage;

// Generated message map functions
protected:
	//{{AFX_MSG(CPicViewerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICVIEWERDOC_H__DB1025B5_D71A_4658_B0EC_87AFAE8F5B4F__INCLUDED_)
