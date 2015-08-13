// HEROLIST.cpp : implementation file
//

#include "stdafx.h"
#include "Mine.h"
#include "HEROLIST.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHEROLIST dialog


CHEROLIST::CHEROLIST(CWnd* pParent /*=NULL*/)
	: CDialog(CHEROLIST::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHEROLIST)
	m_szPrimary = _T("");
	m_szSecond = _T("");
	m_szAdvance = _T("");
	m_uPrimary =999;
	m_uSecond =999;
	m_uAdvance =999;
	//}}AFX_DATA_INIT
}


void CHEROLIST::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHEROLIST)
	DDX_Text(pDX, IDC_NAME1, m_szPrimary);
	DDX_Text(pDX, IDC_NAME2, m_szSecond);
	DDX_Text(pDX, IDC_NAME3, m_szAdvance);
	DDX_Text(pDX, IDC_SCORE1, m_uPrimary);
	DDX_Text(pDX, IDC_SCORE2, m_uSecond);
	DDX_Text(pDX, IDC_SCORE3, m_uAdvance);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHEROLIST, CDialog)
	//{{AFX_MSG_MAP(CHEROLIST)
	ON_BN_CLICKED(ID_NEW_SCORE, OnNewScore)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHEROLIST message handlers

void CHEROLIST::OnNewScore() 
{
	// TODO: Add your control notification handler code here
	m_szPrimary=_T("ÄäÃû");
	m_szSecond=_T("ÄäÃû");
	m_szAdvance=_T("ÄäÃû");
    m_uPrimary=999;
    m_uSecond=999;
    m_uAdvance=999;
	UpdateData(FALSE);
}
