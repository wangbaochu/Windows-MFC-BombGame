; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMineWnd
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Mine.h"
LastPage=0

ClassCount=8
Class1=CMineApp
Class2=CMineDoc
Class3=CMineView
Class4=CMainFrame

ResourceCount=4
Resource1=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=CMineWnd
Resource2=IDR_MAINFRAME
Resource3=IDD_NEW_RECORD
Class7=CHEROLIST
Class8=CNEWRECORD
Resource4=IDD_HERO_LIST

[CLS:CMineApp]
Type=0
HeaderFile=Mine.h
ImplementationFile=Mine.cpp
Filter=N
LastObject=CMineApp

[CLS:CMineDoc]
Type=0
HeaderFile=MineDoc.h
ImplementationFile=MineDoc.cpp
Filter=N
LastObject=CMineDoc

[CLS:CMineView]
Type=0
HeaderFile=MineView.h
ImplementationFile=MineView.cpp
Filter=C
LastObject=CMineView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=Mine.cpp
ImplementationFile=Mine.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
Command2=ID_BASE_LEVEL
Command3=ID_MIDDLE_LEVEL
Command4=ID_ADVANCE_LEVEL
Command5=ID_DEFINE
Command6=ID_TAG
Command7=ID_COLOR
Command8=ID_SOUND
Command9=ID_HERO_TABLE
Command10=ID_EXIT
Command11=ID_HELP
Command12=ID_ABOUT
CommandCount=12

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[CLS:CMineWnd]
Type=0
HeaderFile=MineWnd.h
ImplementationFile=MineWnd.cpp
BaseClass=CWnd
Filter=W
LastObject=CMineWnd
VirtualFilter=WC

[DLG:IDD_NEW_RECORD]
Type=1
Class=CNEWRECORD
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_NEW_NAME,edit,1350631552

[DLG:IDD_HERO_LIST]
Type=1
Class=CHEROLIST
ControlCount=11
Control1=IDOK,button,1342242817
Control2=ID_NEW_SCORE,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_SCORE1,static,1342308352
Control7=IDC_SCORE2,static,1342308352
Control8=IDC_SCORE3,static,1342308352
Control9=IDC_NAME1,static,1342308352
Control10=IDC_NAME2,static,1342308352
Control11=IDC_NAME3,static,1342308352

[CLS:CHEROLIST]
Type=0
HeaderFile=HEROLIST.h
ImplementationFile=HEROLIST.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_NEW_SCORE
VirtualFilter=dWC

[CLS:CNEWRECORD]
Type=0
HeaderFile=NEWRECORD.h
ImplementationFile=NEWRECORD.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CNEWRECORD

