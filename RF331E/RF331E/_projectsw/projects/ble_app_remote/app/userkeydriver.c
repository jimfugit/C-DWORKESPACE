/*

** keyscan handler
**P33----P37  
**P20 P21
**P31 P32

*/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "app_key.h"
#include "gpio.h"
#include "rf.h"
#include "uart.h" 
//#include "bk2461.h"
//#include "driver_rf.h"
#include "userkeydriver.h"
//#include "driver_gpio.h"
#include "userbkdriver.h"
//#include "driver_i2cm.h"

#define TST_VERSION 4//

uint8_t  gGrouppreValue = 0; // to store the key group value
uint8_t  gbulbGroupValue = 0;//bulb group
uint8_t  gbulbTypeValue = 0; //bulb type
uint8_t  gbulbHandleValue = 0;//bulb handle
uint8_t  gbulbwifipd_value = 0;//bulb wifi fuwei 0x33 other value 0x03

uint8_t  keynum = 0;         //key
uint8_t  scankeyvalue = 0;
uint16_t  keytempvalue = 0;
uint16_t  keyvalue = 0;
uint16_t  keyprevalue = 0;
uint8_t  keyi = 0;         //key index
uint8_t  keychangecounter = 0;//key change counter
	
uint8_t  keyvalueL = 0;
uint8_t  keyvalueH = 0;


bool keypress_rlsf = 0;//	 as to 	sync key press or release
bool keylearnflag = 0; //learn key
bool keylearnkeyrlsf = 0;//learn key relase

bool validkeypressf = 0;//key press valid flag to send rf singal as to timer counter
bool longkeypress_stepf = 0;//to long key press rf send 
bool	longkeypress_step1f	= 0; //	to long key press rf send 50ms
bool longkeypress_step2f = 0; //	to long key press rf send 300ms	

uint16_t  cmplongkey_rfsendcounter = 0; //to long key press 50ms 300ms
uint16_t  rfsendstep1_counter = 0;// to long key counter
uint16_t  rfsend_counter = 0;//to start the key counter to rf send 1300ms


 bool  key_leng_sewenflag = 0;//leng se wen first press flag
 bool  key_liandu_decflag = 0;//liang du dec first press flag
 bool  key_liandu_incflag = 0;//liang du inc first press flag
 bool  key_nuan_sewenflag = 0;//ruan se wen first press flag
 bool key_linkagef = 0;//linkage for many key press handle flag
 uint16_t  key_linkagecounter = 0;//for many key press timer out handle

//pair
uint16_t  keyprepeiduvalue = 0;//using as the current key and previous key compare
uint16_t  kpeidutimer_counter = 0;//pair timer counter
bool  keypairf = 0;//pair flag
bool keypeiduistartf = 0; //start pair counter
uint8_t  keypeidui_counter = 0;//pair counter 

//
bool powerupflag = 0;//power up to test rf
bool factorytstrfsingalf = 0; //rf test mode flag
uint16_t  rfsingaltst_counter = 0;	 //rf test counter

bool kp_txinitf = 0;//kp to initial the tx mode
bool iic_haveclrf = 0;// to clr mac

bool  wifikeypressf = 0;//wifi press f
uint16_t  wifilinkage_cnt = 0;//wifi counter

//---------------------------
uint8_t keybuf[6] ={0}; //{0x8d, 0x8d, 0x8e, 0x83, 0x82, 0x82}; //key array
uint16_t  timelongkey_cnt = 0;
uint16_t  timesleep_cnt;
//--------------------------
extern uint8_t  keybuf[];//external variable
//----------extern uint16_t  time1ms_cnt; //external variable
extern uint16_t  timesleep_cnt;//external variable
extern uint16_t  timelongkey_cnt;//external variable
//---------------
extern uint8_t gpio_buff_c[KEYBOARD_MAX_COL_SIZE];
extern uint8_t gpio_buff_r[KEYBOARD_MAX_ROW_SIZE];

//--------------
 void clr_longkeysteprfsend(void);
 void clr_keypeidui(void);
void keyvaluehandle(void);
/**
 * @brief   key init
 * @note
 * @param   
 * @retval  
 */
