//*************************************************************************************************
//  Copyright (c) 	��������Ԫ΢�������޹�˾
//	�ļ�����	:  S_TouchKeyCFG.c
//	����		: 
//	ģ�鹦��	:  SC91F844���ؼ������ļ�
// 	�汾		:
// 	���ļ�¼	:
//	ע������	:  �û���Ҫ���õ��ļ���S_TouchKeyCFG.h��
//  ��汾���	: 
//************************************************************************************************
#include "lib\S_TouchKeyCFG.h"

//*************************************************************************************
//		844 �Ĵ�������
//*************************************************************************************
/*PSW*/
sfr 	TK_PSW	    = 	0xD0;	//����״̬��
sbit 	TK_CY		= 	TK_PSW^7;	//��λ  

//===========================================================================
//ȫ�ֱ�������
unsigned	char	xdata		SOCAPI_TouchKeyStatus;					//API�ӿ�״̬��bit7-һ��ɨ����ɱ�־  1:��� 	0��δ���
																	    //			   bit6-ͨ���������������־ 1:���	 0:δ���
//===============================================================================
//ȫ�ֱ��������������򲻿��޸�
unsigned 	int 	xdata		RawData [SOCAPI_SET_TOUCHKEY_TOTAL];			
unsigned 	int		xdata		BaseLine[SOCAPI_SET_TOUCHKEY_TOTAL];
unsigned    int	 	xdata		FilterData[SOCAPI_SET_TOUCHKEY_TOTAL];												
unsigned	char    xdata		RestAreaCnt[SOCAPI_SET_TOUCHKEY_TOTAL]; 			
unsigned	char    xdata		TouchCnt[SOCAPI_SET_TOUCHKEY_TOTAL];				
unsigned	char    xdata		NoTouchCnt[SOCAPI_SET_TOUCHKEY_TOTAL];  			
unsigned	char	xdata		CurrentChannel[SOCAPI_SET_TOUCHKEY_TOTAL];						     
unsigned    char    xdata 	    LowFingerDataCnt[SOCAPI_SET_TOUCHKEY_TOTAL];
unsigned	char    xdata		FloatAreaCnt[SOCAPI_SET_TOUCHKEY_TOTAL]; 
unsigned 	char 	xdata 	    BaseLineAdjusttmp[SOCAPI_SET_TOUCHKEY_TOTAL]; 	
int                 xdata 	    DifferAccum[SOCAPI_SET_TOUCHKEY_TOTAL]; 
char	            xdata		SetNoiseThreshold;
unsigned 	char	xdata		ConfirmTouchCnt;
unsigned 	char	xdata		MultipleDealTpye = 0; 

//�Զ������
unsigned 	int 	xdata  	    UpdateBaseLNum; 						// ��������������
unsigned 	int 	xdata  	    MultipleLNum;						// �ఴ�����ż���

//�ⲿ�����ӿ�
extern 	unsigned	char	data		CurrentChannelMax;		//��ǰѡ�е�keysensor�ĸ���
extern  bit  bMultiple;	//�ఴ����־	
extern 	bit  GetIsNeedUpdateBaseline(void);
extern  void SetNeedUpdateBaseline(void);
extern  unsigned long int SensorKeyFlag(void);
extern  void MultipleDeal(unsigned char CycleCnt);
extern  void TouchKey_Service(void);

/***************���ɿ����***************/
#define		SOCAPI_SET_CS_FUNCTION						1		//0:��ʾ������CS����,1: ��ʾ����CS����,Ĭ��0
#define		SOCAPI_INHIBITION_ZONE					    8		//��������%�����÷�Χ5-10��Ĭ��7,����7*10��%=70% ����ˮʱ�Ӵ�ò���,�Խ�������С
#define		SOCAPI_MAX_KEY_MUTIPLE						300		//���ٴθ��Ÿ��»��ߣ�Ĭ��300*5=1500
#define		SOCAPI_MAX_KEY_NUM_INVALID					3		//ǿ�Ƹ��»��߰������Ƹ�����Ĭ��3
/****************************************/

