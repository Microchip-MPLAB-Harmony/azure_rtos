# coding: utf-8
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

def loadModule():
    thirdPartyThreadX = Module.CreateComponent("ThreadX", "ThreadX", "/Third Party Libraries/RTOS/", "threadx/config/threadx.py")
    thirdPartyThreadX.setDisplayType("Third Party Library")
    thirdPartyThreadX.addCapability("ThreadX", "RTOS", True)
    execfile(Module.getPath() + "/threadx/config/threadx.py")

######################  Azure RTOS Library  ######################
    # Azure IoT
    azureIOTComponent = Module.CreateGeneratorComponent("lib_azure_rtos", "Azure RTOS", "/Third Party Libraries/AzureRtos/", "third_party_adapter/azure_rtos/config/azureRtos_common.py","third_party_adapter/azure_rtos/config/azureRtos.py" )
    azureIOTComponent.addCapability("lib_azure_rtos","azure_rtos",True)
    azureIOTComponent.addDependency("AZURE_MAC_Dependency", "MAC")
    azureIOTComponent.addDependency("Azure_SysTime_Dependency", "SYS_TIME", None, True, True)
    # azureIOTComponent.addDependency("Azure_SysConsole_Dependency", "SYS_CONSOLE", None, False, False)
    azureIOTComponent.setDisplayType("Thirdparty")

