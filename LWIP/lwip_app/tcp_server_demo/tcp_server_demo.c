#include "tcp_server_demo.h"
#include "lwip/opt.h"
#include "lwip_comm.h"
#include "led.h"
#include "lwip/lwip_sys.h"
#include "lwip/api.h"
#include "delay.h"
#include "ov2640.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK ENC28J60ģ��
//NETCONN API��̷�ʽ��TCP���������Դ���	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/3/21
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//*******************************************************************************
//�޸���Ϣ
//��
////////////////////////////////////////////////////////////////////////////////// 	   

// ���� ����jpg���ݵĿռ䡢�ռ�Ĵ�С
u8 FrameBuffer[FRAMEBUFFER_SIZE];
u32 fbLen = 0;
u8 ov2640_jpg_photo(void)
{
	fbLen = 0;
	while(OV2640_VSYNC==1);	 
	while(OV2640_VSYNC==0);	  		// 	������֡���֡����֤��һ֡������
	while(OV2640_VSYNC==1);	 
	while(OV2640_VSYNC==0);	  		// 	����һ֡���֡����֤��һ֡������
	while(OV2640_VSYNC==1)			//	��ʼ�ɼ�jpeg����
	{
		while(OV2640_HREF && fbLen < FRAMEBUFFER_SIZE)
		{  
			while(OV2640_PCLK==0); 
			FrameBuffer[fbLen++]=OV2640_DATA;
			while(OV2640_PCLK==1); 
		} 
	}
	if(fbLen >= FRAMEBUFFER_SIZE)
		return 1;
	return 0;
}

void itoa(u32 i, u8* a)
{
	u32 index = 0 , j = 0;
	while(i>0){
		a[index++] = i%10 + '0';
		i /= 10;
	}
	
	for(; j < index / 2 ; j ++){
		u8 t = a[index - j - 1];
		a[index - j - 1] = a[j];
		a[j] = t;
	}
	a[index++] = '\n';
	a[index++] = '\0';
}

u8 tcp_server_recvbuf[TCP_SERVER_RX_BUFSIZE];	//TCP�ͻ��˽������ݻ�����

u8 FrameBuffer[FRAMEBUFFER_SIZE];
u8 tcp_server_flag;								//TCP���������ݷ��ͱ�־λ

//TCP�ͻ�������
#define TCPSERVER_PRIO		8
//�����ջ��С
#define TCPSERVER_STK_SIZE	300
//�����ջ
OS_STK TCPSERVER_TASK_STK[TCPSERVER_STK_SIZE];

