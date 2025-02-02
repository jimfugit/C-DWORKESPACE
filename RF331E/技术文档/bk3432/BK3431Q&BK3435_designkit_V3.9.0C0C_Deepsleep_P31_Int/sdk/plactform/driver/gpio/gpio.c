/**
****************************************************************************************
*
* @file gpio.c
*
* @brief icu initialization and specific functions
*
* Copyright (C) Beken 2009-2016
*
* $Rev: $
*
****************************************************************************************
*/

#include <stddef.h>     // standard definition
#include "BK3435_reg.h"
#include "gpio.h"
#include "timer.h"      // timer definition

#include "rwip.h"       // SW interface
#include "h4tl.h"
#include "nvds.h"       // NVDS

#include "dbg.h"
#include "icu.h"
#include "rf.h"
#include "app.h"
#include "app_task.h"
#include "uart.h"
#include "user_config.h"


volatile unsigned long * GPIO_CFG[] = 
{
    &REG_APB5_GPIOA_CFG,
    &REG_APB5_GPIOB_CFG,
    &REG_APB5_GPIOC_CFG,
    &REG_APB5_GPIOD_CFG,
    &REG_APB5_GPIOE_CFG
};


volatile unsigned long * GPIO_DATA[] = 
{
    &REG_APB5_GPIOA_DATA,
    &REG_APB5_GPIOB_DATA,
    &REG_APB5_GPIOC_DATA,
    &REG_APB5_GPIOD_DATA,
    &REG_APB5_GPIOE_DATA
};

unsigned int GPIO_CFG_BACKUP[5];
unsigned int GPIO_DATA_BACKUP[5];


static GPIO_INT_CALLBACK_T gpio_int_cb = NULL; 

void gpio_config(uint8_t gpio, Dir_Type dir, Pull_Type pull)
{
    uint32_t  temp_cfg, temp_data;
    uint8_t port = (gpio&0xf0)>>4;
    uint8_t  pin = gpio&0xf;
    temp_cfg = *(GPIO_CFG[port]);
    temp_data = *(GPIO_DATA[port]);
 
    if(dir == OUTPUT)	
    {
        temp_cfg |= (1<<pin);
        temp_cfg &= ~(1<<(pin+8));
		
        temp_data &= ~(1<<pin<<16);
    }
    else if(dir== INPUT)
    {
        temp_cfg |= 1<<pin;
        temp_cfg |= (1<<(pin+8));
        temp_data |= (1<<pin)<<16;
    }
	else if(dir == HIRESI)		
	{
		temp_cfg |= 1<<pin;
        temp_cfg |= (1<<(pin+8));
		temp_data  &= ~(1<<pin<<16);	
	}
    else
    {
        temp_cfg &= ~(1<<pin);
        temp_cfg |= (1<<(pin+8));
	  	temp_data  |= (1<<pin<<16);
    }

    switch(pull)
    {
    case PULL_HIGH:
        temp_cfg |= (1<<pin<<16);
        temp_cfg &= ~(1<<pin<<24);
        break;
    case PULL_LOW:
        temp_cfg &= ~(1<<pin<<16);
        temp_cfg |= (1<<pin<<24);
        break;
    case PULL_NONE:
        temp_cfg &= ~(1<<pin<<16);
        temp_cfg &= ~(1<<pin<<24);
        break;
    }
    *(GPIO_CFG[port]) = temp_cfg;
    *(GPIO_DATA[port]) = temp_data;
}

uint8_t gpio_get_input(uint8_t gpio)
{
    uint32_t temp;
    uint8_t port = (gpio&0xf0)>>4;
    uint8_t  pin = gpio&0xf;

    temp = *(GPIO_DATA[port]);
    temp = ((temp >> 0x08)&0xff)>>pin;
	
    return temp&0x01;
}

void gpio_set(uint8_t gpio, uint8_t val)
{
    uint32_t temp;
    uint8_t port = (gpio&0xf0)>>4;
    uint8_t  pin = gpio&0xf;
    
    temp = *(GPIO_DATA[port]);
    if(val)
    {
        temp |= 1<<pin;
    }
    else
    {
        temp &= ~(1<<pin);
    }

    *(GPIO_DATA[port]) = temp;
}



void gpio_init(void)
{
#if DEBUG_HW
    *(GPIO_CFG[2]) = 0XFF0000;
    *(GPIO_DATA[2]) = 0;
    REG_AHB0_ICU_DIGITAL_PWD |= (0X01 << 4);
#endif

#if GPIO_DBG_MSG
	*(GPIO_CFG[0]) = 0X0000ff;		    	
	*(GPIO_DATA[0]) = 0;
	gpio_config(0x34, OUTPUT, PULL_NONE);
	gpio_set(0x34, 0);
#endif
}


void gpio_triger(uint8_t gpio)
{
	gpio_set(gpio, 1);
	gpio_set(gpio, 0);
}


void gpio_cb_register(GPIO_INT_CALLBACK_T cb)
{
	if(cb)
	{
		gpio_int_cb = cb;
	}
}










/*BELON @Emily 上电2s后进入深度休眠 ,休眠电流1.4uA，P3.1下降沿中断唤醒，之后继续休眠，step 8*/
#if 1

#define CENTRAL_KEY_WAKEUP 1
#if CENTRAL_KEY_WAKEUP 

void app_gpio_int_cb(void)
{   
	//static uint8_t tog = 0; 
	 //irqPinLow = 1;  
	 UART_PRINTF("key wakeup\n");
	 key_wakeup_flag = 1;
	 //ke_timer_clear(APP_SCANTO_TIMER,TASK_APP);
	 //appm_start_scanning(); 
	 
	 /*if(tog)
	 {        
							tog = 0;        
							gpio_set(KEY_STATUS_PIN, 1);
	 }   
	 else
	 {       
							tog = 1;        
							gpio_set(KEY_STATUS_PIN, 0); 
	 }*/
}

