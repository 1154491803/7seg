/*--------------------------------------------------------------------------
SC95F861x_C.H

C Header file for SC95F861x microcontroller.
Copyright (c) 2019 Shenzhen SinOne Chip Electronic CO., Ltd.
All rights reserved.
深圳市赛元微电子有限公司
版本号:  V1.0    
日期:  2019.04.16
--------------------------------------------------------------------------*/
#ifndef _SC95F861x_H_
#define _SC95F861x_H_

/* ------------------- 字节寄存器-------------------- */
///*CPU*/
sfr 	ACC	   = 0xE0;		//累加器Ａ
sfr 	B	   = 0xF0;		//通用寄存器B		
sfr 	PSW	   = 0xD0;		//程序状态字
sfr 	DPS	   = 0x86;      //数据选择寄存器
sfr 	DPH1   = 0x85;		//DPH1数据指针高8位	
sfr 	DPL1   = 0x84;      //DPL1数据指针低8位	
sfr 	DPH	   = 0x83;		//DPH数据指针高8位		
sfr 	DPL	   = 0x82;		//DPL数据指针低8位		
sfr 	SP	   = 0x81;		//堆栈指针	
		
/*system*/
sfr		PCON   = 0x87;		//电源管理控制寄存器

/*interrupt*/
sfr		IP2    = 0xBA;      //中断优先级控制寄存器2
sfr		IP1    = 0xB9;      //中断优先级控制寄存器1
sfr		IP	   = 0xB8;		//中断优先权控制寄存器
sfr		IE	   = 0xA8;		//中断控制寄存器
sfr		IE1    = 0xA9;  	//中断控制寄存器1
sfr		IE2    = 0xAA;      //中断控制寄存器2

/*PORT*/
sfr 	P5PH    = 0xDA;		//P5口模式控制寄存器		
sfr	  	P5CON	= 0xD9;		//P5口模式控制寄存器		
sfr   	P5	    = 0xD8;		//P5口数据寄存器
sfr 	P4PH    = 0xC2;		//P4口模式控制寄存器		
sfr	  	P4CON	= 0xC1;		//P4口模式控制寄存器		
sfr   	P4	    = 0xC0;		//P4口数据寄存器
sfr 	P3PH    = 0xB2;		//P3口模式控制寄存器		
sfr	  	P3CON	= 0xB1;		//P3口模式控制寄存器		
sfr   	P3	    = 0xB0;		//P3口数据寄存器
sfr 	P2PH    = 0xA2;		//P2口模式控制寄存器		
sfr	  	P2CON	= 0xA1;		//P2口模式控制寄存器		
sfr   	P2	    = 0xA0;		//P2口数据寄存器
sfr   	P1PH    = 0x92;		//P1口模式控制寄存器		
sfr	  	P1CON   = 0x91;		//P1口模式控制寄存器	
sfr   	P1	    = 0x90;		//P1口数据寄存器
sfr	  	P0PH    = 0x9B;		//P0口模式控制寄存器		
sfr	 	P0CON   = 0x9A;		//P0口模式控制寄存器		
sfr 	P0	    = 0x80;		//P0口数据寄存器
sfr 	IOHCON0 = 0x96;		//IOH0设置寄存器
sfr 	IOHCON1 = 0x97;		//IOH1设置寄存器

/*TIMER*/
sfr 	TMCON   = 0x8E;		//定时器频率控制寄存器
sfr 	TH1	    = 0x8D;		//定时器1高8位
sfr 	TH0	    = 0x8C;		//定时器0高8位
sfr 	TL1	    = 0x8B;		//定时器1低8位
sfr 	TL0	    = 0x8A;		//定时器0低8位
sfr 	TMOD	= 0x89;		//定时器工作模式寄存器
sfr 	TCON	= 0x88;		//定时器控制寄存器
sfr   	TXCON   = 0xC8;   //定时器2/3/4控制寄存器
sfr   	TXMOD   = 0xC9;   //定时器2/3/4重载/捕捉低8位
sfr   	RCAPXL  = 0xCA;   //定时器2/3/4重载/捕捉高8位
sfr   	RCAPXH  = 0xCB;   //定时器2/3/4重载/捕捉高8位
sfr   	TLX     = 0xCC;   //定时器2/3/4低8位
sfr   	THX     = 0xCD;   //定时器2/3/4高8位
sfr   	TXINX   = 0xCE;   //定时器控制寄存器指针

