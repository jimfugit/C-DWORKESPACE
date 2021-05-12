#include "BS84C12C.h"

volatile unsigned char EE_write_addr = 0;
volatile unsigned char EE_write_data = 0;
volatile unsigned char EE_read_addr = 0;

void eeprom_Write(void)			//写一字节到指定地址
{
	
	_eea = EE_write_addr;
	_eed = EE_write_data;

	_mp1=0x40;//point EEC
	_bp=0x01;// select bank1
	
    _emi=0;//disable interrupt
    
	_iar1|=0x08;//enable wren	
	_iar1|=0x04;//initial a write nop
	
	_emi=1;	
	while((_iar1&0b00000100)==0b00000100)//check wr
	{
	              _clrwdt();
                _clrwdt2();
                _clrwdt1();
	}		
	_iar1=0x00;//disable write
	_bp=0x00;//select bank0
	/*_emi=1;*/
}


unsigned char  eeprom_Read(void)								//读取指定地址的一个字节
{
/*	_emi=0;*/
	_eea=EE_read_addr;
	_mp1=0x40;	
	_bp=0x01;	
	
	_iar1|=0x02;
	_iar1|=0x01;	
	while((_iar1&0b00000001)==0b00000001)
	{
	              _clrwdt();
                _clrwdt2();
                _clrwdt1();
	}
	_iar1=0x00;
	_bp=0x00;		
/*	_emi=1;*/
	return(_eed);
}






