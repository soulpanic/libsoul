
//
//  list.c
//
//  Created by Soul..
//  Copyright (c) 2012 XcureNet. All rights reserved.
//

#include "list.h"


static Node * pndGetNode(List * _this, void * _pvObject)
{
    Node * pndNode = (Node *)malloc(sizeof(Node) + _this->__siSize);
    if( ! pndNode ) return NULL;

    pndNode->__pndNext = pndNode;
    pndNode->__pndPrev = pndNode;
    memcpy(pndNode + 1, _pvObject, _this->__siSize);

    return pndNode;
}

static Node * pndRead(List * _this, size_t _siIndex)
{
    size_t siIndex = 0;

    if (!(_siIndex < _this->__siCount)) return NULL;

    for (_this->__pndCurrent = _this->__pndHead, siIndex = 0 ; _this->__pndCurrent != NULL && siIndex < _siIndex ; _this->__pndCurrent = _this->__pndCurrent->__pndNext, siIndex ++);

    return _this->__pndCurrent;
}

static Node * pndAppendFromHead(List * _this, void * _pvObject)
{
    if (!(_this->__pndCurrent = _this->__pfnpndGetNode(_this, _pvObject))) return NULL;

    if (_this->__pndHead) {
        _this->__pndCurrent->__pndNext = _this->__pndHead;
        _this->__pndHead = _this->__pndCurrent;
    } else _this->__pndTail = _this->__pndCurrent;

    _this->__pndCurrent->__pndNext->__pndPrev = _this->__pndCurrent;
    _this->__pndHead = _this->__pndCurrent;
    (_this->__siCount) ++;

    return _this->__pndCurrent;
}

static Node * pndAppendFromTail(List * _this, void * _pvObject)
{
    if (!(_this->__pndCurrent = _this->__pfnpndGetNode(_this, _pvObject))) return NULL;

    if (_this->__pndTail) {
        _this->__pndCurrent->__pndPrev = _this->__pndTail;
        _this->__pndTail = _this->__pndCurrent;
    } else _this->__pndHead = _this->__pndCurrent;

    _this->__pndCurrent->__pndPrev->__pndNext = _this->__pndCurrent;
    _this->__pndTail = _this->__pndCurrent;
    (_this->__siCount) ++;

    return _this->__pndCurrent;
}

static Node * pndInsertBefore(List * _this, Node * _pndNode, void * _pvObject)
{
    if (_this->__pndHead == _pndNode) return _this->__pfnpndAppendFromHead(_this, _pvObject);
    else {
        if (!(_this->__pndCurrent = _this->__pfnpndGetNode(_this, _pvObject))) return NULL;

        _this->__pndCurrent->__pndNext = _pndNode;
        _this->__pndCurrent->__pndPrev = _this->__pndCurrent->__pndNext->__pndPrev;
        _this->__pndCurrent->__pndNext->__pndPrev = _this->__pndCurrent;
        _this->__pndCurrent->__pndPrev->__pndNext = _this->__pndCurrent;
        (_this->__siCount) ++;

        return _this->__pndCurrent;
    }
}

static Node * pndInsertAfter(List * _this, Node * _pndNode, void * _pvObject)
{
    if (_this->__pndTail == _pndNode) return _this->__pfnpndAppendFromTail(_this, _pvObject);
    else {
        if (!(_this->__pndCurrent = _this->__pfnpndGetNode(_this, _pvObject))) return NULL;

        _this->__pndCurrent->__pndPrev = _pndNode;
        _this->__pndCurrent->__pndNext = _this->__pndCurrent->__pndPrev->__pndNext;
        _this->__pndCurrent->__pndPrev->__pndNext = _this->__pndCurrent;
        _this->__pndCurrent->__pndNext->__pndPrev = _this->__pndCurrent;
        (_this->__siCount) ++;

        return _this->__pndCurrent;
    }
}

static Node * pndDeleteFromHead(List * _this)
{
    if (!_this->__pndHead) return NULL;

    _this->__pndCurrent = _this->__pndHead;

    if (_this->__pndHead == _this->__pndTail) _this->__pndTail = _this->__pndHead = NULL;
    else {
        _this->__pndHead = _this->__pndHead->__pndNext;
        _this->__pndHead->__pndPrev = _this->__pndHead;
    }
    if (_this->__pfnbDestroyNode != NULL) _this->__pfnbDestroyNode(_this->__pndCurrent);
    free(_this->__pndCurrent);

    (_this->__siCount) --;

    return _this->__pndCurrent;
}

static Node * pndDeleteFromTail(List * _this)
{
    if (!_this->__pndTail) return NULL;

    _this->__pndCurrent = _this->__pndTail;

    if (_this->__pndHead == _this->__pndTail) _this->__pndTail = _this->__pndHead = NULL;
    else { 
        _this->__pndTail = _this->__pndTail->__pndPrev;
        _this->__pndTail->__pndNext = _this->__pndTail;
    }
    
    if (_this->__pfnbDestroyNode != NULL) _this->__pfnbDestroyNode(_this->__pndCurrent);
    free(_this->__pndCurrent);

    (_this->__siCount) --;

    return _this->__pndCurrent;
}

