/*******************************************************************************
  Linked list helper file

  Company:
    Microchip Technology Inc.
    
  File Name:
    wdrv_winc_link_list.h

  Summary:
    Linked lists manipulation Interface Header
    
  Description:
    This header file contains the function prototypes and definitions of the 
    linked lists manipulation routines
*******************************************************************************/
// DOM-IGNORE-BEGIN
/*****************************************************************************
 Copyright (C) 2012-2018 Microchip Technology Inc. and its subsidiaries.

Microchip Technology Inc. and its subsidiaries.

Subject to your compliance with these terms, you may use Microchip software 
and any derivatives exclusively with Microchip products. It is your 
responsibility to comply with third party license terms applicable to your 
use of third party software (including open source software) that may 
accompany Microchip software.

THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR 
PURPOSE.

IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE 
FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN 
ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY, 
THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*****************************************************************************/








// DOM-IGNORE-END

#ifndef _LINK_LISTS_H_
#define _LINK_LISTS_H_

#include "osal/osal.h"
#include <stdbool.h>

typedef struct _WDRV_WINC_TAG_SGL_LIST_NODE
{
	struct _WDRV_WINC_TAG_SGL_LIST_NODE*		next;		// next node in list
    void*                           data[];     // generic payload    
}WDRV_WINC_SGL_LIST_NODE;	// generic linked list node definition


typedef struct
{
	WDRV_WINC_SGL_LIST_NODE*	head;	// list head
	WDRV_WINC_SGL_LIST_NODE*	tail;
    int             nNodes; // number of nodes in the list

}WDRV_WINC_SINGLE_LIST;	// single linked list


/////  single linked lists manipulation ///////////
//


void  WDRV_WINC_Helper_SingleListInitialize(WDRV_WINC_SINGLE_LIST* pL);


static __inline__ bool __attribute__((always_inline)) WDRV_WINC_Helper_SingleListIsEmpty(WDRV_WINC_SINGLE_LIST* pL)
{
    return pL->head == 0;
}


static __inline__ int __attribute__((always_inline)) WDRV_WINC_Helper_SingleListCount(WDRV_WINC_SINGLE_LIST* pL)
{
    return pL->nNodes;
}

void  WDRV_WINC_Helper_SingleListHeadAdd(WDRV_WINC_SINGLE_LIST* pL, WDRV_WINC_SGL_LIST_NODE* pN);

void  WDRV_WINC_Helper_SingleListTailAdd(WDRV_WINC_SINGLE_LIST* pL, WDRV_WINC_SGL_LIST_NODE* pN);


// insertion in the middle, not head or tail
void  WDRV_WINC_Helper_SingleListMidAdd(WDRV_WINC_SINGLE_LIST* pL, WDRV_WINC_SGL_LIST_NODE* pN, WDRV_WINC_SGL_LIST_NODE* after);


// removes the head node
WDRV_WINC_SGL_LIST_NODE*  WDRV_WINC_Helper_SingleListHeadRemove(WDRV_WINC_SINGLE_LIST* pL);

// removes the next node (following prev) in the list
// if prev == 0 removed the head
WDRV_WINC_SGL_LIST_NODE*  WDRV_WINC_Helper_SingleListNextRemove(WDRV_WINC_SINGLE_LIST* pL, WDRV_WINC_SGL_LIST_NODE* prev);


// removes a node anywhere in the list
// Note: this is lengthy!
// Use a double linked list if faster operation needed!
WDRV_WINC_SGL_LIST_NODE*  WDRV_WINC_Helper_SingleListNodeRemove(WDRV_WINC_SINGLE_LIST* pL, WDRV_WINC_SGL_LIST_NODE* pN);

// concatenates the append list to the destination one
void  WDRV_WINC_Helper_SingleListAppend(WDRV_WINC_SINGLE_LIST* pDstL, WDRV_WINC_SINGLE_LIST* pAList);



