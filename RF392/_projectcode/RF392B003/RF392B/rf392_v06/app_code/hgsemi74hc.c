/*
**************************************
hgsemi 74hc595 
**************************************
*/
//preledvalue 
//nowledvalue
//ledstatus
//ledstatus_0
#include "hgsemi74hc.h"
#include "board_efm8sb.h"

//extern unsigned  int xdata itcounter;

//unsigned char xdata LED_Data[4] _at_ 0x1FF0;

/*#define LED1_ON()       semi74hc_writedata(nowledvalue = (nowledvalue & (~0x01)));
#define LED1_OFF()      semi74hc_writedata(nowledvalue = (nowledvalue & (~0x01)) | 0x01);

#define LED2_ON()       semi74hc_writedata(nowledvalue = (nowledvalue & (~0x02)));
#define LED2_OFF()      semi74hc_writedata(nowledvalue = (nowledvalue & (~0x02)) | 0x02);

#define LED3_ON()       semi74hc_writedata(nowledvalue = (nowledvalue & (~0x04)));
#define LED3_OFF()      semi74hc_writedata(nowledvalue = (nowledvalue & (~0x04)) | 0x04);

#define LED4_ON()       semi74hc_writedata(nowledvalue = (nowledvalue & (~0x08)));
#define LED4_OFF()      semi74hc_writedata(nowledvalue = (nowledvalue & (~0x08)) | 0x08);

#define LED5_ON()       semi74hc_writedata(nowledvalue = (nowledvalue & (~0x10)));
#define LED5_OFF()      semi74hc_writedata(nowledvalue = (nowledvalue & (~0x10)) | 0x10);

#define LED6_ON()       semi74hc_writedata(nowledvalue = (nowledvalue & (~0x20)));
#define LED6_OFF()      semi74hc_writedata(nowledvalue = (nowledvalue & (~0x20)) | 0x20);

#define LED7_ON()       semi74hc_writedata(nowledvalue = (nowledvalue & (~0x40)));
#define LED7_OFF()      semi74hc_writedata(nowledvalue = (nowledvalue & (~0x40)) | 0x40);

#define LED8_ON()       semi74hc_writedata(nowledvalue = (nowledvalue & (~0x80)));
#define LED8_OFF()      semi74hc_writedata(nowledvalue = (nowledvalue & (~0x80)) | 0x80);*/



/*
**@描述: 高位数据先出，最后移动Q7
*/
void semi74hc_writedata(unsigned char wda)
{
	
	//sck
	//ser
	//rck
	unsigned char i;
	//if(nowledvalue == wda) return;
	//nowledvalue = wda;
	//--SEMI74HC_G = 0;
	for(i = 0; i < 8; i++)
	{
	    delay1ms(1);
		SEMI74HC_SCK = 0;
		if(wda & 0x80)
		{
		  SEMI74HC_SER = 1; 	
		}
		else
		{
		  SEMI74HC_SER = 0;	
		}
		delay1ms(1);
		SEMI74HC_SCK = 1;
		wda <<=1;
	}
	SEMI74HC_RCK = 0;
	app_delay10us(1);
	//dly 1us
	SEMI74HC_RCK = 1;
	app_delay10us(1);
	//dly 1us
	SEMI74HC_RCK = 0;
}

/*void user_led1_litup(void)
{
  //d5
  LED1_ON();
}

void user_led2_litup(void)
{
  //d3
  LED2_ON();
//
}

void user_led3_litup(void)
{
  //d6
  LED3_ON();
//
}

void user_led4_litup(void)
{
  //D4
  LED4_ON();
}

void user_led5_litup(void)
{
  //D2
//
  LED5_ON();
}
void user_led6_litup(void)
{
//D7
  LED6_ON();
}

void user_led7_litup(void)
{
  //D1
  LED7_ON();

}

void user_led1_litoff(void)
{
  LED1_OFF();
}

void user_led2_litoff(void)
{
  LED2_OFF();
}

void user_led3_litoff(void)
{
  LED3_OFF();
}

void user_led4_litoff(void)
{
  LED4_OFF();
}

void user_led5_litoff(void)
{
  LED5_OFF();
}
void user_led6_litoff(void)
{
  LED6_OFF();
}

void user_led7_litoff(void)
{
  LED7_OFF();
}

void user_ledall_turnon(void)
{
  LEDALL_ON();
}

void user_ledall_turnoff(void)
{
  LEDALL_OFF();
}*/

void app_delayus(unsigned char us)
{
  for(;us>0;us--)
    {

      NOP();
    }
}
void app_delay10us(unsigned char us)
{
  for(;us>0;us--)
    {
  app_delayus(15);
    }
}

void delay1ms(unsigned char ums)
{
  for(;ums>0;ums--)
    {
      app_delay10us(100);
    }
}




