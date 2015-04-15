
//
//  datainfo.c
//
//  Created by Soul..
//  Copyright (c) 2012 XcureNet. All rights reserved.
//

#include "datainfo.h"

static bool bAppendData( DataInfo * _pDatainfo, const unsigned char * _pbyData, size_t _siLength ) {
	if ( _pDatainfo->__siCapacity - _pDatainfo->__siLength < _siLength ) {
		if ( _pDatainfo->__eState == ALLOC_DATAINFO ) {
			if ( ! _pDatainfo->__bReallocDataInfo ( _pDatainfo, _siLength + _pDatainfo->__siLength ) ) return false;
		} else if ( _pDatainfo->__eState == NOT_USED ) _pDatainfo->__bAllocDataInfo ( _pDatainfo, _siLength );
		else return false;
	}
	memcpy ( _pDatainfo->__pbyData + _pDatainfo->__siLength, _pbyData, _siLength );
	_pDatainfo->__siLength += _siLength;

	return true;
}

static bool bInsertData( DataInfo * _pDatainfo, size_t _siOffset, const unsigned char * _pbyData, size_t _siLength ) {
	if ( _pDatainfo->__siCapacity < _siOffset + _siLength) {
		if ( _pDatainfo->__eState == ALLOC_DATAINFO ) {
			if ( ! _pDatainfo->__bReallocDataInfo ( _pDatainfo, _siOffset + _siLength ) ) return false;
		} else return false;
	}
	memcpy ( _pDatainfo->__pbyData + _siOffset, _pbyData, _siLength );
	if ( _pDatainfo->__siLength < _siOffset + _siLength ) {
		_pDatainfo->__siLength = _siOffset + _siLength;
	}

	return true;
}

static bool bSetData( DataInfo * _pDatainfo, const unsigned char * _pbyData, size_t _siLength ) {
	if ( _siLength <= _pDatainfo->__siCapacity ) {
		memcpy ( _pDatainfo->__pbyData, _pbyData, ( _pDatainfo->__siLength = _siLength ) );
		return true;
	}

	return false;
}

static bool bCopyDataInfo( DataInfo * _pSrcDatainfo, DataInfo * _pDstDatainfo ) {
	_pSrcDatainfo->__bResetDataInfo ( _pSrcDatainfo );
	switch ( _pSrcDatainfo->__eState ) {
		case NOT_USED:
		_pSrcDatainfo->__bAllocDataInfo( _pSrcDatainfo, _pDstDatainfo->__siCapacity );
		_pSrcDatainfo->__bSetData( _pSrcDatainfo, _pDstDatainfo->__pbyData, _pDstDatainfo->__siLength );
		break;
		case ALLOC_DATAINFO :
		if ( _pSrcDatainfo->__siCapacity < _pDstDatainfo->__siCapacity )
			_pSrcDatainfo->__bReallocDataInfo ( _pSrcDatainfo, _pDstDatainfo->__siCapacity );
		_pSrcDatainfo->__bSetData( _pSrcDatainfo, _pDstDatainfo->__pbyData, _pDstDatainfo->__siLength );
		break;
		case BUFFER_DATAINFO :
		if ( _pSrcDatainfo->__siCapacity < _pDstDatainfo->__siCapacity ) {
			_pSrcDatainfo->__bReleaseDataInfo( _pSrcDatainfo );
			_pSrcDatainfo->__bAllocDataInfo( _pSrcDatainfo, _pDstDatainfo->__siCapacity );
		}
		_pSrcDatainfo->__bSetData( _pSrcDatainfo, _pDstDatainfo->__pbyData, _pDstDatainfo->__siLength );
		break;
	}
	return true;
}

static bool bShiftData( DataInfo * _pDatainfo, size_t _siOffset ) {
	if ( _siOffset < _pDatainfo->__siLength ) {
		if ( ! memmove ( _pDatainfo->__pbyData, _pDatainfo->__pbyData + _siOffset, _pDatainfo->__siLength - _siOffset) ) return false;
		_pDatainfo->__siLength -= _siOffset;
                //			memset ( this->__pbyData + this->__siLength, 0, this->__siCapacity - this->__siLength );
		return true;
	}

	return false;
}


