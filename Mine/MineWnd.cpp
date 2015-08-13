// MineWnd.cpp : implementation file
//Initialstance()

#include "stdafx.h"
#include "Mine.h"
#include "MineWnd.h"
#include "HEROLIST.h"
#include "Mmsystem.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "NEWRECORD.h"


//#include "MineDefs.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMineWnd
CMineWnd::CMineWnd()
{
    m_uXNum=PRIMARY_XNUM;
    m_uYNum=PRIMARY_YNUM;
	m_uMineNum=PRIMARY_MINENUM;
    m_uBtnState=BUTTON_NORMAL;//笑脸初始状态

    m_sszPrimary=_T("匿名");
	m_sszSecond=_T("匿名");
    m_sszAdvance=_T("匿名"); 
/*	 m_bmpButton.LoadBitmap(IDB_BTN_COLOR);//雷位图
     m_bmpNumber.LoadBitmap(IDB_NUM_COLOR);//数字位图
     m_bmpMine.LoadBitmap(IDB_MINE_COLOR);//笑脸按钮位图
*/
    
//     m_uBtnRect[0]=MINE_AREA_LEFT+m_uXNum*MINE_WIDTH/2-12;//笑脸的左上角和右下角X坐标
//     m_uBtnRect[1]=MINE_AREA_LEFT+m_uXNum*MINE_WIDTH/2+12;

     m_uGameState=GS_WAIT;//开始游戏状态默认为（GS_WAIT==0）
     m_bSoundful=FALSE;
     m_bColorful=TRUE;
	 m_bMarkful=TRUE;
	 m_bLRBtnDown=FALSE;
	 m_LRBtnDouble=FALSE;//标识鼠标左右键是否曾经同时按下，主要是为了在左键弹起时判断是否挖掉所点击模块
     m_WndActive=TRUE;//在OnActive（）中标识窗口是否处于激活状态，以便决定是否计时
	 
	 CMineWnd::LoadBitmap();
    // CBrush brush1(RGB(192,192,192));
	//m_brsBG=&brush1;
//	 m_brsBG=CBrush::FromHandle((HBRUSH)GetStockObject(LTGRAY_BRUSH));


/*	 m_uShellRcX[0]=m_uXNum *MINE_WIDTH + LINE_WIDTH_0*3 + SIDE_WIDTH_0 + SIDE_WIDTH_1;
	 m_uShellRcX[1]=m_uXNum *MINE_WIDTH + LINE_WIDTH_0*2;
     m_uShellRcY[0]=m_uYNum *MINE_HEIGHT + LINE_WIDTH_0*3 + SIDE_WIDTH_0*2 + SIDE_WIDTH_1 + SHELL_S_H;
	 m_uShellRcY[1]=m_uYNum *MINE_HEIGHT + LINE_WIDTH_0*2;
*/
//     m_uNumRect[0]=17;
//     m_uNumRect[1]=1+2*(MINE_AREA_LEFT+m_uXNum*MINE_WIDTH/2)-57;//数字所在坐标区
//   m_uNumRect[1]=m_uXNum *MINE_WIDTH + LINE_WIDTH_0*3 + SIDE_WIDTH_0 + SIDE_WIDTH_1-57;
	 

     m_uLevel=1;//记录选择的级别
     m_uTimer=0;//定时器标识初始化为0

     m_nLeaveNum=PRIMARY_MINENUM;//数字显示雷的个数
}

CMineWnd::~CMineWnd()
{
}


BEGIN_MESSAGE_MAP(CMineWnd, CWnd)
	//{{AFX_MSG_MAP(CMineWnd)
	ON_COMMAND(ID_BASE_LEVEL, OnBaseLevel)
	ON_COMMAND(ID_MIDDLE_LEVEL, OnMiddleLevel)
	ON_COMMAND(ID_ADVANCE_LEVEL, OnAdvanceLevel)
	ON_COMMAND(ID_COLOR, OnColor)
	ON_COMMAND(ID_SOUND, OnSound)
	ON_COMMAND(ID_HELP, OnHelp)
	ON_COMMAND(ID_ABOUT, OnAbout)
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_COMMAND(ID_HERO_TABLE, OnHeroTable)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_TAG, OnTag)
	ON_COMMAND(ID_EXIT, OnExit)
	ON_WM_ACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMineWnd message handlers

void CMineWnd::SizeWindow()//改变窗口大小的函数
{
	//计算不同难度的窗口的大小
    m_uWidth=DEFAULT_FRAME_X + m_uXNum *MINE_WIDTH + LINE_WIDTH_0*3 + SIDE_WIDTH_0 + SIDE_WIDTH_1;
	m_uHeight=DEFAULT_FRAME_Y + m_uYNum *MINE_HEIGHT + LINE_WIDTH_0*3 + SIDE_WIDTH_0*2 + SIDE_WIDTH_1 + SHELL_S_H;	

    m_uBtnRect[0]=MINE_AREA_LEFT+m_uXNum*MINE_WIDTH/2-12;//笑脸的左上角和右下角X坐标
    m_uBtnRect[1]=MINE_AREA_LEFT+m_uXNum*MINE_WIDTH/2+12;



    //内存画图工作区的大小
	m_rcClient.left=0;
    m_rcClient.top=0;
    m_rcClient.right=m_uWidth-DEFAULT_FRAME_X;	
    m_rcClient.bottom=m_uHeight-DEFAULT_FRAME_Y;

    //笑脸的左上角和右下角X坐标
    m_uBtnRect[0]=MINE_AREA_LEFT+m_uXNum*MINE_WIDTH/2-12;
    m_uBtnRect[1]=MINE_AREA_LEFT+m_uXNum*MINE_WIDTH/2+12;

	//三维外壳的起点坐标
	 m_uShellRcX[0]=m_uXNum *MINE_WIDTH + LINE_WIDTH_0*3 + SIDE_WIDTH_0 + SIDE_WIDTH_1;
	 m_uShellRcX[1]=m_uXNum *MINE_WIDTH + LINE_WIDTH_0*2;
     m_uShellRcY[0]=m_uYNum *MINE_HEIGHT + LINE_WIDTH_0*3 + SIDE_WIDTH_0*2 + SIDE_WIDTH_1 + SHELL_S_H;
	 m_uShellRcY[1]=m_uYNum *MINE_HEIGHT + LINE_WIDTH_0*2;

     //两个数字显示区的x起点坐标
     m_uNumRect[0]=17;
     m_uNumRect[1]=1+2*(MINE_AREA_LEFT+m_uXNum*MINE_WIDTH/2)-57;



//	SetWindowPos(&wndTopMost, 0,0,m_uWidth,m_uHeight,SWP_NOZORDER|SWP_NOMOVE|SWP_NOCOPYBITS);
	// SetWindowPos（）改变当前窗口的大小



//	Invalidate();
}

void CMineWnd::OnBaseLevel() 
{
	// TODO: Add your command handler code here
	m_uXNum=PRIMARY_XNUM;//x方向初级雷方块数目m_uXNum
    m_uYNum=PRIMARY_YNUM;//y方向初级雷方块数目m_uYNum
	m_uMineNum=PRIMARY_MINENUM;
    m_nLeaveNum=PRIMARY_MINENUM;
	m_uLevel=1;//选择的级别记录
	m_uBtnState=BUTTON_NORMAL;
	InitGame();
	SizeWindow();
    SetWindowPos(&wndTopMost, 0,0,m_uWidth,m_uHeight,SWP_NOZORDER|SWP_NOMOVE|SWP_NOCOPYBITS);
	Invalidate();

}

