#include "..\USER_PROGRAM\USER_PROGRAM.CEX"
#include "..\BS84C12C_LIBV413\BS84C12C_LIBV413.CEX"
#include "BS84C12C.h"
#define SW_FACTORYVER 1
#define TouchKeyAmount 7

#define CLRLED_LONGPRESS_TIMER 63//63 500ms  37 300ms 
/* led define   hilink xiao ye deng*/
// #define LED1TURNON {_pdpu5 =0; _pdc5 = 0; _pd5= 0;_papu3 =0; _pac3 = 0; _pa3 = 0;}
// #define LED1TURNOFF {_pdpu5 =0;_pdc5 = 0; _pd5= 1;_papu3 =0;  _pac3 = 0; _pa3 = 1;}

// #define LED2TURNON {_pdpu5 =0; _pdc5 = 0; _pd5= 0;_pdpu0 =0; _pdc0 = 0; _pd0 = 0;}//pd0->pd5
// #define LED2TURNOFF {_pdpu5 =0; _pdc5 = 0; _pd5= 1; _pdpu0 =0; _pdc0 = 0; _pd0 = 1;}

// #define LED3TURNON {_pdpu5 =0; _pdc5 = 0; _pd5= 0;_pdpu1 =0; _pdc1 = 0; _pd1 = 0;}
// #define LED3TURNOFF {_pdpu5 =0; _pdc5 = 0; _pd5= 1;_pdpu1 =0; _pdc1 = 0; _pd1 = 1;}

// #define LED4TURNON {_pdpu5 =0; _pdc5 = 0; _pd5= 0;_papu2 =0; _pac2 = 0; _pa2 = 0;}//pa2
// #define LED4TURNOFF {_pdpu5 =0; _pdc5 = 0; _pd5= 1;_papu2 =0; _pac2 = 0; _pa2 = 1;}

// #define LED5TURNON {_pdpu5 =0; _pdc5 = 0; _pd5= 0;_papu0 =0; _pac0 = 0; _pa0 = 0;}
// #define LED5TURNOFF {_pdpu5 =0; _pdc5 = 0; _pd5= 1; _papu0 =0; _pac0 = 0; _pa0 = 1;}

// #define LED6TURNON {_pdpu5 =0; _pdc5 = 0; _pd5= 0;_papu4 =0; _pac4 = 0; _pa4 = 0;}
// #define LED6TURNOFF {_pdpu5 =0; _pdc5 = 0; _pd5= 1;_papu4 =0; _pac4 = 0; _pa4 = 1;}

// #define LED7TURNON {_pdpu5 =0; _pdc5 = 0; _pd5= 0;_pbpu7 =0; _pbc7 = 0; _pb7 = 0;}
// #define LED7TURNOFF {_pdpu5 =0; _pdc5 = 0; _pd5= 1;_pbpu7 =0; _pbc7 = 0; _pb7 = 1;}

//-----------------
// #define LED1TURNON {_papu3 =0; _pac3 = 0; _pa3 = 0;}
// #define LED1TURNOFF {_papu3 =0;  _pac3 = 0; _pa3 = 1;}

// #define LED2TURNON {_pdpu5 =0; _pdc5 = 0; _pd5 = 0;}//pd0->pd5
// #define LED2TURNOFF { _pdpu5 =0; _pdc5 = 0; _pd5 = 1;}

// #define LED3TURNON {_pdpu1 =0; _pdc1 = 0; _pd1 = 0;}
// #define LED3TURNOFF {_pdpu1 =0; _pdc1 = 0; _pd1 = 1;}

// #define LED4TURNON {_papu2 =0; _pac2 = 0; _pa2 = 0;}//pa2
// #define LED4TURNOFF {_papu2 =0; _pac2 = 0; _pa2 = 1;}

// #define LED5TURNON {_papu0 =0; _pac0 = 0; _pa0 = 0;}
// #define LED5TURNOFF { _papu0 =0; _pac0 = 0; _pa0 = 1;}

// #define LED6TURNON {_papu4 =0; _pac4 = 0; _pa4 = 0;}
// #define LED6TURNOFF {_papu4 =0; _pac4 = 0; _pa4 = 1;}

// #define LED7TURNON {_pbpu7 =0; _pbc7 = 0; _pb7 = 0;}
// #define LED7TURNOFF {_pbpu7 =0; _pbc7 = 0; _pb7 = 1;}

//----------------------------------
/*#define LED1TURNON  _pa4 = 0
#define LED1TURNOFF  _pa4 = 1
#define LED1TURNINIT {_papu4 =0;  _pac4 = 0; _pa4 = 1;}

#define LED2TURNON  _pa3 = 0
#define LED2TURNOFF _pa3 = 1
#define LED2TURNINIT {_papu3 =0;  _pac3 = 0; _pa3 = 1;}

#define LED3TURNON  _pa2 = 0
#define LED3TURNOFF  _pa2 = 1
#define LED3TURNINIT {_papu2 =0; _pac2 = 0; _pa2 = 1;}

#define LED4TURNON   _pa0 = 0
#define LED4TURNOFF  _pa0 = 1
#define LED4TURNINIT { _papu0 =0; _pac0 = 0; _pa0 = 1;}

#define LED5TURNON  _pd1 = 0
#define LED5TURNOFF _pd1 = 1
#define LED5TURNINIT {_pdpu1 =0; _pdc1 = 0; _pd1 = 1;}

#define LED6TURNON _pd5 = 0
#define LED6TURNOFF _pd5 = 1
#define LED6TURNINIT{_pdpu5 =0; _pdc5 = 0; _pd5 = 1;}

#define LED7TURNON  _pb7 = 0
#define LED7TURNOFF _pb7 = 1
#define LED7TURNINIT {_pbpu7 =0; _pbc7 = 0; _pb7 = 1;}*/
//-#define LED1TURNON {_papu3 =0; _pac3 = 0; _pa3 = 0;}
//-#define LED1TURNOFF {_papu3 =0;  _pac3 = 0; _pa3 = 1;}
#define LED1TURNON {_papu4 =0; _pac4 = 0; _pa4 = 0;}
#define LED1TURNOFF {_papu4 =0;  _pac4 = 0; _pa4 = 1;}

//-#define LED2TURNON {_pdpu5 =0; _pdc5 = 0; _pd5 = 0;}//pd0->pd5
//-#define LED2TURNOFF { _pdpu5 =0; _pdc5 = 0; _pd5 = 1;}
#define LED2TURNON {_papu3 =0; _pac3 = 0; _pa3 = 0;}
#define LED2TURNOFF{_papu3 =0;  _pac3 = 0; _pa3 = 1;}

//-#define LED3TURNON {_pdpu1 =0; _pdc1 = 0; _pd1 = 0;}
//-#define LED3TURNOFF {_pdpu1 =0; _pdc1 = 0; _pd1 = 1;}

