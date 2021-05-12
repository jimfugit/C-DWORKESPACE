
//#include "gpio.h"
#include "board_efm8sb.h"
#include "lt8920.h"
//extern stc_gpio_cfg_t lt8920_outCfg;

#define _nop() NOP()
/*
********************************
spiss ---pa7
spiclk----pd4
pkt ----no connect
mosi----pd0
miso-----pd1
reset----pa1
*******************************
*/
#define PACKLOADLEN 19
#define WRITEFIFOLEN PACKLOADLEN + 2
#define SPI_SS_H { LT8920_SPISS_PIN = 1;}//p14
#define SPI_SS_L { LT8920_SPISS_PIN = 0;}
#define LTRESET_H { LT8920_RESET_PIN = 1;}
#define LTRESET_L {LT8920_RESET_PIN = 0;}

#define SPI_CLK_H {LT8920_SPICLK_PIN = 1;}
#define SPI_CLK_L {LT8920_SPICLK_PIN = 0;}

#define MOSI_H {LT8920_MOSI_PIN = 1;}
#define MOSI_L {LT8920_MOSI_PIN = 0;}
//#define MOSI  _pd0
#define MISO  P1_B2

#define SETRST_OUT {LT8920_RESET_PIN = 0;}
#define SETMOSI_OUT {LT8920_MOSI_PIN = 0;}
#define SETSCK_OUT {LT8920_SPICLK_PIN = 0;}
#define SETMISO_IN //{_nop();_pdpu1 =1; _pdc1 = 1; }
#define SETMISO_OUT {LT8920_MISO_PIN = 1;}
#define SPI_SS_OUT { LT8920_SPISS_PIN = 0;}

/*hlink-��ַ����ʱ��3��ַ�̶�Ϊһ��ֵ�������ֽ�ʵ���ۼ�*/
//char xdata LED_Data[50] _at_ 0x8000;
#ifdef USERDEBUGID
const unsigned char itykaddr0 __attribute__ ((at(0xBF8))) = 19;
const unsigned char itykaddr1 __attribute__ ((at(0xBF9))) = 0;
const unsigned char itykaddr2 __attribute__ ((at(0xBFA))) = 0;
const unsigned char itykaddr3 __attribute__ ((at(0xBFB))) = 0xb1;

unsigned char itykaddr0 = 0;
unsigned char itykaddr1 = 0;
unsigned char itykaddr2 = 0;
unsigned char itykaddr3 = 0 ;
 
#else
// volatile unsigned char itykaddr0 = 0;
// volatile unsigned char itykaddr1 = 0;
// volatile unsigned char itykaddr2 = 0;
// volatile unsigned char itykaddr3 = 0 ;

  //unsigned char code itykaddr0  _at_ 0x8000;
	//	int variable1[100] __attribute__((at(0x00030))); 0x0000_4000
//unsigned char itykaddr[4] __attribute__((section(".ARM.__at_0x00003FF0"))) = {1,2,3,4};
unsigned char code itykaddr[4] _at_ 0x1FFA;
//unsigned char itykaddr1 __attribute__((section(".ARM.__at_0x00003FF1"))) = 0x00;
#define itykaddr0 itykaddr[0] 
#define itykaddr1 itykaddr[1] 
#define itykaddr2 itykaddr[2]
#define itykaddr3 itykaddr[3]
#endif


