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
	delay_init();	    	 	//��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 		//���ڳ�ʼ��Ϊ115200
	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();					//��ʼ������
	FSMC_SRAM_Init();			//��ʼ���ⲿSRAM	 
	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ��
	my_mem_init(SRAMEX);		//��ʼ���ⲿ�ڴ��
	OSInit();					//UCOS��ʼ��
	while(lwip_comm_init()) 	//lwip��ʼ��
	{
		printf("Lwip Init failed!"); 	//lwip��ʼ��ʧ��
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
