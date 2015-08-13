#if !defined(AFX_HEROLIST_H__D669AAC9_048E_4268_8CD8_04B6300C1080__INCLUDED_)
#define AFX_HEROLIST_H__D669AAC9_048E_4268_8CD8_04B6300C1080__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HEROLIST.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHEROLIST dialog

class CHEROLIST : public CDialog
{
// Construction
public:
	CHEROLIST(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHEROLIST)
	enum { IDD = IDD_HERO_LIST };
	CString	m_szPrimary;
	CString	m_szSecond;
	CString	m_szAdvance;
	UINT	m_uPrimary;
	UINT	m_uSecond;
	UINT	m_uAdvance;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHEROLIST)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHEROLIST)
	afx_msg void OnNewScore();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEROLIST_H__D669AAC9_048E_4268_8CD8_04B6300C1080__INCLUDED_)
