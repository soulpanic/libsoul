
//
//  array.c
//
//  Created by Soul..
//  Copyright ( c ) 2012 XcureNet. All rights reserved.
//

#include "array.h"

static bool bDestroyArray ( Array * _this )
{
    if ( _this->__pfnbDestroyObject ) for ( _this->__iCurrent = 0 ; _this->__iCurrent < _this->__iLength ; _this->__iCurrent ++ ) _this->__pfnbDestroyObject ( _this->__pfnpvRead ( _this, _this->__iCurrent ) );
    if ( _this->__pvFront ) free ( _this->__pvFront );
    memset ( _this, 0, sizeof ( *_this ) );

    return true;
}

static void * pvRead ( Array * _this, int _iIndex )
{
    //_this->__iCurrent = _iIndex;
    if ( _iIndex > -1 && _iIndex < _this->__iLength ) return ( unsigned char * )_this->__pvFront + ( _iIndex * _this->__siSize );
    return NULL;
}

static int iStore ( Array * _this, int _iIndex, void * _pvObject )
{
    _this->__iCurrent = _iIndex;
    if ( _iIndex > -1 && _iIndex < _this->__iCapacity ) {
        memcpy (  ( unsigned char * )_this->__pvFront + ( _iIndex * _this->__siSize ), _pvObject, _this->__siSize );
        ( _this->__iLength ) ++;
        return _this->__iCurrent;
    }

    return -1;
}

static int iRightShiftObject ( Array * _this, void* _pvSrc, int _iStart, int _iEnd )
{
    for ( _this->__iCurrent =  _iEnd ; _this->__iCurrent > _iStart - 1 ; _this->__iCurrent -- ) memcpy ( ( unsigned char * )_this->__pvFront + (  ( _this->__iCurrent + 1 ) * _this->__siSize ), ( unsigned char * )_pvSrc + ( _this->__iCurrent * _this->__siSize ), _this->__siSize );

    return _iEnd - _iStart + 1;
}

static int iAppendFromFront ( Array * _this, void * _pvObject )
{
    void * pvBuffer = _this->__pvFront;

    if ( ! ( _this->__iLength < _this->__iCapacity ) ) {
        if ( ! ( _this->__pvFront = calloc (  ( _this->__iCapacity + _this->__iAddSize ), _this->__siSize ) ) ) return -1;
        _this->__iCapacity += _this->__iAddSize;
    }

    _this->__pfniRightShiftObject ( _this, pvBuffer, 0, _this->__iLength -1 );

    if ( pvBuffer != _this->__pvFront ) free ( pvBuffer );

    _this->__pvRear = ( unsigned char * )_this->__pvFront + (  ( _this->__iCapacity - 1 ) * _this->__siSize );

    return _this->__pfniStore ( _this, 0, _pvObject );
}

static int iAppendFromRear ( Array * _this, void * _pvObject )
{
    void * pvBuffer = NULL;

    if ( ! ( _this->__iLength < _this->__iCapacity ) ) {
        if ( ! ( pvBuffer = calloc (  ( _this->__iCapacity + _this->__iAddSize ), _this->__siSize ) ) ) return -1;
        memcpy ( pvBuffer, _this->__pvFront, _this->__iCapacity * _this->__siSize );
        _this->__iCapacity += _this->__iAddSize;
        free ( _this->__pvFront );
        _this->__pvFront = pvBuffer;
        _this->__pvRear = ( unsigned char * )_this->__pvFront + (  ( _this->__iCapacity - 1 ) * _this->__siSize );
    }
    return _this->__pfniStore ( _this, _this->__iLength, _pvObject );
}

static int iInsert ( Array * _this, int _iIndex, void * _pvObject )
{
    void * pvBuffer = NULL;
    //_this->__iCurrent = _iIndex;
    if ( _iIndex == 0 ) return _this->__pfniAppendFromFront ( _this, _pvObject );
    else if ( _iIndex == _this->__iLength ) return _this->__pfniAppendFromRear ( _this, _pvObject );
    else if ( _iIndex > 0 && _iIndex < _this->__iLength ) {
        if ( ! ( _this->__iLength < _this->__iCapacity ) ) {
            if ( ! ( pvBuffer = calloc (  ( _this->__iCapacity + _this->__iAddSize ), _this->__siSize ) ) ) return -1;
            memcpy ( pvBuffer, _this->__pvFront, _this->__iCapacity * _this->__siSize );
            _this->__iCapacity += _this->__iAddSize;
            free ( _this->__pvFront );
            _this->__pvFront = pvBuffer;
        }

        _this->__pfniRightShiftObject ( _this, _this->__pvFront, _iIndex, _this->__iLength - 1 );

        return _this->__pfniStore ( _this, _iIndex, _pvObject );
    } else return -1;
}
static int iLeftShiftObject ( Array * _this, void* _pvSrc, int _iStart, int _iEnd )
{
    for ( _this->__iCurrent =  _iStart ; _this->__iCurrent < _iEnd ; _this->__iCurrent ++ ) memcpy ( ( unsigned char * )_this->__pvFront + (  ( _this->__iCurrent ) * _this->__siSize ), ( unsigned char * )_pvSrc + (  ( _this->__iCurrent + 1 ) * _this->__siSize ), _this->__siSize );

    return _iEnd - _iStart + 1;
}

static int iDeleteFromFront ( Array * _this )
{
    if ( ! ( ( _this->__iCurrent = ( _this->__iLength ? 0 : -1 ) ) < 0 ) )
        if ( _this->__pfnbDestroyObject ) {
            _this->__pfnbDestroyObject ( _this->__pfnpvRead ( _this, _this->__iCurrent ) );
            _this->__pfniLeftShiftObject ( _this, _this->__pvFront, _this->__iCurrent, _this->__iLength );
            ( _this->__iLength ) --;
        }

    return _this->__iCurrent;
}