void vuserkeyinit(void)
{
	//端口号,输入,使能上拉 ,使能下拉
	//port ,input,pull up,pull down
  //-GPIO_InputSetup(2, 0xff, 0xff, 0);
  //-GPIO_InputSetup(2, BIT(3), 0,0)//P23 input
  
 //断口号,oe,od
 //GPIO_OutputSetup(2, BIT(3), 0); //p23 output 
 //p3.3--P3.7 input 0x08 0x0f and enalbe the pull up resistor
/*GPIO_InputSetup(3, 0xf8, 0, 0);	//enable p33--p37 input
//P2.0 p2.1 p31 p32 output od
GPIO_OutputSetup(3, 0x06, 0x06);//eanble p31 p32 output
GPIO_OutputSetup(2, 0x03, 0x03);//enable p20 p21 output

//led init p12
GPIO_OutputSetup(1, 0x04, 0x00);
P12 = 0;*/
}

/**
 * @brief  clr liang du and se wen linkage
 * @note
 * @param   
 * @retval  
 */

 //exit linkage:
 //other key press or the timer counter is out

void clr_keylinkage(void)
{	
 key_leng_sewenflag = 0;
 key_liandu_decflag = 0;
 key_liandu_incflag = 0;
 key_nuan_sewenflag = 0;
 key_linkagef = 0;	  //many key press flag
 key_linkagecounter = 0;//many key press counter  in 800ms to handle key
}

/**
 * @brief   liang du and se wen linkage
 * @note
 * @param   
 * @retval  
 */

 //exit linkage:
 //other key press or the timer counter is out

void keyliangdusewenlinkage(bool leng_sw, bool nuan_sw, bool dec_liandu, bool inc_liandu)
{	
 key_leng_sewenflag = leng_sw;
 key_liandu_decflag = dec_liandu;
 key_liandu_incflag = inc_liandu;
 key_nuan_sewenflag = nuan_sw;
 key_linkagef = 1;	  //many key press flag
 key_linkagecounter = 0;//many key press counter  in 800ms to handle key
}


/**
 * @brief   key row status set
 * @note
 * @param   
 * @retval  
 */
void keyrowstatus(bool up20, bool up21, bool up31, bool up32)
{	
	/*P20 = up20;
	P21 = up21;
	P31 = up31;
	P32 = up32;	*/
}


void gbulb_assemblekeyvalue(void)
{
keybuf[0] = keychangecounter;
keybuf[1] = gbulbGroupValue;
keybuf[2] = gbulbwifipd_value;//0x03; //fixed
keybuf[3] = gbulbTypeValue;
keybuf[4] = 0x01;//fixed
keybuf[5] = gbulbHandleValue;

}

/**
 * @brief   key scan
 * @note
 * @param   
 * @retval  
 */
