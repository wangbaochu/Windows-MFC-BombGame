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
    m_uBtnState=BUTTON_NORMAL;//Ц����ʼ״̬

    m_sszPrimary=_T("����");
	m_sszSecond=_T("����");
    m_sszAdvance=_T("����"); 
/*	 m_bmpButton.LoadBitmap(IDB_BTN_COLOR);//��λͼ
     m_bmpNumber.LoadBitmap(IDB_NUM_COLOR);//����λͼ
     m_bmpMine.LoadBitmap(IDB_MINE_COLOR);//Ц����ťλͼ
*/
    
//     m_uBtnRect[0]=MINE_AREA_LEFT+m_uXNum*MINE_WIDTH/2-12;//Ц�������ϽǺ����½�X����
//     m_uBtnRect[1]=MINE_AREA_LEFT+m_uXNum*MINE_WIDTH/2+12;

     m_uGameState=GS_WAIT;//��ʼ��Ϸ״̬Ĭ��Ϊ��GS_WAIT==0��
     m_bSoundful=FALSE;
     m_bColorful=TRUE;
	 m_bMarkful=TRUE;
	 m_bLRBtnDown=FALSE;
	 m_LRBtnDouble=FALSE;//��ʶ������Ҽ��Ƿ�����ͬʱ���£���Ҫ��Ϊ�����������ʱ�ж��Ƿ��ڵ������ģ��
     m_WndActive=TRUE;//��OnActive�����б�ʶ�����Ƿ��ڼ���״̬���Ա�����Ƿ��ʱ
	 
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
//     m_uNumRect[1]=1+2*(MINE_AREA_LEFT+m_uXNum*MINE_WIDTH/2)-57;//��������������
//   m_uNumRect[1]=m_uXNum *MINE_WIDTH + LINE_WIDTH_0*3 + SIDE_WIDTH_0 + SIDE_WIDTH_1-57;
	 

     m_uLevel=1;//��¼ѡ��ļ���
     m_uTimer=0;//��ʱ����ʶ��ʼ��Ϊ0

     m_nLeaveNum=PRIMARY_MINENUM;//������ʾ�׵ĸ���
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

void CMineWnd::SizeWindow()//�ı䴰�ڴ�С�ĺ���
{
	//���㲻ͬ�ѶȵĴ��ڵĴ�С
    m_uWidth=DEFAULT_FRAME_X + m_uXNum *MINE_WIDTH + LINE_WIDTH_0*3 + SIDE_WIDTH_0 + SIDE_WIDTH_1;
	m_uHeight=DEFAULT_FRAME_Y + m_uYNum *MINE_HEIGHT + LINE_WIDTH_0*3 + SIDE_WIDTH_0*2 + SIDE_WIDTH_1 + SHELL_S_H;	

    m_uBtnRect[0]=MINE_AREA_LEFT+m_uXNum*MINE_WIDTH/2-12;//Ц�������ϽǺ����½�X����
    m_uBtnRect[1]=MINE_AREA_LEFT+m_uXNum*MINE_WIDTH/2+12;



    //�ڴ滭ͼ�������Ĵ�С
	m_rcClient.left=0;
    m_rcClient.top=0;
    m_rcClient.right=m_uWidth-DEFAULT_FRAME_X;	
    m_rcClient.bottom=m_uHeight-DEFAULT_FRAME_Y;

    //Ц�������ϽǺ����½�X����
    m_uBtnRect[0]=MINE_AREA_LEFT+m_uXNum*MINE_WIDTH/2-12;
    m_uBtnRect[1]=MINE_AREA_LEFT+m_uXNum*MINE_WIDTH/2+12;

	//��ά��ǵ��������
	 m_uShellRcX[0]=m_uXNum *MINE_WIDTH + LINE_WIDTH_0*3 + SIDE_WIDTH_0 + SIDE_WIDTH_1;
	 m_uShellRcX[1]=m_uXNum *MINE_WIDTH + LINE_WIDTH_0*2;
     m_uShellRcY[0]=m_uYNum *MINE_HEIGHT + LINE_WIDTH_0*3 + SIDE_WIDTH_0*2 + SIDE_WIDTH_1 + SHELL_S_H;
	 m_uShellRcY[1]=m_uYNum *MINE_HEIGHT + LINE_WIDTH_0*2;

     //����������ʾ����x�������
     m_uNumRect[0]=17;
     m_uNumRect[1]=1+2*(MINE_AREA_LEFT+m_uXNum*MINE_WIDTH/2)-57;



//	SetWindowPos(&wndTopMost, 0,0,m_uWidth,m_uHeight,SWP_NOZORDER|SWP_NOMOVE|SWP_NOCOPYBITS);
	// SetWindowPos�����ı䵱ǰ���ڵĴ�С



//	Invalidate();
}

