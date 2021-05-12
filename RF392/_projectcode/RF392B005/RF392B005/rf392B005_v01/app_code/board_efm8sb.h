/******************************************************************************
* Copyright (C) 2017, Huada Semiconductor Co.,Ltd All rights reserved.    
*
* This software is owned and published by: 
* Huada Semiconductor Co.,Ltd ("HDSC").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND 
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with HDSC 
* components. This software is licensed by HDSC to be adapted only 
* for use in systems utilizing HDSC components. HDSC shall not be 
* responsible for misuse or illegal use of this software for devices not 
* supported herein. HDSC is providing this software "AS IS" and will 
* not be responsible for issues arising from incorrect user implementation 
* of the software.  
*
* Disclaimer:
* HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS), 
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING, 
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED 
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED 
* WARRANTY OF NONINFRINGEMENT.  
* HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT, 
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT 
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION, 
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR 
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT, 
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA, 
* SAVINGS OR PROFITS, 
* EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. 
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED 
* FROM, THE SOFTWARE.  
*
* This software may be replicated in part or whole for the licensed use, 
* with the restriction that this Disclaimer and Copyright notice must be 
* included with each copy of this software, whether used in part or whole, 
* at all times.
*/
/******************************************************************************/
/** \file stkhc32l13x.h
 **
 ** stk board common define.
 ** @link SampleGroup Some description @endlink
 **
 **   - 2018-03-09  1.0  Lux First version.
 **
 ******************************************************************************/
#ifndef __BOARD_EFM8SB_H__
#define __BOARD_EFM8SB_H__

#include <SI_EFM8SB1_Register_Enums.h>

SI_SBIT(INDICADE_PIN, SFR_P2, 7);

///< touch int
///< USER KEY
SI_SBIT(SEMI74HC_SCK, SFR_P0, 4);
SI_SBIT(SEMI74HC_RCK, SFR_P0, 5);

SI_SBIT(SEMI74HC_SER, SFR_P0, 6);



SI_SBIT(LT8920_SPICLK_PIN, SFR_P1, 5);
SI_SBIT(LT8920_RESET_PIN, SFR_P1, 7);

SI_SBIT(LT8920_SPISS_PIN, SFR_P1, 3);

SI_SBIT(LT8920_MISO_PIN, SFR_P1, 2);

SI_SBIT(LT8920_MOSI_PIN, SFR_P1, 6);

//#define SEMI74HC_G   LT8920_SPISS_PIN
//SI_SBIT(LT8920_PKT_PIN, SFR_P1, 6);

//lt8920


//----------------------

void userswd_tonormal_ioout(void);
void user_othernormal_ioinit(void);
//-----------------------
/*void user_led1_litup(void);
void user_led2_litup(void);
void user_led3_litup(void);
void user_led4_litup(void);
void user_led5_litup(void);
void user_led6_litup(void);
void user_led7_litup(void);

void user_led1_litoff(void);
void user_led2_litoff(void);
void user_led3_litoff(void);
void user_led4_litoff(void);
void user_led5_litoff(void);
void user_led6_litoff(void);
void user_led7_litoff(void);*/

void user_ledall_turnon(void);
void user_ledall_turnoff(void);

void user_enable_touchint(void);
void user_disable_touchint(void);
void user_touchIO_init(void);

void touch_sda_outcfg_init(void);
void touch_sda_ininit(void);

void set_syssleep(unsigned char val);
unsigned char get_syssleepsta(void);

void user_timer_process(void);

void delay1ms(unsigned char ums);
void app_delayus(unsigned char us);
void app_delay10us(unsigned char us);
#endif
