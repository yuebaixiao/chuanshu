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


void *mystart_routine(void *arg)
{
	int 		ret = 0;
	int 		timeout = 3;
	int 		connfd = (int)arg;
	
	unsigned char 	*out = NULL;
	int 			outlen = 0;
	
	while (1)
	{	
		//服务器端端接受报文
		ret =  sckServer_rev(connfd, timeout, &out, &outlen); //1
		if (ret == Sck_ErrPeerClosed)
		{
			//printf("aaaaa \n");
			printf("服务器端检测到客户端有一条连接已关闭 \n");
			break;
		}
		else if (ret == Sck_ErrTimeOut)
		{
			printf("服务器端send超时\n");
			continue;
		}
		else if (ret != 0)
		{
			printf("服务器端 sckServer_send() err\n");
			break;
		}
	
		printf("out:%s \n", out);  //回射
		
		//服务器端发送报文
		ret =  sckServer_send(connfd, timeout, out, outlen);
		if (ret == Sck_ErrPeerClosed)
		{
			sck_FreeMem((void **)&out);
			printf("服务器端检测到客户端有一条连接已关闭\n");
			break;
		}
		else if (ret == Sck_ErrTimeOut)
		{
			sck_FreeMem((void **)&out);
			printf("服务器端send超时\n");
			continue;
		}
		else if (ret != 0)
		{
			sck_FreeMem((void **)&out);
			printf("服务器端 sckServer_send() err\n");
			break;
		}
		sck_FreeMem((void **)&out);
	}
	
	sckServer_close(connfd);
	return NULL;
}


int main()
{
	int 		ret 		= 0;
	int		 	port 		= 8001;
	int 		listenfd 	= 0;
	int 		timeout		= 3;
	int 		connfd = 0;
	pthread_t 	pid;
	
	
	//函数声明
	//服务器端初始化
	ret = sckServer_init(port, &listenfd);
	if (ret != 0)
	{
		printf("func sckServer_init() err:%d \n", ret);
		return ret;
	}
	
	while (1)
	{
		ret = sckServer_accept(listenfd, timeout, &connfd);
		if (ret == Sck_ErrTimeOut)
		{
			printf("func sckServer_accept() Sck_ErrTimeOut\n");
			continue;
		}
		else if (ret != 0)
		{
			ret = 2;
			printf("fun sckServer_accept() err :%d \n", ret);
			break;
		}
	
		pthread_create(&pid, NULL,  mystart_routine, (void *)(connfd));

	}


	//服务器端环境释放 
	int sckServer_destroy();
	printf("hello....\n");	
}
