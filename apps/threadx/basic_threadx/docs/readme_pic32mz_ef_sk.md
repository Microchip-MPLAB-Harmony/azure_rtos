---
grand_parent: Harmony 3 Azure RTOS ThreadX configurations and application examples
parent: Basic ThreadX
title: Building and Running on PIC32MZ Embedded Connectivity with FPU (EF) Starter Kit
has_toc: false
---

[![MCHP](https://www.microchip.com/ResourcePackages/Microchip/assets/dist/images/logo.png)](https://www.microchip.com)

# Basic ThreadX

This example application blinks an LED to show the Azure RTOS ThreadX threads that are running and to indicate status

## Description

This demonstration creates a task which toggle an LED for every 500ms. 

## Downloading and building the application

To clone or download these applications from Github, go to the [main page of this repository](https://github.com/Microchip-MPLAB-Harmony/azure_rtos) and then click **Clone** button to clone this repository or download as zip file. This content can also be downloaded using content manager by following these [instructions](https://github.com/Microchip-MPLAB-Harmony/contentmanager/wiki)

Path of the application within the repository is **apps/threadx/basic_threadx/firmware/**

To build the application, refer to the following table and open the project using its IDE.

### Azure RTOS ThreadX Application

| Project Name      | Description                                    |
| ----------------- | ---------------------------------------------- |
| pic32mz_ef_sk.X  | MPLABX Project for [PIC32MZ Embedded Connectivity with FPU (EF) Starter Kit](https://www.microchip.com/Developmenttools/ProductDetails/Dm320007) |

## Setting up [PIC32MZ Embedded Connectivity with FPU (EF) Starter Kit](https://www.microchip.com/Developmenttools/ProductDetails/Dm320007)

- Connect a mini USB cable to the USB Debug port J3

## Running the Application

1. Build and program the application using the MPLAB X IDE
2. The LED indicates the success or failure.
    - The LED toggles on success i.e. for every 500 ms.

Refer to the following table for LED name:  

| Board | LED Name |
| ----- | -------- |
| [PIC32MZ Embedded Connectivity with FPU (EF) Starter Kit](https://www.microchip.com/Developmenttools/ProductDetails/Dm320007) | LED1 |
|||
