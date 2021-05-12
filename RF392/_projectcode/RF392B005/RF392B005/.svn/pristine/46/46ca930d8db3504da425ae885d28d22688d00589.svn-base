//#include "gpio.h"
//#include "lpm.h"
//#include "bt.h"
//#include "basetimer.h"
//#include "bt.h"
//#include "flash.h"
//#include "touch01_tongtai.h"
//#include "capsense_power_modes.h"
#include "cslib_hwconfig.h"
#include "cslib_config.h"
#include "cslib.h"
#include "InitDevice.h"
#include "lt8920.h"
#include "USER_PROGRAM.h"
#include "board_efm8sb.h"
#include "hgsemi74hc.h"
#include "absacc.h"
#include<stdlib.h>

#define SW_FACTORYVER 1
#define TouchKeyAmount 7

#define CLRLED_LONGPRESS_TIMER 100//50 500ms  37 300ms 58--16
#define KEYPRESS_RFTX_TIMR 100 //500ms  58--16

extern bit clib_keypressflag;
#define ANY_KEY_PRESSF clib_keypressflag


/*#define LED1TURNON {user_led1_litup();}
#define LED1TURNOFF {user_led1_litoff();}


#define LED2TURNON {user_led2_litup();}
#define LED2TURNOFF {user_led2_litoff();}



#define LED3TURNON {user_led3_litup();}//pa2
#define LED3TURNOFF {user_led3_litoff();}


#define LED4TURNON {user_led4_litup();}
#define LED4TURNOFF {user_led4_litoff();}



#define LED5TURNON  {user_led5_litup();}
#define LED5TURNOFF {user_led5_litoff();}


#define LED6TURNON {user_led6_litup();}
#define LED6TURNOFF {user_led6_litoff();}

#define LED7TURNON {user_led7_litup();}
#define LED7TURNOFF {user_led7_litoff();}*/

unsigned char xdata keyrawvalue = 0;
 unsigned char xdata keyvalue = 0;
 unsigned char xdata pkeyvalue = 0;
 unsigned char xdata keytempvalue = 0;
 unsigned char xdata lastpkeyvalue = 0;
 unsigned char xdata keycount = 0;
 unsigned int xdata keyledtimer = 0;//8ms
 unsigned int xdata keypairtimer = 0;//
 unsigned int xdata keypresstimer = 0;
 //unsigned int xdata keypaizangrlstimer = 0;
 unsigned char xdata multikeyreset_timer=0;
//unsigned char tempcount = 0;
 unsigned char xdata K7paircounter = 0;
 unsigned char xdata keyonlyrlstxtimer = 0;
 unsigned char xdata prerlstxtimer = 0;
 unsigned char xdata keyonlyhuanqitimer = 0;
 unsigned char xdata nowledvalue = 0x00;
//unsigned char preusertmpvalue = 0;
 unsigned char xdata usertmpvalue = 0;
 unsigned char xdata krlsrftxtimer = 0;
 unsigned char xdata STANDBY_TIME = 0x7E;
unsigned char xdata romd_datatimer = 0;
unsigned char xdata keylvvalue = 0;

 _TKS_FLAGA_type xdata userflag1 = {0};
#define KtimerstartF		userflag1.bits.b0
#define KLedtimerstartF		userflag1.bits.b1
#define KrfittimerstartF		userflag1.bits.b2
#define KpairtimerstartF		userflag1.bits.b3
#define KhuanqirlsF          userflag1.bits.b4
#define usernouse0          userflag1.bits.b5
#define KonlyrlstxF          userflag1.bits.b6
#define KmachPtimerF          userflag1.bits.b7

 _TKS_FLAGA_type  xdata userflag2 = {0};
#define KrepeatdataF		userflag2.bits.b0
#define KsleephaveF		userflag2.bits.b1
#define KwakupF		userflag2.bits.b2
#define KzhaomingrlsF		userflag2.bits.b3
#define KmuyurlsF		userflag2.bits.b4
#define KjinhuarlsF		userflag2.bits.b5
#define KganzaorlsF		userflag2.bits.b6
#define keypressdownF   userflag2.bits.b7


 _TKS_FLAGA_type  xdata userflag3 = {0};