/*ADC*/
sfr	  ADCCFG0 = 0xAB;	//ADC功能配置寄存器0
sfr	  ADCCFG1 = 0xAC;	//ADC功能配置寄存器1
sfr	  ADCCFG2 = 0xB5;	//ADC功能配置寄存器2
sfr   ADCCON  = 0xAD;   //ADC控制寄存器
sfr   ADCVL	  = 0xAE;	//ADC 结果寄存器
sfr   ADCVH	  = 0xAF;	//ADC 结果寄存器

/*PWM*/
sfr 	PWMCON	= 0xD3;		//PWM控制寄存器
sfr 	PWMCFG	= 0xD4;		//PWM周期设置寄存器
sfr 	PWMDFR	= 0xD5;		//PWM3占空比设置寄存器
sfr 	PWMFLT	= 0xD6;		//PWM0占空比设置寄存器
sfr 	PWMMOD	= 0xD7;		//PWM1占空比设置寄存器

//
///*WatchDog*/
sfr	    BTMCON  = 0xFB;   //低频定时器控制寄存器
sfr 	WDTCON	= 0xCF;		//WDT控制寄存器

/*LCD*/
sfr   OTCON   = 0x8F;	//LCD电压输出控制寄存器
sfr   P0VO    = 0x9C;   //P0显示驱动输出寄存器
sfr   P1VO    = 0x94;   //P1显示驱动输出寄存器
sfr   P2VO    = 0xA3;   //P2显示驱动输出寄存器
sfr   P3VO    = 0xB3;   //P3显示驱动输出寄存器

sfr   DDRCON  = 0x93;   //显示驱动设置寄存器

/*INT*/
sfr   INT0F   = 0xB4; 	//INT0 下降沿中断控制寄存器
sfr   INT0R   = 0xBB; 	//INT0 上降沿中断控制寄存器
sfr   INT1F   = 0xBC; 	//INT2 下降沿中断控制寄存器
sfr   INT1R   = 0xBD; 	//INT2 上降沿中断控制寄存器
sfr   INT2F   = 0xBE; 	//INT2 下降沿中断控制寄存器
sfr   INT2R   = 0xBF; 	//INT2 上降沿中断控制寄存器

/*IAP */
sfr   IAPCTL	= 0xF6;		//IAP控制寄存器
sfr   IAPDAT	= 0xF5;		//IAP数据寄存器
sfr   IAPADE    = 0xF4;     //IAP扩展地址寄存器
sfr   IAPADH	= 0xF3;		//IAP写入地址高位寄存器
sfr   IAPADL	= 0xF2;		//IAP写入地址低8位寄存器
sfr   IAPKEY	= 0xF1;		//IAP保护寄存器

/*UART*/
sfr   SCON    = 0x98;   //串口控制寄存器
sfr   SBUF    = 0x99;  	//串口数据缓存寄存器


/*USCI0*/
sfr   US0CON0  = 0x95;   //SPI0控制寄存器0
sfr   US0CON1  = 0x9D;   //SPI0控制寄存器1
sfr   US0CON2  = 0x9E;   //SP10控制寄存器2
sfr   US0CON3  = 0x9F;  //SPI0数据寄存器

/*USCI1*/
sfr   US1CON0  = 0xA4;   //SPI1控制寄存器0
sfr   US1CON1  = 0xA5;   //SPI1控制寄存器1
sfr   US1CON2  = 0xA6;   //SPI1控制寄存器2
sfr   US1CON3  = 0xA7;  //SPI1数据寄存器

/*USCI2*/
sfr   US2CON0  = 0xC4;   //SPI2控制寄存器0
sfr   US2CON1  = 0xC5;   //SPI2控制寄存器1
sfr   US2CON2  = 0xC6;   //SPI2控制寄存器2
sfr   US2CON3  = 0xC7;   //SPI2数据寄存器

sfr   OPINX   = 0xFE; 
sfr   OPREG   = 0xFF;
sfr   EXADH   = 0xF7;

/*模拟比较器*/
sfr   CMPCFG  = 0xB6;	//模拟比较器设置寄存器
sfr   CMPCON  = 0xB7;	//模拟比较器控制寄存器

/*乘除法器*/
sfr   EXA0    = 0xE9;   //扩展累加器0
sfr   EXA1    = 0xEA;   //扩展累加器1
sfr   EXA2    = 0xEB;   //扩展累加器2
sfr   EXA3    = 0xEC;   //扩展累加器3
sfr   EXBL    = 0xED;   //扩展B寄存器0
sfr   EXBH    = 0xEE;   //扩展B寄存器1
sfr   OPERCON = 0xEF;   //运算控制寄存器