void CMineWnd::OnMiddleLevel() 
{
	// TODO: Add your command handler code here
	m_uXNum=SECONDRY_XNUM;
    m_uYNum=SECONDRY_YNUM;
	m_uMineNum=SECONDRY_MINENUM;
    m_nLeaveNum=SECONDRY_MINENUM;
   	m_uLevel=2;//选择的级别记录
	m_uBtnState=BUTTON_NORMAL;
	InitGame();
	SizeWindow();
    SetWindowPos(&wndTopMost, 0,0,m_uWidth,m_uHeight,SWP_NOZORDER|SWP_NOMOVE|SWP_NOCOPYBITS);
	Invalidate(FALSE);

}

void CMineWnd::OnAdvanceLevel() 
{
	// TODO: Add your command handler code here
	m_uXNum=ADVANCE_XNUM;
    m_uYNum=ADVANCE_YNUM;
	m_uMineNum=ADVANCE_MINENUM;
    m_nLeaveNum=ADVANCE_MINENUM;
    m_uLevel=3;	//选择的级别记录
	m_uBtnState=BUTTON_NORMAL;			
	InitGame();
	SizeWindow();
    SetWindowPos(&wndTopMost, 0,0,m_uWidth,m_uHeight,SWP_NOZORDER|SWP_NOMOVE|SWP_NOCOPYBITS);
	Invalidate();
}

void CMineWnd::OnColor() 
{
	// TODO: Add your command handler code here
    
	m_bColorful=!m_bColorful;//该变旧颜色显示类型
	 if (m_bColorful)	
		GetMenu()->GetSubMenu(0)->CheckMenuItem(8,MF_BYPOSITION|MF_CHECKED);
	 else
		GetMenu()->GetSubMenu(0)->CheckMenuItem(8,MF_BYPOSITION|MF_UNCHECKED);
	LoadBitmap();//调用重写的位图加载函数，即时显示新效果
	Invalidate();
}

void CMineWnd::OnSound() 
{
	// TODO: Add your command handler code here
     m_bSoundful=!m_bSoundful;
	 if (m_bSoundful)	
		GetMenu()->GetSubMenu(0)->CheckMenuItem(9,MF_BYPOSITION|MF_CHECKED);
	 else
		GetMenu()->GetSubMenu(0)->CheckMenuItem(9,MF_BYPOSITION|MF_UNCHECKED);
}

void CMineWnd::OnHelp() 
{
	// TODO: Add your command handler code here
	::WinExec("HH WINMINE.CHM",SW_SHOW);
	//以第一个参数为命令行执行命令，以第二参数方式显示，意思是在命令行调用HH.EXE，
	//并输入参数WINMINE.CHM，令其打开该文件，即windows自带的扫雷游戏使用手册
}

void CMineWnd::OnAbout() 
{
	// TODO: Add your command handler code here
	ShellAbout(this->m_hWnd,"扫雷——王保初","wbc.wbc@163.com",NULL);
	//用代码创建一个“关于信息”的对话框
}

void CMineWnd::LayMines(UINT row, UINT col)//鼠标第一次点击时调用此函数
{
	srand((unsigned)time(NULL));//埋下随即种子
	UINT i,j;
	for (UINT index=0;index< m_uMineNum;)
	{
		//取随机数
		i=rand()%m_uYNum;
		j=rand()%m_uXNum;
		
		if (i==row&&j==col) continue;//第一个点击块不布雷，（row, col)是鼠标传过来的行列位置参数
		if (m_pMines[i][j].uAttrib!=ATTRIB_MINE)
		{
			m_pMines[i][j].uAttrib=ATTRIB_MINE;//修改属性为雷
			index++;
		}
	}
/////////////////////////////////////修改其它方块属性为非雷
    for (i=0;i<m_uYNum;i++)
    {
		for (j=0;j<m_uXNum;j++)
		{
			if (m_pMines[i][j].uAttrib!=ATTRIB_MINE)
			{
               m_pMines[i][j].uAttrib=ATTRIB_EMPTY;
			} 
		}
    }
		
}





void CMineWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	 CRect rcBtn(m_uBtnRect[0],15,m_uBtnRect[1],39);//笑脸所在区
	 CRect rcMineArea(MINE_AREA_LEFT,MINE_AREA_TOP,
		MINE_AREA_LEFT+m_uXNum*MINE_WIDTH,
        MINE_AREA_TOP+m_uYNum*MINE_HEIGHT);//雷区所在区域
    
     if (!rcMineArea.PtInRect(point))
     {//主要是为了实现左右键都按下时，拖动到外面松手后，笑脸能恢复原状
		 m_uBtnState=BUTTON_NORMAL;
		 m_bLRBtnDown=FALSE;
		 InvalidateRect(&rcBtn);
		 ReleaseCapture();
     }

