
平台：
	德飞莱stm32f103zet6开发板
	enc28j60网卡
	ov2640摄像头

本实验将实现如下功能：
	本实验在正点原子 LWIP的NETCONN编程方法实现TCP Server功能的项目基础上，实现一个信令服务：
		1. 收到"GET Header"后，从ov2640中读取摄像头的jpg数据。通过tcp返回客户端jpg数据总大小；
		2. 收到“GET Body”后，将缓存的jpg数据转发给客户端。
		
注意：本例程使用了UCOSII操作系统，默认开启DHCP。
