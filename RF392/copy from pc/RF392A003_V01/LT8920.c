#include "BS84C12C.h"
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
#define RXPACKLOADLEN 7
#define PACKLOADLEN 19
#define SPI_SS_H { _pa7 = 1;}
#define SPI_SS_L { _pa7 = 0;}
#define LTRESET_H {_pa1 = 1;}
#define LTRESET_L {_pa1 = 0;}

#define SPI_CLK_H {_pd4= 1;}
#define SPI_CLK_L {_pd4= 0;}
#define MOSI  _pd0
#define MISO  _pd1

#define SETRST_OUT {_nop();_papu1 =0; _pac1 = 0; _pa1 = 0;}
#define SETMOSI_OUT {_nop();_pdpu0 =0; _pdc0 = 0; _pd0 = 0;}
#define SETSCK_OUT {_nop();_pdpu4 =0; _pdc4 = 0; _pd4= 0;}
#define SETMISO_IN {_nop();_pdpu1 =1; _pdc1 = 1; }
#define SETMISO_OUT {_nop();_pdpu1 =0; _pdc1 = 0; _pd1 = 1;}
#define SPI_SS_OUT {_nop();_papu7 =0; _pac7 = 0; _pa7 = 0;}


const unsigned char itykaddr0 __attribute__ ((at(0xBF8))) = 39;
const unsigned char itykaddr1 __attribute__ ((at(0xBF9))) = 0;
const unsigned char itykaddr2 __attribute__ ((at(0xBFA))) = 0;
const unsigned char itykaddr3 __attribute__ ((at(0xBFB))) = 0;

const unsigned char it8920regarry[][3]={
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
{35, 0x05, 0x00},//repeat 9- 03 00 ->-0a 20
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
//{50, 0x00, 0x00 },
};
const unsigned char it8920rftstarry[][3]={
{7, 0x00, 0x00 },
{32, 0x18, 0x07 },
{34, 0x83, 0x0b},
{11, 0x80, 0x08 },
{7, 0x01, 0x30 },//2.45g
};

/*const unsigned char it8920realdytxdata[][3]={
{41, 0xb8, 0x00},//crc on  fix leng pkt high active
{52, 0x80, 0x80},//clr tx fifo and rx fifo pointer
};*/

const unsigned char it8920sleepdata[][3]={
{35, 0x45, 0x00},//f->repeat data 00---20
};

const unsigned char it8920compttx[][3]={
{41, 0xb0, 0x00},//f->repeat data 00---20
};


//----------------------rx------------
const unsigned char it8920realdyrxdata[][3]={
{44, 0x10, 0x00 },//62.5k	
{45, 0x05, 0x52},//
};

//------------------tx---------------
const unsigned char it8920realdytxdata[][3]={
{44, 0x01, 0x00 },//1M	
{45, 0x01, 0x52},//
};

volatile unsigned int itcounter = 0;		
volatile unsigned char it8920reg = 0;
volatile unsigned char reghighvalue = 0;
volatile unsigned char reglowvalue = 0;
volatile unsigned char spicount = 0;
volatile unsigned char regIndex= 0;
volatile unsigned char RegH;
volatile unsigned char RegL;              //Used to store the Registor Value which is read.

volatile unsigned char rftxdataarry[PACKLOADLEN]={0};
volatile unsigned char itmosivalue = 0;




volatile unsigned int ittranscounter = 0;
volatile unsigned char rfmsgarry[2]= {0};
volatile unsigned char remoteTypearry[2]= {0};

//--------------------

static volatile unsigned char rftxdatadstarry[PACKLOADLEN] __attribute__((at(0x380)));
static volatile unsigned char rfrxdatadstarry[RXPACKLOADLEN] __attribute__((at(0x394)));

