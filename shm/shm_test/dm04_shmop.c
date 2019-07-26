#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int  main(void)
{
	int 	shmid = 0;
	//创建共享内存 , 相当于打开打开文件 
	//若共享内存存在 则使用   fopen()
	//若共享内存 不存在 则创建 
	shmid = shmget(0x1111, 128, 0666 | IPC_CREAT);
	if (shmid < 0)
	{
		printf("创建共享内存失败\n");
		return 0;
	}
		
	//使用共享内存
	//void *shmat(int shmid, const void *shmaddr, int shmflg);
    void *p = shmat(shmid, NULL, 0);
    if (p == NULL)
    {
    	printf("func shmat() err:\n");
    	return 2;
    }
    strcpy(p, "abcdeg");
       
    printf("p:%s\n", (char *)p);
    
    printf("任意键删除共享内存 \n");
    getchar();
    
    //删除共享内存
    shmctl(shmid, IPC_RMID, NULL);
    
	printf("shm hello...\n");
	
	return 0;
}
