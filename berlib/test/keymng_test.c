#include "keymng_msg.h"
#include <stdio.h>
#include "itcast_asn1_der.h"
#include "itcastderlog.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int mywritefile(unsigned char *buf, int len){
  int fd = open("teacher.ber", O_WRONLY | O_CREAT, 0664);
  if (fd == -1){
    printf("fopen file error \n");
    return -1;
  }
  write(fd, buf, len);
  close(fd);
  return 0;
}


void test(){

  MsgKey_Res req;
  req.rv = 100;
  sprintf(req.clientId, "cli009");
  sprintf(req.serverId, "ser009");
  sprintf(req.r2, "1aa999");
  req.seckeyid = 999;

  unsigned char* myOut = NULL;
  int myOutlen = 0;
 
  MsgEncode(&req, ID_MsgKey_Res, &myOut, &myOutlen);
  mywritefile(myOut, myOutlen);

  void* ptr;
  int type;
  MsgDecode(myOut, myOutlen, &ptr, &type);
  if(type == ID_MsgKey_Res){
    MsgKey_Res* requ = (MsgKey_Res*)ptr;
    printf("rv:%d\n", requ->rv);
    printf("clientid:%s\n", requ->clientId);
    printf("ser:%s\n", requ->serverId);
    printf("r2:[%s]\n", requ->r2);
    printf("seckeyid:%d\n", requ->seckeyid);
  }

  MsgMemFree(&ptr,type); 
}

void test1(){
  
  MsgKey_Req req;
  req.cmdType = 212;
  sprintf(req.clientId, "clieng002");
  sprintf(req.AuthCode, "AuthCode002");
  sprintf(req.serverId, "serverId002");
  sprintf(req.r1, "abc");

  unsigned char* myOut = NULL;
  int myOutlen = 0;
 
  MsgEncode(&req, ID_MsgKey_Req, &myOut, &myOutlen);
  mywritefile(myOut, myOutlen);

  
  void* ptr;
  int type;
  MsgDecode(myOut, myOutlen, &ptr, &type);
  if(type == ID_MsgKey_Req){
    MsgKey_Req* requ = (MsgKey_Req*)ptr;
    printf("cmpd:%d\n", requ->cmdType);
    printf("clientid:%s\n", requ->clientId);
    printf("autocode:%s\n", requ->AuthCode);
    printf("ser:%s\n", requ->serverId);
    printf("r1:%s\n", requ->r1);
  }

  MsgMemFree(&ptr,type); 
  
}

int main(int argc, char** argv){  
  test1();
  test();
}