/*CRC*/
sfr   CRCINX = 0xFC;	  //Check Sum结果寄存器低位
sfr   CRCREG = 0xFD;	  //Check Sum结果寄存器高位

///* ------------------- 位寄存器-------------------- */
/*B*/
/*TKCON*/
/*ACC*/
/*PSW*/
sbit 	CY	= PSW^7;	   //标志位		0:加法运算最高位无进位，或者减法运算最高位无借位时		1:加法运算最高位有进位，或者减法运算最高位有借位时
sbit 	AC	= PSW^6;	   //进位辅助标志位	0:无借位、进位		1:加法运算时在bit3位有进位，或减法运算在bit3位有借位时
sbit 	F0	= PSW^5;	   //用户标志位
sbit 	RS1	= PSW^4;	   //工作寄存器组选择位
sbit 	RS0	= PSW^3;	   //工作寄存器组选择位
sbit 	OV	= PSW^2;	   //溢出标志位
sbit 	F1	= PSW^1;	   //F1标志
sbit 	P	  = PSW^0;	   //奇偶标志位		0:ACC中1的个数为偶数（包括0个）		1:ACC中1的个数为奇数

/*TXCON*/
sbit  TFX   = TXCON^7;
sbit  EXFX	= TXCON^6;
sbit  RCLKX = TXCON^5;
sbit  TCLKX	= TXCON^4;
sbit  EXENX	= TXCON^3;
sbit  TRX	= TXCON^2;
sbit  TX    = TXCON^1;
sbit  CP	= TXCON^0;

/*IP*/
sbit 	IPADC  = IP^6;		//ADC中断优先控制位	0:设定 ADC的中断优先权是 “低”		1:设定 ADC的中断优先权是 “高”
sbit	IPT2   = IP^5;		//PWM中断优先控制位	0:设定 PWM的中断优先权是 “低”		1:设定 PWM 的中断优先权是 “高”
sbit 	IPUART = IP^4;		//SIF中断优先控制位	0:设定 SIF的中断优先权是 “低”		1:设定 SIF的中断优先权是 “高”
sbit 	IPT1   = IP^3;		//Timer1中断优先控制位	0:设定 Timer 1的中断优先权是 “低”	1:设定 Timer 1的中断优先权是 “高”
sbit	IPINT1 = IP^2;		//32K Base Timer中断优先控制位		0:设定 32K的中断优先权是 “低”		1:设定 32K的中断优先权是 “高”
sbit 	IPT0   = IP^1;		//Timer0中断优先控制位	0:设定 Timer 0的中断优先权是 “低”	1:设定 Timer 0的中断优先权是 “高”
sbit	IPINT0 = IP^0;

/*IE*/
sbit 	EA	   = IE^7;		//中断使能的总控制	0:关闭所有的中断	1:打开所有的中断
sbit 	EADC   = IE^6;		//ADC中断使能控制	0:关闭ADC中断		1:打开ADC中断
sbit 	ET2    = IE^5;		//PWM中断使能控制	0:关闭PWM中断		1:打开PWM中断
sbit	EUART  = IE^4;		//UART中断使能控制	0:关闭SIF中断		1:打开SIF中断
sbit 	ET1    = IE^3;		//Timer1中断使能控制	0:关闭TIMER1中断	1:打开TIMER1中断
sbit	EINT1  = IE^2;		//32K Base Timer中断使能控制	0:关闭32K中断		1:打开32K中断	
sbit 	ET0	   = IE^1;		//Timer0中断使能控制	0:关闭TIMER0中断	1:打开TIMER0中断
sbit	EINT0  = IE^0;		//TouchKey的中断使能控制	0:关闭TouchKey中断  1:打开TouchKey中断

/*TCON*/
sbit 	TF1	   = TCON^7;	//T1溢出中断请求标志位	T1产生溢出，发生中断时，硬件将TF1置为“1”，申请中断，CPU响应时，硬件清“0”。
sbit 	TR1	   = TCON^6;	//定时器T1的运行控制位	0:Timer1禁止计数		1:Timer1开始计数
sbit 	TF0	   = TCON^5;	//T0溢出中断请求标志位	T0产生溢出，发生中断时，硬件将TF0置为“1”，申请中断，CPU响应时，硬件清“0”。
sbit 	TR0	   = TCON^4;	//定时器T0的运行控制位	0:Timer0禁止计数		1:Timer0开始计数
sbit 	Bit_IE1	   = TCON^3;	//INT1标志位
sbit 	Bit_IE0	   = TCON^1;	//INT0标志位

