#include "itcast_asn1_der.h"
#include "itcastderlog.h"
#include "keymng_msg.h"
#include <stdio.h>

int MsgEncode(void* pStruct, int type, unsigned char** outData, int* outLen ){

  int ret = -1;
  if (pStruct == NULL && type < 0 || outData == NULL || outLen == NULL){
    ret = KeyMng_ParamErr;
    return ret;
  }

  ITCAST_ANYBUF	*pHeadbuf = NULL, *pTemp = NULL;
  ITCAST_ANYBUF	*pOutData = NULL;

  ret = DER_ItAsn1_WriteInteger(type, &pHeadbuf);
  if (ret != 0){
    return ret;
  }
  
  switch (type){
    //case ID_MsgKey_Teacher:
    //ｱ狡・ﾏﾊｦ
    //Teacher_Encode(&t1, &myOut, &mOutlen);
    //ret = TeacherEncode_((Teacher *)pStruct, &pTemp);
    //break;

  case ID_MsgKey_Req:
    //ret = MsgKey_ReqEncode(ﾃﾜﾔｿﾇ・盪ｹﾌ螢ｬ Anybuf);
    break;

  case ID_MsgKey_Res:
    //ﾃﾜﾔｿﾓｦｴｨﾎﾄ ｱ狡・
    //ret = MsgKey_ResEncode(ﾃﾜﾔｿﾇ・盪ｹﾌ螢ｬ Anybuf);
    break;

  default:
    ret = KeyMng_TypeErr;
    break;
  }

  if (ret != 0){
    DER_ITCAST_FreeQueue(pHeadbuf);
    return ret;
  }
}