#define KpairEnterF		userflag3.bits.b0
#define KqiruanrlsF		userflag3.bits.b1
#define KyijianguanjirlsF		userflag3.bits.b2
#define KmultizhaomingF		userflag3.bits.b3
#define KmultiwifiRestF		userflag3.bits.b4
#define KlonghuanqiF		userflag3.bits.b5
#define KmultizhaomingrlsF		userflag3.bits.b6
#define KinitRfstartF		        userflag3.bits.b7

 _TKS_FLAGA_type  xdata userflag4 = {0};
#define K7zhaomingpressF userflag4.bits.b0
#define K7zhaomingrelaseF userflag4.bits.b1
#define Khavepressflag userflag4.bits.b2
#define keymachpressflag  userflag4.bits.b3 
#define keymachpresszmflag  userflag4.bits.b4 
#define KhuanqirlsPressF    userflag4.bits.b5
#define KhuanqiPressStartF    userflag4.bits.b6
#define keymachlongfunflag  userflag4.bits.b7

 _TKS_FLAGA_type  xdata userflag5 = {0};

#define ledzhaomingF userflag5.bits.b0
#define ledqiruanF userflag5.bits.b1
#define ledliangfengF userflag5.bits.b2
#define ledyijiguanjiF  userflag5.bits.b3 
#define ledganzaoF  userflag5.bits.b4 
#define ledmuyuF  userflag5.bits.b5
#define ledhuangqiF  userflag5.bits.b6
#define ledidicatestartF userflag5.bits.b7

 _TKS_FLAGA_type xdata userflag6 = {0};
#define keyrestscanF userflag6.bits.b0
#define lastprekeyF userflag6.bits.b1
#define keypaizangrlsF userflag6.bits.b2
#define keypaizconF    userflag6.bits.b3


unsigned char xdata tempcount = 0;

//----------------------
// unsigned char xdata keysamecounter = 0;
 unsigned char xdata keysamerepeatflag = 1;
 unsigned int xdata keymachtimer = 0;

 unsigned int xdata keyledidicatetimer= 0;

 unsigned int xdata app_sleep_counter = 0;
//----------------------
 //extern unsigned  int xdata itcounter;
//extern volatile unsigned char txtimercounter ;
//extern volatile unsigned int itcounter ;
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

extern  unsigned int xdata ittranscounter ;
extern unsigned char xdata rfmsgarry[];
//-----------------------

static void touchkeyHandle(void);
//----------------------
#define DELAYUSER(a)  	delay1ms(a)
#define InitLed() LEDALL_OFF()
#define TurnoffallLed() LEDALL_OFF()
#define TurnonallLed()  LEDALL_ON();

/*
**key pa2 is press LED3 lit up and release the key
*/
static void Dqa_testIt8920(void)
{
unsigned int loopcount = 0;
	//if((_pa0==0)&&(_pa2==0))
	if(P2_B7==0)
	{
	   //
	    delay1ms(20);

		//if((_pa0==0)&&(_pa2==0))
	    while(P2_B7==0)
	      {
	        delay1ms(20);
	        loopcount++;
	        if(loopcount >= 300)
	          {
	            return;
	          }
	      };
		
		{
			 LT8900rf_test();
			 
			 /*sw version*/	
			 for(usertmpvalue = 0;usertmpvalue <SW_FACTORYVER;usertmpvalue++)
			 {
			
			 	//LED5TURNON();
			   LEDALL_ON();
			 	delay1ms(100);
			 	LEDALL_OFF();
			 	delay1ms(100);
			 }

			 //loopcount = 0;
        do{
            //delay1ms(200);
            //loopcount++;
        }while(1);
        //}while(loopcount<100);

		}
	}

}

void user_rset_scancapcity(void)
{
  CSLIB_0_enter_DefaultMode_from_RESET();
  //CSLIB_initLibrary();
  keyrestscanF = 1;
  multikeyreset_timer = 0;
}

void user_rsetlvt1s_fun(void)
{
  if(keyrestscanF )
    {
      if(multikeyreset_timer < 100)//60*8.5=  100*5
        {
      clib_keypressflag = 0;//don't to check key
      keymachpresszmflag = 0;
      KmachPtimerF = 0;
        }
      else
        {
          keyrestscanF = 0;
          multikeyreset_timer = 0;
        }


    }
}

