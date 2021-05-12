/**
****************************************************************************************
*
* @file icu.c
*
* @brief icu initialization and specific functions
*
* Copyright (C) Beken 2009-2016
*
* $Rev: $
*
****************************************************************************************
*/

/**
****************************************************************************************
* @addtogroup ICU
* @ingroup ICU
* @brief ICU
*
* This is the driver block for ICU
* @{
****************************************************************************************
*/


#include <stddef.h>     // standard definition
#include "rwip_config.h"
#include "rwip.h"
#include "user_config.h"
#include "BK3435_reg.h"
#include "icu.h"      // timer definition
#include "rf.h"
#include "flash.h"
#include "gpio.h"


static volatile uint8_t reduce_voltage_set=0;
static uint8_t default_sleep_mode = 0;  //0:降压休眠   1:普通idel
extern uint8_t system_sleep_flag;
extern uint8_t system_mode;
extern uint32_t flash_mid;

void system_sleep_init(void)
{
#if SYSTEM_SLEEP
    system_sleep_flag = 0x1;
#else
    system_sleep_flag = 0x0;
#endif
    if((system_mode & RW_DUT_MODE) == RW_DUT_MODE)
    {
    system_sleep_flag = 0x0;
    }
}


void icu_init(void)
{
#if DEBUG_HW
    REG_AHB0_ICU_LPO_CLK_ON |= (0x01 << 2);
#endif

    REG_AHB0_ICU_FLASH &= ~(0xff << 16);
    REG_AHB0_ICU_FLASH |= (0x15 << 16);

    REG_AHB0_ICU_FLASH &= ~(0xffff << 0);
    REG_AHB0_ICU_FLASH |= (0x10f << 0);

    if( (flash_mid==XTX_FLASH_1)&&(HZ32000==1) )
    {
        REG_AHB0_ICU_CPU_STATUS  = 0x661;
        REG_AHB0_ICU_CLKSRCSEL = 0X000001B1; //usr 16M,
    }
    else
    {
        REG_AHB0_ICU_CPU_STATUS  = 0x771;
        REG_AHB0_ICU_CLKSRCSEL = 0X000001F9; //usr 16M,
    }


    REG_AHB0_ICU_DIGITAL_PWD = REG_AHB0_ICU_DIGITAL_PWD & (~0X02);

    REG_AHB0_ICU_CORECLKCON = 0X00;

        

    REG_AHB0_ICU_ANA_CTL |= (0X01 << 6);


}


uint8_t icu_get_sleep_mode(void)
{
	return default_sleep_mode;
}


void icu_set_sleep_mode(uint8_t v)
{
	default_sleep_mode = v;
}
#if SYSTEM_SLEEP


void cpu_reduce_voltage_sleep(void)
{
    reduce_voltage_set=1;

    REG_AHB0_ICU_DIGITAL_PWD |= (0x80 | (0X01 << 4));

 
#if (REDUCE_VOL_SLEEP)
    REG_AHB0_ICU_INT_ENABLE &= (~(0x01 << 9));

    if( (flash_mid==XTX_FLASH_1)&&(HZ32000==1) )
    {
        REG_AHB0_ICU_CLKSRCSEL = 0x19C;
        REG_AHB0_ICU_CPU_STATUS  = 0x631;
    }
    else
    {
        REG_AHB0_ICU_CLKSRCSEL = 0x1DC;
        REG_AHB0_ICU_CPU_STATUS  = 0x731;
    }
        
#else
     if( (flash_mid==XTX_FLASH_1)&&(HZ32000==1) )
    {
        REG_AHB0_ICU_CLKSRCSEL = 0X000001B0; //usr 16M,
    }
    else
    {
        REG_AHB0_ICU_CLKSRCSEL = 0X000001F8; //usr 16M,
    }
#endif

    REG_AHB0_ICU_DIGITAL_PWD |= SET_CLK48M_PWD;
    REG_AHB0_ICU_DIGITAL_PWD |= SET_CB_BAIS_PWD;
    REG_AHB0_ICU_DIGITAL_PWD |= SET_CLK16M_PWD;//can not power dn 16M, or flash cant nor be read
    REG_AHB0_ICU_DIGITAL_PWD |=SET_HP_LDO_PWD;
    REG_AHB0_ICU_CORECLKCON  = 0x1; // Power down MCU

}
void cpu_wakeup(void)
{
    if(reduce_voltage_set==1)
    {
        reduce_voltage_set=0;
        //REG_AHB0_ICU_INT_ENABLE |= (0x01 << 9);

        REG_AHB0_ICU_DIGITAL_PWD = 0x80 | (0X01 << 4);
         
        //REG_AHB0_ICU_CLKSRCSEL  = 0x1F9;
        //REG_AHB0_ICU_CPU_STATUS  = 0x771;
#if (REDUCE_VOL_SLEEP)
        REG_AHB0_ICU_INT_ENABLE |= (0x01 << 9);

        if( (flash_mid==XTX_FLASH_1)&&(HZ32000==1) )
        {
            REG_AHB0_ICU_CPU_STATUS  = 0x661;
            REG_AHB0_ICU_CLKSRCSEL = 0X000001B1; //usr 16M,
        }
        else
        {
            REG_AHB0_ICU_CPU_STATUS  = 0x771;
            REG_AHB0_ICU_CLKSRCSEL = 0X000001F9; //usr 16M,
        }        
#else
         if( (flash_mid==XTX_FLASH_1)&&(HZ32000==1) )
        {
            REG_AHB0_ICU_CLKSRCSEL = 0X000001B1; //usr 16M,
        }
        else
        {
            REG_AHB0_ICU_CLKSRCSEL = 0X000001F9; //usr 16M,
        }
#endif
    }
}

