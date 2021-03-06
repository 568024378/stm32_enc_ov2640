#include "tcp_server_demo.h"
#include "lwip/opt.h"
#include "lwip_comm.h"
#include "led.h"
#include "lwip/lwip_sys.h"
#include "lwip/api.h"
#include "delay.h"
#include "ov2640.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK ENC28J60模块
//NETCONN API编程方式的TCP服务器测试代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/3/21
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//*******************************************************************************
//修改信息
//无
////////////////////////////////////////////////////////////////////////////////// 	   

// 输入 保存jpg数据的空间、空间的大小
u8 FrameBuffer[FRAMEBUFFER_SIZE];
u32 fbLen = 0;
u8 ov2640_jpg_photo(void)
{
	OS_CPU_SR cpu_sr;
	while(1) {
		OS_ENTER_CRITICAL();
		fbLen = 0;
		while(OV2640_VSYNC==1);	 
		while(OV2640_VSYNC==0);	  		// 	丢掉两帧或半帧，保证下一帧完整性
		while(OV2640_VSYNC==1)			//	开始采集jpeg数据
		{
			while(OV2640_HREF)
			{  
				while(OV2640_PCLK==0); 
				FrameBuffer[fbLen++]=OV2640_DATA;
				while(OV2640_PCLK==1); 
			} 
		}
		OS_EXIT_CRITICAL();
		if((FrameBuffer[0]==0XFF)&&(FrameBuffer[1]==0XD8)){
			printf("GetPhoto success , pbuf[0] = %x ; 1 = %x\n", FrameBuffer[0],FrameBuffer[1]);
			break;
		}
		printf("GetPhoto Error\n");
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

u8 tcp_server_recvbuf[TCP_SERVER_RX_BUFSIZE];	//TCP客户端接收数据缓冲区

u8 FrameBuffer[FRAMEBUFFER_SIZE];
u8 tcp_server_flag;								//TCP服务器数据发送标志位

//TCP客户端任务
#define TCPSERVER_PRIO		8
//任务堆栈大小
#define TCPSERVER_STK_SIZE	300
//任务堆栈
OS_STK TCPSERVER_TASK_STK[TCPSERVER_STK_SIZE];

//tcp服务器任务
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

	conn = netconn_new(NETCONN_TCP);  //创建一个TCP链接
	netconn_bind(conn,IP_ADDR_ANY,TCP_SERVER_PORT);  //绑定端口 
	netconn_listen(conn);  //进入监听模式
	conn->recv_timeout = 10;  //禁止阻塞线程 等待10ms
	while (1) 
	{
		err = netconn_accept(conn,&newconn);  //接收连接请求
		if(err==ERR_OK) newconn->recv_timeout = 10;
		
		if (err == ERR_OK)    //处理新连接的数据
		{ 
			struct netbuf *recvbuf;

			netconn_getaddr(newconn,&ipaddr,&port,0); //获取远端IP地址和端口号
			
			remot_addr[3] = (uint8_t)(ipaddr.addr >> 24); 
			remot_addr[2] = (uint8_t)(ipaddr.addr>> 16);
			remot_addr[1] = (uint8_t)(ipaddr.addr >> 8);
			remot_addr[0] = (uint8_t)(ipaddr.addr);
			printf("主机%d.%d.%d.%d连接上服务器,主机端口号为:%d\r\n",remot_addr[0], remot_addr[1],remot_addr[2],remot_addr[3],port);
			
			while(1)
			{
				if(tcp_server_flag & LWIP_SEND_HEADER) {//发送头
					u8 s_Len[32];
					ov2640_jpg_photo();
					printf("jpg is %d\n",(int)fbLen);
					itoa(fbLen , s_Len);
					err = netconn_write(newconn ,s_Len,strlen((char *)s_Len),NETCONN_COPY); //发送tcp_server_sendbuf中的数据
					if(err != ERR_OK)
					{
						printf("发送失败\r\n");
					}
					tcp_server_flag = 0;
				} else if(tcp_server_flag & LWIP_SEND_BODY) { //发送数据
					u8 * pbuf = (u8*)FrameBuffer;
					u32 send_size = 0;
					while(send_size + 1024 < fbLen){
						err = netconn_write(newconn ,pbuf,1024,NETCONN_COPY); //发送tcp_server_sendbuf中的数据
						if(err != ERR_OK)
						{
							printf("发送失败\r\n");
							continue;
						}
						pbuf += 1024;
						send_size += 1024;
					}
					err = netconn_write(newconn ,pbuf,fbLen - send_size,NETCONN_COPY); //发送tcp_server_sendbuf中的数据
					if(err != ERR_OK)
					{
						printf("发送失败\r\n");
					}
					tcp_server_flag = 0;
				}

				if((recv_err = netconn_recv(newconn,&recvbuf)) == ERR_OK)  	//接收到数据
				{		
					OS_ENTER_CRITICAL(); //关中断
					memset(tcp_server_recvbuf,0,TCP_SERVER_RX_BUFSIZE);  //数据接收缓冲区清零
					for(q=recvbuf->p;q!=NULL;q=q->next)  //遍历完整个pbuf链表
					{
						//判断要拷贝到TCP_SERVER_RX_BUFSIZE中的数据是否大于TCP_SERVER_RX_BUFSIZE的剩余空间，如果大于
						//的话就只拷贝TCP_SERVER_RX_BUFSIZE中剩余长度的数据，否则的话就拷贝所有的数据
						if(q->len > (TCP_SERVER_RX_BUFSIZE-data_len)) memcpy(tcp_server_recvbuf+data_len,q->payload,(TCP_SERVER_RX_BUFSIZE-data_len));//拷贝数据
						else memcpy(tcp_server_recvbuf+data_len,q->payload,q->len);
						data_len += q->len;  	
						if(data_len > TCP_SERVER_RX_BUFSIZE) break; //超出TCP客户端接收数组,跳出	
					}
					OS_EXIT_CRITICAL();  //开中断
					data_len=0;  //复制完成后data_len要清零。	
					printf("%s\r\n",tcp_server_recvbuf);  //通过串口发送接收到的数据

					// check cmd
					if(strcmp(tcp_server_recvbuf,"GET Header") == 0){
						tcp_server_flag = LWIP_SEND_HEADER;
					} else if(strcmp(tcp_server_recvbuf, "GET Body") == 0){
						tcp_server_flag = LWIP_SEND_BODY;
					}
					netbuf_delete(recvbuf);
				}else if(recv_err == ERR_CLSD)  //关闭连接
				{
					netconn_close(newconn);
					netconn_delete(newconn);
					printf("主机:%d.%d.%d.%d断开与服务器的连接\r\n",remot_addr[0], remot_addr[1],remot_addr[2],remot_addr[3]);
					break;
				}
			}
		}
		//delay_ms(100);
	}
}


//创建TCP服务器线程
//返回值:0 TCP服务器创建成功
//		其他 TCP服务器创建失败
INT8U tcp_server_init(void)
{
	INT8U res=0;
	OS_CPU_SR cpu_sr;

	OS_ENTER_CRITICAL();	//关中断
	res = OSTaskCreate(tcp_server_thread,(void*)0,(OS_STK*)&TCPSERVER_TASK_STK[TCPSERVER_STK_SIZE-1],TCPSERVER_PRIO); //创建TCP服务器线程
	printf("tcp_server_thread线程错误码:%d\r\n",res);
	OS_EXIT_CRITICAL();		//开中断
	
	return res;
}


