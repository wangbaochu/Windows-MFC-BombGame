// MineDoc.cpp : implementation of the CMineDoc class
//

#include "stdafx.h"
#include "Mine.h"

#include "MineDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMineDoc

IMPLEMENT_DYNCREATE(CMineDoc, CDocument)

BEGIN_MESSAGE_MAP(CMineDoc, CDocument)
	//{{AFX_MSG_MAP(CMineDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMineDoc construction/destruction

CMineDoc::CMineDoc()
{
	// TODO: add one-time construction code here

}

CMineDoc::~CMineDoc()
{
}

BOOL CMineDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMineDoc serialization

void CMineDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMineDoc diagnostics

#ifdef _DEBUG
void CMineDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMineDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMineDoc commands