void CMineWnd::OnBaseLevel() 
{
	// TODO: Add your command handler code here
	m_uXNum=PRIMARY_XNUM;//x��������׷�����Ŀm_uXNum
    m_uYNum=PRIMARY_YNUM;//y��������׷�����Ŀm_uYNum
	m_uMineNum=PRIMARY_MINENUM;
    m_nLeaveNum=PRIMARY_MINENUM;
	m_uLevel=1;//ѡ��ļ����¼
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
   	m_uLevel=2;//ѡ��ļ����¼
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
    m_uLevel=3;	//ѡ��ļ����¼
	m_uBtnState=BUTTON_NORMAL;			
	InitGame();
	SizeWindow();
    SetWindowPos(&wndTopMost, 0,0,m_uWidth,m_uHeight,SWP_NOZORDER|SWP_NOMOVE|SWP_NOCOPYBITS);
	Invalidate();
}

void CMineWnd::OnColor() 
{
	// TODO: Add your command handler code here
    
	m_bColorful=!m_bColorful;//�ñ����ɫ��ʾ����
	 if (m_bColorful)	
		GetMenu()->GetSubMenu(0)->CheckMenuItem(8,MF_BYPOSITION|MF_CHECKED);
	 else
		GetMenu()->GetSubMenu(0)->CheckMenuItem(8,MF_BYPOSITION|MF_UNCHECKED);
	LoadBitmap();//������д��λͼ���غ�������ʱ��ʾ��Ч��
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
	//�Ե�һ������Ϊ������ִ������Եڶ�������ʽ��ʾ����˼���������е���HH.EXE��
	//���������WINMINE.CHM������򿪸��ļ�����windows�Դ���ɨ����Ϸʹ���ֲ�
}

void CMineWnd::OnAbout() 
{
	// TODO: Add your command handler code here
	ShellAbout(this->m_hWnd,"ɨ�ס���������","wbc.wbc@163.com",NULL);
	//�ô��봴��һ����������Ϣ���ĶԻ���
}

