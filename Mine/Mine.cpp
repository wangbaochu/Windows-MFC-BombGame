// Mine.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Mine.h"
#include "MineWnd.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMineApp

BEGIN_MESSAGE_MAP(CMineApp, CWinApp)
	//{{AFX_MSG_MAP(CMineApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMineApp construction

CMineApp::CMineApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMineApp object

CMineApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMineApp initialization

BOOL CMineApp::InitInstance()
{
    //λͼ��Դ���������


    CMineWnd *m_pMineWnd;
    m_pMineWnd=new CMineWnd();

    m_pMineWnd->InitGame();
    m_pMineWnd->SizeWindow();

 
	//��ƴ�����
	WNDCLASS wc;//����һ��������wc�������ʮ����Ա������������
	            //The WNDCLASS structure contains the window class attributes 
    ZeroMemory(&wc,sizeof(wc));
//	wc.hbrBackground=(HBRUSH)GetStockObject(LTGRAY_BRUSH);
//	wc.hbrBackground=(HBRUSH)GetStockObject(LTGRAY_BRUSH);
//	wc.hbrBackground=NULL;
//  wc.hbrBackground=(HBRUSH)COLOR_CAPTIONTEXT;

    wc.hCursor=LoadCursor(IDC_ARROW);//ָ��������Ĺ����
    wc.hIcon=LoadIcon(IDI_ICON1);//ָ���������ͼ����
    wc.hInstance=AfxGetInstanceHandle();
    wc.lpfnWndProc=::DefWindowProc;
    wc.lpszClassName="className";//ָ������������ơ�wc.lpszWindowName��ָ���ڱ�����
    wc.lpszMenuName=MAKEINTRESOURCE(IDR_MAINFRAME);//ָ���˵���Դ������



   if (!AfxRegisterClass(&wc))
   {
	AfxMessageBox("ע����ʧ��!");
		return FALSE;
   }

   UINT uWidth=DEFAULT_FRAME_X + PRIMARY_XNUM*MINE_WIDTH + LINE_WIDTH_0*3 + SIDE_WIDTH_0 + SIDE_WIDTH_1;
   UINT uHeight=DEFAULT_FRAME_Y + PRIMARY_YNUM*MINE_HEIGHT + LINE_WIDTH_0*3 + SIDE_WIDTH_0*2 + SIDE_WIDTH_1 + SHELL_S_H;
   UINT uXPos=GetSystemMetrics(SM_CXSCREEN)/2-uWidth/2;
   UINT uYPos=GetSystemMetrics(SM_CYSCREEN)/2-uHeight/2;//������ʾ����Ļ������


   //��������
   if (!m_pMineWnd->CreateEx(NULL,"className",_T("ɨ��"),WS_SYSMENU|WS_CAPTION|WS_MINIMIZEBOX ,uXPos,uYPos,uWidth,uHeight,NULL,NULL))
   {//CWnd::Create()�Ǵ����Ӵ��ڣ�������attach��������
	   AfxMessageBox("��������ʧ�ܣ�");
		return FALSE;
   }

    //���ó�ʼ�˵��ı��
	if (m_pMineWnd->m_bMarkful)	
		m_pMineWnd->GetMenu()->GetSubMenu(0)->CheckMenuItem(7,MF_BYPOSITION|MF_CHECKED);
	if (m_pMineWnd->m_bColorful)	
		m_pMineWnd->GetMenu()->GetSubMenu(0)->CheckMenuItem(8,MF_BYPOSITION|MF_CHECKED);
	if (m_pMineWnd->m_bSoundful)	
		m_pMineWnd->GetMenu()->GetSubMenu(0)->CheckMenuItem(9,MF_BYPOSITION|MF_CHECKED);

    //�󶨸ô���Ϊ������
	m_pMainWnd=m_pMineWnd;
    m_pMineWnd->ShowWindow(SW_NORMAL);
    m_pMineWnd->UpdateWindow();

	return TRUE;
}