/*
----------------------------------
            *timer0*
----------------------------------
*/
//DEFINE_ISR(INTERRUPTTIMER0,0x20)
void user_timer_process(void)
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
		if((krlsrftxtimer%15)==0)//16--10
		{
			KrepeatdataF = 1;
		}
	}
	
	if(KonlyrlstxF)
	{
	keyonlyrlstxtimer++;
		/*if((keyonlyrlstxtimer%2)==0)
		{
			keypressdownF = 1;
		}*/
	
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

  if(keyrestscanF)
    {
      multikeyreset_timer++;
    }
		//itcounter++;
}




/*
---------------------------
         **LED**
---------------------------
*/


/*static void TurnonallLed(void)
{

 //LED1TURNON ;


 //LED2TURNON ;


 //LED3TURNON ;


 //LED4TURNON;


 //LED5TURNON ;


 //LED6TURNON ;


 //LED7TURNON ;

  user_ledall_turnon();
}*/
/*static void TurnoffallLed(void)
{
 //LED1TURNOFF ;


 //LED2TURNOFF ;


 //LED3TURNOFF ;


 //LED4TURNOFF;


 //LED5TURNOFF ;


 //LED6TURNOFF ;


//LED7TURNOFF ;
  user_ledall_turnoff();
}*/
/*static void InitLed(void)
{
TurnoffallLed();
}*/
void clrflagledtimer(void)
{
	
	                      ledidicatestartF = 0;
						  keyledidicatetimer = 0;	
}

unsigned char UpdateSensorStatus(void)
{
  //static uint8_t lastActiveSensors = 0xFF;
  uint8_t activeSensors = 0;
  uint8_t i;

  // Get the sensor status and convert to
  // a bitmask
  for (i = 0; i < DEF_NUM_SENSORS; i++)
  {
    if (CSLIB_isSensorDebounceActive(i))
    {
      activeSensors |= (1 << i);
    }
  }

  // status has changed
  //if (activeSensors != lastActiveSensors)
  //{
    //lastActiveSensors = activeSensors;
  //}
  return(activeSensors);
}
/*void  uservar_init(void)
{
  userflag4.byte = 0;
  userflag1.byte = 0;
  userflag2.byte = 0;
  userflag3.byte = 0;
  userflag5.byte = 0;
}*/
void USER_PROGRAM_INITIAL(void)
{   

  	


  userflag3.byte = 0;
LT8900_Reset();

LT8900Reg_Init();
Dqa_testIt8920();
//factorytestIt8920();
//itcounter = 0;
It8920_Idle();

//SPI_ReadReg(38);
//SPI_ReadReg(39);
//It8920_Sleep();
delay1ms(80);//200ms
TurnonallLed();
delay1ms(200);//200ms
TurnoffallLed();

/*intial to check is key is press*/
//KLedtimerstartF = 1;
keyledtimer = 0;
keylvvalue = 5;
}
//INDICADE_PIN = !INDICADE_PIN;
void wakeup_init(void)
{
  if(!KwakupF)
    {
  keypairtimer = 0;
  K7paircounter = 0;
  //K7zhaomingrelaseF = 0;
  //KpairEnterF = 0;
      /*intitial variable*/
  userflag4.byte = 0;
  userflag1.byte = 0;
  userflag2.byte = 0;
  userflag3.byte = 0;
  userflag5.byte = 0;
  userflag6.byte = 0;
  keyvalue = 0;
  keylvvalue = 0;
  Khavepressflag = 0;
 KwakupF = 1;

 //KinitRfstartF = 0;
 /*to timer count the wakup no keypress time*/
 KLedtimerstartF = 1;
 keyledtimer = 0;
 /**/
 keyonlyrlstxtimer = 0;

 //keypaizangrlsF = 0;//clr pai zangrls
 //keypaizangrlstimer = 0;

   clrflagledtimer();
    }
}

void user_sleep_fun(void)
{
  if(app_sleep_counter>=130)//600ms
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
        keylvvalue = 0;
        clrflagledtimer();
        //INDICADE_PIN = 1;//2.8s
      }
      InitLed();
      KwakupF = 0;
     // LT8920_SPISS_PIN = 1;
    }
}

