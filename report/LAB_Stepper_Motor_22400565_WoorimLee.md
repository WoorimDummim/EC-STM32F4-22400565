# LAB: Stepper Motor

**Date:** 2026-10-14

**Author/Partner:** WoorimLee

**Demo Video:** [[EC 26-2] LAB (Stepper Motor)](https://youtu.be/G5TREwSk1WY)

**PDF version:** [LAB_Stepper_Motor.pdf](./LAB_Stepper_Motor_22400565_WoorimLee.pdf)



## Introduction

This lab demonstrates how to drive a stepper motor using the digital GPIO outputs of an MCU. A Finite State Machine (FSM) is utilized to implement the stepper motor control algorithm.

#### Requirement

**Hardware**

- MCU
  - NUCLEO-F411RE
- Actuator/Sensor/Others:
  - **Tutorial:**
    - Stepper Motor SM-42BYG011 (12V)
    - Motor Driver A4988
  - **Lab:**
    - Stepper Motor 28BYJ-48 (5V)
    - Motor Driver ULN2003
  - breadboard

**Software**

- Keil uVision, CMSIS, EC_HAL library

  

## Tutorial: Stepper Motor Driver (A4988)

A simple method to drive a stepper motor is using a motor driver that receives only a pulse and direction pin.



#### Results

<img src="img/KakaoTalk_20261012_130815334_02.jpg" alt="KakaoTalk_20261012_130815334_02" style="zoom:8%;" />

​	The A4988 motor driver was successfully tested using a simplified STEP/DIR interface (DIR, STEP, ENABLE).



## Problem : Stepper Motor Control with FSM

### Problem Description

This lab utilizes a stepper motor driver that requires a sequence of 4-input pulses.

- **Driver:** **ULN2003 motor driver.**[ULN2003 spec sheet](https://www.electronicoscaldas.com/datasheet/ULN2003A-PCB.pdf)

- **Motor:** 28BYJ-48, Search for the spec sheet

  <img src="img/스크린샷 2026-10-12 125014.png" alt="스크린샷 2026-10-12 125014" style="zoom:67%;" />

1. Find out the number of steps required to rotate 1 revolution of the stepper motor with Full-steppping.
2. Then, rotate the stepper motor 5 revolutions with 1 rpm.
3. Repeat the above process in the opposite direction.
4. Increase and decrease the speed of the motor as fast as it can rotate to find the maximum and minimum speed of the motor.
5. Apply the half-stepping and repeat the above.



### FSM design for Stepper Motor Sequence

A Finite State Machine (FSM) method is applied to drive the stepper motor.



#### State Table for Full-Stepping

**Full-stepping sequence**

<center><img src="img/그림1.png" alt="그림1" style="zoom: 90%;" /></center>

<img src="img/스크린샷 2026-10-12 125916.png" alt="스크린샷 2026-10-12 125916" style="zoom: 67%;" />



- **State Table**: Moore FSM

<img src="img/스크린샷 2026-10-14 061247.png" alt="스크린샷 2026-10-14 061247" style="zoom: 90%;" />



#### State Table for Half-Stepping

**Half-stepping sequence**

<img src="img/스크린샷 2026-10-12 135549.png" alt="스크린샷 2026-10-12 135549" style="zoom: 80%;" />

<img src="img/스크린샷 2026-10-12 140631.png" alt="스크린샷 2026-10-12 140631" style="zoom: 67%;" />



- **State Table**: Moore FSM

<img src="img/스크린샷 2026-10-12 140623.png" alt="스크린샷 2026-10-12 140623" style="zoom: 67%;" />



#### Programming FSM

**Function Definitions**

`ecStepper2.h`

```c
// Stepper Mode
typedef enum {
    HALF = 0,
    FULL = 1
} StepperMode_t;

extern const uint32_t STEP_PER_REV[2];
```

​	An enum is utilized to index the STEP_PER_REV array, distinguishing the required steps for Half and Full-stepping modes without conditional branching.



`ecStepper2.c`

```c
// Initialization of Stepper Motor
void stepper_init(uint32_t mode, PinName_t *pinStepper){
	if (mode == HALF) 
		fsm = fsm_Half;
	else
		fsm = fsm_Full;

	_mode = mode;                          // Stores the selected operating mode (HALF or FULL)

	//  GPIO Digital Out Initiation
	// For A, B, AN, BN

	for (int i=0; i<4; i++){
		stepperPins[i] = pinStepper[i];                             
		GPIO_init(stepperPins[i], OUTPUT); // Initializes the assigned stepper motor pins as digital outputs
	}
}
```

​	Initializes the assigned GPIO pins as digital outputs and sets the internal FSM pointer to either the Half-step or Full-step sequence array based on the selected mode.



```c
// Converts Motor [rpm] to step delay in [msec]
void stepper_speed (uint32_t speedRPM){                             // rpm
		_step_delay = 60*1000/(STEP_PER_REV[_mode]*speedRPM); 		//in [msec]	
		// [usec] can be used for a higher accuracy 
}		  
```

​	Calculates and sets the required time delay (in milliseconds) between each step based on the target RPM and the specific `STEP_PER_REV` value mapped to the current mode.



```c
// Run Stepper Motor for given steps and direction
void stepper_step(uint32_t steps, uint32_t direction){
	// Exit if stepper_init() not called 
	if (fsm == 0) return;
	_steps = steps;							  // Stores the target number of steps

	// run for step size: 
	for (uint32_t i = 0; i < _steps; i++){
		// Update Present State
		state = fsm[state].next[direction];   // Updates the FSM state based on the current row and target direction column
		
		// Output of Present State
		stepper_out(state);                // Outputs the 4-bit sequence corresponding to the current state
	
		// Delay for steppermotor speed
		delay_ms(_step_delay);				  // delay
	}
}
```

​	Executes the motor rotation for a specified number of steps and direction. It continuously updates the FSM state based on the direction input and calls the output function while applying the calculated step delay.



```c
// Stepper Motor Output for given state
void stepper_out(uint32_t state){
	
	// stepperPins[0]=A, stepperPins[1]=B, ...
	// out[0]=A, out[1]=B, ...

    // Writes the corresponding FSM output logic to the stepper pins
	for (int i=0; i<4; i++) GPIO_write(stepperPins[i], fsm[state].out[i]);  
}
```

​	Reads the 4-bit output sequence array corresponding to the current FSM state and writes the logic levels to the four designated motor GPIO pins.



```c
// Stop Stepper Motor
void stepper_stop(void) {
    _steps = 0;    
    // All pins DigitalOut '0'
    
    // Halts the motor by setting all stepper pins to LOW (0)
	for (int i=0; i<4; i++) GPIO_write(stepperPins[i], 0);			
}
```

 	Instantly halts the motor operation by clearing the remaining step count to zero and setting all four motor GPIO pins to LOW, effectively cutting off the current to the coils.



##### Code

`LAB_Stepper_Motor_22400565.c`

```c
// ( A, B,  AN,  BN)
PinName_t pinStepper[4]    = {PB_10,PB_4,PB_5,PB_3};
uint32_t steps = 0; 

StepperMode_t current_mode = FULL;                  		// Select mode(HALF or FULL)  
uint32_t rev = 1;
int speed = 14;               
```



```c
// Initialiization 
void setup(void){	
	RCC_PLL_init();                                 // System Clock = 84MHz
	SysTick_init();                                 // Systick init
	
	GPIO_init(BUTTON_PIN, INPUT);           		// GPIOC pin13 initialization
    EXTI_init(BUTTON_PIN, FULL, 0);           		// External Interrupt Setting

	stepper_init(current_mode, pinStepper); 				// Stepper GPIO pin initialization
	stepper_speed(speed);                          		//  set stepper motor speed
}
```

​	Configures the system environment before the main loop execution by initializing the system clock, SysTick, the EXTI button pin, and the stepper motor parameters including GPIO pins and initial speed.



```c
int main(void) { 
	// Initialiization --------------------------------------------------------
	setup();

	steps = STEP_PER_REV[current_mode]*rev;
	
	// Inifinite Loop ----------------------------------------------------------
	while(1){
		stepper_step(steps, DIR_CCW);     // (Step : 2048, Direction : 0, Mode : FULL or HALF)
		delay_ms(1000);
		stepper_step(steps, DIR_CW);    // (Step : 2048, Direction : 1, Mode : FULL or HALF)
		delay_ms(1000);
	}
}
```

​	The main loop alternates the motor rotation for one full revolution clockwise and counter-clockwise with a 1-second interval.



```c
void EXTI15_10_IRQHandler(void) {  
	if (is_pending_EXTI(BUTTON_PIN)) {
		stepper_stop();
		clear_pending_EXTI(BUTTON_PIN); // cleared by writing '1'
	}
}
```

​	If the push-button is pressed during operation, the EXTI handler is triggered to instantly halt the motor.



#### Discussion

**1. Find out the trapezoid-shape velocity profile for a stepper motor. When is this profile necessary?**

​	A trapezoidal velocity profile consists of three distinct phases: constant acceleration, constant maximum velocity, and constant deceleration. This profile is strictly necessary when driving a stepper motor with a high-inertia load or when aiming for high-speed operations. If a motor starts abruptly at a high target speed without an acceleration phase (a rectangular profile), it is highly likely to stall or lose steps due to mechanical inertia. Applying gradual acceleration and deceleration ensures smooth mechanical transitions, prevents step loss, and reduces mechanical vibration.



**2. How would you change the code more efficiently for micro-stepping control? You don’t have to code this but need to explain your strategy.**

​	For micro-stepping control, the current Finite State Machine (FSM) approach—which utilizes a hardcoded array of discrete GPIO HIGH/LOW states—becomes highly inefficient, as the number of required states increases exponentially (e.g., 64 states for 1/16 micro-stepping). A more efficient strategy is to transition from discrete GPIO toggling to Pulse Width Modulation (PWM) control. By utilizing a mathematical look-up table (LUT), such as sine and cosine values, the MCU can dynamically adjust the PWM duty cycles for the motor coils. This method proportionally controls the coil currents, eliminating the need for massive state arrays and allowing for smooth, high-resolution micro-stepping with minimal memory overhead.



**3. There are other types of Stepper Motor Drivers that are simple to use, such as you only give one pulse signal and direction, instead of giving 4 pulse signals. Such examples are A4988, DRV 8834, and TB6600 drivers. Compare these motor drivers with ULN2003 in terms of operating method.**

​	The ULN2003 is essentially a basic Darlington transistor array acting as a current amplifier. When using the ULN2003, the MCU must directly manage the complex phase sequencing by sending 4 separate pulse signals to control each coil (requiring 4 GPIO pins and FSM software logic). In contrast, dedicated drivers like the A4988, DRV8834, and TB6600 feature built-in hardware indexers and logic. They operate using a highly simplified STEP/DIR (Pulse/Direction) interface. The MCU only needs to use 2 GPIO pins: one pin to provide a single pulse signal to advance the motor one step, and another pin to set a logic HIGH/LOW for the direction. This significantly reduces the MCU's GPIO usage and offloads the complex phase sequencing burden to the driver hardware.



#### Results

**Full_CW_1RPM**

| ![Screenshot 2026-10-15 000704](img/Screenshot 2026-10-15 000704.png)(a) | ![Screenshot 2026-10-15 000712](img/Screenshot 2026-10-15 000712.png) (b) |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
| ![Screenshot 2026-10-15 000720](img/Screenshot 2026-10-15 000720.png)**(c)** | ![Screenshot 2026-10-15 000744](img/Screenshot 2026-10-15 000744.png)**(d)** |

​	The time-lapse sequence from (a) to (d) illustrates the stepper motor completing one full revolution in the clockwise direction. The motor is driven using the Full-stepping FSM algorithm with a target speed of 1 RPM. A stopwatch was utilized to track the real-time execution of the rotation. As captured in panel (d), one complete revolution takes approximately 57.43 seconds. This visual evidence clearly demonstrates the continuous operation of the control logic and practically verifies the timing discrepancy caused by the integer truncation error in the `delay_ms()` function, as analyzed in the discussion section.



**Half_CCW_1RPM**

| ![Screenshot 2026-10-15 001259](img/Screenshot 2026-10-15 001259.png)(a) | ![Screenshot 2026-10-15 001307](img/Screenshot 2026-10-15 001307.png)(b) |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
| ![Screenshot 2026-10-15 001314](img/Screenshot 2026-10-15 001314.png)**(c)** | ![Screenshot 2026-10-15 001327](img/Screenshot 2026-10-15 001327.png)**(d)** |

​	The time-lapse sequence from (a) to (d) captures the stepper motor completing one full revolution in the counter-clockwise (CCW) direction using the Half-stepping FSM algorithm. With a target speed of 1 RPM, the enumeration-based look-up table (LUT) dynamically adjusts the total required steps per revolution to 4096. As shown in panel (d), the single revolution is completed in approximately 57.61 seconds. This real-world measurement closely aligns with the theoretically calculated duration (approx. 57.34 seconds), further validating the systemic integer truncation error while confirming the proper operation of the mode-switching and directional control logic.



**Maximum Speed Operation (14 RPM)**	

​	While it is visually challenging to capture the exact speed of 14 RPM through static photographs, the motor was experimentally confirmed to operate smoothly up to this threshold. Beyond 14 RPM, the motor exhibited noticeable step loss and stalling. As detailed in the subsequent technical analysis, this limitation is a combined result of the mechanical inertia of the rotor and the integer resolution constraints of the `delay_ms()` software function. Thus, the maximum operational speed is firmly documented at 14 RPM without a sequential time-lapse.



**EXTI Interrupt Trigger (Motor Halt)**

​	Although visual documentation for this specific feature was not explicitly requested in the problem description, the hardware interrupt functionality was additionally verified during the experiment. When the push-button was pressed while the motor was in continuous rotation, the EXTI handler successfully interrupted the main FSM loop. The `stepper_stop()` function was triggered, instantly halting the motor and driving all corresponding GPIO pins LOW to cut off the coil currents. This confirms the reliable responsiveness of the external interrupt logic implemented in the system.



**1. Timing Discrepancy Analysis at 1 RPM (Integer Truncation Error)**

​	During the 1 RPM operation test, timing discrepancies were observed in both modes. In Half-stepping mode (4096 steps/rev), the ideal delay is 
$$
60000ms / 4096 = 14.648ms
$$
​	However, due to integer truncation (`uint32_t`), the delay is fixed at 14 ms, resulting in a total revolution time of 
$$
14 \text{ ms} \times 4096 \text{ steps} = 57,344 \text{ ms} (57.34 s)
$$


​	Similarly, in Full-stepping mode (2048 steps/rev), the ideal delay is calculated as $60,000 
$$
\text{ ms} / 2048 = 29.297 \text{ ms}.
$$
​	This truncates to 29 ms, resulting in a total time of 
$$
29 \text{ ms} \times 2048 \text{ steps} = 59,392 \text{ ms}(59.39s)
$$
​	The truncation error is more pronounced in Half-stepping mode due to its smaller ideal delay value. This highlights the resolution limitation of millisecond-level delays (`delay_ms`), suggesting that microsecond delays (`delay_us`) or hardware timer interrupts are required for precise motor speed control.



**2. Maximum Speed Limitation (Software and Hardware Constraints)**

​	During the speed test, the maximum operational speed for both modes was identified as 14 RPM. This limitation arises from a combination of software resolution limits and physical hardware characteristics.

​	From a software perspective, in Half-stepping mode at 14 RPM, the step delay is calculated as 
$$
60,000 / (4096 \times 14) \approx 1.04 \text{ ms},
$$
which truncates to exactly 1 ms. If the speed is increased to 15 RPM, the calculated delay drops below 
$$
1 ms (0.97 \text{ ms})
$$
, truncating to 0 ms. A delay of 0 ms instructs the MCU to output pulses without any wait time.

​	From a hardware perspective, stepper motor coils have electrical inductance, requiring a minimum amount of time for the magnetic field to build up. Additionally, the rotor has mechanical inertia. If the GPIO pulse frequency is too high 
$$
(delay \le 1 \text{ ms})
$$
, the rotor cannot physically catch up with the rapidly changing magnetic field. This phenomenon is known as "step loss" or stalling, where the motor merely vibrates in place without rotating.