const unsigned char code it8920regarry[][3]={


{ 0, 0x6f, 0xe0 },
{ 1, 0x56, 0x81 },
{2, 0x66, 0x17},
{4, 0x9c, 0xc9 },
{5, 0x66, 0x37},
{7, 0x00, 0x00},
{8, 0x6c, 0x90},
{9, 0x48, 0x00 },
{10, 0x7f, 0xfd},
{11, 0x00, 0x08},
{12, 0x00, 0x00 },
{13, 0x48, 0xbd},
{22, 0x00, 0xff},
{23, 0x80, 0x05},
{24, 0x00, 0x67},
{25, 0x16, 0x59},
{26, 0x19, 0xe0},
{27, 0x13, 0x00},
{28, 0x18, 0x00},
{32, 0x48, 0x00 },
{33, 0x3f, 0xc7},
{34, 0x20, 0x00},
{35, 0x03, 0x00},//repeat 9- 03 00 ->-0a 20
{36, 0x05, 0x0a},
{37, 0x03, 0x80},
{38, 0x5a, 0x5a},
{39, 0x55, 0xaa},
{40, 0x44, 0x02},//01---02
{41, 0xb8, 0x00},//pkt high active
{42, 0xfd, 0xb0},
{43, 0x00, 0x0f },
{44, 0x01, 0x00 },
{45, 0x01, 0x52},


};




const unsigned char code it8920rftstarry[][3]={
{7, 0x00, 0x00 },
{32, 0x18, 0x07 },
{34, 0x83, 0x0b},
{11, 0x80, 0x08 },
{7, 0x01, 0x30 },//2.45g
};

const unsigned char code it8920realdytxdata[][3]={
{41, 0xb8, 0x00},//crc on  fix leng pkt high active
{52, 0x80, 0x80},//clr tx fifo and rx fifo pointer
};

const unsigned char code it8920sleepdata[][3]={
{35, 0x45, 0x00},//f->repeat data 00---20
};

const unsigned char code it8920compttx[][3]={
{41, 0xb0, 0x00},//f->repeat data 00---20
};

const unsigned char code it8920realdyrxdata[][3]={
{52, 0x80, 0x80},//clr tx fifo and rx fifo pointer

};

//unsigned  int xdata itcounter = 0;
unsigned  char xdata it8920reg = 0;
unsigned  char xdata reghighvalue = 0;
unsigned  char xdata reglowvalue = 0;
volatile unsigned  char xdata spicount = 0;
unsigned  char xdata regIndex= 0;
unsigned  char xdata RegH;
unsigned  char xdata RegL;              //Used to store the Registor Value which is read.


unsigned  char  rftxdataarry[PACKLOADLEN]={0};
unsigned  char xdata itmosivalue = 0;
unsigned char xdata lastrffifo[WRITEFIFOLEN]={0};



unsigned int xdata ittranscounter = 0;
unsigned char xdata rfmsgarry[2]= {0};

extern unsigned int xdata keypaizangrlstimer;
//-------------------
//unsigned char  eeprom_Read(void);
//extern volatile unsigned char EE_read_addr;
//--------------------

//static volatile unsigned char rftxdatadstarry[PACKLOADLEN];
//static volatile unsigned char rfrxdatadstarry[PACKLOADLEN];
/*****************************************/
// SPI Write and Read ,as well as Read8  // 
/*****************************************/
void SPI_WriteReg(unsigned char regval, unsigned char hval,unsigned char lval)
{

  //SETMISO_IN;
  //SETMISO_OUT;
  volatile unsigned char regarry[3];
  volatile unsigned char mosival,i,j;
  regarry[0] = regval;
  regarry[1] = hval;
  regarry[2] = lval;
  delay1ms(1);
  SETSCK_OUT;
  SPI_SS_OUT ;

  for(j=0;j<3;j++)
    {
      mosival = regarry[j];
      for(i= 0; i < 8; i++)
      //for(spicount= 0; spicount < 8; spicount++)
      {
        //MOSI = addr & 0x80;
        if(mosival & 0x80)
        {
          //MOSI = 1;
          MOSI_H;
        }
        else
        {
          //MOSI = 0;
          MOSI_L;
        }
        app_delay10us(3);
        SPI_CLK_H ;                       //capturing at the down side.
        app_delay10us(3);
        SPI_CLK_L ;
        mosival = mosival << 1;                    //There is no Delay here. determines the rate of SPI.
      }
    }

  SPI_SS_H;
  app_delay10us(2);

}

