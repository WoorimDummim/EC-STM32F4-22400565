# Embedded Controller - GPIO Library
Written by: Woorim Lee

Program: C/C++

IDE/Compiler: PlatformIO

OS: Win10/11

MCU: STM32F411RE, Nucleo-64



## Table of Contents

* [GPIO Digital In/Out](#gpio-digital-inout)
  
  * [Header File](#header-file)
  
  * [GPIO_init()](#gpio_init)
  
  * [GPIO_mode()](#gpio_mode)
  
  * [GPIO_ospeed()](#gpio_ospeed)
  
  * [GPIO_otype()](#gpio_type)
  
  * [GPIO_pupd()](#gpio_pupd)
  
  * [GPIO_write()](#gpio_write)
  
  * [GPIO_read()](#gpio_read)
  
  * [pinMode()](#pinMode)
  
  * [digitalWrite()](#digitalWrite)
  
  * [digitalRead]()
  
    
  
  * [FND_init](#FND_init)
  
  * [FND_select_init](#FND_select_init)
  
  * [FND_display](#FND_display)
  
  * [FND_select](#FND_select)
  
  * [FND_display_init](#FND_display_init)
  
  * [FND_select_init](#FND_display_init)



## GPIO Digital InOut

### Header File

`#include "ecGPIO.h"`

```c
#ifndef __ECGPIO2_H
#define __ECGPIO2_H

#include "stm32f411xe.h"
#include "ecRCC2.h"
#include "ecPinNames.h"

#define INPUT  0x00
#define OUTPUT 0x01
#define AF     0x02
#define ANALOG 0x03

#define HIGH 1
#define LOW  0

#define EC_PU   01
#define EC_PD   10
#define EC_NO_PUPD 00

#define LED_PIN 	PA_5
#define BUTTON_PIN  PC_13

// ADD MORE  MACRO related to GPIO 
// PU, PD, NO_PUPD, PUSH_PULL, LOW, MEDIUM, etc

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
	 
void GPIO_init(PinName_t pinName, uint32_t mode);     
void GPIO_mode(PinName_t pinName, uint32_t mode);
void GPIO_ospeed(PinName_t pinName, uint32_t speed);
void GPIO_otype(PinName_t pinName, uint32_t type);
void GPIO_pupd(PinName_t pinName, uint32_t pupd);
void GPIO_write(PinName_t pinName, uint32_t Output);
uint32_t  GPIO_read(PinName_t pinName);

// ARDUINO Syntax  (Optional)
void pinMode(PinName_t pin, uint32_t mode);
void digitalWrite(PinName_t pin, uint32_t value);
uint32_t  digitalRead(PinName_t pin);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __ECGPIO2_H

////////////////////////////////////////////////////////////////////
/* Include the following in GPIO.h */
////////////////////////////////////////////////////////////////////

// FND for JKIT board 
extern int numberFND[12][8];
void FND_init(PinName_t *pinFND);
void FND_select_init(PinName_t *selectFND);
void FND_display(uint8_t num);
void FND_select(uint8_t digit);

// Display a number 0 - 9 only
void FND_display_init(PinName_t *pinFND);
//void FND_display(uint8_t  num, PinName_t *pinFND)

// Select display: FND0 to FND3
void FND_select_init(PinName_t *selectFND);
//void FND_select(uint8_t select, PinName_t *selectFND);


```



#### GPIO_init()

Initializes GPIO pins with default setting and Enables GPIO Clock. Mode: In/Out/AF/Analog

```c
void GPIO_init(GPIO_TypeDef *Port, int pin, int mode);
```

**Parameters**

- **Port:** Port Number, GPIOA~GPIOH
- **pin**: pin number (int) 0~15
- **mode**: INPUT(0), OUTPUT(1), AF(02), ANALOG (03)

**Example code**

```c
GPIO_init(GPIOA, 5, OUTPUT);
GPIO_init(GPIOC, 13, INPUT); //GPIO_init(GPIOC, 13, 0);
```



#### GPIO_mode()

Configures GPIO pin modes: In/Out/AF/Analog

```c
void GPIO_mode(GPIO_TypeDef *Port, int pin, int mode);
```

**Parameters**

- **Port:** Port Number, GPIOA~GPIOH
- **pin**: pin number (int) 0~15
- **mode**: INPUT (0), OUTPUT (1), AF(02), ANALOG (03)

**Example code**

```c
GPIO_mode(GPIOA, 5, OUTPUT);
```



#### GPIO_ospeed()

Configures output speed of GPIO pin : Low, Mid, Fast, High

```c
void GPIO_ospeed(GPIO_TypeDef* Port, int pin, int speed);
```

**Parameters**

- **Port:** Port Number, GPIOA~GPIOH
- **pin**: pin number (int) 0~15
- **speed**: LOW_SPEED(0), MID_SPEED(1), FAST_SPEED(2) , HIGH_SPEED(3)

**Example code**

```c
GPIO_ospeed(GPIOA, 5, 2);  // 2: FAST_SPEED
```



#### GPIO_otype()

Configures output type of GPIO pin: Push-Pull / Open-Drain

```c
void GPIO_otype(GPIO_TypeDef* Port, int pin, int type);
```

**Parameters**

- **Port:** Port Number, GPIOA~GPIOH
- **pin**: pin number (int) 0~15
- **type**: PUSH_PULL(0), OPEN_DRAIN(1)

**Example code**

```c
GPIO_otype(GPIOA, 5, 0);  // 0: Push-Pull
```



#### GPIO_pupdr()

Configures Pull-up/Pull-down mode of GPIO pin: No Pull-up, Pull-down/ Pull-up/ Pull-down/ Reserved

```c
void GPIO_pupd(GPIO_TypeDef* Port, int pin, int pupd);
```

**Parameters**

- **Port:** Port Number, GPIOA~GPIOH
- **pin**: pin number (int) 0~15
- **pupd**: NO_PUPD(0), PULL_UP(1), PULL_DOWN(2), RESERVED(3)

**Example code**

```c
GPIO_pupd(GPIOA, 5, 0);  // 0: No Pull-up, Pull-down
```



#### GPIO_write()

Write the data to GPIO pin: High, Low

```c
void GPIO_write(GPIO_TypeDef *Port, int pin, int output);
```

**Parameters**

- **Port:** Port Number, GPIOA~GPIOH
- **pin**: pin number (int) 0~15
- **output**: LOW(0), HIGH(1)

**Example code**

```c
GPIO_write(GPIOA, 5, 1);  // 1: High
```



#### GPIO_read()

Read the data from GPIO pin

```c
int  GPIO_read(GPIO_TypeDef *Port, int pin);
```

**Parameters**

- **Port:** Port Number, GPIOA~GPIOH
- **pin**: pin number (int) 0~15

**Example code**

```c
GPIO_read(GPIOC, 13);
```



#### pinMode()

Configures the specified pin to behave either as an input or an output. (Arduino-like syntax)

```c
void pinMode(PinName_t pin, uint32_t mode);
```

**Parameters**

- **pin**:  Pin name defined in PinName_t (e.g., `PA_5`, `PC_13`)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
- **mode**

**Example code**

```c
pinMode(PA_5, OUTPUT);
pinMode(PC_13, INPUT);
```



#### digitalWrite()

Writes a HIGH or LOW value to a digital output pin. (Arduino-like syntax)

```c
void digitalWrite(PinName_t pin, uint32_t value);
```

**Parameters**

- **pin**: Pin name defined in PinName_t (e.g., `PA_5`)
- **value**: `HIGH` (1) or `LOW` (0)

**Example code**

```c
digitalWrite(PA_5, HIGH);
```



#### digitalRead()

Reads the value from a specified digital pin, either HIGH or LOW. (Arduino-like syntax)

```c
uint32_t  digitalRead(PinName_t pin);
```

**Parameters**

- **pin**: Pin name defined in PinName_t (e.g., `PC_13`)

**Example code**

```c
uint32_t buttonState = digitalRead(PC_13);
```



#### FND_init()

간단설명문

```c
void FND_init(PinName_t *pinFND);
```

**Parameters**

- **pinFND**: Pointer to an array of PinName_t representing the FND segment and select pins.

**Example code**

```c
PinName_t fndPins[8] = {PA_5, PA_6, PA_7, PB_6, PC_7, PA_9, PA_8, PB_10};
FND_init(fndPins);
```



#### FND_display()

Displays a specific single-digit number (0-9) on the active FND.

```
void FND_display(uint8_t num);
```

**Parameters**

- **num:** An integer value from 0 to 9 to be displayed on the FND.

**Example code**

```c
FND_display(7);  // Displays the number 7 on the FND
```



#### FND_select()

Activates a specific FND digit position in a multi-digit FND module.

```
void FND_select(uint8_t digit);
```

**Parameters**

- **digit:** The index of the FND digit to be activated (e.g., 0 to 3 for a 4-digit display).

**Example code**

```c
FND_select(0);   // Activates the first digit of the FND
```



#### FND_display_init()

Initializes only the GPIO pins connected to the FND segments (a-g, dp).

```c
void FND_display_init(PinName_t *pinFND);
```

**Parameters**

- **pinFND**: Pointer to an array of PinName_t representing the 8 segment pins of the FND.

**Example code**

```c
PinName_t segmentPins[8] = {PA_5, PA_6, PA_7, PB_6, PC_7, PA_9, PA_8, PB_10};
FND_display_init(segmentPins);
```



#### FND_select_init()

Initializes the GPIO pins used for selecting specific FND digits in a multiplexed display setup.

```
void FND_select_init(PinName_t *selectFND);
```

**Parameters**

- **selectFND:** Pointer to an array of PinName_t representing the digit selection pins.

**Example code**

```c
PinName_t selectPins[4] = {PB_9, PB_8, PB_7, PC_6};
FND_select_init(selectPins);
```

