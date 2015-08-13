// NEWRECORD.cpp : implementation file
//

#include "stdafx.h"
#include "Mine.h"
#include "NEWRECORD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNEWRECORD dialog


CNEWRECORD::CNEWRECORD(CWnd* pParent /*=NULL*/)
	: CDialog(CNEWRECORD::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNEWRECORD)
	m_newname = _T("");
	//}}AFX_DATA_INIT
}


void CNEWRECORD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNEWRECORD)
	DDX_Text(pDX, IDC_NEW_NAME, m_newname);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNEWRECORD, CDialog)
	//{{AFX_MSG_MAP(CNEWRECORD)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNEWRECORD message handlers

BOOL CNEWRECORD::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//DEL void CNEWRECORD::OnOK() 
//DEL {
//DEL 	// TODO: Add extra validation here
//DEL 
//DEL 	CDialog::OnOK();
//DEL }
