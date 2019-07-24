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

int MsgResEncode_(MsgKey_Res *pRes, ITCAST_ANYBUF **outData){
  int ret = 0;
  ITCAST_ANYBUF* pTmp     = NULL;
  ITCAST_ANYBUF* pHeadBuf = NULL;
  ITCAST_ANYBUF* pTmpBuf  = NULL;
  ITCAST_ANYBUF* pOutData = NULL;
  unsigned char* tmpout   = NULL;
  int tmpoutlen = 0;

  //rv
  ret = DER_ItAsn1_WriteInteger(pRes->rv, &pHeadBuf);
  if (ret != 0){
    return ret;
  }

  pTmp = pHeadBuf;
  //clientId
  ret = EncodeChar(pRes->clientId, strlen(pRes->clientId), &pTmp->next);
  if (ret != 0){
    DER_ITCAST_FreeQueue(pHeadBuf);
    return ret;
  }
  
  pTmp = pTmp->next;
  //serverId
  ret = EncodeChar(pRes->serverId, strlen(pRes->serverId), &pTmp->next);
  if (ret != 0){
    DER_ITCAST_FreeQueue(pHeadBuf);
    return ret;
  }
  
  pTmp = pTmp->next;
  //r2
  ret = EncodeChar(pRes->r2, strlen(pRes->r2), &pTmp->next);
  if (ret != 0){
    DER_ITCAST_FreeQueue(pHeadBuf);
    return ret;
  }
  
  pTmp = pTmp->next;
  //seckyid
  ret = DER_ItAsn1_WriteInteger(pRes->seckeyid, &pTmp->next);
  if (ret != 0){
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

int MsgKey_ReqDecode_(unsigned char* indata, int inLen, MsgKey_Req** pStruct){
  int ret = 0;
  ITCAST_ANYBUF* pTmp     = NULL;
  ITCAST_ANYBUF* pHead    = NULL;
  ITCAST_ANYBUF* pOutData = NULL;
  ITCAST_ANYBUF* inAnyBuf = NULL;

  MsgKey_Req* pTmpStru = NULL;

  ret = DER_ITCAST_String_To_AnyBuf(&inAnyBuf, indata, inLen);
  if (ret != 0){
    return ret;
  }

  ret = DER_ItAsn1_ReadSequence(inAnyBuf, &pHead);
  if (ret != 0){
    DER_ITCAST_FreeQueue(inAnyBuf);
    return ret;
  }
  DER_ITCAST_FreeQueue(inAnyBuf);

  pTmpStru = (MsgKey_Req *)malloc(sizeof(MsgKey_Req));
  if (pTmpStru == NULL){
    ret = 3;
    DER_ITCAST_FreeQueue(pHead);
    return ret;
  }
  memset(pTmpStru, 0, sizeof(MsgKey_Req));

  pTmp = pHead;

  //cmdType
  ret = DER_ItAsn1_ReadInteger(pTmp, (ITCAST_UINT32 *)&(pTmpStru->cmdType));
  if (ret != 0){
    DER_ITCAST_FreeQueue(pHead);
    return ret;
  }
  pTmp = pTmp->next;

  //clientId
  ret = DER_ItAsn1_ReadPrintableString(pTmp, &pOutData);
  if (ret != 0){
    DER_ITCAST_FreeQueue(pHead);
    return ret;
  }
  memcpy(pTmpStru->clientId, pOutData->pData, pOutData->dataLen);
  pTmp = pTmp->next; 
  DER_ITCAST_FreeQueue(pOutData);

  //AuthCode
  ret = DER_ItAsn1_ReadPrintableString(pTmp, &pOutData);
  if (ret != 0){
    DER_ITCAST_FreeQueue(pHead);
    return ret;
  }
  memcpy(pTmpStru->AuthCode, pOutData->pData, pOutData->dataLen);
  pTmp = pTmp->next; 
  DER_ITCAST_FreeQueue(pOutData);

  //serverId
  ret = DER_ItAsn1_ReadPrintableString(pTmp, &pOutData);
  if (ret != 0){
    DER_ITCAST_FreeQueue(pHead);
    return ret;
  }
  memcpy(pTmpStru->serverId, pOutData->pData, pOutData->dataLen);
  pTmp = pTmp->next; 
  DER_ITCAST_FreeQueue(pOutData);

  //r1
  ret = DER_ItAsn1_ReadPrintableString(pTmp, &pOutData);
  if (ret != 0){
    DER_ITCAST_FreeQueue(pHead);
    return ret;
  }
  memcpy(pTmpStru->r1, pOutData->pData, pOutData->dataLen);
  pTmp = pTmp->next; 
  DER_ITCAST_FreeQueue(pOutData);

  *pStruct = pTmpStru;
  return ret;
}

int MsgKey_ResDecode_(unsigned char* indata, int inLen, MsgKey_Res** pStruct){
  int ret = 0;
  ITCAST_ANYBUF* pTmp     = NULL;
  ITCAST_ANYBUF* pHead    = NULL;
  ITCAST_ANYBUF* pOutData = NULL;
  ITCAST_ANYBUF* inAnyBuf = NULL;

  MsgKey_Res* pTmpStru = NULL;

  ret = DER_ITCAST_String_To_AnyBuf(&inAnyBuf, indata, inLen);
  if (ret != 0){
    return ret;
  }

  ret = DER_ItAsn1_ReadSequence(inAnyBuf, &pHead);
  if (ret != 0){
    DER_ITCAST_FreeQueue(inAnyBuf);
    return ret;
  }
  DER_ITCAST_FreeQueue(inAnyBuf);

  pTmpStru = (MsgKey_Res *)malloc(sizeof(MsgKey_Res));
  if (pTmpStru == NULL){
    ret = 3;
    DER_ITCAST_FreeQueue(pHead);
    return ret;
  }
  memset(pTmpStru, 0, sizeof(MsgKey_Res));

  pTmp = pHead;

  //rv
  ret = DER_ItAsn1_ReadInteger(pTmp, (ITCAST_UINT32 *)&(pTmpStru->rv));
  if (ret != 0){
    DER_ITCAST_FreeQueue(pHead);
    return ret;
  }
  pTmp = pTmp->next;

  //clientId
  ret = DER_ItAsn1_ReadPrintableString(pTmp, &pOutData);
  if (ret != 0){
    DER_ITCAST_FreeQueue(pHead);
    return ret;
  }
  memcpy(pTmpStru->clientId, pOutData->pData, pOutData->dataLen);
  pTmp = pTmp->next; 
  DER_ITCAST_FreeQueue(pOutData);

  //serverId
  ret = DER_ItAsn1_ReadPrintableString(pTmp, &pOutData);
  if (ret != 0){
    DER_ITCAST_FreeQueue(pHead);
    return ret;
  }
  memcpy(pTmpStru->serverId, pOutData->pData, pOutData->dataLen);
  pTmp = pTmp->next; 
  DER_ITCAST_FreeQueue(pOutData);

  //r2
  ret = DER_ItAsn1_ReadPrintableString(pTmp, &pOutData);
  if (ret != 0){
    DER_ITCAST_FreeQueue(pHead);
    return ret;
  }
  memcpy(pTmpStru->r2, pOutData->pData, pOutData->dataLen);
  pTmp = pTmp->next;
  DER_ITCAST_FreeQueue(pOutData);
  
  //seckeyid
  ret = DER_ItAsn1_ReadInteger(pTmp, (ITCAST_UINT32 *)&(pTmpStru->seckeyid));
  if (ret != 0){
    DER_ITCAST_FreeQueue(pHead);
    return ret;
  }

  *pStruct = pTmpStru;
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
    ret = MsgResEncode_((MsgKey_Res *)pStruct, &pTemp);
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

int MsgDecode(unsigned char* inData, int inLen, void** pStruct, int* type){

  ITCAST_ANYBUF* pHeadBuf = NULL;
  ITCAST_ANYBUF* inAnyBuf = NULL;
  int ret = 0;
  unsigned long	itype = 0;

  ret = DER_ITCAST_String_To_AnyBuf(&inAnyBuf, inData, inLen);
  if (ret != 0){
    return ret;
  }

  ret = DER_ItAsn1_ReadSequence(inAnyBuf, &pHeadBuf);
  if (ret != 0){
    return ret;
  }
  DER_ITCAST_FreeQueue(inAnyBuf);

  ret = DER_ItAsn1_ReadInteger(pHeadBuf, &itype);
  if (ret != 0){
    DER_ITCAST_FreeQueue(pHeadBuf); 
    return ret;
  }

  switch (itype){
  case ID_MsgKey_Req:
    ret = MsgKey_ReqDecode_(pHeadBuf->next->pData, pHeadBuf->next->dataLen, (MsgKey_Req **)pStruct);
    break;
  case ID_MsgKey_Res:
    ret = MsgKey_ResDecode_(pHeadBuf->next->pData, pHeadBuf->next->dataLen, (MsgKey_Res **)pStruct);
    break;
  default:
    ret = KeyMng_TypeErr;
    break;
  }

  if (ret != 0){
    DER_ITCAST_FreeQueue(pHeadBuf);
    return ret;
  }

  *type = itype;
  DER_ITCAST_FreeQueue(pHeadBuf);

  return ret;
}