static int iDeleteFromRear ( Array * _this )
{
    if ( ! ( ( _this->__iCurrent = _this->__iLength - 1 ) < 0 ) ) {
        if ( _this->__pfnbDestroyObject ) _this->__pfnbDestroyObject ( _this->__pfnpvRead ( _this, _this->__iCurrent ) );
        ( _this->__iLength ) --;
    }
    return _this->__iCurrent;
}

static int iDelete ( Array * _this, int _iIndex )
{
    //_this->__iCurrent = _iIndex;
    if ( ! ( _iIndex > -1 && _iIndex < _this->__iLength + 1 ) ) return -1;
    else if ( _iIndex == _this->__iLength ) return _this->__pfniDeleteFromRear ( _this );
    if ( _this->__pfnbDestroyObject ) _this->__pfnbDestroyObject ( _this->__pfnpvRead ( _this, _iIndex ) );
    _this->__pfniLeftShiftObject ( _this, _this->__pvFront, _iIndex, _this->__iLength );
    -- ( _this->__iLength );

    return _iIndex;
}

static int iDeleteAll ( Array * _this ) 
{
    while ( ! ( _this->__pfniDeleteFromRear ( _this ) < 0 ) );
    return _this->__iCurrent;
}

static int iLinearSearchByUnique ( Array * _this, void * _pvKey, int ( * _pfniCompare ) ( void *, void* ) )
{
    for ( _this->__iCurrent = 0 ; _this->__iCurrent < _this->__iLength ; _this->__iCurrent ++ ) if ( _pfniCompare ( _this->__pfnpvRead ( _this, _this->__iCurrent ), _pvKey ) == 0 ) return _this->__iCurrent;

    return -1;
}

static int iSortByBubble ( Array * _this, int ( * _pfniCompare ) ( void *, void * ) )
{
    void * pvTemp = calloc ( 1, _this->__siSize );
    bool bSwitched = true;
    int i = 0;

    for ( i = 0 ; ( i < _this->__iLength - 1 ) && ( bSwitched == true ) ; i ++ ) {
        bSwitched = false;
        for ( _this->__iCurrent = 0 ; _this->__iCurrent < _this->__iLength - i - 1 ; _this->__iCurrent ++ )
            if ( _pfniCompare ( _this->__pfnpvRead ( _this, _this->__iCurrent ), _this->__pfnpvRead ( _this, _this->__iCurrent + 1 ) ) > 0 ) {
                bSwitched = true;
                memcpy ( pvTemp, _this->__pfnpvRead ( _this, _this->__iCurrent ), _this->__siSize );
                memcpy ( _this->__pfnpvRead ( _this, _this->__iCurrent ), _this->__pfnpvRead ( _this, _this->__iCurrent + 1 ), _this->__siSize );
                memcpy ( _this->__pfnpvRead ( _this, _this->__iCurrent + 1 ), pvTemp, _this->__siSize );		
            }
    }

    if ( pvTemp ) free ( pvTemp );

    return _this->__iLength;
}

static bool bModify ( Array * _this, int _iIndex, void * _pvObject )
{
    //_this->__iCurrent = _iIndex;
    if ( _iIndex > -1 && _iIndex < _this->__iLength ) {
        memcpy ( ( unsigned char * )_this->__pvFront + ( _iIndex * _this->__siSize ), _pvObject, _this->__siSize );
        return true;
    }

    return false;
}

bool ___bInitArray ( Array * _this, int _iCapacity, int _iAddSize, size_t _siSize, bool ( * _bfnDestroyObject ) ( void * ) )
{
    _this->__iCapacity = _iCapacity;
    _this->__siSize = _siSize;
    _this->__iAddSize = _iAddSize;

    if ( ! ( _this->__pvFront = calloc ( _this->__iCapacity, _this->__siSize ) ) ) return false;

    _this->__pvRear = ( unsigned char * )_this->__pvFront + (  ( _this->__iCapacity - 1 ) * _this->__siSize );
    _this->__iLength = 0;
    _this->__iCurrent = -1;

    _this->__pfnbDestroyObject = _bfnDestroyObject;
    _this->__pfnbDestroyArray = bDestroyArray;
    _this->__pfnpvRead = pvRead;
    _this->__pfniStore = iStore;
    _this->__pfniAppendFromFront = iAppendFromFront;
    _this->__pfniAppendFromRear = iAppendFromRear;
    _this->__pfniInsert = iInsert;
    _this->__pfniDeleteFromFront = iDeleteFromFront;
    _this->__pfniDeleteFromRear = iDeleteFromRear;
    _this->__pfniDelete = iDelete;
    _this->__pfniDeleteAll = iDeleteAll;
    _this->__pfniLinearSearchByUnique = iLinearSearchByUnique;
    _this->__pfniRightShiftObject = iRightShiftObject;
    _this->__pfniLeftShiftObject = iLeftShiftObject;    
    /*
       _this->__pifnLinearSearchByDuplicate = iLinearSearchByDuplicate;
       _this->__pifnBinarySearchByUnique = iBinarySearchByUnique;
       _this->__pifnBinarySearchByDuplicate = iBinarySearchByDuplicate;
       _this->__pifnSortBySelection = iSortBySelection;
       _this->__pifnSortByInsertion = iSortByInsertion;
       */
    _this->__pfniSortByBubble = iSortByBubble;
    _this->__pfnbModify = bModify;

    return true;
}