#ifdef SPI_OLDFIFO
void SPI_WriteReg(void)
{
	//SETMISO_IN;
	//SETMISO_OUT;
	SETSCK_OUT;
   SETMOSI_OUT;
	SPI_SS_OUT ;

	for(spicount= 0; spicount < 8; spicount++)
	{
		//MOSI = addr & 0x80;
		if(it8920reg & 0x80)
		{
			//MOSI = 1;
			MOSI_H;
		}
		else
		{
			//MOSI = 0;
			MOSI_L;
		}

		SPI_CLK_H ;                       //capturing at the down side.
		SPI_CLK_L ;

		it8920reg = it8920reg << 1;                    //There is no Delay here. determines the rate of SPI.
	}

	for(spicount= 0; spicount < 8; spicount++)                 //Write H
	{
		
		//MOSI = H & 0x80;
		if( reghighvalue & 0x80)
		{
			//MOSI = 1;
			MOSI_H;
		}
		else
		{
			//MOSI = 0;
			MOSI_L;
		}
		
		SPI_CLK_H ;                       //capturing at the down side.
		SPI_CLK_L ;

		reghighvalue = reghighvalue << 1;
	}

	for(spicount = 0; spicount < 8; spicount++)                 //Write L
	{  
		//MOSI = L & 0x80;
        if(reglowvalue & 0x80)
		{
			//MOSI = 1;
			MOSI_H;
		}
		else
		{
			//MOSI = 0;
			MOSI_L;
		}
		SPI_CLK_H ;                      
		SPI_CLK_L ;

		reglowvalue = reglowvalue << 1;
	}

	//-SPI_SS_H;
}
#endif

void SPI_WriteFifo(void)
{

  unsigned char i ,j;
  lastrffifo[0]=50;
  lastrffifo[1]=PACKLOADLEN;
  for(i=2,j=0;j<PACKLOADLEN;i++,j++)
    {
      lastrffifo[i] = rftxdataarry[j];
    }
  delay1ms(1);
  SETSCK_OUT;
   //SETMOSI_OUT;
  SPI_SS_OUT ;
  /*write data*/
 // for(regIndex = 0 ; regIndex < PACKLOADLEN; regIndex++)
  for(i=0;i<WRITEFIFOLEN;i++)
  {
    itmosivalue = lastrffifo[i];
    for(j= 0; j < 8; j++)
    {
      if(itmosivalue & 0x80)
      {
        //MOSI = 1;
        MOSI_H;
      }
      else
      {
        //MOSI = 0;
        MOSI_L;
      }
      app_delay10us(3);
      SPI_CLK_H ;                       //capturing at the down side.
      app_delay10us(3);
      SPI_CLK_L ;

      itmosivalue = itmosivalue << 1;                    //There is no Delay here. determines the rate of SPI.
    }
  }

  SPI_SS_H;
  app_delay10us(2);

}

