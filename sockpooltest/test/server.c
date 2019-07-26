#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
 
#include "poolsocket.h"    
 
 void *start_routine(void * arg)
 {
 	int ret;
 	int timeout = 3;
 	int connfd = (int)arg;
 	
 	unsigned char *out = NULL;
 	int outlen = 0;
 	
 	while (1) {

		//服务器端端接受报文
		ret = sckServer_rev(connfd, timeout, &out, &outlen); 
		if (ret == Sck_ErrPeerClosed) {
			// 检测到 对端关闭，关闭本端。
			printf("----------------ErrPeerClosed 关闭服务器\n");
			break;
		} else if (ret == Sck_ErrTimeOut) {
			printf("---服务器检测到客户端发送数据 超时 \n");
			continue;
		} else if (ret != 0) {
			printf("未知错误\n");
			break;
		}
	
		// 处理数据。 ----- 回射
		printf("====客户端发送了：%s\n", out);
	
	 	//服务器端发送报文
		ret = sckServer_send(connfd, timeout, out, outlen);
	 	if (ret == Sck_ErrPeerClosed) {
			// 检测到 对端关闭，关闭本端。
			printf("---ErrPeerClosed \n");
			break;
		} else if (ret == Sck_ErrTimeOut) {
			printf("---服务器检测到本端发送数据 超时 \n");
			continue;
		} else if (ret != 0) {
			printf("未知错误\n");
			break;
		}
	}
	sckServer_close(connfd);
 	return NULL;
 }

int main(void)
{
	int listenfd;
	int port = 8080;
	int ret = 0;
	
	int timeout = 3;
	int connfd = -1;
	
	pthread_t pid;
	
	//服务器端初始化
	ret = sckServer_init(port, &listenfd);
	if (ret != 0) {
		printf("sckServer_init error %d\n", ret);	
		return ret;
	}
	
	while (1) {
		ret = sckServer_accept(listenfd, timeout, &connfd);
		if (ret == Sck_ErrTimeOut){
			printf("-----客户端连接超时----\n");
			continue;	
		} else if(ret != 0)  {
			printf("sckServer_accept error %d\n", ret);	
			return ret;
		}
		ret = pthread_create(&pid, NULL, start_routine, (void *)connfd);					
	}
 	
 	//服务器端环境释放 
	sckServer_destroy();

	return 0;	
}