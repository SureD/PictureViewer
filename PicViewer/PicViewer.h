// PicViewer.h : main header file for the PICVIEWER application
//

#if !defined(AFX_PICVIEWER_H__ACEA6BE1_C3BE_4100_8570_D9240227C929__INCLUDED_)
#define AFX_PICVIEWER_H__ACEA6BE1_C3BE_4100_8570_D9240227C929__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPicViewerApp:
// See PicViewer.cpp for the implementation of this class
//

class CPicViewerApp : public CWinApp
{
public:
	CPicViewerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPicViewerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CPicViewerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICVIEWER_H__ACEA6BE1_C3BE_4100_8570_D9240227C929__INCLUDED_)
