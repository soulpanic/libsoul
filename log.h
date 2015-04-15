/*
    PROGRAM      : log.o
    SCOPE        : Utiltity
    DESCRIPTION  : Log Control Util 
    NAME         : Soul ( soul@xcurenet.com )
    DATE         : 2012. 09. 28.
    LAST MODIFY  : -
 */

#ifndef __LOG_H__
#define __LOG_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h> 
#include <fcntl.h>

#include "io.h"

/*
    Constant Data
 */
#define LENGTH                                  2048L

/*
    Data Structure
 */

/* LogLevel */
typedef unsigned short LogLevel;

/* LogStr */
typedef struct __log_str {

    LogLevel __eLoglv;
    char * __pszLog;

} LogStr;


/* Log */
typedef struct __log {
   
    /*
       Member Value List
     */
	
    /*  */
    LogLevel                                    __eCurLoglever;
    
    /*  */
    LogStr                                      * __arrLogStr;
	
    /*  */
    char                                        __szFilePath[LENGTH];
    
    /*  */
    int                                         __iPid;
    
    /*
        Member Function List
     */
	
    /*
        FUNCTION     : 
        LEVEL        : 
        PURPOSE      : 
        PARAMETER    : ( DATA TYPE / DESCRIPTION / PARAMETER PASSING )
                 
        RETURN VALUE : 
                       
        ALGORITHM    : -
        CALLED BY    : -
        CALLS        : -
    */
    bool                                        (* __pfnbLogging)(struct __log *, LogLevel , char *, ...);

    /*
        FUNCTION     : 
        LEVEL        : 
        PURPOSE      : 
        PARAMETER    : ( DATA TYPE / DESCRIPTION / PARAMETER PASSING )
                 
        RETURN VALUE : 
                       
        ALGORITHM    : -
        CALLED BY    : -
        CALLS        : -
    */
	void                                        (* __pfnvChangeLoglever)(struct __log *, LogLevel);    

    /*
        FUNCTION     : 
        LEVEL        : 
        PURPOSE      : 
        PARAMETER    : ( DATA TYPE / DESCRIPTION / PARAMETER PASSING )
                 
        RETURN VALUE : 
                       
        ALGORITHM    : -
        CALLED BY    : -
        CALLS        : -
    */
    char *                                      (* __pfnpszLogLv2String)(struct __log *, LogLevel);

} Log;

/*
    Global Function List
 */

/*
    FUNCTION     :  
    LEVEL        : 
    PURPOSE      : 
    PARAMETER    : ( DATA TYPE / DESCRIPTION / PARAMETER PASSING )
               
    RETURN VALUE : 
                
    ALGORITHM    : -
    CALLED BY    : -
    CALLS        : -
 */
bool ___bInitLog(Log *, LogLevel, const char *, LogStr []);

#endif