void SPI_ReadReg(unsigned char ltreg)
{
  unsigned char tmpreg,i;
  unsigned char tmpdataH = 0,tmpdataL = 0;
  //SETMISO_IN;
SETSCK_OUT;
 //SETMOSI_OUT;
SPI_SS_OUT ;
  tmpreg = ltreg | 0x80;

  for(i = 0; i < 8; i++)
  {
    //MOSI = addr & 0x80;
        if(tmpreg & 0x80)
    {
     // MOSI = 1;
            MOSI_H;
    }
    else
    {
      //MOSI = 0;
        MOSI_L;
    }

        app_delay10us(1);
    SPI_CLK_H ;
    app_delay10us(1);
    SPI_CLK_L ;

    tmpreg = tmpreg << 1;                      //Move one bit to the left.
  }
  app_delay10us(1);
  for(i = 0; i < 8; i++)
  {
    SPI_CLK_H ;
    app_delay10us(1);
    SPI_CLK_L ;
    app_delay10us(1);
    tmpdataH = tmpdataH << 1;
    if(MISO)
    {
        tmpdataH |= 1;
    }
       else
     {
           tmpdataH &= 0xfe;
     }

  }
  RegH = tmpdataH;
  app_delay10us(1);
  for(i= 0; i < 8; i++)
  {
    SPI_CLK_H ;
    app_delay10us(1);
    SPI_CLK_L ;
    app_delay10us(1);
    tmpdataL = tmpdataL << 1;
    if(MISO)
    {
        tmpdataL |= 1;
    }
       else
     {
           tmpdataL &= 0xfe;
     }

    //RegL |= MISO;
  }
  RegL =tmpdataL;
  SPI_SS_H;
}
#ifdef SPI_OLDFIFO
void SPI_ReadReg(void)
{
    SETMISO_IN;
  SETSCK_OUT;
   SETMOSI_OUT;
  SPI_SS_OUT ;
  //SPI_SS = 0;
  it8920reg += 0x80;                    //when reading a Register,the Address should be added with 0x80.

  for(spicount = 0; spicount < 8; spicount++)
  {
    //MOSI = addr & 0x80;
        if(it8920reg & 0x80)
    {
      MOSI = 1;
    }
    else
    {
      MOSI = 0;
    }
    SPI_CLK_H ;
    SPI_CLK_L ;

    it8920reg = it8920reg << 1;                      //Move one bit to the left.
  }

  for(spicount = 0; spicount < 8; spicount++)
  {
    SPI_CLK_H ;
    SPI_CLK_L ;

    RegH = RegH << 1;
    if(MISO)
    {
      RegH |= 1;
    }
       else
     {
       RegH &= 0xfe;
     }

  }



  for(spicount= 0; spicount < 8; spicount++)
  {
    SPI_CLK_H ;
    SPI_CLK_L ;

    RegL = RegL << 1;
    if(MISO)
    {
      RegL |= 1;
    }
       else
     {
       RegL &= 0xfe;
     }

    //RegL |= MISO;
  }

  SPI_SS_H;
}
#endif
	
#ifdef SPI_OLDFIFO
/*write fifo*/
void SPI_WriteFifo(void)
{

	//SETMISO_IN;
	//SETMISO_OUT;
	SETSCK_OUT;
   //SETMOSI_OUT;
	SPI_SS_OUT ;
    it8920reg = 50;
	for(spicount= 0; spicount < 8; spicount++)
	{
		//MOSI = addr & 0x80;
		if(it8920reg & 0x80)
		{
			//MOSI = 1;
			MOSI_H;
		}
		else
		{
			//MOSI = 0;
			MOSI_L;
		}

		SPI_CLK_H ;                       //capturing at the down side.
		_nop();
		SPI_CLK_L ;

		it8920reg = it8920reg << 1;                    //There is no Delay here. determines the rate of SPI.
	}
	/*write leng*/
	itmosivalue = PACKLOADLEN;
	for(spicount= 0; spicount < 8; spicount++)
	{
		if(itmosivalue & 0x80)
		{
			//MOSI = 1;
			MOSI_H;
		}
		else
		{
			//MOSI = 0;
			MOSI_L;
		}

		SPI_CLK_H ;                       //capturing at the down side.
		_nop();
		SPI_CLK_L ;

		itmosivalue = itmosivalue << 1;                    //There is no Delay here. determines the rate of SPI.
	}
	/*write data*/
	for(regIndex = 0 ; regIndex < PACKLOADLEN; regIndex++)
	{
		itmosivalue = rftxdataarry[regIndex];
		for(spicount= 0; spicount < 8; spicount++)
		{
			if(itmosivalue & 0x80)
			{
				//MOSI = 1;
				MOSI_H;
			}
			else
			{
				//MOSI = 0;
				MOSI_L;
			}

			SPI_CLK_H ;                       //capturing at the down side.
			_nop();
			SPI_CLK_L ;

			itmosivalue = itmosivalue << 1;                    //There is no Delay here. determines the rate of SPI.
		}
	}	
	
	SPI_SS_H;	

}
#endif
/**/
void LT8900_Reset(void)
{

	//SETRST_OUT;
		LTRESET_L;
//	  _emi = 0;
//	 itcounter = 0;
//	 _emi = 1;
//	 do{_nop();}while(itcounter==0);
	 delay1ms(10);//10ms
//	  _emi = 0;
//	 itcounter = 0;
//	 _emi = 1;
LTRESET_H
	
 //do{_nop();}while(itcounter==0);	
delay1ms(10);//10ms




}