/////////////////////////////////////////////////////////////////
//////////判断当前鼠标的位置
	if (rcBtn.PtInRect(point))
	{//点击笑脸
        m_uBtnState=BUTTON_NORMAL;//改变笑脸状态为BUTTON_NORMAL
        m_nLeaveNum=m_uMineNum; 
		InitGame();
		Invalidate(FALSE);
	}
	else if (rcMineArea.PtInRect(point))
	{//点击雷区
//		CString value;
		UINT around=0;//记录周围雷的数目		
////////////////////////////////////根据不同的游戏状态作处理
		switch(m_uGameState)
		{//游戏进行状态
		case GS_WAIT: case GS_RUN:	
			
		m_pOldMine=GetMine(point.x,point.y);
        if (!m_pOldMine)//判断鼠标是否击中雷块，没有则返回，跳出整个函数
	       return;							
//////////////////////////////////////////////游戏初始化时为GS_WAIT状态
		if (m_uGameState==GS_WAIT)
		{
            m_uSpendTime=1;
			//启动定时器
			m_uTimer=SetTimer(ID_TIMER_EVENT,1000,NULL);

			//布雷
			LayMines(m_pOldMine->uRow,m_pOldMine->uCol);

			//改变游戏状态为运行GS_RUN
			m_uGameState=GS_RUN;
		}
////////////////////////////////////////////////////判断是否左右键一起按下
        if (m_bLRBtnDown)
        {//判断是否左右键一起按下
		   BOOL blast=FALSE;//是否雷块标志错误
		   UINT i,j;
           UINT row=m_pOldMine->uRow;
           UINT col=m_pOldMine->uCol;
 	       UINT minRow=(row==0)? 0:row-1;
           UINT maxRow=row+2;
           UINT minCol=(col==0)? 0:col-1;
	       UINT maxCol=col+2;
           UINT around=0;
           around=GetAroundNum(row,col);
/////////////////////////////////////////////////////////////////
	       if ((around==m_uFlagNum&&m_uDICEYNum==0)&&(m_pOldMine->uOldState!=STATE_NORMAL)&&(m_pOldMine->uOldState!=STATE_FLAG)&&(m_pOldMine->uOldState!=STATE_DICEY)) 		   
		   {//如果点击的是已经挖过的模块 
		     // m_uDICEYNum;//周围被标记为问号的模块数
	           // m_uFlagNum周围被标记为雷Flag的模块数
			     //如果周围标志数等于雷数则打开周围所有块，即自动挖雷
			    for (i=minRow;i<maxRow;i++)
				{
				  for (j=minCol;j<maxCol;j++)
				  {
					if (!IsInMineArea(i,j)) continue;
		        	if(m_pMines[i][j].uOldState==STATE_NORMAL)
					{  
						if (m_pMines[i][j].uAttrib==ATTRIB_MINE)
						{/////////////////////////模块标志错误
							m_pMines[i][j].uState=STATE_BLAST;
                            m_pMines[i][j].uOldState=STATE_BLAST;
							blast=TRUE;//自动挖错
						}
						else //模块标志正确自动全部挖掉
						{
							UINT Aaround=GetAroundNum(i,j);
							if (Aaround==0) ExpandMines(i,j); 
							else
							{  m_pMines[i][j].uState=15-Aaround;
						       m_pMines[i][j].uOldState=15-Aaround;
							}
						} 
					}				  
				  }
				}
//				if ()
//				{
//				}
			    if (blast)//如果自动挖错则游戏结束
				{
					if (m_bSoundful)
					{
	                   PlaySound(MAKEINTRESOURCE(IDR_WAVE_BOMB),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
					   //或者SndPlaySound("c:\sound\music.wav",SND_ASYNC)
					}

					for (i=0;i<m_uYNum;i++)
					{/////////////找出标志错误的模块
						for (j=0;j<m_uXNum;j++)
						{/////////////找出标志错误的模块
							if ((m_pMines[i][j].uOldState==STATE_FLAG)&&(m_pMines[i][j].uAttrib==ATTRIB_EMPTY))
							{
							   m_pMines[i][j].uOldState=STATE_ERROR;
							   m_pMines[i][j].uState=STATE_ERROR;
							}
							if ((m_pMines[i][j].uOldState==STATE_NORMAL)&&(m_pMines[i][j].uAttrib==ATTRIB_MINE))
							{
							   m_pMines[i][j].uOldState=STATE_MINE;
							   m_pMines[i][j].uState=STATE_MINE;
							}
						}
					}

			    	m_uBtnState=BUTTON_DEAD;
	                m_uGameState=GS_DEAD;
	                if (m_uTimer!=0)
					{//将定时器销毁
		                KillTimer(ID_TIMER_EVENT);
	                	m_uTimer=0;
					}
	                Invalidate();
					ReleaseCapture();
					return;
				}			  			  
		   }			
///////////////////////////////////////////////////////////////////////
	       else////如果左右点击的不是已经挖过的模块，则恢复双击之前的原状
		   {
				  for (i=minRow;i<maxRow;i++)
				  {
					  for (j=minCol;j<maxCol;j++)
					  {
						 if (!IsInMineArea(i,j)) continue;
                         if(m_pMines[i][j].uOldState==STATE_NORMAL)						 
							m_pMines[i][j].uState=STATE_NORMAL;                            						 
					  }
				  }
		    // Invalidate();
		   }	
       m_bLRBtnDown=FALSE;		
		}
/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////判断左右双击已经结束，下面为左键单击挖雷
		 if ((m_pOldMine->uOldState==STATE_NORMAL)&&(m_LRBtnDouble==FALSE))//m_LRBtnDouble=FALSE表示之前没有左右键同时按下
				{//2.当该雷区域为正常，未作标记才打开
					//2.1如果该区域为雷则死亡
					if (IsMine(m_pOldMine->uRow,m_pOldMine->uCol))
					{
                        if (m_bSoundful)
						{
	                      PlaySound(MAKEINTRESOURCE(IDR_WAVE_BOMB),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
						  //或者SndPlaySound("c:\sound\music.wav",SND_ASYNC)
						}
						Dead(m_pOldMine->uRow,m_pOldMine->uCol);
						ReleaseCapture();
						return;
					}

					//2.2不是雷则获取周围雷的数目
					around=GetAroundNum(m_pOldMine->uRow,m_pOldMine->uCol);
					//2.3如果为空区域则拓展，否则打开该区域，显示周围的雷数目
					if (around==0) ExpandMines(m_pOldMine->uRow,m_pOldMine->uCol);
					else DrawDownNum(m_pOldMine,around);
				}
		    //	m_LRBtnDouble=FALSE;//双击后左键弹起上面代码没执行，则需复位，下次直接单击弹起便可执行

			   //2.4判断是否胜利
			   if (Victory())
			   {
                 if (m_bSoundful)
				 {
	               PlaySound(MAKEINTRESOURCE(IDR_WAVE_VICTORY),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
				 //或者SndPlaySound("c:\sound\music.wav",SND_ASYNC)
				 }
				Invalidate(FALSE);
//				ReleaseCapture();
				return;
			   }

			break;

		case GS_VICTORY:
		case GS_DEAD:
//			ReleaseCapture();
			return;
		default:
			break;
		}
		m_uBtnState=BUTTON_NORMAL;//笑脸按钮矩形图像恢复原状态状态
		Invalidate(FALSE);
	}

	else
	{//点击非雷区
		if (m_uGameState==GS_WAIT||m_uGameState==GS_RUN)
		{
			m_uBtnState=BUTTON_NORMAL;
			InvalidateRect(&rcBtn);
		}
	}
	
	ReleaseCapture();
	CWnd::OnLButtonUp(nFlags, point);
}

void CMineWnd::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	//雷所在区域
	CRect rcMineArea(MINE_AREA_LEFT,MINE_AREA_TOP,
		MINE_AREA_LEFT+m_uXNum*MINE_WIDTH,
        MINE_AREA_TOP+m_uYNum*MINE_HEIGHT);

	if (rcMineArea.PtInRect(point))
	{//点击雷区
		//if (m_uGameState==GS_RUN)
	
		m_pOldMine=GetMine(point.x,point.y);
		if (!m_pOldMine) return;

		if ((m_uGameState==GS_RUN||m_uGameState==GS_WAIT)&&nFlags==(MK_LBUTTON|MK_RBUTTON))
		{// 判断当前状态是否为左右鼠标同时按下
		    m_uBtnState=BUTTON_CLICK;
			m_bLRBtnDown=TRUE;//该变量是为了方便接下来在OnRButtonUp（）里面判断是否同时按下
			OnLRBtnDown(m_pOldMine->uRow,m_pOldMine->uCol);
			m_LRBtnDouble=TRUE;////左右双击后为TRUE，左键弹起不执行挖雷
		}

        else
			{
			  switch(m_pOldMine->uState)
			  {
		    	case STATE_NORMAL:
			    	m_pOldMine->uState=STATE_FLAG;
			    	m_pOldMine->uOldState=STATE_FLAG;
					m_nLeaveNum--;//剩余雷的数目
			    	break;

				case STATE_FLAG:
					if (m_bMarkful)
					{
					m_pOldMine->uState=STATE_DICEY;
					m_pOldMine->uOldState=STATE_DICEY;
                    m_nLeaveNum++;
					}				
					else
					{
					m_pOldMine->uState=STATE_NORMAL;
					m_pOldMine->uOldState=STATE_NORMAL;
                    m_nLeaveNum++;
					}
                     break;
		    	case STATE_DICEY:
			    	m_pOldMine->uState=STATE_NORMAL;
			    	m_pOldMine->uOldState=STATE_NORMAL;               
			    	break;
		    	default:
			    	break;
			  }
			}
			Invalidate();
	}
	CWnd::OnRButtonDown(nFlags, point);
}

void CMineWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_uGameState==GS_DEAD||m_uGameState==GS_VICTORY)
        return;

	//笑脸按钮所在区域
	CRect rcBtn(m_uBtnRect[0],15,m_uBtnRect[1],39);
	//雷所在区域
	CRect rcMineArea(MINE_AREA_LEFT,MINE_AREA_TOP,
		MINE_AREA_LEFT+m_uXNum*MINE_WIDTH,
        MINE_AREA_TOP+m_uYNum*MINE_HEIGHT);

      m_uOrigPoint=point;//存贮左键点击处位置，在鼠标移动函数中进行判断
	 SetCapture(); //设置鼠标捕获窗体外的消息，当拖到雷区外面松手后能响应鼠标消息函数

	if (rcBtn.PtInRect(point))
	{//鼠标点击笑脸
        m_uBtnState=BUTTON_DOWN;//改变笑脸状态为按下
//		InvalidateRect(rcBtn);
		Invalidate(FALSE);
	}
