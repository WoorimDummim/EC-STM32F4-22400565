# Embedded Controller - SysTick Library

Written by: Woorim Lee

Program: C/C++

IDE/Compiler: PlatformIO

OS: Win10/11

MCU: STM32F411RE, Nucleo-64



## Table of Contents

* [SysTick](#SysTick)
  * [Header File](#header-file)
  * [SysTick_init()](#SysTick_init)
  * [SysTick_Handler()](#SysTick_Handler)
  * [SysTick_counter()](#SysTick_counter)
  * [delay_msI()](#delay_ms)
  * [SysTick_reset](#SysTick_reset)
  * [SysTick_val](#SysTick_val)



## SysTick

### Header File

`#include "ecSysThick2.h"`

```c
#ifndef __EC_SYSTICK2_H
#define __EC_SYSTICK2_H

#include "stm32f4xx.h"
#include "ecRCC2.h"
#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */


extern volatile uint32_t msTicks;	

void SysTick_init(void);
void SysTick_Handler(void);
void SysTick_counter(void);
void delay_ms(uint32_t msec);
void SysTick_reset(void);
uint32_t SysTick_val(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __EC_SYSTICK2_H

```



#### SysTick_init()

Initializes the SysTick timer to generate hardware interrupts at regular intervals (typically exactly 1 millisecond). It automatically configures the reload value based on the current system clock (`EC_SYSCLK`).

```c
void SysTick_init(void);
```

**Parameters**

- **None**

**Example code**

```c
SysTick_init();  // Starts the SysTick timer with a 1 ms interrupt interval
```



#### SysTick_Handler()

The Interrupt Service Routine (ISR) for the SysTick exception. This function is automatically triggered by the hardware every time the SysTick counter reaches zero.

```c
void SysTick_Handler(void);
```

**Parameters**

- **None**

**Example code**

```c
// This function is automatically called by the hardware.
// Do not call it manually in the main loop.
void SysTick_Handler(void) {
    SysTick_counter();
}
```



#### SysTick_counter()

Increments the global `msTicks` variable. This function is designed to be called internally within the `SysTick_Handler()` to maintain an accurate count of elapsed milliseconds since startup.

```c
void SysTick_counter(void);
```

**Parameters**

- **None**

**Example code**

```c
SysTick_counter();  // Adds 1 to the msTicks variable
```



#### delay_ms()

Creates a precise software delay in milliseconds by continuously checking the hardware-updated `msTicks` variable.

```c
void delay_ms(uint32_t msec);
```

**Parameters**

- **msec:** The desired delay time in milliseconds.

**Example code**

```c
delay_ms(1000);  // Halts the program execution for exactly 1000 ms (1 second)
```



#### SysTick_reset()

Resets the hardware SysTick Current Value Register (`SysTick->VAL`) and clears the global `msTicks` tracking variable to zero.

```c
void SysTick_reset(void);
```

**Parameters**

- **None**

**Example code**

```c
SysTick_reset();  // Clears the tick counter for a fresh start
```



#### SysTick_val()

Reads and returns the current hardware value straight from the SysTick Current Value Register (`SysTick->VAL`). Useful for sub-millisecond or microsecond level measurements.

``` c
uint32_t SysTick_val(void);
```

**Parameters**

- **None**

**Example code**

```c
uint32_t currentTimerValue = SysTick_val();
```