// no memory de-allocation is performed, just removes the nodes from the list
static __inline__ void __attribute__((always_inline)) WDRV_WINC_Helper_SingleListRemoveAll(WDRV_WINC_SINGLE_LIST* pL)
{
	while((WDRV_WINC_Helper_SingleListHeadRemove(pL)));
}

// returns true if pN belongs to pL; false otherwise
// expensive, traverses the list
bool        WDRV_WINC_Helper_SingleListFind(WDRV_WINC_SINGLE_LIST* pL, WDRV_WINC_SGL_LIST_NODE* pN);

// Single linked protected list /////
typedef struct
{
    WDRV_WINC_SINGLE_LIST list;
    OSAL_SEM_HANDLE_TYPE semaphore;
    bool   semValid;
} WDRV_WINC_PROTECTED_SINGLE_LIST;

// creates an empty single linked list and associated semaphore
// the list should NOT be used if the initialization failed!
// However, WDRV_WINC_Helper_ProtectedSingleListDeinitialize() can be safely called
bool  WDRV_WINC_Helper_ProtectedSingleListInitialize(WDRV_WINC_PROTECTED_SINGLE_LIST* pL);

// removes all nodes from a single linked list and deletes the associated semaphore
// no memory de-allocation is performed, just removes the nodes from the list
void  WDRV_WINC_Helper_ProtectedSingleListDeinitialize(WDRV_WINC_PROTECTED_SINGLE_LIST* pL);

static __inline__ bool __attribute__((always_inline)) WDRV_WINC_Helper_ProtectedSingleListIsEmpty(WDRV_WINC_PROTECTED_SINGLE_LIST* pL)
{
    return WDRV_WINC_Helper_SingleListIsEmpty(&pL->list);
}


static __inline__ int __attribute__((always_inline)) WDRV_WINC_Helper_ProtectedSingleListCount(WDRV_WINC_PROTECTED_SINGLE_LIST* pL)
{
    return WDRV_WINC_Helper_SingleListCount(&pL->list);
}

void  WDRV_WINC_Helper_ProtectedSingleListHeadAdd(WDRV_WINC_PROTECTED_SINGLE_LIST* pL, WDRV_WINC_SGL_LIST_NODE* pN);

void  WDRV_WINC_Helper_ProtectedSingleListTailAdd(WDRV_WINC_PROTECTED_SINGLE_LIST* pL, WDRV_WINC_SGL_LIST_NODE* pN);


// insertion in the middle, not head or tail
void  WDRV_WINC_Helper_ProtectedSingleListMidAdd(WDRV_WINC_PROTECTED_SINGLE_LIST* pL, WDRV_WINC_SGL_LIST_NODE* pN, WDRV_WINC_SGL_LIST_NODE* after);


// removes the head node
WDRV_WINC_SGL_LIST_NODE*  WDRV_WINC_Helper_ProtectedSingleListHeadRemove(WDRV_WINC_PROTECTED_SINGLE_LIST* pL);

// removes the next node (following prev) in the list
// if prev == 0 removed the head
WDRV_WINC_SGL_LIST_NODE*  WDRV_WINC_Helper_ProtectedSingleListNextRemove(WDRV_WINC_PROTECTED_SINGLE_LIST* pL, WDRV_WINC_SGL_LIST_NODE* prev);


// removes a node anywhere in the list
// Note: this is lengthy!
// Use a double linked list if faster operation needed!
WDRV_WINC_SGL_LIST_NODE*  WDRV_WINC_Helper_ProtectedSingleListNodeRemove(WDRV_WINC_PROTECTED_SINGLE_LIST* pL, WDRV_WINC_SGL_LIST_NODE* pN);


// concatenates the append list to the destination one
void  WDRV_WINC_Helper_ProtectedSingleListAppend(WDRV_WINC_PROTECTED_SINGLE_LIST* pDstL, WDRV_WINC_SINGLE_LIST* pAList);