void CMineWnd::LayMines(UINT row, UINT col)//����һ�ε��ʱ���ô˺���
{
	srand((unsigned)time(NULL));//�����漴����
	UINT i,j;
	for (UINT index=0;index< m_uMineNum;)
	{
		//ȡ�����
		i=rand()%m_uYNum;
		j=rand()%m_uXNum;
		
		if (i==row&&j==col) continue;//��һ������鲻���ף���row, col)����괫����������λ�ò���
		if (m_pMines[i][j].uAttrib!=ATTRIB_MINE)
		{
			m_pMines[i][j].uAttrib=ATTRIB_MINE;//�޸�����Ϊ��
			index++;
		}
	}
/////////////////////////////////////�޸�������������Ϊ����
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
	 CRect rcBtn(m_uBtnRect[0],15,m_uBtnRect[1],39);//Ц��������
	 CRect rcMineArea(MINE_AREA_LEFT,MINE_AREA_TOP,
		MINE_AREA_LEFT+m_uXNum*MINE_WIDTH,
        MINE_AREA_TOP+m_uYNum*MINE_HEIGHT);//������������
    
     if (!rcMineArea.PtInRect(point))
     {//��Ҫ��Ϊ��ʵ�����Ҽ�������ʱ���϶����������ֺ�Ц���ָܻ�ԭ״
		 m_uBtnState=BUTTON_NORMAL;
		 m_bLRBtnDown=FALSE;
		 InvalidateRect(&rcBtn);
		 ReleaseCapture();
     }

/////////////////////////////////////////////////////////////////
//////////�жϵ�ǰ����λ��
	if (rcBtn.PtInRect(point))
	{//���Ц��
        m_uBtnState=BUTTON_NORMAL;//�ı�Ц��״̬ΪBUTTON_NORMAL
        m_nLeaveNum=m_uMineNum; 
		InitGame();
		Invalidate(FALSE);
	}
	else if (rcMineArea.PtInRect(point))
	{//�������
//		CString value;
		UINT around=0;//��¼��Χ�׵���Ŀ		
////////////////////////////////////���ݲ�ͬ����Ϸ״̬������
		switch(m_uGameState)
		{//��Ϸ����״̬
		case GS_WAIT: case GS_RUN:	
			
		m_pOldMine=GetMine(point.x,point.y);
        if (!m_pOldMine)//�ж�����Ƿ�����׿飬û���򷵻أ�������������
	       return;							
//////////////////////////////////////////////��Ϸ��ʼ��ʱΪGS_WAIT״̬
		if (m_uGameState==GS_WAIT)
		{
            m_uSpendTime=1;
			//������ʱ��
			m_uTimer=SetTimer(ID_TIMER_EVENT,1000,NULL);

			//����
			LayMines(m_pOldMine->uRow,m_pOldMine->uCol);

			//�ı���Ϸ״̬Ϊ����GS_RUN
			m_uGameState=GS_RUN;
		}
////////////////////////////////////////////////////�ж��Ƿ����Ҽ�һ����
        if (m_bLRBtnDown)
        {//�ж��Ƿ����Ҽ�һ����
		   BOOL blast=FALSE;//�Ƿ��׿��־����
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
		   {//�����������Ѿ��ڹ���ģ�� 
		     // m_uDICEYNum;//��Χ�����Ϊ�ʺŵ�ģ����
	           // m_uFlagNum��Χ�����Ϊ��Flag��ģ����
			     //�����Χ��־���������������Χ���п飬���Զ�����
			    for (i=minRow;i<maxRow;i++)
				{
				  for (j=minCol;j<maxCol;j++)
				  {
					if (!IsInMineArea(i,j)) continue;
		        	if(m_pMines[i][j].uOldState==STATE_NORMAL)
					{  
						if (m_pMines[i][j].uAttrib==ATTRIB_MINE)
						{/////////////////////////ģ���־����
							m_pMines[i][j].uState=STATE_BLAST;
                            m_pMines[i][j].uOldState=STATE_BLAST;
							blast=TRUE;//�Զ��ڴ�
						}
						else //ģ���־��ȷ�Զ�ȫ���ڵ�
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
			    if (blast)//����Զ��ڴ�����Ϸ����
				{
					if (m_bSoundful)
					{
	                   PlaySound(MAKEINTRESOURCE(IDR_WAVE_BOMB),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
					   //����SndPlaySound("c:\sound\music.wav",SND_ASYNC)
					}

					for (i=0;i<m_uYNum;i++)
					{/////////////�ҳ���־�����ģ��
						for (j=0;j<m_uXNum;j++)
						{/////////////�ҳ���־�����ģ��
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
					{//����ʱ������
		                KillTimer(ID_TIMER_EVENT);
	                	m_uTimer=0;
					}
	                Invalidate();
					ReleaseCapture();
					return;
				}			  			  
		   }			
///////////////////////////////////////////////////////////////////////
	       else////������ҵ���Ĳ����Ѿ��ڹ���ģ�飬��ָ�˫��֮ǰ��ԭ״
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
////////////////////////////////////�ж�����˫���Ѿ�����������Ϊ�����������
		 if ((m_pOldMine->uOldState==STATE_NORMAL)&&(m_LRBtnDouble==FALSE))//m_LRBtnDouble=FALSE��ʾ֮ǰû�����Ҽ�ͬʱ����
				{//2.����������Ϊ������δ����ǲŴ�
					//2.1���������Ϊ��������
					if (IsMine(m_pOldMine->uRow,m_pOldMine->uCol))
					{
                        if (m_bSoundful)
						{
	                      PlaySound(MAKEINTRESOURCE(IDR_WAVE_BOMB),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
						  //����SndPlaySound("c:\sound\music.wav",SND_ASYNC)
						}
						Dead(m_pOldMine->uRow,m_pOldMine->uCol);
						ReleaseCapture();
						return;
					}

					//2.2���������ȡ��Χ�׵���Ŀ
					around=GetAroundNum(m_pOldMine->uRow,m_pOldMine->uCol);
					//2.3���Ϊ����������չ������򿪸�������ʾ��Χ������Ŀ
					if (around==0) ExpandMines(m_pOldMine->uRow,m_pOldMine->uCol);
					else DrawDownNum(m_pOldMine,around);
				}
		    //	m_LRBtnDouble=FALSE;//˫������������������ûִ�У����踴λ���´�ֱ�ӵ���������ִ��

			   //2.4�ж��Ƿ�ʤ��
			   if (Victory())
			   {
                 if (m_bSoundful)
				 {
	               PlaySound(MAKEINTRESOURCE(IDR_WAVE_VICTORY),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
				 //����SndPlaySound("c:\sound\music.wav",SND_ASYNC)
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
		m_uBtnState=BUTTON_NORMAL;//Ц����ť����ͼ��ָ�ԭ״̬״̬
		Invalidate(FALSE);
	}

	else
	{//���������
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

	//����������
	CRect rcMineArea(MINE_AREA_LEFT,MINE_AREA_TOP,
		MINE_AREA_LEFT+m_uXNum*MINE_WIDTH,
        MINE_AREA_TOP+m_uYNum*MINE_HEIGHT);

	if (rcMineArea.PtInRect(point))
	{//�������
		//if (m_uGameState==GS_RUN)
	
		m_pOldMine=GetMine(point.x,point.y);
		if (!m_pOldMine) return;

		if ((m_uGameState==GS_RUN||m_uGameState==GS_WAIT)&&nFlags==(MK_LBUTTON|MK_RBUTTON))
		{// �жϵ�ǰ״̬�Ƿ�Ϊ�������ͬʱ����
		    m_uBtnState=BUTTON_CLICK;
			m_bLRBtnDown=TRUE;//�ñ�����Ϊ�˷����������OnRButtonUp���������ж��Ƿ�ͬʱ����
			OnLRBtnDown(m_pOldMine->uRow,m_pOldMine->uCol);
			m_LRBtnDouble=TRUE;////����˫����ΪTRUE���������ִ������
		}

        else
			{
			  switch(m_pOldMine->uState)
			  {
		    	case STATE_NORMAL:
			    	m_pOldMine->uState=STATE_FLAG;
			    	m_pOldMine->uOldState=STATE_FLAG;
					m_nLeaveNum--;//ʣ���׵���Ŀ
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

	//Ц����ť��������
	CRect rcBtn(m_uBtnRect[0],15,m_uBtnRect[1],39);
	//����������
	CRect rcMineArea(MINE_AREA_LEFT,MINE_AREA_TOP,
		MINE_AREA_LEFT+m_uXNum*MINE_WIDTH,
        MINE_AREA_TOP+m_uYNum*MINE_HEIGHT);

      m_uOrigPoint=point;//������������λ�ã�������ƶ������н����ж�
	 SetCapture(); //������겶���������Ϣ�����ϵ������������ֺ�����Ӧ�����Ϣ����

	if (rcBtn.PtInRect(point))
	{//�����Ц��
        m_uBtnState=BUTTON_DOWN;//�ı�Ц��״̬Ϊ����
//		InvalidateRect(rcBtn);
		Invalidate(FALSE);
	}
/////////////////////////////////////////////
	else if (rcMineArea.PtInRect(point))
	{//���������
      //  m_uOrigPoint=point;
        m_pOldMine=GetMine(point.x,point.y);
     	if (!m_pOldMine) return;
        m_uBtnState=BUTTON_CLICK;//�ı�Ц��״̬Ϊ�����ġ�
        m_LRBtnDouble=FALSE;//����˫����ΪTRUE���������ִ�����ס��˴���λ���´����ֱ�ӵ�������ʱ���ִ������

		if (nFlags==(MK_LBUTTON|MK_RBUTTON))
		{// �жϵ�ǰ״̬�Ƿ�Ϊ�������ͬʱ����
			m_bLRBtnDown=TRUE;//�ñ�����Ϊ�˷����������OnLButtonUp���������ж��Ƿ�ͬʱ����
			OnLRBtnDown(m_pOldMine->uRow,m_pOldMine->uCol);
			m_LRBtnDouble=TRUE;////����˫����ΪTRUE���������ִ�����ס����渴λ���´����ֱ�ӵ�������ʱ���ִ������
		}   
		
        else if (m_pOldMine->uState==STATE_NORMAL)       
 	    m_pOldMine->uState=STATE_EMPTY;	
		
		Invalidate(FALSE);
	}

	else
	{//�����������
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
{//��ȡ����8�����������
    m_uFlagNum=0;//��Χ�����Ϊ�׵�ģ����
	m_uDICEYNum=0;//��Χ�����Ϊ�ʺŵ�ģ����
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
			//�жϸ������Ƿ��������� ��������������
			if (!IsInMineArea(i,j)) continue;
			//�ж������Ƿ�Ϊ�׷��飬��������
			if(m_pMines[i][j].uAttrib==ATTRIB_MINE) around++;
		    //��Χ����ǹ���ģ�������Ժ��������Ҽ�ͬʱ����
			if (m_pMines[i][j].uOldState==STATE_FLAG)
			m_uFlagNum++;
			if (m_pMines[i][j].uOldState==STATE_DICEY)
			m_uDICEYNum++;			
		}
	}
  return around;
}

void CMineWnd::ExpandMines(UINT row, UINT col)
{//�׷�����չ
   	UINT i,j;
	UINT minRow=(row==0)? 0:row-1;
	UINT maxRow=row+2;
	UINT minCol=(col==0)? 0:col-1;
	UINT maxCol=col+2;
    UINT around=GetAroundNum(row,col);
    
	m_pMines[row][col].uState=15-around;
    m_pMines[row][col].uOldState=15-around;
	m_pMines[row][col].uAttrib=ATTRIB_EMPTY;

//�򿪸������ػ�
    Invalidate();
//����Χһ���׶�û�еĿհ�����
	if (around==0)
	{
		for (i=minRow;i<maxRow;i++)
		{
			for (j=minCol;j<maxCol;j++)
			{
				//������Χ������չ�����������չ
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
{//ʤ���жϲ�����
	UINT i,j;
	//����Ƿ�ʤ��
	for (i=0;i<m_uYNum;i++)
	{
		for (j=0;j<m_uXNum;j++)
		{
			if (m_pMines[i][j].uState==STATE_NORMAL) return FALSE;
			if (m_pMines[i][j].uState==STATE_DICEY) return FALSE;	
		}
	}
    //���ʤ������ʤ������
	m_uBtnState=BUTTON_VICTORY;
	m_uGameState=GS_VICTORY;

	if (m_uTimer!=0)
	{//����ʱ������
		KillTimer(ID_TIMER_EVENT);
		m_uTimer=0;
	}
	Invalidate();
//////////////�����Ƽ�¼�Ի���
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
{//ʧ�ܴ���

    m_pMines[row][col].uState=STATE_BLAST;
    m_pMines[row][col].uOldState=STATE_BLAST;

	m_uBtnState=BUTTON_DEAD;
	m_uGameState=GS_DEAD;
    
	for (UINT i=0;i<m_uYNum;i++)
	{/////////////�ҳ���־�����ģ��
		for (UINT j=0;j<m_uXNum;j++)
		{/////////////�ҳ���־�����ģ��
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
	{//����ʱ������
		KillTimer(ID_TIMER_EVENT);
		m_uTimer=0;
	}
	Invalidate();
}

void CMineWnd::DrawMineArea(CPaintDC &dc)
{   
	UINT i,j;
	CDC cdd;
	cdd.CreateCompatibleDC(&dc);//ʹ������豸��dc����
	cdd.SelectObject(&m_bmpMine);//ʹ������豸���ڴ���Դ����

	for (i=0;i<m_uYNum;i++)
	{//����������׵ķ���״̬������Ӧ��ͼ��ָ��������
		for (j=0;j<m_uXNum;j++)
		{
			dc.StretchBlt(MINEAREA_FRAME_X+16*j,MINEAREA_FRAME_Y+16*i,16,16,&cdd,0,16*m_pMines[i][j].uState,16,16,SRCCOPY);
            //SRCCOPY��ʾֱ�ӿ���
		}
	}

}

void CMineWnd::OnPaint() 
{
	 // device context for painting
	 
    m_brsBG=CBrush::FromHandle((HBRUSH)GetStockObject(LTGRAY_BRUSH));
	//ˢ�����Ļ�ˢ�������ڴ˴���ֵ������ڶ���ˢ��ʱ��ͱ�ɰ�ɫ���ˡ�
	//��֪��ʲôԭ�򡣿���FillRect����ִ����Ϻ���Զ��ͷŵ���ˢ�����Եڶ���
	//�ٵ���ʱ������ٴθ�ֵ
	CPaintDC dc(this);//��Ļ��ʾ�豸
	CDC dcMemory;//�ڴ��豸

	CBitmap bitmap;
	if (!dc.IsPrinting())//�ж��ǲ���ʹ�ô�ӡ�������л��ƹ���
	{
		if (dcMemory.CreateCompatibleDC(&dc))//ʹ�ڴ��豸��dc�豸����
		{
			if (bitmap.CreateCompatibleBitmap(&dc,m_rcClient.right,m_rcClient.bottom))
			{//ʹbitmap����ʾ�豸����
               
				dcMemory.SelectObject(&bitmap);//�ڴ��豸ѡ�����
				dcMemory.FillRect(&m_rcClient,m_brsBG);//���Ʊ�����,ˢ�һ���

				DrawButton((CPaintDC&)dcMemory);//Ц����ť��ͼ
				DrawNumber((CPaintDC&)dcMemory);//���ֻ�ͼ����ʱ����ʣ�������֣�
				DrawShell((CPaintDC&)dcMemory);//3DЧ�����
	     		DrawMineArea((CPaintDC&)dcMemory);//������ͼ

				dc.BitBlt(m_rcClient.left,m_rcClient.top,m_rcClient.right,m_rcClient.bottom,&dcMemory,0,0,SRCCOPY);
				//���ڴ��豸�����ݿ�������ʾ�豸
				//BitBlt()��һ�����ĳ�������ͼ�񿽱�������һ�������ĳ��������ȥ
				//StretchBlt������BitBlt()������ͬ����Ŀ�����򲻵���Դͼ��ʱ���ú��������о���ѹ��ʹ֮ƥ�䡣
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

     dc.FillSolidRect(0,0,m_uShellRcX[0],LINE_WIDTH_0,RGB(255,255,255));//��������
	 dc.FillSolidRect(0,0,LINE_WIDTH_0,m_uShellRcY[0],RGB(255,255,255));//�������󲿷ֱ𻭰���

	 dc.Draw3dRect(SHELL_S_START_X,SHELL_S_START_Y,m_uShellRcX[1],SHELL_S_H,m_clrDark,RGB(255,255,255));
	 dc.Draw3dRect(SHELL_S_START_X+1,SHELL_S_START_Y+1,m_uShellRcX[1]-2,SHELL_S_H-2,m_clrDark,RGB(255,255,255));
     //��С����ǡ�Draw3dRect����Ĭ�ϻ�����������߿�����1�����Ի�����ʹ����߿���Ϊ2

     dc.Draw3dRect(SHELL_L_START_X,SHELL_L_START_Y,m_uShellRcX[1],m_uShellRcY[1],m_clrDark,RGB(255,255,255));
	 dc.Draw3dRect(SHELL_L_START_X+1,SHELL_L_START_Y+1,m_uShellRcX[1]-2,m_uShellRcY[1]-2,m_clrDark,RGB(255,255,255));
 	 dc.Draw3dRect(SHELL_L_START_X+2,SHELL_L_START_Y+2,m_uShellRcX[1]-4,m_uShellRcY[1]-4,m_clrDark,RGB(255,255,255));
	 //��������
}

void CMineWnd::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rctime(17,16,56,39);//m_uNumRect[0]=17;

	if (nIDEvent==m_uTimer)
	{//������ʾ��ʱ��
       if(m_WndActive)
	   { 
		   m_uSpendTime++;
		   InvalidateRect(rctime);
           if (m_bSoundful)
	          PlaySound(MAKEINTRESOURCE(IDR_WAVE_TIME),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
		      //����SndPlaySound("c:\sound\music.wav",SND_ASYNC)		   
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
   //��������ͼ���3D���
   dc.Draw3dRect(16,15,41,25,m_clrDark,RGB(255,255,255));//��������Ŀ����ģ�����
   dc.Draw3dRect(m_uNumRect[1]-1,15,41,25,m_clrDark,RGB(255,255,255));//���Ƽ�ʱ����ģ�����

   int num,num1,num2;
   //���Ƽ�ʱ����ͼ�񣬷ֱ����ʱ��İ�λ�� ʮλ�� ��λ����
   m_uSpendTime=m_uSpendTime%1000;
   num=m_uSpendTime/100;
   dc.StretchBlt(m_uNumRect[0],16,13,23,&dcMemory,0,276-23*(num+1),13,23,SRCCOPY);
   num=(m_uSpendTime-num*100)/10;
   dc.StretchBlt(m_uNumRect[0]+13,16,13,23,&dcMemory,0,276-23*(num+1),13,23,SRCCOPY);
   num=m_uSpendTime%10;
   dc.StretchBlt(m_uNumRect[0]+26,16,13,23,&dcMemory,0,276-23*(num+1),13,23,SRCCOPY);

   //��������Ŀͼ�񣬷ֱ����ʱ��İ�λ�� ʮλ�� ��λ����
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
     dc.StretchBlt(m_uNumRect[1],16,13,23,&dcMemory,0,0,13,23,SRCCOPY);//ֱ�ӻ�����
     dc.StretchBlt(m_uNumRect[1]+13,16,13,23,&dcMemory,0,276-23*(num1+1),13,23,SRCCOPY); 
     dc.StretchBlt(m_uNumRect[1]+26,16,13,23,&dcMemory,0,276-23*(num2+1),13,23,SRCCOPY);  
   }
}


void CMineWnd::LoadBitmap()       //����Ķ�������ͬ���������κβ���
{
   //�ͷ���ǰ�Ĺ�����Դ
	 m_bmpButton.DeleteObject();//��λͼ
     m_bmpNumber.DeleteObject();//����λͼ
     m_bmpMine.DeleteObject();//Ц����ťλͼ

	 //�����û�ѡ���ж���������λͼ��Դ����ɫ/�ڰף�
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
//	heroList.UpdateData(FALSE);//�Զ�����CHEROLIST::DoDataExchange()�����ݴ����ݳ�Ա������Ӧ�Ŀؼ�
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
	//________��ȡ����Ŀ¼
	char exeFullPath[MAX_PATH];
	CString strPath;
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);//��ȡ��ǰ���г���ģ�����ڵ�Ŀ¼·��
	//��һ������ָ��Ŀ��ģ�飬NULL��ʾ��ȡ��ǰĿ��ģ��
	//exeFullPath��������·���洢����
	//��ʾ��������Ĵ�С
    strPath=CString(exeFullPath);
	strPath=strPath.Left(strPath.ReverseFind('\\'));//�����ұ�ʾ����Ѱ�ң����ؽű�
	strPath+="\\config.ini";

	//����������
//	CString strXNum,strYNum;
	//���� ѡ�񼶱�
//	CString strMineNum, strLevel;
	//��¼���ַ���
	CString strPrimary, strSecond, strAdvance;
	//��¼������
	CString strPrimaryHolder, strSecondHolder,strAdvanceHolder;
	//��������
//	CString strMarkful,strColorful,strSoundful;//strMarkful�ж��Ƿ��Ҽ������ʺţ����

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

//	WritePrivateProfileString("WINDOW","XNum",strXNum,strPath);	//iniд��������
	//"WINDOW"�ļ��е�һ���ֶ���
	//"XNum"������
	//strXNum������ֵ
	//strPath������ini�ļ���
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
    //��ȡ����Ŀ¼
	char exeFullPath[MAX_PATH];
	CString strPath;
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);
	strPath=CString(exeFullPath);
	strPath=strPath.Left(strPath.ReverseFind('\\'));
	strPath+="\\config.ini";
	
	//��¼����������
	char strPrimaryHolder[10];
	char strSecondHolder[10];
	char strAdvanceHolder[10];

//	m_uXNum=GetPrivateProfileInt("WINDOW","XNum",10,strPath);
//	m_uXNum=GetPrivateProfileInt("WINDOW","YNum",10,strPath);

//	m_uMineNum=GetPrivateProfileInt("MINE","MineNum",10,strPath);
//	m_uLevel=GetPrivateProfileInt("MINE","Level",0,strPath);
    
	//��ͬ�����¼��ʱ
	m_uuPrimary=GetPrivateProfileInt("SCORE","Primary",999,strPath);
	m_uuSecond=GetPrivateProfileInt("SCORE","Second",999,strPath);
	m_uuAdvance=GetPrivateProfileInt("SCORE","Advance",999,strPath);

	//��ͬ�����¼�����ߵ�����
	GetPrivateProfileString("HOLDER","PrimaryHolder","����",strPrimaryHolder,10,strPath);
	GetPrivateProfileString("HOLDER","SecondHolder","����",strSecondHolder,10,strPath);
	GetPrivateProfileString("HOLDER","AdvanceHolder","����",strAdvanceHolder,10,strPath);
    //����ļ���û��ǰ��������ָ�����ֶ�����������򽫡���������������

//   strcpy(m_sszPrimary,strPrimaryHolder);//���ɸ�ֵ������strcpy(strPrimaryHolder,m_sszPrimary)���Ը�ֵ��
	//��ΪCString����ֻ���Ա�Const Char*���档 strcpy��char*, const char*��
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
//    m_uBtnRect[0]=MINE_AREA_LEFT+m_uXNum*MINE_WIDTH/2-12;//Ц�������ϽǺ����½�X����
//   m_uBtnRect[1]=MINE_AREA_LEFT+m_uXNum*MINE_WIDTH/2+12;

	m_uGameState=0;//��Ϸ״̬��λ(GS_WAIT==0)
//////////////////////ˢ�����¿�ʼ
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

////////////////////�ж�ʱ�������Ƿ�������״̬
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
     	return &m_pMines[i][j];//ע������(j,i)�����꣨x,y���������෴��
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
	 {//����ǹ���ģ��	   
		 	for (i=minRow;i<maxRow;i++)
			{
	        	for (j=minCol;j<maxCol;j++)
				{
		        	//�жϸ������Ƿ��������� ��������������
		        	if (!IsInMineArea(i,j)||(i==row&&j==col)) continue;			   
		        	if(m_pMines[i][j].uState==STATE_NORMAL)
				    	m_pMines[i][j].uState=STATE_EMPTY;	
				}
			}
	 }       
	else //δ����ǵ�ģ��
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
{/////////////////////ֻ��Ӧ˫�����º���ʱ����Ϣ(�Ҽ��ȵ�������)
	// TODO: Add your message handler code here and/or call default
	if (m_uGameState==GS_DEAD||m_uGameState==GS_VICTORY)
        return;

	CRect rcBtn(m_uBtnRect[0],15,m_uBtnRect[1],39);//Ц��������
	CRect rcMineArea(MINE_AREA_LEFT,MINE_AREA_TOP,
		MINE_AREA_LEFT+m_uXNum*MINE_WIDTH,
        MINE_AREA_TOP+m_uYNum*MINE_HEIGHT);//������������

     if (!rcMineArea.PtInRect(point))
     {//��Ҫ��Ϊ��ʵ�����Ҽ�������ʱ���϶����������ֺ�Ц���ָܻ�ԭ״
		 m_uBtnState=BUTTON_NORMAL;
		 m_bLRBtnDown=FALSE;
		 InvalidateRect(&rcBtn);
		 ReleaseCapture();
     }

	if (rcMineArea.PtInRect(point))
	{//�������
		m_pOldMine=GetMine(point.x,point.y);
        if (!m_pOldMine)//�ж�����Ƿ�����׿飬û���򷵻أ�������������
	       return;

        if (m_bLRBtnDown)
		{/////////////////////////////////�ж��Ƿ����Ҽ�һ����
		   BOOL blast=FALSE;//�Ƿ��׿��־����
		   UINT i,j;
           UINT row=m_pOldMine->uRow;
           UINT col=m_pOldMine->uCol;
 	       UINT minRow=(row==0)? 0:row-1;
           UINT maxRow=row+2;
           UINT minCol=(col==0)? 0:col-1;
	       UINT maxCol=col+2;
           UINT around=0;
           around=GetAroundNum(row,col);							
//////////////////////////////////////////////��Ϸ��ʼ��ʱΪGS_WAIT״̬
	    	if (m_uGameState==GS_WAIT)
			{
                m_uSpendTime=1;
		    	//������ʱ��
			    m_uTimer=SetTimer(ID_TIMER_EVENT,1000,NULL);

		    	//����
			    LayMines(m_pOldMine->uRow,m_pOldMine->uCol);

			    //�ı���Ϸ״̬Ϊ����GS_RUN
		    	m_uGameState=GS_RUN;
			}	  	  
////////////////////////////////////////////////////////////////
	        if ((around==m_uFlagNum&&m_uDICEYNum==0)&&(m_pOldMine->uOldState!=STATE_NORMAL)&&(m_pOldMine->uOldState!=STATE_FLAG)&&(m_pOldMine->uOldState!=STATE_DICEY)) 		   
			{//�����������Ѿ��ڹ���ģ�� 
		     // m_uDICEYNum;//��Χ�����Ϊ�ʺŵ�ģ����
	           // m_uFlagNum��Χ�����Ϊ��Flag��ģ����
			     //�����Χ��־���������������Χ���п飬���Զ�����
			    for (i=minRow;i<maxRow;i++)
				{
				  for (j=minCol;j<maxCol;j++)
				  {
					if (!IsInMineArea(i,j)) continue;
		        	if(m_pMines[i][j].uOldState==STATE_NORMAL)
					{  
						if (m_pMines[i][j].uAttrib==ATTRIB_MINE)
						{/////////////////////////ģ���־����
							m_pMines[i][j].uState=STATE_BLAST;
                            m_pMines[i][j].uOldState=STATE_BLAST;
							blast=TRUE;//�Զ��ڴ�
						}
						else //ģ���־��ȷ�Զ�ȫ���ڵ�
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
			    if (blast)//����Զ��ڴ�����Ϸ����
				{
					if (m_bSoundful)
					{
	                   PlaySound(MAKEINTRESOURCE(IDR_WAVE_BOMB),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
					   //����SndPlaySound("c:\sound\music.wav",SND_ASYNC)
					}

					for (i=0;i<m_uYNum;i++)
					{/////////////�ҳ���־�����ģ��
						for (j=0;j<m_uXNum;j++)
						{/////////////�ҳ���־�����ģ��
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
					{//����ʱ������
		                KillTimer(ID_TIMER_EVENT);
	                	m_uTimer=0;
					}
	                Invalidate();
					ReleaseCapture();
					return;
				}			  			  
			}			
///////////////////////////////////////////////////////////////////////
	        else////������ҵ���Ĳ����Ѿ��ڹ���ģ�飬��ָ�˫��֮ǰ��ԭ״
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
	    m_uBtnState=BUTTON_NORMAL;//�ı�Ц��״̬Ϊԭ״̬
		m_bLRBtnDown=FALSE;
//		m_LRBtnDouble=TRUE;
		Invalidate(FALSE); 
		
	}
/////////////////////////////////////////////////
			   //2.4�ж��Ƿ�ʤ��
			 if(m_uGameState==GS_RUN)
			 {
			   if (Victory())
			   {
                 if (m_bSoundful)
				 {
	               PlaySound(MAKEINTRESOURCE(IDR_WAVE_VICTORY),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
				 //����SndPlaySound("c:\sound\music.wav",SND_ASYNC)
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
        MINE_AREA_TOP+m_uYNum*MINE_HEIGHT);//������������
//////////////////////////////////////////////////////////////////////////////�����ƶ������
	if((nFlags==MK_LBUTTON)&&(m_LRBtnDouble==FALSE)&&(m_uGameState==GS_RUN||m_uGameState==GS_WAIT))
	{      
        m_pOldMine=GetMine(m_uOrigPoint.x,m_uOrigPoint.y);
        if (!m_pOldMine)//�ж�����Ƿ�����׿飬û���򷵻أ�������������
		{//�����������������
			m_uOrigPoint=point;
		return;}

		m_pNewMine=GetMine(point.x,point.y);
        if (!m_pNewMine)
		{//���ڲ������Ƴ������
			if (m_pOldMine->uOldState==STATE_NORMAL)           
			   m_pOldMine->uState=STATE_NORMAL;
		 Invalidate();
	     return;}

		if ((m_pNewMine->uRow!=m_pOldMine->uRow)||(m_pNewMine->uCol!=m_pOldMine->uCol)) 		
		{//�������ڲ��ƶ������
           if (m_pOldMine->uOldState==STATE_NORMAL)           
			   m_pOldMine->uState=STATE_NORMAL;
           if (m_pNewMine->uOldState==STATE_NORMAL)
               m_pNewMine->uState=STATE_EMPTY;
		   m_uOrigPoint=point;
		}
	    else if (m_pOldMine->uOldState==STATE_NORMAL)           
		   m_pOldMine->uState=STATE_EMPTY;//ʹ������������ʱ�Ƚ�����

        Invalidate();
	}
////////////////////////////////////////////////////////˫���ƶ������
    if (m_bLRBtnDown&&(m_uGameState==GS_RUN||m_uGameState==GS_WAIT))
    {	
        UINT i,j,row,col,minRow,maxRow,minCol,maxCol;
		
        m_pOldMine=GetMine(m_uOrigPoint.x,m_uOrigPoint.y);
        if (!m_pOldMine)//�ж�����Ƿ�����׿飬û���򷵻أ�������������
		{//�����������������
			m_uOrigPoint=point;
		return;}

		m_pNewMine=GetMine(point.x,point.y);
        if (!m_pNewMine)
		{//���ڲ������Ƴ������		   
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
		{//�������ڲ��ƶ������          		  
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
				 m_pMines[i][j].uState=STATE_EMPTY; ///ʹ������������ʱ�Ƚ����� 			
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
	//��Ӧ����active/deactive�ĺ���
	CWnd::OnActivate(nState, pWndOther, bMinimized);
	
	// TODO: Add your message handler code here
	if (nState==WA_INACTIVE)
	   m_WndActive=FALSE;
	else
		m_WndActive=TRUE;	   
}