void LT8900Reg_Init(void)
{

 for(regIndex = 0 ; regIndex < sizeof(it8920regarry)/3; regIndex++)
 {
//it8920reg = it8920regarry[regIndex][0];
//reghighvalue = it8920regarry[regIndex][1];
//reglowvalue = it8920regarry[regIndex][2];
//SPI_WriteReg();
 SPI_WriteReg(it8920regarry[regIndex][0], it8920regarry[regIndex][1],it8920regarry[regIndex][2]);
 }
 	 // it8920reg = 4;
		// SPI_ReadReg();
	// if ((RegH==0x9c) && (RegL==0xc9))
	// {
		// _nop();
	// }
	
 	 // it8920reg = 26;
		// SPI_ReadReg();
 	 // it8920reg = 27;
		// SPI_ReadReg();
 	 // it8920reg = 23;
		// SPI_ReadReg();		

}
 void It8920_ResetFifo(void)
 {

	//it8920reg = 52;
	//reghighvalue =0x80;
	//reglowvalue = 0x80;
	//SPI_WriteReg();
	SPI_WriteReg(52,0x80,0x80);

 }
 
 void It8920_Idle(void)
{

		// SPI_SS_L ;
	// _emi = 0;
	 // itcounter = 0;
	 // _emi = 1;
    // do
	// {
	   // _clrwdt();
        // _clrwdt2();
        // _clrwdt1();		
	// }while(itcounter<=1);
	// SPI_SS_H;
	//it8920reg = 7;
	//reghighvalue =0;
	//reglowvalue = 0;
	//SPI_WriteReg();
	SPI_WriteReg(7,0,0);


}

	 // it8920reg = 4;
		// SPI_ReadReg();
	// if ((RegH==0x9c) && (RegL==0xc9))
	// {
		// _nop();
	// }
	


void LT8900rf_test(void)
{

	 for(regIndex = 0 ; regIndex < sizeof(it8920rftstarry)/3; regIndex++)
	 {
	//it8920reg = it8920rftstarry[regIndex][0];
	//reghighvalue = it8920rftstarry[regIndex][1];
	//reglowvalue = it8920rftstarry[regIndex][2];
	//SPI_WriteReg();
	 SPI_WriteReg(it8920rftstarry[regIndex][0],it8920rftstarry[regIndex][1],it8920rftstarry[regIndex][2]);
	 }

}

void It8920_EnterRx(void)
{

	//it8920reg = 7;
	//reghighvalue = 0x00;//
	//reglowvalue = 0xca;// rx 2.476Ghz
	//SPI_WriteReg();
	SPI_WriteReg(7,0,0xca);

}

void It892_EnterTx(void)
{


	//it8920reg = 7;
	//reghighvalue = 0x01;//tx
	//reglowvalue = 0x4a;//2.476Ghz
//SPI_WriteReg();
  SPI_WriteReg(7,0x01,0x4a);

}					   
void LT8900_txdata(void)
{

	/*_emi = 0;
	 itcounter = 0;
	 _emi = 1;
    do
	{
	   _clrwdt();
        _clrwdt2();
        _clrwdt1();		
	}while(itcounter==0);*/
	
	/*for(regIndex = 1; regIndex < 100; regIndex++)//50
	{
		_nop();
	}*/
  delay1ms(10);

}



