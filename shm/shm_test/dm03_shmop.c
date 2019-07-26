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

// int shmget(key_t key, size_t size, int shmflg);
// A valid segment identifier, shmid, is returned on success, -1 on error.
int  main()
{
	//创建共享内存
	int 	shmid = 0;
	//创建共享内存 , 相当于打开文件 
	//若共享内存存在 则使用   fopen()
	//若共享内存 不存在 则报错 -1
	shmid = shmget(0x1111, 128, 0666);
	if (shmid < 0)
	{
		printf("创建共享内存失败\n");
		return 0;
	}	
	printf("shm hello...\n");
	
	return 0;
}


int  main_2()
{

	int 	shmid = 0;
	//创建共享内存 , 相当于打开文件 
	//若共享内存存在 则使用   fopen()
	//若共享内存 不存在 则创建 
	shmid = shmget(0x1111, 128, 0666 | IPC_CREAT);
	if (shmid < 0)
	{
		printf("创建共享内存失败\n");
		return 0;
	}
	
	printf("创建共享内存ok\n");

	return 0;
}


int  main_3()
{

	int 	shmid = 0;
	//创建共享内存 , 相当于打开文件 
	//若共享内存存在 则使用   报错
	//若共享内存 不存在 则创建 
	//作用 IPC_EXCL判断存在不存在的标志  避免已经存在的文件 被覆盖
	shmid = shmget(0x1111, 128, 0666 | IPC_CREAT | IPC_EXCL);
	if (shmid < 0)
	{
		printf("创建共享内存失败\n");
		return 0;
	}
	
	printf("创建共享内存ok\n");

	return 0;
}

int  main_4()
{
	int 	shmid = 0;
	//创建共享内存 , 相当于打开文件 
	//若共享内存存在 则使用   fopen()
	//若共享内存 不存在 则创建 
	shmid = shmget(0x1111, 128, 0666 | IPC_CREAT);
	if (shmid < 0)
	{
		printf("创建共享内存失败\n");
		return 0;
	}
	
	//使用共享内存
	//	void *shmat(int shmid, const void *shmaddr, int shmflg);
    void *p = shmat(shmid, NULL, 0);
    if (p == NULL)
    {
    	printf("func shmat() err:\n");
    	return 2;
    }
    strcpy(p, "abcdeg");
    
    printf("p:%s\n", (char *)p);
    
    //删除共享内存
    shmctl(shmid, IPC_RMID, NULL);
    
	printf("shm hello...\n");
	return 0;
}
