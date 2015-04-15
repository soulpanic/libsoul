//
//  hash.h
//  libsoul
//
//  Created by Soul on 13. 7. 27..
//  Copyright (c) 2013³â Soul. All rights reserved.
//

#ifndef __HASH_H__
#define __HASH_H__

#include "list.h"

typedef struct __hash {
    /*
       Member Value List
     */
    
    /* */
    size_t __siSlot;
	size_t __siCount;
    /* */
    List * __plstTable;
    /* */
    size_t ( * __pfnsiHashFunc ) ( void * );

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
    int ( * __pfniGetSlot )( struct __hash *, void * );

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
    int ( * __pfniKeyCompare ) ( void *, void *);

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
    Node * ( * __pfnpndGet ) ( struct __hash *, void * );

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
    Node * ( * __pfnpndPut ) ( struct __hash *, void *, void * );

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
    Node * ( * __pfnpndRemove ) ( struct __hash *, void *, Node * );

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
    Node * ( * __pfnpndSearchByUnique ) ( struct __hash *, void *, int ( * ) ( void *, void * ) );

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
    int  ( * __pfniSearchByDuplicate ) ( struct __hash *, void *, int **, Node ****, int ( * ) ( void *, void * ) );

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
    int ( * __pfniRelease ) ( struct __hash * );
    
} Hash;

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
bool ___bInitHash ( Hash *, size_t, size_t, size_t ( * ) ( void * ), int ( * ) ( void *, void * ), bool ( * ) ( Node * ) );

#endif
