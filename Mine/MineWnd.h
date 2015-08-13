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
	BOOL m_WndActive;//��OnActive�����б�ʶ�����Ƿ��ڼ���״̬���Ա�����Ƿ��ʱ
	CString m_sszAdvance;
	CString m_sszSecond;
	CString m_sszPrimary;
	UINT m_uuAdvance;
	UINT m_uuSecond;
	UINT m_uuPrimary;

	MINEWND * m_pNewMine;
	BOOL m_LRBtnDouble;//��ʶ������Ҽ��Ƿ�����ͬʱ���£���Ҫ��Ϊ�����������ʱ�ж��Ƿ��ڵ������ģ��
	CPoint m_uOrigPoint;//��¼����ƶ�ǰ�������ֵ
	UINT m_uDICEYNum;//��Χ�����Ϊ�ʺŵ�ģ����
	UINT m_uFlagNum;//��Χ�����Ϊ��Flag��ģ����
	UINT m_uHeight;
	UINT m_uWidth;
	MINEWND m_pMines[100][100];//����������С����Ķ�ά����
	COLORREF m_clrDark;
	int m_uNumRect[2];//����ģ����ʾ����ĺ�����
	int m_uShellRcY[2];
	int m_uShellRcX[2];
	CBrush* m_brsBG;//�û�ɫˢ�ӳ�ʼ���ڴ�λͼ
	RECT m_rcClient;//�����ڴ�λͼ�ľ������������
	BOOL IsInMineArea(UINT x, UINT y);
	int m_nLeaveNum;//ʣ���׵���Ŀ
//	MINEWND * m_pNewMine;
	UINT m_uBtnState;
	void DrawDownNum(MINEWND *P, UINT x);
	void OnLRBtnDown(UINT x, UINT y);
	BOOL m_bLRBtnDown;//�Ƿ�������궼����
	MINEWND * GetMine(UINT x, UINT y);
	MINEWND * m_pOldMine;
	UINT m_uGameState;
	void InitGame();
	UINT m_uBtnRect[2];
	BOOL m_bMarkful;//�ж��Ƿ��Ҽ������ʺţ����


	UINT m_uLevel;
	UINT m_uMineNum;
	void LoadConfig();
	void SaveConfig();
	void LoadBitmap();
	void DrawNumber(CPaintDC &dc);
	UINT m_uSpendTime;//��Ϸ�ӿ�ʼ��Ŀǰ���ѵ�ʱ��
	UINT m_uTimer;//��ʱ����ʶ
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
	UINT m_uYNum;//��ʾ��ǰ�Ѷȼ����y����ķ�����Ŀ
	UINT m_uXNum;//��ʾ��ǰ�Ѷȼ����x����ķ�����Ŀ
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