void cpu_idle_sleep(void)
{
	REG_AHB0_ICU_CORECLKCON = 0x01;//MCU sleep
}

#endif


extern void CLK32K_AutoCali_init(void);
extern volatile uint32_t XVR_ANALOG_REG_BAK[16];

void switch_clk(uint8_t clk)
{
    REG_AHB0_ICU_DIGITAL_PWD = REG_AHB0_ICU_DIGITAL_PWD & (~0X02);

    if (clk == MCU_CLK_16M )
    {
        mHWreg_Assign_XVR_Regsiter(09, 0x74203C0A);
        XVR_ANALOG_REG_BAK[0x09] = 0x74203C0A;

        REG_AHB0_ICU_CORECLKCON = 0X00; //clk div 0

        //REG_AHB0_ICU_CLKSRCSEL = 0X000001F9; //usr 16m,VN=7,VD=3
        if( (flash_mid==XTX_FLASH_1)&&(HZ32000==1) )
        {
            REG_AHB0_ICU_CLKSRCSEL = 0X000001B1; //usr 16M,
        }
        else
        {
            REG_AHB0_ICU_CLKSRCSEL = 0X000001F9; //usr 16M,
        }

    }
    else if (clk == MCU_CLK_64M )
    {
        mHWreg_Assign_XVR_Regsiter(09, 0x74203C4A);
        XVR_ANALOG_REG_BAK[0x09] = 0x74203C4A;
        REG_AHB0_ICU_CORECLKCON = 0X00; //clk div 0

        REG_AHB0_ICU_CLKSRCSEL = 0X000005FB; //usr PLL CLK SELT 64M

    }

    else if (clk == MCU_CLK_32M )
    {
        mHWreg_Assign_XVR_Regsiter(09, 0x74203C4A);
        XVR_ANALOG_REG_BAK[0x09] = 0x74203C4A;
        REG_AHB0_ICU_CORECLKCON = 0x04; //clk div 2

        REG_AHB0_ICU_CLKSRCSEL = 0X000005FB; //usr PLL CLK SELT 64M

    }
    else if (clk == MCU_CLK_48M )
    {
        mHWreg_Assign_XVR_Regsiter(09, 0x74203C0a);
        XVR_ANALOG_REG_BAK[0x09] = 0x74203C0a;
        REG_AHB0_ICU_CORECLKCON = 0x04; //clk div 2

        REG_AHB0_ICU_CLKSRCSEL = 0X000001FB; //usr PLL CLK SELT 64M
    }
#if (HZ32000)
    CLK32K_AutoCali_init();
#endif

}











/*BELON @Emily 上电2s后进入深度休眠 ,休眠电流1.4uA，P3.1下降沿中断唤醒，之后继续休眠，step 3*/
#if 1

void delay_us(uint32_t num)
{
	//for 48M clock
	//100=12.5us
	//16=2us
	//8=1us
	//for 32.768 clock
	//8=1.6ms
	//16M clock
	//100=120us
	uint32_t i,j;
	for(i=0; i<num; i++)
			for(j=0; j<3; j++)
			{
					;
			}
}

