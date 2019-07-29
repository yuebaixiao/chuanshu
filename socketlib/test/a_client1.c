#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include "poolsocket.h"

int  main(void)
{
	int 		ret = 0;
	char 		*ip = "127.0.0.1"; 
	int 		port = 8001;
	int 		time = 3;
	int 		connfd = 0;
	
	//客户端 初始化
	ret = sckClient_init();
	if (ret != 0)
	{
		printf("func sckClient_init() err:%d \n", ret);
		return ret;
	}

	//客户端 连接服务器
	ret = sckClient_connect(ip, port, time, &connfd);
	if (ret != 0)
	{
		printf("func sckClient_connect() err:%d \n", ret);
		return ret;
	}

	unsigned char *data = "abdefghijklmnopqrst";
	int 		datalen = 8;
	//客户端 发送报文
	ret = sckClient_send(connfd, time, data, datalen);
	if (ret != 0)
	{
		printf("func sckClient_send() err:%d \n", ret);
		return ret;
	}
	
	unsigned char 	*myout = NULL;
	int 			outlen = 0;
	
	//客户端 接受报文
	ret = sckClient_rev(connfd, time, &myout, &outlen); //1
	if (ret != 0)
	{
		printf("func sckClient_send() err:%d \n", ret);
		return ret;
	}
	
	printf("客户端收到的报文:%s \n", myout);
	//客户端 释放内存
	sck_FreeMem((void **)&myout);
	
	//客户端 关闭和服务端的连接
	sckClient_closeconn(connfd);
	
	//客户端 释放
	sckClient_destroy();

	printf("client hello....\n");

	return 0;
}

