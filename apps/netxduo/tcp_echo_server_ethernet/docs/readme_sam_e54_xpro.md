---
grand parent: Harmony 3 Azure RTOS configurations and application examples
parent: Azure NetX Duo Demo Ethernet
title: Building and Running on SAM E54 Xplained Pro Evaluation Kit
has_toc: false
---

[![MCHP](https://www.microchip.com/ResourcePackages/Microchip/assets/dist/images/logo.png)](https://www.microchip.com)

# Azure  NetX Duo Demo Ethernet

This example application implements a TCP echo server using an Ethernet connection

## Description

This demonstration implements a TCP echo server using an Ethernet connection.

Refer to the full Microsoft documentation for this application: TBD.

## Downloading and building the application

To clone or download these applications from Github, go to the [main page of this repository](https://github.com/Microchip-MPLAB-Harmony/azure_rtos) and then click **Clone** button to clone this repository or download as zip file. This content can also be downloaded using content manager by following these [instructions](https://github.com/Microchip-MPLAB-Harmony/contentmanager/wiki)

Path of the application within the repository is **apps/netxduo/tcp_echo_server_ethernet/firmware/**

To build the application, refer to the following table and open the project using its IDE.

### Azure  NetX Duo Demo Ethernet Application

| Project Name      | Description                                    |
| ----------------- | ---------------------------------------------- |
| sam_e54_xpro.X  | MPLABX Project for [SAM E54 Xplained Pro Evaluation Kit](https://www.microchip.com/developmenttools/ProductDetails/atsame54-xpro) |

## Setting up [SAM E54 Xplained Pro Evaluation Kit](https://www.microchip.com/developmenttools/ProductDetails/atsame54-xpro)

- Connect the Debug USB port on the board to the computer using a micro USB cable

## Running the Application

1. Build and program the application using the MPLAB X IDE
2. The board has a SERCOM configuration:
    1. A virtual COM port will be detected on the computer, when the USB cable is connected to USB-UART connector.
    2. Open a standard terminal application on the computer (like Hyper-terminal or Tera Term) and configure the virtual COM port.
    3. Set the serial baud rate to 115200 baud in the terminal application.
    4. See that the initialization prints on the serial port terminal.
3. Connect with a client TCP socket to the board IP address, using port 7
4. Type a message to the server. The server will echo back the message to the client and close the connection.
5. Another connection can then be started.
6. Refer to the full Microsoft documentation for this application: TBD.