/////////////////////////////////////////////
	else if (rcMineArea.PtInRect(point))
	{//鼠标点击雷区
      //  m_uOrigPoint=point;
        m_pOldMine=GetMine(point.x,point.y);
     	if (!m_pOldMine) return;
        m_uBtnState=BUTTON_CLICK;//改变笑脸状态为“担心”
        m_LRBtnDouble=FALSE;//左右双击后为TRUE，左键弹起不执行挖雷。此处复位，下次左键直接单击弹起时便可执行挖雷

		if (nFlags==(MK_LBUTTON|MK_RBUTTON))
		{// 判断当前状态是否为左右鼠标同时按下
			m_bLRBtnDown=TRUE;//该变量是为了方便接下来在OnLButtonUp（）里面判断是否同时按下
			OnLRBtnDown(m_pOldMine->uRow,m_pOldMine->uCol);
			m_LRBtnDouble=TRUE;////左右双击后为TRUE，左键弹起不执行挖雷。上面复位，下次左键直接单击弹起时便可执行挖雷
		}   
		
        else if (m_pOldMine->uState==STATE_NORMAL)       
 	    m_pOldMine->uState=STATE_EMPTY;	
		
		Invalidate(FALSE);
	}

	else
	{//鼠标点击非雷区
       m_uBtnState=BUTTON_CLICK;
       Invalidate();
	}	
	CWnd::OnLButtonDown(nFlags, point);
}



BOOL CMineWnd::IsMine(UINT row, UINT col)
{
	if(m_pMines[row][col].uAttrib==ATTRIB_MINE)
        return TRUE;
	else
		return FALSE;
}

UINT CMineWnd::GetAroundNum(UINT row, UINT col)
{//获取相邻8个区域的雷数
    m_uFlagNum=0;//周围被标记为雷的模块数
	m_uDICEYNum=0;//周围被标记为问号的模块数
	UINT i,j;
	UINT around=0;
	UINT minRow=(row==0)? 0:row-1;
	UINT maxRow=row+2;
	UINT minCol=(col==0)? 0:col-1;
	UINT maxCol=col+2;
    
	for (i=minRow;i<maxRow;i++)
	{
		for (j=minCol;j<maxCol;j++)
		{            
			//判断该行列是否在雷区， 不在雷区则跳过
			if (!IsInMineArea(i,j)) continue;
			//判断属性是否为雷方块，是则自增
			if(m_pMines[i][j].uAttrib==ATTRIB_MINE) around++;
		    //周围被标记过的模块数，以后用作左右键同时弹起
			if (m_pMines[i][j].uOldState==STATE_FLAG)
			m_uFlagNum++;
			if (m_pMines[i][j].uOldState==STATE_DICEY)
			m_uDICEYNum++;			
		}
	}
  return around;
}

void CMineWnd::ExpandMines(UINT row, UINT col)
{//雷方块拓展
   	UINT i,j;
	UINT minRow=(row==0)? 0:row-1;
	UINT maxRow=row+2;
	UINT minCol=(col==0)? 0:col-1;
	UINT maxCol=col+2;
    UINT around=GetAroundNum(row,col);
    
	m_pMines[row][col].uState=15-around;
    m_pMines[row][col].uOldState=15-around;
	m_pMines[row][col].uAttrib=ATTRIB_EMPTY;

//打开该区域，重绘
    Invalidate();
//对周围一个雷都没有的空白区域
	if (around==0)
	{
		for (i=minRow;i<maxRow;i++)
		{
			for (j=minCol;j<maxCol;j++)
			{
				//对于周围可以拓展的区域进行拓展
				if (!(i==row&&j==col)&&(m_pMines[i][j].uState==STATE_NORMAL)&&(m_pMines[i][j].uAttrib!=ATTRIB_MINE))
				{
					if (!IsInMineArea(i,j)) continue;
					ExpandMines(i,j);
				}
			}
		}
	}

}

BOOL CMineWnd::Victory()
{//胜利判断并处理
	UINT i,j;
	//检测是否胜利
	for (i=0;i<m_uYNum;i++)
	{
		for (j=0;j<m_uXNum;j++)
		{
			if (m_pMines[i][j].uState==STATE_NORMAL) return FALSE;
			if (m_pMines[i][j].uState==STATE_DICEY) return FALSE;	
		}
	}
    //如果胜利则作胜利处理
	m_uBtnState=BUTTON_VICTORY;
	m_uGameState=GS_VICTORY;

	if (m_uTimer!=0)
	{//将定时器销毁
		KillTimer(ID_TIMER_EVENT);
		m_uTimer=0;
	}
	Invalidate();
//////////////创建破记录对话框
	LoadConfig();	
	if (m_uXNum==PRIMARY_XNUM&&m_uSpendTime<m_uuPrimary)	
	{
       CNEWRECORD nemrecord;
       nemrecord.DoModal();
  //     nemrecord.UpdateData();
       m_sszPrimary=nemrecord.m_newname;
       m_uuPrimary=m_uSpendTime;
	   SaveConfig();
	} 	
	if (m_uXNum==SECONDRY_XNUM&&m_uSpendTime<m_uuSecond)
	{
        CNEWRECORD nemrecord;
		nemrecord.DoModal();
   //     nemrecord.UpdateData();
        m_sszSecond=nemrecord.m_newname;
		m_uuSecond=m_uSpendTime;
		SaveConfig();
	}  
	if (m_uXNum==ADVANCE_XNUM&&m_uSpendTime<m_uuAdvance)
	{   
        CNEWRECORD nemrecord;
		nemrecord.DoModal();
      //  nemrecord.UpdateData();
        m_sszAdvance=nemrecord.m_newname;
        m_uuAdvance=m_uSpendTime;
		SaveConfig();
	}
    return TRUE;
}

void CMineWnd::Dead(UINT row, UINT col)
{//失败处理

    m_pMines[row][col].uState=STATE_BLAST;
    m_pMines[row][col].uOldState=STATE_BLAST;

	m_uBtnState=BUTTON_DEAD;
	m_uGameState=GS_DEAD;
    
	for (UINT i=0;i<m_uYNum;i++)
	{/////////////找出标志错误的模块
		for (UINT j=0;j<m_uXNum;j++)
		{/////////////找出标志错误的模块
			if ((m_pMines[i][j].uOldState==STATE_FLAG)&&(m_pMines[i][j].uAttrib==ATTRIB_EMPTY))
			{
				m_pMines[i][j].uOldState=STATE_ERROR;
				m_pMines[i][j].uState=STATE_ERROR;
			}
			if ((m_pMines[i][j].uOldState==STATE_NORMAL)&&(m_pMines[i][j].uAttrib==ATTRIB_MINE))
			{
				m_pMines[i][j].uOldState=STATE_MINE;
				m_pMines[i][j].uState=STATE_MINE;
			}
		}
	}

	if (m_uTimer!=0)
	{//将定时器销毁
		KillTimer(ID_TIMER_EVENT);
		m_uTimer=0;
	}
	Invalidate();
}

void CMineWnd::DrawMineArea(CPaintDC &dc)
{   
	UINT i,j;
	CDC cdd;
	cdd.CreateCompatibleDC(&dc);//使得这个设备与dc兼容
	cdd.SelectObject(&m_bmpMine);//使得这个设备与内存资源关联

	for (i=0;i<m_uYNum;i++)
	{//根据区域的雷的方块状态拷贝相应的图像到指定的区域
		for (j=0;j<m_uXNum;j++)
		{
			dc.StretchBlt(MINEAREA_FRAME_X+16*j,MINEAREA_FRAME_Y+16*i,16,16,&cdd,0,16*m_pMines[i][j].uState,16,16,SRCCOPY);
            //SRCCOPY表示直接拷贝
		}
	}

}