#define LED3TURNON {_papu2 =0; _pac2 = 0; _pa2 = 0;}//pa2
#define LED3TURNOFF {_papu2 =0; _pac2 = 0; _pa2 = 1;}

//-#define LED4TURNON {_papu2 =0; _pac2 = 0; _pa2 = 0;}//pa2
//-#define LED4TURNOFF {_papu2 =0; _pac2 = 0; _pa2 = 1;}
#define LED4TURNON {_papu0 =0; _pac0 = 0; _pa0 = 0;}
#define LED4TURNOFF{ _papu0 =0; _pac0 = 0; _pa0 = 1;}

//-#define LED5TURNON {_papu0 =0; _pac0 = 0; _pa0 = 0;}
//-#define LED5TURNOFF { _papu0 =0; _pac0 = 0; _pa0 = 1;}

#define LED5TURNON  {_pdpu1 =0; _pdc1 = 0; _pd1 = 0;}
#define LED5TURNOFF {_pdpu1 =0; _pdc1 = 0; _pd1 = 1;}

//-#define LED6TURNON {_papu4 =0; _pac4 = 0; _pa4 = 0;}
//-#define LED6TURNOFF {_papu4 =0; _pac4 = 0; _pa4 = 1;}
#define LED6TURNON {_pdpu5 =0; _pdc5 = 0; _pd5 = 0;}
#define LED6TURNOFF {_pdpu5 =0; _pdc5 = 0; _pd5 = 1;}

#define LED7TURNON {_pbpu7 =0; _pbc7 = 0; _pb7 = 0;}
#define LED7TURNOFF {_pbpu7 =0; _pbc7 = 0; _pb7 = 1;}

volatile unsigned char keyvalue = 0;
volatile unsigned char pkeyvalue = 0;
volatile unsigned char keytempvalue = 0;
volatile unsigned char keycount = 0;
volatile unsigned int keyledtimer = 0;//8ms
volatile unsigned int keypairtimer = 0;//
volatile unsigned int keypresstimer = 0;
//unsigned char tempcount = 0;
volatile unsigned char K7paircounter = 0;
volatile unsigned char keyonlyrlstxtimer = 0;

volatile unsigned char keyonlyhuanqitimer = 0;

//unsigned char preusertmpvalue = 0;
volatile unsigned char usertmpvalue = 0;
volatile unsigned char krlsrftxtimer = 0;


volatile _TKS_FLAGA_type  userflag1;
#define KtimerstartF		userflag1.bits.b0
#define KLedtimerstartF		userflag1.bits.b1
#define KrfittimerstartF		userflag1.bits.b2
#define KpairtimerstartF		userflag1.bits.b3
#define KhuanqirlsF          userflag1.bits.b4
#define usernouse0          userflag1.bits.b5
#define KonlyrlstxF          userflag1.bits.b6
#define KmachPtimerF          userflag1.bits.b7

volatile _TKS_FLAGA_type  userflag2;
#define KrepeatdataF		userflag2.bits.b0
#define KsleephaveF		userflag2.bits.b1
#define KwakupF		userflag2.bits.b2
#define KzhaomingrlsF		userflag2.bits.b3
#define KmuyurlsF		userflag2.bits.b4
#define KjinhuarlsF		userflag2.bits.b5
#define KganzaorlsF		userflag2.bits.b6
#define keypressdownF   userflag2.bits.b7


volatile _TKS_FLAGA_type  userflag3;
#define KpairEnterF		userflag3.bits.b0
#define KqiruanrlsF		userflag3.bits.b1
#define KyijianguanjirlsF		userflag3.bits.b2
#define KmultizhaomingF		userflag3.bits.b3
#define KmultiwifiRestF		userflag3.bits.b4
#define KlonghuanqiF		userflag3.bits.b5
#define KmultizhaomingrlsF		userflag3.bits.b6
#define KinitRfstartF		        userflag3.bits.b7
volatile _TKS_FLAGA_type  userflag4;
#define K7zhaomingpressF userflag4.bits.b0
#define K7zhaomingrelaseF userflag4.bits.b1
#define Khavepressflag userflag4.bits.b2
#define keymachpressflag  userflag4.bits.b3 
#define keymachpresszmflag  userflag4.bits.b4 
#define KhuanqirlsPressF    userflag4.bits.b5
#define KhuanqiPressStartF    userflag4.bits.b6
#define keymachlongfunflag  userflag4.bits.b7

volatile _TKS_FLAGA_type  userflag5;

#define ledzhaomingF userflag5.bits.b0
#define ledqiruanF userflag5.bits.b1
#define ledliangfengF userflag5.bits.b2
#define ledyijiguanjiF  userflag5.bits.b3 
#define ledganzaoF  userflag5.bits.b4 
#define ledmuyuF  userflag5.bits.b5
#define ledhuangqiF  userflag5.bits.b6
#define ledidicatestartF userflag5.bits.b7

static volatile unsigned char tempcount __attribute__((at(0x393)));

//----------------------
volatile unsigned char keysamecounter = 0;
volatile unsigned char keysamerepeatflag = 1;
volatile unsigned int keymachtimer = 0;

volatile unsigned int keyledidicatetimer= 0;
//----------------------
//extern volatile unsigned char txtimercounter ;
extern volatile unsigned int itcounter ;
void LT8900_Reset(void);
void LT8900Reg_Init(void);
void LT8900rf_test(void);
void It8920_filldata(void);
void LT8900_txdata(void);
void It8920_Sleep(void);
void It8920_Idle(void);
 void It8920_ResetFifo(void);
 void SPI_WriteFifo(void);
 void It892_EnterTx(void);

//--------------

extern volatile unsigned int ittranscounter ;
extern volatile unsigned char rfmsgarry[];
//-----------------------
static void touchkeyHandle(void);
//----------------------
#define DELAYUSER(a)  	_emi = 0;itcounter = 0;_emi = 1;do{\
			 	_clrwdt();_clrwdt2();_clrwdt1(); \	
			 	}while(itcounter<a)
					
