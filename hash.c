//
//  hash.c
//  libsoul
//
//  Created by Soul on 13. 7. 1..
//  Copyright (c) 2013??Soul. All rights reserved.
//

#include "hash.h"

static int GetSlot( Hash * _phsHash, void * _pvKey )
{
	return (int)(_phsHash->__pfnsiHashFunc ( _pvKey ) % _phsHash->__siSlot);
}

static Node * Get ( Hash * _phsHash, void * _pvKey)
{
	int iIdx = _phsHash->__pfniGetSlot ( _phsHash, _pvKey );

	return _phsHash->__plstTable[ iIdx ].__pfnpndLinearSearchByUnique ( _phsHash->__plstTable + iIdx, _pvKey, _phsHash->__pfniKeyCompare );
}

static Node * Put ( Hash * _phsHash, void * _pvKey, void * _pvObject )
{
	int iIdx = _phsHash->__pfniGetSlot ( _phsHash, _pvKey );
	_phsHash->__siCount ++;
	return _phsHash->__plstTable[ iIdx ].__pfnpndAppendFromHead ( _phsHash->__plstTable + iIdx, _pvObject );
}

static Node * Remove ( Hash * _phsHash, void * _pvKey, Node * _pndNode  )
{
	int iIdx = _phsHash->__pfniGetSlot ( _phsHash, _pvKey );
	_phsHash->__siCount --;
	return _phsHash->__plstTable[ iIdx ].__pfnpndDelete ( _phsHash->__plstTable + iIdx, _pndNode );
}

static Node * SearchByUnique ( Hash * _phsHash, void * _pvKey, int ( * _pfniCompare ) ( void *, void * ) )
{
	int iIdx = _phsHash->__pfniGetSlot ( _phsHash, _pvKey );

	return _phsHash->__plstTable[ iIdx ].__pfnpndLinearSearchByUnique ( _phsHash->__plstTable + iIdx, _pvKey, _pfniCompare);
}

static int SearchByDuplicate ( Hash * _phsHash, void * _pvKey, int ** _piCount, Node **** _ppndNodeSet, int ( * _pfniCompare ) ( void *, void * ) )
{
	int i = 0, iSum = 0;
	* _piCount = ( int * ) calloc( _phsHash->__siSlot, sizeof ( int ) );
	* _ppndNodeSet = ( Node *** ) calloc( _phsHash->__siSlot, sizeof ( Node ** ) );

	for ( i = 0 ; i < ( int ) _phsHash->__siSlot ; i ++ ) {
		if ( _phsHash->__plstTable[i].__siCount > 0 ) {
			( * _ppndNodeSet )[ i ] = ( Node ** ) calloc( _phsHash->__plstTable[i].__siCount, sizeof ( Node * ) );
			iSum += _phsHash->__plstTable[i].__pfniLinearSearchByDuplicate ( _phsHash->__plstTable + i, _pvKey, ( * _piCount ) + i, ( * _ppndNodeSet )[ i ] , _pfniCompare );
		}
	}
	return iSum;
}

static int Release ( Hash * _phsHash )
{
	int i = 0, iSum = 0;

	for ( i = 0 ; i < ( int )_phsHash->__siSlot ; i ++ ) iSum += _phsHash->__plstTable[i].__pfniDeleteAll( _phsHash->__plstTable + i );

	return iSum;
}

bool ___bInitHash ( Hash * _phsHash, size_t _siSlots, size_t _siObjectSize, size_t ( * pfnsiHashFunc ) ( void * ) , int ( * _pfniCompare ) ( void *, void * ), bool ( * _pfnbDestroyNode ) ( Node * ) )
{
	int i = 0;
	_phsHash->__siSlot = _siSlots;
	_phsHash->__plstTable = ( List * ) calloc( _phsHash->__siSlot, sizeof ( List ) );
	for ( i = 0 ; i < ( int ) _phsHash->__siSlot ; i ++ ) if ( ! ___bInitList( _phsHash->__plstTable + i, _siObjectSize, _pfnbDestroyNode ) ) return false;
	_phsHash->__siCount = 0;
	_phsHash->__pfnsiHashFunc = pfnsiHashFunc;
	_phsHash->__pfniKeyCompare = _pfniCompare;
	_phsHash->__pfniGetSlot = GetSlot;
	_phsHash->__pfnpndGet = Get;
	_phsHash->__pfnpndPut = Put;
	_phsHash->__pfnpndRemove = Remove;
	_phsHash->__pfnpndSearchByUnique = SearchByUnique;
	_phsHash->__pfniSearchByDuplicate = SearchByDuplicate;
	_phsHash->__pfniRelease = Release;

	return true;
}