void CMineWnd::OnPaint() 
{
	 // device context for painting
	 
    m_brsBG=CBrush::FromHandle((HBRUSH)GetStockObject(LTGRAY_BRUSH));
	//刷背景的画刷，必须在此处赋值，否则第二次刷的时候就变成白色的了。
	//不知是什么原因。可能FillRect（）执行完毕后会自动释放掉画刷，所以第二次
	//再调用时候必须再次赋值
	CPaintDC dc(this);//屏幕显示设备
	CDC dcMemory;//内存设备

	CBitmap bitmap;
	if (!dc.IsPrinting())//判断是不是使用打印机来进行绘制工作
	{
		if (dcMemory.CreateCompatibleDC(&dc))//使内存设备与dc设备兼容
		{
			if (bitmap.CreateCompatibleBitmap(&dc,m_rcClient.right,m_rcClient.bottom))
			{//使bitmap与显示设备兼容
               
				dcMemory.SelectObject(&bitmap);//内存设备选择物件
				dcMemory.FillRect(&m_rcClient,m_brsBG);//绘制背景框,刷灰画布

				DrawButton((CPaintDC&)dcMemory);//笑脸按钮绘图
				DrawNumber((CPaintDC&)dcMemory);//数字绘图（计时器和剩余雷数字）
				DrawShell((CPaintDC&)dcMemory);//3D效果外壳
	     		DrawMineArea((CPaintDC&)dcMemory);//雷区绘图

				dc.BitBlt(m_rcClient.left,m_rcClient.top,m_rcClient.right,m_rcClient.bottom,&dcMemory,0,0,SRCCOPY);
				//将内存设备的内容拷贝到显示设备
				//BitBlt()将一个物件某个区域的图像拷贝到另外一个物件的某个区域中去
				//StretchBlt（）与BitBlt()基本相同。当目标区域不等于源图像时，该函数将进行镜面压缩使之匹配。
				bitmap.DeleteObject();

			}
		}
	}
	// Do not call CWnd::OnPaint() for painting messages
}

void CMineWnd::DrawButton(CPaintDC &dc)
{
     CDC cdc;
	 cdc.CreateCompatibleDC(&dc);
	 cdc.SelectObject(&m_bmpButton);
	 dc.StretchBlt(m_uBtnRect[0],16,24,24,&cdc,0,24*m_uBtnState,24,24,SRCCOPY);
	 dc.Draw3dRect(m_uBtnRect[0]-1,15,26,26,m_clrDark,m_clrDark);
}

void CMineWnd::DrawShell(CPaintDC &dc)
{

     dc.FillSolidRect(0,0,m_uShellRcX[0],LINE_WIDTH_0,RGB(255,255,255));//画白条线
	 dc.FillSolidRect(0,0,LINE_WIDTH_0,m_uShellRcY[0],RGB(255,255,255));//顶部和左部分别画白条

	 dc.Draw3dRect(SHELL_S_START_X,SHELL_S_START_Y,m_uShellRcX[1],SHELL_S_H,m_clrDark,RGB(255,255,255));
	 dc.Draw3dRect(SHELL_S_START_X+1,SHELL_S_START_Y+1,m_uShellRcX[1]-2,SHELL_S_H-2,m_clrDark,RGB(255,255,255));
     //画小的外壳。Draw3dRect（）默认画出来的立体边框宽度是1，所以画两次使立体边框宽度为2

     dc.Draw3dRect(SHELL_L_START_X,SHELL_L_START_Y,m_uShellRcX[1],m_uShellRcY[1],m_clrDark,RGB(255,255,255));
	 dc.Draw3dRect(SHELL_L_START_X+1,SHELL_L_START_Y+1,m_uShellRcX[1]-2,m_uShellRcY[1]-2,m_clrDark,RGB(255,255,255));
 	 dc.Draw3dRect(SHELL_L_START_X+2,SHELL_L_START_Y+2,m_uShellRcX[1]-4,m_uShellRcY[1]-4,m_clrDark,RGB(255,255,255));
	 //画大的外壳
}

void CMineWnd::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rctime(17,16,56,39);//m_uNumRect[0]=17;

	if (nIDEvent==m_uTimer)
	{//数字显示定时器
       if(m_WndActive)
	   { 
		   m_uSpendTime++;
		   InvalidateRect(rctime);
           if (m_bSoundful)
	          PlaySound(MAKEINTRESOURCE(IDR_WAVE_TIME),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
		      //或者SndPlaySound("c:\sound\music.wav",SND_ASYNC)		   
	   }
	}
	else
	{
    	CWnd::OnTimer(nIDEvent);
	}	
}

void CMineWnd::DrawNumber(CPaintDC &dc)
{
//     m_uNumRect[0]=17;
//     m_uNumRect[1]=1+2*(MINE_AREA_LEFT+m_uXNum*MINE_WIDTH/2)-57;
   CDC dcMemory;
   dcMemory.CreateCompatibleDC(&dc);
   dcMemory.SelectObject(&m_bmpNumber);
   //绘制数字图像的3D外框
   dc.Draw3dRect(16,15,41,25,m_clrDark,RGB(255,255,255));//绘制雷数目数字模块外框
   dc.Draw3dRect(m_uNumRect[1]-1,15,41,25,m_clrDark,RGB(255,255,255));//绘制计时数字模块外框

   int num,num1,num2;
   //绘制计时数字图像，分别绘制时间的百位， 十位， 个位数字
   m_uSpendTime=m_uSpendTime%1000;
   num=m_uSpendTime/100;
   dc.StretchBlt(m_uNumRect[0],16,13,23,&dcMemory,0,276-23*(num+1),13,23,SRCCOPY);
   num=(m_uSpendTime-num*100)/10;
   dc.StretchBlt(m_uNumRect[0]+13,16,13,23,&dcMemory,0,276-23*(num+1),13,23,SRCCOPY);
   num=m_uSpendTime%10;
   dc.StretchBlt(m_uNumRect[0]+26,16,13,23,&dcMemory,0,276-23*(num+1),13,23,SRCCOPY);

   //绘制雷数目图像，分别绘制时间的百位， 十位， 个位数字
   num=m_nLeaveNum/100;
   num1=(m_nLeaveNum-num*100)/10;
   num2=m_nLeaveNum%10;

   if (m_nLeaveNum>=0)
   { 
     num=m_nLeaveNum/100;
     num1=(m_nLeaveNum-num*100)/10;
     num2=m_nLeaveNum%10;
     dc.StretchBlt(m_uNumRect[1],16,13,23,&dcMemory,0,276-23*(num+1),13,23,SRCCOPY);
     dc.StretchBlt(m_uNumRect[1]+13,16,13,23,&dcMemory,0,276-23*(num1+1),13,23,SRCCOPY); 
     dc.StretchBlt(m_uNumRect[1]+26,16,13,23,&dcMemory,0,276-23*(num2+1),13,23,SRCCOPY);
   }
   else
   {
     int tt=0-m_nLeaveNum;
     num=tt/100;
     num1=(tt-num*100)/10;
     num2=tt%10;
     dc.StretchBlt(m_uNumRect[1],16,13,23,&dcMemory,0,0,13,23,SRCCOPY);//直接画负号
     dc.StretchBlt(m_uNumRect[1]+13,16,13,23,&dcMemory,0,276-23*(num1+1),13,23,SRCCOPY); 
     dc.StretchBlt(m_uNumRect[1]+26,16,13,23,&dcMemory,0,276-23*(num2+1),13,23,SRCCOPY);  
   }
}


void CMineWnd::LoadBitmap()       //与类的对象函数不同，它不带任何参数
{
   //释放以前的关联资源
	 m_bmpButton.DeleteObject();//雷位图
     m_bmpNumber.DeleteObject();//数字位图
     m_bmpMine.DeleteObject();//笑脸按钮位图

	 //根据用户选项判断载入哪种位图资源（彩色/黑白）
     if (m_bColorful)
     {
     m_bmpButton.LoadBitmap(IDB_BTN_COLOR);
     m_bmpNumber.LoadBitmap(IDB_NUM_COLOR);
     m_bmpMine.LoadBitmap(IDB_MINE_COLOR);
	 m_clrDark=RGB(128,128,128);
     }
	 else		 
	 {
	 m_bmpButton.LoadBitmap(IDB_BTN_GRAY);
     m_bmpNumber.LoadBitmap(IDB_NUM_GRAY);
     m_bmpMine.LoadBitmap(IDB_MINE_GRAY);
     m_clrDark=RGB(0,0,0);
	 }
}