/*
**key pa2 is press LED3 lit up and release the key
*/
static void Dqa_testIt8920(void)
{
	//if((_pa0==0)&&(_pa2==0))
	if(_pa2==0)
	{
		do{
			_clrwdt();_clrwdt2();_clrwdt1(); _nop();
		}while(itcounter==0);

		//if((_pa0==0)&&(_pa2==0))
		while(_pa2==0)
		{
			_clrwdt();_clrwdt2();_clrwdt1(); _nop();
		}
		
		{
			 LT8900rf_test();
			 
			 /*sw version*/	
			 for(usertmpvalue = 0;usertmpvalue <SW_FACTORYVER;usertmpvalue++)
			 {
			
			 	LED3TURNON;
                DELAYUSER(30);
			 	LED3TURNOFF;
			    DELAYUSER(30);
			 }
             DELAYUSER(400);
             
        do{_clrwdt();_clrwdt2();_clrwdt1(); _nop();}while(1); 

		}
	}
}
/*
**key is press LED5 lit up and release the key
*/
#ifdef FACTORY_TEST
static void factorytestIt8920(void)
{
	//if((_pa0==0)&&(_pa2==0))
	if(_pa0==0)
	{
		do{
			_clrwdt();_clrwdt2();_clrwdt1(); _nop();
		}while(itcounter==0);

		//if((_pa0==0)&&(_pa2==0))
		while(_pa0==0)
		{
			_clrwdt();_clrwdt2();_clrwdt1(); _nop();
		}
		
		//_emi = 0;
		//itcounter = 0;
		//_emi = 1;
		
		//do{
			//_clrwdt();_clrwdt2();_clrwdt1(); _nop();
		//}while(itcounter==0);
		
		//if(_pa0==1)
		{

			 LT8900rf_test();
			 
			 /*sw version*/	
			 for(usertmpvalue = 0;usertmpvalue <SW_FACTORYVER;usertmpvalue++)
			 {
			
			 	LED3TURNON;
                DELAYUSER(30);
			 	LED3TURNOFF;
			    DELAYUSER(30);
			 }
             DELAYUSER(400);
			


		}
	}
}
#endif
/*
----------------------------------
            *timer0*
----------------------------------
*/
DEFINE_ISR(INTERRUPTTIMER0,0x20)
{
	if(KtimerstartF)
	{
		keypresstimer++;
	}
	if(KLedtimerstartF)
	{
		keyledtimer++;
	}
	if(KpairtimerstartF)
	{
		keypairtimer++;
	}
	if(KrfittimerstartF)
	{
		krlsrftxtimer++;
		//if((krlsrftxtimer%25)==0)
		if((krlsrftxtimer%10)==0)
		{
			KrepeatdataF = 1;
		}
	}
	
	if(KonlyrlstxF)
	{
	keyonlyrlstxtimer++;
		if((keyonlyrlstxtimer%2)==0)
		{
			keypressdownF = 1;
		}
	
	}

	/*if(KhuanqiPressStartF)
	{
	 keyonlyhuanqitimer ++ ;	
	}*/
	if(KmachPtimerF)
	{
	 keymachtimer++;	
	}
	
	if(ledidicatestartF)
	{
	 keyledidicatetimer++;	
	}
		itcounter++;

	_ctmaf = 0;
}
/*
**ctmc0 using as timing
*/
static void InitCtmc0Timer(void)
{
	
	//_ctck0 = 1;
	//_ctck1 = 1;
	//_ctck2 = 0; //ftck=Fsys/64
	_ctmc0 = 0b00110110;
	
	//_ctm0 = 1;
	//_ctm1 = 1; //timer mo shi
	
	//_ctcclr = 1;//ctm compare A match
	_ctmc1 = 0b11000001;
	//_ctmdl counter low 8 bits
	//_ctmdh counter high 2 bits 
	//_ctmal compare counter low 8 bits
	_ctmal = 0xff;
	_ctmah = 0x03; //8ms
	_mf1e = 1;
	_mf1f = 0;
	//_ctmah compare counter high 2 bits
	//_ctmae enable interrut
	_ctmae = 1;
	_ctmaf = 0;
	//_ctmaf overflow flag --MFI1 regsitor
	_emi = 1;// enable interrupt
   _cton = 1;//turn on timer
}

void TurnoffTimer0(void)
{
	_cton = 0;
}

void TurnonTimer0(void)
{
	_cton = 1;
}

/*
---------------------------
         **LED**
---------------------------
*/
static void InitLed(void)
{

	//pa3 led1
	//pa4 led6
	//pa7 led5
	//pd5 all led
	
	//pd4 led4
	//pd1 led3
	//pd0 led2
	
	//pb7 led7 
	// _pac3 = 0;        // 
	// _pa3 = 1;	//turn off
	// _pac4 = 0;        // 
	// _pa4= 1;	//turn off	
	// _pac7 = 0;        // 
	// _pa7= 1;	//turn off	
	
		// _pdc4 = 0;        // 
	// _pd4= 1;	//turn off	
	
			// _pdc1 = 0;        // 
	// _pd1 = 1;	//turn off	
	
			// _pdc0 = 0;        // 
	// _pd0 = 1;	//turn off	
	
				// _pbc7 = 0;        // 
	// _pb7 = 1;	//turn off	
	
		_pdc5 = 1;        // in put--led2
        _pdpu5 = 1; //enable pull up
		
				_pac3 = 1;        // in put
        _papu3 = 1; //enable pull up
		
						_pac4 = 1;        // in put
        _papu4= 1; //enable pull up
		
						_pac7 = 1;        // in put
        _papu7= 1; //enable pull up		
		
		//_pdc0 = 1;        // in put
       // _pdpu0= 1; //enable pull up		
		
		_pdc1 = 1;        // in put
        _pdpu1= 1; //enable pull up	
		
		_pac2 = 1;        // in put---led4
        _papu2= 1; //enable pull up		
		
		_pac0 = 1;        // in put---led5
        _papu0= 1; //enable pull up		
		
		_pbc7 = 1;        // in put
        _pbpu7= 1; //enable pull up	
		
}
static void userInitLed(void)
{
/*LED1TURNINIT;
LED2TURNINIT;
LED3TURNINIT;
LED4TURNINIT;
LED5TURNINIT;
LED6TURNINIT;
LED7TURNINIT;*/	
}
static void TurnonallLed(void)
{

 LED1TURNON ;


 LED2TURNON ;


 LED3TURNON ;


 LED4TURNON;


 LED5TURNON ;


 LED6TURNON ;


LED7TURNON ;

}
static void TurnoffallLed(void)
{
 LED1TURNOFF ;


 LED2TURNOFF ;


 LED3TURNOFF ;


 LED4TURNOFF;


 LED5TURNOFF ;


 LED6TURNOFF ;


LED7TURNOFF ;	
}
void clrflagledtimer(void)
{
	
	                      ledidicatestartF = 0;
						  keyledidicatetimer = 0;	
}
void USER_PROGRAM_INITIAL()
{   
	//没有用的引脚进行处理
  _papu= 0b01100000;
  _pac = 0b01100000; 
  _pa = 0b01111111; 
  
  _pbpu7= 0;
  _pbc7 = 0; 
  _pb7 = 0x1;  
 
  _pcpu = 0;
  _pcc = 0; 
  _pc = 0;
  
  _pdpu = 0;
  _pdc = 0; 
  _pd = 0b00100010;
  	
userflag3.byte = 0;
_acerl = 0x00;//AD IO 设置为IO
//userInitLed();
InitCtmc0Timer();
LT8900_Reset();
InitLed();
LT8900Reg_Init();
Dqa_testIt8920();
//factorytestIt8920();
itcounter = 0;
It8920_Idle();
//It8920_Sleep();
TurnonallLed();
while(1){
	              _clrwdt();
                _clrwdt2();
                _clrwdt1();
               _nop();
               if(itcounter>20) break;
}
//TurnoffallLed();
InitLed();
/*intial to check is key is press*/
KLedtimerstartF = 1;
keyledtimer = 0;
}

