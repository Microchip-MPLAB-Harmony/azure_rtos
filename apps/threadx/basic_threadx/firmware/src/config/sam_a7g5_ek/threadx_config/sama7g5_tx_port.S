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

    .extern      _tx_thread_vectored_context_save
    .extern      _tx_thread_context_restore

    .global      ThreadX_IRQ_Handler

//------------------------------------------------------------------------------
//         Definitions
//------------------------------------------------------------------------------

#define GICC_BASE        0xE8C12000
#define GICC_IAR         0x0C
#define GICC_EOIR        0x10

#define ARM_MODE_IRQ     0x12
#define ARM_MODE_SVC     0x13

#define I_BIT            0x80
#define F_BIT            0x40

//------------------------------------------------------------------------------
//         ThreadX IRQ handler routine
//------------------------------------------------------------------------------
	.TEXT
    .ARM
ThreadX_IRQ_Handler:
	/* Jump to context save to save system context.  */
	STMDB   sp!, {r0-r3}                    /* Save some scratch registers */
	MRS     r0, SPSR                        /* Pickup saved SPSR */
	SUB     lr, lr, #4                      /* Adjust point of interrupt */
	STMDB   sp!, {r0, r10, r12, lr}         /* Store other registers */
	LDR     r0, =_tx_thread_vectored_context_save
	BLX     r0                              /* Call vectored context save */

    // Change to supervisor mode to allow reentry.
    CPS     #ARM_MODE_SVC

    // Push used registers.
    PUSH    {r0-r4, r12}

    // Acknowledge the interrupt and get the interrupt ID
    LDR     r1, =GICC_BASE
    LDR     r0, [r1, #GICC_IAR]
    
    // Synchronize access upto this point
    DSB

    // Save r0(we need its value to mark EOI) and lr
    PUSH    {r0, lr}
    
    // Jump to Handler
    LDR    r1, =GIC_IRQHandler
    BLX    r1
    
    // Pop back r0 and lr
    POP    {r0, lr}

    // Disable interrupt if enabled by the IRQ handler
    CPSID    i

    // Write the value read from ICCIAR to ICCEOIR
    LDR    r1, =GICC_BASE
    STR    r0, [r1, #GICC_EOIR]

    // Restore used registers
    POP    {r0-r4, r12}
    
    // Switch back to IRQ mode
    CPS    #ARM_MODE_IRQ
    
	/* Jump to context restore to restore system context.  */
	LDR     r0,=_tx_thread_context_restore
	BX      r0                              /* Jump to context restore */

	.END
