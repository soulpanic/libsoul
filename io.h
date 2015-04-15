/*
    PROGRAM      : io.o
    SCOPE        : Utiltity
    DESCRIPTION  : IO Function Util 
    NAME         : Soul ( soul@xcurenet.com )
    DATE         : 2012. 09. 28.
    LAST MODIFY  : -
 */

#ifndef __IO_H__
#define __IO_H__

#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h> 
#include <sys/types.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <ctype.h>

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
int ___iGuaranteeRead(int, unsigned char *, ssize_t);

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
int ___iGuaranteeWrite(int, unsigned char *, ssize_t);

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
int ___iGuaranteeClose(int);

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
int ___iGuaranteeAccept(int);

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
int ___iGuarnateeInitNonBlockServer(int *, int, int);

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
int ___iGuaranteeNonBlockConnect(int *, char *, int, int);

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
int ___iStrncmpi(const char *, const char *, unsigned int);

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
char * ___pszStristr(const char *, const char *);

#endif
