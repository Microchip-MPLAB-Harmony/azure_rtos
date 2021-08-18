<#--
/*******************************************************************************
  Azuer IOT Freemarker Template File

  Company:
    Microchip Technology Inc.

  File Name:
    nx_user.h.ftl

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
<#if (NX_AZURE_ENABLE)?has_content && (NX_AZURE_ENABLE == true)>
    <#lt>/*** NetX Configuration ***/
    <#lt>#define NX_PHYSICAL_HEADER                 (16 + 4 + ${MAC_DATA_GAP_SIZE})
    <#lt>#define NX_DEMO_PACKET_SIZE                ${NX_DEMO_PACKET_SIZE}
    <#lt>#define NX_DEMO_NUMBER_OF_PACKETS          ${NX_DEMO_NUMBER_OF_PACKETS}
    <#lt>#define NX_DEMO_PACKET_POOL_SIZE           (((NX_DEMO_PACKET_SIZE) + sizeof(NX_PACKET)) * (NX_DEMO_NUMBER_OF_PACKETS))
    <#lt>#define NX_DEMO_IP_STACK_SIZE              ${NX_DEMO_IP_STACK_SIZE}
    <#lt>#define NX_DEMO_IP_THREAD_PRIORITY         ${NX_DEMO_IP_THREAD_PRIORITY}
    <#lt>#define NX_DEMO_MAX_PHYSICAL_INTERFACES    ${NX_DEMO_MAX_PHYSICAL_INTERFACES}
    <#lt>#define AZURE_NET_INTERFACES               (NX_DEMO_MAX_PHYSICAL_INTERFACES)
    
    <#if (NX_DEMO_DISABLE_LOOPBACK_INTERFACE)?has_content>
        <#if (NX_DEMO_DISABLE_LOOPBACK_INTERFACE == true)>
            <#lt>#define NX_DEMO_DISABLE_LOOPBACK_INTERFACE     1
        <#else>
            <#lt>#define NX_DEMO_DISABLE_LOOPBACK_INTERFACE     0
        </#if>
    </#if>
    <#if (NX_DEMO_DISABLE_IPV6)?has_content>
        <#if (NX_DEMO_DISABLE_IPV6 == true)>
            <#lt>#define NX_DEMO_DISABLE_IPV6       1
        <#else>
            <#lt>#define NX_DEMO_DISABLE_IPV6       0
        </#if>
    </#if>
    <#lt>#define NX_DEMO_DISABLE_IPV4               0
    <#if (NX_DEMO_ENABLE_TCP)?has_content>
        <#if (NX_DEMO_ENABLE_TCP == true)>
            <#lt>#define NX_DEMO_ENABLE_TCP         1
        <#else>
            <#lt>#define NX_DEMO_ENABLE_TCP         0
        </#if>
    </#if>
    <#if (NX_DEMO_ENABLE_UDP)?has_content>
        <#if (NX_DEMO_ENABLE_UDP == true)>
            <#lt>#define NX_DEMO_ENABLE_UDP         1
        <#else>
            <#lt>#define NX_DEMO_ENABLE_UDP         0
        </#if>
    </#if>  
    <#if (NX_DEMO_ENABLE_DHCP)?has_content>
        <#if (NX_DEMO_ENABLE_DHCP == true)>
            <#lt>#define NX_DEMO_ENABLE_DHCP            1
            <#lt>#define NX_DEMO_IPV4_ADDRESS      IP_ADDRESS(0,0,0,0)
            <#lt>#define NX_DEMO_IPV4_MASK            IP_ADDRESS(0,0,0,0)
            <#lt>#define NX_DEMO_GATEWAY_ADDRESS        IP_ADDRESS(0,0,0,0)
        <#else>
            <#lt>#define NX_DEMO_ENABLE_DHCP            0
            <#lt>#define NX_DEMO_IPV4_ADDRESS      IP_ADDRESS(${NX_DEMO_STATIC_IP_ADDRESS_COM})
            <#lt>#define NX_DEMO_IPV4_MASK            IP_ADDRESS(${NX_DEMO_SUBNET_MASK_COM})
            <#lt>#define NX_DEMO_GATEWAY_ADDRESS        IP_ADDRESS(${NX_DEMO_DEFAULT_GATEWAY_COM})
        </#if>

    </#if>  
    <#if (NX_DEMO_DISABLE_IPV6)?has_content>
        <#if (NX_DEMO_DISABLE_IPV6 == true)>
            <#lt>#define NX_DEMO_DISABLE_IPV6       1
        <#else>
            <#lt>#define NX_DEMO_DISABLE_IPV6       0
        </#if>
    </#if>  
    <#if NX_DEMO_ENABLE_DNS?has_content && NX_DEMO_ENABLE_DNS == true>
        <#lt>#define NX_DEMO_ENABLE_DNS            1
        <#if (NX_DEMO_ENABLE_DHCP == true)>
            <#lt>#define NX_DEMO_DNS_SERVER_ADDRESS             IP_ADDRESS(0,0,0,0)
        <#else>
            <#lt>#define NX_DEMO_DNS_SERVER_ADDRESS             IP_ADDRESS(${NX_DEMO_DNS_SERVER_ADDRESS_COM})
        </#if> 
        <#lt>#define NX_DNS_CLIENT_USER_CREATE_PACKET_POOL      1
    <#else>
        <#lt>#define NX_DEMO_ENABLE_DNS            0
    </#if>  
    <#lt>#define NX_DEMO_ARP_CACHE_SIZE         ${NX_DEMO_ARP_CACHE_SIZE}
    <#lt>/*** Crypto Configuration ***/ 
    <#if (NX_SECURE_ENABLE)?has_content>
        <#if (NX_SECURE_ENABLE == true)>
            <#lt>#define NX_SECURE_ENABLE       1
        <#else>
            <#lt>#define NX_SECURE_ENABLE       0
        </#if>
    </#if>      

    <#if AZURE_C_SDK_EN?has_content && AZURE_C_SDK_EN == true>
        <#lt>/*** Azure IoT embedded C SDK Configuration ***/
        <#lt>#define NX_ENABLE_EXTENDED_NOTIFY_SUPPORT
        <#lt>#define NX_ENABLE_IP_PACKET_FILTER 
        <#lt>#define NXD_MQTT_CLOUD_ENABLE
        <#lt>#define NXD_MQTT_PING_TIMEOUT_DELAY        500
        <#lt>#define NXD_MQTT_SOCKET_TIMEOUT            0
    </#if>

    <#lt>#define NX_ENABLE_INTERFACE_CAPABILITY

</#if>
#endif  // NX_USER_H