//#define user_touch_counter DBYTE 0x45
//==============================================
//**********************************************
//==============================================
void USER_PROGRAM(void)
{

    wakeup_init();
    user_sleep_fun();
    //user_rsetlvt1s_fun();
		if( ANY_KEY_PRESSF )
		{	
			/*to have the key start dont to check the STANDBY_TIME*/

			KLedtimerstartF = 0;
			keyledtimer = 0;
			KsleephaveF = 0;
		  prerlstxtimer = 0;
			keyvalue = UpdateSensorStatus();
			keycount = getpresskeycount();
			if((keycount<3) && (keyvalue !=0x08))
			  {
          /*the key press fisrt time to set up the rf*/
          if(!KinitRfstartF & Khavepressflag)
          {
            KinitRfstartF = 1;
                  LT8900_Reset();
                LT8900Reg_Init();
                //keycount = getpresskeycount();


               // return;
          }
          if(!Khavepressflag)
            {
          Khavepressflag = 1;
          return;
            }
			  }
			//Khavepressflag = 1;
						 /*key change*/
				 if(keyvalue != pkeyvalue)
				 {
				     lastpkeyvalue = pkeyvalue;
            pkeyvalue =  keyvalue;
            if(KpairEnterF || (keyvalue!=0x08))//fei zao ming or have three times zhao ming then click the zhao ming key
            {
            /*clr pair flag*/
              //KpairtimerstartF = 0; //clr the pair timer the press the key is not the same
              KpairtimerstartF = 0; //clr the pair timer
             keypairtimer = 0;
             K7paircounter = 0;
             K7zhaomingrelaseF = 0;
             KpairEnterF = 0;
             /**/
            }
             /*reset the keypress timer*/
              //_emi = 0;
             keypresstimer = 0;
					  //_emi = 1;
					 // _emi = 0;
					 // keytimer = 0;
					 // _emi = 1;
					 /*when mulit key zhaoming press this counter cannot ++
					 when huan qi key is press this counter can not and wait the relase to counter*/
             /*if(lastpkeyvalue && ((lastpkeyvalue^pkeyvalue)!=0)&&(lastpkeyvalue == (lastpkeyvalue & pkeyvalue) ))
               {
                 lastprekeyF =1;
               }*/
             // if(!KmultizhaomingrlsF && !lastprekeyF)
             if(!KmultizhaomingrlsF)
                {

               ittranscounter++;
               /*if(keypaizangrlsF && keypaizangrlstimer < 30)
                 {
                   ittranscounter--;
                 }*/
               InitLed();
               userflag5.byte = 0;
                }
              //if(!KmultizhaomingrlsF)
               //ittranscounter++;
             /*key change to clr the multi or long key press send flag*/
             KmultizhaomingF = 0;
             //KmultiwifiRestF = 0;
             //keymachlongfunflag = 0;//clr the press short zhao ming + huanqi

                         /*clr the led flag*/
             //if(!lastprekeyF)
            // InitLed();
             //userflag5.byte = 0;

                       /*repeat counter check the key*/
             keysamerepeatflag = 1;
            // keysamecounter = 0;
					 /**/
					 	/*to check many key release */
                    	 /*keytempvalue = keyvalue;
						 keycount = 0;
						 for(tempcount = 0; tempcount < 7; tempcount++)
						 {
								if(keytempvalue & 0x01)
								 {
									 keycount++;
								 }
								 keytempvalue = keytempvalue >> 1;
						 }*/

               keycount = getpresskeycount();
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
                        // keysamecounter = 0;
                        //--multile key chang to one key ,need clr the led if the led is litup
                         //InitLed();
                         //if(!lastprekeyF)
                         //-InitLed();
                         //lastprekeyF = 0;
                     }

                 }

					 

					 
				 }
				 else
				 {
				 	/*many key change to function key need go to dithering*/
				     if(keymachpresszmflag)
				     {
                  //if(KmultizhaomingF || KmultiwifiRestF || keymachlongfunflag)//one key
                  if(KmultizhaomingF || keypaizconF)//one key
                  {
                 //	keysamecounter = 0;
                    keysamerepeatflag = 1;// to check key
                  }
                  else
                  {
                                   /*multile key inorge the key handle*/
                         // keysamecounter = 0;
                          keysamerepeatflag = 0;
                          /*to show x led 200ms when multile key press*/
                        if(keypresstimer>1040)//led x show 200ms turn off led  605--16  140--8
                        {
                               InitLed();
                               CSLIB_0_enter_DefaultMode_from_RESET();

                        }
                         else if(keypresstimer>1000)//5s 580--16  1000--8
                        {
                          //LED1TURNON;LED2TURNON;LED3TURNOFF;LED4TURNON;
                        //LED5TURNON;LED6TURNOFF; LED7TURNON;
                             LEDALL_XON();
                               keypressdownF = 0;//do noning
                           KmultizhaomingF = 0;
                           KmultizhaomingrlsF = 0;
                        }
                  }
                //dithering time to 24ms
                  if(KmachPtimerF && (keymachtimer >= 100))//58--16  100-8
                  {
                    KmachPtimerF = 0;
                  //_emi = 0;
                   keymachtimer = 0;
                   //_emi = 1;
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
			   	//_emi = 0;
			 	keyonlyrlstxtimer = 0;
                //_emi = 1;
                //KhuanqirlsF = 0;
                KyijianguanjirlsF = 0;
                //KmuyurlsF = 0;
                //KjinhuarlsF = 0;
                //KzhaomingrlsF = 0;
                //KganzaorlsF = 0;
                //KqiruanrlsF = 0;

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
				  //touchkeyHandle();
				  touchkeyHandle();
				}
				/*need rf send code key clear the counter  to interval the send code*/
				/*if(keypressdownF)
				{
				  keysamecounter = 0;	
				}*/
				
		}
		else
		{
			/*key release*/
		   // Khavepressflag = 0;
        lastpkeyvalue = 0;
        lastprekeyF = 0;//clr the prss tx code flt flag
			/*mach key zao ming*/
			if(keymachpresszmflag)
			{
			    keyledtimer = 0;
               if(!KmachPtimerF)
               {
	     	  	KmachPtimerF = 1;
	     	  //_emi = 0;
	     	   keymachtimer = 0;
	     	   //_emi = 1;
               }
               //to kuai an not to counter
               if(KmultizhaomingrlsF && keypresstimer>30)//20--16  30--8
                 {
                   KmultizhaomingrlsF = 0;

                 }
			}
			//58-- 30
			if(KmachPtimerF && (keymachtimer >= 30))//58--30
			{
				KmachPtimerF = 0;
			  keymachtimer = 0;	
			  keymachpresszmflag = 0;
			   KmultizhaomingrlsF = 0;//need clr avoid the transcount cannot inc
			  
			}
			keymachpressflag = 0;
		//	keymachpresszmflag = 0;
/*clr the flag*/
// ledzhaomingF= 0;
 //ledqiruanF=0;
 //ledliangfengF =0;
 ledyijiguanjiF  =0;
 //ledganzaoF  =0;
 //ledmuyuF =0;
 //ledhuangqiF =0;
			
			keyvalue = 0;
			pkeyvalue = 0;
			KtimerstartF = 0;
			
			if(ledidicatestartF && (keyledidicatetimer >= 100))//CLRLED_LONGPRESS_TIMER 58--16   100--8
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
				 keypaizconF =0;//clr zhang pai rls

			 }
			 if(keypairtimer>=360)//300--16  360--8
			 {
					/*clr pair flag*/
					  KpairtimerstartF = 0; //clr the pair timer the press the key is not the same
					 // KpairtimerstartF = 0; //clr the pair timer
					 keypairtimer = 0;
					 K7paircounter = 0;
					 K7zhaomingrelaseF = 0;	
					 KpairEnterF = 0;
					 //INDICADE_PIN = 0;
			 }
			 if((K7paircounter > 2) && (keypairtimer >0) && (keypairtimer < 360))
			 {
			     //K7paircounter = 0;
			     //
			 	 if(!KpairEnterF)
			 	 {
                  ittranscounter++;
                 // _emi = 0;
                  keypairtimer = 0xe0;

                  //_emi = 1;
			 	 }
				 KpairEnterF = 1;
				 KzhaomingrlsF = 0;//need clr the KzhaomingrlsF
				 KyijianguanjirlsF  = 0;
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
		//	if(!KonlyrlstxF && !KhuanqirlsF && !KyijianguanjirlsF && !KmuyurlsF && !KjinhuarlsF
			//    && !KzhaomingrlsF && !KganzaorlsF && !KqiruanrlsF)
			if(KmultizhaomingF)    
			{
				KmultizhaomingF = 0;
				KmultizhaomingrlsF = 0;
				//KmultiwifiRestF = 0;
				//keymachlongfunflag = 0;
				KlonghuanqiF = 0;
				keyledtimer = 0;
				 if(!keypressdownF && (keypresstimer > 0) && (keypresstimer <70))//500ms 40--16  70--8
				 {
					 krlsrftxtimer = keypresstimer; 
					 keypresstimer = 0;
					 KrfittimerstartF = 1;
					 KrepeatdataF = 1;
				 }
			}
       if(KrfittimerstartF && (krlsrftxtimer < 70))//125-80 640ms
			 {
           //keypaizangrlsF = 1;
           //keypaizangrlstimer = 0;
           //keyledtimer = 0;//clr idle timer
           //when pan zhang contiue pai xia need to litup led
           keymachtimer = 0; //clr the timer to contiue 500ms lv
				 if(KrepeatdataF)
				 {
				     keyledtimer = 0;
				    /* if(krlsrftxtimer >=45)//30--16  45--8
				       {
				     //KwakupF = 0;
				     InitLed();
				       }*/
				     keypaizconF =1;
					 KrepeatdataF = 0;
					 user8920_txdata();
				 	 /*It8920_Idle();
					It8920_ResetFifo();
					It8920_filldata();
					SPI_WriteFifo();
					It892_EnterTx();
					LT8900_txdata();*/

				 }
			 }
			 if(krlsrftxtimer>=100)//125-80
			 {
				 KrfittimerstartF = 0;
				 krlsrftxtimer = 0;
				 KrepeatdataF =0;
				 keyledtimer = 0;
			 }
			 /*multi key press have relaese but the zhaomingF is zero*/
			 if(!KmultizhaomingF && KmultizhaomingrlsF)
			 {
			 			 	keypressdownF = 1;
			 	KonlyrlstxF = 1;
			 	KmultizhaomingrlsF = 0;
			 	  //_emi = 0;
			 	  keyonlyrlstxtimer = 0;
			 	 keyledtimer = 0;

                  //_emi = 1;
                  // rfmsgarry[0] = 0x03;//
		          //rfmsgarry[1] = 0x37;
			 }
			 /* huan qi rls send code*/
			 //if(KhuanqirlsF || KzhaomingrlsF || KmuyurlsF || KjinhuarlsF
			 
			   //  || KyijianguanjirlsF || KganzaorlsF || KqiruanrlsF)
			 if(KyijianguanjirlsF)
			 {
			 	KmultizhaomingrlsF = 0;
			 	//KhuanqirlsF = 0;
			 //	KzhaomingrlsF = 0;
			 	//KmuyurlsF = 0;
			 	//KjinhuarlsF = 0;
			 	KyijianguanjirlsF = 0;
			 	//KganzaorlsF = 0;
			 	//KqiruanrlsF = 0;
			 	
			 	keypressdownF = 1;
			 	KonlyrlstxF = 1;
			 	 // _emi = 0;

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
			 	 // KhuanqirlsF = 0;
			 	  
                  //_emi = 1;
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
			 
			 if(KonlyrlstxF && (keyonlyrlstxtimer < 85))//KEYPRESS_RFTX_TIMR 50--16 80--8
			 {

			    /*srand(CSLIB_node[0].rawBuffer[0]);
			     romd_datatimer = (rand()%10);
			     romd_datatimer +=8;
			     //delay1ms(romd_datatimer+30);
			     if(keyonlyrlstxtimer > prerlstxtimer)
			       {

			         if((keyonlyrlstxtimer - prerlstxtimer) >= romd_datatimer)//8--18
			          // if((keyonlyrlstxtimer - prerlstxtimer) >= 5)
			           {
			             prerlstxtimer = keyonlyrlstxtimer;
                    // if( romd_datatimer%2)
                       {
                         //INDICADE_PIN = !INDICADE_PIN;
                     keypressdownF = 1;
                     keyledtimer = 0;//clr idle timer
                     keypaizconF =0;//clr zhang pai rls
                       }
			           }
			       }*/
			     keypressdownF = 1;
			     keyledtimer = 0;//clr idle timer
			 } 
			 if(keyonlyrlstxtimer >= 85)//KEYPRESS_RFTX_TIMR
			 {
			    // KwakupF = 0;
			     InitLed();
			   KonlyrlstxF = 0;
			   //	_emi = 0;
			 	keyonlyrlstxtimer = 0;
			 	/*huang qi*/
			 	//KhuanqirlsPressF = 0;
			 	  //KhuanqiPressStartF = 0;
			 	  //keyonlyhuanqitimer = 0;
                //_emi = 1;
                keypressdownF = 0;

                //----
                KpairtimerstartF = 0; //clr the pair timer the press the key is not the same
               // KpairtimerstartF = 0; //clr the pair timer
               keypairtimer = 0;
               K7paircounter = 0;
               K7zhaomingrelaseF = 0;
               KpairEnterF = 0;
                 
			 }  
			 

		}

	/*no key press wake up to quickly to sleep*/
    //if(!ANY_KEY_PRESSF && (keyledtimer > 13))//3*30=90ms--100ms
		if(!KinitRfstartF && (keyledtimer > 400))//130--16  220--8
    {
		    KinitRfstartF = 1;
	    LT8900_Reset();
		 LT8900Reg_Init();
		 It8920_Idle();
		 It8920_Sleep();
		 //LT8920_SPISS_PIN = 1;
	                 // _emi = 0;
                  keyledtimer = 0;
                  //app_sleep_counter = 100;//to quickly sleep
                  //_emi = 1;	
                  //INDICADE_PIN = !INDICADE_PIN;
    }

	if(keypressdownF)
	{

		keypressdownF = 0;
		user8920_txdata();

	}
   /*set the io port*/

	

}
unsigned char getpresskeycount(void)
{
  unsigned char tmpkeycount = 0, i;
  unsigned char tmplpkeyvalue = keyvalue;
  //keytempvalue = keyvalue;
  for(i = 0; i < 7; i++)
  {
     if(tmplpkeyvalue & 0x01)
      {
         tmpkeycount++;
      }
     tmplpkeyvalue = tmplpkeyvalue >> 1;
  }
  return(tmpkeycount);
}

static void touchkeyHandle(void)
{
  switch(keyvalue)
  {
    case 0x01:
     // LED5TURNON();
      nowledvalue = LED5ON_VALUE;
      rfmsgarry[0] = 0x03;//bai feng
      rfmsgarry[1] = 0x41;

      break;
    case 0x02:
      //LED7TURNON();
      nowledvalue = LED7ON_VALUE;
      rfmsgarry[0] = 0x03;//huang qi
      rfmsgarry[1] = 0x39;
      break;
    case 0x04:
      //LED2TURNON();
      nowledvalue = LED2ON_VALUE;

      rfmsgarry[0] = 0x03;//mu yu
      rfmsgarry[1] = 0x5A;

      break;
    case 0x08:
      //LED4TURNON();
      nowledvalue = LED4ON_VALUE;
      rfmsgarry[0] = 0x03;//zhao ming 0x0337
      rfmsgarry[1] = 0x37;




      break;
    case 0x10:
      //LED1TURNON();
      nowledvalue = LED1ON_VALUE;
      rfmsgarry[0] = 0x03;//yi jian guan ji
      rfmsgarry[1] = 0x50;

      break;
    case 0x20:
      //LED3TURNON();
      nowledvalue = LED3ON_VALUE;
      rfmsgarry[0] = 0x03;//cui feng 0x033B
             rfmsgarry[1] = 0x3B;
      break;
    case 0x40:

      //LED6TURNON();
      nowledvalue = LED6ON_VALUE;
      rfmsgarry[0] = 0x03;//quruan 0x033F
      rfmsgarry[1] = 0x3F;
      break;
    case 0x42://ganzao
    nowledvalue = LED67ON_VALUE;
    rfmsgarry[0] = 0x03;//quruan 0x033F
    rfmsgarry[1] = 0x90;                          //qu ruan 0x40 + huanqi 0x02
    break;
    default:
      if(keypresstimer<KEYPRESS_RFTX_TIMR)//640--zao ming
      {
          keycount = getpresskeycount();
           if(keycount >=3 ) //k7 xiao ye deng
           {
            // LED1TURNOFF;
            // LED2TURNOFF;
            // LED3TURNOFF;
            // LED4TURNOFF;
            // LED5TURNOFF;
             //LED6TURNOFF;
               LED4TURNON();
             //nowledvalue = LED7ON_VALUE;
                     keypressdownF = 1;
          rfmsgarry[0] = 0x03;//zhao ming 0x0337
          rfmsgarry[1] = 0xa1;
          KmultizhaomingF = 1;//���� ����ʱ��
          KmultizhaomingrlsF = 1;//���� ����ʱ��
          keypaizconF = 0;   //paizhang rls to set 1
            ledidicatestartF = 1;
              keyledidicatetimer = 0;
             //CSLIB_0_enter_DefaultMode_from_RESET(); //easy to wu chu
              //user_rset_scancapcity();
           }
           else
           {
            //--if one key is press and led is lit up ,then sencond key is press need clr the led
               /*if(lastprekeyF)
               {
                   //the prss to flt press send code have a gan lao bo xing
                   if(keypresstimer > 4)//5*8
                     {
                   //CSLIB_0_enter_DefaultMode_from_RESET();
                       InitLed();
           userflag5.byte = 0;//clr the led flag
                     }

                 }
               else
                 {

                   //InitLed();
       userflag5.byte = 0;//clr the led flag
                 }*/
               //InitLed();
  // userflag5.byte = 0;//clr the led flag


           }



      }


        keymachpresszmflag = 1;
      KmachPtimerF = 1;
     //_emi = 0;
     keymachtimer = 0;
     //_emi = 1;
     keylvvalue = 5;
    break;
  }
if(keypresstimer<KEYPRESS_RFTX_TIMR)//2s 130-85
{

//if(KmultizhaomingF)
   if(keymachpresszmflag)
  {

  }
else
  {
    //if((keypresstimer>2) || (keyvalue==0x08) )
    if(keypresstimer>=keylvvalue)
      {
            if(!ledyijiguanjiF)
          {
                 ledyijiguanjiF = 1;
                //LED1TURNON;LED2TURNOFF;LED3TURNOFF;LED4TURNOFF;
                //LED5TURNOFF;LED6TURNOFF; LED7TURNOFF;
                 semi74hc_writedata(nowledvalue);
                           ledidicatestartF = 1;
                 keyledidicatetimer = 0;
                }
                KyijianguanjirlsF = 1;

                if(keyvalue == 0x08)
                 {

                    if(!KpairtimerstartF)
                     {
                      KpairtimerstartF = 1;
                      K7paircounter = 0;
                     //_emi = 0;
                     keypairtimer = 0;
                     //_emi = 1;
                     }
                     if(!K7zhaomingrelaseF)
                     {
                      K7zhaomingrelaseF = 1;
                     K7zhaomingpressF = 1;
                      }

                 }
                //if(keypresstimer>1)
                keypressdownF = 1;// key press and relase both to send code
            }
                //keypaizangrlsF = 0;//clr pai zangrls
                //keypaizangrlstimer = 0;
  }


      /*if(keypresstimer>=CLRLED_LONGPRESS_TIMER)//200ms 25 clr led-->�ĳ�500ms --63  CLRLED_LONGPRESS_TIMER 63
      {
       InitLed();
clrflagledtimer();
      }*/

}
else if(keypresstimer>1040)//led x show 200ms turn off led 605--16  1040--8
{
          InitLed();
          CSLIB_0_enter_DefaultMode_from_RESET();
}
else if(keypresstimer>1000)//5s  580--16    1000--8
{
KyijianguanjirlsF = 0;
keypressdownF = 0;

         //LED1TURNON;LED2TURNON;LED3TURNOFF;LED4TURNON;
// LED5TURNON;LED6TURNOFF; LED7TURNON;
LEDALL_XON();
}
else
{
KyijianguanjirlsF = 0;
//LED1TURNOFF;LED2TURNOFF;LED3TURNOFF;LED4TURNOFF;
//LED5TURNOFF;LED6TURNOFF; LED7TURNOFF;

keypressdownF = 0;//do noning
ledyijiguanjiF = 0;

//ru guo an jian hen ming gan,ze yi zhi hui jin lai ,dao zhi tiao
          //KmultizhaomingF = 0;
          //KmultizhaomingrlsF = 0;
          //InitLed();
          //clrflagledtimer(); //zan pai zao ming chang an hui shan

          if(!KmultizhaomingrlsF)
            {
              InitLed();
              clrflagledtimer();
            }

          /*if(KmultizhaomingrlsF && keypresstimer>40)
            {
              KmultizhaomingrlsF = 0;

            }*/
          /*else
            {

             // user_rset_scancapcity();
            }*/
}


}

