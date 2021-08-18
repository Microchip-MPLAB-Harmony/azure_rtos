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

def instantiateComponent(azureIOTComponent, index):
    configName = Variables.get("__CONFIGURATION_NAME")  
    
    interface_counter_dict = {}
    interface_counter_dict = Database.sendMessage("lib_azure_rtos", "AZURE_INTERFACE_COUNTER_INC", interface_counter_dict)
    
    # Network interface Number
    azureNetxIfConfigNum = azureIOTComponent.createIntegerSymbol("AZURE_INTERFACE_CONFIG_NUMBER", None)
    azureNetxIfConfigNum.setLabel("Network Interface Index")
    azureNetxIfConfigNum.setVisible(True)
    azureNetxIfConfigNum.setValue(int(str(index)),1)
    azureNetxIfConfigNum.setReadOnly(True)

    # Network interface name
    azureNetxIfName = azureIOTComponent.createStringSymbol("AZURE_INTERFACE_DEFAULT_INTERFACE_NAME_IDX" + str(index),None)   
    azureNetxIfName.setLabel("Interface")
    azureNetxIfName.setVisible(True)
    azureNetxIfName.setDefaultValue("")
    azureNetxIfName.setReadOnly(True)

    # Network Interface MAC address
    azureNetxIfMacAddress = azureIOTComponent.createStringSymbol("AZURE_INTERFACE_DEFAULT_MAC_ADDR_IDX" + str(index),None)
    azureNetxIfMacAddress.setLabel("Mac Address")
    azureNetxIfMacAddress.setVisible(True)
    azureNetxIfMacAddress.setDefaultValue("")
    azureNetxIfMacAddress.setDependencies(azureNetxIfMacAddrUpdate, [azureNetxIfName.getID()])

    
    # Network Interface MAC Driver Object
    azureNetxIfDrvObj = azureIOTComponent.createStringSymbol("AZURE_INTERFACE_DEFAULT_DRIVER_IDX" + str(index),None)
    azureNetxIfDrvObj.setLabel("Interface Driver Object")
    azureNetxIfDrvObj.setVisible(True)
    azureNetxIfDrvObj.setDefaultValue("")
    azureNetxIfDrvObj.setDependencies(azureNetxIfDrvObjUpdate, [azureNetxIfName.getID()])
    
    
    azureNetxIfConfigFile = azureIOTComponent.createFileSymbol("AZURE_INTERFACE_CONFIG", None)
    azureNetxIfConfigFile.setType("STRING")
    azureNetxIfConfigFile.setOutputName("core.LIST_SYSTEM_CONFIG_H_MIDDLEWARE_CONFIGURATION")
    azureNetxIfConfigFile.setSourcePath("third_party_adapter/azure_rtos/config/azureRtos_interface_idx.h.ftl")
    azureNetxIfConfigFile.setMarkup(True)

def azureNetxIfMacAddrUpdate(symbol, event):   
    interfaceToMacAddress = {
        'GMAC':         '00:04:25:1C:A0:02',
        'EMAC0':        '00:04:25:1C:A0:03',
        'EMAC1':        '00:04:25:1C:A0:04',
        'ENC28J60':     '00:04:a3:12:34:56',
    }

    azureInterfaceName = event["value"]
    symbol.clearValue()
    macAddress = interfaceToMacAddress.get( azureInterfaceName, '' )
    if len( macAddress ):
        symbol.setValue( macAddress )
    else:
        if( azureInterfaceName == "ETHMAC" ):
            if "DA" in Variables.get("__PROCESSOR"):
                symbol.setValue( "c4:de:39:75:d8:80" )
      
def azureNetxIfDrvObjUpdate(symbol, event):
    interfaceToMacObject = {
        'ETHMAC':       'DRV_ETHMAC_PIC32MACObject',
        'GMAC':         'DRV_GMAC_Object',
        'ENCX24J600':   'DRV_ENCX24J600_MACObject',
        'ENC28J60':     'DRV_ENC28J60_MACObject',
        'EMAC0':        'DRV_EMAC0_Object',
        'EMAC1':        'DRV_EMAC1_Object',
        'MRF24WN':      'WDRV_MRF24WN_MACObject',
        'WINC':         'WDRV_WINC_MACObject',
        'WINC1500':     'WDRV_WINC1500_MACObject',
        'WILC1000':     'WDRV_WILC1000_MACObject',
        'PIC32MZW1':    'WDRV_PIC32MZW1_MACObject',
    }

    symbol.clearValue()
    symbol.setValue( interfaceToMacObject.get( event[ "value" ], '' ) )
    
    Database.getSymbolValue("HarmonyCore", "ENABLE_OSAL")
    if (event[ "value" ] == 'MRF24WN') or (event[ "value" ] == 'WINC') or (event[ "value" ] == 'WINC1500') or (event[ "value" ] == 'WILC1000') or (event[ "value" ] == 'PIC32MZW1'):
        # For wireless, set mac data segment gap size = 34 
        setVal("lib_azure_rtos", "MAC_DATA_GAP_SIZE", 34)
    else:
        if (Database.getSymbolValue("lib_azure_rtos", "MAC_DATA_GAP_SIZE") < 4) : 
            setVal("lib_azure_rtos", "MAC_DATA_GAP_SIZE", 4)

def onAttachmentConnected(source, target):
    if (source["id"] == "AZURE_MAC_Dependency"):
        azureInterfaceIndex = int(source["component"].getID().strip("lib_azure_rtos_"))
        drvInterface = source["component"].getSymbolByID("AZURE_INTERFACE_DEFAULT_INTERFACE_NAME_IDX"+str(azureInterfaceIndex))
        if( drvInterface ):
            drvInterface.clearValue()
            drvInterface.setValue( target["component"].getDisplayName() )
               
def onAttachmentDisconnected(source, target):
    if (source["id"] == "AZURE_MAC_Dependency"):    
        azureInterfaceIndex = int(source["component"].getID().strip("lib_azure_rtos_"))
        source["component"].clearSymbolValue("AZURE_INTERFACE_DEFAULT_INTERFACE_NAME_IDX"+str(azureInterfaceIndex))

#Set symbols of other components
def setVal(component, symbol, value):
    triggerDict = {"Component":component,"Id":symbol, "Value":value}
    if(Database.sendMessage(component, "SET_SYMBOL", triggerDict) == None):
        print "Set Symbol Failure" + component + ":" + symbol + ":" + str(value)
        return False
    else:
        return True

#Handle messages from other components
def handleMessage(messageID, args):
    retDict= {}
    if (messageID == "SET_SYMBOL"):
        print "handleMessage: Set Symbol"
        retDict= {"Return": "Success"}
        Database.setSymbolValue(args["Component"], args["Id"], args["Value"])
    else:
        retDict= {"Return": "UnImplemented Command"}
    return retDict
      
def destroyComponent(azureIOTComponent):
    interface_counter_dict = {}
    interface_counter_dict = Database.sendMessage("lib_azure_rtos", "AZURE_INTERFACE_COUNTER_DEC", interface_counter_dict)    
