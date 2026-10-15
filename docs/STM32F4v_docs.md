# Embedded Controller - STM32F4v2 Library
Written by: Woorim Lee

Program: C/C++

IDE/Compiler: PlatformIO

OS: Windows / Ubuntu 24.04

MCU: STM32F411RE, Nucleo-64



## Table of Contents
* [STM32F4v2](#stm32f4v2)
  * [Header File](#header-file)
  * [MCU_init()](#mcu_init)



## STM32F4v2

### Header File

`#include "ecSTM32F4v2.h"`

```c
#ifndef __EC_STM_H
#define __EC_STM_H

// STM built-In Library
#include "stm32f4xx.h"
#include "stm32f411xe.h"
#include "math.h"

// EC course Library
#include "ecPinNames.h"
#include "ecRCC2.h"
#include "ecGPIO2.h"
#include "ecEXTI2.h"
#include "ecSysTick2.h"

extern PinName_t pinFND[8];
extern PinName_t selectFND[4];

void MCU_init(void);

#endif // __EC_STM_H
```



#### MCU_init()

Acts as a master initialization function. It automatically configures the system clock (PLL) to 84 MHz, initializes the SysTick timer, and sets up default GPIO configurations for essential peripherals such as the Flexible Numeric Display (FND) to streamline the setup process in the main program.

```c
void MCU_init(void);
```

**Parameters**

- **None**

**Example code**

```c
int main(void) {
    MCU_init();  // Initializes System Clock, SysTick, and default peripherals in one line
    
    while(1) {
        // Main infinite loop
    }
}
```