//==============================================
//**********************************************
//==============================================
void USER_PROGRAM()
{   
usertmpvalue = STANDBY_TIME;
if(usertmpvalue <= 1)
{
	if(!KsleephaveF)
	{
		 /*LT8900_Reset();
		 LT8900Reg_Init();*/
		//It8920_Idle();
	 It8920_Sleep();
	 KsleephaveF = 1;
	 /*sleep dont to check the timer*/
	 		KLedtimerstartF = 0;
		keyledtimer = 0;	
		
     clrflagledtimer();
	}
	KwakupF = 0;
    


}
else if(usertmpvalue == 0x7e)
{
	KsleephaveF = 0;
	_emi = 0;
	STANDBY_TIME = 0x12;//0x12;//1e-18
	_emi = 1;
	 
	if(!KwakupF)
	{
        /*LT8900_Reset();
		//InitLed();
		LT8900Reg_Init();*/	

		
		/*every wake up to clr pair flag so as to release the zhaoming function
		 and at the same time user want to pair the remoter,need quickly press the zhaoming key
		*/
		  KpairtimerstartF = 0; //clr the pair timer the press the key is not the same
		  KpairtimerstartF = 0; //clr the pair timer
		 keypairtimer = 0;
		 K7paircounter = 0;
		 K7zhaomingrelaseF = 0;
		 KpairEnterF = 0;
		 		 /*intitial variable*/
		 userflag4.byte = 0;
		 userflag1.byte = 0;
		 userflag2.byte = 0;
		 userflag3.byte = 0;
		 userflag5.byte = 0;
		 keyvalue = 0;
		 
		KwakupF = 1;

		KinitRfstartF = 0;
		/*to timer count the wakup no keypress time*/
		KLedtimerstartF = 1;
		keyledtimer = 0;
		/**/
		keyonlyrlstxtimer = 0;
		
      clrflagledtimer();
					 
	}
}

	if( SCAN_CYCLEF )
	{
		if( ANY_KEY_PRESSF )
		{	
			/*to have the key start dont to check the STANDBY_TIME*/
			Khavepressflag = 1;
			KLedtimerstartF = 0;
			keyledtimer = 0;
			
			/*the key press fisrt time to set up the rf*/
			if(!KinitRfstartF)
			{
				KinitRfstartF = 1;
			        LT8900_Reset();
		        LT8900Reg_Init();	
			}
				  GET_KEY_BITMAP();	
				 keyvalue = DATA_BUF[0] ;

						 /*key change*/
				 if(keyvalue != pkeyvalue)
				 {
					 
					pkeyvalue =  keyvalue;
					if(KpairEnterF || (keyvalue!=0x40))//fei zao ming or have three times zhao ming then click the zhao ming key
					{
					/*clr pair flag*/
					  KpairtimerstartF = 0; //clr the pair timer the press the key is not the same
					  KpairtimerstartF = 0; //clr the pair timer
					 keypairtimer = 0;
					 K7paircounter = 0;
					 K7zhaomingrelaseF = 0;
					 KpairEnterF = 0;
					 /**/
					}
					 /*reset the keypress timer*/
					  _emi = 0;
					 keypresstimer = 0;
					  _emi = 1;
					 // _emi = 0;
					 // keytimer = 0;
					 // _emi = 1;
					 /*when mulit key zhaoming press this counter cannot ++
					 when huan qi key is press this counter can not and wait the relase to counter*/
					/* if( keyvalue!= 0x08) //k4 huan qi 
					 {
						 if(!KmultizhaomingrlsF)
						 ittranscounter++;
						 
						 KhuanqirlsPressF = 0;
					 }
					 else
					 {
					 	if(KhuanqirlsPressF && (keyonlyrlstxtimer > 0) && (keyonlyrlstxtimer < 80) )
					 	{
					 		_emi = 0;
					 		KhuanqirlsPressF = 0;
					 		keyonlyhuanqitimer = keyonlyrlstxtimer;
					 	  KhuanqiPressStartF = 1;
					 	  _emi = 1;	
					 	}
					 }*/
					 	if(!KmultizhaomingrlsF)
						 ittranscounter++;
					 /*key change to clr the multi or long key press send flag*/
					 KmultizhaomingF = 0;
					 KmultiwifiRestF = 0; 
					 keymachlongfunflag = 0;//clr the press short zhao ming + huanqi
					 
					  					 /*clr the led flag*/
					 InitLed();
					 userflag5.byte = 0;
					 
                     /*repeat counter check the key*/
					 keysamerepeatflag = 1;
					 keysamecounter = 0;	
					 /**/
					 	/*to check many key release */
                    	 keytempvalue = keyvalue;
						 keycount = 0;
						 for(tempcount = 0; tempcount < 7; tempcount++)
						 {
								if(keytempvalue & 0x01)
								 {
									 keycount++;
								 }
								 keytempvalue = keytempvalue >> 1;
						 }
						 if(keycount < 2 )
						 {
						 /*smoothing the key dithering*/
					     /*keysamecounter=0;

					     keysamerepeatflag = 0;	//don't to check*/
					      
						     if(keymachpresszmflag)	
						     {
                              
						     	   
						     	   /*KmachPtimerF = 1;
						     	   _emi = 0;
						     	   keymachtimer = 0;
						     	   _emi = 1;*/
						     	   keysamerepeatflag = 0;//don't to key check
						     	   keysamecounter = 0;
						     	  //--multile key chang to one key ,need clr the led if the led is litup 
						     	   InitLed();
						     }	

						 }
					 

					 
				 }
				 else
				 {
				 	/*many key change to function key need go to dithering*/
				     if(keymachpresszmflag)
				     {
				     	if(KmultizhaomingF || KmultiwifiRestF || keymachlongfunflag)//one key
				     	{
				     	keysamecounter = 0;
				        keysamerepeatflag = 1;// to check key
				     	}
				     	else
				     	{
                         /*multile key inorge the key handle*/
				        keysamecounter = 0;
				        keysamerepeatflag = 0;
				        /*to show x led 200ms when multile key press*/	
							if(keypresstimer>650)//led x show 200ms turn off led
							{
					           InitLed();
							
							}
							 else if(keypresstimer>625)//5s
							{
								LED1TURNON;LED2TURNON;LED3TURNOFF;LED4TURNON;
							LED5TURNON;LED6TURNOFF; LED7TURNON;
										 keypressdownF = 0;//do noning
								 KmultizhaomingF = 0;  
								 KmultizhaomingrlsF = 0;  
							}				        	
				     	}
			     		//dithering time to 24ms
				     	  if(KmachPtimerF && (keymachtimer >= 100))	
				     	  {
				     	  	KmachPtimerF = 0;
				     	  _emi = 0;
				     	   keymachtimer = 0;
				     	   _emi = 1;
				     	    keymachpresszmflag = 0;	
				     	    KmultizhaomingrlsF = 0;//need clr avoid the transcount cannot inc
				     	  }

				     }
                   else
                   {
				 	/*smoothing the key dithering*/
				     /*keysamecounter++;
				     if(keysamecounter > 3)	
				     {
				     	keysamerepeatflag = 1;
				     }
				     else
				     {
				       keysamerepeatflag = 0;	
				     }*/
				     keysamerepeatflag = 1;
                   }

				 }
				 
			/* have any key press clr only rls tx code */        
			 {
			 	KonlyrlstxF = 0;
			   	_emi = 0;
			 	keyonlyrlstxtimer = 0;
                _emi = 1;
                KhuanqirlsF = 0;
                KyijianguanjirlsF = 0;
                KmuyurlsF = 0;
                KjinhuarlsF = 0;
                KzhaomingrlsF = 0;
                KganzaorlsF = 0;
                KqiruanrlsF = 0;

			 }
			 
				 /*key timer*/
				if(!KtimerstartF)
				{
				keypresstimer = 0;
				 KtimerstartF = 1;
				}
				/**/
				//-KinitRfstartF = 0;
				/**/
				//--touchkeyHandle();
				/*key counter*/
				if(keysamerepeatflag) 
				{
				  keysamerepeatflag = 0;
				  touchkeyHandle();	
				}
				/*need rf send code key clear the counter  to interval the send code*/
				if(keypressdownF)
				{
				  keysamecounter = 0;	
				}
				
		}
		else
		{
			/*key release*/
			/*mach key zao ming*/
			if(keymachpresszmflag)
			{
               if(!KmachPtimerF)
               {
	     	  	KmachPtimerF = 1;
	     	  _emi = 0;
	     	   keymachtimer = 0;
	     	   _emi = 1;
               }
			}
			if(KmachPtimerF && (keymachtimer >= 100))
			{
				KmachPtimerF = 0;
			  keymachtimer = 0;	
			  keymachpresszmflag = 0;
			   KmultizhaomingrlsF = 0;//need clr avoid the transcount cannot inc
			  
			}
			keymachpressflag = 0;
		//	keymachpresszmflag = 0;
/*clr the flag*/
 ledzhaomingF= 0;
 ledqiruanF=0;
 ledliangfengF =0;
 ledyijiguanjiF  =0;
 ledganzaoF  =0;
 ledmuyuF =0;
 ledhuangqiF =0;
			
			keyvalue = 0;
			pkeyvalue = 0;
			KtimerstartF = 0;
			
			if(ledidicatestartF && (keyledidicatetimer >= CLRLED_LONGPRESS_TIMER))
			{

			
				InitLed();
              clrflagledtimer();
			  
			}
           if(!ledidicatestartF)
		   {

			InitLed();
		   }
				//TurnoffallLed();
			/*clr the key flag*/
			keypressdownF = 0;
			/*
             *key pair 
			*/
			K7zhaomingrelaseF = 0;
             if(K7zhaomingpressF)
			 {
				 K7zhaomingpressF = 0;
				 K7paircounter++;
			 }
			 if(keypairtimer>=300)
			 {
					/*clr pair flag*/
					  KpairtimerstartF = 0; //clr the pair timer the press the key is not the same
					  KpairtimerstartF = 0; //clr the pair timer
					 keypairtimer = 0;
					 K7paircounter = 0;
					 K7zhaomingrelaseF = 0;	
					 KpairEnterF = 0;			 
			 }
			 if((K7paircounter > 2) && (keypairtimer >0) && (keypairtimer < 300))
			 {
			 	 if(!KpairEnterF)
			 	 {
                  ittranscounter++;
                  _emi = 0;
                  keypairtimer = 0xe0;
                  if(STANDBY_TIME < 0x12)
                  {
                  	STANDBY_TIME = 0x12;
                  }
                  _emi = 1;
			 	 }
				 KpairEnterF = 1;
				 KzhaomingrlsF = 0;//need clr the KzhaomingrlsF
				 /**/
				 //-KinitRfstartF = 0;
				 if(keypairtimer%2)
				 {
				 keypressdownF = 1;
				 }
				 			rfmsgarry[0] = 0x03;//pei dui
			     rfmsgarry[1] = 0x4d;		
				 keypresstimer = 0;
			 }			 
            /*
            key press to send code if the send time is not enough,
            now change to rls send code and only the multible key is press to send code
            and the long have the code to send
			*/
		//	if(!KonlyrlstxF && !KhuanqirlsF && !KyijianguanjirlsF && !KmuyurlsF && !KjinhuarlsF \
		//	    && !KzhaomingrlsF && !KganzaorlsF && !KqiruanrlsF)
			if(KmultizhaomingF)    
			{
				KmultizhaomingF = 0;
				KmultizhaomingrlsF = 0;
				KmultiwifiRestF = 0;
				keymachlongfunflag = 0;
				KlonghuanqiF = 0;
				 if(!keypressdownF && (keypresstimer >0) && (keypresstimer <62))//500ms
				 {
					 krlsrftxtimer = keypresstimer; 
					 keypresstimer = 0;
					 KrfittimerstartF = 1;
					 KrepeatdataF = 1;
				 }
			}
             if(KrfittimerstartF && (krlsrftxtimer < 80))//125-80 640ms
			 {
				 if(KrepeatdataF)
				 {
					 
					 KrepeatdataF = 0;
				 	    It8920_Idle();
					It8920_ResetFifo();
					It8920_filldata();
					SPI_WriteFifo();
					It892_EnterTx();
					LT8900_txdata();

				 }
			 }
			 if(krlsrftxtimer>=80)//125-80
			 {
				 KrfittimerstartF = 0;
				 krlsrftxtimer = 0;
				 KrepeatdataF =0;
			 }
			 /*multi key press have relaese but the zhaomingF is zero*/
			 if(!KmultizhaomingF && KmultizhaomingrlsF)
			 {
			 			 	keypressdownF = 1;
			 	KonlyrlstxF = 1;
			 	KmultizhaomingrlsF = 0;
			 	  _emi = 0;
			 	  keyonlyrlstxtimer = 0;
                  if(STANDBY_TIME < 0x12)
                  {
                  	STANDBY_TIME = 0x12;
                  }
                  _emi = 1;
                  // rfmsgarry[0] = 0x03;//
		          //rfmsgarry[1] = 0x37;
			 }
			 /* huan qi rls send code*/
			 if(KhuanqirlsF || KzhaomingrlsF || KmuyurlsF || KjinhuarlsF \
			 
			     || KyijianguanjirlsF || KganzaorlsF || KqiruanrlsF)
			 {
			 	KmultizhaomingrlsF = 0;
			 	//KhuanqirlsF = 0;
			 	KzhaomingrlsF = 0;
			 	KmuyurlsF = 0;
			 	KjinhuarlsF = 0;
			 	KyijianguanjirlsF = 0;
			 	KganzaorlsF = 0;
			 	KqiruanrlsF = 0;
			 	
			 	keypressdownF = 1;
			 	KonlyrlstxF = 1;
			 	  _emi = 0;
			 	  
			 	  keyonlyrlstxtimer = keypresstimer;
			 	  
			 	  /*huang qi key need from the zero to counter*/
			 	 /* if(KhuanqirlsF)
			 	  {
			 	  keyonlyrlstxtimer = 0;
			 	  ittranscounter++;//huan qi key is release to send code 
			 	  KhuanqirlsPressF = 1;// to check the huanqi key if press again
			 	  KhuanqiPressStartF = 0;
			 	  keyonlyhuanqitimer = 0;
			 	  }*/
			 	  KhuanqirlsF = 0;
			 	  
                  if(STANDBY_TIME < 0x12)
                  {
                  	STANDBY_TIME = 0x12;
                  }
                  _emi = 1;
                  //-rfmsgarry[0] = 0x03;//
		          //-rfmsgarry[1] = 0x39;
			 	
			 }
             /*liang feng or cui feng or jing hua send code*/
			/* if(KjinhuarlsF)
			 {
			 	KjinhuarlsF = 0;
                keypressdownF = 1;
                KonlyrlstxF = 1;
			 	  _emi = 0;
			 	  keyonlyrlstxtimer = 0;
                  if(STANDBY_TIME < 0x12)
                  {
                  	STANDBY_TIME = 0x12;
                  }
                  _emi = 1;
                 //- rfmsgarry[0] = 0x03;//cui feng 0x033B
		          //-rfmsgarry[1] = 0x3B;
			 } */ 
			 
			 if(KonlyrlstxF && (keyonlyrlstxtimer < 80))
			 {
			     //keypressdownF = 1;
			 } 
			 if(keyonlyrlstxtimer >= 80)
			 {
			   KonlyrlstxF = 0;
			   	_emi = 0;
			 	keyonlyrlstxtimer = 0;
			 	/*huang qi*/
			 	KhuanqirlsPressF = 0;
			 	  KhuanqiPressStartF = 0;
			 	  keyonlyhuanqitimer = 0;
                _emi = 1;
                keypressdownF = 0;
                if(STANDBY_TIME > 3)
                {
                  _emi = 0;
                  STANDBY_TIME = 2;
                  _emi = 1;	
                }  
                 
			 }  
			 

		}
	}
	/*no key press wake up to quickly to sleep*/
    if(!Khavepressflag && (keyledtimer > 10))
    {
    		/*if(KLedtimerstartF)
	{
		keyledtimer++;
	}*/
	     LT8900_Reset();
		 LT8900Reg_Init();
		 It8920_Idle();
	                  _emi = 0;
                  STANDBY_TIME = 2;
                  keyledtimer = 0;
                  _emi = 1;	

    }

	if(keypressdownF)
	{

		keypressdownF = 0;
	   It8920_Idle();
		It8920_ResetFifo();
		It8920_filldata();
		SPI_WriteFifo();
		It892_EnterTx();
		LT8900_txdata();

	}
   /*set the io port*/

	

}