void CMineWnd::OnHeroTable() 
{
	// TODO: Add your command handler code here
	LoadConfig();
    CHEROLIST heroList;
    heroList.m_szPrimary=m_sszPrimary;
    heroList.m_szSecond=m_sszSecond;
    heroList.m_szAdvance=m_sszAdvance;
    heroList.m_uPrimary=m_uuPrimary;
    heroList.m_uSecond=m_uuSecond;
    heroList.m_uAdvance=m_uuAdvance;
//	heroList.UpdateData(FALSE);//自动调用CHEROLIST::DoDataExchange()将数据从数据成员传给相应的控件
     if (heroList.DoModal()==IDOK)
    {
	  m_sszPrimary=heroList.m_szPrimary;
	  m_sszSecond=heroList.m_szSecond;
	  m_sszAdvance=heroList.m_szAdvance;
      m_uuPrimary=heroList.m_uPrimary;
      m_uuSecond=heroList.m_uSecond;
      m_uuAdvance=heroList.m_uAdvance;
	  SaveConfig();
   }
	 
 }

void CMineWnd::SaveConfig()
{
	//________获取本地目录
	char exeFullPath[MAX_PATH];
	CString strPath;
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);//获取当前运行程序模块所在的目录路径
	//第一个参数指向目标模块，NULL表示获取当前目标模块
	//exeFullPath用作返回路径存储区域
	//表示存贮区域的大小
    strPath=CString(exeFullPath);
	strPath=strPath.Left(strPath.ReverseFind('\\'));//从左到右表示逆向寻找，返回脚标
	strPath+="\\config.ini";

	//雷区行列数
//	CString strXNum,strYNum;
	//雷数 选择级别
//	CString strMineNum, strLevel;
	//记录保持分数
	CString strPrimary, strSecond, strAdvance;
	//记录保持者
	CString strPrimaryHolder, strSecondHolder,strAdvanceHolder;
	//其他配置
//	CString strMarkful,strColorful,strSoundful;//strMarkful判断是否右键能用问号？标记

//	strXNum.Format("%d",m_uXNum);
//	strYNum.Format("%d",m_uYNum);

//	strMineNum.Format("%d",m_uMineNum);
//	strLevel.Format("%d",m_uLevel);

	strPrimary.Format("%d",m_uuPrimary);
	strSecond.Format("%d",m_uuSecond);
	strAdvance.Format("%d",m_uuAdvance);

/*	strPrimaryHolder.Format("%s",m_sszPrimary);
	strSecondHolder.Format("%s",m_sszSecond);
	strAdvanceHolder.Format("%s",m_sszAdvance);
*/
    strPrimaryHolder=m_sszPrimary;
	strSecondHolder=m_sszSecond;
	strAdvanceHolder=m_sszAdvance;


//	strMarkful.Format("%d",m_bMarkful);
//	strColorful.Format("%d",m_bColorful);
//	strSoundful.Format("%d",m_bSoundful);

//	WritePrivateProfileString("WINDOW","XNum",strXNum,strPath);	//ini写操作函数
	//"WINDOW"文件中的一个字段名
	//"XNum"变量名
	//strXNum变量的值
	//strPath完整的ini文件名
//	WritePrivateProfileString("WINDOW","YNum",strYNum,strPath);

//	WritePrivateProfileString("MINE","MineNum",strMineNum,strPath);
//	WritePrivateProfileString("MINE","Level",strLevel,strPath);

	WritePrivateProfileString("SCORE","Primary",strPrimary,strPath);
	WritePrivateProfileString("SCORE","Second",strSecond,strPath);
	WritePrivateProfileString("SCORE","Advance",strAdvance,strPath);

	WritePrivateProfileString("HOLDER","PrimaryHolder",strPrimaryHolder,strPath);
	WritePrivateProfileString("HOLDER","SecondHolder",strSecondHolder,strPath);
	WritePrivateProfileString("HOLDER","AdvanceHolder",strAdvanceHolder,strPath);

//	WritePrivateProfileString("CONFIG","Markful",strMarkful,strPath);
//	WritePrivateProfileString("CONFIG","Colorful",strColorful,strPath);
//	WritePrivateProfileString("CONFIG","Soundful",strSoundful,strPath);


}

void CMineWnd::LoadConfig()
{
    //获取本地目录
	char exeFullPath[MAX_PATH];
	CString strPath;
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);
	strPath=CString(exeFullPath);
	strPath=strPath.Left(strPath.ReverseFind('\\'));
	strPath+="\\config.ini";
	
	//记录保持者姓名
	char strPrimaryHolder[10];
	char strSecondHolder[10];
	char strAdvanceHolder[10];

//	m_uXNum=GetPrivateProfileInt("WINDOW","XNum",10,strPath);
//	m_uXNum=GetPrivateProfileInt("WINDOW","YNum",10,strPath);

//	m_uMineNum=GetPrivateProfileInt("MINE","MineNum",10,strPath);
//	m_uLevel=GetPrivateProfileInt("MINE","Level",0,strPath);
    
	//不同级别记录用时
	m_uuPrimary=GetPrivateProfileInt("SCORE","Primary",999,strPath);
	m_uuSecond=GetPrivateProfileInt("SCORE","Second",999,strPath);
	m_uuAdvance=GetPrivateProfileInt("SCORE","Advance",999,strPath);

	//不同级别记录保持者的姓名
	GetPrivateProfileString("HOLDER","PrimaryHolder","匿名",strPrimaryHolder,10,strPath);
	GetPrivateProfileString("HOLDER","SecondHolder","匿名",strSecondHolder,10,strPath);
	GetPrivateProfileString("HOLDER","AdvanceHolder","匿名",strAdvanceHolder,10,strPath);
    //如果文件中没有前两个参数指定的字段名或键名，则将“匿名”赋给键名

//   strcpy(m_sszPrimary,strPrimaryHolder);//不可赋值。但是strcpy(strPrimaryHolder,m_sszPrimary)可以赋值，
	//因为CString对象只可以被Const Char*代替。 strcpy（char*, const char*）
	strcpy(m_sszPrimary.GetBuffer(10),strPrimaryHolder);
	strcpy(m_sszSecond.GetBuffer(10),strSecondHolder);
	strcpy(m_sszAdvance.GetBuffer(10),strAdvanceHolder);
	m_sszPrimary.ReleaseBuffer();
    m_sszSecond.ReleaseBuffer();
    m_sszAdvance.ReleaseBuffer();

//	m_bMarkful=GetPrivateProfileInt("CONFIG","Markful",0,strPath);
//	m_bColorful=GetPrivateProfileInt("CONFIG","Colorful",1,strPath);
//	m_bSoundful=GetPrivateProfileInt("CONFIG","Soundful",1,strPath);

}

void CMineWnd::InitGame()
{    
//    m_uBtnRect[0]=MINE_AREA_LEFT+m_uXNum*MINE_WIDTH/2-12;//笑脸的左上角和右下角X坐标
//   m_uBtnRect[1]=MINE_AREA_LEFT+m_uXNum*MINE_WIDTH/2+12;

	m_uGameState=0;//游戏状态复位(GS_WAIT==0)
//////////////////////刷屏重新开始
	UINT i,j;
	for (i=0;i<m_uYNum;i++)
	{
		for (j=0;j<m_uXNum;j++)
		{
        m_pMines[i][j].uOldState=STATE_NORMAL;
        m_pMines[i][j].uState=STATE_NORMAL;
		m_pMines[i][j].uRow=i;
        m_pMines[i][j].uCol=j;
        m_pMines[i][j].uAttrib=ATTRIB_EMPTY;
		}
	}

////////////////////判断时间种子是否处于启动状态
	if (m_uTimer)
	{
		KillTimer(ID_TIMER_EVENT);
		m_uTimer=0;
	}
	m_uSpendTime=0;

}



