# Embedded Controller - RCC Library

Written by: Woorim Lee

Program: C/C++

IDE/Compiler: PlatformIO

OS: Win10/11

MCU: STM32F411RE, Nucleo-64



## Table of Contents

* [RCC](#RCC)
  * [Header File](#header-file)
  * [delay_ms_HSI()](#delay_ms_HSI)
  * [RCC_HSI_init()](#RCC_HSI_init)
  * [RCC_PLL_init()](#RCC_PLL_init)
  * [RCC_GPIOA_enable()](#RCC_GPIOA_enable)
  * [RCC_GPIOB_enable()](#RCC_GPIOB_enable)
  * [RCC_GPIOC_enable()](#RCC_GPIOC_enable)
  * [RCC_GPIOD_enable()](#RCC_GPIOD_enable)
  * [RCC_GPIOD_enable()](#RCC_GPIOD_enable)

RCC_GPIO structure로 만들기



## EXTI

### Header File

`#include "ecRCC2.h"`

```c
#ifndef __EC_RCC2_H
#define __EC_RCC2_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#include "stm32f4xx.h"
#include "stm32f411xe.h"
#include "ecPinNames.h"

extern volatile int EC_SYSCLK;		// current SYSCLK [Hz], set by RCC_HSI_init()/RCC_PLL_init()
void delay_ms_HSI(uint32_t ms); 
void RCC_HSI_init(void);
void RCC_PLL_init(void);
void RCC_GPIOA_enable(void);
void RCC_GPIOB_enable(void);
void RCC_GPIOC_enable(void);

void RCC_GPIOD_enable(void);
void RCC_GPIOE_enable(void);
// void RCC_GPIO_enable(GPIO_TypeDef * GPIOx);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __EC_RCC2_H

```



#### delay_ms_HSI()

Generates a software-based delay in milliseconds utilizing the High-Speed Internal (HSI) clock.

```
void delay_ms_HSI(uint32_t ms); 
```

**Parameters**

- **ms:** The amount of time to delay, in milliseconds.

**Example code**

```c
delay_ms_HSI(1000);  // Delays the program execution for 1000 ms (1 second)
```



#### RCC_HSI_init()

Initializes the system clock to use the 16 MHz High-Speed Internal (HSI) oscillator. It configures the flash latency and updates the global `EC_SYSCLK` variable.

```c
void RCC_HSI_init(void);c
```

**Parameters**

- **None**

**Example code**

```c
RCC_HSI_init();  // System clock is now set to 16 MHz
```



#### void RCC_PLL_init()

Initializes the system clock using the Phase-Locked Loop (PLL) to boost the core clock frequency. For the STM32F411RE, this typically configures the system clock to its maximum of 84 MHz.

```c
void RCC_PLL_init(void);
```

**Parameters**

- **None**

**Example code**

```c
RCC_PLL_init();  // System clock is now boosted to 84 MHz via PLL
```



#### RCC_GPIOA_enable()

Enables the peripheral clock for GPIO Port A by setting the corresponding bit in the RCC AHB1 peripheral clock enable register (`RCC_AHB1ENR`).

```c
void RCC_GPIOA_enable(void);
```

**Parameters**

- **None**

**Example code**

```c
RCC_GPIOA_enable();  // Activates clock for GPIOA
```



#### RCC_GPIOB_enable()

Enables the peripheral clock for GPIO Port B.

```c
void RCC_GPIOB_enable(void);
```

**Parameters**

- **None**

**Example code**

```c
RCC_GPIOB_enable();  // Activates clock for GPIOB
```



#### RCC_GPIOC_enable()

Enables the peripheral clock for GPIO Port C.

```c
void RCC_GPIOC_enable(void);
```

**Parameters**

- **None**

**Example code**

```c
RCC_GPIOC_enable();  // Activates clock for GPIOC
```



#### RCC_GPIOD_enable()

Enables the peripheral clock for GPIO Port D.

```c
void RCC_GPIOD_enable(void);
```

**Parameters**

- **None**

**Example code**

```c
RCC_GPIOD_enable();  // Activates clock for GPIOD
```



#### RCC_GPIOE_enable()

Enables the peripheral clock for GPIO Port E.

```c
void RCC_GPIOE_enable(void);
```

**Parameters**

- **None**

**Example code**

```c
RCC_GPIOE_enable();  // Activates clock for GPIOE
```

