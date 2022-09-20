/*! company     :     guangzhou HoneStar
 *                        _oo0oo_
 *                       o8888888o
 *                       88" . "88
 *                       (| -_- |)
 *                       0\  =  /0
 *                     ___/`---'\___
 *                   .' \\|     |// '.
 *                  / \\|||  :  |||// \
 *                 / _||||| -:- |||||- \
 *                |   | \\\  - /// |   |
 *                | \_|  ''\---/''  |_/ |
 *                \  .-\__  '-'  ___/-. /
 *              ___'. .'  /--.--\  `. .'___
 *           ."" '<  `.___\_<|>_/___.' >' "".
 *          | | :  `- \`.;`\ _ /`;.`/ - ` : | |
 *          \  \ `_.   \_ __\ /__ _/   .-` /  /
 *      =====`-.____`.___ \_____/___.-`___.-'=====
 *                        `=---='
 * 
 * 
 *      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 *            佛祖保佑     永不宕机     永无BUG
 * 
 *        佛曰:  
 *                写字楼里写字间，写字间里程序员；  
 *                程序人员写程序，又拿程序换酒钱。  
 *                酒醒只在网上坐，酒醉还来网下眠；  
 *                酒醉酒醒日复日，网上网下年复年。  
 *                但愿老死电脑间，不愿鞠躬老板前；  
 *                奔驰宝马贵者趣，公交自行程序员。  
 *                别人笑我忒疯癫，我笑自己命太贱；  
 *                不见满街漂亮妹，哪个归得程序员？
 * 
 * Date: 2022-08-26 16:59:12
 * LastEditors: qs
 * LastEditTime: 2022-09-20 10:42:27
 * FilePath: \7seg\main.c
 */



#include <SC92R342_C.H>
#include "SensorMethod.h"

sbit    COM0 = P0^1;
sbit 	COM1 = P0^0;
sbit	COM3 = P0^2;
sbit	COM2 = P0^3;
sbit	COM4 = P2^1;
sbit	COM5 = P0^7;

sbit	SEG0 = P0^5;//a
sbit	SEG1 = P2^0;//f
sbit	SEG2 = P0^6;//b
sbit	SEG3 = P0^4;//g
sbit	SEG4 = P5^1;//c
sbit	SEG5 = P5^0;//dp
sbit	SEG6 = P1^1;//d
sbit	SEG7 = P1^2;//e

sbit	BUZ = P1^6;


/*
typedef enum
{
	GPIO_PIN_0    = ((uint8_t)0x01),  //IO??Px0
	GPIO_PIN_1    = ((uint8_t)0x02),  //IO??Px1
	GPIO_PIN_2    = ((uint8_t)0x04),  //IO??Px2
	GPIO_PIN_3    = ((uint8_t)0x08),  //IO??Px3
	GPIO_PIN_4    = ((uint8_t)0x10),  //IO??Px4
	GPIO_PIN_5    = ((uint8_t)0x20),  //IO??Px5
	GPIO_PIN_6    = ((uint8_t)0x40),  //IO??Px6
	GPIO_PIN_7    = ((uint8_t)0x80),  //IO??Px7
	GPIO_PIN_LNIB = ((uint8_t)0x0F),  //IO??Px0~3
	GPIO_PIN_HNIB = ((uint8_t)0xF0),  //IO??Px4~7
	GPIO_PIN_ALL  = ((uint8_t)0xFF)   //IO??Px0~7
}GPIO_Pin_TypeDef;
*/
#define RELODE 		65210
typedef enum
{
	SEGCOM0 = 0,
	SEGCOM1,
	SEGCOM2,
	SEGCOM3,
	SEGCOM4,
	SEGCOM5
} comTypedef;