//--------------------------
void setRFtxReadyflag(void);
void turnonRFrxLed(void);
void turnoffRFrxLed(void);
//--------------------------
/*****************************************/
// SPI Write and Read ,as well as Read8  // 
/*****************************************/

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
			MOSI = 1;
		}
		else
		{
			MOSI = 0;
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
			MOSI = 1;
		}
		else
		{
			MOSI = 0;
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
			MOSI = 1;
		}
		else
		{
			MOSI = 0;
		}
		SPI_CLK_H ;                      
		SPI_CLK_L ;

		reglowvalue = reglowvalue << 1;
	}

	SPI_SS_H;
}

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


void SPI_READFifo(void)
{
		SETMISO_IN;
	SETSCK_OUT;
   SETMOSI_OUT;
	SPI_SS_OUT ;
	it8920reg += 0x80;                    //when reading a Register,the Address should be added with 0x80.

	for(spicount = 0; spicount < 8; spicount++)//write reg 50
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
	//RegH read the data len
	RegH = 0;
	for(spicount = 0; spicount < 8; spicount++)
	{
		SPI_CLK_H ;                      
		SPI_CLK_L ;

		RegH = RegH << 1;  
		if(MISO)
		{
			RegH |= 0x01;
		}
       else
	   {
		   RegH &= 0xfe;
	   }
		
	}

   // read the data
   for(regIndex = 0; regIndex < RegH; regIndex++)
   {
	    RegL = 0;
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
		   rfrxdatadstarry[regIndex]=RegL;
       }
   }

	SPI_SS_H;
}
	
	
/*write fifo*/
void SPI_WriteFifo(void)
{
	//SETMISO_IN;
	//SETMISO_OUT;
	SETSCK_OUT;
   SETMOSI_OUT;
	SPI_SS_OUT ;
    it8920reg = 50;
	for(spicount= 0; spicount < 8; spicount++)
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
			MOSI = 1;
		}
		else
		{
			MOSI = 0;
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
				MOSI = 1;
			}
			else
			{
				MOSI = 0;
			}

			SPI_CLK_H ;                       //capturing at the down side.
			_nop();
			SPI_CLK_L ;

			itmosivalue = itmosivalue << 1;                    //There is no Delay here. determines the rate of SPI.
		}
	}	
	
	SPI_SS_H;	
}

/**/
void LT8900_Reset(void)
{
	SETRST_OUT;
		LTRESET_L;
	  _emi = 0;
	 itcounter = 0;
	 _emi = 1;
	 do{_nop();}while(itcounter==0);
	 
	  _emi = 0;
	 itcounter = 0;
	 _emi = 1;
LTRESET_H
	
 do{_nop();}while(itcounter==0);	
	
}

void LT8900Reg_Init(void)
{

 for(regIndex = 0 ; regIndex < sizeof(it8920regarry)/3; regIndex++)
 {
it8920reg = it8920regarry[regIndex][0];
reghighvalue = it8920regarry[regIndex][1];
reglowvalue = it8920regarry[regIndex][2];
SPI_WriteReg();
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
	it8920reg = 52;
	reghighvalue =0x80;
	reglowvalue = 0x80;
	SPI_WriteReg();		 
	 
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
	it8920reg = 7;
	reghighvalue =0;
	reglowvalue = 0;
	SPI_WriteReg();	
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
	it8920reg = it8920rftstarry[regIndex][0];
	reghighvalue = it8920rftstarry[regIndex][1];
	reglowvalue = it8920rftstarry[regIndex][2];
	SPI_WriteReg();
	 }					
}
void It8920ReadyTx(void)
{
	 for(regIndex = 0 ; regIndex < sizeof(it8920realdytxdata)/3; regIndex++)
	 {
		it8920reg = it8920realdytxdata[regIndex][0];
		reghighvalue = it8920realdytxdata[regIndex][1];
		reglowvalue = it8920realdytxdata[regIndex][2];
		SPI_WriteReg();
	 }	
	 	
}
void It8920ReadyRx(void)
{
	 for(regIndex = 0 ; regIndex < sizeof(it8920realdyrxdata)/3; regIndex++)
	 {
		it8920reg = it8920realdyrxdata[regIndex][0];
		reghighvalue = it8920realdyrxdata[regIndex][1];
		reglowvalue = it8920realdyrxdata[regIndex][2];
		SPI_WriteReg();
	 }	
	
}
void It8920_EnterRx(void)
{
	it8920reg = 7;
	reghighvalue = 0x00;//
	reglowvalue = 0x88;// rx 2.410Ghz
	SPI_WriteReg();	
}

