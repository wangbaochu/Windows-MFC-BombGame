#if !defined(AFX_NEWRECORD_H__2D74C425_710D_48C6_B217_C2EE8A4585B2__INCLUDED_)
#define AFX_NEWRECORD_H__2D74C425_710D_48C6_B217_C2EE8A4585B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NEWRECORD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNEWRECORD dialog

class CNEWRECORD : public CDialog
{
// Construction
public:
	CNEWRECORD(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNEWRECORD)
	enum { IDD = IDD_NEW_RECORD };
	CString	m_newname;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNEWRECORD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNEWRECORD)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWRECORD_H__2D74C425_710D_48C6_B217_C2EE8A4585B2__INCLUDED_)
