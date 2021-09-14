---
grand_parent: Harmony 3 Azure RTOS ThreadX configurations and application examples
parent: Basic ThreadX
title: Building and Running on SAMA7G5 Evaluation Kit
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
| sam_a7g5_ek.X | MPLABX project for [SAMA7G5 Evaluation Kit]() |

## Setting up the hardware

The following table shows the target hardware for the application projects.

| Project Name| Board|
|:---------|:---------:|
| sam_a7g5_ek.X | [SAMA7G5 Evaluation Kit]() |
|||

### Setting up [SAMA7G5 Evaluation Kit]()

#### Addtional hardware required

- SD Card with FAT32 file system

#### Setting up the SD Card

- Download harmony MPU bootstrap loader from this [location](firmware/at91bootstrap_sam_a7g5_ek.X/build/binaries/boot.bin)
- Copy the downloaded boot loader binary(boot.bin) onto the SD card

#### Setting up the board

- SDMMC slot used for bootloading the application is SDMMC1 (J4)
- Connect the USB port J7 on board to the computer using a micro USB cable (to power the board)
- Connect the USB port J24 on board to the computer using a micro USB cable (to enable debug com port)

## Running the Application

1. Build the application using its IDE
2. Copy the output binary (named 'harmony.bin') onto the SD Card (Refer to the 'Setting up hardware' section above for setting up the SD card)
3. Insert the SD card into SDMMC slot on the board (Refer to the 'Setting up hardware' section for the correct SDMMC slot)
4. Reset the board to run the application
5. The LED indicates the success or failure.
    - The LED toggles on success i.e. for every 500 ms.

Refer to the following table for LED name:  

| Board | LED Name |
| ----- | -------- |
|  [SAMA7G5 Evaluation Kit]()  | RGB_LED(Green) |
|||