void It892_EnterTx(void)
{
	it8920reg = 7;
	reghighvalue = 0x01;//tx
	reglowvalue = 0x4a;//2.476Ghz
SPI_WriteReg();	
}					   
void LT8900_txdata(void)
{
	_emi = 0;
	 itcounter = 0;
	 _emi = 1;
    do
	{
	   _clrwdt();
        _clrwdt2();
        _clrwdt1();	
			it8920reg = 48;
		RegH = 0;
		RegL = 0;			
			SPI_ReadReg();	
		  if ( RegL & 0x40)//wait the pkt flag to set
			{
				break;
			}		
	}while(itcounter==0);

}

void LT8900_rxdata(void)
{
		do
		{	
				 _clrwdt();
                _clrwdt2();
                _clrwdt1();
			   _nop();
			   turnonRFrxLed();
			it8920reg = 48;
RegH = 0;
RegL = 0;			
			SPI_ReadReg();	
		  if ( RegL & 0x40)//wait the pkt flag to set
			{
				break;
			}
		}while(1);	
	It8920_Idle();
	if((RegH & 0x80) == 0)
	{
		//received the data 
		it8920reg = 50;
		SPI_READFifo();
		ittranscounter = rfrxdatadstarry[2];
		 ittranscounter |= rfrxdatadstarry[1] << 8;
		rfmsgarry[0] = rfrxdatadstarry[3] ;
		rfmsgarry[1] = rfrxdatadstarry[4] ;
		
		remoteTypearry[0] = rfrxdatadstarry[5];
		remoteTypearry[1] = rfrxdatadstarry[6];
		
		turnoffRFrxLed();
		setRFtxReadyflag();
	}
}
void It8920_filldata(void)
{
rftxdataarry[0] = 0;	
rftxdataarry[1] = 0;	
rftxdataarry[2] = 0;
rftxdataarry[3] = 0;
// rftxdataarry[4] = 0;
// rftxdataarry[5] = 0;	
// rftxdataarry[6] = 0;	
// rftxdataarry[7] = 0;	
// rftxdataarry[8] = 0;	
rftxdataarry[9] =0x13;	//data leng 19
rftxdataarry[10] = ittranscounter>>8;	//fa song pi ci
rftxdataarry[11] = ittranscounter;	
//rftxdataarry[12] = 0; rev
//rftxdataarry[13] = 0;	
rftxdataarry[14] = rfmsgarry[0];//msg	
rftxdataarry[15] = rfmsgarry[1];		
rftxdataarry[16] = remoteTypearry[0];	//rev	
rftxdataarry[17] = remoteTypearry[1];//hilink / homekit flag
rftxdataarry[18] = 1;
// rftxdataarry[0] = 0xb2;	
 // rftxdataarry[1] = 0xb2;	
 // rftxdataarry[2] = 0x07;
// rftxdataarry[3] = 0xaa;		
// rftxdataarry[4] = 0xbb;	//1CH
// rftxdataarry[5] = 0x1e;	
// rftxdataarry[6] = 0x1f;//on
}

void It8920_encryptdata(void)
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
}


void It8920_Sleep(void)
{
		/*go to sleep*/
	 for(regIndex = 0 ; regIndex < sizeof(it8920sleepdata)/3; regIndex++)
	 {
	it8920reg = it8920sleepdata[regIndex][0];
	reghighvalue = it8920sleepdata[regIndex][1];
	reglowvalue = it8920sleepdata[regIndex][2];
	SPI_WriteReg();
	 }
}