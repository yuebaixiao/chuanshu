#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "keymngclientop.h"
#include "keymng_msg.h"
#include "socketlog.h"

int main111(void)
{
	KeyMng_Log(__FILE__, __LINE__, KeyMngLevel[0], 0, "%s", "00000000000000");
	KeyMng_Log(__FILE__, __LINE__, KeyMngLevel[1], 1, "%s", "11111111111111");
	KeyMng_Log(__FILE__, __LINE__, KeyMngLevel[2], 2, "%s", "22222222222222");
	KeyMng_Log(__FILE__, __LINE__, KeyMngLevel[3], 3, "%s", "33333333333333");
	KeyMng_Log(__FILE__, __LINE__, KeyMngLevel[4], 4, "%s", "44444444444444");
	
	return 0;	
}

int Usage()
{
    int nSel = -1;
    
    system("clear");    
    printf("\n  /*************************************************************/");
    printf("\n  /*************************************************************/");
    printf("\n  /*     1.密钥协商                                            */");
    printf("\n  /*     2.密钥校验                                            */");
    printf("\n  /*     3.密钥注销                                            */");
    printf("\n  /*     4.密钥查看                                            */");
    printf("\n  /*     0.退出系统                                            */");
    printf("\n  /*************************************************************/");
    printf("\n  /*************************************************************/");
    printf("\n\n  选择:");
    scanf("%d", &nSel);
    while(getchar() != '\n'); //把应用程序io缓冲器的所有的数据 都读走,避免影响下一次 输入
    
    return nSel;
}

int main()
{
	int 				ret = 0;
	int 				nSel = 0;
	
	MngClient_Info		mngClientInfo;
	memset(&mngClientInfo, 0, sizeof(MngClient_Info));

	// 初始化客户端结构体信息
	ret = MngClient_InitInfo(&mngClientInfo);
	if (ret != 0)
	{
		printf("func MngClient_InitInfo() err:%d \n ", ret);
		KeyMng_Log(__FILE__, __LINE__, KeyMngLevel[4], ret, "func MngClient_InitInfo() err:%d", ret);
	}
	
	while (1)
	{
		// 显示菜单  接收用户选择
		nSel = Usage();
		
		switch (nSel)
		{
		case KeyMng_NEWorUPDATE:	
			//密钥协商
			ret =  MngClient_Agree(&mngClientInfo);
			break;
		case KeyMng_Check:	
			//ret = MngClient_Check(&mngClientInfo);
			break;
		case KeyMng_Revoke:	
			//密钥注销
			break;
		case 0:	
			//退出
			return 0;
			
		default :
			printf("选项不支持\n");
			break;
		}
		
		// 结果展示给用户。
		if (ret)
		{
			printf("\n!!!!!!!!!!!!!!!!!!!!ERROR!!!!!!!!!!!!!!!!!!!!");
			printf("\n错误码是：%x\n", ret);
		}
		else
		{
			printf("\n!!!!!!!!!!!!!!!!!!!SUCCESS!!!!!!!!!!!!!!!!!!!!\n");
		}	
		getchar();	
	}
	
	return 0;
}
