
//
//  log.c
//
//  Created by Soul..
//  Copyright (c) 2012 XcureNet. All rights reserved.
//

#include "log.h"

static char * pszLogLv2String(Log * _this, LogLevel _eLoglv)
{
    int i = 0;

    for ( i = 0 ; _this->__arrLogStr [ i ].__eLoglv ; i ++ ) if ( _this->__arrLogStr [ i ].__eLoglv == _eLoglv ) return _this->__arrLogStr [ i ].__pszLog;
    return "UNKWN";
}

static void vChangeLoglevel(Log * _this, LogLevel _eLoglv)
{
    _this->__eCurLoglever = _eLoglv;
}

static bool bLogging(Log * _this, LogLevel _eLoglv, char * _szMsg, ...)
{
    static char szFilePath[LENGTH] = {0, }, szMsg[LENGTH] = {0, }, szBuffer[LENGTH] = {0, };
    int ifdLogFile = -1;
    time_t stTime = 0;
    struct tm * pstTm = NULL;
    va_list stValist;

    if (!(_this->__eCurLoglever & _eLoglv)) return false;

    if (time(&stTime) < 0) return false;

    pstTm = localtime(&stTime);

    if (sprintf(szFilePath, "%s.%05d.%02d%02d%02d", _this->__szFilePath, _this->__iPid, (pstTm->tm_year + 1900) % 100, pstTm->tm_mon + 1, pstTm->tm_mday) < 0) return false;

    va_start(stValist, _szMsg);
    vsprintf(szBuffer, _szMsg, stValist);
    va_end(stValist);

    if (sprintf(szMsg, "%02d.%02d.%02d : %s : %s\n", pstTm->tm_hour, pstTm->tm_min, pstTm->tm_sec, _this->__pfnpszLogLv2String( _this, _eLoglv), szBuffer) < 0) return false;

    if ((ifdLogFile = open(szFilePath, O_CREAT | O_WRONLY | O_APPEND | O_SYNC, 0666)) < 0) return false;

    if (___iGuaranteeWrite(ifdLogFile, (unsigned char *)szMsg, strlen(szMsg)) < 0) return false;

    if (___iGuaranteeClose(ifdLogFile) < 0) return false;

    return true;
}

bool ___bInitLog(Log * _this, LogLevel _eLoglv, const char * _szFilePath, LogStr _parrLogStr[])
{
    size_t siPath = 0;

    if (_this == NULL || _szFilePath == NULL || _parrLogStr == NULL) return false;

    _this->__eCurLoglever = _eLoglv;
    _this->__arrLogStr = _parrLogStr;

    _this->__iPid = (int)getpid();

    bzero(_this->__szFilePath, sizeof(_this->__szFilePath));

    if ((siPath = strlen(_szFilePath)) > LENGTH) return false;

    strncpy(_this->__szFilePath, _szFilePath, siPath);    
    _this->__pfnbLogging = bLogging;
    _this->__pfnvChangeLoglever = vChangeLoglevel;

    _this->__pfnpszLogLv2String = pszLogLv2String;
/*
    _this->__pfnbLogging(_this, 0xFFFF, 
            "INIT Log INSTANCE, LEVEL : %04x, PATH : %s",
            _this->__eCurLoglever, _this->__szFilePath);
*/
    return true;
}

