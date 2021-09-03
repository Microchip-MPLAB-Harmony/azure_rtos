/*******************************************************************************
  WINC Wireless Driver OS Abstraction Layer

  File Name:
    wdrv_winc_osal.c

  Summary:
    OS abstraction layer for WINC wireless driver.

  Description:
    OS abstraction layer for WINC wireless driver.
 *******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "osal/osal.h"
#include "wdrv_winc_common.h"

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
*   Depending upon the OSAL mode,
*   a support level specific implementation file is included by this
*   file to give the required level of compatibility. The available
*   support levels include, OSAL_USE_NONE, OSAL_USE_BASIC, and
*   OSAL_USE_RTOS.
*******************************************************************************/
#define OSAL_USE_NONE        0
#define OSAL_USE_BASIC       0
#define OSAL_USE_RTOS        0

/* *****************************************************************************/

/* Blocking delay using Harmony Timer Service */
static void _harmony_blocking_delay(uint32_t ms)
{
  SYS_TIME_HANDLE tmrHandle = SYS_TIME_HANDLE_INVALID;

  if (SYS_TIME_SUCCESS != SYS_TIME_DelayMS(ms, &tmrHandle))
  {
    return;
  }

  while (true != SYS_TIME_DelayIsComplete(tmrHandle))
  {
  }
}

/* Implement a Bare metal or RTOS specific delay */
void WDRV_MSDelay(uint32_t ms)
{
    if ((ms / (TX_TICK_PERIOD_MS)) < 1)
    {
        _harmony_blocking_delay(ms);
    }
    else
    {
         tx_thread_sleep(ms / (TX_TICK_PERIOD_MS));
    }
}
