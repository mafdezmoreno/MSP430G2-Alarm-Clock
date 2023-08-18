# MSP430G2-Alarm-Clock

## Introduction

## Hardware Requirements

 - MCU: msp430g2553 or similar (with enough memory).
 - External low frequency clock (32768Hz).
 - PCB, proto board, something to build the circuit.
 - Programmer. In my case I'm using the programmer of a launchpad.

Warning: LaunchPads with eZ430-RF2500 will not work with linux or mac, look for launchpads with eZ-FET interface.

### Functions Implemented

 - [x] Clock
 - [ ] Control to set clock time
 - [ ] Alarm
 - [ ] Control to set alarm
 - [ ] Date

## Compiling the Code

There are two principal compiler options:
 * Ti Compiler, included in [CSStudio IDE](https://www.ti.com/tool/CCSTUDIO) (recommended).
 * [GNU Compiler](https://www.ti.com/tool/MSP430-GCC-OPENSOURCE) 

The best way to avoid problems is develop uding CSStudio and Ti compiler. Trying another options can ba a frustrating process.

Anyway, I prefer to generate/update the makefile with CSS and then work with Clion or VSCode.

I've also tried to create a cMake projects, based on [AlexanderSidorenko repo](https://github.com/AlexanderSidorenko/msp-cmake), but with no success by now.

## Flashing the MCU
There are several tools to flash the compiled code into the MSC:
 * Code Composer Studio, which uses internally MSP430Flasher (recomended).
 * [MSP430Flasher](https://www.ti.com/tool/MSP430-FLASHER) cl software and your favourite text editor (more work). A 'upload' make argument can be manually placed inside the CSS generated makefile.
 * [mpsdebuger](https://dlbeer.co.nz/mspdebug/). This was my favourite in the past, but I was unable to make in work, maybe mspdebuger is not compatible with current TI compiler.

[More info about upload code using MSP430Flasher here](https://github.com/mafdezmoreno/Testing_MSP430G2)

### Hadware Connections:

Connect the following signals from the debugger to the target MCU.

 * 3.3V
 * GND
 * SBWTDIO
 * SBWTCK
 * TXD (if the UART backchannel is to be used)
 * RXD (if the UART backchannel is to be used)

## Schematics and PCB

A Kicad project is included in this repo. This projects include schematics and PCB.

Todo:
 - [ ] Review of connections
 - [ ] PCB Design
 - [ ] Gerber files generation and PCB ordering.

## Other Comments and Problems Working With MSP430


