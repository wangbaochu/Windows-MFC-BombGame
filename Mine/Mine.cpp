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
    //位图资源的载入操作


    CMineWnd *m_pMineWnd;
    m_pMineWnd=new CMineWnd();

    m_pMineWnd->InitGame();
    m_pMineWnd->SizeWindow();

 
	//设计窗口类
	WNDCLASS wc;//定义一个窗口类wc，其具有十个成员变量依次如下
	            //The WNDCLASS structure contains the window class attributes 
    ZeroMemory(&wc,sizeof(wc));
//	wc.hbrBackground=(HBRUSH)GetStockObject(LTGRAY_BRUSH);
//	wc.hbrBackground=(HBRUSH)GetStockObject(LTGRAY_BRUSH);
//	wc.hbrBackground=NULL;
//  wc.hbrBackground=(HBRUSH)COLOR_CAPTIONTEXT;

    wc.hCursor=LoadCursor(IDC_ARROW);//指定窗口类的光标句柄
    wc.hIcon=LoadIcon(IDI_ICON1);//指定窗口类的图标句柄
    wc.hInstance=AfxGetInstanceHandle();
    wc.lpfnWndProc=::DefWindowProc;
    wc.lpszClassName="className";//指定窗口类的名称。wc.lpszWindowName是指窗口标题名
    wc.lpszMenuName=MAKEINTRESOURCE(IDR_MAINFRAME);//指定菜单资源的名称



   if (!AfxRegisterClass(&wc))
   {
	AfxMessageBox("注册类失败!");
		return FALSE;
   }

   UINT uWidth=DEFAULT_FRAME_X + PRIMARY_XNUM*MINE_WIDTH + LINE_WIDTH_0*3 + SIDE_WIDTH_0 + SIDE_WIDTH_1;
   UINT uHeight=DEFAULT_FRAME_Y + PRIMARY_YNUM*MINE_HEIGHT + LINE_WIDTH_0*3 + SIDE_WIDTH_0*2 + SIDE_WIDTH_1 + SHELL_S_H;
   UINT uXPos=GetSystemMetrics(SM_CXSCREEN)/2-uWidth/2;
   UINT uYPos=GetSystemMetrics(SM_CYSCREEN)/2-uHeight/2;//窗口显示在屏幕的中央


   //创建窗口
   if (!m_pMineWnd->CreateEx(NULL,"className",_T("扫雷"),WS_SYSMENU|WS_CAPTION|WS_MINIMIZEBOX ,uXPos,uYPos,uWidth,uHeight,NULL,NULL))
   {//CWnd::Create()是创建子窗口，并把它attach给父窗口
	   AfxMessageBox("创建窗口失败！");
		return FALSE;
   }

    //设置初始菜单的标记
	if (m_pMineWnd->m_bMarkful)	
		m_pMineWnd->GetMenu()->GetSubMenu(0)->CheckMenuItem(7,MF_BYPOSITION|MF_CHECKED);
	if (m_pMineWnd->m_bColorful)	
		m_pMineWnd->GetMenu()->GetSubMenu(0)->CheckMenuItem(8,MF_BYPOSITION|MF_CHECKED);
	if (m_pMineWnd->m_bSoundful)	
		m_pMineWnd->GetMenu()->GetSubMenu(0)->CheckMenuItem(9,MF_BYPOSITION|MF_CHECKED);

    //绑定该窗口为主窗口
	m_pMainWnd=m_pMineWnd;
    m_pMineWnd->ShowWindow(SW_NORMAL);
    m_pMineWnd->UpdateWindow();

	return TRUE;
}


