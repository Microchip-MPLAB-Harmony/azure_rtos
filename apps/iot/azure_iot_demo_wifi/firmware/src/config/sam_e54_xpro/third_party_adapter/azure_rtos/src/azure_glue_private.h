/*******************************************************************************
  Azure IoT glue private header File

  Summary: 
    Azure IoT glue file
    
  Description:
    This file provides the private Azure IoT glue definitions and functions
*******************************************************************************/

/*****************************************************************************
 Copyright (C) 2020 Microchip Technology Inc. and its subsidiaries.

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

#ifndef _AZURE_IOT_PRIVATE_GLUE_H_
#define _AZURE_IOT_PRIVATE_GLUE_H_

#include <stdint.h>
#include <stdbool.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct _TAG_AZ_SGL_LIST_NODE
{
	struct _TAG_AZ_SGL_LIST_NODE*	next;		// next node in list
    void*                           data[];     // generic payload    
}AZ_SGL_LIST_NODE;	// generic linked list node definition


typedef struct
{
	AZ_SGL_LIST_NODE*	head;	// list head
	AZ_SGL_LIST_NODE*	tail;
    int                 nNodes; // number of nodes in the list
}AZ_SINGLE_LIST;	// single linked list


/////  single linked lists manipulation ///////////
//


void  _Azure_SingleListInitialize(AZ_SINGLE_LIST* pL);


static __inline__ bool __attribute__((always_inline)) _Azure_SingleListIsEmpty(AZ_SINGLE_LIST* pL)
{
    return pL->head == 0;
}


static __inline__ int __attribute__((always_inline)) _Azure_SingleListCount(AZ_SINGLE_LIST* pL)
{
    return pL->nNodes;
}

void  _Azure_SingleListHeadAdd(AZ_SINGLE_LIST* pL, AZ_SGL_LIST_NODE* pN);

void  _Azure_SingleListTailAdd(AZ_SINGLE_LIST* pL, AZ_SGL_LIST_NODE* pN);


// insertion in the middle, not head or tail
void  _Azure_SingleListMidAdd(AZ_SINGLE_LIST* pL, AZ_SGL_LIST_NODE* pN, AZ_SGL_LIST_NODE* after);


// removes the head node
AZ_SGL_LIST_NODE*  _Azure_SingleListHeadRemove(AZ_SINGLE_LIST* pL);

// removes the next node (following prev) in the list
// if prev == 0 removed the head
AZ_SGL_LIST_NODE*  _Azure_SingleListNextRemove(AZ_SINGLE_LIST* pL, AZ_SGL_LIST_NODE* prev);


// removes a node anywhere in the list
// Note: this is lengthy!
// Use a double linked list if faster operation needed!
AZ_SGL_LIST_NODE*  _Azure_SingleListNodeRemove(AZ_SINGLE_LIST* pL, AZ_SGL_LIST_NODE* pN);

// concatenates the append list to the destination one
void  _Azure_SingleListAppend(AZ_SINGLE_LIST* pDstL, AZ_SINGLE_LIST* pAList);



// no memory de-allocation is performed, just removes the nodes from the list
static __inline__ void __attribute__((always_inline)) _Azure_SingleListRemoveAll(AZ_SINGLE_LIST* pL)
{
	while((_Azure_SingleListHeadRemove(pL)));
}

// returns true if pN belongs to pL; false otherwise
// expensive, traverses the list
bool        _Azure_SingleListFind(AZ_SINGLE_LIST* pL, AZ_SGL_LIST_NODE* pN);

// other helpers
//
// convert a MAC address string to binary
bool     _Azure_StringToMACAddress(const char* macAddrStr, uint8_t b[6]);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _AZURE_IOT_PRIVATE_GLUE_H_ */