//tcp����������
static void tcp_server_thread(void *arg)
{
	OS_CPU_SR cpu_sr;
	u32 data_len = 0;
	struct pbuf *q;
	err_t err,recv_err;
	u8 remot_addr[4];
	struct netconn *conn, *newconn;
	static ip_addr_t ipaddr;
	static u16_t 			port;
	
	LWIP_UNUSED_ARG(arg);

	conn = netconn_new(NETCONN_TCP);  //����һ��TCP����
	netconn_bind(conn,IP_ADDR_ANY,TCP_SERVER_PORT);  //�󶨶˿� 
	netconn_listen(conn);  //�������ģʽ
	conn->recv_timeout = 10;  //��ֹ�����߳� �ȴ�10ms
	while (1) 
	{
		err = netconn_accept(conn,&newconn);  //������������
		if(err==ERR_OK) newconn->recv_timeout = 10;
		
		if (err == ERR_OK)    //���������ӵ�����
		{ 
			struct netbuf *recvbuf;

			netconn_getaddr(newconn,&ipaddr,&port,0); //��ȡԶ��IP��ַ�Ͷ˿ں�
			
			remot_addr[3] = (uint8_t)(ipaddr.addr >> 24); 
			remot_addr[2] = (uint8_t)(ipaddr.addr>> 16);
			remot_addr[1] = (uint8_t)(ipaddr.addr >> 8);
			remot_addr[0] = (uint8_t)(ipaddr.addr);
			printf("����%d.%d.%d.%d�����Ϸ�����,�����˿ں�Ϊ:%d\r\n",remot_addr[0], remot_addr[1],remot_addr[2],remot_addr[3],port);
			
			while(1)
			{
				if(tcp_server_flag & LWIP_SEND_HEADER) {//����ͷ
					u8 s_Len[32];
					ov2640_jpg_photo();
					printf("jpg is %d\n",(int)fbLen);
					itoa(fbLen , s_Len);
					err = netconn_write(newconn ,s_Len,strlen((char *)s_Len),NETCONN_COPY); //����tcp_server_sendbuf�е�����
					if(err != ERR_OK)
					{
						printf("����ʧ��\r\n");
					}
					tcp_server_flag = 0;
				} else if(tcp_server_flag & LWIP_SEND_BODY) { //��������
					err = netconn_write(newconn ,FrameBuffer,fbLen,NETCONN_COPY); //����tcp_server_sendbuf�е�����
					if(err != ERR_OK)
					{
						printf("����ʧ��\r\n");
					}
					tcp_server_flag = 0;
				}

				if((recv_err = netconn_recv(newconn,&recvbuf)) == ERR_OK)  	//���յ�����
				{		
					OS_ENTER_CRITICAL(); //���ж�
					memset(tcp_server_recvbuf,0,TCP_SERVER_RX_BUFSIZE);  //���ݽ��ջ���������
					for(q=recvbuf->p;q!=NULL;q=q->next)  //����������pbuf����
					{
						//�ж�Ҫ������TCP_SERVER_RX_BUFSIZE�е������Ƿ����TCP_SERVER_RX_BUFSIZE��ʣ��ռ䣬�������
						//�Ļ���ֻ����TCP_SERVER_RX_BUFSIZE��ʣ�೤�ȵ����ݣ�����Ļ��Ϳ������е�����
						if(q->len > (TCP_SERVER_RX_BUFSIZE-data_len)) memcpy(tcp_server_recvbuf+data_len,q->payload,(TCP_SERVER_RX_BUFSIZE-data_len));//��������
						else memcpy(tcp_server_recvbuf+data_len,q->payload,q->len);
						data_len += q->len;  	
						if(data_len > TCP_SERVER_RX_BUFSIZE) break; //����TCP�ͻ��˽�������,����	
					}
					OS_EXIT_CRITICAL();  //���ж�
					data_len=0;  //������ɺ�data_lenҪ���㡣	
					printf("%s\r\n",tcp_server_recvbuf);  //ͨ�����ڷ��ͽ��յ�������

					// check cmd
					if(strcmp(tcp_server_recvbuf,"GET Header") == 0){
						tcp_server_flag = LWIP_SEND_HEADER;
					} else if(strcmp(tcp_server_recvbuf, "GET Body") == 0){
						tcp_server_flag = LWIP_SEND_BODY;
					}
					netbuf_delete(recvbuf);
				}else if(recv_err == ERR_CLSD)  //�ر�����
				{
					netconn_close(newconn);
					netconn_delete(newconn);
					printf("����:%d.%d.%d.%d�Ͽ��������������\r\n",remot_addr[0], remot_addr[1],remot_addr[2],remot_addr[3]);
					break;
				}
			}
		}
		//delay_ms(100);
	}
}


//����TCP�������߳�
//����ֵ:0 TCP�����������ɹ�
//		���� TCP����������ʧ��
INT8U tcp_server_init(void)
{
	INT8U res=0;
	OS_CPU_SR cpu_sr;

	OS_ENTER_CRITICAL();	//���ж�
	res = OSTaskCreate(tcp_server_thread,(void*)0,(OS_STK*)&TCPSERVER_TASK_STK[TCPSERVER_STK_SIZE-1],TCPSERVER_PRIO); //����TCP�������߳�
	printf("tcp_server_thread�̴߳�����:%d\r\n",res);
	OS_EXIT_CRITICAL();		//���ж�
	
	return res;
}


