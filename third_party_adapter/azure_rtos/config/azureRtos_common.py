"""*****************************************************************************
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
*****************************************************************************"""
import os

azure_visibility = False

def instantiateComponent(azureIOTComponent):
    global azureNetXInterfaceNum
    configName = Variables.get("__CONFIGURATION_NAME") 
    
    # Activate Harmony Core
    if(Database.getComponentByID("HarmonyCore") == None):
        res = Database.activateComponents(["HarmonyCore"])
    # Enable "Generate Harmony Driver Common Files" option in MHC
    if (Database.getSymbolValue("HarmonyCore", "ENABLE_DRV_COMMON") == False):
        Database.setSymbolValue("HarmonyCore", "ENABLE_DRV_COMMON", True)

    # Enable "Generate Harmony System Service Common Files" option in MHC
    if (Database.getSymbolValue("HarmonyCore", "ENABLE_SYS_COMMON") == False):
        Database.setSymbolValue("HarmonyCore", "ENABLE_SYS_COMMON", True)
        
    # Enable "Enable System Interrupt" option in MHC
    if (Database.getSymbolValue("HarmonyCore", "ENABLE_SYS_INT") == False):
        Database.setSymbolValue("HarmonyCore", "ENABLE_SYS_INT", True)
        
    # Enable "Enable OSAL" option in MHC
    if (Database.getSymbolValue("HarmonyCore", "ENABLE_OSAL") == False):
        Database.setSymbolValue("HarmonyCore", "ENABLE_OSAL", True)
    
    device_node = ATDF.getNode('/avr-tools-device-file/devices/device')
    dev_architecture = str(device_node.getAttribute("architecture"))
    if dev_architecture == "CORTEX-M4":
        arch = "cortex_m4" 
    elif dev_architecture == "CORTEX-M7":
        arch = "cortex_m7"
    # No support added from PIC32M devices as no port avialable for netxduo and filex

    compiler_choice = Database.getComponentByID("core").getSymbolByID("COMPILER_CHOICE")
    if compiler_choice.getSelectedKey() == "XC32":
        toolchain = "gnu"
    elif compiler_choice.getSelectedKey() == "IAR":
        toolchain = "iar"
    elif compiler_choice.getSelectedKey() == "KEIL":
        toolchain = "keil"
    # Enable AzureRtos
    azureNetXEnable = azureIOTComponent.createBooleanSymbol("NX_AZURE_ENABLE", None) 
    azureNetXEnable.setLabel("Enable AzureRtos")
    azureNetXEnable.setVisible(False)
    azureNetXEnable.setDescription("Enable AzureRtos")
    azureNetXEnable.setDefaultValue(True)
    
    azureDemoConfig = azureIOTComponent.createMenuSymbol("AZURE_DEMO_MENU", None)
    azureDemoConfig.setLabel("Demo Configurations")
    azureDemoConfig.setVisible(True)
    
    azureNetXMenu = azureIOTComponent.createMenuSymbol("AZURE_NETX_MENU", azureDemoConfig)
    azureNetXMenu.setLabel("NetX Duo")
    azureNetXMenu.setVisible(True)
    
    # Size of NetX pool packet
    azureNetXPoolPacketSize = azureIOTComponent.createIntegerSymbol("NX_DEMO_PACKET_SIZE", azureNetXMenu)
    azureNetXPoolPacketSize.setLabel("Packet Payload Size")
    azureNetXPoolPacketSize.setVisible(True)
    azureNetXPoolPacketSize.setDescription("Packet Payload Size")
    azureNetXPoolPacketSize.setDefaultValue(1536)
    
    # MAC Data segment gap size
    azureNetXMacDataSegGapSize = azureIOTComponent.createIntegerSymbol("MAC_DATA_GAP_SIZE", azureNetXMenu)
    azureNetXMacDataSegGapSize.setLabel("MAC Data segment gap size")
    azureNetXMacDataSegGapSize.setVisible(False)
    azureNetXMacDataSegGapSize.setDefaultValue(4)
    
    # Number of packets in pool
    azureNetXPoolPacketNum = azureIOTComponent.createIntegerSymbol("NX_DEMO_NUMBER_OF_PACKETS", azureNetXMenu)
    azureNetXPoolPacketNum.setLabel("Number of Packets in Pool")
    azureNetXPoolPacketNum.setVisible(True)
    azureNetXPoolPacketNum.setDescription("Number of packets in pool")
    azureNetXPoolPacketNum.setDefaultValue(60)    

    # Stack size of IP thread 
    azureNetXIpThreadStackSize = azureIOTComponent.createIntegerSymbol("NX_DEMO_IP_STACK_SIZE", azureNetXMenu)
    azureNetXIpThreadStackSize.setLabel("IP Thread Stack Size")
    azureNetXIpThreadStackSize.setVisible(True)
    azureNetXIpThreadStackSize.setDescription("Stack size of IP thread")
    azureNetXIpThreadStackSize.setDefaultValue(2048)        

    # IP thread Priority
    azureNetXIpThreadPriority = azureIOTComponent.createIntegerSymbol("NX_DEMO_IP_THREAD_PRIORITY", azureNetXMenu)
    azureNetXIpThreadPriority.setLabel("IP Thread Priority")
    azureNetXIpThreadPriority.setVisible(True)
    azureNetXIpThreadPriority.setDescription("Priority of IP thread")
    azureNetXIpThreadPriority.setDefaultValue(1) 

    # Number of Interfaces
    azureNetXInterfaceNum = azureIOTComponent.createIntegerSymbol("NX_DEMO_MAX_PHYSICAL_INTERFACES", azureNetXMenu)
    azureNetXInterfaceNum.setLabel("Number of Interfaces")
    azureNetXInterfaceNum.setVisible(True)
    azureNetXInterfaceNum.setDescription("Number of Interfaces")
    azureNetXInterfaceNum.setDefaultValue(1)     

    # Disable Loopback
    azureNetXLoopBackDisable = azureIOTComponent.createBooleanSymbol("NX_DEMO_DISABLE_LOOPBACK_INTERFACE", azureNetXMenu)
    azureNetXLoopBackDisable.setLabel("Disable Loopback")
    azureNetXLoopBackDisable.setVisible(True)
    azureNetXLoopBackDisable.setDescription("Disable Loopback")
    azureNetXLoopBackDisable.setDefaultValue(False) 

    # Disable IPv6
    azureNetXIpv6Disable = azureIOTComponent.createBooleanSymbol("NX_DEMO_DISABLE_IPV6", azureNetXMenu)
    azureNetXIpv6Disable.setLabel("Disable IPv6")
    azureNetXIpv6Disable.setVisible(True)
    azureNetXIpv6Disable.setDescription("Disable IPv6")
    azureNetXIpv6Disable.setDefaultValue(False) 

    # Enable DHCP 
    azureNetXDhcpEnable = azureIOTComponent.createBooleanSymbol("NX_DEMO_ENABLE_DHCP", azureNetXMenu)
    azureNetXDhcpEnable.setLabel("Enable DHCP")
    azureNetXDhcpEnable.setVisible(True)
    azureNetXDhcpEnable.setDescription("Enable DHCP")
    azureNetXDhcpEnable.setDefaultValue(True)  

    # Static IP Address
    azureNetXStaticIpAddress = azureIOTComponent.createStringSymbol("NX_DEMO_IPV4_ADDRESS", azureNetXDhcpEnable)
    azureNetXStaticIpAddress.setLabel("Static IP Address")
    azureNetXStaticIpAddress.setVisible(False)
    azureNetXStaticIpAddress.setDefaultValue("192.168.1.10")
    azureNetXStaticIpAddress.setDescription("Static IP Address")
    azureNetXStaticIpAddress.setDependencies(azureNetXMenuInvisibility, ["NX_DEMO_ENABLE_DHCP"])
    ip_addr_comma = azureNetXStaticIpAddress.getValue().replace(".", ",")
    
    # Static IP Address Comma Separator
    azureNetXStaticIpAddressComma = azureIOTComponent.createStringSymbol("NX_DEMO_STATIC_IP_ADDRESS_COM", azureNetXDhcpEnable)
    azureNetXStaticIpAddressComma.setLabel("IP Address Comma Separator")
    azureNetXStaticIpAddressComma.setVisible(False)
    azureNetXStaticIpAddressComma.setDefaultValue(ip_addr_comma)
    azureNetXStaticIpAddressComma.setDependencies(azureNetXIPComConverter, ["NX_DEMO_IPV4_ADDRESS"])
        
    # Subnet Mask
    azureNetXSubnetMask = azureIOTComponent.createStringSymbol("NX_DEMO_IPV4_MASK", azureNetXDhcpEnable)
    azureNetXSubnetMask.setLabel("Subnet Mask")
    azureNetXSubnetMask.setVisible(False)
    azureNetXSubnetMask.setDefaultValue("255.255.255.0")
    azureNetXSubnetMask.setDescription("Subnet Mask")
    azureNetXSubnetMask.setDependencies(azureNetXMenuInvisibility, ["NX_DEMO_ENABLE_DHCP"])
    subNetMask_comma = azureNetXSubnetMask.getValue().replace(".", ",")

    # Subnet Mask Comma Separator
    azureNetXSubnetMaskComma = azureIOTComponent.createStringSymbol("NX_DEMO_SUBNET_MASK_COM", azureNetXDhcpEnable)
    azureNetXSubnetMaskComma.setLabel("Subnet Mask Comma Separator")
    azureNetXSubnetMaskComma.setVisible(False)
    azureNetXSubnetMaskComma.setDefaultValue(subNetMask_comma)
    azureNetXSubnetMaskComma.setDependencies(azureNetXIPComConverter, ["NX_DEMO_IPV4_MASK"])
    
    # Default Gateway
    azureNetXDefaultGateway = azureIOTComponent.createStringSymbol("NX_DEMO_GATEWAY_ADDRESS", azureNetXDhcpEnable)
    azureNetXDefaultGateway.setLabel("Default Gateway")
    azureNetXDefaultGateway.setVisible(False)
    azureNetXDefaultGateway.setDefaultValue("192.168.1.1")
    azureNetXDefaultGateway.setDescription("Default Gateway")
    azureNetXDefaultGateway.setDependencies(azureNetXMenuInvisibility, ["NX_DEMO_ENABLE_DHCP"])
    dfltGateway_comma = azureNetXDefaultGateway.getValue().replace(".", ",")
    
    # Default Gateway Comma Separator
    azureNetXDefaultGatewayComma = azureIOTComponent.createStringSymbol("NX_DEMO_DEFAULT_GATEWAY_COM", azureNetXDhcpEnable)
    azureNetXDefaultGatewayComma.setLabel("Default Gateway Comma Separator")
    azureNetXDefaultGatewayComma.setVisible(False)
    azureNetXDefaultGatewayComma.setDefaultValue(dfltGateway_comma)    
    azureNetXDefaultGatewayComma.setDependencies(azureNetXIPComConverter, ["NX_DEMO_GATEWAY_ADDRESS"])
    
    # Enable DNS 
    azureNetXDnsEnable = azureIOTComponent.createBooleanSymbol("NX_DEMO_ENABLE_DNS", azureNetXMenu)
    azureNetXDnsEnable.setLabel("Enable DNS")
    azureNetXDnsEnable.setVisible(True)
    azureNetXDnsEnable.setDescription("Enable DNS")
    azureNetXDnsEnable.setDefaultValue(True)  
    
    # DNS Server IP Address
    azureNetXDnsIpAddress = azureIOTComponent.createStringSymbol("NX_DEMO_DNS_SERVER_ADDRESS", azureNetXDnsEnable)
    azureNetXDnsIpAddress.setLabel("DNS Server IP Address")
    azureNetXDnsIpAddress.setVisible(True)
    azureNetXDnsIpAddress.setDefaultValue("192.168.1.1")
    azureNetXDnsIpAddress.setDescription("DNS Server IP Address")
    azureNetXDnsIpAddress.setDependencies(azureNetXMenuVisibility, ["NX_DEMO_ENABLE_DNS"])
    dnsIpAddr_comma = azureNetXDnsIpAddress.getValue().replace(".", ",")
    
    # DNS Server IP Address Comma Separator
    azureNetXDnsIpAddressComma = azureIOTComponent.createStringSymbol("NX_DEMO_DNS_SERVER_ADDRESS_COM", azureNetXDnsEnable)
    azureNetXDnsIpAddressComma.setLabel("DNS Server IP Address Comma Separator")
    azureNetXDnsIpAddressComma.setVisible(False)
    azureNetXDnsIpAddressComma.setDefaultValue(dnsIpAddr_comma)
    azureNetXDnsIpAddressComma.setDependencies(azureNetXIPComConverter, ["NX_DEMO_DNS_SERVER_ADDRESS"])

    # Enable TCP 
    azureNetXTcpEnable = azureIOTComponent.createBooleanSymbol("NX_DEMO_ENABLE_TCP", azureNetXMenu)
    azureNetXTcpEnable.setLabel("Enable TCP")
    azureNetXTcpEnable.setVisible(True)
    azureNetXTcpEnable.setDescription("Enable TCP")
    azureNetXTcpEnable.setDefaultValue(True)      

    # Enable UDP 
    azureNetXUdpEnable = azureIOTComponent.createBooleanSymbol("NX_DEMO_ENABLE_UDP", azureNetXMenu)
    azureNetXUdpEnable.setLabel("Enable UDP")
    azureNetXUdpEnable.setVisible(True)
    azureNetXUdpEnable.setDescription("Enable UDP")
    azureNetXUdpEnable.setDefaultValue(True) 

    # ARP cache size
    azureNetXArpCacheSize = azureIOTComponent.createIntegerSymbol("NX_DEMO_ARP_CACHE_SIZE", azureNetXMenu)
    azureNetXArpCacheSize.setLabel("ARP cache size")
    azureNetXArpCacheSize.setVisible(True)
    azureNetXArpCacheSize.setDescription("ARP cache size")
    azureNetXArpCacheSize.setDefaultValue(1024)   
    
    azureNetXAddonMenu = azureIOTComponent.createMenuSymbol("AZURE_NETX_ADDON_MENU", azureNetXMenu)
    azureNetXAddonMenu.setLabel("Addons")
    azureNetXAddonMenu.setVisible(azure_visibility)
    
    azureNetXPreProcessorIncludeUsrFile = azureIOTComponent.createSettingSymbol("AZURE_PRE_PROC_INCL_USR_FILE", None)
    azureNetXPreProcessorIncludeUsrFile.setCategory("C32")
    azureNetXPreProcessorIncludeUsrFile.setKey("preprocessor-macros")
    azureNetXPreProcessorIncludeUsrFile.setValue("NX_INCLUDE_USER_DEFINE_FILE")
    azureNetXPreProcessorIncludeUsrFile.setAppend(True, ";")
    
    
    h3_dir = Variables.get("__FRAMEWORK_DIR")
    netxDuo_dir = os.path.join(h3_dir, "netxduo")
    netxDuoAddonSourcePath = os.path.join(netxDuo_dir, "addons")
    for name in os.listdir(netxDuoAddonSourcePath) :
        if os.path.isdir(os.path.join(netxDuoAddonSourcePath, name)) :
            addon =  name.upper()                
            # Enable Add-Ons
            azureNetXAddonEnable = azureIOTComponent.createBooleanSymbol(addon + "_ENABLE", azureNetXAddonMenu)
            azureNetXAddonEnable.setLabel(name)
            azureNetXAddonEnable.setVisible(azure_visibility)
            azureNetXAddonEnable.setDescription(name)
            azureNetXAddonEnable.setDefaultValue(False)   
            
            netxDuoAddonPath = azureIOTComponent.createSettingSymbol("AZURE_ADDON_PATH_" + addon, None)
            netxDuoAddonPath.setValue("../src/third_party/azure_rtos/netxduo/addons/" + name)
            netxDuoAddonPath.setCategory("C32")
            netxDuoAddonPath.setKey("extra-include-directories")
            netxDuoAddonPath.setAppend(True, ";")
            netxDuoAddonPath.setEnabled(False)
            netxDuoAddonPath.setDependencies(azureNetXPathEnable, [addon + "_ENABLE"])

    netxDuoAddonIotSecurityPath = azureIOTComponent.createSettingSymbol("NETX_ADDON_IOT_SECURITY_PATH", None)
    netxDuoAddonIotSecurityPath.setValue("../src/third_party/azure_rtos/netxduo/addons/azure_iot/azure_iot_security_module;../src/third_party/azure_rtos/netxduo/addons/azure_iot/azure_iot_security_module/inc;../src/third_party/azure_rtos/netxduo/addons/azure_iot/azure_iot_security_module/inc/configs/RTOS_BASE_UT;../src/third_party/azure_rtos/netxduo/addons/azure_iot/azure_iot_security_module/iot-security-module-core/deps/flatcc/include;../src/third_party/azure_rtos/netxduo/addons/azure_iot/azure_iot_security_module/iot-security-module-core/inc")
    netxDuoAddonIotSecurityPath.setCategory("C32")
    netxDuoAddonIotSecurityPath.setKey("extra-include-directories")
    netxDuoAddonIotSecurityPath.setAppend(True, ";")
    netxDuoAddonIotSecurityPath.setEnabled(False)
    netxDuoAddonIotSecurityPath.setDependencies(azureNetXPathEnable, ["AZURE_IOT_ENABLE"])
    
    netxCryptoSourcePath = os.path.join(netxDuo_dir, "crypto_libraries")
    # Enable NetX Crypto Libraries
    azureNetXCryptoLibraryEnable = azureIOTComponent.createBooleanSymbol("NX_CRYPTO_LIB_ENABLE", azureNetXMenu)
    azureNetXCryptoLibraryEnable.setLabel("NetX Crypto")
    azureNetXCryptoLibraryEnable.setVisible(azure_visibility)
    azureNetXCryptoLibraryEnable.setDescription("Enable NetX Crypto Libraries")
    azureNetXCryptoLibraryEnable.setDefaultValue(False) 

    azureNetXCryptoPath = azureIOTComponent.createSettingSymbol("NETX_CRYPTO_INCLUDE_PATH", None)
    azureNetXCryptoPath.setValue("../src/third_party/azure_rtos/netxduo/crypto_libraries/inc")
    azureNetXCryptoPath.setCategory("C32")
    azureNetXCryptoPath.setKey("extra-include-directories")
    azureNetXCryptoPath.setAppend(True, ";")
    azureNetXCryptoPath.setEnabled(False)
    azureNetXCryptoPath.setDependencies(azureNetXPathEnable, ["NX_CRYPTO_LIB_ENABLE"])
    
    netxSecureSourcePath = os.path.join(netxDuo_dir, "nx_secure")
    # Enable NetX Secure
    azureNetXSecureEnable = azureIOTComponent.createBooleanSymbol("NX_SECURE_ENABLE", azureNetXMenu)
    azureNetXSecureEnable.setLabel("NetX Secure")
    azureNetXSecureEnable.setVisible(azure_visibility)
    azureNetXSecureEnable.setDescription("Enable NetX Secure")
    azureNetXSecureEnable.setDefaultValue(False) 
    
    azureNetXSecurePath = azureIOTComponent.createSettingSymbol("NETX_SECURE_INCLUDE_PATH", None)
    azureNetXSecurePath.setValue("../src/third_party/azure_rtos/netxduo/nx_secure/inc;../src/third_party/azure_rtos/netxduo/nx_secure/ports")
    azureNetXSecurePath.setCategory("C32")
    azureNetXSecurePath.setKey("extra-include-directories")
    azureNetXSecurePath.setAppend(True, ";")
    azureNetXSecurePath.setEnabled(False)
    azureNetXSecurePath.setDependencies(azureNetXPathEnable, ["NX_SECURE_ENABLE"])
    
    filex_dir = os.path.join(h3_dir, "filex")
    # filex Enable 
    azurefilexEnable = azureIOTComponent.createBooleanSymbol("AZURE_FILEX_ENABLE", None)
    azurefilexEnable.setLabel("FileX")
    azurefilexEnable.setVisible(True)
    azurefilexEnable.setDescription("Azure RTOS FileX Enable")
    azurefilexEnable.setDefaultValue(False) 
    
    azurefilexPath = azureIOTComponent.createSettingSymbol("AZURE_FILEX_PATH", None)
    azurefilexPath.setValue("../src/third_party/azure_rtos/filex/common/inc;../src/third_party/azure_rtos/filex/ports/" + arch + "/gnu/inc")
    azurefilexPath.setCategory("C32")
    azurefilexPath.setKey("extra-include-directories")
    azurefilexPath.setAppend(True, ";")
    azurefilexPath.setEnabled(False)
    azurefilexPath.setDependencies(azureNetXPathEnable, ["NX_SECURE_ENABLE"])

    # Azure IoT Embedded C-SDK Enable 
    azureCSdkEnable = azureIOTComponent.createBooleanSymbol("AZURE_C_SDK_EN", azureDemoConfig)
    azureCSdkEnable.setLabel("Azure IoT embedded C SDK")
    azureCSdkEnable.setVisible(True)
    azureCSdkEnable.setDescription("Azure IoT Embedded C-SDK Enable ")
    azureCSdkEnable.setDefaultValue(False)     
    azureCSdkEnable.setDependencies(azureNetXCSdkEnable, ["AZURE_C_SDK_EN"])

    # Azure IoT Thread Priority
    azureNetXCSdkThreadPriority = azureIOTComponent.createIntegerSymbol("NX_AZURE_IOT_THREAD_PRIORITY", azureCSdkEnable)
    azureNetXCSdkThreadPriority.setLabel("Azure IoT Thread Priority")
    azureNetXCSdkThreadPriority.setVisible(False)
    azureNetXCSdkThreadPriority.setDescription("Azure IoT Thread Priority")
    azureNetXCSdkThreadPriority.setDefaultValue(4) 
    azureNetXCSdkThreadPriority.setDependencies(azureNetXCSdkMenuVisibility, ["AZURE_C_SDK_EN"])
    
    # Azure IoT Thread Stack Size
    azureNetXCSdkThreadStackSize = azureIOTComponent.createIntegerSymbol("NX_AZURE_IOT_STACK_SIZE", azureCSdkEnable)
    azureNetXCSdkThreadStackSize.setLabel("Azure IoT Thread Stack Size")
    azureNetXCSdkThreadStackSize.setVisible(False)
    azureNetXCSdkThreadStackSize.setDescription("Azure IoT Thread Stack Size")
    azureNetXCSdkThreadStackSize.setDefaultValue(2048) 
    azureNetXCSdkThreadStackSize.setDependencies(azureNetXCSdkMenuVisibility, ["AZURE_C_SDK_EN"])

    # Sample Thread Priority
    sampleThreadPriority = azureIOTComponent.createIntegerSymbol("SAMPLE_THREAD_PRIORITY", azureCSdkEnable)
    sampleThreadPriority.setLabel("Sample Thread Priority")
    sampleThreadPriority.setVisible(False)
    sampleThreadPriority.setDescription("Sample Thread Priority")
    sampleThreadPriority.setDefaultValue(16) 
    sampleThreadPriority.setDependencies(azureNetXCSdkMenuVisibility, ["AZURE_C_SDK_EN"])
    
    # Sample Thread Stack Size
    sampleThreadStackSize = azureIOTComponent.createIntegerSymbol("SAMPLE_STACK_SIZE", azureCSdkEnable)
    sampleThreadStackSize.setLabel("Sample Thread Stack Size")
    sampleThreadStackSize.setVisible(False)
    sampleThreadStackSize.setDescription("Sample Thread Stack Size")
    sampleThreadStackSize.setDefaultValue(2048) 
    sampleThreadStackSize.setDependencies(azureNetXCSdkMenuVisibility, ["AZURE_C_SDK_EN"])
    
    # Maximum Number of Sample Properties
    sampleMaxPropertyCount = azureIOTComponent.createIntegerSymbol("MAX_PROPERTY_COUNT", azureCSdkEnable)
    sampleMaxPropertyCount.setLabel("Maximum Number of Sample Properties")
    sampleMaxPropertyCount.setVisible(False)
    sampleMaxPropertyCount.setDescription("Maximum Number of Sample Properties")
    sampleMaxPropertyCount.setDefaultValue(2) 
    sampleMaxPropertyCount.setDependencies(azureNetXCSdkMenuVisibility, ["AZURE_C_SDK_EN"])
    
    # Azure IoT Hub Module ID 
    azureNetXCSdkModuleId = azureIOTComponent.createStringSymbol("MODULE_ID", azureCSdkEnable)
    azureNetXCSdkModuleId.setLabel("Azure IoT Hub Module ID")
    azureNetXCSdkModuleId.setVisible(False)
    azureNetXCSdkModuleId.setDescription("Azure IoT Hub Module ID")
    azureNetXCSdkModuleId.setDefaultValue("") 
    azureNetXCSdkModuleId.setDependencies(azureNetXCSdkMenuVisibility, ["AZURE_C_SDK_EN"])
    
    # Use DPS? 
    azureNetXCSdkUseDps = azureIOTComponent.createBooleanSymbol("ENABLE_DPS_SAMPLE", azureCSdkEnable)
    azureNetXCSdkUseDps.setLabel("Use DPS?")
    azureNetXCSdkUseDps.setVisible(False)
    azureNetXCSdkUseDps.setDescription("Use DPS?")
    azureNetXCSdkUseDps.setDefaultValue(False)       
    azureNetXCSdkUseDps.setDependencies(azureNetXCSdkMenuVisibility, ["AZURE_C_SDK_EN"])

    # Endpoint
    azureNetXCSdkEndPoint = azureIOTComponent.createStringSymbol("ENDPOINT", azureNetXCSdkUseDps)
    azureNetXCSdkEndPoint.setLabel("Endpoint")
    azureNetXCSdkEndPoint.setVisible(False)
    azureNetXCSdkEndPoint.setDescription("Endpoint")
    azureNetXCSdkEndPoint.setDefaultValue("")
    azureNetXCSdkEndPoint.setDependencies(azureNetXCSdkMenuVisibility, ["ENABLE_DPS_SAMPLE"])

    # ID Scope
    azureNetXCSdkIdScope = azureIOTComponent.createStringSymbol("ID_SCOPE", azureNetXCSdkUseDps)
    azureNetXCSdkIdScope.setLabel("ID Scope")
    azureNetXCSdkIdScope.setVisible(False)
    azureNetXCSdkIdScope.setDescription("ID Scope")
    azureNetXCSdkIdScope.setDefaultValue("")
    azureNetXCSdkIdScope.setDependencies(azureNetXCSdkMenuVisibility, ["ENABLE_DPS_SAMPLE"])

    # Registration ID
    azureNetXCSdkRegId = azureIOTComponent.createStringSymbol("REGISTRATION_ID", azureNetXCSdkUseDps)
    azureNetXCSdkRegId.setLabel("Registration ID")
    azureNetXCSdkRegId.setVisible(False)
    azureNetXCSdkRegId.setDescription("Registration ID")
    azureNetXCSdkRegId.setDefaultValue("")
    azureNetXCSdkRegId.setDependencies(azureNetXCSdkMenuVisibility, ["ENABLE_DPS_SAMPLE"])    
    
    # Sample Maximum Buffer Size
    azureNetXCSdkSampleMaxBuffer = azureIOTComponent.createIntegerSymbol("SAMPLE_MAX_BUFFER", azureNetXCSdkUseDps)
    azureNetXCSdkSampleMaxBuffer.setLabel("Sample Maximum Buffer Size")
    azureNetXCSdkSampleMaxBuffer.setVisible(False)
    azureNetXCSdkSampleMaxBuffer.setDescription("Sample Maximum Buffer Size")
    azureNetXCSdkSampleMaxBuffer.setDefaultValue(256) 
    azureNetXCSdkSampleMaxBuffer.setDependencies(azureNetXCSdkMenuVisibility, ["ENABLE_DPS_SAMPLE"])   
    
    # Host Name
    azureNetXCSdkHostName = azureIOTComponent.createStringSymbol("HOST_NAME", azureNetXCSdkUseDps)
    azureNetXCSdkHostName.setLabel("Host Name")
    azureNetXCSdkHostName.setVisible(True)
    azureNetXCSdkHostName.setDescription("Host Name")
    azureNetXCSdkHostName.setDefaultValue("")
    azureNetXCSdkHostName.setDependencies(azureNetXCSdkMenuInvisibility, ["ENABLE_DPS_SAMPLE"])
    
    # Device ID
    azureNetXCSdkDeviceId = azureIOTComponent.createStringSymbol("DEVICE_ID", azureNetXCSdkUseDps)
    azureNetXCSdkDeviceId.setLabel("Device ID")
    azureNetXCSdkDeviceId.setVisible(True)
    azureNetXCSdkDeviceId.setDescription("Device ID")
    azureNetXCSdkDeviceId.setDefaultValue("")
    azureNetXCSdkDeviceId.setDependencies(azureNetXCSdkMenuInvisibility, ["ENABLE_DPS_SAMPLE"])
    
    # Azure IoT Device Authentication
    azureNetXCSdkDevSecurity = azureIOTComponent.createKeyValueSetSymbol("NX_AZURE_C_SDK_DEV_SECURITY", azureCSdkEnable)
    azureNetXCSdkDevSecurity.setLabel("Azure IoT Device Authentication")
    azureNetXCSdkDevSecurity.setOutputMode("Key")
    azureNetXCSdkDevSecurity.setDisplayMode("Description")
    azureNetXCSdkDevSecurity.addKey("Symmetric_Key", "0", "Symmetric Key" )
    azureNetXCSdkDevSecurity.addKey("X.509_Certificate", "1", "X.509 Certificate" )
    azureNetXCSdkDevSecurity.setDefaultValue(0)
    azureNetXCSdkDevSecurity.setVisible(False)
    azureNetXCSdkDevSecurity.setDependencies(azureNetXCSdkMenuVisibility, ["AZURE_C_SDK_EN"])

    # Symmetric Key
    azureNetXCSdkSymmKey = azureIOTComponent.createStringSymbol("DEVICE_SYMMETRIC_KEY", azureNetXCSdkDevSecurity)
    azureNetXCSdkSymmKey.setLabel("Symmetric Key")
    azureNetXCSdkSymmKey.setVisible(True)
    azureNetXCSdkSymmKey.setDescription("Symmetric Key")
    azureNetXCSdkSymmKey.setDefaultValue("")
    azureNetXCSdkSymmKey.setDependencies(azureNetXCSdkAuthVisibility, ["NX_AZURE_C_SDK_DEV_SECURITY"])
    
    azureNetXCSdkCertComment = azureIOTComponent.createCommentSymbol("NX_AZURE_C_SDK_CERT_COMMENT",azureNetXCSdkDevSecurity)
    azureNetXCSdkCertComment.setLabel("*** Configure Certificate as given in user-guide ***")
    azureNetXCSdkCertComment.setVisible(False)
    azureNetXCSdkCertComment.setDependencies(azureNetXCSdkAuthVisibility, ["NX_AZURE_C_SDK_DEV_SECURITY"])
                
    #Add to definitions.h
    azureNetXSystemDefFile = azureIOTComponent.createFileSymbol("AZURE_H_FILE", None)
    azureNetXSystemDefFile.setType("STRING")
    azureNetXSystemDefFile.setOutputName("core.LIST_SYSTEM_DEFINITIONS_H_INCLUDES")
    azureNetXSystemDefFile.setSourcePath("third_party_adapter/azure_rtos/templates/system/system_definitions.h.ftl")
    azureNetXSystemDefFile.setMarkup(True) 
    
    #Add to initialization.c
    azureNetXSysInitDataSourceFtl = azureIOTComponent.createFileSymbol(None, None)
    azureNetXSysInitDataSourceFtl.setType("STRING")
    azureNetXSysInitDataSourceFtl.setOutputName("core.LIST_SYSTEM_INIT_C_LIBRARY_INITIALIZATION_DATA")
    azureNetXSysInitDataSourceFtl.setSourcePath("third_party_adapter/azure_rtos/templates/system/system_data_initialize.c.ftl")
    azureNetXSysInitDataSourceFtl.setMarkup(True)
    
    azureNetXHeaderFtl = azureIOTComponent.createFileSymbol(None, None)
    azureNetXHeaderFtl.setSourcePath("third_party_adapter/azure_rtos/config/nx_user.h.ftl")
    azureNetXHeaderFtl.setOutputName("nx_user.h")
    azureNetXHeaderFtl.setDestPath("third_party_adapter/azure_rtos/")
    azureNetXHeaderFtl.setProjectPath("config/" + configName + "/third_party_adapter/azure_rtos/")
    azureNetXHeaderFtl.setType("HEADER")
    azureNetXHeaderFtl.setMarkup(True)

    azureNetXCSdkHeaderFtl = azureIOTComponent.createFileSymbol(None, None)
    azureNetXCSdkHeaderFtl.setSourcePath("third_party_adapter/azure_rtos/config/sample_config.h.ftl")
    azureNetXCSdkHeaderFtl.setOutputName("sample_config.h")
    # azureNetXCSdkHeaderFtl.setDestPath("third_party_adapter/azure_rtos/")
    # azureNetXCSdkHeaderFtl.setProjectPath("config/" + configName + "/third_party_adapter/azure_rtos/")
    azureNetXCSdkHeaderFtl.setDestPath("../../azure_rtos_demo/sample_azure_iot_embedded_sdk/")
    azureNetXCSdkHeaderFtl.setProjectPath("azure_rtos_demo/sample_azure_iot_embedded_sdk/")
    azureNetXCSdkHeaderFtl.setType("HEADER")
    azureNetXCSdkHeaderFtl.setMarkup(True)   
    azureNetXCSdkHeaderFtl.setEnabled(False)    
    azureNetXCSdkHeaderFtl.setDependencies(azureNetXCSdkSampleConfig, ["AZURE_C_SDK_EN"])    
                                
    azureNetXPath = azureIOTComponent.createSettingSymbol("AZURE_INCLUDE_PATH", None)
    azureNetXPath.setValue("../src/config/"+configName+ "/third_party_adapter/azure_rtos;../src/config/" + configName + "/third_party_adapter/azure_rtos/src; ../src/config/"+ configName + "/third_party_adapter/azure_rtos/src/tcpip")
    azureNetXPath.setCategory("C32")
    azureNetXPath.setKey("extra-include-directories")
    azureNetXPath.setAppend(True, ";")
    
    azureGlueEthernetHeaderFile = azureIOTComponent.createFileSymbol(None, None)
    azureGlueEthernetHeaderFile.setSourcePath("../net/tcpip/tcpip_ethernet.h")    
    azureGlueEthernetHeaderFile.setOutputName("tcpip_ethernet.h")
    azureGlueEthernetHeaderFile.setDestPath("third_party_adapter/azure_rtos/src/tcpip/")
    azureGlueEthernetHeaderFile.setProjectPath("config/" + configName+ "/third_party_adapter/azure_rtos/src/tcpip/")
    azureGlueEthernetHeaderFile.setType("HEADER")
    azureGlueEthernetHeaderFile.setOverwrite(True) 

    azureGlueMacHeaderFile = azureIOTComponent.createFileSymbol(None, None)
    azureGlueMacHeaderFile.setSourcePath("../net/tcpip/tcpip_mac.h")    
    azureGlueMacHeaderFile.setOutputName("tcpip_mac.h")
    azureGlueMacHeaderFile.setDestPath("third_party_adapter/azure_rtos/src/tcpip/")
    azureGlueMacHeaderFile.setProjectPath("config/" + configName+ "/third_party_adapter/azure_rtos/src/tcpip/")
    azureGlueMacHeaderFile.setType("HEADER")
    azureGlueMacHeaderFile.setOverwrite(True) 

    azureGlueMacObjHeaderFile = azureIOTComponent.createFileSymbol(None, None)
    azureGlueMacObjHeaderFile.setSourcePath("../net/tcpip/tcpip_mac_object.h")    
    azureGlueMacObjHeaderFile.setOutputName("tcpip_mac_object.h")
    azureGlueMacObjHeaderFile.setDestPath("third_party_adapter/azure_rtos/src/tcpip/")
    azureGlueMacObjHeaderFile.setProjectPath("config/" + configName+ "/third_party_adapter/azure_rtos/src/tcpip/")
    azureGlueMacObjHeaderFile.setType("HEADER")
    azureGlueMacObjHeaderFile.setOverwrite(True) 

    # Add Azure Glue Code C files from azure_rtos/third_party_adapter/azure_rtos/src    
    thirdPartyAdapterPath = os.path.join(h3_dir,"azure_rtos", "third_party_adapter")
    azureGlueSourcePath = os.path.join(thirdPartyAdapterPath, "azure_rtos", "src")
    supportedExtension = ["c"]
    for root,dir,files in os.walk(azureGlueSourcePath):          
        for sourceFileName in files:
            if sourceFileName.split(".")[-1].lower() in supportedExtension: 
                relative_path_glue_src = os.path.relpath(root, thirdPartyAdapterPath)
                relpath = relative_path_glue_src.replace("\\", "/")
                symbol_end = relpath.replace("/", "#")
                glueSrc = sourceFileName.replace(".", "_").upper() + symbol_end.upper()+ "#"
                azureGlueSourceFile = azureIOTComponent.createFileSymbol(glueSrc, None)
                azureGlueSourceFile.setRelative(False)
                azureGlueSourceFile.setSourcePath(os.path.join(root, sourceFileName))
                azureGlueSourceFile.setOutputName(sourceFileName)
                azureGlueSourceFile.setMarkup(False)
                azureGlueSourceFile.setOverwrite(True)                
                dest_path_glue_src =  "third_party_adapter/" + relpath + "/"
                azureGlueSourceFile.setDestPath(dest_path_glue_src)
                azureGlueSourceFile.setProjectPath("config/" + configName + "/" + dest_path_glue_src)
                azureGlueSourceFile.setType("SOURCE")
                azureGlueSourceFile.setEnabled(True)
                            
    # Add Azure Glue Code H files from azure_rtos/third_party_adapter/azure_rtos/src
    supportedExtension = ["h"]
    for root,dir,files in os.walk(azureGlueSourcePath):          
        for headerFileName in files:
            if headerFileName.split(".")[-1].lower() in supportedExtension: 
                relative_path_glue_inc = os.path.relpath(root, thirdPartyAdapterPath)
                relpath = relative_path_glue_inc.replace("\\", "/")
                symbol_end = relpath.replace("/", "#")
                glueInc = headerFileName.replace(".", "_").upper() + symbol_end.upper()+ "#"
                azureGlueHeaderFile = azureIOTComponent.createFileSymbol(glueInc, None)
                azureGlueHeaderFile.setRelative(False)
                azureGlueHeaderFile.setSourcePath(os.path.join(root, headerFileName))
                azureGlueHeaderFile.setOutputName(headerFileName)
                azureGlueHeaderFile.setMarkup(False)
                azureGlueHeaderFile.setOverwrite(True)                
                dest_path_glue_inc =  "third_party_adapter/" + relpath + "/"
                azureGlueHeaderFile.setDestPath(dest_path_glue_inc)
                azureGlueHeaderFile.setProjectPath("config/" + configName + "/" + dest_path_glue_inc)
                azureGlueHeaderFile.setType("HEADER")
                azureGlueHeaderFile.setEnabled(True)             
                                               
    # Add files from netxduo/common to the project
    # Add C files from netxduo/common/src 
    netxDuoCommonSourcePath = os.path.join(netxDuo_dir, "common", "src")
    supportedExtension = ["c"]
    for root,dirs,files in os.walk(netxDuoCommonSourcePath):
        for sourceFileName in files:
            if sourceFileName.split(".")[-1].lower() in supportedExtension:
                commonSrc = sourceFileName.replace(".", "_").upper()
                netxDuoCommonSourceFile = azureIOTComponent.createFileSymbol(commonSrc, None)
                netxDuoCommonSourceFile.setRelative(False)
                netxDuoCommonSourceFile.setSourcePath(os.path.join(root, sourceFileName))
                netxDuoCommonSourceFile.setOutputName(sourceFileName)
                netxDuoCommonSourceFile.setMarkup(False)
                netxDuoCommonSourceFile.setOverwrite(True)
                netxDuoCommonSourceFile.setDestPath("../../third_party/azure_rtos/netxduo/common/src/")
                netxDuoCommonSourceFile.setProjectPath("third_party/azure_rtos/netxduo/common/src/")
                netxDuoCommonSourceFile.setType("SOURCE")
                netxDuoCommonSourceFile.setEnabled(True)    
    
    # Add H files from netxduo/common/inc
    netxDuoCommonHeaderPath = os.path.join(netxDuo_dir, "common", "inc")
    supportedExtension = ["h"]
    for root,dirs,files in os.walk(netxDuoCommonHeaderPath):
        for headerFileName in files:
            if headerFileName.split(".")[-1].lower() in supportedExtension:
                commonInc = headerFileName.replace(".", "_").upper()
                netxDuoCommonHeaderFile = azureIOTComponent.createFileSymbol(commonInc, None)
                netxDuoCommonHeaderFile.setRelative(False)
                netxDuoCommonHeaderFile.setSourcePath(os.path.join(root, headerFileName))
                netxDuoCommonHeaderFile.setOutputName(headerFileName)
                netxDuoCommonHeaderFile.setMarkup(False)
                netxDuoCommonHeaderFile.setOverwrite(True)
                netxDuoCommonHeaderFile.setDestPath("../../third_party/azure_rtos/netxduo/common/inc/")
                netxDuoCommonHeaderFile.setProjectPath("third_party/azure_rtos/netxduo/common/inc/")
                netxDuoCommonHeaderFile.setType("HEADER")
                netxDuoCommonHeaderFile.setEnabled(True)

    # Add H files from netxduo/ports/<core>/<toolchain>/inc
    netxDuoPortsHeaderPath = os.path.join(netxDuo_dir, "ports",arch,toolchain,"inc")
    supportedExtension = ["h"]
    for root,dirs,files in os.walk(netxDuoPortsHeaderPath):
        for headerFileName in files:
            if headerFileName.split(".")[-1].lower() in supportedExtension:
                portsInc = headerFileName.replace(".", "_").upper()
                netxDuoPortsHeaderFile = azureIOTComponent.createFileSymbol(portsInc, None)
                netxDuoPortsHeaderFile.setRelative(False)
                netxDuoPortsHeaderFile.setSourcePath(os.path.join(root, headerFileName))
                netxDuoPortsHeaderFile.setOutputName(headerFileName)
                netxDuoPortsHeaderFile.setMarkup(False)
                netxDuoPortsHeaderFile.setOverwrite(True)
                netxDuoPortsHeaderFile.setDestPath("../../third_party/azure_rtos/netxduo/ports/" + arch + "/" + toolchain + "/inc/")
                netxDuoPortsHeaderFile.setProjectPath("third_party/azure_rtos/netxduo/ports/" + arch + "/" + toolchain + "/inc/")
                netxDuoPortsHeaderFile.setType("HEADER")
                netxDuoPortsHeaderFile.setEnabled(True)

    azureNetXCommonPath = azureIOTComponent.createSettingSymbol("AZURE_COMMON_INCLUDE_PATH", None)
    azureNetXCommonPath.setValue("../src/third_party/azure_rtos/netxduo;../src/third_party/azure_rtos/netxduo/common/inc;../src/third_party/azure_rtos/netxduo/addons")
    azureNetXCommonPath.setCategory("C32")
    azureNetXCommonPath.setKey("extra-include-directories")
    azureNetXCommonPath.setAppend(True, ";")

    azureNetXPortPath = azureIOTComponent.createSettingSymbol("NETX_PORT_PATH", None)
    azureNetXPortPath.setValue("../src/third_party/azure_rtos/netxduo/ports/" + arch +"/gnu/inc")
    azureNetXPortPath.setCategory("C32")
    azureNetXPortPath.setKey("extra-include-directories")
    azureNetXPortPath.setAppend(True, ";")       

       
    # Add C files from netxduo/addons to the project
    supportedExtension = ["c"]
    excludePath = ["addons/azure_iot/samples", "addons/azure_iot/azure-sdk-for-c"]
    for root,dir,files in os.walk(netxDuoAddonSourcePath):          
        for sourceFileName in files:
            if sourceFileName.split(".")[-1].lower() in supportedExtension:
                dep_path_addon_src = os.path.relpath(root, netxDuoAddonSourcePath)
                if dep_path_addon_src.split("\\"):
                    dependency = dep_path_addon_src.split("\\")[0].upper() + "_ENABLE"
                else:
                    dependency = ""
                relative_path_addon_src = os.path.relpath(root, netxDuo_dir)
                relpath = relative_path_addon_src.replace("\\", "/")
                
                if not any(x in relpath for x in excludePath):
                    symbol_end = relpath.replace("/", "#")
                    addonSrc = sourceFileName.replace(".", "_").upper() + symbol_end.upper()+ "#"
                    netxDuoAddonSourceFile = azureIOTComponent.createFileSymbol(addonSrc, None)
                    netxDuoAddonSourceFile.setRelative(False)
                    netxDuoAddonSourceFile.setSourcePath(os.path.join(root, sourceFileName))
                    netxDuoAddonSourceFile.setOutputName(sourceFileName)
                    netxDuoAddonSourceFile.setMarkup(False)
                    netxDuoAddonSourceFile.setOverwrite(True)                
                    dest_path_addon_src =  "third_party/azure_rtos/netxduo/" + relpath + "/"
                    netxDuoAddonSourceFile.setDestPath("../../" + dest_path_addon_src)
                    netxDuoAddonSourceFile.setProjectPath(dest_path_addon_src)
                    netxDuoAddonSourceFile.setType("SOURCE")
                    netxDuoAddonSourceFile.setEnabled(False)
                    netxDuoAddonSourceFile.setDependencies(azureNetXAddonFileEnable, [dependency])
                    
    # Add H files from netxduo/addons to the project
    netxDuoAddonHeaderPath = os.path.join(netxDuo_dir, "addons")
    supportedExtension = ["h"]
    for root,dir,files in os.walk(netxDuoAddonHeaderPath):          
        for headerFileName in files:
            if headerFileName.split(".")[-1].lower() in supportedExtension:
                dep_path_addon_inc = os.path.relpath(root, netxDuoAddonHeaderPath)
                if dep_path_addon_inc.split("\\"):
                    dependency = dep_path_addon_inc.split("\\")[0].upper() + "_ENABLE"
                else:
                    dependency = ""
                relative_path_addon_inc = os.path.relpath(root, netxDuo_dir)
                relpath = relative_path_addon_inc.replace("\\", "/")
                if not any(x in relpath for x in excludePath):
                    symbol_end = relpath.replace("/", "#")
                    addonInc = headerFileName.replace(".", "_").upper() + symbol_end.upper()+ "#"
                    netxDuoAddonHeaderFile = azureIOTComponent.createFileSymbol(addonInc, None)
                    netxDuoAddonHeaderFile.setRelative(False)
                    netxDuoAddonHeaderFile.setSourcePath(os.path.join(root, headerFileName))
                    print os.path.join(root, headerFileName)
                    netxDuoAddonHeaderFile.setOutputName(headerFileName)
                    netxDuoAddonHeaderFile.setMarkup(False)
                    netxDuoAddonHeaderFile.setOverwrite(True)                
                    dest_path_addon_inc =  "third_party/azure_rtos/netxduo/" + relpath + "/"
                    netxDuoAddonHeaderFile.setDestPath("../../" + dest_path_addon_inc)
                    netxDuoAddonHeaderFile.setProjectPath(dest_path_addon_inc)
                    netxDuoAddonHeaderFile.setType("HEADER")
                    netxDuoAddonHeaderFile.setEnabled(False)
                    netxDuoAddonHeaderFile.setDependencies(azureNetXAddonFileEnable, [dependency])


    netxDuoAddonLicenseFile = azureIOTComponent.createFileSymbol("LICENSE_FILE", None)
    netxDuoAddonLicenseFile.setRelative(False)
    azure_iot_security_module_path  = os.path.join(netxDuoAddonSourcePath, "azure_iot", "azure_iot_security_module", "configs")
    azure_iot_security_module_Licene_path  = os.path.join(azure_iot_security_module_path, "license")
    netxDuoAddonLicenseFile.setSourcePath(azure_iot_security_module_Licene_path)
    netxDuoAddonLicenseFile.setOutputName("license")
    netxDuoAddonLicenseFile.setMarkup(False)
    netxDuoAddonLicenseFile.setOverwrite(True)                
    netxDuoAddonLicenseFile.setDestPath("../../third_party/azure_rtos/netxduo/addons/azure_iot/azure_iot_security_module/configs/")
    netxDuoAddonLicenseFile.setProjectPath("third_party/azure_rtos/netxduo/addons/azure_iot/azure_iot_security_module/configs/")
    netxDuoAddonLicenseFile.setType("HEADER")
    netxDuoAddonLicenseFile.setEnabled(False)
    netxDuoAddonLicenseFile.setDependencies(azureNetXAddonFileEnable, ["AZURE_IOT_ENABLE"])
                
    azureSdkC_dir = os.path.join(netxDuoAddonSourcePath, "azure_iot", "azure-sdk-for-c")
    # Add C files from azure-sdk-for-c/sdk/src
    azureSdkCSourcePath = os.path.join(azureSdkC_dir, "sdk", "src")
    supportedExtension = ["c"]
    excludePath = ["sdk/src/azure/platform"]
    for root,dirs,files in os.walk(azureSdkCSourcePath):
        for sourceFileName in files:
            if sourceFileName.split(".")[-1].lower() in supportedExtension:
                relative_path_azureSdk_src = os.path.relpath(root, azureSdkC_dir)
                relpath = relative_path_azureSdk_src.replace("\\", "/")
                if not any(x in relpath for x in excludePath):
                    symbol_end = relpath.replace("/", "#")
                    azureSdkSrc = sourceFileName.replace(".", "_").upper() + symbol_end.upper()+ "#"
                    azureSdkCSourceFile = azureIOTComponent.createFileSymbol(azureSdkSrc, None)
                    azureSdkCSourceFile.setRelative(False)
                    azureSdkCSourceFile.setSourcePath(os.path.join(root, sourceFileName))
                    azureSdkCSourceFile.setOutputName(sourceFileName)
                    azureSdkCSourceFile.setMarkup(False)
                    azureSdkCSourceFile.setOverwrite(True)                
                    dest_path_azureSdk_src =  "third_party/azure_rtos/netxduo/addons/azure_iot/azure-sdk-for-c/" + relpath + "/"
                    azureSdkCSourceFile.setDestPath("../../" + dest_path_azureSdk_src)
                    azureSdkCSourceFile.setProjectPath(dest_path_azureSdk_src)
                    azureSdkCSourceFile.setType("SOURCE")
                    azureSdkCSourceFile.setEnabled(False)    
                    azureSdkCSourceFile.setDependencies(azureNetXAddonFileEnable, ["AZURE_IOT_ENABLE"])

    # Add H files from azure-sdk-for-c/sdk/src
    supportedExtension = ["h"]
    excludePath = ["sdk/src/azure/platform"]
    for root,dirs,files in os.walk(azureSdkCSourcePath):
        for headerFileName in files:
            if headerFileName.split(".")[-1].lower() in supportedExtension:
                relative_path_azureSdk_src = os.path.relpath(root, azureSdkC_dir)
                relpath = relative_path_azureSdk_src.replace("\\", "/")
                if not any(x in relpath for x in excludePath):                    
                    symbol_end = relpath.replace("/", "#")
                    azureSdkSrcH= headerFileName.replace(".", "_").upper() + symbol_end.upper()+ "#"
                    azureSdkCSrcHeaderFile = azureIOTComponent.createFileSymbol(azureSdkSrcH, None)
                    azureSdkCSrcHeaderFile.setRelative(False)
                    azureSdkCSrcHeaderFile.setSourcePath(os.path.join(root, headerFileName))
                    azureSdkCSrcHeaderFile.setOutputName(headerFileName)
                    azureSdkCSrcHeaderFile.setMarkup(False)
                    azureSdkCSrcHeaderFile.setOverwrite(True)                
                    dest_path_azureSdk_src =  "third_party/azure_rtos/netxduo/addons/azure_iot/azure-sdk-for-c/" + relpath + "/"
                    azureSdkCSrcHeaderFile.setDestPath("../../" + dest_path_azureSdk_src)
                    azureSdkCSrcHeaderFile.setProjectPath(dest_path_azureSdk_src)
                    azureSdkCSrcHeaderFile.setType("HEADER")
                    azureSdkCSrcHeaderFile.setEnabled(False)    
                    azureSdkCSrcHeaderFile.setDependencies(azureNetXAddonFileEnable, ["AZURE_IOT_ENABLE"])    

    azureSdkCPath = azureIOTComponent.createSettingSymbol("AZURE_IOT_PATH", None)
    azureSdkCPath.setCategory("C32")
    azureSdkCPath.setKey("extra-include-directories")
    azureSdkCPath.setValue("../src/third_party/azure_rtos/netxduo/addons/azure_iot/azure-sdk-for-c/sdk/inc")
    azureSdkCPath.setAppend(True, ";")
    azureSdkCPath.setEnabled(False)
    azureSdkCPath.setDependencies(azureNetXAddonFileEnable, ["AZURE_IOT_ENABLE"])
    
    # Add H files from azure-sdk-for-c/sdk/inc
    azureSdkCHeaderPath = os.path.join(azureSdkC_dir, "sdk", "inc")
    supportedExtension = ["h"]
    excludePath = []
    for root,dirs,files in os.walk(azureSdkCHeaderPath):
        for headerFileName in files:
            if headerFileName.split(".")[-1].lower() in supportedExtension:
                relative_path_azureSdk_inc = os.path.relpath(root, azureSdkC_dir)
                relpath = relative_path_azureSdk_inc.replace("\\", "/")
                if relpath not in excludePath:
                    symbol_end = relpath.replace("/", "#")
                    azureSdkInc = headerFileName.replace(".", "_").upper() + symbol_end.upper()+ "#"
                    azureSdkCHeaderFile = azureIOTComponent.createFileSymbol(azureSdkInc, None)
                    azureSdkCHeaderFile.setRelative(False)
                    azureSdkCHeaderFile.setSourcePath(os.path.join(root, headerFileName))
                    azureSdkCHeaderFile.setOutputName(headerFileName)
                    azureSdkCHeaderFile.setMarkup(False)
                    azureSdkCHeaderFile.setOverwrite(True)                
                    dest_path_azureSdk_inc =  "third_party/azure_rtos/netxduo/addons/azure_iot/azure-sdk-for-c/" + relpath + "/"
                    azureSdkCHeaderFile.setDestPath("../../" + dest_path_azureSdk_inc)
                    azureSdkCHeaderFile.setProjectPath(dest_path_azureSdk_inc)
                    azureSdkCHeaderFile.setType("HEADER")
                    azureSdkCHeaderFile.setEnabled(False)    
                    azureSdkCHeaderFile.setDependencies(azureNetXAddonFileEnable, ["AZURE_IOT_ENABLE"]) 
                    
    netxDuoAddonAuzreIotPreProcessor = azureIOTComponent.createSettingSymbol("AZURE_IOT_PRE_PROC", None)
    netxDuoAddonAuzreIotPreProcessor.setCategory("C32")
    netxDuoAddonAuzreIotPreProcessor.setKey("preprocessor-macros")
    netxDuoAddonAuzreIotPreProcessor.setValue("AZ_NO_PRECONDITION_CHECKING")
    netxDuoAddonAuzreIotPreProcessor.setAppend(True, ";")
    netxDuoAddonAuzreIotPreProcessor.setEnabled(False)
    netxDuoAddonAuzreIotPreProcessor.setDependencies(azureNetXAddonFileEnable, ["AZURE_IOT_ENABLE"])
  
    # Add C files from netxduo/crypto_libraries to the project
    supportedExtension = ["c"]
    for root,dir,files in os.walk(netxCryptoSourcePath):          
        for sourceFileName in files:
            if sourceFileName.split(".")[-1].lower() in supportedExtension:
                relative_path_crypto_src = os.path.relpath(root, netxDuo_dir)
                relpath = relative_path_crypto_src.replace("\\", "/")
                symbol_end = relpath.replace("/", "#")
                cryptoSrc = sourceFileName.replace(".", "_").upper() + symbol_end.upper()+ "#"
                netxDuoCryptoSourceFile = azureIOTComponent.createFileSymbol(cryptoSrc, None)
                netxDuoCryptoSourceFile.setRelative(False)
                netxDuoCryptoSourceFile.setSourcePath(os.path.join(root, sourceFileName))
                netxDuoCryptoSourceFile.setOutputName(sourceFileName)
                netxDuoCryptoSourceFile.setMarkup(False)
                netxDuoCryptoSourceFile.setOverwrite(True)                
                dest_path_crypto_src =  "third_party/azure_rtos/netxduo/" + relpath + "/"
                netxDuoCryptoSourceFile.setDestPath("../../" + dest_path_crypto_src)
                netxDuoCryptoSourceFile.setProjectPath(dest_path_crypto_src)
                netxDuoCryptoSourceFile.setType("SOURCE")
                netxDuoCryptoSourceFile.setEnabled(False)
                netxDuoCryptoSourceFile.setDependencies(azureNetXCryptoFileEnable, ["NX_CRYPTO_LIB_ENABLE"])
                  
    # Add H files from netxduo/crypto_libraries to the project
    netxDuoCryptoHeaderPath = os.path.join(netxDuo_dir, "crypto_libraries")
    supportedExtension = ["h"]
    for root,dir,files in os.walk(netxDuoCryptoHeaderPath):          
        for headerFileName in files:
            if headerFileName.split(".")[-1].lower() in supportedExtension:
                relative_path_crypto_inc = os.path.relpath(root, netxDuo_dir)
                relpath = relative_path_crypto_inc.replace("\\", "/")
                symbol_end = relpath.replace("/", "#")
                cryptoInc = headerFileName.replace(".", "_").upper() + symbol_end.upper()+ "#"
                netxDuoCryptoHeaderFile = azureIOTComponent.createFileSymbol(cryptoInc, None)
                netxDuoCryptoHeaderFile.setRelative(False)
                netxDuoCryptoHeaderFile.setSourcePath(os.path.join(root, headerFileName))
                netxDuoCryptoHeaderFile.setOutputName(headerFileName)
                netxDuoCryptoHeaderFile.setMarkup(False)
                netxDuoCryptoHeaderFile.setOverwrite(True)                
                dest_path_crypto_inc =  "third_party/azure_rtos/netxduo/" + relpath + "/"
                netxDuoCryptoHeaderFile.setDestPath("../../" + dest_path_crypto_inc)
                netxDuoCryptoHeaderFile.setProjectPath(dest_path_crypto_inc)
                netxDuoCryptoHeaderFile.setType("HEADER")
                netxDuoCryptoHeaderFile.setEnabled(False)
                netxDuoCryptoHeaderFile.setDependencies(azureNetXCryptoFileEnable, ["NX_CRYPTO_LIB_ENABLE"])
  
    # Add C files from netxduo/nx_secure to the project
    supportedExtension = ["c"]
    for root,dir,files in os.walk(netxSecureSourcePath):          
        for sourceFileName in files:
            if sourceFileName.split(".")[-1].lower() in supportedExtension:
                relative_path_secure_src = os.path.relpath(root, netxDuo_dir)
                relpath = relative_path_secure_src.replace("\\", "/")
                symbol_end = relpath.replace("/", "#")
                secureSrc = sourceFileName.replace(".", "_").upper() + symbol_end.upper()+ "#"
                netxDuoSecureSourceFile = azureIOTComponent.createFileSymbol(secureSrc, None)
                netxDuoSecureSourceFile.setRelative(False)
                netxDuoSecureSourceFile.setSourcePath(os.path.join(root, sourceFileName))
                netxDuoSecureSourceFile.setOutputName(sourceFileName)
                netxDuoSecureSourceFile.setMarkup(False)
                netxDuoSecureSourceFile.setOverwrite(True)                
                dest_path_secure_src =  "third_party/azure_rtos/netxduo/" + relpath + "/"
                netxDuoSecureSourceFile.setDestPath("../../" + dest_path_secure_src)
                netxDuoSecureSourceFile.setProjectPath(dest_path_secure_src)
                netxDuoSecureSourceFile.setType("SOURCE")
                netxDuoSecureSourceFile.setEnabled(False)
                netxDuoSecureSourceFile.setDependencies(azureNetXSecureFileEnable, ["NX_SECURE_ENABLE"])
                  
    # Add H files from netxduo/nx_secure to the project
    netxDuoSecureHeaderPath = os.path.join(netxDuo_dir, "nx_secure")
    supportedExtension = ["h"]
    for root,dir,files in os.walk(netxDuoSecureHeaderPath):          
        for headerFileName in files:
            if headerFileName.split(".")[-1].lower() in supportedExtension:
                relative_path_secure_inc = os.path.relpath(root, netxDuo_dir)
                relpath = relative_path_secure_inc.replace("\\", "/")
                symbol_end = relpath.replace("/", "#")
                secureInc = headerFileName.replace(".", "_").upper() + symbol_end.upper()+ "#"
                netxDuoSecureHeaderFile = azureIOTComponent.createFileSymbol(secureInc, None)
                netxDuoSecureHeaderFile.setRelative(False)
                netxDuoSecureHeaderFile.setSourcePath(os.path.join(root, headerFileName))
                netxDuoSecureHeaderFile.setOutputName(headerFileName)
                netxDuoSecureHeaderFile.setMarkup(False)
                netxDuoSecureHeaderFile.setOverwrite(True)                
                dest_path_secure_inc =  "third_party/azure_rtos/netxduo/" + relpath + "/"
                netxDuoSecureHeaderFile.setDestPath("../../" + dest_path_secure_inc)
                netxDuoSecureHeaderFile.setProjectPath(dest_path_secure_inc)
                netxDuoSecureHeaderFile.setType("HEADER")
                netxDuoSecureHeaderFile.setEnabled(False)
                netxDuoSecureHeaderFile.setDependencies(azureNetXSecureFileEnable, ["NX_SECURE_ENABLE"])
                                   
    # Add files from filex/common to the project
    # Add C files from filex/common/src 
    filexCommonSourcePath = os.path.join(filex_dir, "common", "src")
    supportedExtension = ["c"]
    for root,dirs,files in os.walk(filexCommonSourcePath):
        for sourceFileName in files:
            if sourceFileName.split(".")[-1].lower() in supportedExtension:
                commonSrc = sourceFileName.replace(".", "_").upper()
                filexCommonSourceFile = azureIOTComponent.createFileSymbol(commonSrc, None)
                filexCommonSourceFile.setRelative(False)
                filexCommonSourceFile.setSourcePath(os.path.join(root, sourceFileName))
                filexCommonSourceFile.setOutputName(sourceFileName)
                filexCommonSourceFile.setMarkup(False)
                filexCommonSourceFile.setOverwrite(True)
                filexCommonSourceFile.setDestPath("../../third_party/azure_rtos/filex/common/src/")
                filexCommonSourceFile.setProjectPath("third_party/azure_rtos/filex/common/src/")
                filexCommonSourceFile.setType("SOURCE")
                filexCommonSourceFile.setEnabled(False)    
                filexCommonSourceFile.setDependencies(azureFileXFileEnable, ["AZURE_FILEX_ENABLE"])
    
    # Add H files from filex/common/inc
    filexCommonHeaderPath = os.path.join(filex_dir, "common", "inc")
    supportedExtension = ["h"]
    for root,dirs,files in os.walk(filexCommonHeaderPath):
        for headerFileName in files:
            if headerFileName.split(".")[-1].lower() in supportedExtension:
                commonInc = headerFileName.replace(".", "_").upper()
                filexCommonHeaderFile = azureIOTComponent.createFileSymbol(commonInc, None)
                filexCommonHeaderFile.setRelative(False)
                filexCommonHeaderFile.setSourcePath(os.path.join(root, headerFileName))
                filexCommonHeaderFile.setOutputName(headerFileName)
                filexCommonHeaderFile.setMarkup(False)
                filexCommonHeaderFile.setOverwrite(True)
                filexCommonHeaderFile.setDestPath("../../third_party/azure_rtos/filex/common/inc/")
                filexCommonHeaderFile.setProjectPath("third_party/azure_rtos/filex/common/inc/")
                filexCommonHeaderFile.setType("HEADER")
                filexCommonHeaderFile.setEnabled(False)
                filexCommonHeaderFile.setDependencies(azureFileXFileEnable, ["AZURE_FILEX_ENABLE"])

    # Add H files from filex/ports/<core>/<toolchain>/inc
    filexPortsHeaderPath = os.path.join(filex_dir, "ports",arch,toolchain,"inc")
    supportedExtension = ["h"]
    for root,dirs,files in os.walk(filexPortsHeaderPath):
        for headerFileName in files:
            if headerFileName.split(".")[-1].lower() in supportedExtension:
                portsInc = headerFileName.replace(".", "_").upper()
                filexPortsHeaderFile = azureIOTComponent.createFileSymbol(portsInc, None)
                filexPortsHeaderFile.setRelative(False)
                filexPortsHeaderFile.setSourcePath(os.path.join(root, headerFileName))
                filexPortsHeaderFile.setOutputName(headerFileName)
                filexPortsHeaderFile.setMarkup(False)
                filexPortsHeaderFile.setOverwrite(True)
                filexPortsHeaderFile.setDestPath("../../third_party/azure_rtos/filex/ports/" + arch + "/" + toolchain + "/inc/")
                filexPortsHeaderFile.setProjectPath("third_party/azure_rtos/filex/ports/" + arch + "/" + toolchain + "/inc/")
                filexPortsHeaderFile.setType("HEADER")
                filexPortsHeaderFile.setEnabled(False)
                filexPortsHeaderFile.setDependencies(azureFileXFileEnable, ["AZURE_FILEX_ENABLE"])

    filexPortPath = azureIOTComponent.createSettingSymbol("FILEX_PORT_PATH", None)
    filexPortPath.setValue("../src/third_party/azure_rtos/filex/ports/" + arch +"/gnu/inc")
    filexPortPath.setCategory("C32")
    filexPortPath.setKey("extra-include-directories")
    filexPortPath.setAppend(True, ";")      
    filexPortPath.setEnabled(False)
    filexPortPath.setDependencies(azureFileXFileEnable, ["AZURE_FILEX_ENABLE"])
    
    azureNetXSysConfigHeaderFile = azureIOTComponent.createFileSymbol(None, None)
    azureNetXSysConfigHeaderFile.setSourcePath("../net/sys_adapter/system_config.h")    
    azureNetXSysConfigHeaderFile.setOutputName("system_config.h")
    azureNetXSysConfigHeaderFile.setDestPath("")
    azureNetXSysConfigHeaderFile.setProjectPath("config/" + configName + "/")
    azureNetXSysConfigHeaderFile.setType("HEADER")
    azureNetXSysConfigHeaderFile.setOverwrite(True)   
    
    azureNetXSysTimeAdapterHeaderFile = azureIOTComponent.createFileSymbol(None, None)
    azureNetXSysTimeAdapterHeaderFile.setSourcePath("../net/sys_adapter/sys_time_h2_adapter.h")
    azureNetXSysTimeAdapterHeaderFile.setOutputName("sys_time_h2_adapter.h")
    azureNetXSysTimeAdapterHeaderFile.setDestPath("system/")
    azureNetXSysTimeAdapterHeaderFile.setProjectPath("config/" + configName + "/system/")
    azureNetXSysTimeAdapterHeaderFile.setType("HEADER")
    azureNetXSysTimeAdapterHeaderFile.setOverwrite(True)
    
    azureNetXSysTimeAdapterSourceFile = azureIOTComponent.createFileSymbol(None, None)
    azureNetXSysTimeAdapterSourceFile.setSourcePath("../net/sys_adapter/sys_time_h2_adapter.c")
    azureNetXSysTimeAdapterSourceFile.setOutputName("sys_time_h2_adapter.c")
    azureNetXSysTimeAdapterSourceFile.setOverwrite(True)
    azureNetXSysTimeAdapterSourceFile.setDestPath("system/")
    azureNetXSysTimeAdapterSourceFile.setProjectPath("config/" + configName + "/system/")
    azureNetXSysTimeAdapterSourceFile.setType("SOURCE")
    azureNetXSysTimeAdapterSourceFile.setEnabled(True)

    azureNetXLdSetting = azureIOTComponent.createSettingSymbol("AZURE_XC32_LD_SETTING", None)
    azureNetXLdSetting.setCategory("C32-LD")
    azureNetXLdSetting.setKey("additional-options-use-response-files")
    azureNetXLdSetting.setValue("true")                

