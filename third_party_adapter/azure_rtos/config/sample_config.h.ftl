<#--
/*******************************************************************************
  Azuer IOT Freemarker Template File

  Company:
    Microchip Technology Inc.

  File Name:
    sample_config.h.ftl

  Summary:
    Azuer IOT Freemarker Template File

  Description:

*******************************************************************************/
-->

<#----------------------------------------------------------------------------
 Copyright (C) 2021 Microchip Technology Inc. and its subsidiaries.

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
----------------------------------------------------------------------------->
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

<#if AZURE_C_SDK_EN?has_content && AZURE_C_SDK_EN == true>
    <#lt>/*** Azure IoT embedded C SDK Configuration ***/
    <#lt>#define MODULE_ID              "${MODULE_ID}"
    <#if ENABLE_DPS_SAMPLE?has_content>
        <#if ENABLE_DPS_SAMPLE == true> 
            <#lt>/* Required when DPS is used.  */
            <#lt>#define ENABLE_DPS_SAMPLE
            <#lt>#define ENDPOINT                       "${ENDPOINT}"
            <#lt>#define ID_SCOPE                       "${ID_SCOPE}"
            <#lt>#define REGISTRATION_ID                "${REGISTRATION_ID}"
            <#lt>#define SAMPLE_MAX_BUFFER              (${SAMPLE_MAX_BUFFER})
            
        <#else>
            <#lt>/* Required when DPS is not used.  */
            <#lt>/* These values can be picked from device connection string which is of format : HostName=<host1>;DeviceId=<device1>;SharedAccessKey=<key1>
            <#lt>HOST_NAME can be set to <host1>,
            <#lt>DEVICE_ID can be set to <device1>,
            <#lt>DEVICE_SYMMETRIC_KEY can be set to <key1>.  */
            <#lt>#define HOST_NAME                      "${HOST_NAME}"
            <#lt>#define DEVICE_ID                      "${DEVICE_ID}"
        </#if>
    </#if>
    
    <#if NX_AZURE_C_SDK_DEV_SECURITY?has_content>
        <#if NX_AZURE_C_SDK_DEV_SECURITY == "X.509_Certificate">
            <#lt>/* This sample uses Symmetric key (SAS) to connect to IoT Hub by default,
            <#lt>simply defining USE_DEVICE_CERTIFICATE and setting your device certificate in sample_device_identity.c
            <#lt>to connect to IoT Hub with x509 certificate. Set up X.509 security in your Azure IoT Hub,
            <#lt>refer to https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-security-x509-get-started  */
            <#lt>#define USE_DEVICE_CERTIFICATE         1
        <#else>
            <#lt>#define DEVICE_SYMMETRIC_KEY           "${DEVICE_SYMMETRIC_KEY}"           
        </#if>
    </#if>
    
    <#lt>#define NX_AZURE_IOT_STACK_SIZE                (${NX_AZURE_IOT_STACK_SIZE})
    <#lt>#define NX_AZURE_IOT_THREAD_PRIORITY           (${NX_AZURE_IOT_THREAD_PRIORITY}) 
    <#lt>#define SAMPLE_STACK_SIZE                      (${SAMPLE_STACK_SIZE})
    <#lt>#define SAMPLE_THREAD_PRIORITY                 (${SAMPLE_THREAD_PRIORITY})
    <#lt>#define MAX_PROPERTY_COUNT                     (${MAX_PROPERTY_COUNT})
</#if>

#ifdef __cplusplus
}
#endif
#endif /* SAMPLE_CONFIG_H */