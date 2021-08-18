<#--
/*******************************************************************************
  azureIoT_interface_idx Freemarker Template File

  Company:
    Microchip Technology Inc.

  File Name:
    azureIoT_interface_idx.h.ftl

  Summary:
    azureIoT_interface_idx Freemarker Template File

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
 
/* AzureIoT Interface Index ${__INSTANCE_NUM} Configuration*/
#define AZURE_INTERFACE_DEFAULT_INTERFACE_NAME_IDX${__INSTANCE_NUM?number}              "${.vars["AZURE_INTERFACE_DEFAULT_INTERFACE_NAME_IDX${__INSTANCE_NUM?number}"]}"

<#if .vars["AZURE_INTERFACE_DEFAULT_INTERFACE_NAME_IDX${__INSTANCE_NUM?number}"]?has_content>
    <#lt><#if .vars["AZURE_INTERFACE_DEFAULT_INTERFACE_NAME_IDX${__INSTANCE_NUM?number}"] = "ETHMAC">
        <#lt>#define TCPIP_IF_ETHMAC
    <#lt><#elseif .vars["AZURE_INTERFACE_DEFAULT_INTERFACE_NAME_IDX${__INSTANCE_NUM?number}"] = "GMAC">
        <#lt>#define TCPIP_IF_GMAC
    <#lt><#elseif .vars["AZURE_INTERFACE_DEFAULT_INTERFACE_NAME_IDX${__INSTANCE_NUM?number}"] = "EMAC0">
        <#lt>#define TCPIP_IF_EMAC0
    <#lt><#elseif .vars["AZURE_INTERFACE_DEFAULT_INTERFACE_NAME_IDX${__INSTANCE_NUM?number}"] = "EMAC1">
        <#lt>#define TCPIP_IF_EMAC1
    <#lt><#elseif .vars["AZURE_INTERFACE_DEFAULT_INTERFACE_NAME_IDX${__INSTANCE_NUM?number}"] = "MRF24WN">
        <#lt>#define TCPIP_IF_MRF24WN
    <#lt><#elseif .vars["AZURE_INTERFACE_DEFAULT_INTERFACE_NAME_IDX${__INSTANCE_NUM?number}"] = "WINC">
        <#lt>#define TCPIP_IF_WINC
    <#lt><#elseif .vars["AZURE_INTERFACE_DEFAULT_INTERFACE_NAME_IDX${__INSTANCE_NUM?number}"] = "WILC1000">
        <#lt>#define TCPIP_IF_WILC1000
    <#lt><#elseif .vars["AZURE_INTERFACE_DEFAULT_INTERFACE_NAME_IDX${__INSTANCE_NUM?number}"] = "PIC32MZW1">
        <#lt>#define TCPIP_IF_PIC32MZW1
    <#lt></#if>
</#if>

<#if .vars["AZURE_INTERFACE_DEFAULT_MAC_ADDR_IDX${__INSTANCE_NUM?number}"]?has_content>
    <#lt>#define AZURE_INTERFACE_DEFAULT_MAC_ADDR_IDX${__INSTANCE_NUM?number}           "${.vars["AZURE_INTERFACE_DEFAULT_MAC_ADDR_IDX${__INSTANCE_NUM?number}"]}"
<#else>
    <#lt>#define AZURE_INTERFACE_DEFAULT_MAC_ADDR_IDX${__INSTANCE_NUM?number}           0
</#if>
                                                    
<#lt>#define AZURE_INTERFACE_DEFAULT_DRIVER_IDX${__INSTANCE_NUM?number}                 ${.vars["AZURE_INTERFACE_DEFAULT_DRIVER_IDX${__INSTANCE_NUM?number}"]}