def azureNetXIPComConverter(symbol, event):    
    symbol.setValue(event["value"].replace(".", ","))
    
def azureNetXMenuVisibility(symbol, event):    
    symbol.setVisible(event["value"])

def azureNetXMenuInvisibility(symbol, event):    
    symbol.setVisible(not event["value"])
    
def azureNetXCSdkMenuVisibility(symbol, event):    
    symbol.setVisible(event["value"])
    
def azureNetXCSdkMenuInvisibility(symbol, event):    
    symbol.setVisible(not event["value"])

def azureNetXCSdkAuthVisibility(symbol, event): 
    if event["value"] == 0:
        if symbol.getID() == "DEVICE_SYMMETRIC_KEY":
            symbol.setVisible(True)
        else:
            symbol.setVisible(False)
    else:
        if symbol.getID() == "DEVICE_SYMMETRIC_KEY":
            symbol.setVisible(False)
        else:
            symbol.setVisible(True)      
    
def azureNetXCSdkEnable(symbol, event):  
    azureComponent = symbol.getComponent()
    # Enable NetX Secure
    azureComponent.setSymbolValue("NX_SECURE_ENABLE", event["value"])
    # Enable NetX Crypto
    azureComponent.setSymbolValue("NX_CRYPTO_LIB_ENABLE", event["value"])
    # Enable Azure IoT
    azureComponent.setSymbolValue("AZURE_IOT_ENABLE", event["value"])
    # Enable Cloud Addon
    azureComponent.setSymbolValue("CLOUD_ENABLE", event["value"])
    # Enable MQTT Addon
    azureComponent.setSymbolValue("MQTT_ENABLE", event["value"])
    # Enable SNTP Addon
    azureComponent.setSymbolValue("SNTP_ENABLE", event["value"])