#define	  	AppType			     			0
#define	  	IsDoubleKey			 			1
#define	  	AirSeparationDistance	 	    2
#define   	CONFIRMTOUCHCNT        	        3
#define   	INIT_AUTO_UPDATE_TIME	 	    4
#define   	SET_KEY_CONTI_TIME     	        5  
#define   	SET_SYNC_UPDATE 		 		6
#define   	SET_UPDATE_SPEED 		 		7	
#define   	AUTO_UPDATE_TIME	     	    8
#define	  	FilteredKValue		 			9
#define	  	SET_ANTIJAM		     			10
#define	  	BAUD		             		11
#define	  	DwellTime		         		12
#define   	SaveTime					    13
#define   	NOISE                  	        16

#define   	SET_TOUCH_FREQ		 			0
#define	  	SET_RESOLUTION		 			1
#define   	SET_GAIN_CFG			 		2
#define   	SCANTIME				 		3
#define   	SET_ICHA				 		4
#define   	FINGER_THRESHOLD_H	 		    6
#define   	FINGER_THRESHOLD_L	 		    7

//**********************************************************************************	
// 								�����ӿڵ��ò���								  //
//**********************************************************************************
/**************************************************
*�������ƣ�unsigned int SetOneKeyPushResetTime(void) 
*�������ܣ�����������ʱ��
*��ڲ�����void
*���ڲ�����unsigned int SOCAPI_SET_KEY_CONTI_TIME
*��ע	 ���������ֵ�����ã� �Ǹ����ж೤ʱ������TouchKeyRestart����һ��
����10ms ����һ�Σ� ��SOCAPI_SET_KEY_CONTI_TIME*10ms������ʱ���˰�����Ч��
**************************************************/
unsigned int SetOneKeyPushResetTime(void)   
{	  
	return  TKCFG[SET_KEY_CONTI_TIME];
}
/**************************************************
*�������ƣ�unsignedint  GetBaselineUpdateThreshold(void)
*�������ܣ������ٶ� 
*��ڲ�����void
*���ڲ�����unsigned  int 
*��ע	 ��
**************************************************/
unsigned int  GetBaselineUpdateThreshold(void)
{
	return TKCFG[SET_UPDATE_SPEED]; 
}

/**************************************************
*�������ƣ�unsigned char GetInitAutoUpdateTime(void)
*�������ܣ���ʼ���Զ�У׼����
*��ڲ�����void
*���ڲ�����unsigned  char 
*��ע	 ��
**************************************************/
unsigned char GetInitAutoUpdateTime(void)
{
	return  TKCFG[INIT_AUTO_UPDATE_TIME];
}
/**************************************************
*�������ƣ�unsigned char GetCsFunction(void)
*�������ܣ�����CS ����
*��ڲ�����void
*���ڲ�����char SOCAPI_SET_CS_FUNCTION
*��ע	 ��
**************************************************/
unsigned char GetCsFunction(void)
{
	return SOCAPI_SET_CS_FUNCTION; 
}
/**************************************************
*�������ƣ�int  GetCurrFingerValue(unsigned char i)
*�������ܣ���ȡ��ǰ��finger ֵ
*��ڲ�����unsigned char
*���ڲ�����int 
*��ע	 ��
**************************************************/
unsigned int   GetCurrFingerValue(unsigned char i)
{ 
	return	TKChannelCfg[i][FINGER_THRESHOLD_H]*256+TKChannelCfg[i][FINGER_THRESHOLD_L] ;
}

