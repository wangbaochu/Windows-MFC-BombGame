// Mine.h : main header file for the MINE application
//

#if !defined(AFX_MINE_H__F5D032E3_E475_49D8_BF43_9B72D8FEAC1B__INCLUDED_)
#define AFX_MINE_H__F5D032E3_E475_49D8_BF43_9B72D8FEAC1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMineApp:
// See Mine.cpp for the implementation of this class
//

class CMineApp : public CWinApp
{
public:
	CMineApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMineApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMineApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MINE_H__F5D032E3_E475_49D8_BF43_9B72D8FEAC1B__INCLUDED_)
