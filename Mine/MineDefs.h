////////////////////////////////////////////////
//�Ѷȼ������ã������С�ĸı�

#define PRIMARY_XNUM                   9     //����x����Ŀ���
#define PRIMARY_YNUM                   9     //����y����Ŀ���
#define PRIMARY_MINENUM                10    //�����׵���Ŀ

#define SECONDRY_XNUM                  16
#define SECONDRY_YNUM                  16
#define SECONDRY_MINENUM               40

#define ADVANCE_XNUM                   30
#define ADVANCE_YNUM                   16
#define ADVANCE_MINENUM                99  
  

////////////////////////////////////////////////////////////////////////
// �����С�Լ����߿������
#define DEFAULT_FRAME_X                6     //����x����Ŀ��
#define DEFAULT_FRAME_Y                52

#define LINE_WIDTH_0                   3     //�߱�0�Ŀ��
#define LINE_WIDTH_1                   2     //�߱�1�Ŀ��

#define SIDE_WIDTH_0                   6    
#define SIDE_WIDTH_1                   5

#define SHELL_S_H                      37
#define SHELL_S_START_X                9
#define SHELL_S_START_Y                9    
#define SHELL_L_START_X                9
#define SHELL_L_START_Y                52

#define MINEAREA_FRAME_X               12
#define MINEAREA_FRAME_Y               55

//�׷���Ķ���
#define MINE_WIDTH                     16
#define MINE_HEIGHT                    16
#define MINE_AREA_LEFT                 12
#define MINE_AREA_TOP                  55


///////////////////////////////////////////////////////////////////////////
//�����׷�������ݽṹ
typedef struct 
{
	UINT uAttrib;
	UINT uCol;
	UINT uOldState;
	UINT uRow;	
	UINT uState;
}MINEWND;



#define STATE_NORMAL         0  //����
#define STATE_FLAG           1  //��־Ϊ��

#define STATE_DICEY          2  //δ֪״̬0
#define STATE_BLAST          3  //��ը״̬

#define STATE_ERROR          4  //����״̬
#define STATE_MINE           5  //��״̬

#define STATE_DICEY_DOWN     6  //δ֪״̬1   
#define STATE_NUM8           7  //��Χ��8����   
#define STATE_NUM7           8    
#define STATE_NUM6           9    
#define STATE_NUM5           10    
#define STATE_NUM4           11     
#define STATE_NUM3           12   
#define STATE_NUM2           13     
#define STATE_NUM1           14
                      
#define STATE_EMPTY          15   //����   
#define ATTRIB_EMPTY          0   //����
#define ATTRIB_MINE           1   //��

//Ц����ť����ͼ��
#define BUTTON_DOWN           0    
#define BUTTON_VICTORY        1     
#define BUTTON_DEAD           2   
#define BUTTON_CLICK          3     
#define BUTTON_NORMAL         4

//��ʱ����ʶ
#define ID_TIMER_EVENT        500

//��Ϸ״̬�ı�ʶ
#define GS_WAIT          0   
#define GS_RUN           1     
#define GS_VICTORY       2
#define GS_DEAD          3