/**************************************************
*�������ƣ�unsigned char  GetScanTimeValue(unsigned char i)
*�������ܣ���ȡ��ǰͨ����ɨ��ʱ��
*��ڲ�����unsigned char
*���ڲ�����unsigned char 
*��ע	 ��
**************************************************/
unsigned char  GetScanTimeValue(unsigned char i)
{ 
	return TKChannelCfg[i][SCANTIME];
}
/**************************************************
*�������ƣ�unsigned char IsDoubleKeyOrSlideKey(void)
*�������ܣ�����Ƿ��ǵ��ɻ�������˫��
*��ڲ�����void
*���ڲ�����unsigned char 
*��ע	 ��
**************************************************/
unsigned char IsDoubleKeyOrSlideKey(void)
{
    return TKCFG[IsDoubleKey];
}
/**************************************************
*�������ƣ�unsigned char  GetBaseLineAdjustValue(unsigned char i)
*�������ܣ���ȡ��ǰͨ���Ļ��ߵ���
j
*��ڲ�����unsigned char
*���ڲ�����unsigned char 
*��ע	 ��
**************************************************/
unsigned char  GetBaseLineAdjustValue(unsigned char i)
{	
     return BaseLineAdjusttmp[i]; 
}
/**************************************************
*�������ƣ�unsigned char GetUpConfirmCnt(void)
*�������ܣ���ⰴ���������
*��ڲ�����void
*���ڲ��������ذ�������ȷ�ϴ��� 
*��ע	 ��
**************************************************/
unsigned char GetUpConfirmCnt(void)
{
	return ConfirmTouchCnt>>1;
}
/**************************************************
*�������ƣ�unsigned char GetTKYzCnt(void)
*�������ܣ���ȡ��������ȷ�ϴ���
*��ڲ�����void
*���ڲ������������ƴ��� 
*��ע	 ��
**************************************************/

unsigned char GetTKYzCnt(void)
{
	return (ConfirmTouchCnt/3);
}

/**************************************************
*�������ƣ�int GetTKYzThreshold(unsigned char i)
*�������ܣ���ȡ������������
*��ڲ�����unsigned char i
*���ڲ�����������������
*��ע	 ��
**************************************************/
unsigned int GetTKYzThreshold(unsigned char i)
{	
	unsigned int SetFingerThresholdtmp; 
	
	SetFingerThresholdtmp = GetCurrFingerValue(i); 
    SetFingerThresholdtmp = SetFingerThresholdtmp*SOCAPI_INHIBITION_ZONE/10;

	return SetFingerThresholdtmp;
}
/**************************************************
*�������ƣ�void CurrentSensorChoose(void)
*�������ܣ���ǰͨ��ѡ��
*��ڲ�����void
*���ڲ�����void
*��ע	 ��
**************************************************/
void CurrentSensorChoose(void)
{
	unsigned char  data	i = 0;
	unsigned char  data	Ctk_Channel_mark = 0;

   /**************************************************/
	unsigned long int  data  CurrentSensorKey ; 		 
	
	CurrentSensorKey = SOCAPI_SET_TOUCHKEY_CHANNEL; 
		
	for(i=0;i<31;i++)
	{
		CurrentSensorKey=CurrentSensorKey>>1;
		if(TK_CY)
		{
			CurrentChannel[Ctk_Channel_mark] = i;						//ѡ������ǰ��ͨ��
			Ctk_Channel_mark++;
			if(Ctk_Channel_mark >= SOCAPI_SET_TOUCHKEY_TOTAL)
				break;
		}		
	}
	CurrentChannelMax = Ctk_Channel_mark;							//��ǰѡ��İ����� 
}

/**************************************************
*�������ƣ�unsigned char  GetCfgMsg(unsigned char i)
*�������ܣ���ȡTouch KEY ������Ϣ
*��ڲ�����void
*���ڲ�����int 
*��ע	 ��
**************************************************/
unsigned char  GetCfgMsg(unsigned char i)
{
	switch(i)
	{ 
		 case 0:  return TKChannelCfg[0][SET_TOUCH_FREQ];
		 case 1:  return TKChannelCfg[0][SET_RESOLUTION];
		 case 2:  return TKChannelCfg[0][SET_GAIN_CFG];
		 case 3:  return GetBaseLineAdjustValue(0);//TKChannelCfg[0][SET_GAIN_CFG];
		 case 4:  return TKCFG[SET_ANTIJAM];
		 default:return 0; 	 	
	}
}