// removes all nodes from a single linked list
// no memory de-allocation is performed, just removes the nodes from the list
// after this operation the list is valid, i.e. the operation
// does not delete the associated semaphore
void WDRV_WINC_Helper_ProtectedSingleListRemoveAll(WDRV_WINC_PROTECTED_SINGLE_LIST* pL);


// locks access to a protected single list
// the list should have been properly initialized
bool WDRV_WINC_Helper_ProtectedSingleListLock(WDRV_WINC_PROTECTED_SINGLE_LIST* pL);

// unlocks access to a protected single list
// the list should have been properly initialized and lock acquired
bool WDRV_WINC_Helper_ProtectedSingleListUnlock(WDRV_WINC_PROTECTED_SINGLE_LIST* pL);

/////  double linked lists manipulation ///////////
//

typedef struct _WDRV_WINC_TAG_DBL_LIST_NODE
{
	struct _WDRV_WINC_TAG_DBL_LIST_NODE*		next;		// next node in list
	struct _WDRV_WINC_TAG_DBL_LIST_NODE*		prev;		// prev node in list
    void*                           data[];     // generic payload    
}WDRV_WINC_DBL_LIST_NODE;	// generic linked list node definition


typedef struct
{
	WDRV_WINC_DBL_LIST_NODE*	head;	// list head
	WDRV_WINC_DBL_LIST_NODE*	tail;   // list tail;
    int             nNodes; // number of nodes in the list 
}WDRV_WINC_DOUBLE_LIST;	// double linked list


void  WDRV_WINC_Helper_DoubleListInitialize(WDRV_WINC_DOUBLE_LIST* pL);


static __inline__ bool __attribute__((always_inline)) WDRV_WINC_Helper_DoubleListIsEmpty(WDRV_WINC_DOUBLE_LIST* pL)
{
    return pL->head == 0;
}

static __inline__ int __attribute__((always_inline)) WDRV_WINC_Helper_DoubleListCount(WDRV_WINC_DOUBLE_LIST* pL)
{
    return pL->nNodes;
}

void  WDRV_WINC_Helper_DoubleListHeadAdd(WDRV_WINC_DOUBLE_LIST* pL, WDRV_WINC_DBL_LIST_NODE* pN);

void  WDRV_WINC_Helper_DoubleListTailAdd(WDRV_WINC_DOUBLE_LIST* pL, WDRV_WINC_DBL_LIST_NODE* pN);

// add node pN in the middle, after existing node "after"
void  WDRV_WINC_Helper_DoubleListMidAdd(WDRV_WINC_DOUBLE_LIST* pL, WDRV_WINC_DBL_LIST_NODE* pN, WDRV_WINC_DBL_LIST_NODE* after);

WDRV_WINC_DBL_LIST_NODE*  WDRV_WINC_Helper_DoubleListHeadRemove(WDRV_WINC_DOUBLE_LIST* pL);

WDRV_WINC_DBL_LIST_NODE*  WDRV_WINC_Helper_DoubleListTailRemove(WDRV_WINC_DOUBLE_LIST* pL);

// remove existing node, neither head, nor tail
void  WDRV_WINC_Helper_DoubleListMidRemove(WDRV_WINC_DOUBLE_LIST* pL, WDRV_WINC_DBL_LIST_NODE* pN);

void  WDRV_WINC_Helper_DoubleListNodeRemove(WDRV_WINC_DOUBLE_LIST* pL, WDRV_WINC_DBL_LIST_NODE* pN);

// no memory de-allocation is performed, just removes the nodes from the list
static __inline__ void __attribute__((always_inline)) WDRV_WINC_Helper_DoubleListRemoveAll(WDRV_WINC_DOUBLE_LIST* pL)
{
    while((WDRV_WINC_Helper_DoubleListHeadRemove(pL)));
}

// returns true if pN belongs to pL; false otherwise
// expensive, traverses the list
bool        WDRV_WINC_Helper_DoubleListFind(WDRV_WINC_DOUBLE_LIST* pL, WDRV_WINC_DBL_LIST_NODE* pN);


