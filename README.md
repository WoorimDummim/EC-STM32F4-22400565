# Embedded Controller

**Date:** 2026-09-20

**Author/Partner:** WoorimLee



## Introduction

​	This repository contains the source code, custom libraries, and documentation for the **Embedded Controller** course. 

​	The projects are developed using the **STM32F411RE (NUCLEO-F411RE)** microcontroller within the PlatformIO IDE environment on Visual Studio Code.  The primary objective of this repository is to build a custom Hardware Abstraction Layer (HAL) from scratch and apply it to various embedded system applications. 

​	Throughout the course, low-level registers are manipulated to implement drivers for GPIO, EXTI, SysTick, Stepper Motors, and UART communication.

 ## Repository Structure The workspace is structured to separate custom library headers, lab assignments, and tutorial exercises.



## Documentation

[See here for API documentation](https://github.com/ykkimhgu/NumericalProg-student/blob/main/docs/NP_API_Documentation.md)



## Contents

This repository contains 

- `\include` : header and definition files of EC_HAL lib 

-  `\docs` : documentation 

-  `\lab` : assignment source files for main() 

-  `\tutorial` : tutorial source files for practice 

- `\report` : lab reports and result analysis files 

  

and more **Notes:** This workspace is built using the PlatformIO environment in Visual Studio Code. It is highly modularized to separate the reusable custom Hardware Abstraction Layer (HAL) from the application codes. All peripheral drivers are implemented at the register level without relying on heavy external frameworks.



## Environment

#### Hardware & Software Requirements

- **Microcontroller:** NUCLEO-F411RE (STM32F411RE)
- **Actuators & Sensors:** LEDs, 7-Segment Displays, Push Buttons, Photo-sensors, Stepper Motors (ULN2003, A4988)
- **IDE & Tools:** Visual Studio Code, PlatformIO
- **Languages:** C / C++