void KEY_int_init(void) 
{	
	// SPI_Transfer_IRQ_Off();	
	//gpio_config(SPI_SYNC_PIN, OUTPUT, PULL_NONE);	
	/*gpio_config(KEY_STATUS_PIN, OUTPUT, PULL_NONE);	
	gpio_set(KEY_STATUS_PIN,1);	*/

	gpio_cb_register(app_gpio_int_cb);	

	//gpio_config(SPI_IRQ_PIN, INPUT, PULL_NONE);	
	gpio_config(KEY_IRQ_PIN, INPUT, PULL_HIGH);	
	REG_APB5_GPIO_WUATOD_TYPE |= 1<<(8*(KEY_IRQ_PIN>>4)+(KEY_IRQ_PIN&0x0f)); 
	//falling edge int	
	REG_APB5_GPIO_WUATOD_STAT |= 1<<(8*(KEY_IRQ_PIN>>4)+(KEY_IRQ_PIN&0x0f)); //cleat int status	
	Delay_ms(2);	
	REG_APB5_GPIO_WUATOD_ENABLE |= 1<<(8*(KEY_IRQ_PIN>>4)+(KEY_IRQ_PIN&0x0f)); 
	//	REG_AHB0_ICU_DEEP_SLEEP0 |= 1<<(8*(SPI_IRQ_PIN>>4)+(SPI_IRQ_PIN&0x0f));			
	REG_AHB0_ICU_INT_ENABLE |= INT_STATUS_GPIO_bit;	
}

#endif 
 
#endif

















void gpio_isr(void)
{
	REG_APB5_GPIO_WUATOD_ENABLE = 0x00000000; 
	REG_APB5_GPIO_WUATOD_STAT = 0xffffffff;
    REG_AHB0_ICU_INT_ENABLE &= (~(0x01 << 9));
    //gpio_triger(0x14);

	//triger int callback
	if(gpio_int_cb)
	{
		(*gpio_int_cb)();
	}
}

void gpio_test_init(void)
{
	gpio_config(GPIOC_0, FLOAT, PULL_HIGH);
	gpio_config(GPIOC_0, FLOAT, PULL_HIGH);
	gpio_config(GPIOC_0, FLOAT, PULL_HIGH);
	gpio_config(GPIOC_0, FLOAT, PULL_HIGH);
	gpio_config(GPIOC_0, FLOAT, PULL_HIGH);
}

void gpio_sleep(void)
{
	GPIO_CFG_BACKUP[0] = REG_APB5_GPIOA_CFG;
	GPIO_CFG_BACKUP[1] = REG_APB5_GPIOB_CFG;
	GPIO_CFG_BACKUP[2] = REG_APB5_GPIOC_CFG;
	GPIO_CFG_BACKUP[3] = REG_APB5_GPIOD_CFG;
	GPIO_CFG_BACKUP[4] = REG_APB5_GPIOE_CFG;
	
	GPIO_DATA_BACKUP[0] = REG_APB5_GPIOA_DATA;
	GPIO_DATA_BACKUP[1] = REG_APB5_GPIOB_DATA;
	GPIO_DATA_BACKUP[2] = REG_APB5_GPIOC_DATA;
	GPIO_DATA_BACKUP[3] = REG_APB5_GPIOD_DATA;
	GPIO_DATA_BACKUP[4] = REG_APB5_GPIOE_DATA;

	
	REG_APB5_GPIOA_CFG = 0x0000ffff;
	REG_APB5_GPIOA_DATA = 0x0000ffff;
	
	REG_APB5_GPIOB_CFG = 0x0000ffff;
	REG_APB5_GPIOB_DATA = 0x0000ffff;
	
	REG_APB5_GPIOC_CFG = 0x0000ffff;
	REG_APB5_GPIOC_DATA = 0x0000ffff;
	
	REG_APB5_GPIOD_CFG = 0x0000ffff;
	REG_APB5_GPIOD_DATA = 0x0000ffff;
	
	REG_APB5_GPIOE_CFG = 0x0000ffff;
	REG_APB5_GPIOE_DATA = 0x0000ffff;
}

void gpio_wakeup(void)
{
	REG_APB5_GPIOA_CFG = GPIO_CFG_BACKUP[0];
	REG_APB5_GPIOB_CFG = GPIO_CFG_BACKUP[1];
	REG_APB5_GPIOC_CFG = GPIO_CFG_BACKUP[2];
	REG_APB5_GPIOD_CFG = GPIO_CFG_BACKUP[3];
	REG_APB5_GPIOE_CFG = GPIO_CFG_BACKUP[4];
	
	REG_APB5_GPIOA_DATA = GPIO_DATA_BACKUP[0];
	REG_APB5_GPIOB_DATA = GPIO_DATA_BACKUP[1];	
	REG_APB5_GPIOC_DATA = GPIO_DATA_BACKUP[2];
	REG_APB5_GPIOD_DATA = GPIO_DATA_BACKUP[3];
	REG_APB5_GPIOE_DATA = GPIO_DATA_BACKUP[4];
}




void DEBUG_MSG(uint8_t x)
{
#if GPIO_DBG_MSG
        
    gpio_set(GPIOD_4, 0);
    REG_APB5_GPIOA_DATA = x & 0xff;
    gpio_set(GPIOD_4, 1);
    //gpio_triger(GPIOD_4);
#endif
}


