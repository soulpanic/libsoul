/*
    PROGRAM      : datainfo.o
    SCOPE        : Utiltity
    DESCRIPTION  : Data Info Structure 
    NAME         : Soul ( soul@xcurenet.com )
    DATE         : 2012. 09. 28.
    LAST MODIFY  : -
 */

#ifndef __DATA_INFO_H__
#define __DATA_INFO_H__

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <stdbool.h>
typedef enum {
	NOT_USED,
	ALLOC_DATAINFO,
	BUFFER_DATAINFO
} DATAINFO_STATE;

/*
    Data Structure
 */

/* DataInfo */
typedef struct __data_info {

    /*
       Member Value List
     */

    DATAINFO_STATE      __eState;
    /* */
    unsigned char       * __pbyData;
    /* */
    size_t              __siLength;
    /* */
    size_t              __siCapacity;

	bool                ( * __bAllocDataInfo )      ( struct __data_info*, size_t );
	bool                ( * __bUsingBuffer )      ( struct __data_info*, unsigned char *, size_t, size_t );
	bool                ( * __bShiftData )      ( struct __data_info*, size_t );
	bool                ( * __bResetDataInfo )      ( struct __data_info* );
    bool                ( * __bCopyDataInfo )      ( struct __data_info *, struct __data_info * );
    bool                ( * __bAppendData )        ( struct __data_info *, const unsigned char *, size_t );
    bool                ( * __bSetData )       ( struct __data_info *, const unsigned char *, size_t );
    bool                ( * __bInsertData )        ( struct __data_info *, size_t, const unsigned char *, size_t );
    bool                ( * __bReallocDataInfo )   ( struct __data_info *, size_t );
    bool                ( * __bReleaseDataInfo )      ( struct __data_info* );



} DataInfo;

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
bool ___bInitDataInfo( DataInfo *, unsigned char *, size_t, size_t, DATAINFO_STATE);
bool ___bAllocDataInfo( DataInfo *, size_t  );
bool ___bUsingBuffer( DataInfo *, unsigned char *, size_t, size_t );
bool ___bReallocDataInfo( DataInfo *, size_t );

#endif