/**************************************************
*�������ƣ�void CurrentSensorChoose(void)
*�������ܣ���ʼ��TK�Ĵ���
*��ڲ�����void
*���ڲ�����void
*��ע	 ��
**************************************************/
void TouchKeyCFGInit(void)
{
	unsigned char  data	i;
	ConfirmTouchCnt = TKCFG[CONFIRMTOUCHCNT];
	SetNoiseThreshold = TKCFG[NOISE];
	CurrentSensorChoose(); 
	 for(i=0;i<CurrentChannelMax;i++)
	{
	  BaseLineAdjusttmp[i] =TKChannelCfg[i][SET_ICHA];;	
	} 
	UpdateBaseLNum = 0; 
}

/**************************************************
*�������ƣ�unsigned int TouchKeyScan(void)
*�������ܣ���ⰴ���ӿ�
*��ڲ�����void
*���ڲ���������ͨ���� ���ص���һ��int , ͨ����
*��ע	 ��1,  ���ô��ؿ��⺯��SensorKeyFlag()
		   2,  �����ó�16��ͨ�����ĸ�ͨ���а��£�����bit λ����Ϊ1������Ϊ0
		   3,  ����Ƿ���Ҫ��������baseline:  ����MAX_KEY_RESET_BASELINE ����������ʱ��������baseline
		   4,  ˫�����ߵ�������ʱ�� ʱ�����SetOneKeyPushResetTime()���ʱ����baseline 
**************************************************/
unsigned long int TouchKeyScan(void)
{
	unsigned char data t;
    unsigned char data MultipleCnt = 0;//��������
	unsigned long int data Keyvalue ; 
	unsigned long int data KeyData = 0; 	
	
	if(GetIsNeedUpdateBaseline() == 0)				//����Ƿ���Ҫ����baseline 
	{
		Keyvalue = SensorKeyFlag();					//Sensor�ж�, �������bMultiple = 1 ��ʾ�м��и���	 //�����������ó���׼��16ͨ��bit λ                     							   
		for(t=0;t<CurrentChannelMax;t++)
		{
			Keyvalue = Keyvalue>>1;
			if(TK_CY)
			{
				KeyData |= ((unsigned long int)0x01 << (CurrentChannel[t]));              
				MultipleCnt++;							
			}
		}                
		if(MultipleCnt >= 2) 	 									//����ఴ������
		{			
			bMultiple = 1;			
			if(MultipleCnt >= SOCAPI_MAX_KEY_NUM_INVALID)
			{
				SetNeedUpdateBaseline(); 							// ��������baseline ,�����ǿ��������ȥ
			}
			else
			{					
				if(IsDoubleKeyOrSlideKey())
				{
					bMultiple = 0;
				} 				 
			}			
		}			

		if(bMultiple == 0)							//���밴���ж�
		{		
			if(KeyData != 0x0)					    //���������ﵽ�೤ʱ���update baseline ,���ּ��
			{			
				UpdateBaseLNum++; 
			}
			else	
			{
				UpdateBaseLNum = 0; 	
			} 
		}	
		else
		{   
		    //���ǻ��߸���		
			MultipleLNum++; 
			KeyData = 0x00;
		}

		if(UpdateBaseLNum > SetOneKeyPushResetTime())	  //������������ʱ����»���
		{
 			SetNeedUpdateBaseline(); 
			UpdateBaseLNum = 0;
		}
				
		if(MultipleLNum >SOCAPI_MAX_KEY_MUTIPLE)		  //���ż����������������»���
 		{
			SetNeedUpdateBaseline(); 
			MultipleDealTpye = 1; 
			MultipleLNum = 0;
		}  
	}			
	else
	{
		MultipleDeal(TKCFG[AUTO_UPDATE_TIME]);										//���߸�λ����
	}  
	
	return KeyData;
}

/**************************************************
*�������ƣ�void CTK_ISR(void) interrupt	11
*�������ܣ������жϷ�����
*��ڲ�����void
*���ڲ�����void
*��ע	 ��
**************************************************/
void CTK_ISR(void) interrupt	11
{
   TouchKey_Service();
}


