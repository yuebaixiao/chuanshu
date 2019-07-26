#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>

#include <sys/ipc.h>
#include <sys/shm.h>

int main(void)
{
	int shmid = -1;
	
	char *buf = NULL;
	
	shmid = shmget(0x0018, 256, 0644 | IPC_CREAT);
	if (shmid == -1) {
		perror("shmget error");
		return -1;		
	}
	
	printf("-------------open shm ok\n");
	
	buf = shmat(shmid, NULL, SHM_RND);
	if (buf == (void *)-1) {
		perror("shmat error:");
		return -1;		
	}
	
	memcpy(buf, "hello", 5);
	
	printf("buf:%s\n", buf);
	
	getchar();
		
	shmdt(buf);
	
	printf("finish---dt-----------\n");
	
	getchar();
	
	int ret = shmctl(shmid, IPC_RMID, NULL);
	if (ret == -1) {
		perror("shmctl error:");
		return -1;	
	}
	
	return 0;
}
