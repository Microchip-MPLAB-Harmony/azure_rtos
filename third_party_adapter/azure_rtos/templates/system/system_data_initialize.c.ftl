<#----------------------------------------------------------------------------
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
---------------------------------------------------------------------------->

const AZURE_GLUE_NETWORK_CONFIG azure_net_config[] = 
{
    <#if (NX_DEMO_MAX_PHYSICAL_INTERFACES)?has_content>
        <#list 0..(NX_DEMO_MAX_PHYSICAL_INTERFACES- 1) as i>
            <#assign interfaceEnabled = "lib_azure_rtos_${i}">
            <#assign interface_name_idx = "lib_azure_rtos_${i}.AZURE_INTERFACE_DEFAULT_INTERFACE_NAME_IDX${i}"?eval>            
            <#if .vars[interfaceEnabled]?has_content>
                <#lt>/*** Interface ${i} Configuration  ***/                    
                <#lt>{
                <#lt>   .macAddr = AZURE_INTERFACE_DEFAULT_MAC_ADDR_IDX${i},
                <#lt>   .pMacObject = &AZURE_INTERFACE_DEFAULT_DRIVER_IDX${i},
                <#if (interface_name_idx == "GMAC")>                        
                <#lt>   .pMacInit = &tcpipMACPIC32CINTInitData,
                <#lt>   .macInitSize = sizeof(tcpipMACPIC32CINTInitData),
                <#lt>   .macIrq = GMAC_IRQn,
                <#lt>   .macRxMaxFrame = TCPIP_GMAC_RX_MAX_FRAME,
                <#elseif (interface_name_idx == "ETHMAC")>  
                <#lt>   .pMacInit = &tcpipMACPIC32INTInitData,
                <#lt>   .macInitSize = sizeof(tcpipMACPIC32INTInitData),
                <#lt>   .macIrq = DRV_ETHMAC_INTERRUPT_SOURCE,
                <#lt>   .macRxMaxFrame = TCPIP_EMAC_MAX_FRAME,
                <#elseif (interface_name_idx == "EMAC0")>   
                <#lt>   .pMacInit = &tcpipEMAC0InitData,
                <#lt>   .macInitSize = sizeof(tcpipEMAC0InitData),
                <#lt>   .macIrq = DRV_EMAC0_INTERRUPT_SOURCE,
                <#lt>   .macRxMaxFrame = TCPIP_EMAC_MAX_FRAME,
                <#elseif (interface_name_idx == "EMAC1")>   
                <#lt>   .pMacInit = &tcpipEMAC1InitData,
                <#lt>   .macInitSize = sizeof(tcpipEMAC1InitData),
                <#lt>   .macIrq = DRV_EMAC1_INTERRUPT_SOURCE,
                <#lt>   .macRxMaxFrame = TCPIP_EMAC_MAX_FRAME,
                <#elseif (interface_name_idx == "WINC")>   
                <#lt>   .pMacInit = 0,
                <#lt>   .macInitSize = 0,
                <#lt>   .macIrq = 0,
                <#lt>   .macRxMaxFrame = 1518,
                <#elseif (interface_name_idx == "WINC (Lite)")>   
                <#lt>   .pMacInit = 0,
                <#lt>   .macInitSize = 0,
                <#lt>   .macIrq = 0,
                <#lt>   .macRxMaxFrame = 1518,
                </#if>                       
                <#lt>},
            </#if>
        </#list>
    </#if>
};

const AZURE_GLUE_INIT azure_glue_init = 
{
    .nNets = sizeof(azure_net_config) / sizeof(*azure_net_config),
    .pNetConf = azure_net_config,
};