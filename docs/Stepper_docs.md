# Embedded Controller - Stepper Library
Written by: Woorim Lee

Program: C/C++

IDE/Compiler: PlatformIO

OS: Windows / Ubuntu 24.04

MCU: STM32F411RE, Nucleo-64



## Table of Contents
* [Stepper](#stepper)
  * [Header File](#header-file)
  * [stepper_init()](#stepper_init)
  * [stepper_speed()](#stepper_speed)
  * [stepper_step()](#stepper_step)
  * [stepper_out()](#stepper_out)
  * [stepper_stop()](#stepper_stop)


## Stepper

### Header File

`#include "ecStepper2.h"`

```c
#ifndef __EC_STEPPER2_H
#define __EC_STEPPER2_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#include "stm32f411xe.h"
#include "ecPinNames.h"
#include "ecRCC2.h"
#include "ecGPIO2.h"
#include "ecSysTick2.h"
			
#define DIR_CW 0
#define DIR_CCW 1	    

// Stepper Mode 
typedef enum {
    HALF = 0,
    FULL = 1
} StepperMode_t;

extern const uint32_t STEP_PER_REV[2];

//State number 
typedef enum {
	S0, S1, S2, S3, S4, S5, S6, S7
} StateNum;

// FULL stepping sequence  - FSM
typedef struct {	
  uint32_t next[2];        // next state
  uint8_t out[4];          // output
} StateStepper_t;

// Initialization of Stepper Motor
void stepper_init(uint32_t mode, PinName_t *pinStepper);
// Converts Motor [rpm] to step delay in [msec]
void stepper_speed (uint32_t speedRPM);
// Run Stepper Motor for given steps and direction
void stepper_step(uint32_t steps, uint32_t direction);
// Stepper Motor Output for given state
void stepper_out(uint32_t state);
// Stop Stepper Motor
void stepper_stop(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __EC_STEPPER2_H
```



#### stepper_init()

Initializes the specified GPIO pins as digital outputs for the stepper motor and sets the operating mode (Half-stepping or Full-stepping) for the Finite State Machine.

```c
void stepper_init(uint32_t mode, PinName_t *pinStepper);
```

**Parameters**

- **mode:** `HALF` (0) or `FULL` (1).
- **pinStepper:** Pointer to an array of 4 `PinName_t` elements representing the motor driver pins (e.g., A, B, AN, BN).

**Example code**

```c
PinName_t motorPins[4] = {PB_10, PB_4, PB_5, PB_3};
stepper_init(FULL, motorPins);
```



#### stepper_speed()

Calculates and sets the required step delay in milliseconds to achieve the target Rotations Per Minute (RPM) based on the current stepping mode.

```c
void stepper_speed(uint32_t speedRPM);
```

**Parameters**

- **speedRPM:** The target speed in RPM.

**Example code**

```c
stepper_speed(14);  // Sets the motor speed to 14 RPM
```



#### stepper_step()

Executes the motor rotation for a given number of steps in the specified direction using the Finite State Machine (FSM).

```c
void stepper_step(uint32_t steps, uint32_t direction);
```

**Parameters**

- **steps:** The total number of steps to rotate.
- **direction:** `DIR_CW` (0) for clockwise or `DIR_CCW` (1) for counter-clockwise.

**Example code**

```c
stepper_step(2048, DIR_CW);  // Rotates 2048 steps clockwise
```



#### stepper_out()

Outputs the 4-bit sequence logic corresponding to the current FSM state to the specific motor driver pins.

```c
void stepper_out(uint32_t state);
```

**Parameters**

- **state:** The current state index (e.g., 0 to 7) of the FSM sequence array.

**Example code**

```c
stepper_out(3);  // Outputs the pin logic for sequence index 3
```



#### stepper_stop()

Instantly halts the stepper motor operation by clearing the remaining step count to zero and driving all motor GPIO pins LOW to cut off current to the coils.

```c
void stepper_stop(void);
```

**Parameters**

- **None**

**Example code**

```c
stepper_stop();  // Immediately stops the motor
```