void set_gpio_deep_sleep(void)
{
	gpio_sleep();
	gpio_config(KEY_IRQ_PIN,INPUT,PULL_HIGH);  ///wakeup pin:input,pull high
	REG_AHB0_ICU_INT_ENABLE |= INT_STATUS_GPIO_bit; //(INT_STATUS_GPIO|INT_STATUS_GPIO_WAKEUP);
	REG_AHB0_ICU_DEEP_SLEEP0 |= 1<<(8*(KEY_IRQ_PIN>>4)+(KEY_IRQ_PIN&0x0f)); ///KEY_IRQ_PIN
}
void Enter_Deep_sleep(void)
{
	set_gpio_deep_sleep();
	set_flash_clk(8);    
	//flash_set_line_mode(1); 
	flash_set_1_mode();
	////Set_CPU_Speed_16M();
	
	REG_AHB0_ICU_ANALOG_MODE &= ~(0x1<<18);// Enable Test Mode of pwdSARADCldo1V
	delay_us(10);
	REG_AHB0_ICU_ANALOG_MODE &= ~(0x1<<21);// Enable Test Mode of pwd48MPLL1V
	delay_us(20);
	
	//BK3000_XVR_REG_0x09  = 0x18250000;
	XVR_REG09 = 0x18250000;
	
	delay_us(20);

	REG_AHB0_ICU_ADCCLKCON  = 0x1 ;
	REG_AHB0_ICU_UARTCLKCON = 0x1 ;
	REG_AHB0_ICU_I2CCLKCON  = 0x1 ;
	REG_AHB0_ICU_SPICLKCON  = 0x1 ;
	//// REG_AHB0_ICU_CEVA_CLKCON= 0x1 ;
	REG_AHB0_ICU_WDTCLKCON  = 0x1 ;
	////REG_AHB0_ICU_BK24CLKCON = 0x1 ;
	////REG_AHB0_ICU_LPO_CLKCON = 0x1 ;
	////REG_AHB0_ICU_PWM0CLKCON = 0x1 ;
	////REG_AHB0_ICU_PWM1CLKCON = 0x1 ;  
	////REG_AHB0_ICU_PWM2CLKCON = 0x1 ;  
	////REG_AHB0_ICU_PWM3CLKCON = 0x1 ;  
	////REG_AHB0_ICU_PWM4CLKCON = 0x1 ;

	REG_AHB0_ICU_SLEEP_TIME = 0x0 ; // Disable 32KHz ROSC Auto-Calibration as it is not used.

	
	//BK3000_XVR_REG_0x0A  = (XVR_ANALOG_REG_BAK[10] | 0x1);
	XVR_REG0A  = (XVR_ANALOG_REG_BAK[10] | 0x1);
	
	delay_us(10);
	REG_AHB0_ICU_INT_ENABLE=0;
	REG_AHB0_ICU_IRQ_ENABLE=0;
	
	////REG_AHB0_RSTNREG_LATCH=0x1;
	delay_us(10);
	////REG_AHB0_DCO16M_PWD     = 0x0 ;
	delay_us(20);

	// Write 0x3231 to Deep Sleep Word Register to enable deep-sleep
	REG_AHB0_ICU_DIGITAL_PWD = SET_CLK16M_PWD + SET_CLK48M_PWD + SET_CB_BAIS_PWD +
																		 SET_HP_LDO_PWD; ////+ SET_REF1V_PWD;
	//REG_AHB0_ICU_DEEP_SLEEP1 &= 0x0000FFFF  ;
	//REG_AHB0_ICU_DEEP_SLEEP1 |=( 0x3231<<16);
	REG_AHB0_ICU_DEEP_SLEEP1 |=( 0x3435<<16);
	delay_us(10);
	while(1);
}

#endif 





















//配置单载波发射
//freq:频点设置，双频点(2-80)
//power:功率等级(0x1-0xf)
void bk3435_singleWaveCfg(uint8_t freq, uint8_t power_level)
{
	uint32_t val = 0;

	val |= freq;
	val |= (power_level<< 7);
	XVR_REG24 = val;
	XVR_REG25 |= (0x1<<12) |(0x1<<13);

	while(1);
}


//修改发射功率
//power_level:功率等级(0x0-0xf)
void bk3435_set_power(uint8_t power_level)
{
	uint32_t val = 0;
	uint32_t reg = XVR_ANALOG_REG_BAK[0x04];

	XVR_REG24 &= ~(0x1 << 20);
	XVR_REG04 = reg | (0x1 << 29);
	val |= (power_level << 7);
	XVR_REG24 &= ~(0xf << 7);
	XVR_REG24 |= val;
}