static bool bResetDataInfo( DataInfo * _pDatainfo ) {
            //if ( memset ( this->__pbyData, 0, this->__siCapacity ) ) {
	_pDatainfo->__siLength = 0;
	return true;
            //}

            //return false;
}

static bool bReleaseDataInfo( DataInfo * _pDatainfo ) {
	if ( _pDatainfo->__eState == ALLOC_DATAINFO && _pDatainfo->__pbyData ) free ( _pDatainfo->__pbyData );
	_pDatainfo->__eState = NOT_USED;
	_pDatainfo->__pbyData = NULL;
	_pDatainfo->__siCapacity = _pDatainfo->__siLength = 0;

	return true;
}

static void ___vLinkFunction( DataInfo * _pDatainfo ) {
	_pDatainfo->__bAllocDataInfo = ___bAllocDataInfo;
	_pDatainfo->__bUsingBuffer = ___bUsingBuffer;
	_pDatainfo->__bReallocDataInfo = ___bReallocDataInfo;
	_pDatainfo->__bAppendData = bAppendData;
	_pDatainfo->__bInsertData = bInsertData;
	_pDatainfo->__bSetData = bSetData;
	_pDatainfo->__bCopyDataInfo = bCopyDataInfo;
	_pDatainfo->__bShiftData = bShiftData;
	_pDatainfo->__bResetDataInfo = bResetDataInfo;
	_pDatainfo->__bReleaseDataInfo = bReleaseDataInfo;
}

bool ___bInitDataInfo( DataInfo * _pDatainfo, unsigned char * _pbyData, size_t _siLength, size_t _siCapacity, DATAINFO_STATE _eState ) {
	_pDatainfo->__eState = NOT_USED;

	if ( _eState == ALLOC_DATAINFO ) {
		return ___bAllocDataInfo( _pDatainfo, _siCapacity );
	} else if ( _pDatainfo->__eState == BUFFER_DATAINFO ) {
		return ___bUsingBuffer( _pDatainfo, _pbyData, _siLength, _siCapacity );
	}
	return true;
}

bool ___bAllocDataInfo( DataInfo * _pDatainfo, size_t _siCapacity ) {
	if ( _pDatainfo->__eState == NOT_USED ) {
		if ( ! ( _pDatainfo->__pbyData = ( unsigned char * ) calloc ( 1, ( _pDatainfo->__siCapacity = _siCapacity ) ) ) ) return false;
		_pDatainfo->__eState = ALLOC_DATAINFO;
		_pDatainfo->__siCapacity = _siCapacity;
		_pDatainfo->__siLength = 0;
		___vLinkFunction ( _pDatainfo );
		return true;
	}

	return false;
}

bool ___bUsingBuffer( DataInfo * _pDatainfo, unsigned char * _pbyBuffer, size_t _siLength, size_t _siCapacity ) { 
	if ( _pDatainfo->__eState == NOT_USED && _pbyBuffer ) {
		_pDatainfo->__eState = BUFFER_DATAINFO;
		_pDatainfo->__pbyData = _pbyBuffer;
		_pDatainfo->__siCapacity = _siCapacity;
		_pDatainfo->__siLength = _siLength;
		___vLinkFunction ( _pDatainfo );
		return true;
	}

	return false;
}

bool ___bReallocDataInfo( DataInfo * _pDatainfo, size_t _siCapacity ) {
	if ( _pDatainfo->__eState == ALLOC_DATAINFO && _pDatainfo->__siCapacity < _siCapacity ) {
		if ( ! ( _pDatainfo->__pbyData = ( unsigned char * ) realloc ( _pDatainfo->__pbyData, ( _pDatainfo->__siCapacity = _siCapacity ) ) ) ) return false;
		return true;
	}

	return false;
}