MINEWND* CMineWnd::GetMine(UINT x, UINT y)
{
    UINT i,j;
 	i=(y-MINEAREA_FRAME_Y)/16;	
	j=(x-MINEAREA_FRAME_X)/16;
	if (i<m_uYNum && j<m_uXNum)
     	return &m_pMines[i][j];//注意行列(j,i)与坐标（x,y）是正好相反的
	else
		return NULL;
}

void CMineWnd::OnLRBtnDown(UINT x, UINT y)
{	UINT i,j;
    UINT row=m_pOldMine->uRow;
	UINT col=m_pOldMine->uCol;
	UINT minRow=(row==0)? 0:row-1;
	UINT maxRow=row+2;
	UINT minCol=(col==0)? 0:col-1;
	UINT maxCol=col+2;

	if (m_pOldMine->uState==STATE_FLAG||m_pOldMine->uState==STATE_DICEY)
	 {//被标记过的模块	   
		 	for (i=minRow;i<maxRow;i++)
			{
	        	for (j=minCol;j<maxCol;j++)
				{
		        	//判断该行列是否在雷区， 不在雷区则跳过
		        	if (!IsInMineArea(i,j)||(i==row&&j==col)) continue;			   
		        	if(m_pMines[i][j].uState==STATE_NORMAL)
				    	m_pMines[i][j].uState=STATE_EMPTY;	
				}
			}
	 }       
	else //未被标记的模块
	{ 	for (i=minRow;i<maxRow;i++)
			{
	        	for (j=minCol;j<maxCol;j++)
				{
		        	if (!IsInMineArea(i,j)) continue;			   
		        	if(m_pMines[i][j].uState==STATE_NORMAL)
				    	m_pMines[i][j].uState=STATE_EMPTY;	
				}
			}
	}
}

void CMineWnd::DrawDownNum(MINEWND *P, UINT x)
{
     P->uAttrib=ATTRIB_EMPTY;
	 P->uState=15-x;
	 P->uOldState=15-x;
	 Invalidate();
}

BOOL CMineWnd::IsInMineArea(UINT x, UINT y)
{          
      if ( x<m_uYNum&&y<m_uXNum)	
           return TRUE;	 
	  else 
	       return FALSE;	      
}



//DEL void CMineWnd::OnUpdateSound(CCmdUI* pCmdUI) 
//DEL {
//DEL 	// TODO: Add your command update UI handler code here
//DEL 	pCmdUI->SetCheck(m_bSoundful);
//DEL }

//DEL void CMineWnd::OnUpdateColor(CCmdUI* pCmdUI) 
//DEL {
//DEL 	// TODO: Add your command update UI handler code here
//DEL     pCmdUI->SetCheck(m_bColorful);	
//DEL }

void CMineWnd::OnFileOpen() 
{
	// TODO: Add your command handler code here
    m_nLeaveNum=m_uMineNum;
	InitGame();
	SizeWindow();
	Invalidate();
}

