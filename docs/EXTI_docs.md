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

Initializes the External Interrupt (EXTI) for a specified GPIO pin, configures the trigger edge condition, and sets the interrupt priority in the NVIC.

```c
void EXTI_init(PinName_t pinName, uint32_t trig_type,uint32_t priority);
```

**Parameters**

- **pinName:** Pin name defined in PinName_t (e.g., `PC_13` for the user button).
- **trig_type**: Trigger condition for the interrupt. Use `FALL` (0), `RISE` (1), or `BOTH` (2).
- **priority**: NVIC interrupt priority level (0 to 15, where a lower number indicates a higher priority).

**Example code**

```c
EXTI_init(SW2_PIN, FALL, 10);
```



#### EXTI_enable()

Enables the external interrupt for the specified pin by unmasking the corresponding bit in the Interrupt Mask Register (IMR).

```c
void EXTI_enable(PinName_t pinName);
```

**Parameters**

- **pinName:** Pin name defined in PinName_t (e.g., `PC_13`).

**Example cod**

```c
EXTI_enable(PC_13);
```



#### EXTI_disable()

Disables the external interrupt for the specified pin by masking the corresponding bit in the Interrupt Mask Register (IMR).

```c
void EXTI_disable(PinName_t pinName);
```

**Parameters**

- **pinName:** Pin name defined in PinName_t (e.g., `PC_13`).

**Example code**

```c
EXTI_disable(PC_13);
```



#### is_pending_EXTI()

Checks whether the EXTI pending bit is set for the specified pin, indicating that an interrupt request has occurred.

```c
uint32_t is_pending_EXTI(PinName_t pinName);
```

**Parameters**

- **pinName:** Pin name defined in PinName_t (e.g., `PC_13`).

**Example code**

```
is_pending_EXTI(SW2_PIN)
```



#### clear_pending_EXTI()

Clears the EXTI pending bit for the specified pin. This function must be called inside the interrupt service routine (ISR) to prevent infinite interrupt loops.

```c
void clear_pending_EXTI(PinName_t pinName);
```

**Parameters**

- **pinName:** Pin name defined in PinName_t (e.g., `PC_13`).

**Example code**

```c
clear_pending_EXTI(PC_13);  // Clears the pending bit (usually by writing '1' to the PR register)
```







