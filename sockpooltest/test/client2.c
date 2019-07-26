#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
 
#include "poolsocket.h" 

/*
typedef struct _SCKClitPoolParam
{
	char 	serverip[64];
	int 	serverport;
	int 	bounds; //池容量
	int 	connecttime;
	int 	sendtime;
	int 	revtime;
}SCKClitPoolParam;
*/ 

void *mystart_routin(void *arg) 
{
	int ret = 0;
	int connfd = -1;
	void *handle = arg;
	
	unsigned char *data = "abcdefg";
	int datalen = 5;
	
	unsigned char *out = NULL;
	int outlen = -1;
		
	// 获取一条连接池中的链接：
	ret = sckCltPool_getConnet(handle, &connfd);
	if (ret != 0) {
		printf("从连接池 获取 连接失败：%d\n", ret);
		return NULL;	
	}
	
	while (1) {
		ret = sckCltPool_send(handle, connfd, data, datalen);
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
		
		ret = sckCltPool_rev(handle, connfd, &out, &outlen); 
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
		printf("------接收到 服务器回发数据：%s\n", out);		
	}
	sckCltPool_putConnet(handle, connfd, 0); 

	
	return NULL;
}


int main(void)
{
	int i = 0;
	int ret = 0;
	pthread_t pidArray[6] = {0};
	
	SCKClitPoolParam clientPoolparam;
	strcpy(clientPoolparam.serverip, "127.0.0.1");
	clientPoolparam.serverport = 8080;
	clientPoolparam.bounds = 10;
	clientPoolparam.connecttime = 3;
	clientPoolparam.sendtime = 3;
	clientPoolparam.revtime = 3;
	
	void *handle = NULL;

	//客户端 初始化
	ret = sckCltPool_init(&handle, &clientPoolparam);
	if (ret != 0) {
		printf("sckCltPool_init error %d\n", ret);	
		return ret;
	}
	
	while (1) {
		
		for (i = 0; i < 6; i++) {
			pthread_create(&pidArray[i], NULL, mystart_routin, handle);	
		}
		
		for (i = 0; i< 6; i++) {
			pthread_join(pidArray[i], NULL);	
		}
	}

	//销毁连接池
	sckCltPool_destroy(handle);

	return 0;	
}