static Node * pndDelete(List * _this, Node * _pndNode)
{
    _this->__pndCurrent = _pndNode;

    if (_this->__pndCurrent == _this->__pndHead) return _this->__pfnpndDeleteFromHead(_this);
    else if (_this->__pndCurrent == _this->__pndTail) return _this->__pfnpndDeleteFromTail(_this);
    else {
        _this->__pndCurrent->__pndNext->__pndPrev = _this->__pndCurrent->__pndPrev;
        _this->__pndCurrent->__pndPrev->__pndNext = _this->__pndCurrent->__pndNext;
    }

    if (_this->__pfnbDestroyNode != NULL) _this->__pfnbDestroyNode(_this->__pndCurrent);
    free(_this->__pndCurrent);

    (_this->__siCount) --;

    return _this->__pndCurrent;
}

static int iDeleteAll(List * _this)
{
    int iResult = 0, iOrigin = (int)_this->__siCount;
    while(_this->__pfnpndDeleteFromHead(_this)) iResult ++;

    return (iResult == iOrigin) ? iResult : -1;
}

static Node * pndModify(List * _this, Node * _pndNode, void * _pvObject)
{
    _this->__pndCurrent = _pndNode;
    memcpy(_this->__pndCurrent + 1, _pvObject, _this->__siSize);

    return _this->__pndCurrent;
}

static Node * pndLinearSearchByUnique(List * _this, void * _pvKey, int (* _pifnCompare)(void *, void *))
{
    size_t siIndex = 0;

    for (siIndex = 0 , _this->__pndCurrent = _this->__pndHead ; siIndex < _this->__siCount ; siIndex ++, _this->__pndCurrent = _this->__pndCurrent->__pndNext) if (_pifnCompare(_this->__pndCurrent + 1, _pvKey) == 0) return _this->__pndCurrent;

    return NULL;
}

static int iLinearSearchByDuplicate(List * _this, void * _pvKey, int * _piCount, Node ** _pndaResultSET, int (* _pifnCompare)(void *, void *))
{
    size_t siIndex = 0, siResultCount = 0;

    if (*_piCount < 0) return -1;

    for (siIndex = 0 , _this->__pndCurrent = _this->__pndHead ; siIndex < _this->__siCount && siResultCount < *((unsigned int *)_piCount) ; siIndex ++, _this->__pndCurrent = _this->__pndCurrent->__pndNext) if (_pifnCompare(_this->__pndCurrent + 1, _pvKey) == 0) _pndaResultSET[siResultCount++] = _this->__pndCurrent;

    return (*_piCount = (int)siResultCount);
}

static int iSortByInsertion(List * _this, int (* _pifnCompare)(void *, void *))
{
    Node * pndInsert = NULL, * pndNextInsert = NULL;
    size_t siIndex = 1;

    pndInsert = _this->__pndHead->__pndNext;

    while (siIndex < _this->__siCount) {
        pndNextInsert = pndInsert->__pndNext;
        _this->__pndCurrent = _this->__pndHead;

        while (_this->__pndCurrent != pndInsert && _pifnCompare(_this->__pndCurrent + 1, pndInsert + 1) < 0) _this->__pndCurrent = _this->__pndCurrent->__pndNext;

        if (_this->__pndCurrent != pndInsert) {
            if (pndInsert != _this->__pndTail) {
                pndInsert->__pndPrev->__pndNext = pndInsert->__pndNext;
                pndInsert->__pndNext->__pndPrev = pndInsert->__pndPrev;
            } else {
                pndInsert->__pndPrev->__pndNext = pndInsert->__pndPrev;
                _this->__pndTail = pndInsert->__pndPrev;
            }

            if (_this->__pndCurrent != _this->__pndHead) {
                pndInsert->__pndPrev = _this->__pndCurrent->__pndPrev;
                pndInsert->__pndNext = _this->__pndCurrent;
                _this->__pndCurrent->__pndPrev->__pndNext = pndInsert;
                _this->__pndCurrent->__pndPrev = pndInsert;
            } else {
                pndInsert->__pndPrev = pndInsert;
                pndInsert->__pndNext = _this->__pndCurrent;
                _this->__pndCurrent->__pndPrev = pndInsert;
                _this->__pndHead = pndInsert;
            }
        }
        pndInsert = pndNextInsert;
        siIndex ++;
    }

    return (int)_this->__siCount;
}

bool ___bInitList(List * _this, size_t _siSize, bool (*_pbfnDestroyNode)(Node *))
{
    _this->__pndHead = NULL;
    _this->__pndTail = NULL;
    _this->__siCount = 0;
    _this->__siSize = _siSize;

    _this->__pfnbDestroyNode = _pbfnDestroyNode;

    _this->__pfnpndGetNode = pndGetNode;
    _this->__pfnpndRead = pndRead;
    _this->__pfnpndAppendFromHead = pndAppendFromHead;
    _this->__pfnpndAppendFromTail = pndAppendFromTail;
    _this->__pfnpndInsertBefore = pndInsertBefore;
    _this->__pfnpndInsertAfter = pndInsertAfter;
    _this->__pfnpndDeleteFromHead = pndDeleteFromHead;
    _this->__pfnpndDeleteFromTail = pndDeleteFromTail;
    _this->__pfnpndDelete = pndDelete;
    _this->__pfniDeleteAll = iDeleteAll;
    _this->__ppndfnModify = pndModify;
    _this->__pfnpndLinearSearchByUnique = pndLinearSearchByUnique;
    _this->__pfniLinearSearchByDuplicate = iLinearSearchByDuplicate;
    _this->__pfniSortByInsertion = iSortByInsertion;

    return true;
}
