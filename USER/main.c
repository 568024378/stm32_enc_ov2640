#include "led.h"
#include "delay.h"
#include "key.h"
#include "usart.h"	 
#include "sram.h"
#include "malloc.h"
#include "enc28j60.h" 	
#include "ov2640.h" 
#include "lwip/netif.h"
#include "lwip_comm.h"
#include "lwipopts.h"
#include "timer.h"
#include "uCosTask.h"
#include "includes.h"

void MX_OV2640_Init()
{
	int i = 0;
	while(OV2640_Init())			//初始化OV2640
	{
		printf("OV2640 Init Error!\n");
		delay_ms(1000);
	}
	printf("OV2640 Init Success!\n");
	OV2640_JPEG_Mode();							//设置ov2640输出jpeg数据 
  	OV2640_OutSize_Set(240,240); 
	// 以下是ov2640的速度设置
	SCCB_WR_Reg(0XFF,0X00);
	SCCB_WR_Reg(0XD3,45);
	SCCB_WR_Reg(0XFF,0X01);
	SCCB_WR_Reg(0X11,0X2); 
	for(i=0;i<10;i++)		
	{
		while(OV2640_VSYNC==1);	 
		while(OV2640_VSYNC==0);	  
	}
}


void system_Init()
{
	delay_init();	    	 	//延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 		//串口初始化为115200
	LED_Init();		  			//初始化与LED连接的硬件接口
	// KEY_Init();					//初始化按键
	FSMC_SRAM_Init();			//初始化外部SRAM	 
	my_mem_init(SRAMIN);		//初始化内部内存池
	my_mem_init(SRAMEX);		//初始化外部内存池
	MX_OV2640_Init();
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
