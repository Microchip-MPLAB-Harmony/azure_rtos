/**************************************************************************/
/*                                                                        */
/*       Copyright (c) Microsoft Corporation. All rights reserved.        */
/*                                                                        */
/*       This software is licensed under the Microsoft Software License   */
/*       Terms for Microsoft Azure RTOS. Full text of the license can be  */
/*       found in the LICENSE file at https://aka.ms/AzureRTOS_EULA       */
/*       and in the root directory of this software.                      */
/*                                                                        */
/**************************************************************************/


/**************************************************************************/
/**************************************************************************/
/**                                                                       */ 
/** NetX Component                                                        */
/**                                                                       */
/**   User Specific                                                       */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/



#ifndef NX_USER_H
#define NX_USER_H

// extra space for packet gap
// TODO aa: should be 14 + 4 + _TCPIP_MAC_DATA_SEGMENT_GAP_SIZE !
#define NX_PHYSICAL_HEADER                  (16 + 8)    /* Maximum physical header        */

// main NX pool
#define NX_MAIN_POOL_PACKET_SIZE            (1536)

#define NX_MAIN_POOL_PACKETS_NO             (70)

#define NX_MAIN_POOL_SIZE                   ((NX_MAIN_POOL_PACKET_SIZE + sizeof(NX_PACKET)) * NX_MAIN_POOL_PACKETS_NO)


#define NXD_MQTT_CLOUD_ENABLE
#define NX_SECURE_ENABLE

#endif  // NX_USER_H