void vkeyscan(void)
{
   keynum = 0;
  do
  {
	/*switch(keynum)
	{
		case 0x00 :
		//keyrowstatus(0, 1, 1, 1);
		gpio_config(gpio_buff_r[0], OUTPUT, PULL_NONE); 
		gpio_set(gpio_buff_r[0], 0);
		break;
		case 0x01:
		//keyrowstatus(1, 0, 1, 1);
				gpio_config(gpio_buff_r[1], OUTPUT, PULL_NONE); 
		gpio_set(gpio_buff_r[1], 0);
		break;
		case 0x02://0x02
		//keyrowstatus(1, 1, 0, 1);
		break;
		case 0x03://0x03
		//keyrowstatus(1, 1, 1, 0);
		break;
		default:	
		break;	
	}*/
	gpio_config(gpio_buff_r[keynum], OUTPUT, PULL_NONE); 
	gpio_set(gpio_buff_r[keynum], 0);
	//delayus
	delay_us(10);
	scankeyvalue = (gpio_get_input(gpio_buff_c[0]) | (gpio_get_input(gpio_buff_c[1]) << 1) | (gpio_get_input(gpio_buff_c[2]) << 2)|
        (gpio_get_input(gpio_buff_c[3]) << 3) | (gpio_get_input(gpio_buff_c[4]) << 4))&0x1F;
	
	//scankeyvalue = scankeyvalue >> 3;
	//UART_PRINTF("scankeyvalue = 0x%x\n", scankeyvalue);
	//PRINT("scankeyvalue = %02bx\n", scankeyvalue);
	
    for(keyi = 0; keyi < KEYBOARD_MAX_COL_SIZE; keyi++)
    {
		keytempvalue = (1 << keyi) + ( (1 << keynum) << 8);
	/*	keyvalueL = timesleep_cnt;  //	keytempvalue
		keyvalueH = timesleep_cnt >> 8; //timesleep_cnt
		PRINT("timesleep_cntL = %02bx timesleep_cntH = %02bx \n", keyvalueL, keyvalueH);*/	
			
	   if(!(scankeyvalue & 0x01))//value 0 is col press
	   {
		   //PRINT("keyi = %02bx\n", keyi);
		keyvalue |= keytempvalue;
	
	   }

	   scankeyvalue = scankeyvalue >> 1 ;
	   
	 
    }
   gpio_set(gpio_buff_r[keynum],  1);
	gpio_config(gpio_buff_r[keynum], HIRESI, PULL_NONE); 		
	keynum++;
	//-PRINT("keynum = %02bx\n", keynum);
  }while(keynum < KEYBOARD_MAX_ROW_SIZE);
	


   if(keyvalue)	 //have the key press
   {
		 UART_PRINTF("keyvalue = 0x%x\n", keyvalue);
	   if(keyvalue != keyprevalue)
	   {
		   //key change
		 keyprevalue = keyvalue;  
		 keychangecounter++;//gun ma
	   	  	wifikeypressf = 0;//wifi 
	     timelongkey_cnt = 0; 
		 rfsend_counter = 0;//key change to clr the rfsend counter 
		 validkeypressf = 0;
		 clr_longkeysteprfsend();
			 //stop the adv
	   }
	   //peidui
	   if(keyvalue != keyprepeiduvalue)
	   {
	   	  keyprepeiduvalue =  keyvalue;
		  clr_keypeidui();
	   }
		keypress_rlsf = 1;
	   //-keyvalueL = keyvalue;
	   //-keyvalueH = keyvalue>>8;
	   
       //-PRINT("keyvaluel = %02bx keyvalueh = %02bx \n", keyvalueL, keyvalueH);

 				//keyvalueL = timesleep_cnt;  //	keytempvalue
		//keyvalueH = timesleep_cnt >> 8; //timesleep_cnt
		//PRINT("timesleep_cntL = %02bx timesleep_cntH = %02bx \n", keyvalueL, keyvalueH);	

     keyvaluehandle();
	 keyvalue = 0;	
   }
   else
   {
	    if(keypairf && timelongkey_cnt <= 1000)
		{
		   	 keypeiduistartf = 1;
			 keypeidui_counter++;
		}
		/*else
		{
		  keypeidui_counter = 0;
		}*/
		//wifi
		wifilinkage_cnt = 0;
		wifikeypressf = 0;
		//
	 keypairf = 0;
   	 keyprevalue = 0;//key release clr the pre key value
	 //P12 = 0;//led output 0
		//gpio_set(GPIOB_3, 0);
		BlueLedOff();
	 timelongkey_cnt = 0;//clr the long key timer counter
	 keypress_rlsf = 0;//key release
	 //learn key press
	 if(keylearnkeyrlsf)
	 {
	 	   keylearnflag = 1;
	   keylearnkeyrlsf = 0;	 
	 }
	 //
	 if(rfsend_counter >= 1300)//key release to stop the rf send
	 {
	   rfsend_counter = 0;
	   validkeypressf = 0;//to stop the rf send singial
	 }
	 //
	 clr_longkeysteprfsend();

   }

	//short press and continuous
	//clr rfsend_counter in the key change




	if(validkeypressf) //key relase do not to clr ,as to continue to send rf singal
	{
	  //validkeypressf = 0;
	  //PRINT("validf\n");	
		  gbulb_assemblekeyvalue();
		  //-------------user_setup_rfpackage();
		  //PRINT("123\n");
		  //---------------rf_packagesend();		
	 }
     /*if(kp_txinitf && !validkeypressf && (timesleep_cnt > 3000))
	 {
	 //-switchtoidlemode();
	 kp_txinitf = 0;
	 PowerDown_Rf();
	 }*/

	
}

//
 /**
 * @brief   fisrst valid key initial the rf
 * @note
 * @param   
 * @retval  
 */
 void keypress_initrf(void)
 {
	 if(!kp_txinitf)
	 {
	   kp_txinitf = 1;
	   //user_rfInit(0);
	    //-----------RF_Init();
		//-------------SwitchToTxMode();
		//--------------user_readmac_eeprom();
	  }
 }

 /**
 * @brief   clr pei dui
 * @note
 * @param   
 * @retval  
 */
