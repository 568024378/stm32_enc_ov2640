#ifndef __TCP_SERVER_DEMO_H
#define __TCP_SERVER_DEMO_H
#include "sys.h"
#include "includes.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK ENC28J60ģ��
//NETCONN API��̷�ʽ��TCP���������Դ���	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/4/30
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//*******************************************************************************
//�޸���Ϣ
//��
////////////////////////////////////////////////////////////////////////////////// 	   

#define FRAMEBUFFER_SIZE       (13*1024)

#define TCP_SERVER_RX_BUFSIZE	10		//����tcp server���������ݳ���

#define TCP_SERVER_PORT			8088	//����tcp server�Ķ˿�

#define LWIP_SEND_HEADER		0x01	//��ʾ׼������ͷ��Ϣ
#define LWIP_SEND_BODY          0x02    //��ʾ׼����������

extern u8 tcp_server_recvbuf[TCP_SERVER_RX_BUFSIZE];	//TCP�ͻ��˽������ݻ�����
extern u8 tcp_server_flag;			//TCP���������ݷ��ͱ�־λ

INT8U tcp_server_init(void);		//TCP��������ʼ��(����TCP�������߳�)
#endif