/*SCON*/
sbit 	SM0	   = SCON^7;
sbit 	SM1	   = SCON^6;
sbit 	SM2	   = SCON^5;
sbit 	REN	   = SCON^4;
sbit 	TB8	   = SCON^3;
sbit 	RB8	   = SCON^2;
sbit 	TI	   = SCON^1;
sbit 	RI	   = SCON^0;

/******************* P0 ******************
*SC95F8617封装未引出的管脚：无
*SC95F8616封装未引出的管脚：无
*SC95F8612封装未引出的管脚：P00/P01/P02/P03
******************************************/
sbit 	P07	= P0^7;
sbit 	P06	= P0^6;
sbit 	P05	= P0^5;
sbit 	P04	= P0^4;
sbit 	P03	= P0^3;
sbit 	P02	= P0^2;
sbit 	P01	= P0^1;
sbit 	P00	= P0^0;

/******************* P1 ******************
*SC95F8617封装未引出的管脚：无
*SC95F8616封装未引出的管脚：无
*SC95F8612封装未引出的管脚：P10/P11/P12/P13
******************************************/
sbit 	P17	= P1^7;
sbit 	P16	= P1^6;
sbit 	P15	= P1^5;
sbit 	P14	= P1^4;
sbit 	P13	= P1^3;
sbit 	P12	= P1^2;
sbit 	P11	= P1^1;
sbit 	P10	= P1^0;

/******************* P2 ******************
*SC95F8617封装未引出的管脚：无
*SC95F8616封装未引出的管脚：无
*SC95F8612封装未引出的管脚：P24/P25/P26/P27
******************************************/
sbit 	P27	= P2^7;
sbit 	P26	= P2^6;
sbit 	P25	= P2^5;
sbit 	P24	= P2^4;
sbit 	P23	= P2^3;
sbit 	P22	= P2^2;
sbit 	P21	= P2^1;
sbit 	P20	= P2^0;

/******************* P3 ******************
*SC95F8617封装未引出的管脚：无
*SC95F8616封装未引出的管脚：无
*SC95F8612封装未引出的管脚P30/P31/P32/P33/P34/P35/P36/P37
******************************************/
sbit 	P37	= P3^7;
sbit 	P36	= P3^6;
sbit 	P35	= P3^5;
sbit 	P34	= P3^4;
sbit 	P33	= P3^3;
sbit 	P32	= P3^2;
sbit 	P31	= P3^1;
sbit 	P30	= P3^0;

/******************* P4 ******************
*SC95F8617封装未引出的管脚：无
*SC95F8616封装未引出的管脚：P46/P47
*SC95F8612封装未引出的管脚P46/P47
******************************************/
sbit 	P47	= P4^7;
sbit 	P46	= P4^6;
sbit 	P45	= P4^5;
sbit 	P44	= P4^4;
sbit 	P43	= P4^3;
sbit 	P42	= P4^2;
sbit 	P41	= P4^1;
sbit 	P40	= P4^0;

/******************* P5 ******************
*SC95F8617封装未引出的管脚：无
*SC95F8616封装未引出的管脚：P54/P55
*SC95F8612封装未引出的管脚P50/P51/P52/P53/P54/P55
******************************************/
sbit 	P55	= P5^5;
sbit 	P54	= P5^4;
sbit 	P53	= P5^3;
sbit 	P52	= P5^2;
sbit 	P51	= P5^1;
sbit 	P50	= P5^0;

/****************************************************************************
*注意：封装未引出的管脚，需设置为强推挽输出模式
*IC选型：请根据所使用的IC型号,在初始化完IO口后，调用相对应的未引出管脚的IO口配置;
*****************************************************************************/
#define  SC95F8616_NIO_Init()   {P4CON|=0xC0,P5CON|=0x30;}              //SC95F8616的未引出来的IO口配置
#define  SC95F8612_NIO_Init()   {P0CON|=0x0F,P1CON|=0x0F,P2CON|=0xF0,P3CON|=0xFF,P4CON|=0xC0,P5CON|=0xFF;}  // SC95F8612的未引出来的IO口配置

#endif