typedef struct
{
    WDRV_WINC_DOUBLE_LIST list;
    OSAL_SEM_HANDLE_TYPE semaphore;
    bool semValid;
}WDRV_WINC_PROTECTED_DOUBLE_LIST;	// double linked list


// creates an empty double linked list and associated semaphore
// the list should NOT be used if the initialization failed!
// However, WDRV_WINC_Helper_ProtectedDoubleListDeinitialize() can be safely called
bool  WDRV_WINC_Helper_ProtectedDoubleListInitialize(WDRV_WINC_PROTECTED_DOUBLE_LIST* pL);

// removes all nodes from a double linked list and deletes the associated semaphore
// no memory de-allocation is performed, just removes the nodes from the list
void  WDRV_WINC_Helper_ProtectedDoubleListDeinitialize(WDRV_WINC_PROTECTED_DOUBLE_LIST* pL);

static __inline__ bool __attribute__((always_inline)) WDRV_WINC_Helper_ProtectedDoubleListIsEmpty(WDRV_WINC_PROTECTED_DOUBLE_LIST* pL)
{
    return WDRV_WINC_Helper_DoubleListIsEmpty(&pL->list);
}

static __inline__ int __attribute__((always_inline)) WDRV_WINC_Helper_ProtectedDoubleListCount(WDRV_WINC_PROTECTED_DOUBLE_LIST* pL)
{
    return WDRV_WINC_Helper_DoubleListCount(&pL->list);
}

void  WDRV_WINC_Helper_ProtectedDoubleListHeadAdd(WDRV_WINC_PROTECTED_DOUBLE_LIST* pL, WDRV_WINC_DBL_LIST_NODE* pN);

void  WDRV_WINC_Helper_ProtectedDoubleListTailAdd(WDRV_WINC_PROTECTED_DOUBLE_LIST* pL, WDRV_WINC_DBL_LIST_NODE* pN);

// add node pN in the middle, after existing node "after"
void  WDRV_WINC_Helper_ProtectedDoubleListMidAdd(WDRV_WINC_PROTECTED_DOUBLE_LIST* pL, WDRV_WINC_DBL_LIST_NODE* pN, WDRV_WINC_DBL_LIST_NODE* after);

WDRV_WINC_DBL_LIST_NODE*  WDRV_WINC_Helper_ProtectedDoubleListHeadRemove(WDRV_WINC_PROTECTED_DOUBLE_LIST* pL);

WDRV_WINC_DBL_LIST_NODE*  WDRV_WINC_Helper_ProtectedDoubleListTailRemove(WDRV_WINC_PROTECTED_DOUBLE_LIST* pL);

// remove existing node, neither head, nor tail
void  WDRV_WINC_Helper_ProtectedDoubleListMidRemove(WDRV_WINC_PROTECTED_DOUBLE_LIST* pL, WDRV_WINC_DBL_LIST_NODE* pN);

void  WDRV_WINC_Helper_ProtectedDoubleListNodeRemove(WDRV_WINC_PROTECTED_DOUBLE_LIST* pL, WDRV_WINC_DBL_LIST_NODE* pN);

// removes all nodes from a double linked list
// no memory de-allocation is performed, just removes the nodes from the list
// after this operation the list is valid, i.e. the operation
// does not delete the associated semaphore
void WDRV_WINC_Helper_ProtectedDoubleListRemoveAll(WDRV_WINC_PROTECTED_DOUBLE_LIST* pL);


// locks access to a protected double list
// the list should have been properly initialized
void WDRV_WINC_Helper_ProtectedDoubleListLock(WDRV_WINC_PROTECTED_DOUBLE_LIST* pL);

// unlocks access to a protected double list
// the list should have been properly initialized and lock acquired
void WDRV_WINC_Helper_ProtectedDoubleListUnlock(WDRV_WINC_PROTECTED_DOUBLE_LIST* pL);

#endif //  _LINK_LISTS_H_


