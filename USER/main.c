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
	while(OV2640_Init())			//��ʼ��OV2640
	{
		printf("OV2640 Init Error!\n");
		delay_ms(1000);
	}
	printf("OV2640 Init Success!\n");
	OV2640_JPEG_Mode();							//����ov2640���jpeg���� 
  	OV2640_OutSize_Set(240,240); 
	// ������ov2640���ٶ�����
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
	delay_init();	    	 	//��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 		//���ڳ�ʼ��Ϊ115200
	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
	// KEY_Init();					//��ʼ������
	FSMC_SRAM_Init();			//��ʼ���ⲿSRAM	 
	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ��
	my_mem_init(SRAMEX);		//��ʼ���ⲿ�ڴ��
	MX_OV2640_Init();
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
