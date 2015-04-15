/*
    PROGRAM      : array.o
    SCOPE        : Utiltity
    DESCRIPTION  : Array ( Vector ) Data Structure 
    NAME         : Soul ( soul@xcurenet.com )
    DATE         : 2012. 09. 28.
    LAST MODIFY  : -
 */

#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>

/*
    Data Structure
 */

/* Array */
typedef struct __array {

    /*
       Member Value List
     */

    /* Pointer Array Front */
    void *                                          __pvFront;
    /* Pointer Array Rear */
    void *                                          __pvRear;
    /* Working Index */
    int                                             __iCurrent;
    /* Object Count */
    int                                             __iLength;
    /* Array Space */
    int                                             __iCapacity;
    /* Realloc Array Space Size */
    int                                             __iAddSize;
    /* Size of Object in Memory */
    size_t                                          __siSize;

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
    bool                                            ( * __pfnbDestroyObject ) ( void * );

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
    bool                                            ( * __pfnbDestroyArray ) ( struct __array * );

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
    void *                                          ( * __pfnpvRead ) ( struct __array *, int );

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
    int                                             ( * __pfniStore ) ( struct __array *, int, void * );

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
    int                                             ( * __pfniAppendFromFront ) ( struct __array *, void * );

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
    int                                             ( * __pfniAppendFromRear ) ( struct __array *, void * );

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
    int                                             ( * __pfniInsert ) ( struct __array *, int, void * );

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
    int                                             ( * __pfniDeleteFromFront ) ( struct __array * );

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
    int                                             ( * __pfniDeleteFromRear ) ( struct __array * );

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
    int                                             ( * __pfniDelete ) ( struct __array *, int );

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
    int                                             ( * __pfniDeleteAll ) ( struct __array * );

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
    int                                             ( * __pfniLinearSearchByUnique ) ( struct __array *, void *, int ( * ) ( void *, void* ) );

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
    int                                             ( * __pfniSortByBubble ) ( struct __array *, int ( * ) ( void *, void * ) );

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
    bool                                            ( * __pfnbModify ) ( struct __array *, int, void * );

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
    int                                             ( * __pfniRightShiftObject ) ( struct __array *, void *, int, int );

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
    int                                             ( * __pfniLeftShiftObject ) ( struct __array *, void *, int, int );


/*
    int                                             ( * __pfniLinearSearchByDuplicate ) ( struct __array *, void *, int *, int **, int ( * ) ( void *, void * ) );
    int                                             ( * __pifnBinarySearchByUnique ) ( struct __array *, void *, int ( * ) ( void *, void* ) );
    int                                             ( * __pifnBinarySearchByDuplicate ) ( struct __array *, void *, int *, int **, int ( * ) ( void *, void * ) );
    int                                             ( * __pifnSortBySelection ) ( struct __array *, int ( * ) ( void *, void * ) );
    int                                             ( * __pifnSortByInsertion ) ( struct __array *, int ( * ) ( void *, void * ) );
    int                                             ( * __pifnSortByHeap ) ( struct __array *, int ( * ) ( void *, void * ) );
    int                                             ( * __pifnSortByMerge ) ( struct __array *, int ( * ) ( void *, void * ) );
    int                                             ( * __pifnSortByQuick ) ( struct __array *, int ( * ) ( void *, void * ) );
    int                                             ( * __pifnSortByShell ) ( struct __array *, int ( * ) ( void *, void * ) );
*/

} Array;

/*
    Global Function List
 */


/*
    FUNCTION     : ___bInitArray 
    LEVEL        : 0
    PURPOSE      : Initialize Array Structure
    PARAMETER    : ( DATA TYPE / DESCRIPTION / PARAMETER PASSING )
               
                   Array * / Array Object / Call by Pointer
                   int / Array Capacity / Call by Value
                   int / Array Realloc Size / Call by Value
                   size_t / Entry Size / Call by Value
                   bool (*) ( void *, void * ) / Entry Release Func Pointer / Call by Pointer
                 
    RETURN VALUE : 
                
                   true      - Success
                   false     - Failed
                       
    ALGORITHM    : -
    CALLED BY    : -
    CALLS        : -
 */
bool                                            ___bInitArray ( Array *, int, int, size_t, bool ( * ) ( void * ) );

#endif
