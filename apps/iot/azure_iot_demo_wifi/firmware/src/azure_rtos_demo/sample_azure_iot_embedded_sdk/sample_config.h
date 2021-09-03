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

#ifndef SAMPLE_CONFIG_H
#define SAMPLE_CONFIG_H

#ifdef __cplusplus
extern   "C" {
#endif

/*** Azure IoT embedded C SDK Configuration ***/
#define MODULE_ID              ""
/* Required when DPS is not used.  */
/* These values can be picked from device connection string which is of format : HostName=<host1>;DeviceId=<device1>;SharedAccessKey=<key1>
HOST_NAME can be set to <host1>,
DEVICE_ID can be set to <device1>,
DEVICE_SYMMETRIC_KEY can be set to <key1>.  */
#define HOST_NAME                      ""
#define DEVICE_ID                      ""
    
#define DEVICE_SYMMETRIC_KEY           ""           
    
#define NX_AZURE_IOT_STACK_SIZE                (2048)
#define NX_AZURE_IOT_THREAD_PRIORITY           (4) 
#define SAMPLE_STACK_SIZE                      (2048)
#define SAMPLE_THREAD_PRIORITY                 (16)
#define MAX_PROPERTY_COUNT                     (2)

#ifdef __cplusplus
}
#endif
#endif /* SAMPLE_CONFIG_H */