/*
    PROGRAM      : list.o
    SCOPE        : Utiltity
    DESCRIPTION  : Linked List Data Structrue 
    NAME         : Soul ( soul@xcurenet.com )
    DATE         : 2012. 09. 28.
    LAST MODIFY  : -
 */

#ifndef __NODE_H__
#define __NODE_H__

/*
    Data Structure
 */

/* Node  */
typedef struct __node{

    /*
       Member Value List
     */
	
    /*  */
    struct __node * __pndPrev;
	
    /*  */
    struct __node * __pndNext;

} Node;

#endif