extern unsigned char xdata keyvalue ;
void It8920_filldata(void)
{

	#ifdef USERDEBUGID
	rftxdataarry[0] = itykaddr3;	//type
	rftxdataarry[1] = itykaddr0;	
	rftxdataarry[2] = itykaddr1;
	rftxdataarry[3] = itykaddr2;	
	#else
//	EE_read_addr = 0;
//	itykaddr0 = eeprom_Read();
//	EE_read_addr = 1;
//	itykaddr1 = eeprom_Read();
//	EE_read_addr = 2;
//	itykaddr2 = eeprom_Read();
//	EE_read_addr = 3;
//	itykaddr3 = eeprom_Read();
	
	if((itykaddr3 == 0xff) && (itykaddr2 == 0xff) && (itykaddr1 == 0xff) && (itykaddr0 == 0xff))
	{
	  //itykaddr3 = 0xb1;
	  //itykaddr2 = 0x00;
	  //itykaddr1 = 0x00;
	  //itykaddr0 = 0x00;
	    rftxdataarry[0] = 0x55;  //type
	    rftxdataarry[1] = 0x01;
	    rftxdataarry[2] = 0x01;//1,2,3,4,5,6,7,8
	    rftxdataarry[3] = 0x32;
	}	
	else
	  {
	rftxdataarry[0] = itykaddr3;	//type
	rftxdataarry[1] = itykaddr0;	
	rftxdataarry[2] = itykaddr1;
	rftxdataarry[3] = itykaddr2;	
	  }
	#endif	

// rftxdataarry[4] = 0;
// rftxdataarry[5] = 0;	
// rftxdataarry[6] = keypaizangrlstimer;
// rftxdataarry[7] = 0;	
// rftxdataarry[8] = 0;	
rftxdataarry[9] =0x13;	//data leng 19
rftxdataarry[10] = ittranscounter>>8;	//fa song pi ci
rftxdataarry[11] = ittranscounter;	
//rftxdataarry[12] = 0x00; 
//rftxdataarry[13] = 0x57;//hlink	
rftxdataarry[14] = rfmsgarry[0];//msg	
rftxdataarry[15] = rfmsgarry[1];		
rftxdataarry[16] = 0x00;	//	
rftxdataarry[17] = 0x57; //hlink
rftxdataarry[18] = keyvalue;//1-
// rftxdataarry[0] = 0xb2;	
 // rftxdataarry[1] = 0xb2;	
 // rftxdataarry[2] = 0x07;
// rftxdataarry[3] = 0xaa;		
// rftxdataarry[4] = 0xbb;	//1CH
// rftxdataarry[5] = 0x1e;	
// rftxdataarry[6] = 0x1f;//on

}

/*void It8920_encryptdata(void)
{
	rftxdatadstarry[0] = rftxdataarry[0]^0xbd;
	//rftxdatadstarry[1] = rftxdataarry[1]^0xbd;
	for(regIndex = 1; regIndex < PACKLOADLEN; regIndex++)
	{
		rftxdatadstarry[regIndex] = rftxdataarry[regIndex] ^ rftxdatadstarry[regIndex - 1];
	}
		for(regIndex = 0; regIndex < PACKLOADLEN; regIndex++)
	{
		rftxdataarry[regIndex] = rftxdatadstarry[regIndex];
	}
}*/


void It8920_Sleep(void)
{

		/*go to sleep*/
	 for(regIndex = 0 ; regIndex < sizeof(it8920sleepdata)/3; regIndex++)
	 {
	//it8920reg = it8920sleepdata[regIndex][0];
	//reghighvalue = it8920sleepdata[regIndex][1];
	//reglowvalue = it8920sleepdata[regIndex][2];
	//SPI_WriteReg();
	     SPI_WriteReg(it8920sleepdata[regIndex][0],it8920sleepdata[regIndex][1],it8920sleepdata[regIndex][2]);
	 }
	 //P1_B5 = 1;
}

void user8920_txdata(void)
{
  It8920_Idle();
 It8920_ResetFifo();
 It8920_filldata();
 SPI_WriteFifo();
 It892_EnterTx();
 LT8900_txdata();
 It8920_Idle();
 It8920_Sleep();

}
