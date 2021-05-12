#ifndef _HGSEMI74HC_H
#define _HGSEMI74HC_H



#define LED1TURNON()   semi74hc_writedata(0xfd)
#define LED2TURNON()   semi74hc_writedata(0xbf)
#define LED3TURNON()   semi74hc_writedata(0xfb)
#define LED4TURNON()   semi74hc_writedata(0x7f)
#define LED5TURNON()   semi74hc_writedata(0xdf)
#define LED6TURNON()   semi74hc_writedata(0xf7)
#define LED7TURNON()   semi74hc_writedata(0xef)
#define LEDALL_ON()     semi74hc_writedata(0x00)
#define LEDALL_OFF()    semi74hc_writedata(0xff)
#define LEDALL_XON()   semi74hc_writedata(0x24)//0x08 0x04

#define LED1ON_VALUE 0xfd;
#define LED2ON_VALUE 0xbf;
#define LED3ON_VALUE 0xfb;
#define LED4ON_VALUE 0x7f;
#define LED5ON_VALUE 0xdf;
#define LED6ON_VALUE 0xf7;
#define LED7ON_VALUE 0xef;


void semi74hc_writedata(unsigned char wda);



#endif