void CMineWnd::OnRButtonUp(UINT nFlags, CPoint point) 
{/////////////////////只响应双键按下后弹起时的消息(右键先弹起的情况)
	// TODO: Add your message handler code here and/or call default
	if (m_uGameState==GS_DEAD||m_uGameState==GS_VICTORY)
        return;

	CRect rcBtn(m_uBtnRect[0],15,m_uBtnRect[1],39);//笑脸所在区
	CRect rcMineArea(MINE_AREA_LEFT,MINE_AREA_TOP,
		MINE_AREA_LEFT+m_uXNum*MINE_WIDTH,
        MINE_AREA_TOP+m_uYNum*MINE_HEIGHT);//雷区所在区域

     if (!rcMineArea.PtInRect(point))
     {//主要是为了实现左右键都按下时，拖动到外面松手后，笑脸能恢复原状
		 m_uBtnState=BUTTON_NORMAL;
		 m_bLRBtnDown=FALSE;
		 InvalidateRect(&rcBtn);
		 ReleaseCapture();
     }

	if (rcMineArea.PtInRect(point))
	{//点击雷区
		m_pOldMine=GetMine(point.x,point.y);
        if (!m_pOldMine)//判断鼠标是否击中雷块，没有则返回，跳出整个函数
	       return;

        if (m_bLRBtnDown)
		{/////////////////////////////////判断是否左右键一起按下
		   BOOL blast=FALSE;//是否雷块标志错误
		   UINT i,j;
           UINT row=m_pOldMine->uRow;
           UINT col=m_pOldMine->uCol;
 	       UINT minRow=(row==0)? 0:row-1;
           UINT maxRow=row+2;
           UINT minCol=(col==0)? 0:col-1;
	       UINT maxCol=col+2;
           UINT around=0;
           around=GetAroundNum(row,col);							
//////////////////////////////////////////////游戏初始化时为GS_WAIT状态
	    	if (m_uGameState==GS_WAIT)
			{
                m_uSpendTime=1;
		    	//启动定时器
			    m_uTimer=SetTimer(ID_TIMER_EVENT,1000,NULL);

		    	//布雷
			    LayMines(m_pOldMine->uRow,m_pOldMine->uCol);

			    //改变游戏状态为运行GS_RUN
		    	m_uGameState=GS_RUN;
			}	  	  
////////////////////////////////////////////////////////////////
	        if ((around==m_uFlagNum&&m_uDICEYNum==0)&&(m_pOldMine->uOldState!=STATE_NORMAL)&&(m_pOldMine->uOldState!=STATE_FLAG)&&(m_pOldMine->uOldState!=STATE_DICEY)) 		   
			{//如果点击的是已经挖过的模块 
		     // m_uDICEYNum;//周围被标记为问号的模块数
	           // m_uFlagNum周围被标记为雷Flag的模块数
			     //如果周围标志数等于雷数则打开周围所有块，即自动挖雷
			    for (i=minRow;i<maxRow;i++)
				{
				  for (j=minCol;j<maxCol;j++)
				  {
					if (!IsInMineArea(i,j)) continue;
		        	if(m_pMines[i][j].uOldState==STATE_NORMAL)
					{  
						if (m_pMines[i][j].uAttrib==ATTRIB_MINE)
						{/////////////////////////模块标志错误
							m_pMines[i][j].uState=STATE_BLAST;
                            m_pMines[i][j].uOldState=STATE_BLAST;
							blast=TRUE;//自动挖错
						}
						else //模块标志正确自动全部挖掉
						{
							UINT Aaround=GetAroundNum(i,j);
							if (Aaround==0) ExpandMines(i,j); 
							else
							{  m_pMines[i][j].uState=15-Aaround;
						       m_pMines[i][j].uOldState=15-Aaround;
							}
						} 
					}				  
				  }
				}
			    if (blast)//如果自动挖错则游戏结束
				{
					if (m_bSoundful)
					{
	                   PlaySound(MAKEINTRESOURCE(IDR_WAVE_BOMB),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
					   //或者SndPlaySound("c:\sound\music.wav",SND_ASYNC)
					}

					for (i=0;i<m_uYNum;i++)
					{/////////////找出标志错误的模块
						for (j=0;j<m_uXNum;j++)
						{/////////////找出标志错误的模块
							if ((m_pMines[i][j].uOldState==STATE_FLAG)&&(m_pMines[i][j].uAttrib==ATTRIB_EMPTY))
							{
							   m_pMines[i][j].uOldState=STATE_ERROR;
							   m_pMines[i][j].uState=STATE_ERROR;
							}
							if ((m_pMines[i][j].uOldState==STATE_NORMAL)&&(m_pMines[i][j].uAttrib==ATTRIB_MINE))
							{
							   m_pMines[i][j].uOldState=STATE_MINE;
							   m_pMines[i][j].uState=STATE_MINE;
							}
						
						}
					}

			    	m_uBtnState=BUTTON_DEAD;
	                m_uGameState=GS_DEAD;
	                if (m_uTimer!=0)
					{//将定时器销毁
		                KillTimer(ID_TIMER_EVENT);
	                	m_uTimer=0;
					}
	                Invalidate();
					ReleaseCapture();
					return;
				}			  			  
			}			
///////////////////////////////////////////////////////////////////////
	        else////如果左右点击的不是已经挖过的模块，则恢复双击之前的原状
			{
				  for (i=minRow;i<maxRow;i++)
				  {
					  for (j=minCol;j<maxCol;j++)
					  {
						 if (!IsInMineArea(i,j)) continue;
                         if(m_pMines[i][j].uOldState==STATE_NORMAL)						 
							m_pMines[i][j].uState=STATE_NORMAL;                            						 
					  }
				  }
		     
			}	
	    m_uBtnState=BUTTON_NORMAL;//改变笑脸状态为原状态
		m_bLRBtnDown=FALSE;
//		m_LRBtnDouble=TRUE;
		Invalidate(FALSE); 
		
	}
/////////////////////////////////////////////////
			   //2.4判断是否胜利
			 if(m_uGameState==GS_RUN)
			 {
			   if (Victory())
			   {
                 if (m_bSoundful)
				 {
	               PlaySound(MAKEINTRESOURCE(IDR_WAVE_VICTORY),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
				 //或者SndPlaySound("c:\sound\music.wav",SND_ASYNC)
				 }
				Invalidate(FALSE);
//				ReleaseCapture();
//				return;
			   }
			 }
}
	CWnd::OnRButtonUp(nFlags, point);
}

void CMineWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
		CRect rcMineArea(MINE_AREA_LEFT,MINE_AREA_TOP,
		MINE_AREA_LEFT+m_uXNum*MINE_WIDTH,
        MINE_AREA_TOP+m_uYNum*MINE_HEIGHT);//雷区所在区域
//////////////////////////////////////////////////////////////////////////////单键移动的情况
	if((nFlags==MK_LBUTTON)&&(m_LRBtnDouble==FALSE)&&(m_uGameState==GS_RUN||m_uGameState==GS_WAIT))
	{      
        m_pOldMine=GetMine(m_uOrigPoint.x,m_uOrigPoint.y);
        if (!m_pOldMine)//判断鼠标是否击中雷块，没有则返回，跳出整个函数
		{//从外界进入雷区的情况
			m_uOrigPoint=point;
		return;}

		m_pNewMine=GetMine(point.x,point.y);
        if (!m_pNewMine)
		{//从内部雷区移出的情况
			if (m_pOldMine->uOldState==STATE_NORMAL)           
			   m_pOldMine->uState=STATE_NORMAL;
		 Invalidate();
	     return;}

		if ((m_pNewMine->uRow!=m_pOldMine->uRow)||(m_pNewMine->uCol!=m_pOldMine->uCol)) 		
		{//在雷区内部移动的情况
           if (m_pOldMine->uOldState==STATE_NORMAL)           
			   m_pOldMine->uState=STATE_NORMAL;
           if (m_pNewMine->uOldState==STATE_NORMAL)
               m_pNewMine->uState=STATE_EMPTY;
		   m_uOrigPoint=point;
		}
	    else if (m_pOldMine->uOldState==STATE_NORMAL)           
		   m_pOldMine->uState=STATE_EMPTY;//使从外界进入雷区时比较连续

        Invalidate();
	}
////////////////////////////////////////////////////////双键移动的情况
    if (m_bLRBtnDown&&(m_uGameState==GS_RUN||m_uGameState==GS_WAIT))
    {	
        UINT i,j,row,col,minRow,maxRow,minCol,maxCol;
		
        m_pOldMine=GetMine(m_uOrigPoint.x,m_uOrigPoint.y);
        if (!m_pOldMine)//判断鼠标是否击中雷块，没有则返回，跳出整个函数
		{//从外界进入雷区的情况
			m_uOrigPoint=point;
		return;}

		m_pNewMine=GetMine(point.x,point.y);
        if (!m_pNewMine)
		{//从内部雷区移出的情况		   
            row=m_pOldMine->uRow;
            col=m_pOldMine->uCol;
 	        minRow=(row==0)? 0:row-1;
            maxRow=row+2;
            minCol=(col==0)? 0:col-1;
	        maxCol=col+2;
           for (i=minRow;i<maxRow;i++)
			{
			  for (j=minCol;j<maxCol;j++)
			  {
				if (!IsInMineArea(i,j)) continue;
		        if(m_pMines[i][j].uOldState==STATE_NORMAL)
				  m_pMines[i][j].uState=STATE_NORMAL;
			  }
		   }		   
			Invalidate();
	     return;}


		if ((m_pNewMine->uRow!=m_pOldMine->uRow)||(m_pNewMine->uCol!=m_pOldMine->uCol)) 		
		{//在雷区内部移动的情况          		  
            row=m_pOldMine->uRow;
            col=m_pOldMine->uCol;
 	        minRow=(row==0)? 0:row-1;
            maxRow=row+2;
            minCol=(col==0)? 0:col-1;
	        maxCol=col+2;          								  	  
			for (i=minRow;i<maxRow;i++)
			{
		     for (j=minCol;j<maxCol;j++)
			 {
			   if (!IsInMineArea(i,j)) continue;
		       if(m_pMines[i][j].uOldState==STATE_NORMAL)
				 m_pMines[i][j].uState=STATE_NORMAL;  			
			 }
			}		 
            row=m_pNewMine->uRow;
            col=m_pNewMine->uCol;
 	        minRow=(row==0)? 0:row-1;
            maxRow=row+2;
            minCol=(col==0)? 0:col-1;
	        maxCol=col+2; 
            for (i=minRow;i<maxRow;i++)
			{
		     for (j=minCol;j<maxCol;j++)
			 {
			   if (!IsInMineArea(i,j)) continue;
               if (m_pMines[i][j].uOldState==STATE_NORMAL)
                 m_pMines[i][j].uState=STATE_EMPTY; 			
			 }
			}
		   m_uOrigPoint=point;
		}
	    else 
		{		   		
            row=m_pOldMine->uRow;
            col=m_pOldMine->uCol;
 	        minRow=(row==0)? 0:row-1;
            maxRow=row+2;
            minCol=(col==0)? 0:col-1;
	        maxCol=col+2;          								  	  
			for (i=minRow;i<maxRow;i++)
			{
		     for (j=minCol;j<maxCol;j++)
			 {
			   if (!IsInMineArea(i,j)) continue;
		       if(m_pMines[i][j].uOldState==STATE_NORMAL)
				 m_pMines[i][j].uState=STATE_EMPTY; ///使从外界进入雷区时比较连续 			
			 }
			}
		}
	Invalidate();  		
    }
	CWnd::OnMouseMove(nFlags, point);
}

void CMineWnd::OnTag() 
{
	// TODO: Add your command handler code here
	m_bMarkful=!m_bMarkful;
	if (m_bMarkful)	
		GetMenu()->GetSubMenu(0)->CheckMenuItem(7,MF_BYPOSITION|MF_CHECKED);
	else
		GetMenu()->GetSubMenu(0)->CheckMenuItem(7,MF_BYPOSITION|MF_UNCHECKED);
}

void CMineWnd::OnExit() 
{
	// TODO: Add your command handler code here
	DestroyWindow();
}

//DEL  void CMineWnd::OnUpdateTag(CCmdUI* pCmdUI) 
//DEL  {
//DEL // 	// TODO: Add your command update UI handler code here
//DEL // 	  pCmdUI->SetCheck(m_bMarkful);
//DEL }

void CMineWnd::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{//
	//响应窗体active/deactive的函数
	CWnd::OnActivate(nState, pWndOther, bMinimized);
	
	// TODO: Add your message handler code here
	if (nState==WA_INACTIVE)
	   m_WndActive=FALSE;
	else
		m_WndActive=TRUE;	   
}
