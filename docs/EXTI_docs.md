# Embedded Controller - EXTI Library

Written by: Woorim Lee

Program: C/C++

IDE/Compiler: PlatformIO

OS: Win10/11

MCU: STM32F411RE, Nucleo-64



## Table of Contents

* [EXTI](#EXTI)
  * [Header File](#header-file)
  * [EXTI_init()](#EXTI_init)
  * [EXTI_enable()](#EXTI_enable)
  * [EXTI_disable()](#EXTI_disable)
  * [is_pending_EXTI()](#is_pending_EXTI)
  * [clear_pending_EXTI](#clear_pending_EXTI)



## EXTI

### Header File

`#include "ecEXTI2.h"`

```c
#ifndef __EC_EXTI2_H
#define __EC_EXTI2_H

#include "stm32f411xe.h"
#include "ecPinNames.h"

#define FALL 0
#define RISE 1
#define BOTH 2

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

void EXTI_init(PinName_t pinName, uint32_t trig_type,uint32_t priority);
void EXTI_enable(PinName_t pinName);
void EXTI_disable(PinName_t pinName);
uint32_t is_pending_EXTI(PinName_t pinName);
void clear_pending_EXTI(PinName_t pinName);

#ifdef __cplusplus
}
#endif /* __cplusplus */
	 
#endif // __EC_EXTI2_H

```



#### EXTI_init()

Initializes EXTI ~~

```
void EXTI_init(PinName_t pinName, uint32_t trig_type,uint32_t priority);
```

**Parameters**

- **pinName:** 
- **trig_type**: 
- **priority**: 

**Example code**

```c
EXTI_init(SW2_PIN, FALL, 10);
```



#### EXTI_enable()



```
void EXTI_enable(PinName_t pinName);
```

**Parameters**

- **pinName:**

  

**Example code**

```

```



#### EXTI_disable()



```
void EXTI_disable(PinName_t pinName);
```

**Parameters**

- **pinName:**

  

**Example code**

```

```



#### is_pending_EXTI()



```c
uint32_t is_pending_EXTI(PinName_t pinName);
```

**Parameters**

- **pinName:**

  

**Example code**

```
is_pending_EXTI(SW2_PIN)
```



#### clear_pending_EXTI()



```
void clear_pending_EXTI(PinName_t pinName);
```

**Parameters**

- **pinName:**

  

**Example code**

```c
clear_pending_EXTI(SW2_PIN)
```