def azureNetXCSdkSampleConfig(symbol, event):  
    symbol.setEnabled(event["value"]) 
    
def azureNetXAddonFileEnable(symbol, event):  
    symbol.setEnabled(event["value"])

def azureNetXPathEnable(symbol, event):  
    symbol.setEnabled(event["value"])    
    
def azureNetXCryptoFileEnable(symbol, event):  
    symbol.setEnabled(event["value"])
    
def azureNetXSecureFileEnable(symbol, event):    
    symbol.setEnabled(event["value"])
    
def azureFileXFileEnable(symbol, event):  
    symbol.setEnabled(event["value"])
    
#Handle messages from other components
def handleMessage(messageID, args):
    global azureNetXInterfaceNum
    retDict= {}
    if (messageID == "SET_SYMBOL"):
        print "handleMessage: Set Symbol"
        retDict= {"Return": "Success"}
        Database.setSymbolValue(args["Component"], args["Id"], args["Value"])
    elif (messageID == "AZURE_INTERFACE_COUNTER_INC"):
        interface_count = azureNetXInterfaceNum.getValue()
        azureNetXInterfaceNum.setValue( interface_count + 1)
        retDict= {"Return": "Success"}
    elif (messageID == "AZURE_INTERFACE_COUNTER_DEC"):
        interface_count = azureNetXInterfaceNum.getValue()
        azureNetXInterfaceNum.setValue(interface_count - 1)
        retDict= {"Return": "Success"}
    else:
        retDict= {"Return": "UnImplemented Command"}
    return retDict
      
#Set symbols of other components
def setVal(component, symbol, value):
    triggerDict = {"Component":component,"Id":symbol, "Value":value}
    if(Database.sendMessage(component, "SET_SYMBOL", triggerDict) == None):
        print "Set Symbol Failure" + component + ":" + symbol + ":" + str(value)
        return False
    else:
        return True

def finalizeComponent(azureIOTComponent):  
    # Enable DHCP by default
    azureIOTComponent.setSymbolValue("DHCP_ENABLE", True)
    
    # Enable DNS by default
    azureIOTComponent.setSymbolValue("DNS_ENABLE", True)
  