#include "keymng_msg.h"
#include "itcast_asn1_der.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int MsgReqEncode_(MsgKey_Req *pReq, ITCAST_ANYBUF **outData){
  int ret = 0;
  ITCAST_ANYBUF* pTmp     = NULL;
  ITCAST_ANYBUF* pHeadBuf = NULL;
  ITCAST_ANYBUF* pTmpBuf  = NULL;
  ITCAST_ANYBUF* pOutData = NULL;
  unsigned char* tmpout   = NULL;
  int tmpoutlen = 0;

  //cmdType
  ret = DER_ItAsn1_WriteInteger(pReq->cmdType, &pHeadBuf);
  if (ret != 0){
    return ret;
  }

  pTmp = pHeadBuf;
  //clientId
  ret = EncodeChar(pReq->clientId, strlen(pReq->clientId), &pTmp->next);
  if (ret != 0){
    DER_ITCAST_FreeQueue(pHeadBuf);
    return ret;
  }
  
  pTmp = pTmp->next;
  //AuthCode
  ret = EncodeChar(pReq->AuthCode, strlen(pReq->AuthCode), &pTmp->next);
  if (ret != 0){
    DER_ITCAST_FreeQueue(pHeadBuf);
    return ret;
  }
  
  pTmp = pTmp->next;
  //serverId
  ret = EncodeChar(pReq->serverId, strlen(pReq->serverId), &pTmp->next);
  if (ret != 0){
    DER_ITCAST_FreeQueue(pHeadBuf);
    return ret;
  }
  
  pTmp = pTmp->next;
  //r1
  ret = EncodeChar(pReq->r1, strlen(pReq->r1), &pTmp->next);
  if (ret != 0){
    DER_ITCAST_FreeQueue(pHeadBuf);
    return ret;
  }

  ret = DER_ItAsn1_WriteSequence(pHeadBuf, &pOutData);
  if (ret != 0){
    DER_ITCAST_FreeQueue(pHeadBuf); 
    return ret;
  }
  
  *outData = pOutData; 
  DER_ITCAST_FreeQueue(pHeadBuf);

  return ret;
}

int MsgEncode(void* pStruct , int type, unsigned char** outData, int* outLen){

  ITCAST_ANYBUF*pHeadbuf = NULL, *pTemp = NULL;
  ITCAST_ANYBUF*pOutData = NULL;
  int ret = 0;

  if (pStruct == NULL && type < 0 || outData == NULL || outLen == NULL){
    ret = KeyMng_ParamErr;
    printf("func MsgEncode() err:%d \n", ret);
    return ret;
  }

  ret = DER_ItAsn1_WriteInteger(type, &pHeadbuf);
  if (ret != 0){
    return ret;
  }

  switch (type){
    //case ID_MsgKey_Teacher:
    //ret = TeacherEncode_((Teacher *)pStruct, &pTemp);
    //break;

  case ID_MsgKey_Req:
    ret = MsgReqEncode_((MsgKey_Req *)pStruct, &pTemp);
    break;

  case ID_MsgKey_Res:

    break;

  default:
    ret = KeyMng_TypeErr;
    break;
  }

  if (ret != 0){
    DER_ITCAST_FreeQueue(pHeadbuf);
    return ret;
  }

  pHeadbuf->next = pTemp; 

  ret = DER_ItAsn1_WriteSequence(pHeadbuf, &pOutData);
  if (ret != 0){
    DER_ITCAST_FreeQueue(pHeadbuf);
    return ret;
  }
  DER_ITCAST_FreeQueue(pHeadbuf);

  *outData = (unsigned char *)malloc(pOutData->dataLen);
  if (*outData == NULL){
    DER_ITCAST_FreeQueue(pOutData);
    ret = KeyMng_MallocErr;
    return ret;
  }
  memcpy(*outData, pOutData->pData, pOutData->dataLen);
  *outLen = pOutData->dataLen;

  DER_ITCAST_FreeQueue(pOutData);

  return ret;
}
