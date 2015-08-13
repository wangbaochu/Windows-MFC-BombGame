////////////////////////////////////////////////
//难度级别设置，窗体大小的改变

#define PRIMARY_XNUM                   9     //初级x方向的块数
#define PRIMARY_YNUM                   9     //初级y方向的块数
#define PRIMARY_MINENUM                10    //初级雷的数目

#define SECONDRY_XNUM                  16
#define SECONDRY_YNUM                  16
#define SECONDRY_MINENUM               40

#define ADVANCE_XNUM                   30
#define ADVANCE_YNUM                   16
#define ADVANCE_MINENUM                99  
  

////////////////////////////////////////////////////////////////////////
// 窗体大小以及各边框的设置
#define DEFAULT_FRAME_X                6     //窗口x方向的宽度
#define DEFAULT_FRAME_Y                52

#define LINE_WIDTH_0                   3     //线边0的宽度
#define LINE_WIDTH_1                   2     //线边1的宽度

#define SIDE_WIDTH_0                   6    
#define SIDE_WIDTH_1                   5

#define SHELL_S_H                      37
#define SHELL_S_START_X                9
#define SHELL_S_START_Y                9    
#define SHELL_L_START_X                9
#define SHELL_L_START_Y                52

#define MINEAREA_FRAME_X               12
#define MINEAREA_FRAME_Y               55

//雷方块的定义
#define MINE_WIDTH                     16
#define MINE_HEIGHT                    16
#define MINE_AREA_LEFT                 12
#define MINE_AREA_TOP                  55


///////////////////////////////////////////////////////////////////////////
//定义雷方块的数据结构
typedef struct 
{
	UINT uAttrib;
	UINT uCol;
	UINT uOldState;
	UINT uRow;	
	UINT uState;
}MINEWND;



#define STATE_NORMAL         0  //正常
#define STATE_FLAG           1  //标志为雷

#define STATE_DICEY          2  //未知状态0
#define STATE_BLAST          3  //爆炸状态

#define STATE_ERROR          4  //错误状态
#define STATE_MINE           5  //雷状态

#define STATE_DICEY_DOWN     6  //未知状态1   
#define STATE_NUM8           7  //周围有8个雷   
#define STATE_NUM7           8    
#define STATE_NUM6           9    
#define STATE_NUM5           10    
#define STATE_NUM4           11     
#define STATE_NUM3           12   
#define STATE_NUM2           13     
#define STATE_NUM1           14
                      
#define STATE_EMPTY          15   //无雷   
#define ATTRIB_EMPTY          0   //非雷
#define ATTRIB_MINE           1   //雷

//笑脸按钮矩形图像
#define BUTTON_DOWN           0    
#define BUTTON_VICTORY        1     
#define BUTTON_DEAD           2   
#define BUTTON_CLICK          3     
#define BUTTON_NORMAL         4

//定时器标识
#define ID_TIMER_EVENT        500

//游戏状态的标识
#define GS_WAIT          0   
#define GS_RUN           1     
#define GS_VICTORY       2
#define GS_DEAD          3