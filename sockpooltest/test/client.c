#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
 
#include "poolsocket.h"  

int main(void)
{
	char *ip = "127.0.0.1"; 
	int port = 8080;
	int time = 3; 
	int connfd = -1;
	int ret = -1;
	
	unsigned char *data = "abcdefg";
	int datalen = 5;
	
	unsigned char *out = NULL;
	int outlen = -1;
	
	//客户端 初始化
	ret = sckClient_init();
	if (ret != 0) {
		printf("sckClient_init error %d\n", ret);	
		return ret;
	}
	
	while (1) {
	
		//客户端 连接服务器
		ret = sckClient_connect(ip, port, time, &connfd);
	 	if (ret == Sck_ErrTimeOut) {
			printf("---客户端连接服务器 超时 \n");
			continue;
		} else if (ret != 0) {
			printf("客户端连接服务器 失败： errorNO：%d\n", ret);
			break;
		}
			
		//客户端 发送报文
		ret = sckClient_send(connfd, time, data, datalen);
		if (ret == Sck_ErrPeerClosed) {
			printf("---服务器关闭，客户端断开连接 \n");
			break;
		} else if (ret == Sck_ErrTimeOut) {
			printf("---服务器接收数据 超时 \n");
			continue;
		} else if (ret != 0) {
			printf("客户端发送数据失败：errorNO:%d\n", ret);
			break;
		}
		sleep(1);

		//客户端 接受报文
		ret = sckClient_rev(connfd, time, &out, &outlen); 
		if (ret == Sck_ErrPeerClosed) {
			printf("---服务器关闭，客户端断开连接 \n");
			break;
		} else if (ret == Sck_ErrTimeOut) {
			printf("---服务器发送数据 超时 \n");
			continue;
		} else if (ret != 0) {
			printf("客户端接收数据失败：errorNO:%d\n", ret);
			break;
		}	
	}

	//客户端 关闭和服务端的连接
	if (connfd != -1)
		sckClient_closeconn(connfd);
		
	//客户端 释放
	sckClient_destroy();
	
	return 0;	
}