/*
    PROGRAM      : list.o
    SCOPE        : Utiltity
    DESCRIPTION  : Linked List Data Structrue 
    NAME         : Soul ( soul@xcurenet.com )
    DATE         : 2012. 09. 28.
    LAST MODIFY  : -
 */

#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>
#include <memory.h>
#include "node.h"
#include "stdbool.h"
/*
    Data Structure
 */

/* List */
typedef struct __list {
	
    /*
       Member Value List
     */
	
    /* */
    Node *                                          __pndHead;
    
    /* */
	Node *                                          __pndTail;
    
    /* */
	size_t                                          __siCount;
    
    /* */
	Node *                                          __pndCurrent;
	
    /* */
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
    bool                                            (* __pfnbDestroyNode)(Node *);
    
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
    Node *                                          (* __pfnpndGetNode)(struct __list *, void *);
    
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
	Node *                                          (* __pfnpndRead)(struct __list *, size_t);
    
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
	Node *                                          (* __pfnpndAppendFromHead)(struct __list *, void *);
    
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
	Node *                                          (* __pfnpndAppendFromTail)(struct __list *, void *);
    
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
	Node *                                          (* __pfnpndInsertBefore)(struct __list *, Node *, void *);
    
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
	Node *                                          (* __pfnpndInsertAfter)(struct __list *, Node *, void *);
    
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
	Node *                                          (* __pfnpndDeleteFromHead)(struct __list *);
    
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
	Node *                                          (* __pfnpndDeleteFromTail)(struct __list *);
    
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
	Node *                                          (* __pfnpndDelete)(struct __list *, Node *);
    
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
	int                                             (* __pfniDeleteAll)(struct __list *);
    
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
	Node *                                          (* __ppndfnModify)(struct __list *, Node *, void *);
    
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
	Node *                                          (* __pfnpndLinearSearchByUnique)(struct __list *, void *, int (*)(void *, void *));
    
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
	int                                             (* __pfniLinearSearchByDuplicate)(struct __list *, void *, int *, Node **, int (*)(void *, void *));
    
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
	int                                             (* __pfniSortByInsertion)(struct __list *, int (*)(void *, void *));

} List;

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
bool ___bInitList(List *, size_t, bool (*)(Node *));

#endif
