#include "led.h"
#include "delay.h"
#include "key.h"
#include "usart.h"	 
#include "sram.h"
#include "malloc.h"
#include "enc28j60.h" 	 
#include "lwip/netif.h"
#include "lwip_comm.h"
#include "lwipopts.h"
#include "timer.h"
#include "uCosTask.h"
#include "includes.h"

void system_Init()
{
	delay_init();	    	 	//延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 		//串口初始化为115200
	LED_Init();		  			//初始化与LED连接的硬件接口
	KEY_Init();					//初始化按键
	FSMC_SRAM_Init();			//初始化外部SRAM	 
	my_mem_init(SRAMIN);		//初始化内部内存池
	my_mem_init(SRAMEX);		//初始化外部内存池
	OSInit();					//UCOS初始化
	while(lwip_comm_init()) 	//lwip初始化
	{
		printf("Lwip Init failed!"); 	//lwip初始化失败
		delay_ms(1000);
	}
}


int main(void)
{	 
	system_Init();
	while(1){
		uCos_main();
	}
}
