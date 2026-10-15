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

/*---------------------------------------------------------------- 
                    [EXERCISE]
---------------------------------------------------------------- */
void RCC_GPIOD_enable(void);
void RCC_GPIOE_enable(void);
// void RCC_GPIO_enable(GPIO_TypeDef * GPIOx);



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __EC_RCC2_H

```



#### delay_ms_HSI()



```
void delay_ms_HSI(uint32_t ms); 
```

**Parameters**

- **ms:** 

  

**Example code**

```c

```



#### RCC_HSI_init()



```
void RCC_HSI_init(void);
```

**Parameters**

- **void:**

  

**Example code**

```

```



#### void RCC_PLL_init()



```
void RCC_PLL_init(void);
```

**Parameters**

- **void:**

  

**Example code**

```

```



#### RCC_GPIOA_enable()



```c
void RCC_GPIOA_enable(void);
```

**Parameters**

- **void:**

  

**Example code**

```

```



#### RCC_GPIOB_enable()



```c
void RCC_GPIOB_enable(void);
```

**Parameters**

- **void:**

  

**Example code**

```

```



#### RCC_GPIOC_enable()



```c
void RCC_GPIOC_enable(void);
```

**Parameters**

- **void:**

  

**Example code**

```

```



#### RCC_GPIOD_enable()



```c
void RCC_GPIOD_enable(void);
```

**Parameters**

- **void:**

  

**Example code**

```

```



#### RCC_GPIOE_enable()



```c
void RCC_GPIOE_enable(void);
```

**Parameters**

- **void:**

  

**Example code**

```

```