static void touchkeyHandle(void)
{
	switch(keyvalue)
	{
		case 0x01:
		             
		            if(keypresstimer<80)//2s 130-85
					{
						if(!ledyijiguanjiF)
						{
							ledyijiguanjiF = 1;
					LED1TURNON;LED2TURNOFF;LED3TURNOFF;LED4TURNOFF;
					 LED5TURNOFF;LED6TURNOFF; LED7TURNOFF;

	                      ledidicatestartF = 1;
						  keyledidicatetimer = 0;
						}
						KyijianguanjirlsF = 1;
					keypressdownF = 1;// key press and relase both to send code
						
                   if(keypresstimer>=CLRLED_LONGPRESS_TIMER)//200ms 25 clr led-->改成500ms --63  CLRLED_LONGPRESS_TIMER 63
                   {
                   	InitLed();
					clrflagledtimer();
                   }
                   
				rfmsgarry[0] = 0x03;//yi jian guan ji
		       rfmsgarry[1] = 0x50;
					}
					else if(keypresstimer>650)//led x show 200ms turn off led
					{
                       InitLed();
					
					}					
					else if(keypresstimer>625)//5s
					{
					KyijianguanjirlsF = 0;
					keypressdownF = 0;
					
											LED1TURNON;LED2TURNON;LED3TURNOFF;LED4TURNON;
					 LED5TURNON;LED6TURNOFF; LED7TURNON;
					}
					
					else
					{
						KyijianguanjirlsF = 0;
					LED1TURNOFF;LED2TURNOFF;LED3TURNOFF;LED4TURNOFF;
					 LED5TURNOFF;LED6TURNOFF; LED7TURNOFF;
						 keypressdownF = 0;//do noning
						 ledyijiguanjiF = 0;   
                       clrflagledtimer();						 
					}
		break;
		case 0x02:
		   
		         if(keypresstimer<80)//2s
				 {
                      if(!ledmuyuF)
                      {
                      	ledmuyuF = 1;
				 						LED1TURNOFF;LED2TURNON;LED3TURNOFF;LED4TURNOFF;
					 LED5TURNOFF;LED6TURNOFF;LED7TURNOFF;
					 	                      ledidicatestartF = 1;
						  keyledidicatetimer = 0; 
                      }
				 	 KmuyurlsF = 1;
					 keypressdownF = 1;
					 
                   if(keypresstimer>=CLRLED_LONGPRESS_TIMER)//200ms clr led
                   {
                   	InitLed();
                   }
					rfmsgarry[0] = 0x03;//mu yu
		            rfmsgarry[1] = 0x5A;
				 }
				 else if(keypresstimer>650)//led x show 200ms turn off led
				{
                   InitLed();
				  clrflagledtimer();
				}
				 else if(keypresstimer>625)//5s
					{
						keypressdownF = 0;//do noning 
						KmuyurlsF = 0;
											LED1TURNON;LED2TURNON;LED3TURNOFF;LED4TURNON;
					 LED5TURNON;LED6TURNOFF; LED7TURNON;
					}
					else
					{
					LED1TURNOFF;LED2TURNOFF;LED3TURNOFF;LED4TURNOFF;
					 LED5TURNOFF;LED6TURNOFF; LED7TURNOFF;
					     KmuyurlsF = 0;
						 keypressdownF = 0;//do noning 
						 ledmuyuF = 0;    
                        clrflagledtimer();						 
					}
		break;
		case 0x04:
		 if(keypresstimer<80)//2s
		 {
                if(!ledganzaoF)
                {
                	ledganzaoF = 1;
		 		LED1TURNOFF;LED2TURNOFF;LED3TURNON;LED4TURNOFF;
				LED5TURNOFF;LED6TURNOFF;LED7TURNOFF;	
									 	                      ledidicatestartF = 1;
						  keyledidicatetimer = 0;  
                }
		 	       KganzaorlsF = 1;
			       keypressdownF = 1;
			       
                   if(keypresstimer>= CLRLED_LONGPRESS_TIMER)//200ms clr led
                   {
                   	InitLed();
					clrflagledtimer();
                   }
					rfmsgarry[0] = 0x03;//gan zao
					rfmsgarry[1] = 0x90;
		 }
		else if(keypresstimer>650)//led x show 200ms turn off led
		{
           InitLed();
		
		}
		 else if(keypresstimer>625)//5s
		{
					 	       KganzaorlsF = 0;
			       keypressdownF = 0;
			
											LED1TURNON;LED2TURNON;LED3TURNOFF;LED4TURNON;
					 LED5TURNON;LED6TURNOFF; LED7TURNON;
		}
		else
		{
					LED1TURNOFF;LED2TURNOFF;LED3TURNOFF;LED4TURNOFF;
					 LED5TURNOFF;LED6TURNOFF; LED7TURNOFF;
					     KganzaorlsF = 0;
						 keypressdownF = 0;//do noning   
						 ledganzaoF = 0;    
                    clrflagledtimer();						 
		}
					
		break;
		case 0x08:
					 if(keypresstimer<80)//2s
					{
                     if(!ledhuangqiF)
                     {
                     	ledhuangqiF = 1;
					 LED1TURNOFF;LED2TURNOFF;LED3TURNOFF;LED4TURNON;
					 LED5TURNOFF;LED6TURNOFF;LED7TURNOFF;		
									 	                      ledidicatestartF = 1;
						  keyledidicatetimer = 0;  			 
                     }	
                     
                     //huanqi gai hui an xia fa ma;  huanqi mei you chang an cha xun wifi gong neng
		             KhuanqirlsF = 1;// = 1;
		             keypressdownF = 1;					 	

					 /*if(KhuanqiPressStartF && keyonlyhuanqitimer < 80)	
					 {
					 	keypressdownF = 1;//to send huangqi code
					 }  
					 else
					 {
					 	KhuanqiPressStartF = 0;
					 	keyonlyhuanqitimer = 0;
		             keypressdownF = 0;
					 }*/
					 
                   if(keypresstimer>=CLRLED_LONGPRESS_TIMER	)//200ms clr led
                   {
                   	InitLed();
					clrflagledtimer();
                   }
					 rfmsgarry[0] = 0x03;//
		             rfmsgarry[1] = 0x39;
					}
					/*else if(keypresstimer>1000)//8s
					{
						keypressdownF = 0;
											LED1TURNON;LED2TURNON;LED3TURNOFF;LED4TURNON;
					 LED5TURNON;LED6TURNOFF; LED7TURNON;
					}*/
					else if(keypresstimer>650)//led x show 200ms turn off led
					{
						//-keypressdownF = 0;
						//-KlonghuanqiF = 0;
						InitLed();
											//LED1TURNOFF;LED2TURNOFF;LED3TURNOFF;LED4TURNOFF;
					 //LED5TURNOFF;LED6TURNOFF; LED7TURNOFF;
					}
	
					else if(keypresstimer>625)//5s F-E6114 no wifi function
					{
						//-KhuanqirlsF = 0;
						//-keypressdownF = 1;
					//-rfmsgarry[0] = 0x03;//gan zao
					//-rfmsgarry[1] = 0xa7;//cha xun wifi
					 //-LED1TURNOFF;LED2TURNON;LED3TURNOFF;LED4TURNOFF;
					 //-LED5TURNON;LED6TURNOFF;LED7TURNON;
										 	       KhuanqirlsF = 0;
			       keypressdownF = 0;
			
					  LED1TURNON;LED2TURNON;LED3TURNOFF;LED4TURNON;
					   LED5TURNON;LED6TURNOFF; LED7TURNON;
					}
					else
					{
									LED1TURNOFF;LED2TURNOFF;LED3TURNOFF;LED4TURNOFF;
					 LED5TURNOFF;LED6TURNOFF; LED7TURNOFF;
					 KhuanqirlsF = 0;
						 keypressdownF = 0;//do noning 
						 ledhuangqiF = 0; 	
						 
						 //-KhuanqiPressStartF = 0;
						 //-keyonlyhuanqitimer = 0;
						 clrflagledtimer();	
					}

		break;
		case 0x10://k5
		 if(keypresstimer<80)//2s
		 {
                if(!ledqiruanF)
                {
                	ledqiruanF = 1;
		 		LED1TURNOFF;LED2TURNOFF;LED3TURNOFF;
				LED4TURNOFF;LED5TURNON;LED6TURNOFF;LED7TURNOFF;	
													 	                      ledidicatestartF = 1;
						  keyledidicatetimer = 0;  		
                }
		 	       KqiruanrlsF = 1;
		           keypressdownF = 1;
		           
                   if(keypresstimer>=CLRLED_LONGPRESS_TIMER	)//200ms clr led
                   {
                   	InitLed();
					clrflagledtimer();
                   }
					 rfmsgarry[0] = 0x03;//quruan 0x033F
		            rfmsgarry[1] = 0x3F;
		 }
		else if(keypresstimer>650)//led x show 200ms turn off led
		{
           InitLed();
		
		}		 
		 else if(keypresstimer>625)//5s
		{
			KqiruanrlsF = 0;
			 keypressdownF = 0;//do noning
			LED1TURNON;LED2TURNON;LED3TURNOFF;LED4TURNON;
		LED5TURNON;LED6TURNOFF; LED7TURNON;
		}
		else
		{
		LED1TURNOFF;LED2TURNOFF;LED3TURNOFF;LED4TURNOFF;
		 LED5TURNOFF;LED6TURNOFF; LED7TURNOFF;
		    KqiruanrlsF = 0;
			 keypressdownF = 0;//do noning 
			 ledqiruanF = 0;       
			 clrflagledtimer();
		}
		break;
		case 0x20://k6--jin hau is to cui feng 
		if(keypresstimer<80)//2s
		{
                if(!ledliangfengF)
                {
                	ledliangfengF = 1;
				LED1TURNOFF;LED2TURNOFF;LED3TURNOFF;LED4TURNOFF;
					 LED5TURNOFF;LED6TURNON;LED7TURNOFF;	
					 													 	                      ledidicatestartF = 1;
						  keyledidicatetimer = 0;  		
                }
			      KjinhuarlsF = 1;
		          keypressdownF = 1;

                   if(keypresstimer>=CLRLED_LONGPRESS_TIMER)//200ms clr led
                   {
                   	InitLed();
					clrflagledtimer();
                   }
					 rfmsgarry[0] = 0x03;//cui feng 0x033B
		              rfmsgarry[1] = 0x3B;
		}
		else if(keypresstimer>650)//led x show 200ms turn off led
		{
           InitLed();
		
		}
		else if(keypresstimer>625)//5s
		{
			LED1TURNON;LED2TURNON;LED3TURNOFF;LED4TURNON;
			LED5TURNON;LED6TURNOFF; LED7TURNON;
		}			
		else
		{
		LED1TURNOFF;LED2TURNOFF;LED3TURNOFF;LED4TURNOFF;
		 LED5TURNOFF;LED6TURNOFF; LED7TURNOFF;
		 KjinhuarlsF = 0;
			 keypressdownF = 0;//do noning
			 ledliangfengF = 0;  
            clrflagledtimer();			 
		}
		
		break;
		case 0x40://k7
		if(keypresstimer<80)//2s
		{
                   if(!ledzhaomingF)
                   {
                   	ledzhaomingF = 1;
								LED1TURNOFF;LED2TURNOFF;LED3TURNOFF;LED4TURNOFF;
					 LED5TURNOFF;LED6TURNOFF;LED7TURNON;	
					 
					 					 													 	                      ledidicatestartF = 1;
						  keyledidicatetimer = 0;  	
                   }
                   if(keypresstimer>=CLRLED_LONGPRESS_TIMER)//200ms clr led
                   {
                   	InitLed();
					clrflagledtimer();
                   }
			       KzhaomingrlsF = 1;
			       keypressdownF = 1;

					if(!KpairtimerstartF)
					 {
					  KpairtimerstartF = 1;
					  K7paircounter = 0;
					 _emi = 0;
					 keypairtimer = 0;
					 _emi = 1;
					 }
					 if(!K7zhaomingrelaseF)
					 {
						K7zhaomingrelaseF = 1;
					 K7zhaomingpressF = 1;	
                     }		
                     
					rfmsgarry[0] = 0x03;//zhao ming 0x0337
					rfmsgarry[1] = 0x37;				
        }
        else if(keypresstimer>650)//led x show 200ms turn off led
		{
           InitLed();
		
		}
		else if(keypresstimer>625)//5s
		{
			LED1TURNON;LED2TURNON;LED3TURNOFF;LED4TURNON;
		LED5TURNON;LED6TURNOFF; LED7TURNON;
		}
		else
		{
		LED1TURNOFF;LED2TURNOFF;LED3TURNOFF;LED4TURNOFF;
		 LED5TURNOFF;LED6TURNOFF; LED7TURNOFF;
		   KzhaomingrlsF = 0;
			 keypressdownF = 0;//do noning 
			 ledzhaomingF = 0;  
         clrflagledtimer();			 
		}		
		break;
		#ifdef WIFI_RESET
		case 0x48://huan qi + zhao ming  wifi fu wei
		  /*if(keypresstimer>1000)
		  {
		  							keypressdownF = 0;
											LED1TURNON;LED2TURNON;LED3TURNOFF;LED4TURNON;
					 LED5TURNON;LED6TURNOFF; LED7TURNON;
		  }*/
		  clrflagledtimer();
		  if(keypresstimer>2000)//2s bu hui cheng X status
		  {
		  							keypressdownF = 0;
											LED1TURNOFF;LED2TURNOFF;LED3TURNOFF;LED4TURNOFF;
					 LED5TURNOFF;LED6TURNOFF; LED7TURNOFF;
					 KmultiwifiRestF = 0;
		  }		  
		  else if(keypresstimer>625)//5s
		  {
			   keypressdownF = 1;
			  	LED1TURNON;LED2TURNOFF;LED3TURNOFF;LED4TURNON;
				LED5TURNOFF;LED6TURNOFF;LED7TURNON;
		  		rfmsgarry[0] = 0x03;
				rfmsgarry[1] = 0xa3;
				KmultiwifiRestF = 1;
				/*muti key press*/
				 keymachpresszmflag = 1;
			    KmachPtimerF = 1;
		 	   _emi = 0;
		 	   keymachtimer = 0;
		 	   _emi = 1;
			
		  }
		  else
		  {
		  				/*muti key press*/
		  				keymachlongfunflag = 1;
				 keymachpresszmflag = 1;
			    KmachPtimerF = 1;
		 	   _emi = 0;
		 	   keymachtimer = 0;
		 	   _emi = 1;	
		  	
		  }
		  
		break;
		#endif
		
		default:
		  if(keypresstimer<80)//640--zao ming 
		  {
					 keytempvalue = keyvalue;
					 keycount = 0;
					 for(tempcount = 0; tempcount < 7; tempcount++)
					 {
							if(keytempvalue & 0x01)
							 {
								 keycount++;
							 }
							 keytempvalue = keytempvalue >> 1;
					 }
					 if(keycount >=3 ) //k7 zhao ming
					 {
						 LED1TURNOFF;
						 LED2TURNOFF;
						 LED3TURNOFF;
						 LED4TURNOFF;
						 LED5TURNOFF;
						 LED6TURNOFF;
						 LED7TURNON;
                     keypressdownF = 1;
					rfmsgarry[0] = 0x03;//zhao ming 0x0337
					rfmsgarry[1] = 0x37;
					KmultizhaomingF = 1;//补尝 照明时间
					KmultizhaomingrlsF = 1;//补尝 照明时间
						
						ledidicatestartF = 1;
						  keyledidicatetimer = 0;  					 
					 }
					 else
					 {
					 	//--if one key is press and led is lit up ,then sencond key is press need clr the led
                         InitLed();
						 userflag5.byte = 0;//clr the led flag	
					 }  
                     
                     if(keypresstimer >= CLRLED_LONGPRESS_TIMER)
                     {
                     	InitLed();
						clrflagledtimer();
                     }
		  
                    
		  }
		else if(keypresstimer>650)//led x show 200ms turn off led
		{
           InitLed();
		
		}
		 else if(keypresstimer>625)//5s
		{
			LED1TURNON;LED2TURNON;LED3TURNOFF;LED4TURNON;
		LED5TURNON;LED6TURNOFF; LED7TURNON;
		}
		else
		{
		LED1TURNOFF;LED2TURNOFF;LED3TURNOFF;LED4TURNOFF;
		 LED5TURNOFF;LED6TURNOFF; LED7TURNOFF;
			 keypressdownF = 0;//do noning
			 KmultizhaomingF = 0;  
			 KmultizhaomingrlsF = 0;  
         clrflagledtimer();			 
		}

        keymachpresszmflag = 1;
	    KmachPtimerF = 1;
 	   _emi = 0;
 	   keymachtimer = 0;
 	   _emi = 1;
 	   
		break;
	}

		 		
}

