#if !defined(AFX_MINEWND_H__CE9D3B95_B47E_42B4_A401_28F336F1FC8C__INCLUDED_)
#define AFX_MINEWND_H__CE9D3B95_B47E_42B4_A401_28F336F1FC8C__INCLUDED_

#include "MineDefs.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MineWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMineWnd window

class CMineWnd : public CWnd
{
// Construction
public:
	CMineWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMineWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL m_WndActive;//在OnActive（）中标识窗口是否处于激活状态，以便决定是否计时
	CString m_sszAdvance;
	CString m_sszSecond;
	CString m_sszPrimary;
	UINT m_uuAdvance;
	UINT m_uuSecond;
	UINT m_uuPrimary;

	MINEWND * m_pNewMine;
	BOOL m_LRBtnDouble;//标识鼠标左右键是否曾经同时按下，主要是为了在左键弹起时判断是否挖掉所点击模块
	CPoint m_uOrigPoint;//记录鼠标移动前点坐标的值
	UINT m_uDICEYNum;//周围被标记为问号的模块数
	UINT m_uFlagNum;//周围被标记为雷Flag的模块数
	UINT m_uHeight;
	UINT m_uWidth;
	MINEWND m_pMines[100][100];//雷区内所有小方块的二维数组
	COLORREF m_clrDark;
	int m_uNumRect[2];//数字模块显示区域的横坐标
	int m_uShellRcY[2];
	int m_uShellRcX[2];
	CBrush* m_brsBG;//用灰色刷子初始化内存位图
	RECT m_rcClient;//保存内存位图的矩形区域的坐标
	BOOL IsInMineArea(UINT x, UINT y);
	int m_nLeaveNum;//剩余雷的数目
//	MINEWND * m_pNewMine;
	UINT m_uBtnState;
	void DrawDownNum(MINEWND *P, UINT x);
	void OnLRBtnDown(UINT x, UINT y);
	BOOL m_bLRBtnDown;//是否左右鼠标都按下
	MINEWND * GetMine(UINT x, UINT y);
	MINEWND * m_pOldMine;
	UINT m_uGameState;
	void InitGame();
	UINT m_uBtnRect[2];
	BOOL m_bMarkful;//判断是否右键能用问号？标记


	UINT m_uLevel;
	UINT m_uMineNum;
	void LoadConfig();
	void SaveConfig();
	void LoadBitmap();
	void DrawNumber(CPaintDC &dc);
	UINT m_uSpendTime;//游戏从开始到目前花费的时间
	UINT m_uTimer;//定时器标识
	void DrawShell(CPaintDC &dc);
	void DrawButton(CPaintDC &dc);
	void DrawMineArea(CPaintDC &dc);
	void Dead(UINT row, UINT col);
	CBitmap m_bmpButton;
	CBitmap m_bmpNumber;
	CBitmap m_bmpMine;
	BOOL Victory();
	void ExpandMines(UINT row,UINT col);
	UINT GetAroundNum(UINT row, UINT col);
	BOOL IsMine(UINT row,UINT col);
	void LayMines(UINT row,UINT col);
	BOOL m_bSoundful;
	BOOL m_bColorful;
	UINT m_uYNum;//表示当前难度级别的y方向的方块数目
	UINT m_uXNum;//表示当前难度级别的x方向的方块数目
	void SizeWindow(void);
	virtual ~CMineWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMineWnd)
	afx_msg void OnBaseLevel();
	afx_msg void OnMiddleLevel();
	afx_msg void OnAdvanceLevel();
	afx_msg void OnColor();
	afx_msg void OnSound();
	afx_msg void OnHelp();
	afx_msg void OnAbout();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnHeroTable();
	afx_msg void OnFileOpen();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTag();
	afx_msg void OnExit();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MINEWND_H__CE9D3B95_B47E_42B4_A401_28F336F1FC8C__INCLUDED_)