void clr_keypeidui(void)
{
  	  kpeidutimer_counter = 0;
	  keypeidui_counter = 0;
	  keypeiduistartf = 0;
	  //-keyprepeiduvalue = 0;
}


  /**
 * @brief   keyvalue assignment	 for pei dui
 * @note
 * @param   
 * @retval  
 */
void gbulb_keypeidui_process(void)
{

	 keypairf = 1;
	 
	 if(keypeidui_counter == 2)
	 {
	 		 //peidui ma
			 gbulbTypeValue = 0x01;
			 gbulbwifipd_value = 0x33;
			  kpeidutimer_counter = 0;
 			  keypeiduistartf = 0;
	 }
	 else if(keypeidui_counter > 2)
	 {

			clr_keypeidui();
			 keypairf =  0;
	 }

}
 /**
 * @brief   keyvalue assignment
 * @note
 * @param   
 * @retval  
 */
 
void gbulb_assignment_value(uint8_t groupValue, uint8_t typevalue, uint8_t handlevalue)
{
	//grouble
	gbulbGroupValue = groupValue;
	gbulbTypeValue = typevalue;
	gbulbHandleValue = handlevalue;
	gbulbwifipd_value = 0x03;
	//check if to init tx mode
	keypress_initrf();
	//press flag
	if(!longkeypress_stepf)
	{
	validkeypressf = 1;	 //to start counter the timer
	}

		// to sync the key press or release
	//lit up the led
	//P12 = 1;
	//gpio_set(GPIOB_3, 1);
	BlueLedOn();
	timesleep_cnt = 0;//clr the counter to sleep
//+++++++++++
	//+++++++++++++send counter	+++key no change+++++
	if(!longkeypress_step1f && (rfsend_counter > 1300))
	//if(rfsend_counter > 1300 )//1300--1330to stop the rf send 
	{
	 rfsend_counter = 0; //end the counter
	  validkeypressf = 0;
	  longkeypress_step1f=1;
	  longkeypress_stepf = 1;
	  cmplongkey_rfsendcounter = 82;
	}
	if(longkeypress_stepf)//30 50 300
	{
		if(rfsendstep1_counter >= cmplongkey_rfsendcounter)
		{
		         rfsendstep1_counter = 0;
		 		 validkeypressf = 0;
				if( longkeypress_step1f	)
				{
				  longkeypress_step1f = 0;
			      cmplongkey_rfsendcounter = 300;
				  longkeypress_step2f = 1;
				}
				else if(longkeypress_step2f)
				{
				
				   longkeypress_step2f = 0;
				   cmplongkey_rfsendcounter = 82;
				   longkeypress_step1f = 1;
				}
			    

		}
		else if(rfsendstep1_counter >= 20)
		{
		  
		  //to send again
		  if(!validkeypressf)
		  {
		  	//inc gun ma
			keychangecounter++;//gun ma
			validkeypressf = 1 ;
		  }

		}
	}
	//++++++++++++++++++++++++++++++linkage key +++++++
	if(typevalue != 0x15 && typevalue != 0x1D)// not the linkage key
	{
		clr_keylinkage();
	}
		
}



/**
 * @brief   keyvalue handle
 * @note
 * @param   
 * @retval  
 */

