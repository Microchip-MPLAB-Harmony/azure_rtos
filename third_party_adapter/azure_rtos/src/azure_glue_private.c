/*******************************************************************************
  Azure IoT glue private Source File

  Summary: 
    Azure IoT glue private file
    
  Description:
    This file provides the private glue file for using
    Azure IoT with the Harmony framework
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

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include <stdarg.h>
#include <sys/types.h>
#include <string.h>

#include "azure_glue_private.h"

// converts a string MAC address (aa:bb:cc:dd:ee:ff) to binary
bool _Azure_StringToMACAddress(const char* macAddrStr, uint8_t b[6])
{
    char buff[20];

    memset(b, 0, 6);

    if(macAddrStr == 0 || strlen(macAddrStr) == 0)
    {
        return true;
    }

    if(strlen(macAddrStr) > sizeof(buff) - 1)
    {   // too big to be valid
        return false;
    }

    strcpy(buff, macAddrStr);
    
    char* endptr;
    char* ptok;
    char* pS = buff;
    int tknIx = 0;
    uint8_t* pb = b;
    while(true)
    {
        ptok = strtok(pS, ":-");
        pS = 0;
        if(ptok == 0)
        {   // done
            break;
        }

        if(tknIx < 6)
        {
            if(strlen(ptok) != 2)
            {   // bad length
                return false;
            }
            *pb++ = (uint8_t)strtoul(ptok, &endptr, 16);
            if(endptr != ptok + 2)
            {
                return false;
            }
        }
        else
        {   // too many
            return false;
        }
        tknIx++;
    }

    return tknIx == 6;
}

// lists implementation: single and double linked

void  _Azure_SingleListInitialize(AZ_SINGLE_LIST* pL)
{
    pL->head = pL->tail = 0;
    pL->nNodes = 0;
}



void  _Azure_SingleListHeadAdd(AZ_SINGLE_LIST* pL, AZ_SGL_LIST_NODE* pN)
{
	pN->next = pL->head;
	pL->head = pN;
	if(pL->tail == 0)
	{  // empty list
		pL->tail = pN;
	}
    pL->nNodes++;
}

void  _Azure_SingleListTailAdd(AZ_SINGLE_LIST* pL, AZ_SGL_LIST_NODE* pN)
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
void  _Azure_SingleListMidAdd(AZ_SINGLE_LIST* pL, AZ_SGL_LIST_NODE* pN, AZ_SGL_LIST_NODE* after)
{
    pN->next = after->next;
    after->next = pN;
    pL->nNodes++; 
}


AZ_SGL_LIST_NODE*  _Azure_SingleListHeadRemove(AZ_SINGLE_LIST* pL)
{
	AZ_SGL_LIST_NODE* pN = pL->head;
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
AZ_SGL_LIST_NODE*  _Azure_SingleListNextRemove(AZ_SINGLE_LIST* pL, AZ_SGL_LIST_NODE* prev)
{
    AZ_SGL_LIST_NODE*  pN;

    if(prev == 0)
    {
        return _Azure_SingleListHeadRemove(pL);
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


AZ_SGL_LIST_NODE*  _Azure_SingleListNodeRemove(AZ_SINGLE_LIST* pL, AZ_SGL_LIST_NODE* pN)
{
    if(pN == pL->head)
    {
        _Azure_SingleListHeadRemove(pL);
    }
    else
    {
        AZ_SGL_LIST_NODE* prev;
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

bool _Azure_SingleListFind(AZ_SINGLE_LIST* pL, AZ_SGL_LIST_NODE* pN)
{
    AZ_SGL_LIST_NODE* node;
    for(node = pL->head; node != 0 ; node = node->next)
    {
        if(node == pN)
        {
            return true;
        }
    }

    return false;
}

void  _Azure_SingleListAppend(AZ_SINGLE_LIST* pDstL, AZ_SINGLE_LIST* pAList)
{
	AZ_SGL_LIST_NODE* pN;
	while((pN = _Azure_SingleListHeadRemove(pAList)))
	{
		_Azure_SingleListTailAdd(pDstL, pN);
	}
}



