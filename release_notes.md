![Microchip logo](https://raw.githubusercontent.com/wiki/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/images/microchip_logo.png)
![Harmony logo small](https://raw.githubusercontent.com/wiki/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/images/microchip_mplab_harmony_logo_small.png)

# Microchip MPLAB® Harmony 3 Release Notes

## Harmony Azure_RTOS Release v1.0.0 (September, 2021)
### ADDITIONS AND UPDATES FOR  1.0.0:


- **New Microsoft Azure-RTOS support** -This beta release introduces initial support for [Azure-RTOS](https://github.com/azure-rtos) a Microsoft RTOS for connecting deeply embedded IoT devices.

- **New part support** -This release introduces initial Azure RTOS ThreadX support for [Cortex-A7]() family of 32-bit MPUs.

- **New Applications**

The following table provides the list of the new applications included in the release:

| Application                 | Platform                        | Description |
| ------------ | ------------ |  ------------ |
| azure_iot_demo_ethernet   | SAME54    | Azure IoT hub connection example using an Ethernet connection |
| azure_iot_demo_wifi       | SAME54    | Azure IoT hub connection example using a Wi-Fi connection |
| tcp_echo_server_ethernet  | SAME54    | NetX Duo TCP server example using an Ethernet connection |
| tcp_echo_server_wifi      | SAME54    | NetX Duo TCP server example using a Wi-Fi connection |

- **Updated Applications**

The following table provides the list of the updated applications:

| Application  | Platform     | Description  |
| ------------ | ------------ | ------------ |
| basic_threadx  | SAMA7G5  | Basic ThreadX demo showing threads and status  |

### TESTED WITH:

#### Software Dependencies

Before using MPLAB Harmony Net, ensure that the following are installed:

- [MPLAB® X IDE v5.45](https://www.microchip.com/mplab/mplab-x-ide) or later
- [MPLAB® XC32 C/C++ Compiler v2.50](https://www.microchip.com/mplab/compilers) or later

In order to regenerate source code for any of the applications, you will also need to use the following versions of the dependent modules (see azure_rtos/package.xml):

- Harmony core repository, 3.9.2
- Harmony bsp repository, 3.9.0
- Harmony csp repository, 3.9.1
- Harmony dev_packs repository, 3.9.0
- Harmony net repository, v3.7.3
- Microsoft ThreadX repository, v6.1.8_rel (https://github.com/azure-rtos/threadx/tree/v6.1.8_rel)
- Microsoft azure-sdk-for-c, 1.0.0 (https://github.com/azure-rtos/netxduo/tree/v6.1.8_rel)
- Microsoft NetX Duo, v6.1.7_rel (https://github.com/azure-rtos/netxduo/tree/v6.1.7_rel)
- Microsoft FileX, v6.1.7_rel (https://github.com/azure-rtos/filex/tree/v6.1.7_rel)
- MPLAB Harmony Configurator (MHC) v.3.8.0 or later
- MPLAB® Harmony Configurator (MHC) plug-in, v3.6.3 or later


#### Development Kit Support

This release supports applications for the following development kits

| Development Kits |
| --- |
| [SAM E54 Xplained Pro Evaluation Kit](https://www.microchip.com/developmenttools/ProductDetails/ATSAME54-XPRO) |
| [SAM9X60-EK Evaluation Kit](https://www.microchip.com/developmenttools/ProductDetails/DT100126) |
| [SAMA5D2 Xplained Ultra Evaluation Kit](https://www.microchip.com/DevelopmentTools/ProductDetails/ATSAMA5D2C-XULT) |
| [SAMA7G5 Evaluation Kit]()  |


### KNOWN ISSUES

This is a beta release.
The current known issues are as follows:

* The demo project builds fine with MPLABX IDE 5.45. There is a known issue with MPLABX5.5 that cause build errors. This issue will be fixed in future MPLAB X releases.
If you are working with MPLAB X IDE 5.5, please follow the instructions as short-term workaround. 

1.	Update SAME54_DFP to the latest from MPLAB X IDE -> Tools -> Packs. (At the time of writing this instruction, latest version is 3.6.99)
2.	Copy "SAME54_DFP" directory  from  'C:\Program Files\Microchip\MPLABX\v5.50\packs\Microchip\' to 'C:\'
3.	Open Azure demo project in MPLAB X. Go to project properties.
4.	Select XC32 (Global Options) -> Override default device support -> set as 'Compiler Location'
5.	At XC32 (Global Options) ->Additional options ->set the following option:

    -mdfp=C:/SAME54_DFP/x.x.xx -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"
    
    For example, if SAME54 DFP is 3.6.99, the option is:
   
    -mdfp=C:/SAME54_DFP/3.6.99 -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"
6.	Click 'Apply' and 'OK'. Then build the project.


### RELEASE CONTENTS

This topic lists the contents of this release and identifies each module.

#### Description

This table lists the contents of this release, including a brief description, and the release type (Alpha, Beta, Production, or Vendor).


| Folder                                | Description                                                          | Release Type |
| --- | --- | --- |
| azure_rtos/apps/iot/azure_iot_demo_ethernet       | Azure IoT hub connection over Ethernet                    | Beta |
| azure_rtos/apps/iot/azure_iot_demo_wifi           | Azure IoT hub connection over Wi-Fi                       | Beta |
| azure_rtos/apps/netxduo/tcp_echo_server_ethernet  | TCP server example over Ethernet                          | Beta |
| azure_rtos/apps/netxduo/tcp_echo_server_wifi      | TCP server example over Wi-Fi                             | Beta |
| azure_rtos/apps/threadx/basic_threadx             | Basic ThreadX demo showing threads and status             | Beta |

