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

void* myclient_startroutine (void *arg)
{
 	int 			i = 0, ret = 0;
 	int 			connfd = 0;
 
	unsigned char 	*data = "abcdefg";
 	int 			datalen = 5;
 	
	unsigned char  	*out = NULL;
	int 			outlen = 0;
	void 			*handle = arg;
	
	//客户端 socket池 获取一条连接 
	ret = sckCltPool_getConnet(handle, &connfd);
	if (ret != 0)
	{
		printf("func sckCltPool_getConnet() err:%d\n", ret);
		return NULL;
	}
	
	//一个客户端连接，想服务器发送 10次数据
	for (i=0; i<10; i++)
	{
		//客户端 socket池 发送数据 
		ret = sckCltPool_send(handle, connfd, data, datalen);
		if (ret == Sck_ErrPeerClosed)
 		{ 
 			printf("sckCltPool_send 客户端检测到 服务器已经关闭 退出\n");
 			break;	
 		}
 		else if (ret == Sck_ErrTimeOut)
 		{
 			printf(" sckCltPool_send timeout \n");
 			break;
 		}
 		else if (ret != 0)
 		{
 			printf("fun sckServer_rev() err:%d \n", ret);
 			break;
 		}
	
		
		//客户端 socket池 接受数据
		ret =  sckCltPool_rev(handle, connfd, &out, &outlen); //1
		if (ret == Sck_ErrPeerClosed)
 		{ 
 			printf("sckCltPool_rev 客户端检测到 服务器已经关闭 退出\n");
 			break;	
 		}
 		else if (ret == Sck_ErrTimeOut)
 		{
 			printf(" sckCltPool_rev timeout \n");
 			break;
 		}
 		else if (ret != 0)
 		{
 			printf("fun sckCltPool_rev() err:%d \n", ret);
 			break;
 		}
 		printf("客户端接收到服务器的回射，out:%s \n", out);
 		
 		sck_FreeMem((void **)&out);
	}
	
	//客户端 socket池 把连接放回 socket池中 
	sckCltPool_putConnet(handle, connfd, 0); //0正常 1
	
 	return NULL;
}


int main()
{
	int 		ret = 0, i = 0;
	char 		*ip = "127.0.0.1"; 
	int 		port = 8001;
	int 		time = 3;
	int 		connfd = 0;
	
	void 		*handle = NULL;
	pthread_t 	pidArray[1024];   //线程ID数组
	
//typedef struct _SCKClitPoolParam
//{
//	char 	serverip[64];
//	int 	serverport;
//	int 	bounds; //池容量
//	int 	connecttime;
//	int 	sendtime;
//	int 	revtime;
//}SCKClitPoolParam;

	SCKClitPoolParam			sckClitPoolParm;
	memset(&sckClitPoolParm, 0, sizeof(SCKClitPoolParam));

	strcpy(sckClitPoolParm.serverip,  "127.0.0.1");
	sckClitPoolParm.serverport = 8001;
	sckClitPoolParm.bounds = 10;
	sckClitPoolParm.connecttime = 3;
	sckClitPoolParm.sendtime = 3;
	sckClitPoolParm.revtime = 3;
	
	
	//客户端 socket池初始化
	ret = sckCltPool_init(&handle, &sckClitPoolParm);
	if (ret != 0)
	{
		printf("func  sckCltPool_init() err:%d \n ", ret);
		return ret;
	}
	
	//启动多线程 
	for (i=0; i<7; i++)
	{
		pthread_create(&pidArray[i], NULL, myclient_startroutine, handle);
	}
	
	
	//主进程 等待子线程 结束
	for (i=0; i<7; i++)
	{
	 	pthread_join(pidArray[i], NULL);
	}
	
	
	//客户端 socket池 销毁连接
	sckCltPool_destroy(handle);

	printf("client hello....\n");
	
	return 0;
}

