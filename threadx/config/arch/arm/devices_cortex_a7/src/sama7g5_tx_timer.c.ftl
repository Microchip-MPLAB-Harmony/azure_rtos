/*******************************************************************************
  ThreadX timer tick handler

  Company:
    Microchip Technology Inc.

  File Name:
    sama7g5_tx_timer.c

  Summary:
    Provides Threadx timer tick handler.

  Description:
    This file contains functional implementations of the Timer tick handler for Threadx.

*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2021 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section lists the other files that are included in this file.
 */
#include "definitions.h"

// *****************************************************************************
extern void _tx_timer_interrupt(void);

// *****************************************************************************
// *****************************************************************************
// Section: Function Routines
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
/* Function: void Threadx_Tick_Handler(void)

  Summary:
    Threadx Tick Handler.

  Description:
    This function must be installed as Threadx tick handler for the Generic Timer
    used to generate the tick interrupt.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    None

 */
void Threadx_Tick_Handler(void)
{
    uint64_t currentCompVal = 0;

    /* Call ThreadX timer interrupt processing.  */
    _tx_timer_interrupt();

    currentCompVal = PL1_GetPhysicalCompareValue();
    PL1_SetPhysicalCompareValue(currentCompVal + (GENERIC_TIMER_CounterFrequencyGet() / ${THREADX_TICK_RATE_HZ}));
}