void keyvaluehandle(void)
{
	uint8_t ui;

	timesleep_cnt = 0;
	 
	switch(keyvalue)
	{
	//case KEYSW17_QUANKAI:
		case KEYSW6_QUANKAI:
	gbulb_assignment_value(0xff,0x11,0x00);
	//-PRINT("gbulbsw17\n");

	break;	
	//case KEYSW13_QUANGUAN:
		case KEYSW7_QUANGUAN:
    gbulb_assignment_value(0xff,0x11,0x01);
	//-PRINT("gbulbsw13\n");
	
	break;	
	//case KEYSW9_YEDENG_MODE:
		case KEYSW15_YEDENG_MODE:
    gbulb_assignment_value(gGrouppreValue,0x0d,0x03);
	//-PRINT("gbulbsw9\n");
	break;

	//case KEYSW5_YULE_MODE:
		case KEYSW03_YULE_MODE:
    gbulb_assignment_value(gGrouppreValue,0x0d,0x01);
	//-PRINT("gbulbsw5\n");
	break;
	//case KEYSW1_LENGSEWEN:
		case KEYSW11_LENGSEWEN:
    gbulb_assignment_value(gGrouppreValue,0x1d,0x01);
	//-PRINT("gbulbsw1\n");
	//The key linkage
	   keyliangdusewenlinkage(1, 0, 0, 0);
	break;
	//case KEYSW18_YINGYUAN_MODE:
		case KEYSW14_YINGYUAN_MODE:
    gbulb_assignment_value(gGrouppreValue,0x0d,0x02);
	//-PRINT("gbulbsw18\n");
	break;
	//case KEYSW14_HUIKE_MODE:
		case KEYSW02_HUIKE_MODE:
    gbulb_assignment_value(gGrouppreValue,0x0d,0x00);
	//-PRINT("gbulbsw14\n");
		//The key linkage
	   //keysewenflag = 1;
	break;
	//case KEYSW10_LIANGDU_DEC:
		case KEYSW18_LIANGDU_DEC:
    gbulb_assignment_value(gGrouppreValue,0x15,0x01);
	//-PRINT("gbulbsw10\n");
		//The key linkage
	   keyliangdusewenlinkage(0, 0, 1, 0);
	break;
	//case KEYSW06_LIANGDU_INC:
		case KEYSW17_LIANGDU_INC:
    gbulb_assignment_value(gGrouppreValue,0x15,0x00);
	//-PRINT("gbulbsw06\n");
	  //The key linkage
	 keyliangdusewenlinkage(0, 0, 0, 1);
	break;
	//case KEYSW02_SEWEN_NUAN:
		case KEYSW10_SEWEN_NUAN:
    gbulb_assignment_value(gGrouppreValue,0x1d,0x00);
	//-PRINT("gbulbsw02\n");
		//The key linkage
	  keyliangdusewenlinkage(0, 1, 0, 0);
	break;
	case KEYSW19_LEARN:
	//-thesleepflag = 1;
     //-PRINT("gbulbsw19\n");
	 
	 if(timelongkey_cnt >= 5000)
	 {
	   //to clr the learn remoter
	   	keylearnkeyrlsf = 0;
	    keylearnflag = 0;
		if(!iic_haveclrf)
		{
		//----------IIC_ClrMacaddr();
		iic_haveclrf = 1;
		}

	 }
	 else if(timelongkey_cnt <= 3000)
	 {
	   // to learn remoter
	   keylearnflag = 0;
	   keylearnkeyrlsf = 1;
	   iic_haveclrf = 0;
	 }
	 else
	 {
	   keylearnflag = 0;
	   keylearnkeyrlsf = 0;
	 }
	break;
	//case KEYSW15_GUAN_GROUP0:
	case KEYSW8_GUAN_GROUP0:
	gGrouppreValue = 0;
    gbulb_assignment_value(gGrouppreValue,0x11,0x01);
	gbulb_keypeidui_process();
	//-PRINT("gbulbsw15\n");
	break;
	//case KEYSW11_GUAN_GROUP2:
	case KEYSW4_GUAN_GROUP2:
	gGrouppreValue = 2;
    gbulb_assignment_value(gGrouppreValue,0x11,0x01);
	gbulb_keypeidui_process();
	//-PRINT("gbulbsw11\n");
	break;
	//case KEYSW7_KAI_GROUP2:
	case KEYSW16_KAI_GROUP2:
	gGrouppreValue = 2;
    gbulb_assignment_value(gGrouppreValue,0x11,0x00);
	gbulb_keypeidui_process();
	//-PRINT("gbulbsw7\n");
	break;
	//case KEYSW3_KAI_GROUP0:
	case KEYSW12_KAI_GROUP0:
	gGrouppreValue = 0;
    gbulb_assignment_value(gGrouppreValue,0x11,0x00);
	gbulb_keypeidui_process();
	//-PRINT("gbulbsw3\n");
	break;
	//case KEYSW16_KAI_GROUP1:
	case KEYSW5_KAI_GROUP1:
	gGrouppreValue = 1;
    gbulb_assignment_value(gGrouppreValue,0x11,0x00);
	gbulb_keypeidui_process();
	//-PRINT("gbulbsw16\n");
	break;
	//case KEYSW12_KAI_GROUP3:
	case KEYSW1_KAI_GROUP3:
	gGrouppreValue = 3;
    gbulb_assignment_value(gGrouppreValue,0x11,0x00);
	gbulb_keypeidui_process();
	//-PRINT("gbulbsw12\n");
	break;
	//case KEYSW8_GUAN_GROUP3:
	case KEYSW13_GUAN_GROUP3:
	gGrouppreValue = 3;
    gbulb_assignment_value(gGrouppreValue,0x11,0x01);
	gbulb_keypeidui_process();
	//-PRINT("gbulbsw8\n");
	break;
	//case KEYSW4_GUAN_GROUP1:
	case KEYSW9_GUAN_GROUP1:
	gGrouppreValue = 1;
    gbulb_assignment_value(gGrouppreValue,0x11,0x01);
	gbulb_keypeidui_process();
	//-PRINT("gbulbsw4\n");
	break;
	case KEY_LDINC_SWLENG:
	
//	if(!key_linkagef) break;

    if(key_leng_sewenflag)
	{
	  gbulb_assignment_value(gGrouppreValue,0x1d,0x01);
	  keyliangdusewenlinkage(1, 0, 0, 0); //clr the counter and set the flag
	}
	else if(key_liandu_incflag)// key_liandu_decflag
	{
	  gbulb_assignment_value(gGrouppreValue,0x15,0x00);
	  keyliangdusewenlinkage(0, 0, 0, 1);//clr the counter and set the flag
	}
	break;
	case KEY_LDINC_SWNUAN:
    if(key_nuan_sewenflag)
	{
	  gbulb_assignment_value(gGrouppreValue,0x1d,0x00);
	  keyliangdusewenlinkage(0, 1, 0, 0); //clr the counter and set the flag
	}
	else if(key_liandu_incflag)// key_liandu_decflag
	{
	  gbulb_assignment_value(gGrouppreValue,0x15,0x00);
	  keyliangdusewenlinkage(0, 0, 0, 1);//clr the counter and set the flag
	}
	break;
	case KEY_LDDEC_SWNUAN:
    if(key_nuan_sewenflag)
	{
	  gbulb_assignment_value(gGrouppreValue,0x1d,0x00);
	  keyliangdusewenlinkage(0, 1, 0, 0); //clr the counter and set the flag
	}
	else if(key_liandu_decflag)// key_liandu_decflag
	{
	  gbulb_assignment_value(gGrouppreValue,0x15,0x01);
	  keyliangdusewenlinkage(0, 0, 1, 0); //clr the counter and set the flag
	}
	break;
	case KEY_LDDEC_SWLENG:
	 if(key_leng_sewenflag)
	{
	  gbulb_assignment_value(gGrouppreValue,0x1d,0x01);
	  keyliangdusewenlinkage(1, 0, 0, 0); //clr the counter and set the flag
	}
	else if(key_liandu_decflag)// key_liandu_decflag
	{
	  gbulb_assignment_value(gGrouppreValue,0x15,0x01);
	  keyliangdusewenlinkage(0, 0, 1, 0); //clr the counter and set the flag
	}
	break;
	case KEY_LDINC_LDDEC_SWRUANG:
		if(key_nuan_sewenflag)
		{
		  gbulb_assignment_value(gGrouppreValue,0x1d,0x00);
		  keyliangdusewenlinkage(0, 1, 0, 0); //clr the counter and set the flag
		}
	break;
	case KEY_LDINC_LDDEC_SWLENG:
		if(key_leng_sewenflag)
		{
		  gbulb_assignment_value(gGrouppreValue,0x1d,0x01);
		  keyliangdusewenlinkage(1, 0, 0, 0); //clr the counter and set the flag
		}
	break;
	case KEYSW8SW4_RFWAVE_TST:
	  	
	if(powerupflag)
	{
	   powerupflag = 0;
	   //eeprom check
	   	//--------if(user_factorytestiic())
		{
		   //P12 = 1;
			//gpio_set(GPIOB_3, 1);
			BlueLedOn();
		   Delay_ms(5000);
			//P12 = 0;
			//gpio_set(GPIOB_3, 0);
			BlueLedOff();
		}
		//-------------else
		{
	  // powerupflag = 0;
	      //P12 = 1;
			//
			//gpio_set(GPIOB_3, 1);
			BlueLedOn();
	    }
	   //-P12 = 1;
	   //rf check
	   factorytstrfsingalf = 1;
	  //------------ RF_SingleWaveTest(0x02,12);
	   do
	   {
	     //PRINT("rf test \r\n");
	   	  Delay_ms(5);
	   //}while(1);
	   }while(rfsingaltst_counter < 60000);
	   //P12 = 0;
		 //gpio_set(GPIOB_3, 0);
		 BlueLedOff();
	   rfsingaltst_counter = 0;
	   factorytstrfsingalf = 0;
	   //-user_rfInit(0);
	   //--------------RF_Init();
	}
	break;
	/*case KEYSW16SW12_FACTORYWAVE:
	if(powerupflag)
	{
	   powerupflag = 0;
		if(user_factorytestiic())
		{
		   P12 = 1;
		   Delay_ms(5000);
			P12 = 0;
		}
		else
		{
	  // powerupflag = 0;
	      P12 = 1;
	    }
	   factorytstrfsingalf = 1;
	   RF_SingleWaveTest(0x02,12);
	   do
	   {
	     //PRINT("rf test \r\n");
	   	  Delay_ms(5);
	   }while(4000);
	   //}while(rfsingaltst_counter < 60000);
	   P12 = 0;
	   rfsingaltst_counter = 0;
	   factorytstrfsingalf = 0;
	   //-user_rfInit(0);
	   RF_Init();
	}
	break;*/
	case KEYSW15SW11_VERSION:
	 if(powerupflag)
	 {
		  powerupflag = 0;
			for(ui = 0; ui < TST_VERSION; ui++)
			{
			     //P12 = 1;
				//gpio_set(GPIOB_3, 1);
				BlueLedOn();
			  	 Delay_ms(100);
				 //P12 = 0;
				//gpio_set(GPIOB_3, 0);
				BlueLedOff();
				 Delay_ms(100);
			}
		
	 }
	break;
	case KEY_WIFIRST_LDDEC:
	case KEY_WIFIRST_LDINC:
	case KEY_WIFIRST_LDDEC_LDINC:
	case KEYSW18SW1_WIFIRST:
	if(!wifikeypressf)
	{
	  wifikeypressf = 1;//key change to clr
	  timelongkey_cnt += wifilinkage_cnt;//keep the long key counter
	}
	//P12 = 1;
	//gpio_set(GPIOB_3, 1);
	BlueLedOn();
	wifilinkage_cnt = timelongkey_cnt;

	 if(timelongkey_cnt >= 5000)
	 {
	gbulbGroupValue = gGrouppreValue;
	gbulbwifipd_value = 0x33;
	gbulbTypeValue = 0x33;
	gbulbHandleValue = 0x00;
	//check to rf tx mode
	keypress_initrf();
	//press flag
	//if(!longkeypress_stepf)

	validkeypressf = 1;	 //to start counter the timer
	
		// to sync the key press or release
	//lit up the led
	
	
	timesleep_cnt = 0;//clr the counter to sleep	 
	 }
	break;


	default:
	//-PRINT("gbulbdefault\n");
	//P12 = 0;//led output 0
	//gpio_set(GPIOB_3, 0);
	BlueLedOff();
	break;	
		
	}

}

void keylearnprocess(void)
{
  bool learmodeflag = 0;
 if(keylearnflag)
 {
	//-PRINT("learn mode \n");
 	keylearnflag = 0;
	//-------------time1ms_cnt = 0;
	//learmodeflag = 1;
	//user_rfInit(1);//to rx mode
	//-------------RF_Init();
	//-----------SwitchToRxMode();
	//---------rf_received_package();
	kp_txinitf = 0;//need to init rf again to tx mode if key press
	//------------PowerDown_Rf();
 }

}

/**
 * @brief   clr flag when key change
 * @note
 * @param   
 * @retval  
 */

 void clr_longkeysteprfsend(void)
 {
 	 if(longkeypress_stepf)
	 {
	  validkeypressf = 0;
	 }
	 longkeypress_step1f = 0;
	 longkeypress_stepf = 0;
	 longkeypress_step2f = 0;

 }

//












