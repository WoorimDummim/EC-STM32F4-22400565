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

Initializes SysTick ~~

```
void SysTick_init(void);
```

**Parameters**

- **void:**

**Example code**

```c
SysTick_init(); 
```



#### SysTick_Handler()



```
void SysTick_Handler(void);
```

**Parameters**

- **void:**

  

**Example code**

```

```



#### SysTick_counter()



```
void SysTick_counter(void);
```

**Parameters**

- **void:**

  

**Example code**

```

```



#### delay_ms()



```c
void delay_ms(uint32_t msec);
```

**Parameters**

- **msec:**

  

**Example code**

```c
delay_ms (1000);
```



#### SysTick_reset()



```
void SysTick_reset(void);
```

**Parameters**

- **void:**

  

**Example code**

```c

```



#### SysTick_val()



``` c
uint32_t SysTick_val(void);
```

**Parameters**

- **void:**

  

**Example code**

```c

```



