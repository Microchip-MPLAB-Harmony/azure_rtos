/*******************************************************************************
  Helper Functions for WINC driver

  Summary:
    WINC Driver Helpers
    
  Description:
    Helpers library for WINC driver
*******************************************************************************/

/*****************************************************************************
 Copyright (C) 2012-2020 Microchip Technology Inc. and its subsidiaries.

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


#include <ctype.h>
#include <stdarg.h>
#include "wdrv_winc_link_list.h"

// lists implementation: single and double linked

void  WDRV_WINC_Helper_SingleListInitialize(WDRV_WINC_SINGLE_LIST* pL)
{
    pL->head = pL->tail = 0;
    pL->nNodes = 0;
}



void  WDRV_WINC_Helper_SingleListHeadAdd(WDRV_WINC_SINGLE_LIST* pL, WDRV_WINC_SGL_LIST_NODE* pN)
{
	pN->next = pL->head;
	pL->head = pN;
	if(pL->tail == 0)
	{  // empty list
		pL->tail = pN;
	}
    pL->nNodes++;
}

void  WDRV_WINC_Helper_SingleListTailAdd(WDRV_WINC_SINGLE_LIST* pL, WDRV_WINC_SGL_LIST_NODE* pN)
{
	pN->next = 0;
	if(pL->tail == 0)
	{
		pL->head = pL->tail = pN;
	}
	else
	{
		pL->tail->next = pN;
		pL->tail = pN;
	}
    pL->nNodes++;
}


// insertion in the middle, not head or tail
void  WDRV_WINC_Helper_SingleListMidAdd(WDRV_WINC_SINGLE_LIST* pL, WDRV_WINC_SGL_LIST_NODE* pN, WDRV_WINC_SGL_LIST_NODE* after)
{
    pN->next = after->next;
    after->next = pN;
    pL->nNodes++; 
}


WDRV_WINC_SGL_LIST_NODE*  WDRV_WINC_Helper_SingleListHeadRemove(WDRV_WINC_SINGLE_LIST* pL)
{
	WDRV_WINC_SGL_LIST_NODE* pN = pL->head;
    if(pN)
    {
        if(pL->head == pL->tail)
        {
            pL->head = pL->tail = 0;
        }
        else
        {
            pL->head = pN->next;
        }
        pL->nNodes--;
    }

	return pN;
}

// removes the next node (following prev) in the list
// if prev == 0 removed the head
WDRV_WINC_SGL_LIST_NODE*  WDRV_WINC_Helper_SingleListNextRemove(WDRV_WINC_SINGLE_LIST* pL, WDRV_WINC_SGL_LIST_NODE* prev)
{
    WDRV_WINC_SGL_LIST_NODE*  pN;

    if(prev == 0)
    {
        return WDRV_WINC_Helper_SingleListHeadRemove(pL);
    }

    pN = prev->next;
    if(pN)
    {
        prev->next = pN->next;
        if(pN == pL->tail)
        {
            pL->tail = prev;
        }
        pL->nNodes--;
    }

    return pN;


}


// removes a node somewhere in the middle
// Note: this is lengthy!
// Use a double linked list if faster operation needed!



WDRV_WINC_SGL_LIST_NODE*  WDRV_WINC_Helper_SingleListNodeRemove(WDRV_WINC_SINGLE_LIST* pL, WDRV_WINC_SGL_LIST_NODE* pN)
{
    if(pN == pL->head)
    {
        WDRV_WINC_Helper_SingleListHeadRemove(pL);
    }
    else
    {
        WDRV_WINC_SGL_LIST_NODE* prev;
        for(prev = pL->head; prev != 0 && prev->next != pN; prev = prev->next);
        if(prev == 0)
        {   // no such node
            return 0;
        }
        // found it
        prev->next = pN->next;
        if(pN == pL->tail)
        {
            pL->tail = prev;
        }
        pL->nNodes--;
    }

    return pN;
}

bool WDRV_WINC_Helper_SingleListFind(WDRV_WINC_SINGLE_LIST* pL, WDRV_WINC_SGL_LIST_NODE* pN)
{
    WDRV_WINC_SGL_LIST_NODE* node;
    for(node = pL->head; node != 0 ; node = node->next)
    {
        if(node == pN)
        {
            return true;
        }
    }

    return false;
}

void  WDRV_WINC_Helper_SingleListAppend(WDRV_WINC_SINGLE_LIST* pDstL, WDRV_WINC_SINGLE_LIST* pAList)
{
	WDRV_WINC_SGL_LIST_NODE* pN;
	while((pN = WDRV_WINC_Helper_SingleListHeadRemove(pAList)))
	{
		WDRV_WINC_Helper_SingleListTailAdd(pDstL, pN);
	}
}


// Protected Single linked list manipulation

bool  WDRV_WINC_Helper_ProtectedSingleListInitialize(WDRV_WINC_PROTECTED_SINGLE_LIST* pL)
{
    WDRV_WINC_Helper_SingleListInitialize(&pL->list);
    pL->semValid = (OSAL_SEM_Create(&pL->semaphore, OSAL_SEM_TYPE_BINARY, 1, 1) == OSAL_RESULT_TRUE);
    return pL->semValid;
}

void  WDRV_WINC_Helper_ProtectedSingleListDeinitialize(WDRV_WINC_PROTECTED_SINGLE_LIST* pL)
{
    if(pL->semValid)
    {
        if (OSAL_SEM_Pend(&pL->semaphore, OSAL_WAIT_FOREVER) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
        WDRV_WINC_Helper_SingleListRemoveAll(&pL->list);
        OSAL_SEM_Delete(&pL->semaphore);
        pL->semValid = false;
    }
}

void  WDRV_WINC_Helper_ProtectedSingleListHeadAdd(WDRV_WINC_PROTECTED_SINGLE_LIST* pL, WDRV_WINC_SGL_LIST_NODE* pN)
{
    if(pL->semValid)
    {
        if (OSAL_SEM_Pend(&pL->semaphore, OSAL_WAIT_FOREVER) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
        WDRV_WINC_Helper_SingleListHeadAdd(&pL->list, pN);
        if (OSAL_SEM_Post(&pL->semaphore) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
    }
}

void  WDRV_WINC_Helper_ProtectedSingleListTailAdd(WDRV_WINC_PROTECTED_SINGLE_LIST* pL, WDRV_WINC_SGL_LIST_NODE* pN)
{
    if(pL->semValid)
    {
        if (OSAL_SEM_Pend(&pL->semaphore, OSAL_WAIT_FOREVER) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
        WDRV_WINC_Helper_SingleListTailAdd(&pL->list, pN);
        if (OSAL_SEM_Post(&pL->semaphore) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
    }

}


// insertion in the middle, not head or tail
void  WDRV_WINC_Helper_ProtectedSingleListMidAdd(WDRV_WINC_PROTECTED_SINGLE_LIST* pL, WDRV_WINC_SGL_LIST_NODE* pN, WDRV_WINC_SGL_LIST_NODE* after)
{
    if(pL->semValid)
    {
        if (OSAL_SEM_Pend(&pL->semaphore, OSAL_WAIT_FOREVER) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
        WDRV_WINC_Helper_SingleListMidAdd(&pL->list, pN, after);
        if (OSAL_SEM_Post(&pL->semaphore) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
    }
}

// removes the head node
WDRV_WINC_SGL_LIST_NODE*  WDRV_WINC_Helper_ProtectedSingleListHeadRemove(WDRV_WINC_PROTECTED_SINGLE_LIST* pL)
{

    if(pL->semValid)
    {
        if (OSAL_SEM_Pend(&pL->semaphore, OSAL_WAIT_FOREVER) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
        WDRV_WINC_SGL_LIST_NODE * ret = WDRV_WINC_Helper_SingleListHeadRemove(&pL->list);
        if (OSAL_SEM_Post(&pL->semaphore) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
        return ret;
    }

    return 0;

}

// removes the next node (following prev) in the list
// if prev == 0 removed the head
WDRV_WINC_SGL_LIST_NODE*  WDRV_WINC_Helper_ProtectedSingleListNextRemove(WDRV_WINC_PROTECTED_SINGLE_LIST* pL, WDRV_WINC_SGL_LIST_NODE* prev)
{

    if(pL->semValid)
    {
        if (OSAL_SEM_Pend(&pL->semaphore, OSAL_WAIT_FOREVER) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
        WDRV_WINC_SGL_LIST_NODE * ret = WDRV_WINC_Helper_SingleListNextRemove(&pL->list, prev);
        if (OSAL_SEM_Post(&pL->semaphore) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
        return ret;
    }
    return 0;
}



// removes a node anywhere in the list
// Note: this is lengthy!
// Use a double linked list if faster operation needed!
WDRV_WINC_SGL_LIST_NODE*  WDRV_WINC_Helper_ProtectedSingleListNodeRemove(WDRV_WINC_PROTECTED_SINGLE_LIST* pL, WDRV_WINC_SGL_LIST_NODE* pN)
{

    if(pL->semValid)
    {
        if (OSAL_SEM_Pend(&pL->semaphore, OSAL_WAIT_FOREVER) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
        WDRV_WINC_SGL_LIST_NODE * ret = WDRV_WINC_Helper_SingleListNodeRemove(&pL->list, pN);
        if (OSAL_SEM_Post(&pL->semaphore) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
        return ret;
    }

    return 0;
}



void  WDRV_WINC_Helper_ProtectedSingleListAppend(WDRV_WINC_PROTECTED_SINGLE_LIST* pDstL, WDRV_WINC_SINGLE_LIST* pAList)
{
    if(pDstL->semValid)
    {
        if (OSAL_SEM_Pend(&pDstL->semaphore, OSAL_WAIT_FOREVER) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
        WDRV_WINC_Helper_SingleListAppend(&pDstL->list, pAList);
        if (OSAL_SEM_Post(&pDstL->semaphore) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
    }
}



void WDRV_WINC_Helper_ProtectedSingleListRemoveAll(WDRV_WINC_PROTECTED_SINGLE_LIST* pL)
{
    if(pL->semValid)
    {
        if (OSAL_SEM_Pend(&pL->semaphore, OSAL_WAIT_FOREVER) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
        WDRV_WINC_Helper_SingleListRemoveAll(&pL->list);
        if (OSAL_SEM_Post(&pL->semaphore) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
    }
}

bool WDRV_WINC_Helper_ProtectedSingleListLock(WDRV_WINC_PROTECTED_SINGLE_LIST* pL)
{
    if(pL->semValid)
    {
        return (OSAL_SEM_Pend(&pL->semaphore, OSAL_WAIT_FOREVER) == OSAL_RESULT_TRUE);
    }

    return false;
}

bool WDRV_WINC_Helper_ProtectedSingleListUnlock(WDRV_WINC_PROTECTED_SINGLE_LIST* pL)
{
    if(pL->semValid)
    {
        return (OSAL_SEM_Post(&pL->semaphore) == OSAL_RESULT_TRUE);
    }

    return false;
}


/////  double linked lists manipulation ///////////
//


void  WDRV_WINC_Helper_DoubleListInitialize(WDRV_WINC_DOUBLE_LIST* pL)
{
    pL->head = pL->tail = 0;
    pL->nNodes = 0;
}


void  WDRV_WINC_Helper_DoubleListHeadAdd(WDRV_WINC_DOUBLE_LIST* pL, WDRV_WINC_DBL_LIST_NODE* pN)
{
	if(pL->head == 0)
	{ // empty list, first node
		pL->head = pL->tail = pN;
		pN->next = pN->prev = 0;
	}
	else
	{
		pN->next = pL->head;
		pN->prev = 0;
		pL->head->prev = pN;
		pL->head = pN;
	}		
    pL->nNodes++;
}

void  WDRV_WINC_Helper_DoubleListTailAdd(WDRV_WINC_DOUBLE_LIST* pL, WDRV_WINC_DBL_LIST_NODE* pN)
{
	if(pL->head == 0)
	{ // empty list, first node
		pL->head = pL->tail = pN;
		pN->next = pN->prev = 0;
	}
	else
	{
		pN->next = 0;
		pN->prev = pL->tail;
		pL->tail->next = pN;
		pL->tail = pN;
	}		
    pL->nNodes++;
}

// add node pN in the middle, after existing node "after"
void  WDRV_WINC_Helper_DoubleListMidAdd(WDRV_WINC_DOUBLE_LIST* pL, WDRV_WINC_DBL_LIST_NODE* pN, WDRV_WINC_DBL_LIST_NODE* after)
{
    pN->next = after->next;
    pN->prev = after;
    after->next->prev = pN;
    after->next = pN;
    pL->nNodes++;
}

WDRV_WINC_DBL_LIST_NODE*  WDRV_WINC_Helper_DoubleListHeadRemove(WDRV_WINC_DOUBLE_LIST* pL)
{
    WDRV_WINC_DBL_LIST_NODE* pN = pL->head;
    if(pN)
    {
        if(pL->head == pL->tail)
        {
            pL->head = pL->tail = 0;
        }
        else
        {
            pL->head = pN->next;
            pL->head->prev = 0;
        }
        pL->nNodes--;
    }
    return pN;
}

WDRV_WINC_DBL_LIST_NODE*  WDRV_WINC_Helper_DoubleListTailRemove(WDRV_WINC_DOUBLE_LIST* pL)
{
    WDRV_WINC_DBL_LIST_NODE* pN = pL->tail;
    if(pN)
    {
        if(pL->head == pL->tail)
        {
            pL->head = pL->tail = 0;
        }
        else
        {
            pL->tail = pN->prev;
            pL->tail->next = 0;
        }
        pL->nNodes--;
    }
    return pN;
}

// remove existing node, neither head, nor tail
void  WDRV_WINC_Helper_DoubleListMidRemove(WDRV_WINC_DOUBLE_LIST* pL, WDRV_WINC_DBL_LIST_NODE* pN)
{
    (pN)->prev->next = (pN)->next;
    (pN)->next->prev = (pN)->prev;
    pL->nNodes--;
}

void  WDRV_WINC_Helper_DoubleListNodeRemove(WDRV_WINC_DOUBLE_LIST* pL, WDRV_WINC_DBL_LIST_NODE* pN)
{
	if(pN == pL->head)
	{
		WDRV_WINC_Helper_DoubleListHeadRemove(pL);
	}
	else if(pN == pL->tail)
	{
		WDRV_WINC_Helper_DoubleListTailRemove(pL);
	}
	else
	{
		WDRV_WINC_Helper_DoubleListMidRemove(pL, pN);
	}
}

bool WDRV_WINC_Helper_DoubleListFind(WDRV_WINC_DOUBLE_LIST* pL, WDRV_WINC_DBL_LIST_NODE* pN)
{
    WDRV_WINC_DBL_LIST_NODE* node;
    for(node = pL->head; node != 0 ; node = node->next)
    {
        if(node == pN)
        {
            return true;
        }
    }

    return false;
}



bool  WDRV_WINC_Helper_ProtectedDoubleListInitialize(WDRV_WINC_PROTECTED_DOUBLE_LIST* pL)
{
    WDRV_WINC_Helper_DoubleListInitialize(&pL->list);
    pL->semValid = (OSAL_SEM_Create(&pL->semaphore, OSAL_SEM_TYPE_BINARY, 1, 1) == OSAL_RESULT_TRUE);
    return pL->semValid;
}

void  WDRV_WINC_Helper_ProtectedDoubleListDeinitialize(WDRV_WINC_PROTECTED_DOUBLE_LIST* pL)
{
    if(pL->semValid)
    {
        if (OSAL_SEM_Pend(&pL->semaphore, OSAL_WAIT_FOREVER) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
        WDRV_WINC_Helper_DoubleListRemoveAll(&pL->list);
        OSAL_SEM_Delete(&pL->semaphore);
        pL->semValid = false;
    }
}


void  WDRV_WINC_Helper_ProtectedDoubleListHeadAdd(WDRV_WINC_PROTECTED_DOUBLE_LIST* pL, WDRV_WINC_DBL_LIST_NODE* pN)
{
    if(pL->semValid)
    {
        if (OSAL_SEM_Pend(&pL->semaphore, OSAL_WAIT_FOREVER) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
        WDRV_WINC_Helper_DoubleListHeadAdd(&pL->list, pN);
        if (OSAL_SEM_Post(&pL->semaphore) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
    }
}

void  WDRV_WINC_Helper_ProtectedDoubleListTailAdd(WDRV_WINC_PROTECTED_DOUBLE_LIST* pL, WDRV_WINC_DBL_LIST_NODE* pN)
{
    if(pL->semValid)
    {
        if (OSAL_SEM_Pend(&pL->semaphore, OSAL_WAIT_FOREVER) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
        WDRV_WINC_Helper_DoubleListTailAdd(&pL->list, pN);
        if (OSAL_SEM_Post(&pL->semaphore) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
    }
}


// insertion in the middle, not head or tail
void  WDRV_WINC_Helper_ProtectedDoubleListMidAdd(WDRV_WINC_PROTECTED_DOUBLE_LIST* pL, WDRV_WINC_DBL_LIST_NODE* pN, WDRV_WINC_DBL_LIST_NODE* after)
{
    if(pL->semValid)
    {
        if (OSAL_SEM_Pend(&pL->semaphore, OSAL_WAIT_FOREVER) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
        WDRV_WINC_Helper_DoubleListMidAdd(&pL->list, pN, after);
        if (OSAL_SEM_Post(&pL->semaphore) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
    }
}

// removes the head node
WDRV_WINC_DBL_LIST_NODE*  WDRV_WINC_Helper_ProtectedDoubleListHeadRemove(WDRV_WINC_PROTECTED_DOUBLE_LIST* pL)
{
    if(pL->semValid)
    {
        if (OSAL_SEM_Pend(&pL->semaphore, OSAL_WAIT_FOREVER) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
        WDRV_WINC_DBL_LIST_NODE * ret = WDRV_WINC_Helper_DoubleListHeadRemove(&pL->list);
        if (OSAL_SEM_Post(&pL->semaphore) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
        return ret;
    }

    return 0;
}

// removes the next node (following prev) in the list
// if prev == 0 removed the head
WDRV_WINC_DBL_LIST_NODE*  WDRV_WINC_Helper_ProtectedDoubleListTailRemove(WDRV_WINC_PROTECTED_DOUBLE_LIST* pL)
{
    if(pL->semValid)
    {
        if (OSAL_SEM_Pend(&pL->semaphore, OSAL_WAIT_FOREVER) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
        WDRV_WINC_DBL_LIST_NODE * ret = WDRV_WINC_Helper_DoubleListTailRemove(&pL->list);
        if (OSAL_SEM_Post(&pL->semaphore) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
        return ret;
    }

    return 0;
}

void  WDRV_WINC_Helper_ProtectedDoubleListMidRemove(WDRV_WINC_PROTECTED_DOUBLE_LIST* pL, WDRV_WINC_DBL_LIST_NODE* pN)
{
    if(pL->semValid)
    {
        if (OSAL_SEM_Pend(&pL->semaphore, OSAL_WAIT_FOREVER) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
        WDRV_WINC_Helper_DoubleListMidRemove(&pL->list, pN);
        if (OSAL_SEM_Post(&pL->semaphore) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
    }
}


void  WDRV_WINC_Helper_ProtectedDoubleListNodeRemove(WDRV_WINC_PROTECTED_DOUBLE_LIST* pL, WDRV_WINC_DBL_LIST_NODE* pN)
{
    if(pL->semValid)
    {
        if (OSAL_SEM_Pend(&pL->semaphore, OSAL_WAIT_FOREVER) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
        WDRV_WINC_Helper_DoubleListNodeRemove(&pL->list, pN);
        if (OSAL_SEM_Post(&pL->semaphore) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
    }
}

void WDRV_WINC_Helper_ProtectedDoubleListRemoveAll(WDRV_WINC_PROTECTED_DOUBLE_LIST* pL)
{
    if(pL->semValid)
    {
        if (OSAL_SEM_Pend(&pL->semaphore, OSAL_WAIT_FOREVER) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
        WDRV_WINC_Helper_DoubleListRemoveAll(&pL->list);
        if (OSAL_SEM_Post(&pL->semaphore) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
    }
}

void WDRV_WINC_Helper_ProtectedDoubleListLock(WDRV_WINC_PROTECTED_DOUBLE_LIST* pL)
{
    if(pL->semValid)
    {
        if (OSAL_SEM_Pend(&pL->semaphore, OSAL_WAIT_FOREVER) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
    }
}

void WDRV_WINC_Helper_ProtectedDoubleListUnlock(WDRV_WINC_PROTECTED_DOUBLE_LIST* pL)
{
    if(pL->semValid)
    {
        if (OSAL_SEM_Post(&pL->semaphore) != OSAL_RESULT_TRUE)
        {
            //SYS_DEBUG LOG
        }
    }
}
