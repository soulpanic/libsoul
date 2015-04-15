
//
//  io.c
//
//  Created by Soul..
//  Copyright (c) 2012 XcureNet. All rights reserved.
//

#include "io.h"

int ___iGuaranteeWrite(int _fdFile, unsigned char * _abyData, ssize_t _siLen)
{
    ssize_t siRet = -1;
    while(_siLen != 0 && (siRet = write(_fdFile, _abyData, _siLen)) != 0){
        if(siRet == -1){
            if (errno == EINTR) continue;
            //perror("write");
            return -1;
        }
        _siLen -= siRet;
        _abyData += siRet;
    }

    return true;
}

int ___iGuaranteeRead(int _fdFile, unsigned char * _abyData, ssize_t _siLen)
{
    ssize_t siRet = 0;

    if (_siLen == 0) return true;

    while( _siLen != 0 && (siRet = read(_fdFile, _abyData, _siLen)) != 0){
        if(siRet == -1){
            if(errno == EINTR || errno == EAGAIN) continue;
            //perror("read");
            return -1;
        }
        _siLen -= siRet;
        _abyData += siRet;
    }

    return siRet ? true : -1;
}


int ___iGuaranteeClose(int _fdFile)
{
    int iFopts = 0;

    if (fcntl(_fdFile, F_GETFL, &iFopts) < 0) return true;

    while(close(_fdFile) == -1) 
        if(errno == EINTR) continue;
        else return -1;

    return true;
}

int ___iGuaranteeAccept(int _sdSoc)
{
    int sdSoc = -1;
    struct sockaddr_in stAddr;
    socklen_t siStSockSize = sizeof(struct sockaddr);;

    bzero(&stAddr, sizeof(struct sockaddr_in));

    while ((sdSoc = accept(_sdSoc,(struct sockaddr *)&stAddr, &siStSockSize)) == -1) {
        if (errno == EAGAIN) continue;
        return -1;
    }

    return sdSoc;
}

int ___iGuarnateeInitNonBlockServer(int * _psdSoc, int _iPort, int _iBacklog)
{
    int iOrgSocFlag = 0;
    struct sockaddr_in stAddr;

    bzero(&stAddr, sizeof(struct sockaddr_in));

    if ((*_psdSoc = socket(AF_INET, SOCK_STREAM, 0)) < 0) return -1;

    if ((iOrgSocFlag = fcntl(*_psdSoc, F_GETFL, 0)) < 0) return -1;

    if (fcntl(*_psdSoc, F_SETFL, iOrgSocFlag | O_NONBLOCK)) return -1;

    stAddr.sin_family = AF_INET;
    stAddr.sin_port = htons(_iPort);
    stAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(*_psdSoc, (struct sockaddr *)&stAddr, sizeof(struct sockaddr)) < 0) return -1;

    if (listen(*_psdSoc, _iBacklog) < 0) return -1;

    return *_psdSoc;
}


int ___iGuaranteeNonBlockConnect(int * _psdSoc, char * _pszIp, int _iPort, int _iTimeout)
{
    int iOrgSocFlag = 0, iResult = -1;
    struct sockaddr_in stAddr;

    socklen_t siStSockSize = sizeof(struct sockaddr);

    fd_set fdsRead, fdsWrite;
    struct timeval stTval; 

    if ((*_psdSoc = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) return -1;

    bzero(&stAddr, sizeof(struct sockaddr_in));
    bzero(&stTval, sizeof(struct timeval));

    stAddr.sin_family = AF_INET;  
    stAddr.sin_port = htons(_iPort);
    stAddr.sin_addr.s_addr = inet_addr(_pszIp);

    if ((iOrgSocFlag = fcntl(*_psdSoc, F_GETFL, 0)) < 0) return -1;

    if (fcntl(*_psdSoc, F_SETFL, iOrgSocFlag | O_NONBLOCK)) return -1;

    if ((iResult = connect(*_psdSoc, (struct sockaddr *)&stAddr, siStSockSize)) < 0) if (errno != EINPROGRESS) return -1;

    if (iResult == 0) return *_psdSoc;

    FD_ZERO(&fdsRead);
    FD_SET(*_psdSoc, &fdsRead);

    fdsWrite = fdsRead;

    stTval.tv_sec = _iTimeout;
    stTval.tv_usec = 0;

    if ((iResult = select(*_psdSoc + 1, &fdsRead, &fdsWrite, NULL, &stTval)) == 0) return -1;

    if (FD_ISSET(*_psdSoc, &fdsRead) || FD_ISSET(*_psdSoc, &fdsWrite)){
        siStSockSize = sizeof(iResult);
        if (getsockopt(*_psdSoc, SOL_SOCKET, SO_ERROR, &iResult, &siStSockSize) < 0) return -1;
    }

    return *_psdSoc;
}

int ___iStrncmpi(const char * _pcszSrc, const char * _pcszDst, unsigned int _uLength)
{
    char chTmp1 = 0, chTmp2 = 0;
    while ((_uLength > 0) && (chTmp1 = *_pcszSrc) | (chTmp2 = *_pcszDst)) {
        if (!chTmp1 || !chTmp2 || (islower(chTmp1) ? toupper(chTmp1) : chTmp1) != (islower(chTmp2) ? toupper(chTmp2) : chTmp2)) return (chTmp1 - chTmp2);
        _pcszSrc ++;
        _pcszDst ++;
        _uLength --;
    }
    return 0;
}

char * ___pszStristr(const char * _pcszStr, const char * _pcszSerach)
{
    const char * pcszS, * pcszSub;

    for ( ; *_pcszStr ; _pcszStr ++) {
        for (pcszSub = _pcszSerach, pcszS = _pcszStr ; * pcszSub && * pcszS ; pcszSub ++, pcszS ++) if (tolower(*pcszS) != tolower(*pcszSub)) break;
        if (*pcszSub == 0) return (char *)_pcszStr;
    }

    return NULL;
}