unsigned char code segData[] = {0xD7,0x14,0xCD,0x5D,0x1E,0x5B,0xDB,0x15,0xDf,0x5F,0x9F,0xDA,0xC3,0xDC,0xCB,0x8B,0x00,0xff,0x08};
unsigned int ledData = 0x8000;
unsigned char i,j=0;
unsigned char seg=0;
unsigned long int exKeyValue;
bit flag;
char number[4]={0,0,0,0};
void segDisplay(comTypedef COMx, unsigned char data1, unsigned char dp)
{	
//	unsigned char digital = 0xff;
	switch(COMx)
	{
		case 0: COM0 = 0;COM1 = 1;COM2 = 1; COM3 = 1; COM4 = 1; COM5 = 1; break;
		case 1: COM0 = 1;COM1 = 0;COM2 = 1; COM3 = 1; COM4 = 1; COM5 = 1; break;
		case 2: COM0 = 1;COM1 = 1;COM2 = 0; COM3 = 1; COM4 = 1; COM5 = 1; break;
		case 3: COM0 = 1;COM1 = 1;COM2 = 1; COM3 = 0; COM4 = 1; COM5 = 1; break;
		default : break;
	}
	
	SEG7 = data1&0x80;
	SEG6 = data1&0x40;
	SEG5 = dp;
	SEG4 = data1&0x10;
	SEG3 = data1&0x08;
	SEG2 = data1&0x04;
	SEG1 = data1&0x02;
	SEG0 = data1&0x01;

}

void ledDisplay(comTypedef COMx, unsigned int data1)
{
	if(COMx == 4) 
	{
		COM0 = 1;COM1 = 1;COM2 = 1; COM3 = 1; COM4 = 0; COM5 = 1;
		SEG0 = data1&0x8000;//1
		SEG7 = data1&0x2000;//3
		SEG1 = data1&0x0800;
		SEG6 = data1&0x0200;
		SEG2 = data1&0x0080;
		SEG5 = data1&0x0020;
	}
	else
	{
		COM0 = 1;COM1 = 1;COM2 = 1; COM3 = 1; COM4 = 1; COM5 = 0;
		SEG0 = data1&0x4000;//1
		SEG7 = data1&0x1000;//3
		SEG1 = data1&0x0400;
		SEG6 = data1&0x0100;
		SEG2 = data1&0x0040;
		SEG5 = data1&0x0010;
	}
}

/*!
 * \description: main
 * \return {*}
 */
void main()
{
	
	P0CON |= 0xff;
	P1CON |= 0xff;
	P2CON |= 0xff;
	P5CON |= 0xff;
	TMCON &= 0XFE;
	TMOD &= 0X01;

	TL0 = RELODE % 256;
	TH0 = RELODE / 256;
	TR0 = 1;
	ET0 = 1;
	IPT0 = 0;

	TouchKeyInit();
	while(1)
	{	
		if(SOCAPI_TouchKeyStatus&0x80)
		{
			SOCAPI_TouchKeyStatus&=0x7F;
			exKeyValue = TouchKeyScan();

			TouchKeyRestart();
		}
		
		if(exKeyValue)
		{
			switch(exKeyValue)
			{
				case 0x00040000:number[0]=1;BUZ = 1;break;
				case 0x00002000:number[0]=3;if(flag==0){flag=1;ledData=ledData>>1;}BUZ = 1;break;
				case 0x00001000:number[0]=4;if(flag==1){flag=0;ledData=ledData>>1;}BUZ = 1;break;
				case 0x00080000:number[0]=2;ledData=ledData>>1;BUZ = 1;break;
				default : number[0]=0;break;
			}
		}
		if(ledData == 0x0008)
		{
			ledData = 0x8000;
		}
	}
}

/*!
 * \description: interrupt timer2
 * \return {*}
 */
void LEDdisplay() interrupt 1
{
	TL0 = RELODE % 256;
	TH0 = RELODE / 256;
	switch(seg++)
	{
		case 0:segDisplay(SEGCOM0,segData[number[0]],1);break;
		case 43:segDisplay(SEGCOM1,segData[2],1);break;
		case 84:segDisplay(SEGCOM2,segData[3],1);break;
		case 128:segDisplay(SEGCOM3,segData[4],1);break;
		case 170:ledDisplay(SEGCOM4,ledData);break;
		case 212:ledDisplay(SEGCOM5,ledData);break;
		default : break;
	}
	if(seg%128) BUZ = 0;
}
